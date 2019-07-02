#include "Point.h"



Point::Point()
{
}


Point::~Point()
{
}

void Point::init(vector2 pos)
{
	m_pos = pos;
	if (!texture.loadFromFile("Resources\\image\\Corredor.png"))
	{
		std::cout << "cant lodad texture";
		// error...
	}
	m_sprite.setTexture(texture);
	size = texture.getSize();
	m_sprite.setOrigin(size.x / 2, size.y / 2);
	m_sprite.setPosition(m_pos.x,m_pos.y);
}

void Point::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
