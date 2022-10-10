//input.h header

#ifndef INPUT_H
#define INPUT_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Input
{
	struct Button { bool left, right, up, down, space, escape; };

public:

	Input();
	Button GetButton(void) const;
	void InputHandler(Event event, RenderWindow& window);

private:

	Button button;
};

#endif

//main.h header

#include <iostream>
#include <SFML/Graphics.hpp>
#include "input.h"

const int WIN_WIDTH = 2050;
const int WIN_HEIGHT = 900;

using namespace sf;
using namespace std;

void SetText(Text& txt, String str, bool bold, int size, int posx, int posy);
void CheckBtn();

//input.cpp

#include "input.h"

Input::Input()
{
	button.left = button.right = button.up = button.down = button.space = button.escape = false;
}

Input::Button Input::GetButton(void) const
{
	return button;
}

void Input::InputHandler(Event event, RenderWindow& window)
{
	if (event.type == Event::Closed)
	{
		window.close();
	}

	if (event.type == Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case Keyboard::Escape:
			button.escape = true;
			break;
		case Keyboard::Left:
			button.left = true;
			break;
		case Keyboard::Right:
			button.right = true;
			break;
		case Keyboard::Down:
			button.down = true;
			break;
		case Keyboard::Up:
			button.up = true;
			break;
		case Keyboard::Space:
			button.space = true;
			break;
		default:
			break;
		}
	}

	if (event.type == Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case Keyboard::Escape:
			button.escape = false;
			break;
		case Keyboard::Left:
			button.left = false;
			break;
		case Keyboard::Right:
			button.right = false;
			break;
		case Keyboard::Down:
			button.down = false;
			break;
		case Keyboard::Up:
			button.up = false;
			break;
		case Keyboard::Space:
			button.space = false;
			break;
		default:
			break;
		}
	}
}

//main.cpp

#include "main.h"

RenderWindow window;
Input input;
Font font;
Text score;
Text finalscore;
Text gameover;
Texture dino_left;
Texture dino_right;
Texture spl_cactus;
Texture dbl_cactus;
Texture tpl_cactus;
Texture gd_cactus;
Texture clouds;
Texture ground;

bool endswitch = false;

float posxclouds = 0.f;
float posxground = 0.f;

float posxdino = 40.f ;
float posydino = 410.f ;
float dino_ph = 5.f;
float dino_hitbox_Height = 250;
float dino_hitbox_Width = 160;
bool apex = false;
bool strt = false;

float posxobstacle = 1500.f;
float posxtpl = 2500.f;
float posxdbl = 7100.f;
float posxspl = 13000.f;
float grd_speed = 15.f;
float cld_speed = 1.f;

int scoreJ1 = 0;


void affich_score()
{
	if (endswitch == false)
	{
		scoreJ1 += 1;
		if (scoreJ1 % 5 == 0)
		{
			SetText(score, "SCORE : " + to_string(scoreJ1), false, 40, (WIN_WIDTH)-600, 140);
		}
	}
}

void jumpmech()
{
	if (((input.GetButton().space == true) && (posydino > 400)) || (strt == true))
	{
		posydino -= 25.0f + dino_ph;
		dino_ph -= 1.5f;
		strt = true;
		if (posydino < 100)
		{
			strt = false;
			apex = true;
			dino_ph = 5.0f;
		}
	}
	if ((strt == false) && (apex == true))
	{
		posydino += 0.0005f + dino_ph;
		dino_ph += 0.5f;
		if (posydino > 410)
		{
			apex = false;
			dino_ph = 5.0f;
		}
	}
}


void screenslide()
{
	if (endswitch == false)
	{
		posxobstacle -= grd_speed;
		posxtpl -= grd_speed;
		posxdbl -= grd_speed;
		posxspl -= grd_speed;
		posxground -= grd_speed;
		posxclouds -= (grd_speed / 5);
		grd_speed += 0.005f;
		if (posxobstacle < -200)
		{
			posxobstacle = WIN_WIDTH;
		}
		if (posxtpl < -300)
		{
			posxtpl = (2*WIN_WIDTH) + 1500;
		}
		if (posxdbl < -800)
		{
			posxdbl = (3 * WIN_WIDTH) + 100;
		}
		if (posxspl < -500)
		{
			posxspl = (3 * WIN_WIDTH) + 2300;
		}
		if (posxclouds < -1545)
		{
			posxclouds = 0.f;
		}
		if (posxground < -2865)
		{
			posxground = 0.f;
		}
	}
}


