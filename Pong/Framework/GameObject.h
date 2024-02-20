#pragma once

class GameObject
{
protected:
	bool active = true;

	Origins originPreset = Origins::TL;
	sf::Vector2f origin = { 0.f, 0.f };
	sf::Vector2f position = { 0.f, 0.f };
	sf::Vector2f scale = { 1.f , 1.f };

	bool isFlipX = false;
	bool isFlipY = false;


public:
	GameObject(const std::string& name = "");
	virtual ~GameObject();

	virtual void Init();
	virtual void Release();

	virtual void Reset(); // 재사용할때 쓰는 함수

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);
	
	virtual bool GetActive() const { return active; }
	virtual void SetActive(bool active) { this->active = active; };
	virtual void SetScale(const float newScale) { scale.x = newScale, scale.y = newScale; };
	virtual void SetPosition(const sf::Vector2f pos) {position = pos;}
	sf::Vector2f GetPosition() const { return position; }
	virtual void SetOrigin(const sf::Vector2f newOrigin) 
	{ 
		originPreset = Origins::CUSTOM;
		origin = newOrigin; 
	}	
	virtual void SetOrigin(Origins preset);
	sf::Vector2f GetOrigin() const { return origin; }

	bool GetFlipX() const { return isFlipX; }
	virtual void SetFlipX(bool flip) { isFlipX = flip; }
	bool GetFlipY() const { return isFlipY; }
	virtual void SetFlipY(bool flip) { isFlipY = flip; }
	virtual void SetScale(const sf::Vector2f& scale);
	sf::Vector2f GetScale() const { return scale; }

	std::string name = "";
	int sortLayer = 0;
	int sortOrder = 0; // 수업때만 퍼블릭  layer 층, order 층 내의 우선도

};

