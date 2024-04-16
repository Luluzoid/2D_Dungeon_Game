#include "Hero.h"

using namespace Game;

void Hero::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	bool playerAlive = playerState.HP > 0;

	if (playerAlive)
	{
		Vector2d direction(0.0f, 0.0f);

		if (playerState.WantsToGoUp)
		{
			direction.Y = -1.0f;
		}
		else if (playerState.WantsToGoDown)
		{
			direction.Y = 1.0f;
		}
		if (playerState.WantsToGoLeft)
		{
			direction.X = -1.0f;
		}
		else if (playerState.WantsToGoRight)
		{
			direction.X = 1.0f;
		}

		direction.Normalize();

		Vector2d newPosition = playerState.PlayerPosition;

		if (playerState.PowerUpSeconds > 0.0f)
		{
			playerState.PowerUpSeconds -= deltaSeconds;
			newPosition += direction * 500.0f * deltaSeconds;
		}
		else
		{
			playerState.IsBoosted = false;
			newPosition += direction * 300.0f * deltaSeconds;
		}


		if (worldState.IsWalkableTile(newPosition))
		{
			playerState.PlayerPosition = newPosition;
		}
	}

	worldState.Camera = playerState.PlayerPosition;

	Position = playerState.PlayerPosition - Vector2d(Size.X * 0.5f, Size.Y * 0.8);




	if (playerState.InvinsibleSeconds > 0.0f)
	{
		playerState.InvinsibleSeconds -= deltaSeconds;
		Visible = !Visible;
	}
	else
		Visible = playerAlive;
}