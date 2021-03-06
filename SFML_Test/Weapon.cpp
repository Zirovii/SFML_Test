#include "pch.h"
#include "Weapon.h"
#include "SoundManager.h"
#include <cmath>

Weapon::Weapon(sf::Vector2f _offset,float _damage, bool _player)
{
	offset = _offset;
	isPlayer = _player;
	damage = _damage;
	OnSpecialShoot = new Action();
}

const double pi = std::acos(-1);

void Weapon::Update(float deltaTime)
{
	if (isPlayer)
	{
		if (Input::GetKeyDown(Input::Mouse0)) 
		{
			sf::Vector2f spawnPoint = GetBulletSpawnPoint();
			sf::Vector2f shootDirection = Input::GetMousePosition() - spawnPoint;
			shootDirection = VectorUtils::Normalize(shootDirection);
			Shoot(spawnPoint, shootDirection);
		}
		else if (Input::GetKeyDown(Input::Mouse1) && specialAttack > 0)
		{
			specialAttack--;
			sf::Vector2f spawnPoint = GetBulletSpawnPoint();
			for (float i = 0; i < 6.28f; i+=.2f)
			{
				sf::Vector2f shootDirection = { 1,1 };
				float rot = i;
				float x = shootDirection.x * std::cos(rot) - shootDirection.y * std::sin(rot);
				float y = shootDirection.x * std::sin(rot) + shootDirection.y * std::cos(rot);
				shootDirection.x = x;
				shootDirection.y = y;
				Shoot(spawnPoint, shootDirection);
			}
			OnSpecialShoot->Invoke();
		}
		
	}
}
#define PI 3.14159265
void Weapon::Shoot(sf::Vector2f origin, sf::Vector2f direction)
{
	GameObject* bulletGo = new GameObject();
	bulletGo->name = "Bullet";
	
	bulletGo->transform->Translate(origin);
	Bullet* b = new Bullet(direction, 450, bulletGo);
	b->damage = damage;
	bulletGo->AddComponent(b);
	int layer;
	if (isPlayer) {
		layer = ColliderManager::PLAYER_BULLETS;
	}
	else {
		layer = ColliderManager::ENEMY_BULLETS;
	}
	bulletGo->AddComponent(ColliderManager::instance->CreateCollider(15, 15,layer));
	Gameplay::instance->AddGameObject(bulletGo);

	SoundManager::instance->Play("fireBall");
}

std::string Weapon::GetClassName()
{
	return "Weapon";
}

sf::Vector2f Weapon::GetBulletSpawnPoint()
{
	return GetOwner()->transform->position + offset;
}
