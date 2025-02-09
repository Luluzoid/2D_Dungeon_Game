#include "Sprite.h"
#include <string>


using namespace Game;

std::vector<Sprite::LoadedTexture> Sprite::s_LoadedTextures;

Sprite::Sprite() :
	MyTexture(nullptr),
	Position(0.0f, 0.0f),
	Size(72.0f, 72.0f),
	Visible(true)

{

}

void Sprite::Initialize(SDL_Renderer* pRenderer, const std::string& imageFilepath)
{
	MyTexture = LoadTexture(pRenderer, imageFilepath);
}

void Sprite::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{

}

void Sprite::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
{
	if (Visible && MyTexture != nullptr)
	{
		SDL_Rect destRect = { (int)Position.X + (int)baseTranslation.X, (int)Position.Y + (int)baseTranslation.Y, (int)Size.X, (int)Size.Y };
		SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
	}
}


void Sprite::Cleanup()
{
	//SDL_DestroyTexture(MyTexture);
}

void Sprite::CleanupTextures()
{
	for (unsigned int i = 0; i < s_LoadedTextures.size(); i++)
	{
		SDL_DestroyTexture(s_LoadedTextures[i].Texture);
	}

	s_LoadedTextures.clear();
}

SDL_Texture* Sprite::LoadTexture(SDL_Renderer* pRenderer, const std::string& imageFilepath)
{
	for (unsigned int i = 0; i < s_LoadedTextures.size(); i++)
	{
		if (s_LoadedTextures[i].Filename == imageFilepath)
		{
			return s_LoadedTextures[i].Texture;
		}
	}

	SDL_Surface* pBmp = SDL_LoadBMP(imageFilepath.c_str());
	SDL_SetColorKey(pBmp, SDL_TRUE, SDL_MapRGB(pBmp->format, 0, 255, 1));
	SDL_Texture* returnTexture = SDL_CreateTextureFromSurface(pRenderer, pBmp);
	SDL_FreeSurface(pBmp);

	LoadedTexture loadedText = { imageFilepath, returnTexture };
	s_LoadedTextures.push_back(loadedText);

	return returnTexture;
}

