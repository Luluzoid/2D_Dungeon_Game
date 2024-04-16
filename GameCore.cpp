#include "GameCore.h"
#include "Sprite.h"
#include "Hero.h"
#include "RoomRenderer.h"
#include "Item.h"
#include "HUD.h"
#include "Foe.h"
#include "BG.h"

namespace Game
{
	std::vector<Sprite*> SpriteList;

	bool PlayerState::PlayerWon() const
	{
		int numberOfSpheres = 0;

		for (int i = 0; i < Inventory.size(); i++)
		{
			if (Inventory[i] == Item_SPHERE)
			{
				numberOfSpheres++;
			}
		}
		return numberOfSpheres >= 4;
	}
	

	bool WorldState::IsWalkableTile(const Vector2d& inPosition)
	{
		int column = (int)(inPosition.X / TileSize.X);
		int row = (int)(inPosition.Y / TileSize.Y);


		char currTile = ' ';
		int index = row * TilesPerRow + column;

		if (index >= 0 && index < (int)Tiles.size())
		{
			currTile = Tiles[index];
		}

		return currTile == '.';
	}

	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState)
	{
		playerState.HasFinishedGame = false;
		playerState.HP = 3;

		playerState.InvinsibleSeconds = 0.0f;
		playerState.PowerUpSeconds = 0.0f;

		playerState.WantsToGoUp=false;
		playerState.WantsToGoDown = false;
		playerState.WantsToGoLeft = false;
		playerState.WantsToGoRight = false;
		playerState.IsBoosted = false;


		worldState.SecondsSinceDefeat = 0.0f;
		worldState.TilesPerRow = 41;
		worldState.TileSize = Vector2d(72.0f, 72.0f);
		worldState.Tiles =
			" ########      ##################        "
			"#........#    #.................##       "
			"#........#    #..................#       "
			"#........#    #.......#######.....#      "
			"#........#    #.......#     #......#     "
			"#........#    #........#     #......#    "
			"#........#    ######....#    #.......#   "
			"#........#          ##...#   #........#  "
			"#........#            #...#   #........# "
			"#........#             #...#  #.........#"
			"#.........##############...#  #.........#"
			"#..........................#  #.........#"
			"#..........................#  #.........#"
			" #.........................#  #.........#"
			" ##########################    ######### ";

		worldState.Items.push_back({ true, Item_SPHERE, Vector2d(17.0f * worldState.TileSize.X,2.0f * worldState.TileSize.Y) });
		worldState.Items.push_back({ true, Item_SPHERE, Vector2d(6.0f * worldState.TileSize.X,12.0f * worldState.TileSize.Y) });
		worldState.Items.push_back({ true, Item_SPHERE, Vector2d(35.0f * worldState.TileSize.X,12.0f * worldState.TileSize.Y) });
		worldState.Items.push_back({ true, Item_SPHERE, Vector2d(6.0f * worldState.TileSize.X,2.0f * worldState.TileSize.Y) });
		worldState.Items.push_back({ true, Item_FLASK, Vector2d(32.0f * worldState.TileSize.X,5.0f * worldState.TileSize.Y) });
		worldState.Items.push_back({ true, Item_SPEED, Vector2d(25.0f * worldState.TileSize.X,9.0f * worldState.TileSize.Y) });
		worldState.Foes.push_back({ true, Vector2d(8.0f * worldState.TileSize.X,12.0f * worldState.TileSize.Y) });
		worldState.Foes.push_back({ true, Vector2d(17.0f * worldState.TileSize.X,4.0f * worldState.TileSize.Y) });

		BG* bg = new BG;
		bg->Initialize(pRenderer, "Assets/skies.bmp");
		bg->Size = Vector2d(WINDOW_WIDTH, WINDOW_HEIGHT);
		SpriteList.push_back(bg);

		RoomRenderer* roomRenderer = new RoomRenderer;
		roomRenderer->InitializeTiles(pRenderer, "Assets/tile1.bmp", "Assets/wall1.bmp");
		SpriteList.push_back(roomRenderer);

		Hero* hero = new Hero;
		hero->Initialize(pRenderer, "Assets/nana.bmp");
		playerState.PlayerPosition = Vector2d(3.0f * worldState.TileSize.X, 4.0f*worldState.TileSize.Y);
		SpriteList.push_back(hero);

		for (unsigned int i = 0; i < worldState.Foes.size(); i++)
		{
			std::string foeFilepath = "Assets/monkaw_trans_recolor.bmp";

			Foe* newFoe = new Foe;
			newFoe->Initialize(pRenderer, foeFilepath);
			newFoe->SetFoeIndex(i);
			SpriteList.push_back(newFoe);
		}

		for (unsigned int i = 0; i < worldState.Items.size(); i++)
		{
			std::string itemFilepath = "Assets/sphere.bmp";

			switch (worldState.Items[i].Type) //which item to render
			{
			case Item_SPHERE:
				break;
			case Item_FLASK:
				itemFilepath = "Assets/flask.bmp";
				break;
			case Item_SPEED:
				itemFilepath = "Assets/speed.bmp";
				break;
			}

			Item* newItem = new Item;
			newItem->Initialize(pRenderer, itemFilepath);
			newItem->SetItemIndex(i);
			SpriteList.push_back(newItem);
		}

		HUD* newHUD = new HUD;
		newHUD->InitializeInventory(pRenderer, "Assets/sphere.bmp", "Assets/nana.bmp", "Assets/GAMEOVER.bmp", "Assets/victory.bmp", "Assets/speed.bmp");
		SpriteList.push_back(newHUD);
	}

	void GetInput(PlayerState& playerState, const WorldState& worldState)
	{
		SDL_Event e = {};
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				playerState.HasFinishedGame = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_ESCAPE:
					playerState.HasFinishedGame = true;
					break;

				case SDLK_UP:
				case SDLK_w:
					playerState.WantsToGoUp = true;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					playerState.WantsToGoDown = true;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					playerState.WantsToGoLeft = true;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					playerState.WantsToGoRight = true;
					break;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_UP:
				case SDLK_w:
					playerState.WantsToGoUp = false;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					playerState.WantsToGoDown = false;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					playerState.WantsToGoLeft = false;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					playerState.WantsToGoRight = false;
					break;
				}
			}

		}
	}

	void UpdateGame(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
	{

		for (unsigned int i = 0; i < SpriteList.size(); i++)
		{
			SpriteList[i]->Update(deltaSeconds, playerState, worldState);
		}

		if (playerState.HP <= 0 || playerState.PlayerWon())
		{
			worldState.SecondsSinceDefeat += deltaSeconds;

			if (worldState.SecondsSinceDefeat > 2.5f)
			{
				playerState.HasFinishedGame = true;
			}
		}
	}

	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState)
	{
		SDL_RenderClear(pRenderer);



		for (unsigned int i = 0; i < SpriteList.size(); i++)
		{
			SpriteList[i]->Render(pRenderer, playerState, worldState, Vector2d(WINDOW_WIDTH*0.5f, WINDOW_HEIGHT*0.5f) - worldState.Camera);
		}

		SDL_RenderPresent(pRenderer);
	}

	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		for (unsigned int i = 0; i < SpriteList.size(); i++)
		{
			SpriteList[i]->Cleanup();
			delete SpriteList[i];
		}
		SpriteList.clear();

		Sprite::CleanupTextures();
	}
}