void collision()
{
	if ( ( ((posxdino + 35) < (posxobstacle + (dino_hitbox_Width*0.7))) &&
		(((posxdino + 35) + (dino_hitbox_Width)) > (posxobstacle)) )
		&& (((posydino + dino_hitbox_Height) > (475))) )
	{
		endswitch = true;
	}
	if ((((posxdino + 35) < (posxtpl + (dino_hitbox_Width))) &&
		(((posxdino + 35) + (dino_hitbox_Width)) > (posxtpl)))
		&& (((posydino + dino_hitbox_Height) > (525))))
	{
		endswitch = true;
	}
	if ((((posxdino + 35) < (posxdbl + (dino_hitbox_Width*0.7))) &&
		(((posxdino + 35) + (dino_hitbox_Width)) > (posxdbl)))
		&& (((posydino + dino_hitbox_Height) > (525))))
	{
		endswitch = true;
	}
	if ((((posxdino + 35) < (posxspl + (dino_hitbox_Width/3))) &&
		(((posxdino + 35) + (dino_hitbox_Width)) > (posxspl)))
		&& (((posydino + dino_hitbox_Height) > (525))))
	{
		endswitch = true;
	}
}

void endscreen()
{
	if (endswitch == true)
	{
		SetText(finalscore, "SCORE : " + to_string(scoreJ1), false, 58, (WIN_WIDTH / 2) - 300, (WIN_HEIGHT / 2) - 200);
		SetText(gameover, "GAME OVER", true, 100, (WIN_WIDTH / 2), (WIN_HEIGHT / 2) - 120);
	}
}


