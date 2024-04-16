#include "Item.h"

using namespace Game;


void Item::SetItemIndex(int newIndex)
{
	ItemIndex = newIndex;
}

void Item::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{

	ItemData& currItem = worldState.Items[ItemIndex];

	if (currItem.Alive)
	{
		Vector2d vecToPlayer = currItem.Position - playerState.PlayerPosition;
		if (vecToPlayer.GetLength() < 28.0f)
		{
			currItem.Alive = false;

			if (currItem.Type == Item_FLASK)
				playerState.HP++;
			else if(currItem.Type == Item_SPHERE)
				playerState.Inventory.push_back(currItem.Type);
			else if (currItem.Type == Item_SPEED)
			{
				playerState.IsBoosted = true;
				playerState.PowerUpSeconds = 5.0f;
			}
		}

		

	}
	Position = currItem.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.8);
	Visible = currItem.Alive;
}