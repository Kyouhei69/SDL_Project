#include "AssetManager.h"
#include "ECS/Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id, std::string flip)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>(id, false);

	if (flip == "Left")
	{
		projectile.getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_HORIZONTAL;
	}
	if (flip == "Right")
	{
		projectile.getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_NONE;
	}

	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	

	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));

}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

