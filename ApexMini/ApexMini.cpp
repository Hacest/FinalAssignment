#include <iostream>
#include <bangtal.h>
#include <ctime>

using namespace bangtal;
using namespace std;

//character size (scaled 0.5) = 50 x 100

int main()
{
	SoundPtr bgm = Sound::create("Images/bgm2.mp3");
	bgm->play();

	srand((unsigned)time(0));

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	auto timer = Timer::create(0.1);

	time_t start_time;
	timer->start();
	start_time = time(NULL);

	//--------------------------------------------------------------------------------character select---------------------------------------------------------

	int character = 0; // if select == 3 click finish button
	int l = 0; // if l == 0 can click
	int w = 0;
	int g = 0;
	int m = 0;
	int c = 0;
	int character1 = 0; // if character1 == 1, character1 is lifeline
	int character2 = 0;
	int character3 = 0;

	auto select = Scene::create("캐릭터 선택", "Images/White.png");
	auto scene1 = Scene::create("Level1", "Images/Background.png");
	auto win = Scene::create("Victory", "Images/win.png");
	auto gameOver = Scene::create("Game Over", "Images/gameOver.png");

	auto Lifeline_Character = Object::create("Images/Lifeline.png", select, 200, 350);// l 1
	Lifeline_Character->setScale(0.5);
	Lifeline_Character->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (character == 0 && l == 0)
			{
				character = character + 1;
				Lifeline_Character->setScale(1.0);
				l = 1;
				character1 = 1;
			}
			else if (character == 1 && l == 0)
			{
				character = character + 1;
				Lifeline_Character->setScale(1.0);
				l = 1;
				character2 = 1;
			}
			else if (character == 2 && l == 0)
			{
				character = character + 1;
				Lifeline_Character->setScale(1.0);
				l = 1;
				character3 = 1;
			}
			return 0;
		});

	auto Wraith_Character = Object::create("Images/Wraith.png", select, 400, 350);// w 2
	Wraith_Character->setScale(0.5);
	Wraith_Character->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (character == 0 && w == 0)
			{
				character = character + 1;
				Wraith_Character->setScale(1.0);
				w = 1;
				character1 = 2;
			}
			else if (character == 1 && w == 0)
			{
				character = character + 1;
				Wraith_Character->setScale(1.0);
				w = 1;
				character2 = 2;
			}
			else if (character == 2 && w == 0)
			{
				character = character + 1;
				Wraith_Character->setScale(1.0);
				w = 1;
				character3 = 2;
			}
			return 0;
		});

	auto Gibraltar_Character = Object::create("Images/Gibraltar.png", select, 600, 350);// g 3
	Gibraltar_Character->setScale(0.5);
	Gibraltar_Character->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (character == 0 && g == 0)
			{
				character = character + 1;
				Gibraltar_Character->setScale(1.0);
				g = 1;
				character1 = 3;
			}
			else if (character == 1 && g == 0)
			{
				character = character + 1;
				Gibraltar_Character->setScale(1.0);
				g = 1;
				character2 = 3;
			}
			else if (character == 2 && g == 0)
			{
				character = character + 1;
				Gibraltar_Character->setScale(1.0);
				g = 1;
				character3 = 3;
			}
			return 0;
		});

	auto Mirage_Character = Object::create("Images/Mirage.png", select, 800, 350); // m 4
	Mirage_Character->setScale(0.5);
	Mirage_Character->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (character == 0 && m == 0)
			{
				character = character + 1;
				Mirage_Character->setScale(1.0);
				m = 1;
				character1 = 4;
			}
			else if (character == 1 && m == 0)
			{
				character = character + 1;
				Mirage_Character->setScale(1.0);
				m = 1;
				character2 = 4;
			}
			else if (character == 2 && m == 0)
			{
				character = character + 1;
				Mirage_Character->setScale(1.0);
				m = 1;
				character3 = 4;
			}
			return 0;
		});

	auto Caustic_Character = Object::create("Images/Caustic.png", select, 1000, 350); // c 5
	Caustic_Character->setScale(0.5);
	Caustic_Character->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (character == 0 && c == 0)
			{
				character = character + 1;
				Caustic_Character->setScale(1.0);
				c = 1;
				character1 = 5;
			}
			else if (character == 1 && c == 0)
			{
				character = character + 1;
				Caustic_Character->setScale(1.0);
				c = 1;
				character2 = 5;
			}
			else if (character == 2 && c == 0)
			{
				character = character + 1;
				Caustic_Character->setScale(1.0);
				c = 1;
				character3 = 5;
			}
			return 0;
		});

	auto Finish_Character = Object::create("Images/finish.png", select, 525, 50);
	Finish_Character->setScale(0.5);
	Finish_Character->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (character == 3)
			{
				scene1->enter();
				showMessage("캐릭터들을 한번씩 클릭해주세요!");
			}
			return 0;
		});
	//----------------------------------------------------------------------Level 1----------------------------------------------------------------------
	int turn = -1; // turn = -1 means pre-game, turn = 0 means player's turn, turn = 1 means computer's turn
	int click = 0; // click++ for each character clicked
	int overCount = 0; // overCount++ whenever a character dies, overCount == 3 is game over
	int winCount = 0; // winCount++ whenever a bot dies, winCount == 3 is 1등급

	int portalCount = 0; // portalCount++ when portal is created by Wraith
	int portalX, portalY;
	int portal2X, portal2Y;

	int shieldX, shieldY;

	int clone1X, clone1Y, clone2X, clone2Y;

	int gasX, gasY;
	int gasTimer = 0;

	int LifelineClick = 0; //pre-game, LifelineClick = 0 means Lifeline was not clicked. 
	int WraithClick = 0;
	int GibraltarClick = 0;
	int MirageClick = 0;
	int CausticClick = 0;

	int LifelineTurn = 2; // LifelineTurn = 2 means Lifeline can move/use skills, LifelineTurn = 0 means Lifeline cannot move (each move costs 1)
	int WraithTurn = 2;
	int GibraltarTurn = 2;
	int MirageTurn = 2;
	int CausticTurn = 2;

	int LifelineSelect = 0; // LifelineSelect = 0 means Lifeline is not selected, LifelineSelect = 1 means Lifeline is selected
	int WraithSelect = 0;
	int GibraltarSelect = 0;
	int MirageSelect = 0;
	int CausticSelect = 0;

	int LifelineX, LifelineY; // X Y coordinates for characters
	int WraithX, WraithY;
	int GibraltarX, GibraltarY;
	int MirageX, MirageY;
	int CausticX, CausticY;
	int Bot1X, Bot1Y, Bot2X, Bot2Y, Bot3X, Bot3Y;
	int goalX, goalY;

	int Bot1Life, Bot2Life, Bot3Life = 1; // BotLife =1 means alive, 0 means dead and cannot move (locate 2000,2000)

	//control key setting
	auto up = Object::create("Images/up.png", scene1, 0, 570);
	up->setScale(0.15);
	auto down = Object::create("Images/down.png", scene1, 0, 500);
	down->setScale(0.15);
	auto right = Object::create("Images/right.png", scene1, 0, 430);
	right->setScale(0.15);
	auto left = Object::create("Images/left.png", scene1, 0, 360);
	left->setScale(0.15);
	auto finish = Object::create("Images/finish.png", scene1, 560, 0);
	finish->setScale(0.25);
	auto skill = Object::create("Images/Skill.png", scene1, 10, 290); 
	skill->setScale(0.2);

	//bot setting
	auto Bot1 = Object::create("Images/Bot.png", scene1, 1100, 420);
	Bot1->setScale(0.5);
	Bot1X = 1100;
	Bot1Y = 420;
	auto Bot2 = Object::create("Images/Bot.png", scene1, 1050, 320);
	Bot2->setScale(0.5);
	Bot2X = 1050;
	Bot2Y = 320;
	auto Bot3 = Object::create("Images/Bot.png", scene1, 1100, 220);
	Bot3->setScale(0.5);
	Bot3X = 1100;
	Bot3Y = 220;

	//skill setting
	auto portal = Object::create("Images/portal.png", scene1, 0, 0);
	portal->setScale(0.2);
	portal->hide();
	auto portal2 = Object::create("Images/portal.png", scene1, 0, 0);
	portal2->setScale(0.2);
	portal2->hide();

	auto shieldU = Object::create("Images/shieldU.png", scene1, 0, 0);
	shieldU->setScale(0.1);
	shieldU->hide();
	auto shieldR = Object::create("Images/shieldR.png", scene1, 0, 0);
	shieldR->setScale(0.1);
	shieldR->hide();
	auto shieldD = Object::create("Images/shieldD.png", scene1, 0, 0);
	shieldD->setScale(0.1);
	shieldD->hide();
	auto shieldL = Object::create("Images/shieldL.png", scene1, 0, 0);
	shieldL->setScale(0.1);
	shieldL->hide();

	auto clone1 = Object::create("Images/Mirage.png", scene1, 0, 0);
	clone1->setScale(0.5);
	clone1->hide();
	auto clone2 = Object::create("Images/Mirage.png", scene1, 0, 0);
	clone2->setScale(0.5);
	clone2->hide();

	auto gas = Object::create("Images/gas.png", scene1, 0, 0);
	gas->setScale(0.2);
	gas->hide();

	auto goal = Object::create("Images/goal.png", scene1, 1110, 320);
	goal->setScale(0.4);
	goalX = 1100;
	goalY = 300;



	auto Lifeline = Object::create("Images/Lifeline.png", scene1, 100, 520);
	Lifeline->setScale(0.5);
	Lifeline->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (character1 == 1 && turn == -1 && LifelineClick == 0)
			{
				Lifeline->locate(scene1, 100, 420);
				click++;
				LifelineX = 100;
				LifelineY = 420;
				LifelineClick++;
			}
			else if (character2 == 1 && turn == -1 && LifelineClick == 0)
			{
				Lifeline->locate(scene1, 100, 320);
				click++;
				LifelineX = 100;
				LifelineY = 320;
				LifelineClick++;
			}
			else if (character3 == 1 && turn == -1 && LifelineClick == 0)
			{
				Lifeline->locate(scene1, 100, 220);
				click++;
				LifelineX = 100;
				LifelineY = 220;
				LifelineClick++;
			}
			else if (character1 != 1 && character2 != 1 && character3 != 1 && turn == -1 && LifelineClick == 0)
			{
				Lifeline->hide();
				click++;
				LifelineClick++;
			}

			if (turn == 0 && LifelineTurn > 0)
			{
				Lifeline->setScale(0.8);
				showMessage("라이프라인으로 무엇을 할까요?");
				LifelineSelect = 1;
			}

			return 0;
		});
	
	auto Wraith = Object::create("Images/Wraith.png", scene1, 100, 420);
	Wraith->setScale(0.5);
	Wraith->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (character1 == 2 && turn == -1 && WraithClick == 0)
			{
				Wraith->locate(scene1, 100, 420);
				click++;
				WraithX = 100;
				WraithY = 420;
				WraithClick++;
			}
			else if (character2 == 2 && turn == -1 && WraithClick == 0)
			{
				Wraith->locate(scene1, 100, 320);
				click++;
				WraithX = 100;
				WraithY = 320;
				WraithClick++;
			}
			else if (character3 == 2 && turn == -1 && WraithClick == 0)
			{
				Wraith->locate(scene1, 100, 220);
				click++;
				WraithX = 100;
				WraithY = 220;
				WraithClick++;
			}
			else if (character1 != 2 && character2 != 2 && character3 != 2 && turn == -1 && WraithClick == 0)
			{
				Wraith->hide();
				click++;
				WraithClick++;
			}

			if (turn == 0 && WraithTurn > 0)
			{
				Wraith->setScale(0.8);
				showMessage("레이스로 무엇을 할까요?");
				WraithSelect = 1;
			}
			return 0;
		});

	auto Gibraltar = Object::create("Images/Gibraltar.png", scene1, 100, 320);
	Gibraltar->setScale(0.5);
	Gibraltar->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (character1 == 3 && turn == -1 && GibraltarClick == 0)
			{
				Gibraltar->locate(scene1, 100, 420);
				click++;
				GibraltarX = 100;
				GibraltarY = 420;
				GibraltarClick++;
			}
			else if (character2 == 3 && turn == -1 && GibraltarClick == 0)
			{
				Gibraltar->locate(scene1, 100, 320);
				click++;
				GibraltarX = 100;
				GibraltarY = 320;
				GibraltarClick++;
			}
			else if (character3 == 3 && turn == -1 && GibraltarClick == 0)
			{
				Gibraltar->locate(scene1, 100, 220);
				click++;
				GibraltarX = 100;
				GibraltarY = 220;
				GibraltarClick++;
			}
			else if (character1 != 3 && character2 != 3 && character3 != 3 && turn == -1 && GibraltarClick == 0)
			{
				Gibraltar->hide();
				click++;
				GibraltarClick++;
			}

			if (turn == 0 && GibraltarTurn > 0)
			{
				Gibraltar->setScale(0.8);
				showMessage("지브롤터로 무엇을 할까요?");
				GibraltarSelect = 1;
			}
			return 0;
		});

	auto Mirage = Object::create("Images/Mirage.png", scene1, 100, 220);
	Mirage->setScale(0.5);
	Mirage->setScale(0.5);
	Mirage->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (character1 == 4 && turn == -1 && MirageClick == 0)
			{
				Mirage->locate(scene1, 100, 420);
				click++;
				MirageX = 100;
				MirageY = 420;
				MirageClick++;
			}
			else if (character2 == 4 && turn == -1 && MirageClick == 0)
			{
				Mirage->locate(scene1, 100, 320);
				click++;
				MirageX = 100;
				MirageY = 320;
				MirageClick++;
			}
			else if (character3 == 4 && turn == -1 && MirageClick == 0)
			{
				Mirage->locate(scene1, 100, 220);
				click++;
				MirageX = 100;
				MirageY = 220;
				MirageClick++;
			}
			else if (character1 != 4 && character2 != 4 && character3 != 4 && turn == -1 && MirageClick == 0)
			{
				Mirage->hide();
				click++;
				MirageClick++;
			}

			if (turn == 0 && MirageTurn > 0)
			{
				Mirage->setScale(0.8);
				showMessage("미라지로 무엇을 할까요?");
				MirageSelect = 1;
			}
			return 0;
		});
	
	auto Caustic = Object::create("Images/Caustic.png", scene1, 100, 120);
	Caustic->setScale(0.5);
	Caustic->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (character1 == 5 && turn == -1 && CausticClick == 0)
			{
				Caustic->locate(scene1, 100, 420);
				click++;
				CausticX = 100;
				CausticY = 420;
				CausticClick++;
			}
			else if (character2 == 5 && turn == -1 && CausticClick == 0)
			{
				Caustic->locate(scene1, 100, 320);
				click++;
				CausticX = 100;
				CausticY = 320;
				CausticClick++;
			}
			else if (character3 == 5 && turn == -1 && CausticClick == 0)
			{
				Caustic->locate(scene1, 100, 220);
				click++;
				CausticX = 100;
				CausticY = 220;
				CausticClick++;
			}
			else if (character1 != 5 && character2 != 5 && character3 != 5 && turn == -1 && CausticClick == 0)
			{
				Caustic->hide();
				click++;
				CausticClick++;
			}

			if (turn == 0 && CausticTurn > 0)
			{
				Caustic->setScale(0.8);
				showMessage("코스틱으로 무엇을 할까요?");
				CausticSelect = 1;
			}
			return 0;
		});

	//--------------------------------------------------------------------------controls--------------------------------------------------------------------
	
	finish->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (turn == -1 && click == 5)
			{
				turn++;
				showMessage("Game start!");
			}
			else if (turn == 0)
			{
				showMessage("몬스터가 움직입니다");
				//Remove bots when they die
				if (Bot1Life == 0)
					Bot1->locate(select, 0, 0);
				if (Bot2Life == 0)
					Bot2->locate(select, 0, 0);
				if (Bot3Life == 0)
					Bot3->locate(select, 0, 0);
				switch (rand() % 4)
				{
				//Bot1 movement
				case 0:
					if (Bot1Y < 600)
					Bot1Y = Bot1Y + 100;
					Bot1->locate(scene1, Bot1X, Bot1Y);
					if (Bot1X >= LifelineX - 10 && Bot1X <= LifelineX + 10 && Bot1Y >= LifelineY - 10 && Bot1Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= WraithX - 10 && Bot1X <= WraithX + 10 && Bot1Y >= WraithY - 10 && Bot1Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= GibraltarX - 10 && Bot1X <= GibraltarX + 10 && Bot1Y >= GibraltarY - 10 && Bot1Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= MirageX - 10 && Bot1X <= MirageX + 10 && Bot1Y >= MirageY - 10 && Bot1Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= CausticX - 10 && Bot1X <= CausticX + 10 && Bot1Y >= CausticY - 10 && Bot1Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;

				case 1:
					if (Bot1Y > 100)
					Bot1Y = Bot1Y - 100;
					Bot1->locate(scene1, Bot1X, Bot1Y);
					if (Bot1X >= LifelineX - 10 && Bot1X <= LifelineX + 10 && Bot1Y >= LifelineY - 10 && Bot1Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= WraithX - 10 && Bot1X <= WraithX + 10 && Bot1Y >= WraithY - 10 && Bot1Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= GibraltarX - 10 && Bot1X <= GibraltarX + 10 && Bot1Y >= GibraltarY - 10 && Bot1Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= MirageX - 10 && Bot1X <= MirageX + 10 && Bot1Y >= MirageY - 10 && Bot1Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= CausticX - 10 && Bot1X <= CausticX + 10 && Bot1Y >= CausticY - 10 && Bot1Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;
				case 2:
					if (Bot1X > 100)
					Bot1X = Bot1X - 50;
					Bot1->locate(scene1, Bot1X, Bot1Y);
					if (Bot1X >= LifelineX - 10 && Bot1X <= LifelineX + 10 && Bot1Y >= LifelineY - 10 && Bot1Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= WraithX - 10 && Bot1X <= WraithX + 10 && Bot1Y >= WraithY - 10 && Bot1Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= GibraltarX - 10 && Bot1X <= GibraltarX + 10 && Bot1Y >= GibraltarY - 10 && Bot1Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= MirageX - 10 && Bot1X <= MirageX + 10 && Bot1Y >= MirageY - 10 && Bot1Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= CausticX - 10 && Bot1X <= CausticX + 10 && Bot1Y >= CausticY - 10 && Bot1Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;
				case 3:
					if (Bot1X < 1100)
					Bot1X = Bot1X + 50;
					Bot1->locate(scene1, Bot1X, Bot1Y);
					if(Bot1X >= LifelineX - 10 && Bot1X <= LifelineX + 10 && Bot1Y >= LifelineY - 10 && Bot1Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					
					if (Bot1X >= WraithX - 10 && Bot1X <= WraithX + 10 && Bot1Y >= WraithY - 10 && Bot1Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= GibraltarX - 10 && Bot1X <= GibraltarX + 10 && Bot1Y >= GibraltarY - 10 && Bot1Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= MirageX - 10 && Bot1X <= MirageX + 10 && Bot1Y >= MirageY - 10 && Bot1Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot1X >= CausticX - 10 && Bot1X <= CausticX + 10 && Bot1Y >= CausticY - 10 && Bot1Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;
				}

				switch (rand() % 4)
				{
				case 0:
					if (Bot2Y < 600)
						Bot2Y = Bot2Y + 100;
					Bot2->locate(scene1, Bot2X, Bot2Y);
					if (Bot2X >= LifelineX - 10 && Bot2X <= LifelineX + 10 && Bot2Y >= LifelineY - 10 && Bot2Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= WraithX - 10 && Bot2X <= WraithX + 10 && Bot2Y >= WraithY - 10 && Bot2Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= GibraltarX - 10 && Bot2X <= GibraltarX + 10 && Bot2Y >= GibraltarY - 10 && Bot2Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= MirageX - 10 && Bot2X <= MirageX + 10 && Bot2Y >= MirageY - 10 && Bot2Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= CausticX - 10 && Bot2X <= CausticX + 10 && Bot2Y >= CausticY - 10 && Bot2Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;
				case 1:
					if (Bot2Y > 100)
						Bot2Y = Bot2Y - 100;
					Bot2->locate(scene1, Bot2X, Bot2Y);
					if (Bot2X >= LifelineX - 10 && Bot2X <= LifelineX + 10 && Bot2Y >= LifelineY - 10 && Bot2Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= WraithX - 10 && Bot2X <= WraithX + 10 && Bot2Y >= WraithY - 10 && Bot2Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= GibraltarX - 10 && Bot2X <= GibraltarX + 10 && Bot2Y >= GibraltarY - 10 && Bot2Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= MirageX - 10 && Bot2X <= MirageX + 10 && Bot2Y >= MirageY - 10 && Bot2Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= CausticX - 10 && Bot2X <= CausticX + 10 && Bot2Y >= CausticY - 10 && Bot2Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;
				case 2:
					if (Bot2X > 100)
						Bot2X = Bot2X - 50;
					Bot2->locate(scene1, Bot2X, Bot2Y);
					if (Bot2X >= LifelineX - 10 && Bot2X <= LifelineX + 10 && Bot2Y >= LifelineY - 10 && Bot2Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= WraithX - 10 && Bot2X <= WraithX + 10 && Bot2Y >= WraithY - 10 && Bot2Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= GibraltarX - 10 && Bot2X <= GibraltarX + 10 && Bot2Y >= GibraltarY - 10 && Bot2Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= MirageX - 10 && Bot2X <= MirageX + 10 && Bot2Y >= MirageY - 10 && Bot2Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= CausticX - 10 && Bot2X <= CausticX + 10 && Bot2Y >= CausticY - 10 && Bot2Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;
				case 3:
					if (Bot2X < 1100)
						Bot2X = Bot2X + 50;
						Bot2->locate(scene1, Bot2X, Bot2Y);
					if (Bot2X >= LifelineX - 10 && Bot2X <= LifelineX + 10 && Bot2Y >= LifelineY - 10 && Bot2Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= WraithX - 10 && Bot2X <= WraithX + 10 && Bot2Y >= WraithY - 10 && Bot2Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= GibraltarX - 10 && Bot2X <= GibraltarX + 10 && Bot2Y >= GibraltarY - 10 && Bot2Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= MirageX - 10 && Bot2X <= MirageX + 10 && Bot2Y >= MirageY - 10 && Bot2Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot2X >= CausticX - 10 && Bot2X <= CausticX + 10 && Bot2Y >= CausticY - 10 && Bot2Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;
				}

				switch (rand() % 4)
				{
				case 0:
					if (Bot3Y < 600)
						Bot3Y = Bot3Y + 100;
					Bot3->locate(scene1, Bot3X, Bot3Y);
					if (Bot3X >= LifelineX - 10 && Bot3X <= LifelineX + 10 && Bot3Y >= LifelineY - 10 && Bot3Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= WraithX - 10 && Bot3X <= WraithX + 10 && Bot3Y >= WraithY - 10 && Bot3Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= GibraltarX - 10 && Bot3X <= GibraltarX + 10 && Bot3Y >= GibraltarY - 10 && Bot3Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= MirageX - 10 && Bot3X <= MirageX + 10 && Bot3Y >= MirageY - 10 && Bot3Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= CausticX - 10 && Bot3X <= CausticX + 10 && Bot3Y >= CausticY - 10 && Bot3Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;
				case 1:
					if (Bot3Y > 100)
					Bot3Y = Bot3Y - 100;
					Bot3->locate(scene1, Bot3X, Bot3Y);
					if(Bot3X >= LifelineX - 10 && Bot3X <= LifelineX + 10 && Bot3Y >= LifelineY - 10 && Bot3Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= WraithX - 10 && Bot3X <= WraithX + 10 && Bot3Y >= WraithY - 10 && Bot3Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= GibraltarX - 10 && Bot3X <= GibraltarX + 10 && Bot3Y >= GibraltarY - 10 && Bot3Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= MirageX - 10 && Bot3X <= MirageX + 10 && Bot3Y >= MirageY - 10 && Bot3Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= CausticX - 10 && Bot3X <= CausticX + 10 && Bot3Y >= CausticY - 10 && Bot3Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;
				case 2:
					if (Bot3X > 100)
					Bot3X = Bot3X - 50;
					Bot3->locate(scene1, Bot3X, Bot3Y);
					if (Bot3X >= LifelineX - 10 && Bot3X <= LifelineX + 10 && Bot3Y >= LifelineY - 10 && Bot3Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= WraithX - 10 && Bot3X <= WraithX + 10 && Bot3Y >= WraithY - 10 && Bot3Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= GibraltarX - 10 && Bot3X <= GibraltarX + 10 && Bot3Y >= GibraltarY - 10 && Bot3Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= MirageX - 10 && Bot3X <= MirageX + 10 && Bot3Y >= MirageY - 10 && Bot3Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= CausticX - 10 && Bot3X <= CausticX + 10 && Bot3Y >= CausticY - 10 && Bot3Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;
				case 3:
					if (Bot3X < 1100)
					Bot3X = Bot3X + 50;
					Bot3->locate(scene1, Bot3X, Bot3Y);
					if (Bot3X >= LifelineX - 10 && Bot3X <= LifelineX + 10 && Bot3Y >= LifelineY - 10 && Bot3Y <= LifelineY + 10)
					{
						Lifeline->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= WraithX - 10 && Bot3X <= WraithX + 10 && Bot3Y >= WraithY - 10 && Bot3Y <= WraithY + 10)
					{
						Wraith->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= GibraltarX - 10 && Bot3X <= GibraltarX + 10 && Bot3Y >= GibraltarY - 10 && Bot3Y <= GibraltarY + 10)
					{
						Gibraltar->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= MirageX - 10 && Bot3X <= MirageX + 10 && Bot3Y >= MirageY - 10 && Bot3Y <= MirageY + 10)
					{
						Mirage->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					if (Bot3X >= CausticX - 10 && Bot3X <= CausticX + 10 && Bot3Y >= CausticY - 10 && Bot3Y <= CausticY + 10)
					{
						Caustic->hide();
						overCount++;
						if (overCount == 3)
							gameOver->enter();
					}
					break;
				}
				//Caustic's gas timer
				if (gasTimer == 1)
				{
					gas->hide();
					gasTimer = 0;
				}


				LifelineTurn = 2;
				WraithTurn = 2;
				GibraltarTurn = 2;
				MirageTurn = 2;
				CausticTurn = 2;

				Lifeline->setScale(0.5);
				Wraith->setScale(0.5);
				Gibraltar->setScale(0.5);
				Mirage->setScale(0.5);
				Caustic->setScale(0.5);
			}
			return 0;
		});

	up->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (turn == 0 && LifelineSelect == 1 && LifelineTurn >0 && LifelineY < 800)
			{
				LifelineY = LifelineY + 100;
				Lifeline->locate(scene1, LifelineX, LifelineY);
				Lifeline->setScale(0.5);
				LifelineTurn--;
				LifelineSelect--;
				if (LifelineX >= portalX - 50 && LifelineX <= portalX + 50 && LifelineY >= portalY - 50 && LifelineY <= portalY + 50)
				{
					Lifeline->locate(scene1, portal2X, portal2Y);
					LifelineX = portal2X;
					LifelineY = portal2Y;
				}

				if (LifelineX >= goalX - 50 && LifelineX <= goalX + 50 && LifelineY >= goalY - 50 && LifelineY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time)/((overCount +1)*10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && WraithSelect == 1 && WraithTurn > 0 && WraithY < 800)
			{
				WraithY = WraithY + 100;
				Wraith->locate(scene1, WraithX, WraithY);
				Wraith->setScale(0.5);
				WraithTurn--;
				WraithSelect--;
				/**if (WraithX >= portalX - 50 && WraithX <= portalX + 50 && WraithY >= portalY - 50 && WraithY <= portalY + 50)
				{
					Wraith->locate(scene1, portal2X, portal2Y);
				}**/

				if (WraithX >= goalX - 50 && WraithX <= goalX + 50 && WraithY >= goalY - 50 && WraithY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && GibraltarSelect == 1 && GibraltarTurn > 0 && GibraltarY < 800)
			{
				GibraltarY = GibraltarY + 100;
				Gibraltar->locate(scene1, GibraltarX, GibraltarY);
				Gibraltar->setScale(0.5);
				GibraltarTurn--;
				GibraltarSelect--;
				if (GibraltarX >= portalX - 50 && GibraltarX <= portalX + 50 && GibraltarY >= portalY - 50 && GibraltarY <= portalY + 50)
				{
					Gibraltar->locate(scene1, portal2X, portal2Y);
					GibraltarX = portal2X;
					GibraltarY = portal2Y;
				}

				if (GibraltarX >= goalX - 50 && GibraltarX <= goalX + 50 && GibraltarY >= goalY - 50 && GibraltarY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && MirageSelect == 1 && MirageTurn > 0 && MirageY < 800)
			{
				MirageY = MirageY + 100;
				Mirage->locate(scene1, MirageX, MirageY);
				Mirage->setScale(0.5);
				MirageTurn--;
				MirageSelect--;
				if (MirageX >= portalX - 50 && MirageX <= portalX + 50 && MirageY >= portalY - 50 && MirageY <= portalY + 50)
				{
					Mirage->locate(scene1, portal2X, portal2Y);
					MirageX = portal2X;
					MirageY = portal2Y;
				}

				if (MirageX >= goalX - 50 && MirageX <= goalX + 50 && MirageY >= goalY - 50 && MirageY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && CausticSelect == 1 && CausticTurn > 0 && CausticY < 800)
			{
				CausticY = CausticY + 100;
				Caustic->locate(scene1, CausticX, CausticY);
				Caustic->setScale(0.5);
				CausticTurn--;
				CausticSelect--;
				if (CausticX >= portalX - 50 && CausticX <= portalX + 50 && CausticY >= portalY - 50 && CausticY <= portalY + 50)
				{
					Caustic->locate(scene1, portal2X, portal2Y);
					CausticX = portal2X;
					CausticY = portal2Y;
				}

				if (CausticX >= goalX - 50 && CausticX <= goalX + 50 && CausticY >= goalY - 50 && CausticY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			return 0;
		});

	down->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (turn == 0 && LifelineSelect == 1 && LifelineTurn > 0 && LifelineY >100)
			{
				LifelineY = LifelineY - 100;
				Lifeline->locate(scene1, LifelineX, LifelineY);
				Lifeline->setScale(0.5);
				LifelineTurn--;
				LifelineSelect--;
				if (LifelineX >= portalX - 50 && LifelineX <= portalX + 50 && LifelineY >= portalY - 50 && LifelineY <= portalY + 50)
				{
					Lifeline->locate(scene1, portal2X, portal2Y);
					LifelineX = portal2X;
					LifelineY = portal2Y;
				}

				if (LifelineX >= goalX - 50 && LifelineX <= goalX + 50 && LifelineY >= goalY - 50 && LifelineY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && WraithSelect == 1 && WraithTurn > 0 && WraithY > 100)
			{
				WraithY = WraithY - 100;
				Wraith->locate(scene1, WraithX, WraithY);
				Wraith->setScale(0.5);
				WraithTurn--;
				WraithSelect--;
				/**if (WraithX >= portalX - 50 && WraithX <= portalX + 50 && WraithY >= portalY - 50 && WraithY <= portalY + 50)
				{
					Wraith->locate(scene1, portal2X, portal2Y);
				}**/

				if (WraithX >= goalX - 50 && WraithX <= goalX + 50 && WraithY >= goalY - 50 && WraithY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && GibraltarSelect == 1 && GibraltarTurn > 0 && GibraltarY > 100)
			{
				GibraltarY = GibraltarY - 100;
				Gibraltar->locate(scene1, GibraltarX, GibraltarY);
				Gibraltar->setScale(0.5);
				GibraltarTurn--;
				GibraltarSelect--;
				if (GibraltarX >= portalX - 50 && GibraltarX <= portalX + 50 && GibraltarY >= portalY - 50 && GibraltarY <= portalY + 50)
				{
					Gibraltar->locate(scene1, portal2X, portal2Y);
					GibraltarX = portal2X;
					GibraltarY = portal2Y;
				}

				if (GibraltarX >= goalX - 50 && GibraltarX <= goalX + 50 && GibraltarY >= goalY - 50 && GibraltarY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && MirageSelect == 1 && MirageTurn > 0 && MirageY > 100)
			{
				MirageY = MirageY - 100;
				Mirage->locate(scene1, MirageX, MirageY);
				Mirage->setScale(0.5);
				MirageTurn--;
				MirageSelect--;
				if (MirageX >= portalX - 50 && MirageX <= portalX + 50 && MirageY >= portalY - 50 && MirageY <= portalY + 50)
				{
					Mirage->locate(scene1, portal2X, portal2Y);
					MirageX = portal2X;
					MirageY = portal2Y;
				}

				if (MirageX >= goalX - 50 && MirageX <= goalX + 50 && MirageY >= goalY - 50 && MirageY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && CausticSelect == 1 && CausticTurn > 0 && CausticY > 100)
			{
				CausticY = CausticY - 100;
				Caustic->locate(scene1, CausticX, CausticY);
				Caustic->setScale(0.5);
				CausticTurn--;
				CausticSelect--;
				if (CausticX >= portalX - 50 && CausticX <= portalX + 50 && CausticY >= portalY - 50 && CausticY <= portalY + 50)
				{
					Caustic->locate(scene1, portal2X, portal2Y);
					CausticX = portal2X;
					CausticY = portal2Y;
				}

				if (CausticX >= goalX - 50 && CausticX <= goalX + 50 && CausticY >= goalY - 50 && CausticY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			return 0;
		});

	right->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (turn == 0 && LifelineSelect == 1 && LifelineTurn > 0 && LifelineX < 1100)
			{
				LifelineX = LifelineX + 50;
				Lifeline->locate(scene1, LifelineX, LifelineY);
				Lifeline->setScale(0.5);
				LifelineTurn--;
				LifelineSelect--;
				if (LifelineX >= portalX - 50 && LifelineX <= portalX + 50 && LifelineY >= portalY - 50 && LifelineY <= portalY + 50)
				{
					Lifeline->locate(scene1, portal2X, portal2Y);
					LifelineX = portal2X;
					LifelineY = portal2Y;
				}

				if (LifelineX >= goalX - 50 && LifelineX <= goalX + 50 && LifelineY >= goalY - 50 && LifelineY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && WraithSelect == 1 && WraithTurn > 0 && WraithX < 1100)
			{
				WraithX = WraithX + 50;
				Wraith->locate(scene1, WraithX, WraithY);
				Wraith->setScale(0.5);
				WraithTurn--;
				WraithSelect--;
				/**if (WraithX >= portalX - 50 && WraithX <= portalX + 50 && WraithY >= portalY - 50 && WraithY <= portalY + 50)
				{
					Wraith->locate(scene1, portal2X, portal2Y);
				}**/

				if (WraithX >= goalX - 50 && WraithX <= goalX + 50 && WraithY >= goalY - 50 && WraithY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && GibraltarSelect == 1 && GibraltarTurn > 0 && GibraltarX < 1100)
			{
				GibraltarX = GibraltarX + 50;
				Gibraltar->locate(scene1, GibraltarX, GibraltarY);
				Gibraltar->setScale(0.5);
				GibraltarTurn--;
				GibraltarSelect--;
				if (GibraltarX >= portalX - 50 && GibraltarX <= portalX + 50 && GibraltarY >= portalY - 50 && GibraltarY <= portalY + 50)
				{
					Gibraltar->locate(scene1, portal2X, portal2Y);
					GibraltarX = portal2X;
					GibraltarY = portal2Y;
				}

				if (GibraltarX >= goalX - 50 && GibraltarX <= goalX + 50 && GibraltarY >= goalY - 50 && GibraltarY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && MirageSelect == 1 && MirageTurn > 0 && MirageX < 1100)
			{
				MirageX = MirageX + 50;
				Mirage->locate(scene1, MirageX, MirageY);
				Mirage->setScale(0.5);
				MirageTurn--;
				MirageSelect--;
				if (MirageX >= portalX - 50 && MirageX <= portalX + 50 && MirageY >= portalY - 50 && MirageY <= portalY + 50)
				{
					Mirage->locate(scene1, portal2X, portal2Y);
					MirageX = portal2X;
					MirageY = portal2Y;
				}

				if (MirageX >= goalX - 50 && MirageX <= goalX + 50 && MirageY >= goalY - 50 && MirageY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && CausticSelect == 1 && CausticTurn > 0 && CausticX < 1100)
			{
				CausticX = CausticX + 50;
				Caustic->locate(scene1, CausticX, CausticY);
				Caustic->setScale(0.5);
				CausticTurn--;
				CausticSelect--;
				if (CausticX >= portalX - 50 && CausticX <= portalX + 50 && CausticY >= portalY - 50 && CausticY <= portalY + 50)
				{
					Caustic->locate(scene1, portal2X, portal2Y);
					CausticX = portal2X;
					CausticY = portal2Y;
				}

				if (CausticX >= goalX - 50 && CausticX <= goalX + 50 && CausticY >= goalY - 50 && CausticY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			return 0;
		});

	left->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (turn == 0 && LifelineSelect == 1 && LifelineTurn > 0 && LifelineX > 100)
			{
				LifelineX = LifelineX - 50;
				Lifeline->locate(scene1, LifelineX, LifelineY);
				Lifeline->setScale(0.5);
				LifelineTurn--;
				LifelineSelect--;
				if (LifelineX >= portalX - 50 && LifelineX <= portalX + 50 && LifelineY >= portalY - 50 && LifelineY <= portalY + 50)
				{
					Lifeline->locate(scene1, portal2X, portal2Y);
					LifelineX = portal2X;
					LifelineY = portal2Y;
				}

				if (LifelineX >= goalX - 50 && LifelineX <= goalX + 50 && LifelineY >= goalY - 50 && LifelineY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && WraithSelect == 1 && WraithTurn > 0 && WraithX > 100)
			{
				WraithX = WraithX - 50;
				Wraith->locate(scene1, WraithX, WraithY);
				Wraith->setScale(0.5);
				WraithTurn--;
				WraithSelect--;
				/**if (WraithX >= portalX - 50 && WraithX <= portalX + 50 && WraithY >= portalY - 50 && WraithY <= portalY + 50)
				{
					Wraith->locate(scene1, portal2X, portal2Y);
				}**/

				if (WraithX >= goalX - 50 && WraithX <= goalX + 50 && WraithY >= goalY - 50 && WraithY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && GibraltarSelect == 1 && GibraltarTurn > 0 && GibraltarX > 100)
			{
				GibraltarX = GibraltarX - 50;
				Gibraltar->locate(scene1, GibraltarX, GibraltarY);
				Gibraltar->setScale(0.5);
				GibraltarTurn--;
				GibraltarSelect--;
				if (GibraltarX >= portalX - 50 && GibraltarX <= portalX + 50 && GibraltarY >= portalY - 50 && GibraltarY <= portalY + 50)
				{
					Gibraltar->locate(scene1, portal2X, portal2Y);
					GibraltarX = portal2X;
					GibraltarY = portal2Y;
				}

				if (GibraltarX >= goalX - 50 && GibraltarX <= goalX + 50 && GibraltarY >= goalY - 50 && GibraltarY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && MirageSelect == 1 && MirageTurn > 0 && MirageX > 100)
			{
				MirageX = MirageX - 50;
				Mirage->locate(scene1, MirageX, MirageY);
				Mirage->setScale(0.5);
				MirageTurn--;
				MirageSelect--;
				if (MirageX >= portalX - 50 && MirageX <= portalX + 50 && MirageY >= portalY - 50 && MirageY <= portalY + 50)
				{
					Mirage->locate(scene1, portal2X, portal2Y);
					MirageX = portal2X;
					MirageY = portal2Y;
				}

				if (MirageX >= goalX - 50 && MirageX <= goalX + 50 && MirageY >= goalY - 50 && MirageY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			else if (turn == 0 && CausticSelect == 1 && CausticTurn > 0 && CausticX > 100)
			{
				CausticX = CausticX - 50;
				Caustic->locate(scene1, CausticX, CausticY);
				Caustic->setScale(0.5);
				CausticTurn--;
				CausticSelect--;
				if (CausticX >= portalX - 50 && CausticX <= portalX + 50 && CausticY >= portalY - 50 && CausticY <= portalY + 50)
				{
					Caustic->locate(scene1, portal2X, portal2Y);
					CausticX = portal2X;
					CausticY = portal2Y;
				}

				if (CausticX >= goalX - 50 && CausticX <= goalX + 50 && CausticY >= goalY - 50 && CausticY <= goalY + 50)
				{
					auto end_time = time(NULL);
					int title = 0;
					title = difftime(end_time, start_time) / ((overCount + 1) * 10);
					if (winCount >= 3)
					{
						title = 1;
					}
					string result = "결과:" + to_string(title) + "등급";
					string print = to_string(overCount) + "번 죽고 목적지 달성하기까지" + to_string(difftime(end_time, start_time)) + "초 걸림." + result.c_str();
					showMessage(print.c_str());
					win->enter();
				}
			}
			return 0;
		});

	skill->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{

			//Lifeline skill
			if (turn == 0 && LifelineSelect == 1 && LifelineTurn > 0)
			{
				if (character1 == 2 || character2 == 2 || character3 == 2)
				{
					Wraith->show();
					LifelineTurn--;
					LifelineSelect--;
					Lifeline->setScale(0.5);
					if (overCount == 0)
						return 0;
					else
						overCount--;
				}
				if (character1 == 3 || character2 == 3 || character3 == 2)
				{
					Gibraltar->show();
					LifelineTurn--;
					LifelineSelect--;
					Lifeline->setScale(0.5);
					if (overCount == 0)
						return 0;
					else
						overCount--;
				}
				if (character1 == 4 || character2 == 4 || character3 == 4)
				{
					Mirage->show();
					LifelineTurn--;
					LifelineSelect--;
					Lifeline->setScale(0.5);
					if (overCount == 0)
						return 0;
					else
						overCount--;
				}
				if (character1 == 5 || character2 == 5 || character3 == 5)
				{
					Caustic->show();
					LifelineTurn--;
					LifelineSelect--;
					Lifeline->setScale(0.5);
					if (overCount == 0)
						return 0;
					else
						overCount--;
				}
			}
			//Wraith skill portal and portal2
			else if (turn == 0 && WraithSelect == 1 && WraithTurn > 0 && portalCount == 0)
			{
				portal->show();
				portal->locate(scene1, WraithX, WraithY);
				portalX = WraithX;
				portalY = WraithY;
				WraithTurn--;
				WraithSelect--;
				Wraith->setScale(0.5);
				portalCount++;
			}
			else if (turn == 0 && WraithSelect == 1 && WraithTurn > 0 && portalCount == 1)
			{
				portal2->show();
				portal2->locate(scene1, WraithX, WraithY);
				portal2X = WraithX;
				portal2Y = WraithY;
				WraithTurn--;
				WraithSelect--;
				Wraith->setScale(0.5);
				portalCount++;
			}
			//Gibraltar skill
			else if (turn == 0 && GibraltarSelect == 1 && GibraltarTurn > 0)
			{
				shieldU->show();
				shieldR->show();
				shieldD->show();
				shieldL->show();
				shieldU->locate(scene1, GibraltarX, GibraltarY);
				shieldR->locate(scene1, GibraltarX, GibraltarY);
				shieldD->locate(scene1, GibraltarX, GibraltarY);
				shieldL->locate(scene1, GibraltarX, GibraltarY);
				shieldX = GibraltarX;
				shieldY = GibraltarY;
				GibraltarTurn--;
				GibraltarSelect--;
				Gibraltar->setScale(0.5);
				if (shieldX >= Bot1X - 50 && shieldX <= Bot1X && shieldY >= Bot1Y - 100 && shieldY <= Bot1Y + 50)
				{
					Bot1->hide();
					Bot1Life = 0;
					winCount++;
				}
				if (shieldX >= Bot2X - 50 && shieldX <= Bot2X && shieldY >= Bot2Y - 100 && shieldY <= Bot2Y + 50)
				{
					Bot2->hide();
					Bot2Life = 0;
					winCount++;
				}
				if (shieldX >= Bot3X - 50 && shieldX <= Bot3X && shieldY >= Bot3Y - 100 && shieldY <= Bot3Y + 50)
				{
					Bot3->hide();
					Bot3Life = 0;
					winCount++;
				}
			}
			//Mirage skill
			else if (turn == 0 && MirageSelect == 1 && MirageTurn > 0)
			{
				clone1->show();
				clone2->show();
				clone1->locate(scene1, MirageX+50, MirageY+100);
				clone2->locate(scene1, MirageX+50, MirageY-100);
				clone1X = MirageX + 50;
				clone1Y = MirageY+100;
				clone2X = MirageX + 50;
				clone2Y = MirageY - 100;
				MirageTurn--;
				MirageSelect--;
				Mirage->setScale(0.5);
				if (clone1X >= Bot1X - 20 && clone1X <= Bot1X + 20 && clone1Y >= Bot1Y - 20 && clone1Y <= Bot1Y + 20)
				{
					Bot1->hide();
					Bot1Life = 0;
					clone1->hide();
					winCount++;
				}
				if (clone1X >= Bot2X - 20 && clone1X <= Bot2X + 20 && clone1Y >= Bot2Y - 20 && clone1Y <= Bot2Y + 20)
				{
					Bot2->hide();
					Bot2Life = 0;
					clone1->hide();
					winCount++;
				}
				if (clone1X >= Bot3X - 20 && clone1X <= Bot3X + 20 && clone1Y >= Bot3Y - 20 && clone1Y <= Bot3Y + 20)
				{
					Bot2->hide();
					Bot2Life = 0;
					clone1->hide();
					winCount++;
				}
				if (clone2X >= Bot1X - 20 && clone2X <= Bot1X + 20 && clone2Y >= Bot1Y - 20 && clone2Y <= Bot1Y + 20)
				{
					Bot1->hide();
					Bot1Life = 0;
					clone2->hide();
					winCount++;
				}
				if (clone2X >= Bot2X - 20 && clone2X <= Bot2X + 20 && clone2Y >= Bot2Y - 20 && clone2Y <= Bot2Y + 20)
				{
					Bot2->hide();
					Bot2Life = 0;
					clone2->hide();
					winCount++;
				}
				if (clone2X >= Bot3X - 20 && clone2X <= Bot3X + 20 && clone2Y >= Bot3Y - 20 && clone2Y <= Bot3Y + 20)
				{
					Bot2->hide();
					Bot2Life = 0;
					clone2->hide();
					winCount++;
				}
			}
			//Caustic skill
			if (turn == 0 && CausticSelect == 1 && CausticTurn > 0)
			{
				gas->show();
				gas->locate(scene1, CausticX, CausticY);
				gasX = CausticX;
				gasY = CausticY;
				CausticTurn--;
				CausticSelect--;
				Caustic->setScale(0.5);
				gasTimer = 1;
				if (gasX >= LifelineX - 150 && gasX <= LifelineX + 100 && gasY >= LifelineY - 150 && gasY <= LifelineY + 100)
					Lifeline->hide();
				if (gasX >= WraithX - 150 && gasX <= WraithX + 100 && gasY >= WraithY - 150 && gasY <= WraithY + 100)
					Wraith->hide();
				if (gasX >= GibraltarX - 150 && gasX <= GibraltarX + 100 && gasY >= GibraltarY - 150 && gasY <= GibraltarY + 100)
					Gibraltar->hide();
				if (gasX >= MirageX - 150 && gasX <= MirageX + 100 && gasY >= MirageY - 150 && gasY <= MirageY + 100)
					Mirage->hide();
				if (gasX >= Bot1X - 150 && gasX <= Bot1X + 100 && gasY >= Bot1Y - 150 && gasY <= Bot1Y + 100)
				{
					Bot1->hide();
					Bot1Life = 0;
					winCount++;
				}
				if (gasX >= Bot2X - 150 && gasX <= Bot2X + 100 && gasY >= Bot2Y - 150 && gasY <= Bot2Y + 100)
				{
					Bot2->hide();
					Bot2Life = 0;
					winCount++;
				}
				if (gasX >= Bot3X - 150 && gasX <= Bot3X + 100 && gasY >= Bot3Y - 150 && gasY <= Bot3Y + 100)
				{
					Bot2->hide();
					Bot2Life = 0;
					winCount++;
				}
			}

			return 0;
		});

	startGame(select);
}
