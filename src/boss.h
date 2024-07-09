#ifndef BOSS_H
#define BOSS_H

#include "game.h"

struct Boss
{
	GameObject base;
	bool is_alive;
	int health;
	int attack;
	int defense;
};

void init_boss(Boss *boss);
void update_boss(Boss *boss, float delta_time);
void render_boss(const Boss *boss, void *mlx, void *window, void *boss_img);
void cleanup_boss(Boss *boss);

#endif
