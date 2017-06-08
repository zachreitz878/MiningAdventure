#ifndef _BLOCKS_H
#define _BLOCKS_H

#include "World.h"

class Blocks
{
public:
	unsigned int id;
	float tile_size;
	int length, width;
	

	Blocks();
	~Blocks();

	void init_blocks(int, int, float);

	float tiles(float);
	void block_solid(float, float);
	unsigned int blockSolid(float, float);
	void block_empty(float, float);
	void create_ladder(float, float);

	void destroyBlock(float, float);
	void destroyBlock(unsigned int);

	void new_blocks(float, float, float, float);
}

#endif