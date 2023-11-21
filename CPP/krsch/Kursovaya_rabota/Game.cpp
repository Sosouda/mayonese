#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640};

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& label(manager.addEntity());
auto& notplcar(manager.addEntity());
auto& label2(manager.addEntity());

float movementTimer = 0.0f;
float movementInterval = 180.0f;
float lerpSpeed = 0.1f;
Vector2D targetPos;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}
	
	assets->AddTexture("Karta", "spites/World/Karta.png");
	assets->AddTexture("player", "spites/Players/Elf/mPlayer_ [elf].png");
	assets->AddTexture("notplcar", "spites/NPC/morganLeFay_.png");
	assets->AddTexture("pauseM", "spites/World/PauseMenu.png");
	assets->AddFont("ComicSans", "spites/comic.ttf", 16);

	map = new Map("Karta", 2, 32);

	map->LoadMap("spites/World/Karta2.map", 32, 32);

	player.addComponent<TransformComponent>(1063, 1067, 32 , 32, 3);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	notplcar.addComponent<TransformComponent>(820,1156,32,32,3);
	notplcar.addComponent<SpriteComponent>("notplcar", true);
	notplcar.addComponent<ColliderComponent>("notplcar");
	SDL_Color white = { 255,255,255,255 };
	SDL_Color black = { 0,0,0,0 };
	notplcar.addGroup(groupNPCs);
	targetPos = generateRandomPosition();
	label.addComponent<UILabel>(10, 10, "Hello World!", "ComicSans", white);
	label2.addComponent<UILabel>(30, 30, "Hi", "ComicSans", black);
	
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& npc(manager.getGroup(Game::groupNPCs));
auto& interactive(manager.getGroup(Game::groupInteractive));
void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEMOTION:
		mouseX = event.motion.x;
		mouseY = event.motion.y;
		break;
	case SDL_KEYDOWN:
		switch(event.key.keysym.sym){
		case SDLK_ESCAPE:
				togglePause();
				break;
		case SDLK_e:

			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (isPaused()) {
			// Обработка клика на кнопке "Продолжить"
			if (resumeButtonHovered) {
				togglePause();
			}

			// Обработка клика на кнопке "Выйти из игры"
			if (exitButtonHovered) {
				isRunning = false;
			}
		}
		break;
	default:
		break;
	}
}

	



bool isMoving = false;

void Game::update()
{	
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D playerVel = player.getComponent<TransformComponent>().velocity;

	SDL_Rect npcCol = notplcar.getComponent<ColliderComponent>().collider;
	Vector2D npcPos = notplcar.getComponent<TransformComponent>().position;
	
	
	std::stringstream ss;
	std::stringstream ss2;
	ss << "Player position: " << playerPos;
	//ss2 << "Current Tile: " << CurrentTile;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "ComicSans");
	label2.getComponent<UILabel>().SetLabelText(ss2.str(), "ComicSans");


	manager.refresh();
	manager.update();
	movementTimer += 0.1f;
	
	if (movementTimer >= movementInterval)
	{
		npcPos = notplcar.getComponent<TransformComponent>().position;
		targetPos = generateRandomPosition();

		movementTimer = 0.0f;
	}
	Vector2D currentPosition = notplcar.getComponent<TransformComponent>().position;
	Vector2D newPosition = lerp(currentPosition, targetPos, lerpSpeed);
	bool collided = false;
	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, npcCol)) {
			notplcar.addComponent<TransformComponent>().position.x = currentPosition.x;
			notplcar.addComponent<TransformComponent>().position.y = currentPosition.y;
			break;
		}
	}
	if (!collided) {
		// Если нет столкновений, обновляем позицию NPC
		notplcar.getComponent<TransformComponent>().position = newPosition;

		// Проверяем, нужно ли проиграть анимацию
		if (currentPosition != newPosition) {
			notplcar.getComponent<SpriteComponent>().Play("Walk");
		}
		else {
			notplcar.getComponent<SpriteComponent>().Play("Idle");
		}
	}

	
	for (auto& c : colliders){
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	
	}
					
	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y);
	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > camera.w) camera.x = camera.w;
	if (camera.y > camera.h*2) camera.y = camera.h*2;



}


