#include "HUD.h"

using namespace Game;

void HUD::InitializeInventory(SDL_Renderer* pRenderer, const std::string& sphereFilepath, const std::string& healthFilepath, const std::string& GameoverFilepath, const std::string& victoryFilepath, const std::string& powerupFilepath)
{
	SphereTexture = LoadTexture(pRenderer, sphereFilepath);
	HealthTexture = LoadTexture(pRenderer, healthFilepath);
	gameOverSprite = LoadTexture(pRenderer, GameoverFilepath);
	VictoryTexture = LoadTexture(pRenderer, victoryFilepath);
	PowerupTexture = LoadTexture(pRenderer, powerupFilepath);
}

void HUD::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
{
	//inventory
	for (unsigned int i = 0; i < playerState.Inventory.size(); i++)
	{
		const ItemType& currItem = playerState.Inventory[i];

		switch (currItem)
		{
		case Item_SPHERE:
			MyTexture = SphereTexture;
			break;
		default:
			MyTexture = nullptr;
			break;
		}

		if (MyTexture != nullptr)
		{
			SDL_Rect destRect = {
				(int)(10.0f + 48.0 * i),
				(int)60.0f,
				(int)Size.X,
				(int)Size.Y
			};
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}

	}

	for (unsigned int i = 0; i < playerState.HP; i++)
	{
		MyTexture = HealthTexture;


		if (MyTexture != nullptr)
		{
			SDL_Rect destRect = {
				(int)(10.0f + 32.0 * i),
				(int)10.0f,
				(int)Size.X,
				(int)Size.Y
			};
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}
	}

	if (playerState.IsBoosted)
	{
		SDL_Rect destRect = {
		1200,
		15,
		(int)Size.X,
		(int)Size.Y
		};
		SDL_RenderCopy(pRenderer, PowerupTexture, nullptr, &destRect);
	}

	if (playerState.HP <= 0)
	{
		SDL_Rect destRect = {
		120,
		120,
		1000,
		360
		};
		SDL_RenderCopy(pRenderer, gameOverSprite, nullptr, &destRect);
	}

	if (playerState.PlayerWon())
	{
		SDL_Rect destRect = {
		130,
		140,
		1000,
		360
		};
		SDL_RenderCopy(pRenderer, VictoryTexture, nullptr, &destRect);
	}
}
