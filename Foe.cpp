#include "Foe.h"

using namespace Game;


void Foe::SetFoeIndex(int newIndex)
{
	FoeIndex = newIndex;
}

void Foe::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	const float FOE_SPEED = -75.0f;
	FoeData& currFoe = worldState.Foes[FoeIndex];

	if (currFoe.Alive && !playerState.PlayerWon())
	{
		Vector2d vecToPlayer = currFoe.Position - playerState.PlayerPosition;
		if (vecToPlayer.GetLength() < 28.0f)
		{
			if (playerState.HP >0 && playerState.InvinsibleSeconds <= 0.0f)
			{
				playerState.HP -= 1;
				playerState.InvinsibleSeconds = 1.5f;
			}
		}

		//CODE FOR MAKING ENEMIES?
		vecToPlayer.Normalize();
		Vector2d newPosition = currFoe.Position;
		newPosition += vecToPlayer * FOE_SPEED * deltaSeconds;

		if (worldState.IsWalkableTile(newPosition))
		{
			currFoe.Position = newPosition;
		}
		//////////////////////////////////



	}
	Position = currFoe.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.8);
	Visible = currFoe.Alive;
}