void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& npc : npc) {
		npc->draw();
	}
	for (auto& i : interactive) {
		i->draw();
	}
	label.draw();

	if (isPaused()) {
		// Отрисовка прямоугольника по центру экрана
		SDL_Rect pauseRect;
		pauseRect.w = 300;
		pauseRect.h = 300;
		pauseRect.x = camera.w / 2 - pauseRect.w / 2;
		pauseRect.y = camera.h / 2 - pauseRect.h;
		SDL_RenderCopy(renderer, assets->GetTexture("pauseM"), nullptr, &pauseRect);

		player.getComponent<TransformComponent>().velocity = Vector2D(0,0);
		player.getComponent<SpriteComponent>().Play("Idle");
		notplcar.getComponent<TransformComponent>().velocity = Vector2D(0, 0);
		notplcar.getComponent<SpriteComponent>().Play("Idle");

		SDL_Color textColor = { 255, 255, 255, 255 };
		SDL_Surface* PauseMessage = TTF_RenderText_Solid(assets->GetFont("ComicSans"), "Paused", textColor);
		SDL_Texture* pauseText = SDL_CreateTextureFromSurface(renderer, PauseMessage);
		SDL_Rect textPRect;
		textPRect.w = PauseMessage->w;
		textPRect.h = PauseMessage->h;
		textPRect.x = pauseRect.x + pauseRect.w / 4;
		textPRect.y = pauseRect.y + pauseRect.h / 4;
		SDL_RenderCopy(renderer, pauseText, NULL, &textPRect);

		

		SDL_Rect resumeButtonRect;
		resumeButtonRect.w = 100;
		resumeButtonRect.h = 25;
		resumeButtonRect.x = pauseRect.x/2 + pauseRect.w /2 + 75;
		resumeButtonRect.y = pauseRect.y + pauseRect.h / 2 - 25;
		

		// Определение, находится ли курсор мыши над кнопкой "Продолжить"
		resumeButtonHovered = (mouseX >= resumeButtonRect.x && mouseX <= resumeButtonRect.x + resumeButtonRect.w &&
			mouseY >= resumeButtonRect.y && mouseY <= resumeButtonRect.y + resumeButtonRect.h);

		// Отрисовка кнопки с учетом состояния наведения
		if (resumeButtonHovered) {
			SDL_SetRenderDrawColor(renderer, 245, 222, 179, 255);  // Цвет хаки (или другой цвет на ваш выбор)
		}
		else {
			SDL_SetRenderDrawColor(renderer, 210, 180, 140, 255);  // Другой цвет для неактивного состояния
		}
		SDL_RenderFillRect(renderer, &resumeButtonRect);

		SDL_Surface* ResumeMessage = TTF_RenderText_Solid(assets->GetFont("ComicSans"), "Resume", textColor);
		SDL_Texture* ResumeText = SDL_CreateTextureFromSurface(renderer, ResumeMessage);
		SDL_Rect textRRect;
		textRRect.w = ResumeMessage->w;
		textRRect.h = ResumeMessage->h;
		textRRect.x = resumeButtonRect.x + resumeButtonRect.w / 4;
		textRRect.y = resumeButtonRect.y + resumeButtonRect.h / 8;
		SDL_RenderCopy(renderer, ResumeText, NULL, &textRRect);

		// Отрисовка кнопки "Выйти из игры"
		SDL_Rect exitButtonRect;
		exitButtonRect.w = 100;
		exitButtonRect.h = 25;
		exitButtonRect.x = pauseRect.x/2 + pauseRect.w /2 + 75;
		exitButtonRect.y = resumeButtonRect.y + resumeButtonRect.h + 10;
		
	
		// Определение, находится ли курсор мыши над кнопкой "Выйти из игры"
		exitButtonHovered = (mouseX >= exitButtonRect.x && mouseX <= exitButtonRect.x + exitButtonRect.w &&
			mouseY >= exitButtonRect.y && mouseY <= exitButtonRect.y + exitButtonRect.h);

		// Отрисовка кнопки с учетом состояния наведения
		if (exitButtonHovered) {
			SDL_SetRenderDrawColor(renderer, 245, 222, 179, 255);  // Цвет хаки
		}
		else {
			SDL_SetRenderDrawColor(renderer, 210, 180, 140, 255);  // Другой цвет для неактивного состояния
		}
		SDL_RenderFillRect(renderer, &exitButtonRect);

		SDL_Surface* ExitMessage = TTF_RenderText_Solid(assets->GetFont("ComicSans"), "Exit Game", textColor);
		SDL_Texture* ExitText = SDL_CreateTextureFromSurface(renderer, ExitMessage);
		SDL_Rect textERect;
		textERect.w = ExitMessage->w;
		textERect.h = ExitMessage->h;
		textERect.x = exitButtonRect.x + exitButtonRect.w / 8;
		textERect.y = exitButtonRect.y + exitButtonRect.h / 8;
		SDL_RenderCopy(renderer, ExitText, NULL, &textERect);
		

		SDL_FreeSurface(PauseMessage);
		SDL_FreeSurface(ResumeMessage);
		SDL_FreeSurface(ExitMessage);
		SDL_DestroyTexture(pauseText);
		SDL_DestroyTexture(ResumeText);
		SDL_DestroyTexture(ExitText);
	}


	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

Vector2D Game::generateRandomPosition()
{
	// Генерируем случайное смещение в пределах 50 пикселей по осям x и y
	int offsetX = rand() % 61 - 25;
	int offsetY = rand() % 61 - 25;

	// Возвращаем новую позицию на основе текущей позиции и смещения
	Vector2D currentPosition = notplcar.getComponent<TransformComponent>().position;
	return Vector2D(currentPosition.x + offsetX, currentPosition.y + offsetY);
}

Vector2D Game::lerp(const Vector2D& start, const Vector2D& end, float percentage)
{
	// Вычисляем новую позицию на основе процента исходного и конечного значения
	float x = start.x + (end.x - start.x) * percentage;
	float y = start.y + (end.y - start.y) * percentage;
	return Vector2D(x, y);
}

