#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"

class InteractiveComponent : public Component
{
public:
    SDL_Rect interactiveArea;
    std::string tag;
    int interactionType;

    SDL_Texture* tex;
    SDL_Rect srcR, destR;

    TransformComponent* transform;

    InteractiveComponent(std::string t)
    {
        tag = t;
    }

    InteractiveComponent(std::string t, int xpos, int ypos, int size)
    {
        tag = t;
        interactiveArea.x = xpos;
        interactiveArea.y = ypos;
        interactiveArea.h = interactiveArea.w = size;
    }

    InteractiveComponent(std::string t, int xpos, int ypos, int size, int interaction)
    {
        tag = t;
        interactiveArea.x = xpos;
        interactiveArea.y = ypos;
        interactiveArea.h = interactiveArea.w = size;
        interactionType = interaction;  // Инициализируем новое поле типом взаимодействия
    }

    void setInteractionType(int interaction)
    {
        interactionType = interaction;
    }

    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();

        tex = TextureManager::LoadTexture("sprites/World/InteractionTex.png");
        srcR = { 0, 0, 32, 32 };
        destR = { interactiveArea.x, interactiveArea.y, interactiveArea.w, interactiveArea.h };

    }

    void update() override
    {
        // Логика обновления компонента взаимодействия, если необходимо
        // Например, обновление координат области взаимодействия относительно положения объекта

        interactiveArea.x = static_cast<int>(transform->position.x);
        interactiveArea.y = static_cast<int>(transform->position.y);
        interactiveArea.w = transform->width * transform->scale;
        interactiveArea.h = transform->height * transform->scale;
    }

    void draw() override
    {
        // Логика отрисовки компонента взаимодействия, если необходимо
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }

private:

};
#pragma once
