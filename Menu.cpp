


//Handels all sprites and input funcitons for the game's Menus
#include "Menu.h"

Menu::Menu()
{
	agk::SetSyncRate(20.0f, 0);//less fps in menu

	//setting game resolution (should change depending on system?)
	agk::SetVirtualResolution(1280, 720);
	agk::SetDisplayAspect(1280.0f/720.0f);
	firstload = true;

	InitMainMenu();
}

Menu::~Menu()
{ 
	agk::StopMusic();
}

void Menu::InitMainMenu()
{
	loading = false;
	backToMain = false;
	goToLoadGame = false;

	if(firstload == true)
	{
	selected = 1;
	//create menu graphics
	menuBackground = agk::CreateSprite(agk::LoadImage("Menu.png"));
	menuSelectSprite = agk::CreateSprite(agk::LoadImage("menuSelect.png"));
	agk::SetSpritePosition(menuSelectSprite, 490.0f, 513.0f);

	menuMusic= agk::LoadMusic("Dubmood - Kenny The Toffelskater.mp3");
	agk::SetMusicFileVolume(menuMusic, 55);
	//agk::PlayMusic(menuMusic,1);
	}
	else
	{
		agk::SetSpriteImage(menuBackground, agk::LoadImage("Menu.png"));
		agk::SetSpriteImage(menuSelectSprite, agk::LoadImage("menuSelect.png"));
		agk::SetSpritePosition(menuSelectSprite, 490.0f, 513.0f);
	}
}

void Menu::InitLoadMenu()
{
	loading = false;
	backToMain = false;
	goToLoadGame = false;

	if(firstload == true)
	{
	selectedSave = 1;
	//create loag game menu graphics
	menuBackground = agk::CreateSprite(agk::LoadImage("load_menu.png"));

	//create the sprite that signifies which save game you are going to select
	menuSelectSprite = agk::CreateSprite(agk::LoadImage("MinerR0.png"));
	agk::SetSpritePosition(menuSelectSprite, 140, 100);
	agk::SetSpriteScale(menuSelectSprite, 3.0f, 3.0f);
	firstload = false;
	}
	else
	{
	agk::SetSpriteImage(menuBackground, agk::LoadImage("load_menu.png"));
	agk::SetSpriteImage(menuSelectSprite, agk::LoadImage("MinerR0.png"));
	agk::SetSpritePosition(menuSelectSprite, 140, 100);
	agk::SetSpriteScale(menuSelectSprite, 3.0f, 3.0f);
	}
}

//Update funciton for the first menu at beginning of the game
void Menu::MainMenuUpdate()
{
	//if Up key pressed
	if(agk::GetRawKeyPressed(38))
	{
		//if at new game, set value of selected to 2 to signify we want to load game
		if (selected == 2) 
		{
			selected = 1;
			agk::SetSpritePosition(menuSelectSprite, 490.0f, 513.0f);
		}
	}

	//if down key pressed
	if(agk::GetRawKeyPressed(40))
	{
		//if at load game, set value of selected to 1 to signify we want to start a new game
		if (selected == 1) 
		{
			selected = 2;
			agk::SetSpritePosition(menuSelectSprite, 490.0f, 584.0f);
		}
	}

	//If ever enter is pushed durring update
	if(agk::GetRawKeyPressed(13))
	{

		if(selected == 2) //if load game option selected
		{
			InitLoadMenu();
			goToLoadGame = true;
		}
		else
		{
			MenuExit();
			loading = true;
		}
	}
}

//Update function for the Menu to choose which game to load
void Menu::LoadMenuUpdate()
{
	if(agk::GetRawKeyPressed(38)) //If up is pressed
		if(selectedSave > 1) //if selected is not at the end of the list
			selectedSave--; //increment value

	if(agk::GetRawKeyPressed(40)) //if down is pressed
		if(selectedSave < 3) //if not at beginning of list
			selectedSave++; //decrement value

	//depending on the value of selectedSave, move menuSelectSprite to correct position
	switch (selectedSave)
	{
		case 1:
			agk::SetSpritePosition(menuSelectSprite, 140, 100);
			break;
		case 2:
			agk::SetSpritePosition(menuSelectSprite, 140, 330);
			break;
		case 3:
			agk::SetSpritePosition(menuSelectSprite, 140, 540);
			break;
	}

	if(agk::GetRawKeyPressed(13)) //if enter is pushed
	{
		MenuExit();
		loading = true;
	}

	if(agk::GetRawKeyPressed(27))//escape
	{
		agk::DeleteSprite(menuBackground);
		agk::DeleteSprite(menuSelectSprite);
		InitMainMenu();
		backToMain = true;
	}
}

//menu cleanup funciton
void Menu::MenuExit()
{
	agk::DeleteSprite(menuBackground);
	agk::DeleteSprite(menuSelectSprite);
	agk::DeleteMusic(menuMusic);
}

//returns the game we want to load
int Menu::SaveGame()
{ return selectedSave; }