#include "CinputManager.h"



CinputManager::CinputManager()
{
}


CinputManager::~CinputManager()
{
}

void CinputManager::onUpdate(int controlID, Boid & player)
{

		if (sf::Joystick::isButtonPressed(controlID, 0))
		{
			//boton A Acelerar
			player.m_timeTrans += m_timeTrans;
			player.m_acelartionTime = player.m_timeTrans;
			if (player.m_speed < player.m_maxSpeed)
			{
				if (player.outOfPath)
				{
					player.m_speed = player.m_speed;
				}
				else
				{
					player.m_speed = player.m_acceleration * player.m_acelartionTime;
					player.m_actualSpeed = player.m_speed;
					player.minimunSpeed = true;
				}
			}
			else if (player.m_speed >= player.m_maxSpeed)
			{
				player.m_speed = player.m_maxSpeed;
				player.m_timeTrans = player.m_speed / player.m_acceleration;
			}
		}
		else if (sf::Joystick::isButtonPressed(controlID, 1))
		{
			player.m_timeTrans += m_timeTrans;
			player.m_acelartionTime = m_timeTrans;
			if (player.m_speed > -player.m_maxSpeed)
			{
				if (player.outOfPath)
				{
					player.m_speed = player.m_speed;
				}
				else
				{
					player.m_speed += player.m_desacceleration * player.m_acelartionTime;
					player.m_actualSpeed = player.m_speed;
					player.minimunSpeed = true;
				}
			}
			else if (player.m_speed <= -player.m_maxSpeed)
			{
				player.m_speed = -player.m_maxSpeed;
				player.m_timeTrans = player.m_speed / player.m_acceleration;
			}
			else
			{
				player.m_speed =- player.m_maxSpeed;
				player.m_timeTrans = player.m_speed / player.m_acceleration;
			}
			//boton B Reversa

		}
		else if (sf::Joystick::isButtonPressed(controlID, 2))
		{
			//boton X Acelerar
		}
		else if (sf::Joystick::isButtonPressed(controlID, 3))
		{
			//boton Y Reversa
		}
		else
		{
			player.m_timeTrans += m_timeTrans;
			player.m_acelartionTime = m_timeTrans;
			if (player.m_speed > 0)
			{
				if (player.outOfPath)
				{
					player.m_speed = player.m_speed;
					player.m_timeTrans = player.m_speed / player.m_acceleration;
				}
				else
				{
					player.m_speed += player.m_desacceleration * player.m_acelartionTime;
					player.m_actualSpeed = player.m_speed;
					player.minimunSpeed = true;
					player.m_timeTrans = player.m_speed / player.m_acceleration;
				}
			}
			else if (player.m_speed <= 0)
			{
				player.m_speed = 0;
				player.m_timeTrans = 0;
			}
			else
			{
				player.m_speed = 0;
				player.m_timeTrans = 0;
			}
			//boton B Reversa
		}
		//DIRECCION X
		vector2 newdirection;
		float axisPovX = sf::Joystick::getAxisPosition(controlID, sf::Joystick::PovX);
		float axisX = sf::Joystick::getAxisPosition(controlID, sf::Joystick::X);
		if (axisX >= 10|| axisPovX >= 10)
		{
			if (axisX >= 10)
			{
				newdirection.x = axisX;
			}
			else
			{
				newdirection.x = axisPovX;
			}
		}
		else if (axisX <= -10|| axisPovX <= -10)
		{
			if (axisX <= -10)
			{
				newdirection.x = axisX;
			}
			else
			{
				newdirection.x = axisPovX;
			}
			
		}
		else
			newdirection.x = player.m_direccion.x;
		//DIRECCION Y
		float axisY = sf::Joystick::getAxisPosition(controlID, sf::Joystick::Y);
		float axisPovY = sf::Joystick::getAxisPosition(controlID, sf::Joystick::PovX);
		if (axisY >= 10|| axisPovY >= 10)
		{
			if (axisY >= 10)
			{
				newdirection.y = axisY;
			}
			else
			{
				newdirection.y = axisPovY;
			}
			
		}
		else if (axisY <= -10|| axisPovY <= -10)
		{
			if (axisY <= -10)
			{
				newdirection.y = axisY;
			}
			else
			{
				newdirection.y = axisPovY;
			}
			
		}
		else
			newdirection.y= player.m_direccion.y;
		newdirection = newdirection.normalize();
		Boid::followPaht(player.follow_pointA, player.follow_pointB, *player.m_position, player.follow_PathRatio, player.follow_PointRatio, player.follow_Magnitud, player.b_follow_arrive, player.outOfPath);
		vector2 FSteering = newdirection;
		vector2 fliccion;

		//utilizar el delta time para calcular la velocidad actual
		if (FSteering.magnitud() > player.m_actualSpeed)
		{
			FSteering = FSteering.normalize();
			FSteering *= player.m_actualSpeed;
		}
		FSteering *= player.m_weight;// se truquea con la valocidad maxima
		newdirection = FSteering;
		newdirection += player.m_direccion;
		if (player.outOfPath)
		{
			float scalarFlic = 1 - player.m_weight;
			fliccion = FSteering;
			//fliccion *=m_actualSpeed;
			fliccion *= -1;
			fliccion *= scalarFlic;
			vector2 result = FSteering;
			result += fliccion;
			//result *= m_actualSpeed;
			if (player.m_speed > result.magnitud())
			{
				float desaceleraction = (result.magnitud() - player.m_actualSpeed) / (player.m_weight*1.2);
				float des = desaceleraction * player.timeDes;
				player.m_speed = player.m_actualSpeed + des;
				if (player.m_speed <= 0)
				{
					player.m_speed = result.magnitud();
				}
			}
			else
			{
				player.minimunSpeed = true;
				player.m_speed = result.magnitud();
			}
			//FSteering += fliccion;
			player.m_timeTrans = player.m_speed / player.m_acceleration;
		}
		//se saca el vectgor de la fuerza menos la direccion y se multiplica por la masa
			// direccion mas nueva direccion
			//esto hara que se voltear hasta que encuentra una nueva direccion en la que si se pueda mover
		vector2 nPos = *player.m_position;
		nPos += FSteering;
		player.m_direccion *= 1 - player.m_weight;
		nPos += player.m_direccion;
		player.m_direccion = nPos;
		player.m_direccion -= *player.m_position;
		//FSteering *= m_speed;
		player.m_direccion *= FSteering.magnitud();
		player.m_direccion = player.m_direccion.normalize();
		if (player.b_follow_arrive)
		{
			player.OE_followPath = player.OE_followPath->nextEvent();
		}

}
