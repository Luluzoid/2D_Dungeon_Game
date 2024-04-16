#pragma once
#include "Sprite.h"

namespace Game
{
	class RoomRenderer :public Sprite
	{
	public:
		void InitializeTiles(SDL_Renderer* pRenderer, const std::string& floorFilepath, const std::string& wallFilepath);

		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);

	private:
		SDL_Texture* FloorTexture;
		SDL_Texture* WallTexture;
	};
}