//Main file for game
//keeps track of which state the game is in
#include "Main.h"

//Game States
#define MAIN_MENU 0
#define LOAD_MENU 1
#define LOAD_GAME 2
#define GAME_LOOP 3
#define PAUSE_MENU 4

using namespace AGK;
app App;

World* World1;
Menu* Menu1;

int game_state = MAIN_MENU;

//when game first loads
void app::Begin ( void )
{
	Menu1 = new Menu();
	World1 = new World();
}

//Main Loop for screen update
void app::Loop ( void )
{
	//Switch game_statement controls the flow of the game based on game_state variable
	switch(game_state)
	{
//***************************MAIN_MENU_STATE****************************//
	case MAIN_MENU:
		
			Menu1->MainMenuUpdate();
			if(Menu1->goToLoadGame)
				game_state = LOAD_MENU;
			if(Menu1->loading)
				game_state = LOAD_GAME;
			break;
			
//***************************LOAD_MENU_STATE*****************************//
	case LOAD_MENU:

			Menu1->LoadMenuUpdate();
			if (Menu1->loading)
				game_state = LOAD_GAME;

			if (Menu1->backToMain)
				game_state = MAIN_MENU;
			break;

//****************************LOAD_GAME_STATE******************************//
	case LOAD_GAME:
			
			World1->LoadWorld(Menu1->SaveGame()); //initialize world
			game_state = GAME_LOOP;
			break;
			
//****************************GAME_PLAY_LOOP*******************************//
	case GAME_LOOP:

		World1->Update();
		//if(agk::GetRawKeyPressed(27))
			//game_state = PAUSE_MENU;
			break;
		
//****************************PAUSE_MENU_STATE*****************************//

	//case PAUSE_MENU:

	//break;

	}//END SWITCH

	agk::Sync ( ); //agk sync function
}

void app::End ( void )
{
}