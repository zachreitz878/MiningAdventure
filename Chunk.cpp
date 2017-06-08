//A "chunk" is an object that refferences and randomly creates all blocks from depth_start to depth_end
//Chunks need to be loaded when needed and freed when not needed  to save memory and cut down on loading time

#include "chunk.h"

//Sprite hit groups
#define DIRT	101
#define EMPTY	102
#define	LADDER  103
#define STONE	151
#define COAL	152
#define COPPER  153
#define TIN		154
#define IRON	155
#define EMERALD	156
#define GOLD	157
#define DIAMOND 158

Chunk::Chunk()
{
}

Chunk::~Chunk()
{}

void Chunk::Init(int chunk_num)
{
	//measured in tiles
	width = 100;
	length = 15;
	depth_start = (chunk_num-1) * length;

	Chunk_Block_Control = new BlockController();

	float i, j;
	int rand;
	if(chunk_num == 1) //first chunk needs to skip some blocks for mine entrance
	{
		for(i = 0; i < width; i++)
			for(j = 1; j < length; j++)
			{
				if (i == 46 && j <= 3) continue; //skip entrance blocks
				else if ((i == 45 && j <= 3) || (i == 47 && j <= 3) || (i == 46 && j == 4)) Chunk_Block_Control->Dirt(Tiles(i), Tiles(j)); //build walls around mine entrance
				else
				{
					if(agk::Random(1,8) == 1)//% chance that any given tile is a resource or not
					{
						rand = agk::Random(2, 4); //randomize which resource to create
						Chunk_Block_Control->Resource(rand + 150, Tiles(i), Tiles(depth_start + j));
					}
					else if(agk::Random(1,15) == 1)
					{
						Chunk_Block_Control->Resource(STONE, Tiles(i), Tiles(depth_start + j));
					}
					else if(agk::Random(1,1000) == 2)
						Chunk_Block_Control->Resource(IRON, Tiles(i), Tiles(depth_start + j));
				}
			}
	}
	else //all other chunks (same code but without mine entrance check)
	{
		for(i = 0; i < 100; i++)
			for(j = 1; j < length; j++)
			{
				rand = agk::Random(1,10);
				if(rand == 1)
				{
					rand = agk::Random(1, 8);
					Chunk_Block_Control->Resource(rand + 150, Tiles(i), Tiles(depth_start + j));
				}
				else continue;
			}
	}

	LoadEntrance();
}

void Chunk::LoadEntrance()
{
	for(float i = -25; i < 125; i++)
	{
		Chunk_Block_Control->Dirt(Tiles(i), 0); //creates solid surface to walk on
		if(i != 46)
		{
		unsigned int grass = agk::CreateSprite(agk::LoadImage("grass1.png"));
		int rand = agk::Random(1,3);
		if (rand == 1) agk::SetSpriteFlip(grass, 1, 0);
		agk::SetSpriteScale(grass, 2.0f, 2.0f);
		agk::SetSpriteDepth(grass, 1);
		agk::SetSpritePosition(grass, Tiles(i), Tiles(-1));
		}
	}

	Chunk_Block_Control->Dirt(0, Tiles(-1));
	Chunk_Block_Control->Dirt(0, Tiles(-2));
	Chunk_Block_Control->Dirt(0, Tiles(-3));
	Chunk_Block_Control->Dirt(Tiles(100), Tiles(-1));
	Chunk_Block_Control->Dirt(Tiles(100), Tiles(-2));
	Chunk_Block_Control->Dirt(Tiles(100), Tiles(-3));

	//create mine entrance
	//ladder can only be placed on an empty (already dug) tile
	Chunk_Block_Control->Empty(Tiles(46), Tiles(-1)); //ladder above ground
	Chunk_Block_Control->Ladder(Tiles(46)+10, Tiles(-1.0f)+10, 0);

	Chunk_Block_Control->Destroy(Tiles(46), Tiles(0)); //creates entrance to mine
	Chunk_Block_Control->Ladder(Tiles(46)+10, Tiles(0.0f)+10, 0);

	Chunk_Block_Control->Empty(Tiles(46), Tiles(1));
	Chunk_Block_Control->Ladder(Tiles(46)+10, Tiles(1.0f)+10, 0);
	
	Chunk_Block_Control->Empty(Tiles(46), Tiles(2));
	Chunk_Block_Control->Ladder(Tiles(46)+10, Tiles(2.0f)+10, 0);
	
	Chunk_Block_Control->Empty(Tiles(46), Tiles(3));
	Chunk_Block_Control->Ladder(Tiles(46)+10, Tiles(3.0f)+10, 0);
}

float Chunk::Tiles(float x)
{
	return 32.0f * x;
}