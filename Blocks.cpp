#include "Blocks.h"
#include "agk.h"

Blocks::Blocks()
{
}

Blocks::~Blocks()
{
}

void Blocks::init_blocks(int w, int l, float t)
{
	width = w;
	length = l;
	tile_size = t;
}

float Blocks::tiles(float x)
{
	return(x * tile_size);
}

