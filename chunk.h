#pragma once
#ifndef _CHUNK_H
#define _CHUNK_H

#include "agk.h"
#include "BlockController.h"

class Chunk
{
	public:
		Chunk();
		~Chunk();

		void Init(int);
		void LoadEntrance();

		BlockController* Chunk_Block_Control;

		float Tiles(float);
		
	private:
		int width, length, depth_start, depth_end;
};
#endif