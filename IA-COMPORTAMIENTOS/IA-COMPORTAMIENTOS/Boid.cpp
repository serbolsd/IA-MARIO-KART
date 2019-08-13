#include "Boid.h"

Boid::Boid()
{
	m_direccion = vector2(0.0f, 0.0f);
	m_position = new vector2(0.0f, 0.0f);
	m_seekObjetivePos = vector2(0.0f, 0.0f);
	m_fleeObjetPos = vector2(0.0f, 0.0f);
	m_arrivePos = vector2(0.0f, 0.0f);
	m_objetivePos = vector2(0.0f, 0.0f);
	m_objetiveDir = vector2(0.0f, 0.0f);
	m_predatorPos = vector2(0.0f, 0.0f);
	m_predatorDir = vector2(0.0f, 0.0f);
}

Boid::~Boid()
{
	//delete OE_followPath;
}

void Boid::setPosition(const float & posX, const float & posy)
{
	*m_position = vector2(posX, posy);
}

void Boid::SetSeekPos(const vector2 & objetivePos, const float & magnitud)
{
	m_seekObjetivePos = objetivePos;
	m_seekMangitude = magnitud;

}

void Boid::SetFleeData(const vector2 & objetPos, const float & ratio, const float & magnitud)
{
	m_fleeObjetPos = objetPos;
	m_fleeRatio = ratio;
	m_fleeMangitude = magnitud;
}

void Boid::SetArriveData(const vector2 & arrivePos, const float & ratio, const float & magnitud)
{
	m_arrivePos = arrivePos;
	m_arriveRatio = ratio;
	m_arriveMangitude = magnitud;
}

void Boid::SetPursueData(const vector2 & objetivePos, const vector2 & objetiveDir, const float & objetiveSpeed, const float & magnitud)
{
	m_objetivePos = objetivePos;
	m_objetiveDir = objetiveDir;
	m_pursueMangitude = magnitud;
	m_objetiveSpeed = objetiveSpeed;
}

void Boid::SetEvadeData(const vector2 & predatorPos, const vector2 & predatorDir, const float & predatorSpeed, const float & magnitud)
{
	m_predatorPos = predatorPos;
	m_predatorDir = predatorDir;
	m_evadeMangitude = magnitud;
	m_predatorSpeed = predatorSpeed;
}

void Boid::SetobstacleData(const vector2 & objetPos, const float & ratio, const float & magnitud)
{
	m_obstaclePos = objetPos;
	m_obstacleRatio = ratio;
	m_obstacleMagnitud = magnitud;
}

void Boid::SetFollowPath(Point & pointA, Point & pointB, const float & pathRatio, const float & pointRatio, const float & magnitud)
{
	pointA.color = { 0,0,0,0 };
	pointB.color = m_color;
	follow_pointA = pointA.m_pos;
	follow_pointB = pointB.m_pos;
	follow_PathRatio = pathRatio;
	follow_PointRatio = pointRatio;
	follow_Magnitud = magnitud;

}

void Boid::onDelete()
{
	//delete m_position;
}

void Boid::init(const float& weight, const float& speed, const float& maxSpeed, const float& acceleration, const float& posX, const float& posY, const float& ratio)
{
	m_weight = weight;
	m_speed = speed;
	m_maxSpeed = maxSpeed;
	m_acceleration = acceleration;
	m_desacceleration = -acceleration;
	setPosition(posX, posY);
	if (!texture.loadFromFile("Resources\\image\\sonic.png"))
	{
		std::cout << "cant lodad texture";
		// error...
	}
	m_sprite.setTexture(texture);
	size = texture.getSize();
	m_sprite.setOrigin(size.x / 2, size.y / 2);
	m_ratio = ratio;

}

void Boid::setTexture(std::string dir_texture)
{
	if (!texture.loadFromFile(dir_texture))
	{
		std::cout << "cant lodad texture";
		// error...
	}
	m_sprite.setTexture(texture);
	size = texture.getSize();
	m_sprite.setOrigin(size.x / 2, size.y / 2);
}

