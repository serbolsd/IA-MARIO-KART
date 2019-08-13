#include "vector2.h"
#include <Window.hpp>
#include <Graphics.hpp>
#include "Boid.h"
#include <chrono>
#include "Point.h"
#include "Manager.h"
#include <sstream>
#include "GpuPreference.hpp"
#include "Pruebas.h"
#include "CinputManager.h"
sf::Font font;
sf::Text *text;
sf::RenderWindow *g_window;
std::vector<Boid*> Boids;
std::vector<vector2*> boidsPos;
std::vector<Point> objetives;
sf::Texture map_texture;
sf::Vector2u map_size;
sf::Sprite map_sprite;
vector2 mousePos;
void display();
void InitBoids();
void update();
void render();
void initPruebas();
Manager g_manager;
CinputManager g_inManager;
using namespace pruebas;
void chekPositions();
void onDelete()
{
	delete g_window;
	for (size_t i = 0; i < Boids.size(); i++)
	{
		Boids[i]->onDelete();
		//delete Boids[i];
		delete boidsPos[i];	
	}
	delete[]text;
}
int main()
{

	if (!font.loadFromFile("SonicShuffle.ttf"))
	{
		std::cout << "cant lodad font";
		// error...
	}
	if (!map_texture.loadFromFile("Resources\\image\\mariocircuit-3.png"))
	{
		std::cout << "cant lodad texture";
		// error...
	}
	map_sprite.setTexture(map_texture);
	map_size = map_texture.getSize();
	map_sprite.setOrigin(map_size.x / 2, map_size.y / 2);
	map_sprite.setPosition(map_size.x / 2, map_size.y / 2);
	//sf::RenderWindow g_windowPrueba(sf::VideoMode(map_size.x, map_size.y), "Boids");
	//g_window2 = new sf::RenderWindow ();
	g_window= new sf::RenderWindow(sf::VideoMode(map_size.x, map_size.y), "Boids");

	//g_window->setFramerateLimit(120);
	// run the program as long as the window is open
	InitBoids();
	sf::Event event;
	while (g_window->isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		while (g_window->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				g_window->close();
		}
		g_window->clear(sf::Color(100, 0, 255, 0));

		mousePos.x = event.mouseMove.x;
		mousePos.y = event.mouseMove.y;
		system("cls");
		//sf::Vector2i position = mousePos;
		std::cout << "x: " << mousePos.x << " y: " << mousePos.y << "\n";
		//run.m_sprite.setPosition(run.getPosition().x, run.getPosition().y);
		//run2.m_sprite.setPosition(run2.getPosition().x, run2.getPosition().y);
		//run3.m_sprite.setPosition(run3.getPosition().x, run3.getPosition().y);
		//
		//
		//run.runingTo(run3.getPosition());
		//run.scapeTo(run2);

		display();

		//g_window->display();
	}
	for (int i = 0; i < Boids.size(); i++)
	{
		Boids[i]->onDelete();
	}
	for (int i = 0; i < Boids.size(); i++)
	{
		delete Boids[i];
	}
	onDelete();
	//Boids.clear();
	return 0;
}
void InitBoids()
{
	Point p1;
	p1.init(vector2(81, 181));
	objetives.push_back(p1);
	Point p1_1;
	p1_1.init(vector2(104, 127));
	objetives.push_back(p1_1);
	Point p2;
	p2.init(vector2(158, 82));
	objetives.push_back(p2);
	Point p2_2;
	p2_2.init(vector2(158, 82));
	objetives.push_back(p2_2);
	Point p3;
	p3.init(vector2(306, 108));
	objetives.push_back(p3);
	Point p4;
	p4.init(vector2(413, 297));
	objetives.push_back(p4);
	Point p4_1;
	p4_1.init(vector2(413, 297));
	objetives.push_back(p4_1);
	Point p5;
	p5.init(vector2(617, 292));
	objetives.push_back(p5);
	Point p6;
	p6.init(vector2(676, 131));
	objetives.push_back(p6);
	Point p6_1;
	p6_1.init(vector2(699, 90));
	objetives.push_back(p6_1);
	Point p6_2;
	p6_2.init(vector2(786, 67));
	objetives.push_back(p6_2);
	Point p7;
	p7.init(vector2(874, 85));
	objetives.push_back(p7);
	Point p7_1;
	p7_1.init(vector2(929, 164));
	objetives.push_back(p7_1);
	Point p8;
	p8.init(vector2(953, 248));
	objetives.push_back(p8);
	Point p8_1;
	p8_1.init(vector2(939, 343));
	objetives.push_back(p8_1);
	Point p9;
	p9.init(vector2(907, 406));
	objetives.push_back(p9);
	Point p10;
	p10.init(vector2(373, 558));
	objetives.push_back(p10);
	Point p11;
	p11.init(vector2(424, 634));
	objetives.push_back(p11);
	Point p12;
	p12.init(vector2(870, 643));
	objetives.push_back(p12);
	Point p12_1;
	p12_1.init(vector2(910, 665));
	objetives.push_back(p12_1);
	Point p13;
	p13.init(vector2(953, 729));
	objetives.push_back(p13);
	Point p14;
	p14.init(vector2(937, 860));
	objetives.push_back(p14);
	Point p15;
	p15.init(vector2(858, 917));
	objetives.push_back(p15);

	Point p16;
	p16.init(vector2(639, 920));
	objetives.push_back(p16);
	Point p17;
	p17.init(vector2(601, 830));
	objetives.push_back(p17);
	Point p18;
	p18.init(vector2(464, 822));
	objetives.push_back(p18);
	Point p19;
	p19.init(vector2(320, 958));
	objetives.push_back(p19);
	Point p20;
	p20.init(vector2(175, 977));
	objetives.push_back(p20);
	Point p20_1;
	p20_1.init(vector2(108, 894));
	objetives.push_back(p20_1);
	Point p21;
	p21.init(vector2(77, 767));
	objetives.push_back(p21);
	Boids.resize(8);
	//Boids.resize(12);
	Boids[0] = new Boid;
	Boids[0]->controlID=0;
	Boids[0]->m_color = {0,0,255,255};
	Boids[0]->setName("Sonic");
	Boids[0]->init(.8, 0, 26, 2, 63, 484, 30);
	Boids[0]->b_followPath = true;
	Boids[0]->iLeader = true;
	Boids[0]->SetSeekPos(objetives[1].getPos(), 10);
	Boids[0]->SetFollowPath(objetives[objetives.size() - 1], objetives[0],150, 80,10);

	Boids[2] = new Boid;
	Boids[2]->controlID = 1;
	Boids[2]->m_color = { 255,255,255,255 };
	Boids[2]->init(.8, 0, 24, 2, 97, 507, 30);
	Boids[2]->b_followPath = true;
	Boids[2]->setTexture("Resources\\image\\silver.png");;
	Boids[2]->setName("Silver");
	Boids[2]->SetSeekPos(objetives[1].getPos(), 10);
	Boids[2]->SetFollowPath(objetives[objetives.size() - 1], objetives[0], 150, 80, 10);

	Boids[1] = new Boid;
	Boids[1]->controlID = 2;
	Boids[1]->m_color = { 0, 0, 102 ,255};
	Boids[1]->init(.25, 0, 20, 2, 97, 460, 30);
	Boids[1]->setTexture("Resources\\image\\metalSonic.png");;
	Boids[1]->setName("MetalSonic");
	Boids[1]->b_followPath = true;
	Boids[1]->SetSeekPos(objetives[1].getPos(), 10);
	Boids[1]->SetFollowPath(objetives[objetives.size() - 1], objetives[0], 150, 80,10);

	Boids[3] = new Boid;
	Boids[3]->controlID = 3;
	Boids[3]->m_color = { 255, 0, 0 ,255};
	Boids[3]->init(0.3, 0, 25, 2, 63, 533, 30);
	Boids[3]->b_followPath = true;
	Boids[3]->setTexture("Resources\\image\\nukles.png");;
	Boids[3]->setName("Nudillos");
	Boids[3]->SetSeekPos(objetives[1].getPos(), 10);
	Boids[3]->SetFollowPath(objetives[objetives.size() - 1], objetives[0], 150, 80,10);

	Boids[4] = new Boid;
	Boids[4]->controlID = 4;
	Boids[4]->m_color = { 255, 102, 204 ,255};
	Boids[4]->init(0.6, 0, 21, 4, 97, 557, 30);
	Boids[4]->b_followPath = true;
	Boids[4]->setTexture("Resources\\image\\amy.png");;
	Boids[4]->setName("Amy");
	Boids[4]->SetSeekPos(objetives[1].getPos(), 10);
	Boids[4]->SetFollowPath(objetives[objetives.size() - 1], objetives[0], 150, 80,10);

	Boids[5] = new Boid;
	Boids[5]->controlID = 5;
	Boids[5]->m_color = { 255, 255, 0 ,255};
	Boids[5]->init(0.7, 0, 20, 5, 63, 581, 30);
	Boids[5]->b_followPath = true;
	Boids[5]->setTexture("Resources\\image\\tails.png");;
	Boids[5]->setName("Tails");
	Boids[5]->SetSeekPos(objetives[1].getPos(), 10);
	Boids[5]->SetFollowPath(objetives[objetives.size() - 1], objetives[0], 150, 80,10);

	Boids[6] = new Boid;
	Boids[6]->controlID = 6;
	Boids[6]->m_color = { 51, 0, 0 ,255};
	Boids[6]->init(0.5, 0, 25, 2, 97, 606, 30);
	Boids[6]->b_followPath = true;
	Boids[6]->setTexture("Resources\\image\\shadow.png");;
	Boids[6]->setName("Shadow");
	Boids[6]->SetSeekPos(objetives[1].getPos(), 10);
	Boids[6]->SetFollowPath(objetives[objetives.size() - 1], objetives[0], 150, 80,10);

	Boids[7] = new Boid;
	Boids[7]->controlID = 7;
	Boids[7]->m_color = { 153, 0, 0 ,255};
	Boids[7]->init(0.25, 0, 20, 4, 63, 627, 30);
	Boids[7]->b_followPath = true;
	Boids[7]->setTexture("Resources\\image\\eggman.png");;
	Boids[7]->setName("Eggman");
	Boids[7]->SetSeekPos(objetives[1].getPos(), 10);
	Boids[7]->SetFollowPath(objetives[objetives.size() - 1], objetives[0], 150, 80,10);



	boidsPos.resize(Boids.size());
	text = new sf::Text[Boids.size()];


	g_manager.initObserveEventsFollowPath(objetives.size());
	for (int i = 0; i < Boids.size(); i++)
	{
		boidsPos[i]=Boids[i]->getBoidPosition();
		text[i].setFont(font);
		// set the character size
		text[i].setCharacterSize(24); // in pixels, not points!
		text[i].setFillColor(Boids[i]->m_color);
		//text[i].setStyle(sf::Text::Bold | sf::Text::Underlined);
	}
	for (int i = 0; i < Boids.size(); i++)
	{
		Boids[i]->setcompas(Boids);
		Boids[i]->setcompasPosition(boidsPos);
		Boids[i]->OE_followPath=g_manager.FirstEvent;
	}
}
void update()
{
	

	for (int i = 0; i < Boids.size(); i++)
	{
		if (!sf::Joystick::isConnected(Boids[i]->controlID))
		{
			continue;
		}
		if (Boids[i]->b_followPath&&Boids[i]->b_follow_arrive)
		{
			Boids[i]->follow_pathNum++;
			if (Boids[i]->follow_pathNum > objetives.size()-1)
			{
				Boids[i]->SetFollowPath(objetives[Boids[i]->follow_pathNum-1], objetives[0], 150, 80, 10);
				Boids[i]->follow_pathNum = 0;
				Boids[i]->punto=0;
				Boids[i]->numVuelta++;
			}
			else
			{
				Boids[i]->SetFollowPath(objetives[Boids[i]->follow_pathNum-1], objetives[Boids[i]->follow_pathNum], 150, 80, 10);
				Boids[i]->punto++;

			}
		}
		if (Boids[i]->follow_pathNum==0 )
		{
			Boids[i]->SetFollowPath(objetives[objetives.size() - 1], objetives[0], 150, 80, 10);
		}
		else
		{
			Boids[i]->SetFollowPath(objetives[Boids[i]->follow_pathNum - 1], objetives[Boids[i]->follow_pathNum], 150, 80, 10);
		}
	}
	for (int i = 0; i < Boids.size(); i++)
	{
		if (sf::Joystick::isConnected(Boids[i]->controlID))
		{
			g_inManager.onUpdate(Boids[i]->controlID,*Boids[i]);
			continue;
		}
		//Boids[i]->setcompas(Boids);
		//Boids[i]->update();

		if (Boids[i]->b_inPoint)
		{
			//Boids[i]->changeSeekPos(objetives);
		}
	}
	chekPositions();
	
}
void render()
{
	g_window->draw(map_sprite);
	sf::VertexArray lines(sf::LinesStrip, objetives.size()+1);
	for (size_t i = 0; i < objetives.size(); i++)
	{
		lines[i].position = sf::Vector2f(objetives[i].getPos().x, objetives[i].getPos().y);

	}
	lines[objetives.size() ].position = sf::Vector2f(objetives[0].getPos().x, objetives[0].getPos().y);

	for (int i = 0; i < objetives.size(); i++)
	{
		objetives[i].draw(*g_window);
	}
	//g_window->draw(lines);
	int pos = 0;
	for (int i = 0; i < Boids.size(); i++)
	{
		//std::cout << Boids[i]->lugar << " " << Boids[i]->getName() << "\t speed: " << (int)Boids[i]->getBoidSpeed() << " \t";
		std::cout << Boids[i]->lugar << " " << Boids[i]->getName() << "\t vuelta: " << (int)Boids[i]->numVuelta << " \tpunto:" << (int)Boids[i]->punto << "\tdist: " << (float)Boids[i]->getDistToPoint();
		std::stringstream ss;
		ss << Boids[i]->lugar;
		ss << " ";
		ss << " ";
		ss << Boids[i]->getName();
		std::string str = ss.str();
		Boids[i]->OE_followPath->OnObserver();
		std::cout << "\n";
		// set the string to display
		text[i].setString(str);
		text[i].setPosition(10,10+pos);
		pos += 20;
	}
	for (int i = 0; i < Boids.size(); i++)
	{
		if (sf::Joystick::isConnected(Boids[i]->controlID))
		{
			Boids[i]->render(*g_window);
			text[i].setFillColor(Boids[i]->m_color);
			g_window->draw(text[i]);
		}	
	}
	
}
void display()
{
	auto start = std::chrono::steady_clock::now();
	g_window->clear(sf::Color(100, 0, 255, 0));
	update();
	render();
	g_window->display();
	auto end = std::chrono::steady_clock::now();
	float timeTrans= std::chrono::duration_cast<std::chrono::milliseconds>  (end - start).count();
	for (int i = 0; i < Boids.size(); i++)
	{
		Boids[i]->m_timeTrans += (timeTrans/60);
		Boids[i]->m_wanderTime += (timeTrans/1);
		Boids[i]->timeDes += (timeTrans / 60);
		g_inManager.m_timeTrans = (timeTrans / 60);
	}
}
void chekPositions()
{
	for (int i = Boids.size() - 1; i > -1; i--)
	{
		for (int j = Boids.size() - 1; j > -1; j--)
		{
			if (j == i)
			{
				continue;
			}
			if (Boids[j]->numVuelta > Boids[i]->numVuelta)
			{
				Boid * change = Boids[i];
				Boids[i] = Boids[j];
				Boids[j] = change;
			}
		}
	}
	for (int i = Boids.size() - 1; i > -1; i--)
	{
		for (int j = Boids.size() - 1; j > -1; j--)
		{
			if (j == i)
			{
				continue;
			}
			if (Boids[j]->punto > Boids[i]->punto
				&&Boids[j]->numVuelta == Boids[i]->numVuelta)
			{
				Boid * change = Boids[i];
				Boids[i] = Boids[j];
				Boids[j] = change;
			}
		}
	}
	for (int i = Boids.size()-1; i > -1; i--)
	{
		for (int j = Boids.size()-1; j > -1; j--)
		{

			if (j == i)
			{
				continue;
			}
			if (Boids[j]->getDistToPoint() < Boids[i]->getDistToPoint()
				&& Boids[j]->numVuelta == Boids[i]->numVuelta
				&& Boids[j]->punto == Boids[i]->punto)
			{
				Boid * change = Boids[i];
				Boids[i] = Boids[j];
				Boids[j] = change;
			}
		}
	}
	for (size_t i = 0; i < Boids.size(); i++)
	{
		Boids[i]->lugar = i + 1;
	}
}
void initPruebas()
{
	if (checkVectorInit())
		std::cout << "El vector SI se inicia en (0,0)\n";
	else
		std::cout << "El vector NO se inicia en (0,0)\n";
	if (checkModulo())
		std::cout << "La magnitud de vector SI da el resultado esperado\n";
	else
		std::cout << "La magnitud de vector NO da el resultado esperado\n";
	if (checkVectorSum())
		std::cout << "La suma de los vectores SI da el resultado esperado\n";
	else
		std::cout << "La suma de los vectores NO da el resultado esperado\n";
	if (checkVectorNormalize())
		std::cout << "La Normalizacion de un vector SI da el resultado esperado\n";
	else
		std::cout << "La Normalizacion de un vector NO da el resultado esperado\n";
	if (checkVectorDot())
		std::cout << "El producto punto de los vectores SI da el resultado esperado\n";
	else
		std::cout << "El producto punto de los vectores NO da el resultado esperado\n";
	if (checkVectorCroos())
		std::cout << "El producto Cruz de los vectores SI da el resultado esperado\n";
	else
		std::cout << "El producto Cruz de los vectores NO da el resultado esperado\n";
	if (ChecKBoidsFunctionSeek())
		std::cout << "El comportamiento Seek SI da el resultado esperado\n";
	else
		std::cout << "El comportamiento Seek NO da el resultado esperado\n";
	if (ChecKBoidsFunctionFlee())
		std::cout << "El comportamiento FLEE SI da el resultado esperado\n";
	else
		std::cout << "El comportamiento FLEE NO da el resultado esperado\n";
}