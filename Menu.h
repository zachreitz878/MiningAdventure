#ifndef _MENU_H
#define _MENU_H

#include "agk.h"

class Menu
{
	public:
		Menu();
		~Menu();

		unsigned int menuBackground, menuSelectSprite, menuMusic; //Menu Sprites
		int selected, selectedSave;
		bool loading, backToMain, goToLoadGame; //bool variables for program control, tells what state to go to
		bool firstload;

		void InitMainMenu();
		void InitLoadMenu();
		void MainMenuUpdate(); //update function for main menu
		void LoadMenuUpdate(); //update funciton for load game menu
		void MenuExit(); //cleanup function
		int SaveGame();

	private:

};

#endif