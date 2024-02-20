#include "pch.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string name) : GameObject(name)
{
}

void SpriteGo::SetTexture(const std::string& textureId)
{
	sprite.setTexture(ResourceMgr<sf::Texture>::Instance().Get(textureId));
}

void SpriteGo::SetTexture(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}

void SpriteGo::SetPosition(const sf::Vector2f pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void SpriteGo::SetOrigin(const sf::Vector2f newOrigin)
{
	originPreset = Origins::CUSTOM;
	GameObject::SetOrigin(newOrigin);
	sprite.setOrigin(newOrigin);
}

void SpriteGo::SetOrigin(Origins preset)
{
	if (preset == Origins::CUSTOM)
	{
		preset = Origins::TL;
	}
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, originPreset);
}

void SpriteGo::SetScale(const float newScale)
{
	sprite.setScale(newScale, newScale);
}

void SpriteGo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	auto spriteScale = scale;
	if (isFlipX)
	{
		spriteScale.x = -scale.x;
	}
	if (isFlipY)
	{
		spriteScale.y = -scale.y;
	}

	sprite.setScale(spriteScale);
}

void SpriteGo::SetFlipX(bool flip)
{
	if (isFlipX == flip)
	{
		return;
	}

	isFlipX = flip;
	SetScale(scale);
}

void SpriteGo::SetFlipY(bool flip)
{
	if (isFlipY == flip)
	{
		return;
	}

	isFlipY = flip;
	SetScale(scale);
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
