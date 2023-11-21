#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Vector2D.h"

class AssetManager;
class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	bool collision(SDL_Rect cCol, SDL_Rect playerCol);
	Vector2D generateRandomPosition();
	Vector2D lerp(const Vector2D& start, const Vector2D& end, float percentage);
	


	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupNPCs,
		groupInteractive
	};
	bool isPaused() const {
		return paused;
	}
	void togglePause() {
		paused = !paused;
	}
private:
	bool paused = false;
	int cnt = 0;
	SDL_Window *window;
	bool resumeButtonHovered;
	bool exitButtonHovered;
	int mouseX;
	int mouseY;
};