void Boid::destroy()
{
}

void Boid::update()
{
	//const clock_t begin_time = clock();
	m_acelartionTime = m_timeTrans;
	if (m_speed<m_maxSpeed)
	{
		if (outOfPath)
		{
			m_speed = m_speed;
		}
		else
		{
			m_speed=m_acceleration*m_acelartionTime;
			m_actualSpeed = m_speed;
			minimunSpeed = true;
		}
	}
	else if(m_speed >= m_maxSpeed)
	{
		m_speed = m_maxSpeed;
		m_timeTrans = m_speed / m_acceleration;
	}
	if (!outOfPath)
	{
		timeDes = 0;
	}
	//std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC;
	vector2 newdirection(0, 0);
	if (b_Seek)
	{
		vector2 prueva = seek(*m_position, m_seekObjetivePos, m_seekMangitude);
		newdirection += prueva;
	}
	if (b_flee)
	{
		vector2 prueva = flee(*m_position, m_fleeObjetPos, m_fleeRatio, m_fleeMangitude);
		newdirection += prueva;
	}
	if (b_arrive)
	{
		newdirection += arrive(*m_position, m_arrivePos, m_arriveMangitude, m_arriveRatio);
	}
	if (b_pursue)
	{
		newdirection += pursue(*m_position, m_objetivePos, m_objetiveDir, 2,m_objetiveSpeed, m_pursueMangitude);
	}
	if (b_evade)
	{
		newdirection += evade(*m_position, m_predatorPos, m_predatorDir, 2,m_predatorSpeed , m_evadeMangitude);
	}
	if (b_obstacle)
	{
		newdirection += obstacle(*m_position, m_obstaclePos, m_obstacleRatio,m_obstacleMagnitud);
	}
	if (b_wandeRam)
	{
		newdirection += wanderRam(*m_position,500,500,10);
	}
	if (b_wandeRamTime)
	{
		newdirection += wanderRamwhitTime(*m_position, m_wamderPos, 1000, 1000, m_wanderTime, 3, 10);
	}
	if (b_wandeToPoint)
	{
		newdirection += wanderToPoint(*m_position,m_wamderPos,30,45,10);
	}
	if (b_followPath)
	{
		newdirection += followPaht(follow_pointA,follow_pointB,*m_position,follow_PathRatio,follow_PointRatio,follow_Magnitud,b_follow_arrive,outOfPath);
	}
	if (b_floking)
	{
		newdirection += floking(*this,compas,compas_pos,100,10);
	}
	if (b_followTheLeader)
	{
		newdirection += followTheLeader(*this, compas, compas_pos, 100, 10);
	}
	newdirection += separate(*m_position,compas_pos,m_ratio,10);
	vector2 FSteering = newdirection;
	vector2 fliccion;
	
	//utilizar el delta time para calcular la velocidad actual
	if (FSteering.magnitud()> m_actualSpeed)
	{
		FSteering = FSteering.normalize();
		FSteering *= m_actualSpeed;
	}
	FSteering *= m_weight;// se truquea con la valocidad maxima
	newdirection = FSteering;
	newdirection += m_direccion;
	if (outOfPath)
	{
		float scalarFlic = 1 - m_weight;
		fliccion = FSteering;
		//fliccion *=m_actualSpeed;
		fliccion *= -1;
		fliccion *= scalarFlic;
		vector2 result = FSteering;
		result += fliccion;
		//result *= m_actualSpeed;
		if (m_speed> result.magnitud())
		{
			float desaceleraction = (result.magnitud() - m_actualSpeed)/(m_weight*1.2);
			float des = desaceleraction * timeDes;
			m_speed = m_actualSpeed + des;
			if (m_speed<= 0)
			{
				m_speed = result.magnitud();
			}
			//m_speed = 1;
			//fliccion = fliccion.normalize();
			//fliccion *= (m_maxSpeed- m_speed);
			//fliccion *= scalarFlic;
			//std::cout <<"time:"<< timeDes<<"\n";
			//std::cout <<"des:"<< des <<"\n";
			//std::cout <<"speed:"<< m_speed<<"\n";
			//std::cout <<"magnitud:"<< result.magnitud() <<"\n";
		}
		else
		{
			minimunSpeed = true;
			m_speed = result.magnitud();
		}
		//FSteering += fliccion;
		m_timeTrans = m_speed / m_acceleration;
	}
//se saca el vectgor de la fuerza menos la direccion y se multiplica por la masa
	// direccion mas nueva direccion
	//esto hara que se voltear hasta que encuentra una nueva direccion en la que si se pueda mover
	vector2 nPos = *m_position;
	nPos += FSteering;
	m_direccion *=1-m_weight;
	nPos += m_direccion;
	m_direccion = nPos;
	m_direccion -= *m_position;
	//FSteering *= m_speed;
	m_direccion *=FSteering.magnitud();
	m_direccion = m_direccion.normalize();
	if (b_follow_arrive)
	{
		OE_followPath = OE_followPath->nextEvent();
	}

}

