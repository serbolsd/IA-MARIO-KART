#pragma once
#include "vector2.h"
#include <Graphics.hpp>
#include <Window.hpp>
class Point
{
public:
	Point();
	~Point();

	vector2 m_pos;
	sf::Texture texture;
	sf::Sprite m_sprite;
	sf::Vector2u size;
	void init(vector2 pos);

	vector2 getPos() { return m_pos; };

	void draw(sf::RenderWindow & window);
};

