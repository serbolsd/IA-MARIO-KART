#include "vector2.h"
#include <Window.hpp>
#include <Graphics.hpp>
#include "Runner.h"
#include "Boid.h"
#include <chrono>
#include "Point.h"
sf::RenderWindow g_window(sf::VideoMode(1920, 1080), "Boids");
std::vector<Boid> Boids;
std::vector<Point> objetives;
vector2 mousePos;
void display();
void InitBoids();
void update();
void render();
int main()
{	
	g_window.setFramerateLimit(120);
	// run the program as long as the window is open
	InitBoids();
	while (g_window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (g_window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				g_window.close();
		}
		g_window.clear(sf::Color(100, 0, 255, 0));

		mousePos.x = event.mouseMove.x;
		mousePos.y = event.mouseMove.y;
		//run.m_sprite.setPosition(run.getPosition().x, run.getPosition().y);
		//run2.m_sprite.setPosition(run2.getPosition().x, run2.getPosition().y);
		//run3.m_sprite.setPosition(run3.getPosition().x, run3.getPosition().y);
		//
		//
		//run.runingTo(run3.getPosition());
		//run.scapeTo(run2);

		display();

		//g_window.display();
	}

	return 0;
}

void InitBoids()
{
	Point p1;
	p1.init(vector2(100, 500));
	objetives.push_back(p1);
	Point p2;
	p2.init(vector2(1000, 100));
	objetives.push_back(p2);
	Point p3;
	p3.init(vector2(500, 500));
	objetives.push_back(p3);
	Point p4;
	p4.init(vector2(900, 900));
	objetives.push_back(p4);
	Point p5;
	p5.init(vector2(700, 600));
	objetives.push_back(p5);
	Boid boid1;
	boid1.init(.8, 0, 2, 1, 0, 0);
	//boid5.b_wandeToPoint = true;
	boid1.b_Seek = true;
	//boid5.b_followPath = true;
	boid1.SetSeekPos(objetives[0].getPos(), 10);
	boid1.SetFollowPath(boid1.getBoidPosition(), objetives[0].getPos(),30, 30, 10);
	boid1.m_sprite.setColor(sf::Color(255, 105, 200, 255));
	//boid1.m_wamderPos = vector2(1000, 1000);
	Boids.push_back(boid1);
	Boid boid2;
	boid2.init(.3, 0, 15, 2, 500, 500);
	//boid5.b_wandeToPoint = true;
	//boid2.b_Seek = true;
	boid2.b_followPath = true;
	boid2.SetSeekPos(objetives[1].getPos(), 10);
	boid2.SetFollowPath(objetives[2].getPos(), objetives[0].getPos(), 30, 30, 10);
	boid2.m_sprite.setColor(sf::Color(255, 1, 1, 255));
	//boid1.m_wamderPos = vector2(1000, 1000);
	Boids.push_back(boid2);
	Boid boid3;
	boid3.init(.1, 0,15, 2, 500, 500);
	//boid5.b_wandeToPoint = true;
	//boid2.b_Seek = true;
	boid3.b_followPath = true;
	boid3.SetSeekPos(objetives[1].getPos(), 10);
	boid3.SetFollowPath(objetives[2].getPos(), objetives[0].getPos(), 30, 30, 10);
	boid3.m_sprite.setColor(sf::Color(0, 255, 1, 255));
	//boid1.m_wamderPos = vector2(1000, 1000);
	Boids.push_back(boid3);
	//Boid boid2;
	//boid2.init(.2, 0, 2, 1, 0, 0);
	//boid2.b_Seek = true;
	//boid2.SetSeekPos(objetives[1].getPos(), 10);
	//boid2.m_sprite.setColor(sf::Color(0, 0, 255, 0));
	//Boids.push_back(boid2);
	//Boid boid5;
	//boid5.init(.2, 0, 2, 1, 0, 0);
	////boid5.b_wandeToPoint = true;
	//boid5.b_Seek = true;
	////boid5.b_followPath = true;
	//boid5.SetSeekPos(objetives[0].getPos(), 10);
	//boid5.SetFollowPath(objetives[0].getPos(), objetives[1].getPos(), 20, 30, 10);
	//boid5.m_sprite.setColor(sf::Color(255, 105, 200, 255));
	////boid5.m_wamderPos = vector2(1000, 1000);
	//Boids.push_back(boid5);
}

void update()
{

	for (int i = 0; i < Boids.size(); i++)
	{
		if (Boids[i].b_followPath&&Boids[i].b_follow_arrive)
		{
			Boids[i].follow_pathNum++;
			if (Boids[i].follow_pathNum > objetives.size()-1)
			{
				Boids[i].SetFollowPath(objetives[Boids[i].follow_pathNum-1].getPos(), objetives[0].getPos(), 30, 30,10);
				Boids[i].follow_pathNum = 0;
			}
			else
			{
				Boids[i].SetFollowPath(objetives[Boids[i].follow_pathNum-1].getPos(), objetives[Boids[i].follow_pathNum].getPos(), 30, 30, 10);
			}
		}
	}
	for (int i = 0; i < Boids.size(); i++)
	{
		Boids[i].update();
		if (Boids[i].b_inPoint)
		{
			//Boids[i].changeSeekPos(objetives);
		}
	}
}
void render()
{
	sf::VertexArray lines(sf::LinesStrip, 7);
	lines[0].position = sf::Vector2f(objetives[2].getPos().x, objetives[2].getPos().y);
	lines[1].position = sf::Vector2f(objetives[0].getPos().x, objetives[0].getPos().y);
	lines[2].position = sf::Vector2f(objetives[1].getPos().x, objetives[1].getPos().y);
	lines[3].position = sf::Vector2f(objetives[2].getPos().x, objetives[2].getPos().y);
	lines[4].position = sf::Vector2f(objetives[3].getPos().x, objetives[3].getPos().y);
	lines[5].position = sf::Vector2f(objetives[4].getPos().x, objetives[4].getPos().y);
	lines[6].position = sf::Vector2f(objetives[0].getPos().x, objetives[0].getPos().y);

	for (int i = 0; i < Boids.size(); i++)
	{
		Boids[i].render(g_window);
	}
	for (int i = 0; i < objetives.size(); i++)
	{
		objetives[i].draw(g_window);
	}
	g_window.draw(lines);
}
void display()
{
	auto start = std::chrono::steady_clock::now();
	g_window.clear(sf::Color(100, 0, 255, 0));
	update();
	render();
	g_window.display();
	auto end = std::chrono::steady_clock::now();
	float timeTrans= std::chrono::duration_cast<std::chrono::milliseconds>  (end - start).count();
	for (int i = 0; i < Boids.size(); i++)
	{
		Boids[i].m_timeTrans += (timeTrans/1000);
		Boids[i].m_wanderTime += (timeTrans/1000);
		Boids[i].timeDes += (timeTrans / 1000);
	}
}