void Boid::render(sf::RenderWindow & window)
{
	sf::VertexArray lines(sf::LinesStrip, 2);
	m_direccion *= m_speed;
	*m_position += m_direccion;
	vector2 position = *m_position;
	m_sprite.setPosition(position.x, position.y);
	lines[0].position = sf::Vector2f(position.x, position.y);
	lines[1].position = sf::Vector2f(position.x+m_direccion.x*10, position.y+m_direccion.y*10);
	window.draw(m_sprite);
	//window.draw(lines);
	if (bf_arrive(position,m_seekObjetivePos,10))
	{
		b_inPoint = true;
	}
	else
	{
		b_inPoint = false;
	}
}

vector2 Boid::seek(const vector2& posI, const vector2 & posF, const float& magnitud)
{
	vector2 dir;
	vector2 F;
	float m;
	dir = posF;
	dir -= posI;
	m = dir.magnitud();
	F = dir * magnitud;
	return F;
}

vector2 Boid::flee(const vector2& posI, const vector2 & posF, const float & ratio, const float & magnitud)
{
	vector2 dist;
	vector2 dir;
	vector2 F;
	dist = posF;
	dist -= posI;
	
	float m;
	dir = posF;
	dir -= posI;
	//dir = dir.normalize();
	m = dist.magnitud();
	if (m < ratio)
	{
		//dir /= m;
		F = -dir * magnitud;
	}
	else
	{
		F = vector2(0, 0);
	}
	return F;
}

vector2 Boid::arrive(const vector2& posI, const vector2 & posF, const float & magnitud, const float &ratio)
{
	vector2 dir;
	vector2 F;
	float m;
	dir = posF;
	dir -= posI;
	m = dir.magnitud();
	dir = dir.normalize();
	F = dir * magnitud;
	if (m < ratio)
	{
		float proporcion = magnitud * m / ratio;
		F = dir;
		F*=proporcion;
	}
	return F;
}

vector2 Boid::pursue(const vector2 & posI, const vector2 & posF, const vector2 & dirOb, const float & timePredic, const float & vel, const float & magnitud)
{
	vector2 PP;
	vector2 PPDir;
	vector2 F;
	vector2 dir;
	float dist;
	float distPP;
	PP = dirOb;
	PP*=(timePredic*vel);
	PP += posF;
	PPDir = PP;
	PPDir -= posI;
	distPP = PPDir.magnitud();
	dir = posF;
	dir -= posI;
	dist = dir.magnitud();
	if (dist<distPP)
	{
		PP = dirOb;
		PP*=dist;
		PP += posF;
	}
	F = seek(posI,PP,magnitud);
	return F;
}

vector2 Boid::evade(const vector2& posI, const vector2 & posF, const vector2 & dirOb, const float & timePredic, const float &vel, const float & magnitud)
{
	vector2 PP;
	vector2 PPdir;
	vector2 F;
	vector2 dir;
	float dist;
	float distPP;
	PP = dirOb;
	PP *= (timePredic*vel);
	PP += posF;//puede que se sume
	PPdir = PP;
	PPdir -= posI;
	distPP = PPdir.magnitud();
	dir = posF;
	dir -= posI;
	dist = dir.magnitud();
	if (dist<distPP)
	{
		vector2 result;
		result = PP;
		result += dir;
	}
	
	F = flee(posI, PP,100, magnitud);
	return F;
}

