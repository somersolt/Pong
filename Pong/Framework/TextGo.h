#pragma once
#include "GameObject.h"
class TextGo : public GameObject
{
protected:
	sf::Text text;

public:
	TextGo(const std::string& name = "");
	void SetString(const std::string str);
	void Set(const sf::Font& texture, int size, std::string str, sf::Color color);

	void SetFont(const std::string& textureId);
	void SetFont(const sf::Font& texture);

	void SetPosition(const sf::Vector2f pos) override;
	void SetOrigin(const sf::Vector2f newOrigin) override;
	void SetOrigin(Origins preset) override;
	//void SetScale(const float newScale) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetFlipX(bool flip) override;
	void SetFlipY(bool flip) override;
	void Draw(sf::RenderWindow& window) override;

};

