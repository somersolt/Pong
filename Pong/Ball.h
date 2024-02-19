#pragma once
class Bat;

class Ball
{
protected:
	sf::Vector2f direction = { 0.f, 0.f };
	Bat& bat;
	sf::FloatRect windowbounds;
public:
	Ball(Bat& b, const sf::FloatRect& bounds);
	
	sf::CircleShape shape;
	float speed = 0.f;
	bool isDead = false;
	bool isBoundBat = false;
	bool isBatCollision = false;


	void fire(sf::Vector2f d, float s);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