vector2 Boid::obstacle(const vector2 & posI, const vector2 & posF, const float & ratio, const float & magnitud)
{
	vector2 dir;
	vector2 F;
	dir = posF;
	dir -= posI;
	float dist;
	dist = dir.magnitud();
	if (dist < ratio)
	{
		F=flee(posI, posF, ratio, magnitud);
	}
	return F;
}

vector2 Boid::wanderRam(const vector2 & posI, const float & rangeX, const float & rangeY, const float & magnitud)
{
	float xram = ((float)rand() / (float)RAND_MAX)*rangeX;
	float yram= ((float)rand() / (float)RAND_MAX)*rangeY;
	vector2 wanderPos = vector2( xram , yram );
	
	return seek(posI, wanderPos, magnitud);
}

vector2 Boid::wanderRamwhitTime(const vector2 & posI, vector2 & posF, const float & rangeX, const float & rangeY, float & timeTrans, const float & timeToChange, const float & magnitud)
{
	if (timeTrans>= timeToChange)
	{
		timeTrans = 0;
//		srand(time(NULL));
		float xram = ((float)rand() / (float)RAND_MAX)*rangeX;
		float yram = ((float)rand() / (float)RAND_MAX)*rangeY;
		posF = vector2(xram, yram);
		//seek(posI, wanderPos, 10);
	}
	return seek(posI, posF, 10);
	//return vector2();
}

vector2 Boid::wanderToPoint(const vector2 & posI, const vector2 & posF, const float & ratio, const float & angle, const float & magnitud)
{
	vector2 F;
	vector2 PP;
	vector2 plano(1,0);
	vector2 dir = posF;
	dir -= posI;
	PP = posF;
	float dist = dir.magnitud();
	dir = dir.normalize();
	if (dist>ratio)
	{

		float midangle = angle / 2;
		float teta = acos(((dir.dot(plano))/(dir.magnitud()*plano.magnitud())));
		float randAngle= ((float)rand() / (float)RAND_MAX)*angle;
		randAngle -= midangle;
		float randPoint=randAngle + teta+ratio;
		float cosss= cos(randPoint) + teta + ratio;
		float sinnn= sin(randPoint) + teta + ratio;
		PP.X += cosss;
		PP.Y += sinnn;
	}
	F = seek(posI, PP, magnitud);
	return F;
}

vector2 Boid::followPaht(const vector2 & pointA, const vector2 & pointB, const vector2 & pos, const float & pathRatio, const float & pointRatio, const float & magnitud, bool&arrivepoint,bool &outofpath)
{
	vector2 F;
	F = seek(pos,pointB,magnitud);
	vector2 Dir = pointB;
	vector2 Dir2;
	vector2 V = pos;
	vector2 P = pointB;
	Dir -= pos;
	V -= pointA;
	P -= pointA;
	vector2 Q = P;
	float escalar = V.magnitud() / P.magnitud();
	Q *= escalar;
	Q += pointA;
	vector2 vecToPath = Q;
	vecToPath -= pos;
	float distToPath = vecToPath.magnitud();
	if (distToPath > pathRatio)
	{
		outofpath = true;
		Dir2 = seek(pos, Q, magnitud*1.5);
		F += Dir2;
	}
	else
	{
		outofpath = false;
	}
	float dist = Dir.magnitud();
	if (dist<=pointRatio)
	{
		arrivepoint = true;
		
	}
	else
	{
		arrivepoint = false;
	}
	return F;
}

