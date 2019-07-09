#include "vector2.h"
#include <Window.hpp>
#include <Graphics.hpp>
#include "Runner.h"
#include "Boid.h"
#include <chrono>
#include "Point.h"
sf::RenderWindow *g_window;
//sf::RenderWindow *g_window2;
std::vector<Boid> Boids;
std::vector<vector2*> boidsPos;
std::vector<Point> objetives;
sf::Texture map_texture;
sf::Vector2u map_size;
sf::Sprite map_sprite;
sf::Sprite gsprite;
sf::Texture sonic_texture;
std::vector<sf::Sprite> sprites;
sf::Vector2u sonic_size;
vector2 mousePos;
void display();
void InitBoids();
void update();
void render();
int main()
{
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
	while (g_window->isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
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
		Boids[i].onDelete();
	}
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

	Boid boid2;
	boid2.init(.3, 0, 15, 2, 500, 500,5);
	boid2.b_followPath = true;
	boid2.SetSeekPos(objetives[1].getPos(), 10);
	boid2.SetFollowPath(objetives[2].getPos(), objetives[0].getPos(), 30, 30, 10);
	boid2.m_sprite.setColor(sf::Color(255, 1, 1, 255));

	Boid boid3;
	boid3.init(.2, 0,20, 4,97, 460,5);
	//boid3.setTexture("Resources\\image\\metalSonic.png");
	boid3.b_followPath = true;
	boid3.SetSeekPos(objetives[1].getPos(), 10);
	boid3.SetFollowPath(objetives[21].getPos(), objetives[0].getPos(),50, 50, 10);
	//boid3.m_sprite.setColor(sf::Color(0, 255, 1, 255));
	//Boids.push_back(boid3);
	//Boids[0].setTexture("Resources\\image\\sonic.png");

	Boid boid4;
	boid4.init(1, 0, 20, 2, 63, 484,5);
	boid4.setTexture("Resources\\image\\sonic.png");
	boid4.b_followPath = true;
	boid4.SetSeekPos(objetives[1].getPos(), 10);
	boid4.SetFollowPath(objetives[21].getPos(), objetives[0].getPos(), 50, 50, 10);
	boid4.m_sprite.setColor(sf::Color(255,255, 255, 255));
	//Boids.push_back(boid4);
	if (!sonic_texture.loadFromFile("Resources\\image\\sonic.png"))
	{
		std::cout << "cant lodad texture";
		// error...
	}
	gsprite.setTexture(sonic_texture);
	gsprite.setPosition(boid4.getBoidPosition()->x, boid4.getBoidPosition()->y);
	sonic_size = map_texture.getSize();
	gsprite.setOrigin(sonic_size.x / 2, sonic_size.y / 2);
	sprites.push_back(gsprite);
	//Boids[0].m_sprite = gsprite;

	Boid boid5;
	boid5.init(1, 0, 12, 2, 63, 484, 5);
	boid5.b_followPath = true;
	boid5.SetSeekPos(objetives[1].getPos(), 10);
	boid5.SetFollowPath(objetives[21].getPos(), objetives[0].getPos(), 50, 50, 10);
	boid5.m_sprite.setColor(sf::Color(0, 0, 255, 255));
	//Boids.push_back(boid5);
	Boid boid6;
	boid6.init(.5, 0, 15, 2, 1000, 500, 15);
	boid6.stay = true;
	boid6.m_sprite.setColor(sf::Color(1, 1, 255, 255));
	//Boids.push_back(boid6);
	Boids.resize(8);
	Boids[0].init(0.5, 0, 26, 2, 63, 484, 30);
	Boids[0].b_followPath = true;
	Boids[0].SetSeekPos(objetives[1].getPos(), 10);
	Boids[0].SetFollowPath(objetives[objetives.size()-1].getPos(), objetives[0].getPos(), 80, 80, 10);
	
	Boids[1].init(.25, 0, 20, 2, 97, 460, 30);
	Boids[1].setTexture("Resources\\image\\metalSonic.png");;
	Boids[1].b_followPath = true;
	Boids[1].SetSeekPos(objetives[1].getPos(), 10);
	Boids[1].SetFollowPath(objetives[objetives.size() - 1].getPos(), objetives[0].getPos(), 80, 80, 10);
	
	Boids[2].init(0.5, 0, 24, 2, 97, 507, 30);
	Boids[2].b_followPath = true;
	Boids[2].setTexture("Resources\\image\\silver.png");;
	Boids[2].SetSeekPos(objetives[1].getPos(), 10);
	Boids[2].SetFollowPath(objetives[objetives.size() - 1].getPos(), objetives[0].getPos(), 80, 80, 10);
	
	Boids[3].init(0.3, 0, 25, 2, 63, 533, 30);
	Boids[3].b_followPath = true;
	Boids[3].setTexture("Resources\\image\\nukles.png");;
	Boids[3].SetSeekPos(objetives[1].getPos(), 10);
	Boids[3].SetFollowPath(objetives[objetives.size() - 1].getPos(), objetives[0].getPos(), 80, 80, 10);
	
	Boids[4].init(0.6, 0, 21, 4, 97, 557, 30);
	Boids[4].b_followPath = true;
	Boids[4].setTexture("Resources\\image\\amy.png");;
	Boids[4].SetSeekPos(objetives[1].getPos(), 10);
	Boids[4].SetFollowPath(objetives[objetives.size() - 1].getPos(), objetives[0].getPos(), 80, 80, 10);
	
	Boids[5].init(0.7, 0, 20, 5, 63, 581, 30);
	Boids[5].b_followPath = true;
	Boids[5].setTexture("Resources\\image\\tails.png");;
	Boids[5].SetSeekPos(objetives[1].getPos(), 10);
	Boids[5].SetFollowPath(objetives[objetives.size() - 1].getPos(), objetives[0].getPos(), 80, 80, 10);
	
	Boids[6].init(0.5, 0, 25, 2, 97, 606, 30);
	Boids[6].b_followPath = true;
	Boids[6].setTexture("Resources\\image\\shadow.png");;
	Boids[6].SetSeekPos(objetives[1].getPos(), 10);
	Boids[6].SetFollowPath(objetives[objetives.size() - 1].getPos(), objetives[0].getPos(), 80, 80, 10);
	
	Boids[7].init(0.25, 0, 20, 4, 63, 627, 30);
	Boids[7].b_followPath = true;
	Boids[7].setTexture("Resources\\image\\eggman.png");;
	Boids[7].SetSeekPos(objetives[1].getPos(), 10);
	Boids[7].SetFollowPath(objetives[objetives.size() - 1].getPos(), objetives[0].getPos(), 80, 80, 10);
	

	boidsPos.resize(Boids.size());
	for (int i = 0; i < Boids.size(); i++)
	{
		boidsPos[i]=Boids[i].getBoidPosition();
	}
	for (int i = 0; i < Boids.size(); i++)
	{
		Boids[i].setcompasPosition(boidsPos);
	}

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
		std::cout << "boid " << i + 1 << " speed: " << Boids[i].getBoidSpeed()<<"\n";
		if (Boids[i].b_inPoint)
		{
			//Boids[i].changeSeekPos(objetives);
		}
	}
}
void render()
{
	//sf__
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	//{
	//	system("cls");
	//	sf::Vector2i position = sf::Mouse::get();
	//	std::cout << "x: " << position.x << "y: " << position.y<<"\n";
	//}
	g_window->draw(map_sprite);
	sf::VertexArray lines(sf::LinesStrip, objetives.size()+1);
	for (size_t i = 0; i < objetives.size(); i++)
	{
		lines[i].position = sf::Vector2f(objetives[i].getPos().x, objetives[i].getPos().y);

	}
	//lines[1].position = sf::Vector2f(objetives[1].getPos().x, objetives[1].getPos().y);
	//lines[2].position = sf::Vector2f(objetives[2].getPos().x, objetives[2].getPos().y);
	//lines[3].position = sf::Vector2f(objetives[3].getPos().x, objetives[3].getPos().y);
	//lines[4].position = sf::Vector2f(objetives[4].getPos().x, objetives[4].getPos().y);
	//lines[5].position = sf::Vector2f(objetives[5].getPos().x, objetives[5].getPos().y);
	//lines[6].position = sf::Vector2f(objetives[6].getPos().x, objetives[6].getPos().y);
	//lines[7].position = sf::Vector2f(objetives[7].getPos().x, objetives[7].getPos().y);
	//lines[8].position = sf::Vector2f(objetives[8].getPos().x, objetives[8].getPos().y);
	//lines[9].position = sf::Vector2f(objetives[9].getPos().x, objetives[9].getPos().y);
	//lines[10].position = sf::Vector2f(objetives[10].getPos().x, objetives[10].getPos().y);
	//lines[11].position = sf::Vector2f(objetives[11].getPos().x, objetives[11].getPos().y);
	//lines[12].position = sf::Vector2f(objetives[12].getPos().x, objetives[12].getPos().y);
	//lines[13].position = sf::Vector2f(objetives[13].getPos().x, objetives[13].getPos().y);
	//lines[14].position = sf::Vector2f(objetives[14].getPos().x, objetives[14].getPos().y);
	//lines[15].position = sf::Vector2f(objetives[15].getPos().x, objetives[15].getPos().y);
	//lines[16].position = sf::Vector2f(objetives[16].getPos().x, objetives[16].getPos().y);
	//lines[17].position = sf::Vector2f(objetives[17].getPos().x, objetives[17].getPos().y);
	//lines[18].position = sf::Vector2f(objetives[18].getPos().x, objetives[18].getPos().y);
	//lines[19].position = sf::Vector2f(objetives[19].getPos().x, objetives[19].getPos().y);
	//lines[20].position = sf::Vector2f(objetives[20].getPos().x, objetives[20].getPos().y);
	//lines[21].position = sf::Vector2f(objetives[21].getPos().x, objetives[21].getPos().y);
	lines[objetives.size() ].position = sf::Vector2f(objetives[0].getPos().x, objetives[0].getPos().y);

	for (int i = 0; i < objetives.size(); i++)
	{
		//objetives[i].draw(*g_window);
	}
	//g_window->draw(lines);
	for (int i = 0; i < Boids.size(); i++)
	{
		Boids[i].render(*g_window);
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
		Boids[i].m_timeTrans += (timeTrans/60);
		Boids[i].m_wanderTime += (timeTrans/1);
		Boids[i].timeDes += (timeTrans / 60);
	}
}