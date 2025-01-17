#pragma once
#include "vector2.h"
#include <vector>
#include <Graphics.hpp>
#include "Point.h"
#include <Window.hpp>
#include "Observe_Event.h"

class Boid
{
public:
	Boid();
	~Boid();
	vector2 m_direccion;
	float m_acceleration;
	float m_desacceleration;
	float m_weight;
	float m_speed;
	float m_actualSpeed;
	float m_maxSpeed;
	float m_actualMaxSpeed;
	float m_ratio;
	int controlID=-1;
public:
	
	vector2* m_position;
	vector2 fliccion;
	void setPosition(const float& posX, const float& posy);
	sf::Texture texture;
	sf::Vector2u size;
	//seek data
	vector2 m_seekObjetivePos;
	float m_seekMangitude;
	//flee data
	vector2 m_fleeObjetPos;
	float m_fleeRatio;
	float m_fleeMangitude;
	//arrive data
	vector2 m_arrivePos;
	float m_arriveRatio;
	float m_arriveMangitude;
	//pursue Data
	vector2 m_objetivePos;
	vector2 m_objetiveDir;
	float m_pursueMangitude;
	float m_objetiveSpeed;
	//evade data
	vector2 m_predatorPos;
	vector2 m_predatorDir;
	float m_evadeMangitude;
	float m_predatorSpeed;
	//obstacle
	vector2 m_obstaclePos;
	float m_obstacleRatio;
	float m_obstacleMagnitud;
	//Wander
	//follow Path
	vector2 follow_pointA;
	vector2 follow_pointB;
	float follow_PathRatio;
	float follow_PointRatio;
	float follow_Magnitud;
	//Separate
	std::vector<vector2*>compas_pos;
	std::vector<Boid*>compas;


	int vec2ArrayCount = 0;
	std::string m_name;
	sf::Color m_color;
public:
	float m_acelartionTime = 0;
	Observe_Event *OE_followPath;
	bool iLeader = false;
	int follow_pathNum = 0;
	vector2 m_wamderPos;
	sf::Sprite m_sprite;
	bool b_inPoint;
	bool b_Seek=false;
	bool b_flee=false;
	bool b_arrive=false;
	bool b_pursue=false;
	bool b_evade = false;
	bool b_obstacle = false;
	bool b_wandeRam = false;
	bool b_wandeRamTime = false;
	bool b_wandeToPoint = false;
	bool b_followPath = false;
	bool b_floking = false;
	bool b_followTheLeader = false;
	void SetSeekPos(const vector2& objetivePos,const float & magnitud);
	void SetFleeData(const vector2& objetPos, const float & ratio, const float & magnitud);
	void SetArriveData(const vector2& arrivePos, const float & ratio, const float & magnitud);
	void SetPursueData(const vector2& objetivePos, const vector2& objetiveDir, const float & objetiveSpeed, const float & magnitud);
	void SetEvadeData(const vector2 & predatorPos, const vector2 & predatorDir, const float & predatorSpeed, const float & magnitud);
	void SetobstacleData(const vector2& objetPos, const float & ratio, const float & magnitud);
	void SetFollowPath( Point& pointA, Point& pointB,const float & pathRatio, const float & pointRatio, const float & magnitud);
	void setBoidRatio(const float &ratio) { m_ratio =ratio; };
	void setcompasPosition(std::vector<vector2*>compa) { compas_pos = compa; };
	void setcompas(std::vector<Boid*>GETcompas) { compas = GETcompas; };
	void setName(std::string name) { m_name = name; };
	std::string getName() { return m_name; };

	vector2* getBoidPosition() { return m_position; };
	vector2 getBoidDirection() { return m_direccion; };
	float getBoidRatio() { return m_ratio; };
	float getBoidSpeed() { return m_speed; };
	void onDelete();
public:
	bool stay = false;
	void init(const float& weight = 1.0f, const float& speed = 2, const float& maxSpeed = 2, const float& acceleration = 1.0f, const float& posX = 0.0f, const float& posY = 0.0f, const float& ratio = 0.0f);
	void setTexture(std::string dir_texture);
	void destroy();
	void update();
	void render( sf::RenderWindow &window);
	static vector2 seek(const vector2& posI, const vector2 & posF, const float& magnitud);
	static vector2 flee(const vector2& posI,const vector2 & posF, const float & ratio, const float& magnitud);
	static vector2 arrive(const vector2& posI, const vector2 & posF, const float & magnitud, const float &ratio);
	static vector2 pursue(const vector2& posI, const vector2 & posF, const vector2 & dirOb, const float & timePredic, const float &vel, const float & magnitud);
	static vector2 evade(const vector2& posI, const vector2 & posF, const vector2 & dirOb, const float & timePredic, const float &vel, const float & magnitud);
	static vector2 obstacle(const vector2& posI, const vector2 & posF,const float & ratio, const float & magnitud);
	static vector2 wanderRam(const vector2& posI, const float & rangeX, const float & rangeY, const float & magnitud);
	static vector2 wanderRamwhitTime(const vector2& posI, vector2& posF, const float & rangeX, const float & rangeY, float & timeTrans,const float & timeToChange, const float & magnitud);
	static vector2 wanderToPoint(const vector2& posI, const vector2& posF, const float & ratio,const float& angle, const float & magnitud);
	static vector2 followPaht(const vector2& pointA, const vector2& pointB, const vector2& pos,const float & pathRatio, const float & pointRatio, const float & magnitud,bool&arrivepoint,bool &outofpath);
	static vector2 separate(const vector2& pos, std::vector<vector2*>& compaPos,const float & ratio, const float & magnitud);
	static vector2 cohesion(const vector2& pos, std::vector<vector2*>& compaPos,const float & ratio, const float & magnitud);
	static vector2 alineacion(const vector2& pos, std::vector<Boid*>& compas,const float & ratio, const float & magnitud);
	static vector2 floking( Boid& me, std::vector<Boid*>& compas, std::vector<vector2*>& compaPos,const float & ratio, const float & magnitud);
	static vector2 followTheLeader(Boid & me, std::vector<Boid*>& compas, std::vector<vector2*>& compaPo, const float & ratio, const float & magnitud);
	static bool bf_arrive(const vector2& posI, const vector2 & posF, const float & ratio);
	void changeSeekPos(std::vector<Point>& vec);

	float getDistToPoint();

	bool b_follow_arrive = false;
	bool outOfPath = false;
	float m_timeTrans=0;
	float timeDes = 0;
	float m_wanderTime = 0;
	bool minimunSpeed = false;


	int numVuelta=0;
	float dist=0;
	int punto=0;
	int lugar = 0;
};

