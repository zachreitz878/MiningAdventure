#ifndef _World_H
#define _World_H

#include "agk.h"
#include "Player.h"

class World
{
	public:
		World();
		~World();

		Player* Player1;

		Chunk* Chunk_Control;
		Chunk* Chunk_Control2;
		std::vector<Chunk*> Chunk_List;

		float width;
		float length;
		float starting_pos;
		float gravity;

		unsigned int music;

		float Tiles(float);
		void SetGlobals();

		void LoadWorld(int);
		void LoadBackground();
		void LoadChunks();
		void LoadEntrance();
		void LoadBlocks(int);
		void SaveGame(int);

		void Update();
};
#endif