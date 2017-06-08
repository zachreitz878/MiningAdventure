#ifndef _PLAYER_H
#define _PLAYER_H

#include "agk.h"
#include "chunk.h"

class Player
{
	public:
		unsigned int sprite, dig_anim, ground, light, sky;
		unsigned int parallax_mountains[5], parallax_forest[4];
		float light_scale, light_burn_rate;
		float edge1, edge2;
		unsigned int jump_sound, dig_sound, break_sound, pickup_sound;
		int ladderHeight, effects_vol;
		float gravity, jump_speed, walk_speed, pickaxe_speed, dig_speed, starting_pos, friction;
		float xOffset, yOffset;
		float x_dir, y_dir;

		bool debug;
		bool building_ladder;
		bool done_digging;
		bool stone_falling;

		float blockX, blockY;

		Player();
		~Player();

		float Tiles(float);
		void Init();

		inline float GetX();
		inline float GetY();
		inline float GetVX();
		inline float GetVY();

		inline void SyncThings();
		void Update();
		void Debug();
		void Parallax(float);

		inline void Walk(float);
		inline void Jump();
		inline void Climb(float);
		
		inline bool CanDig(float, float);
		inline void Dig(float, float);
		bool CheckBlock(int, float, float);
		bool CheckBlock(float, float);
		void BlockBreakParticleEffect(float, float);
		
		inline bool OnLadder();
		inline void StopMoving();
		void StopDigging();
};
#endif