#include "pch.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& name) : GameObject(name)
{
}

void TextGo::SetString(const std::string str)
{
	text.setString(str);
	SetOrigin(originPreset);
}

void TextGo::Set(const sf::Font& texture, int size, std::string str, sf::Color color)
{
	SetFont(texture);
	text.setString(str);
	text.setCharacterSize(size);
	text.setFillColor(color);
}

void TextGo::SetFont(const std::string& fontId)
{
	text.setFont(ResourceMgr<sf::Font>::Instance().Get(fontId));
}

void TextGo::SetFont(const sf::Font& font)
{
	text.setFont(font);
}

void TextGo::SetPosition(const sf::Vector2f pos)
{
	position = pos;
	text.setPosition(position);
}

void TextGo::SetOrigin(const sf::Vector2f newOrigin)
{
	GameObject::SetOrigin(newOrigin);
}

void TextGo::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	origin = Utils::SetOrigin(text, preset);
	
}

void TextGo::SetScale(const sf::Vector2f& s)
{
	scale = s;

	sf::Vector2f spriteScale = scale;
	if (isFlipX)
	{
		scale.x = -scale.x;
	}
	if (isFlipY)
	{
		scale.y = -scale.y;
	}
}

void TextGo::SetFlipX(bool flip)
{
	if (isFlipX == flip)
	{
		return;
	}

	isFlipX = flip;
	SetScale(scale);
}

void TextGo::SetFlipY(bool flip)
{
	if (isFlipY == flip)
	{
		return;
	}

	isFlipY = flip;
	SetScale(scale);
}

void TextGo::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}
