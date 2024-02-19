#include "pch.h"

#include "Bat.h"

Bat::Bat()
	{
		shape.setSize({ 100.f, 5.f });
		shape.setPosition({ 1920.f / 2.f , 1080.f - 20.f });
		shape.setFillColor(sf::Color::White);

		Utils::SetOrigin(shape, Origins::TC);
	}

void Bat::Update(float dt)
{
	
	float h = InputMgr::GetAxisRaw(Axis::Horizontal);

	sf::Vector2f pos = shape.getPosition();
	pos.x += h * speed * dt;
	shape.setPosition(pos);
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
