#pragma once
class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;


public:
	SpriteGo (const std::string name);

	void SetTexture(const std::string& textureId);
	void SetTexture(const sf::Texture& texture);

	void SetPosition(const sf::Vector2f pos) override;
	void SetOrigin(const sf::Vector2f newOrigin) override;
	void SetOrigin(Origins preset) override;
	void SetScale(const float newScale) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetFlipX(bool flip) override;
	void SetFlipY(bool flip) override;
	void Draw(sf::RenderWindow& window) override;
};

