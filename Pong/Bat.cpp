#include "Framework/pch.h"

#include "Bat.h"

Bat::Bat(const std::string name) : GameObject(name)
	{
	}

void Bat::Init()
{
	shape.setSize({ 500.f, 20.f });
	Utils::SetOrigin(shape, Origins::TC);
	shape.setPosition({ 1920.f / 2.f , 1080.f - 20.f });
	shape.setFillColor(sf::Color::White);
	pos = shape.getPosition();
	speed = 2000.f;
}

void Bat::Release()
{
}

void Bat::Reset()
{
	pos.x = 1920.f / 2.f;
}

void Bat::Update(float dt)
{
	float h = InputMgr::GetAxis(Axis::Horizontal);
	pos.x += h * speed * dt;
	shape.setPosition(pos);
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
