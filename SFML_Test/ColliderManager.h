#pragma once
#include "ColliderComponent.h"
#include "IGameComponent.h"

class ColliderManager : public IGameComponent
{
private:
	map<int, vector<ColliderComponent*>*>* collidersMap;
	float totalTime;
	bool Intersecting(const sf::RectangleShape* a, const sf::RectangleShape* b);
public:
	static const int PLAYER = 0;
	static const int PLAYER_BULLETS = 1;
	static const int ENEMY = 2;
	static const int ENEMY_BULLETS = 3;

	static ColliderManager* instance;

	ColliderComponent * CreateCollider(float width, float height, int layer);

	ColliderManager();
	~ColliderManager();

	void CheckCollisions(float deltaTime);
	void CheckCollission(vector<ColliderComponent*>* listA, vector<ColliderComponent*>* listB);
	void Update(float deltaTime);
	void RemoveCollider(ColliderComponent* collider);
	virtual std::string GetClassName();

};

