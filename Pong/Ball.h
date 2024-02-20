#pragma once
class Bat;

class Ball : public GameObject
{
protected:
	sf::Vector2f direction = { 0.f, 0.f };
	sf::FloatRect windowBounds;
public:
	Ball(Bat& b, const sf::FloatRect& bounds, const std::string name);
	Bat& bat;
	sf::CircleShape shape;
	float speed = 0.f;
	bool isDead = false;
	bool isBoundBat = false;
	bool isBatCollision = false;


	void Init();
	void Release();

	void Reset(); // 재사용할때 쓰는 함수

	void Update(float dt);
	void Draw(sf::RenderWindow& window);


	void fire(sf::Vector2f d, float s);
};

