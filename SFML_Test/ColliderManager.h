#pragma once
#include "ColliderComponent.h"
#include "IGameComponent.h"

class ColliderManager : public IGameComponent
{
private:
	vector<ColliderComponent*>* colliders;
	float totalTime;
	bool Intersecting(const sf::RectangleShape* a, const sf::RectangleShape* b);
public:
	static ColliderManager* instance;

	ColliderComponent * CreateCollider(float width, float height);

	ColliderManager();
	~ColliderManager();

	void CheckCollisions(float deltaTime);
	void Update(float deltaTime);
	virtual std::string GetClassName();
};