vector2 Boid::separate(const vector2 & pos, std::vector<vector2*>& compasPos, const float & ratio, const float & magnitud)
{
	vector2 F;
	for (int i = 0; i < compasPos.size(); i++)
	{
		vector2 dist= pos;
		dist -= *compasPos[i];
		vector2 compaPosition = *compasPos[i];
		vector2 miPosition = pos;
		if (dist.magnitud()<ratio&& miPosition!=compaPosition)
		{
			//std::cout << "separate\n";
			vector2 dir = dist;
			dir = dir.normalize();
			dir *= magnitud;
			dir *=ratio/dist.magnitud();
			F += dir;
		}
		else
		{
			//std::cout << "no separate\n";
		}
	}
	return F;
}

vector2 Boid::cohesion(const vector2 & pos, std::vector<vector2*>& compaPos, const float & ratio, const float & magnitud)
{
	vector2 F;
	vector2 sum;
	int numInRange=0;
	for (int i = 0; i < compaPos.size(); i++)
	{
		vector2 dist = pos;
		dist -= *compaPos[i];
		if (dist.magnitud()<= ratio)
		{
			sum += *compaPos[i];
			numInRange++;
		}
	}
	if (numInRange>0)
	{
		sum /= numInRange;
		vector2 dir = sum;
		dir -= pos;
		vector2 dist = dir;
		dir *= magnitud;
		dir /= ratio / dist.magnitud();
		F = dir ;
	}
	return F;
}

vector2 Boid::alineacion(const vector2 & pos, std::vector<Boid*>& compas, const float & ratio, const float & magnitud)
{
	vector2 F;
	vector2 sum;
	int numInRange = 0;
	for (int i = 0; i < compas.size(); i++)
	{
		vector2 dist = pos;
		dist -= *compas[i]->getBoidPosition();
		if (dist.magnitud() <= ratio)
		{
			sum += compas[i]->getBoidDirection();
			numInRange++;
		}
	}
	if (numInRange > 0)
	{
		sum /= numInRange;
		vector2 dir = sum;
		dir *= magnitud;
		F = dir;
	}
	return F;
}

vector2 Boid::floking( Boid & me, std::vector<Boid*>& compas, std::vector<vector2*>& compaPos, const float & ratio, const float & magnitud)
{
	vector2 F;
	F = cohesion(*me.getBoidPosition(), compaPos, ratio, magnitud);
	F += alineacion(*me.getBoidPosition(), compas, ratio, magnitud);
	F += separate(*me.getBoidPosition(),compaPos,me.getBoidRatio(), magnitud);
	return F;
}

vector2 Boid::followTheLeader( Boid & me, std::vector<Boid*>& compas, std::vector<vector2*>& compaPos, const float & ratio, const float & magnitud)
{
	vector2 F;
	vector2 dir;
	if (!me.iLeader)
	{
		for (int i = 0; i < compas.size(); i++)
		{
			if (compas[i]->iLeader)
			{
				dir = seek(*me.getBoidPosition(), *compas[i]->getBoidPosition(), magnitud);
				vector2 dist = *me.getBoidPosition();
				dist-= *compas[i]->getBoidPosition();
				if (dist.magnitud()<=ratio)
				{
					dir+=flee(*me.getBoidPosition(), *compas[i]->getBoidPosition(),ratio, magnitud*1.5);
				}
				F = dir;
			}
		}
	}
	//F += cohesion(*me.getBoidPosition(), compaPos, ratio, magnitud);
	//F+=separate(*me.getBoidPosition(), compaPos, me.m_ratio, magnitud);

	return F;
}

bool Boid::bf_arrive(const vector2 & posI, const vector2 & posF, const float & ratio)
{
	vector2 dist;
	float m;
	dist = posF;
	dist -= posI;
	m = dist.magnitud();
	if (m<= ratio)
	{
		return true;
	}
	return false;
}

void Boid::changeSeekPos(std::vector<Point>& vec)
{
	vec2ArrayCount++;
	if (vec2ArrayCount== vec.size())
	{
		vec2ArrayCount = 0;
	}
	m_seekObjetivePos = vec[vec2ArrayCount].getPos();
}

float Boid::getDistToPoint()
{
	vector2 dist = follow_pointB;
	dist -= *m_position;
	return dist.magnitud();
}
