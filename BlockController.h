#ifndef _BLOCKCONTROLLER_H
#define _BLOCKCONTROLLER_H

#include <vector>
#include "agk.h"

class BlockController
{
	public:
		BlockController();
		~BlockController();
		
		std::vector<unsigned int> Block_List; //list of block sprites

		float offset;
		inline float Tiles(float);

		void Dirt(float, float);
		void Empty(float, float);
		void Ladder(float, float, int);
		void Resource(int, float, float);
		void Destroy(float, float);
		void Destroy(unsigned int);
		void NewBlocks(float, float);
		bool isResource(float, float);
		unsigned int getResource(float, float);
		//void Swap();

		bool CanPlace(float, float);
};
#endif