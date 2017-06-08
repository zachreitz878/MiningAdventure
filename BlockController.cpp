//Bock Controller manages all functoins related to changing blocks durring game
//This includes the Destruciton and Creation of new blocks, and storing their location for save/load of game
#include "BlockController.h"

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

//keycodes
#define LEFT	65
#define RIGHT	68
#define UP		87
#define DOWN	83

BlockController::BlockController()
{offset = 16.0f;}

BlockController::~BlockController()
{}

inline float BlockController::Tiles(float x)
{ return 32.0f * x; }

//Places a block which can be dug but gives player no resource
void BlockController::Dirt(float x, float y)
{
	unsigned int newBlock = agk::CreateSprite(agk::LoadImage ("dirt.png"));
	agk::SetSpritePhysicsOn (newBlock,  3);
	agk::SetSpriteVisible(newBlock, 0);
	agk::SetSpritePosition (newBlock, x, y);
	agk::SetSpriteGroup(newBlock, DIRT);
	agk::SetSpriteDepth(newBlock, 80);
}

//The Darker collored blocks after block is dug out
void BlockController::Empty(float x, float y)
{
	unsigned int newBlock1 = agk::CreateSprite(agk::LoadImage ("dirt.png"));
	agk::SetSpritePosition (newBlock1, x, y);
	agk::SetSpriteGroup(newBlock1, EMPTY);
	agk::SetSpriteDepth(newBlock1, 82);
}

//exchanges empty tile for ladder tile, and can place max_height amount of ladders above a ladder sprite
void BlockController::Ladder(float x, float y, int max_height)
{
	//x+=10.0f; y+=10.0f;
	//empty block to swap with ladder block
	unsigned int blockID = agk::GetSpriteHitGroup(EMPTY, x, y);

	//if player is not on a ladder
	if(!agk::GetSpriteHitGroup(LADDER, x, y))
	{
		unsigned int new_ladder = agk::CreateSprite(agk::LoadImage("ladder.png"));
		agk::SetSpriteGroup(new_ladder, LADDER);
		agk::SetSpriteDepth(new_ladder, 6);
		agk::SetSpritePosition(new_ladder, agk::GetSpriteX(blockID), agk::GetSpriteY(blockID));
		agk::DeleteSprite(blockID);
	}
	//if player is on a ladder
	else if(max_height > 0)
	{
		//recursively call ladder function until hit empty block or non empty block
		Ladder(x, y - Tiles(1.0f), --max_height);
	}
}

void BlockController::Resource(int type, float x, float y)
{
	unsigned int Block;

	if(type != STONE) 
	{
		Block = agk::CreateSprite(agk::LoadImage("resources.png"));
		agk::SetSpriteAnimation(Block, 32, 32, type-150);
		agk::SetSpriteFrame(Block, type-150);
		Dirt(x,y);
	}

	if(type == STONE) 
	{
		Block = agk::CreateSprite(agk::LoadImage("RockFall_Anim.png"));
		//agk::SetSpriteImage(Block, agk::LoadImage("RockFall_Anim.png"), 1);
		agk::SetSpriteAnimation(Block, 32, 64, 19);
		agk::SetSpriteFrame(Block, 1);
		agk::SetSpritePhysicsOn(Block,3);
		agk::SetSpriteShape(Block, 3);
		//agk::SetSpriteShapeBox(Block, -16, -32, 16, 0, 0);
		Empty(x,y);
		//agk::SetSpritePhysicsCanRotate(Block, 0 );
		//agk::SetSpritePhysicsMass(Block, 1000);
		//agk::SetSpriteDepth(Block, 3);
	}

	agk::SetSpriteDepth(Block, 81);
	agk::SetSpritePosition(Block, x, y);
	agk::SetSpriteGroup(Block, type);
	
}

void BlockController::Destroy(float x, float y)
{
	unsigned int blockID = agk::GetSpriteHitGroup(DIRT, x + offset, y + offset);
	agk::DeleteSprite(blockID);
	NewBlocks(x, y);
}

