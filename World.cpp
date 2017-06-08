//Handles Loading the world, and all the above ground sprites
#include "World.h"

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

World::World()
{
	Player1 = new Player();
	Chunk_Control = new Chunk();
	Chunk_Control2 = new Chunk();
	Chunk_List.push_back(Chunk_Control);
	Chunk_List.push_back(Chunk_Control2);
}

World::~World()
{}

float World::Tiles(float x)
{
	return 32.0f * x;
}

void World::SetGlobals()
{
	width = 100.0f; //amount of tiles wide
	length= 100.0f; //amount of tiles deep
	starting_pos = Tiles(width)/2.0f;
}

void World::LoadWorld(int save_state)
{
	unsigned int loadScreen = agk::CreateSprite(agk::LoadImage("loading_screen.png"));
	SetGlobals();
	LoadBackground();
	//LoadBlocks(save_state);
	agk::SetClearColor(140, 70, 35);//setting background to dirt color
	music = agk::LoadMusic("Level Up.mp3");
	agk::SetMusicFileVolume(music, 100);
	//agk::PlayMusic(music, 1); /************************?
	agk::DeleteSprite(loadScreen);
	agk::SetSyncRate(60,0);
	agk::SetVSync(1);

	Chunk_Control->Init(1);
	Chunk_Control->Init(2);
	Player1->Init();
}

void World::LoadBackground()
{
	//creating shop sprite
	unsigned int shop = agk::CreateSprite(agk::LoadImage ( "shop.png" ));
	agk::SetSpriteDepth(shop, 17);
	agk::SetSpritePosition(shop, starting_pos + Tiles(6), - agk::GetSpriteHeight(shop) + 1.0f);

	//creating mine entrance
	unsigned int mine = agk::CreateSprite( agk::LoadImage("mineshaft.png"));
	agk::SetSpriteDepth(mine, 17);
	agk::SetSpritePosition(mine, Tiles(44)-16.0f, - agk::GetSpriteHeight(mine) + 2.0f);

	//TREES
	for(float i = -2; i < 12; i++)
	{
		int rand_size = agk::Random(0,5);
		float size = 2.5f + rand_size * 0.1f;
		int rand_spot = agk::Random(0,10);
		unsigned int tree = agk::CreateSprite(agk::LoadImage ("tree.png"));
		agk::SetSpriteScale(tree, float(size), float(size));
		agk::SetSpriteDepth(tree,20);
		agk::SetSpritePosition(tree, Tiles(float(rand_spot)) + Tiles(i*10), -agk::GetSpriteHeight(tree)+ 4.0f);
	}

}

void World::LoadBlocks(int save_state)
{
}

void World::SaveGame(int save)
{
}

void World::Update()
{
	Player1->Update();
	if(Player1->building_ladder)
	{
		Chunk_List.at(0)->Chunk_Block_Control->Ladder(Player1->GetX(), Player1->GetY(), 1);
		Player1->building_ladder = false;
	}
	else if (Player1->done_digging)
	{
		Chunk_List.at(0)->Chunk_Block_Control->Destroy(Player1->blockX, Player1->blockY);
		if(Player1->stone_falling)
			Chunk_List.at(0)->Chunk_Block_Control->Destroy(Player1->blockX, Player1->blockY - 32.0f);
		Player1->done_digging = false;
	}
}