int main()
{
	window.create(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Pong SFML C++", Style::Default);
	window.setVerticalSyncEnabled(true);
	font.loadFromFile("res/nipporeg.otf");
	dino_left.loadFromFile("res/dino-step1.png");
	dino_right.loadFromFile("res/dino-step2.png");
	clouds.loadFromFile("res/clouds-textureuncut.png");
	ground.loadFromFile("res/sol-desert.png");
	spl_cactus.loadFromFile("res/spl-cactus-pixel.png");
	dbl_cactus.loadFromFile("res/dbl-cactus-pixel.png");
	tpl_cactus.loadFromFile("res/tpl-cactus-pixel.png");
	gd_cactus.loadFromFile("res/gd-cactus-pixel.png");

	Sprite ground_sprite;
	ground_sprite.setTexture(ground);
	ground_sprite.setTextureRect(IntRect(0, 0, 5000, 300));
	ground_sprite.setPosition(0, 650);

	Sprite clouds_sprite;
	clouds_sprite.setTexture(clouds);
	clouds_sprite.setTextureRect(IntRect(0, 0, 5000, 150));
	clouds_sprite.setPosition(0, 0);

	Sprite dino_sprite_left;
	dino_sprite_left.setTexture(dino_left);
	dino_sprite_left.setTextureRect(IntRect(0, 0, 48, 50));
	dino_sprite_left.setColor(Color::White);
	dino_sprite_left.setPosition(posxdino, posydino - 10.f);
	Vector2f scale_left = dino_sprite_left.getScale();
	dino_sprite_left.setScale(scale_left.x *5 , scale_left.y *5 );

	Sprite dino_sprite_right;
	dino_sprite_right.setTexture(dino_right);
	dino_sprite_right.setTextureRect(IntRect(0, 0, 48, 50));
	dino_sprite_right.setColor(Color::White);
	dino_sprite_right.setPosition(posxdino, posydino - 10.f);
	Vector2f scale_right = dino_sprite_right.getScale();
	dino_sprite_right.setScale(scale_right.x * 5, scale_right.y * 5);

	RectangleShape dino_Hitbox(Vector2f(dino_hitbox_Width, dino_hitbox_Height));
	dino_Hitbox.setFillColor(Color(0,0,155, 35));
	dino_Hitbox.setPosition(posxdino + 35, posydino);

	RectangleShape spl_cactus_hit(Vector2f(dino_hitbox_Width/3, dino_hitbox_Height/2));
	spl_cactus_hit.setFillColor(Color(0, 0, 155, 100));
	spl_cactus_hit.setPosition(1200, 525);

	Sprite spl_cactus_sprite;
	spl_cactus_sprite.setTexture(spl_cactus);
	spl_cactus_sprite.setTextureRect(IntRect(0, 0, 9, 20));
	spl_cactus_sprite.setColor(Color::White);
	spl_cactus_sprite.setPosition(1200, 525);
	Vector2f spl_scale = spl_cactus_sprite.getScale();
	spl_cactus_sprite.setScale(spl_scale.x * 5.8, spl_scale.y * 6.3);

	RectangleShape dbl_cactus_hit(Vector2f(dino_hitbox_Width*0.7, dino_hitbox_Height/2));
	dbl_cactus_hit.setFillColor(Color(0, 0, 155, 100));
	dbl_cactus_hit.setPosition(1000, 525);

	Sprite dbl_cactus_sprite;
	dbl_cactus_sprite.setTexture(dbl_cactus);
	dbl_cactus_sprite.setTextureRect(IntRect(0, 0, 23, 20));
	dbl_cactus_sprite.setColor(Color::White);
	dbl_cactus_sprite.setPosition(1000, 525);
	Vector2f dbl_scale = dbl_cactus_sprite.getScale();
	dbl_cactus_sprite.setScale(dbl_scale.x * 4.85, dbl_scale.y * 6.3);

	RectangleShape tpl_cactus_hit(Vector2f(dino_hitbox_Width, dino_hitbox_Height/2));
	tpl_cactus_hit.setFillColor(Color(0, 0, 155, 100));
	tpl_cactus_hit.setPosition(600, 525);

	Sprite tpl_cactus_sprite;
	tpl_cactus_sprite.setTexture(tpl_cactus);
	tpl_cactus_sprite.setTextureRect(IntRect(0, 0, 41, 22));
	tpl_cactus_sprite.setColor(Color::White);
	tpl_cactus_sprite.setPosition(600, 525);
	Vector2f tpl_scale = tpl_cactus_sprite.getScale();
	tpl_cactus_sprite.setScale(tpl_scale.x * 3.9, tpl_scale.y * 5.75);

	RectangleShape gd_cactus_hit(Vector2f(dino_hitbox_Width*0.7, dino_hitbox_Height*0.7));
	gd_cactus_hit.setFillColor(Color(0, 0, 155, 100));
	gd_cactus_hit.setPosition(400, 475);

	Sprite gd_cactus_sprite;
	gd_cactus_sprite.setTexture(gd_cactus);
	gd_cactus_sprite.setTextureRect(IntRect(0, 0, 25, 35));
	gd_cactus_sprite.setColor(Color::White);
	gd_cactus_sprite.setPosition(400, 475);
	Vector2f gd_scale = gd_cactus_sprite.getScale();
	gd_cactus_sprite.setScale(gd_scale.x * 4.5, gd_scale.y * 5);



	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			input.InputHandler(event, window);
		}

		CheckBtn();
		affich_score();
		jumpmech();
		screenslide();
		collision();
		endscreen();

		clouds_sprite.setPosition(posxclouds, 0);
		ground_sprite.setPosition(posxground, 650);
		dino_sprite_left.setPosition(posxdino , posydino - 10);
		dino_sprite_right.setPosition(posxdino, posydino - 10);
		dino_Hitbox.setPosition(posxdino + 35, posydino);
		spl_cactus_hit.setPosition(posxspl, 525);
		spl_cactus_sprite.setPosition(posxspl, 525);
		dbl_cactus_hit.setPosition(posxdbl, 525);
		dbl_cactus_sprite.setPosition(posxdbl, 525);
		tpl_cactus_hit.setPosition(posxtpl, 525);
		tpl_cactus_sprite.setPosition(posxtpl, 525);
		gd_cactus_hit.setPosition(posxobstacle, 475);
		gd_cactus_sprite.setPosition(posxobstacle, 475);


		window.clear(Color(196, 238, 255));

		window.draw(clouds_sprite);
		window.draw(dino_sprite_left);
		if (posydino > 275)
		{
			if ((scoreJ1 % 20) < 10)
			{
				window.draw(dino_sprite_right);
			}
		}
		//window.draw(dino_Hitbox);
		window.draw(spl_cactus_sprite);
		//window.draw(spl_cactus_hit);
		window.draw(dbl_cactus_sprite);
		//window.draw(dbl_cactus_hit);
		window.draw(tpl_cactus_sprite);
		//window.draw(tpl_cactus_hit);
		window.draw(gd_cactus_sprite);
		//window.draw(gd_cactus_hit);
		window.draw(ground_sprite);
		if (endswitch == false)
		{
			window.draw(score);
		}
		window.draw(finalscore);
		window.draw(gameover);

		window.display();
	}

	return 0;
}

void SetText(Text& txt, String str, bool bold, int size, int posx, int posy)
{
	txt.setFont(font);
	txt.setString(str);
	if (bold == true)
	{
		txt.setOutlineColor(Color(100, 100, 100));
		txt.setOutlineThickness(3);
	}
	txt.setCharacterSize(size);
	txt.setFillColor(Color(100,100,100));
	txt.setPosition(posx, posy);
}

void CheckBtn()
{

	if (input.GetButton().escape == true)
	{
		window.close();
	}
}
