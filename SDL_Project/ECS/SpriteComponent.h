#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"
#include "../Camera.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	int animIndex = 0;
	int flip = 0;
	std::map<const char*, Animation>animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTex(id);
	}
	SpriteComponent(int flipStatus)
	{
		if (flip == 0)
		{
			spriteFlip = SDL_FLIP_NONE;
			std::cout << "No Flip Proj" << std::endl;
		}
		if (flip == 1)
		{
			spriteFlip = SDL_FLIP_HORIZONTAL;
			std::cout << "Flip Proj" << std::endl;
		}
	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 6, 100);
		Animation walk = Animation(1, 6, 100);
		Animation slash = Animation(2, 6, 100);
		Animation died = Animation(3, 6, 100);
		Animation diedFrame = Animation(4, 1, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		animations.emplace("Slash", slash);
		animations.emplace("Died", died);
		animations.emplace("DiedFrame",diedFrame);

		Play("Idle");

		setTex(id);
	}

	~SpriteComponent()
	{
		//SDL_DestroyTexture(texture);
	}
	
	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}
	

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.h = transform->height;
		srcRect.w = transform->width; 
		
	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

		}
		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::cam->camPos.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::cam->camPos.y;
		destRect.h = transform->height * transform->scale;
		destRect.w = transform->width * transform->scale;

		
	}

	void draw() override
	{
		TextureManager::DrawTexture(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};