#include "pch.h"
#include "PlayerHud.h"

void PlayerHud::OnPlayerDamageHandler()
{
	string hp = GetPlayHP();
}

string PlayerHud::GetPlayHP()
{
	string currentHP = std::to_string(HPComponent->GetCurrentHP());
	string maxHP = std::to_string(HPComponent->GetMaxHP());
	return  currentHP + " / " + maxHP;
}

PlayerHud::PlayerHud(poke::HPComponent* _HPComponent, GameObject * _owner)
{
	fontType.loadFromFile("Assets/Rubric Regular.ttf");

	HPComponent = _HPComponent;
	HPComponent->OnDamage = make_callback(this, &PlayerHud::OnPlayerDamageHandler);

	textComponent = new poke::TextComponent(GetPlayHP(), fontType, 20,false);
	_owner->AddComponent(textComponent);
}

void PlayerHud::Update(float deltaTime)
{
}

void PlayerHud::Render(sf::RenderWindow*)
{
}