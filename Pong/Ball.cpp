#include "Framework/pch.h"
#include "Bat.h"
#include "Ball.h"
#include "Framework/Scene.h"

Ball::Ball(Bat& b, const sf::FloatRect& bounds, const std::string name) : bat(b) ,windowBounds(bounds), GameObject(name)
{
}

void Ball::fire(sf::Vector2f d, float s)
{
	direction = d;
	speed = s;
	isDead = false;
}

void Ball::Init()
{
	shape.setRadius(20.f);
	shape.setFillColor(sf::Color::White);
	Utils::SetOrigin(shape, Origins::BC);
}

void Ball::Release()
{

}

void Ball::Reset()
{

}

void Ball::Update(float dt)
{

	isBoundBat = false;
	const sf::FloatRect& preBallBounds = shape.getGlobalBounds();
	sf::Vector2f prePos = shape.getPosition();
	sf::Vector2f pos = prePos;
	pos += direction * speed * dt;
	shape.setPosition(pos);

	const sf::FloatRect& ballBounds = shape.getGlobalBounds();
	float ballLeft = ballBounds.left;
	float ballRight = ballBounds.left + ballBounds.width;
	float ballTop = ballBounds.top;
	float ballBottom = ballBounds.top + ballBounds.height;

	float windowLeft = windowBounds.left;
	float windowRight = windowBounds.left + windowBounds.width;
	float windowTop = windowBounds.top;
	float windowBottom = windowBounds.top + windowBounds.height;

	//충돌처리
	
	const sf::FloatRect& batBounds = bat.shape.getGlobalBounds();
	float batLeft = batBounds.left;
	float batRight = batBounds.left + batBounds.width;
	float batTop = batBounds.top;
	float batBottom = batBounds.top + batBounds.height;


	if (ballBounds.intersects(batBounds) && !isBatCollision)
	{
		isBatCollision = true;
		isBoundBat = true;

		if (ballBottom > batTop || ballTop < batBottom)
		{
			direction.y *= -1.f;
		}

		if (ballLeft > batRight || ballRight < batLeft)
		{
			direction.x *= -1.f;
		}

	}
	if (!ballBounds.intersects(batBounds))
	{
		isBatCollision = false;
	}

	if (ballTop > windowBottom)
	{
		isDead = true;
		shape.setPosition(prePos);
		direction.y *= -1.f;
	}
	else if (ballTop < windowTop)
	{
		shape.setPosition(prePos);
		direction.y *= -1.f;
	}
	else if (ballLeft < windowLeft || ballRight > windowRight)
	{
		shape.setPosition(prePos);
		direction.x *= -1.f;
	}
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
