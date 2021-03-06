#pragma once
#include "IGameComponent.h"
#include "Callbacks.h"

namespace poke
{
	class HPComponent : public IGameComponent
	{
	private:
		int currentHP;
		int maxHP;
	public :
		HPComponent(int maxHP);
		~HPComponent();
		bool IsDead();
		Action* OnDamage;
		Action* OnHeal;
		Action* OnDead;
		int GetCurrentHP();
		int GetMaxHP();
		void TakeDamage(int amount);
		void Heal(int amount);
		void Update(float deltaTime);
		void Render(sf::RenderWindow*);
		std::string GetClassName();
	};
}
