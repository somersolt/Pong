#pragma once

class Bat
{
protected:

public:
	Bat();
	float speed = 500.f;

	sf::RectangleShape shape;

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