void BlockController::Destroy(unsigned int blockID)
{
	float x = agk::GetSpriteX(blockID);
	float y =  agk::GetSpriteY(blockID);
	NewBlocks(x, y);
	agk::DeleteSprite(blockID);
}

void BlockController::NewBlocks(float x, float y)
{
	float x_dir = 0;
	float y_dir = 0;
//LEFT
	if(agk::GetRawKeyState(LEFT)) x_dir = -1.0f;
//RIGHT
	else if(agk::GetRawKeyState(RIGHT)) x_dir =  1.0f;
//UP
	else if(agk::GetRawKeyState(UP)) y_dir = -1.0f;
//DOWN
	else if(agk::GetRawKeyState(DOWN)) y_dir =  1.0f;
	
	if(x_dir != 0 || y_dir != 0)
	{
		//this places the block directly in front of block being dug, if able
		if(CanPlace(x + Tiles(x_dir),  y + Tiles(y_dir)))
			Dirt(x + Tiles(x_dir), y + Tiles(y_dir));

		//based on x and y direction, place two more blocks if able
		switch(int(x_dir))
		{
			case 0:
				switch(int(y_dir))
				{
					case 0: break;
					default:
						if(CanPlace(x + Tiles(-1.0f), y))
							Dirt(x + Tiles(-1.0f), y);
						if(CanPlace(x + Tiles(1.0f), y))
							Dirt(x + Tiles(1.0f), y);
						break;
				}
			break;

			default:
				if(CanPlace(x, y + Tiles(-1.0f)))
					Dirt(x, y + Tiles(-1.0f));
				if(CanPlace(x, y + Tiles(1.0f)))
					Dirt(x, y + Tiles(1.0f));
				break;
		}
	}

	unsigned int blockGroup = getResource(x,y);
	if(blockGroup != 2) agk::DeleteSprite(agk::GetSpriteHitGroup(blockGroup, x+offset, y+offset));
	Empty(x, y);
}

//returns true if no block is at locaiton x, y and false if there is alreayd a block there
bool BlockController::CanPlace(float x, float y)
{
	x+=offset;
	y+=offset;
	bool out = true;
	if(agk::GetSpriteHitGroup(DIRT, x, y))	out = false;
	else if(agk::GetSpriteHitGroup(EMPTY, x, y)) out = false;
	else if(agk::GetSpriteHitGroup(LADDER, x, y)) out = false;
	else if(agk::GetSpriteHitGroup(STONE, x, y)) out = false;
	else out = !isResource(x,y);
	return out;
}

bool BlockController::isResource(float x, float y)
{
	if(
		agk::GetSpriteHitGroup(COAL, x, y)
		|| agk::GetSpriteHitGroup(COPPER, x, y)
		|| agk::GetSpriteHitGroup(TIN, x, y)
		|| agk::GetSpriteHitGroup(IRON, x, y)
		|| agk::GetSpriteHitGroup(EMERALD, x, y)
		|| agk::GetSpriteHitGroup(GOLD, x, y)
		|| agk::GetSpriteHitGroup(DIAMOND, x, y)
		)
		return true;
	else return false;
}

unsigned int BlockController::getResource(float x, float y)
{
	x+=offset;
	y+=offset;
	unsigned int temp = 2;
    if(agk::GetSpriteHitGroup(COAL, x, y))
		temp = COAL;
	else if(agk::GetSpriteHitGroup(COPPER, x, y))
		temp = COPPER;
	else if(agk::GetSpriteHitGroup(TIN, x, y))
		temp = TIN;
	else if(agk::GetSpriteHitGroup(IRON, x, y))
		temp = IRON;
	else if(agk::GetSpriteHitGroup(EMERALD, x, y))
		temp = EMERALD;
	else if(agk::GetSpriteHitGroup(GOLD, x, y))
		temp = GOLD;
	else if(agk::GetSpriteHitGroup(DIAMOND, x, y))
		temp = DIAMOND;
	//return agk::GetSpriteHitGroup(temp, x, y);
	return temp;
}