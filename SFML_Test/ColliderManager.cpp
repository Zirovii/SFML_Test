#include "pch.h"
#include "ColliderManager.h"
#include <Algorithm>

ColliderManager* ColliderManager::instance = nullptr;

const float COLLISSION_PER_SECONDS = .035f;

ColliderManager::ColliderManager()
{
	placeHolderCollider = new ColliderComponent(30, 30);
	collidersMap = new map<int, vector<ColliderComponent*>*>();
	collidersMap->insert(std::pair<int, vector<ColliderComponent*>*>(PLAYER, new vector<ColliderComponent*>()));
	collidersMap->insert(std::pair<int, vector<ColliderComponent*>*>(PLAYER_BULLETS, new vector<ColliderComponent*>()));
	collidersMap->insert(std::pair<int, vector<ColliderComponent*>*>(ENEMY, new vector<ColliderComponent*>()));
	collidersMap->insert(std::pair<int, vector<ColliderComponent*>*>(ENEMY_BULLETS, new vector<ColliderComponent*>()));
	collidersMap->insert(std::pair<int, vector<ColliderComponent*>*>(BLOCK, new vector<ColliderComponent*>()));
	instance = this;
}

ColliderManager::~ColliderManager()
{
	cout << " DESTRYPED COLLIDER MANAGER" << endl;
}

void ColliderManager::CheckCollisions(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= COLLISSION_PER_SECONDS) {
		totalTime -= COLLISSION_PER_SECONDS;

		vector<ColliderComponent*>* collidersA = collidersMap->find(PLAYER_BULLETS)->second;
		vector<ColliderComponent*>* collidersB = collidersMap->find(ENEMY)->second;
		CheckCollission(collidersA, collidersB);

		collidersA = collidersMap->find(ENEMY_BULLETS)->second;
		collidersB = collidersMap->find(PLAYER)->second;
		CheckCollission(collidersA, collidersB);
	}
}

void ColliderManager::CheckCollission(vector<ColliderComponent*>* collidersA, vector<ColliderComponent*>* collidersB)
{
	for (size_t i = 0; i < collidersA->size(); i++)
	{
		for (size_t j = 0; j < collidersB->size(); j++)
		{
			ColliderComponent* a = collidersA->at(i);
			ColliderComponent* b = collidersB->at(j);
			if (Intersecting(a->GetRectangleShape(), b->GetRectangleShape())) {
				a->OnCollisionEnter(b);
				b->OnCollisionEnter(a);
			}
		}
	}
}

sf::Vector2f ColliderManager::CheckMovement(ColliderComponent* realCollider, sf::Vector2f movement)
{
	sf::Vector2f movementX = { movement.x, 0 };
	sf::Vector2f movementY = { 0, movement.y};

	vector<ColliderComponent*>* collidersA = collidersMap->find(BLOCK)->second;
	for (size_t j = 0; j < collidersA->size(); j++)
	{

		ColliderComponent* a = collidersA->at(j);
		if (a == realCollider)
			continue;
		placeHolderCollider->SetPosition(realCollider->GetPosition() + movementX);
		if (Intersecting(a->GetRectangleShape(), placeHolderCollider->GetRectangleShape()))
		{
			movement.x = 0;
		}
		placeHolderCollider->SetPosition(realCollider->GetPosition() + movementY);
		if (Intersecting(a->GetRectangleShape(), placeHolderCollider->GetRectangleShape()))
		{
			movement.y = 0;
		}
	}
	return movement;
}

void ColliderManager::Update(float deltaTime)
{
	CheckCollisions(deltaTime);
}

void ColliderManager::RemoveCollider(ColliderComponent* collider)
{
	vector<ColliderComponent*>* collidersA = collidersMap->find(collider->layer)->second;
	auto begin = collidersA->begin();
	auto end = collidersA->end();
	vector<ColliderComponent*>::iterator it = std::remove(begin, end, collider);
	collidersA->erase(it, collidersA->end());
	if (collider->layer == PLAYER || collider->layer == ENEMY)
	{
		RemoveBlockCollider(collider);
	}
}

void ColliderManager::RemoveBlockCollider(ColliderComponent* collider)
{
	vector<ColliderComponent*>* collidersA = collidersMap->find(BLOCK)->second;
	auto begin = collidersA->begin();
	auto end = collidersA->end();
	vector<ColliderComponent*>::iterator it = std::remove(begin, end, collider);
	collidersA->erase(it, collidersA->end());
}

std::string ColliderManager::GetClassName()
{
	return "ColliderManager";
}

bool ColliderManager::Intersecting(const sf::RectangleShape * a, const sf::RectangleShape * b)
{
	return a->getGlobalBounds().intersects(b->getGlobalBounds());
}

ColliderComponent * ColliderManager::CreateCollider(float width, float height, int layer)
{
	ColliderComponent* colliderComponent = new ColliderComponent(width, height);
	collidersMap->find(layer)->second->push_back(colliderComponent);
	colliderComponent->layer = layer;

	if (layer == PLAYER || layer == ENEMY) 
	{
		collidersMap->find(BLOCK)->second->push_back(colliderComponent);
	}

	return colliderComponent;
}
