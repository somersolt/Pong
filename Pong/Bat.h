#pragma once

class Bat : public GameObject
{
protected:

public:
	float speed = 0.f;
	sf::RectangleShape shape;
	sf::Vector2f pos;
	Bat(const std::string name);

	void Init();
	void Release();

	void Reset();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);


};

