#include "pch.h"
#include "Bat.h"
#include "Ball.h"

Ball::Ball(Bat& b, const sf::FloatRect& bounds) : bat(b) , windowbounds(bounds)
{
	shape.setRadius(10.f);
	//shape.setPosition({ 1920.f / 2.f , 1080.f - 35.f });
	shape.setFillColor(sf::Color::White);
	Utils::SetOrigin(shape, Origins::BC);
}

void Ball::fire(sf::Vector2f d, float s)
{
	direction = d;
	speed = s;
	isDead = false;
}

void Ball::Update(float dt)
{

	isBoundBat = false;
	sf::Vector2f pos = shape.getPosition();
	pos += direction * speed * dt;
	shape.setPosition(pos);


	const sf::FloatRect& ballBounds = shape.getGlobalBounds();
	const sf::FloatRect& batBounds = bat.shape.getGlobalBounds();
	if (ballBounds.intersects(batBounds) && !isBatCollision)
	{
		isBatCollision = true;
		isBoundBat = true;
		direction.y *= -1.f;
	}
	if (!ballBounds.intersects(batBounds))
	{
		isBatCollision = false;
	}

	//충돌처리
	if (windowbounds.top > shape.getGlobalBounds().getPosition().y)
	{
		Utils::SetOrigin(shape, Origins::TC);
		shape.setPosition(shape.getPosition().x, windowbounds.top);
		direction.y *= -1.f;
	}

	if (windowbounds.left > shape.getGlobalBounds().getPosition().x)
	{
		Utils::SetOrigin(shape, Origins::ML);
		shape.setPosition(windowbounds.left, shape.getPosition().y);
		direction.x *= -1.f;
	}

	if (windowbounds.width < shape.getGlobalBounds().getPosition().x)
	{
		Utils::SetOrigin(shape, Origins::MR);
		shape.setPosition(windowbounds.width, shape.getPosition().y);
		direction.x *= -1.f;
	}

	if (windowbounds.height < shape.getGlobalBounds().getPosition().y)
	{
		Utils::SetOrigin(shape, Origins::BC);
		isDead = true;
	}
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
