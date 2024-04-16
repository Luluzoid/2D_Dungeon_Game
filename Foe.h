#pragma once
#include "Sprite.h"

namespace Game
{
	class Foe :public Sprite
	{
	public:
		void SetFoeIndex(int newIndex);

		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);

	private:
		int FoeIndex;
	};
}
