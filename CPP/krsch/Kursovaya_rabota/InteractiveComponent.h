#pragma once
#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"

class InteractiveComponent : public Component
{
public:
	SDL_Rect interaction;
	std::string tag;
	

	SDL_Texture* texI;
	SDL_Rect srcR, destR;

	TransformComponent* transform;

	InteractiveComponent(std::string t)
	{
		tag = t;
	}

	InteractiveComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		interaction.x = xpos;
		interaction.y = ypos;
		interaction.h = interaction.w = size;
	}

	InteractiveComponent(std::string t, int xpos, int ypos, int size, int type)
	{
		tag = t;
		interaction.x = xpos;
		interaction.y = ypos;
		interaction.h = interaction.w = size;

	}



	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

		texI = TextureManager::LoadTexture("spites/World/InteractionTex.png");
		srcR = { 0, 0, 32, 32 };
		destR = { interaction.x, interaction.y, interaction.w, interaction.h };

	}

	void update() override
	{
		if (tag != "Karta")
		{
			interaction.x = static_cast<int>(transform->position.x);
			interaction.y = static_cast<int>(transform->position.y);
			interaction.w = transform->width * transform->scale;
			interaction.h = transform->height * transform->scale;
		}

		destR.x = interaction.x - Game::camera.x;
		destR.y = interaction.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texI, srcR, destR, SDL_FLIP_NONE);
	}

private:

};