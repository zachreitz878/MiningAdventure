#ifndef _H_APP
#define _H_APP

// Link to AGK libraries
#include "agk.h"
//Link to Player Defined Classes
#include "Player.h"
#include "World.h"
#include "Menu.h"

// Global values for the app
class app
{
	public:

		// main vars

	public:

		// constructor
		app() { memset ( this, 0, sizeof(app)); }

		// main app functions
		void Begin( void );
		void Loop( void );
		void End( void );
};

extern app App;

#endif

// Allow us to use the LoadImage function name
#ifdef LoadImage
 #undef LoadImage
#endif
