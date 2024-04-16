#pragma once
#include "Sprite.h"

namespace Game
{
	class Hero :public Sprite
	{
	public:

		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);
	};
}