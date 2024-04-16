#pragma once
#include "Sprite.h"

namespace Game
{
	class HUD :public Sprite
	{
	public:
		void InitializeInventory(SDL_Renderer* pRenderer, const std::string& sphereFilepath, const std::string& healthFilepath, const std::string& GameoverFilepath, const std::string& victoryFilepath, const std::string& powerupFilepath);

		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);

	private:
		SDL_Texture* SphereTexture;
		SDL_Texture* HealthTexture;
		SDL_Texture* gameOverSprite;
		SDL_Texture* VictoryTexture;
		SDL_Texture* PowerupTexture;
	};
}