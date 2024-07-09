#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

struct Player
{
	GameObject base;
	int health;
	int attack;
};

void init_player(Player *player);
void update_player(Player *player, float delta_time);
void render_player(const Player *player, void *mlx, void *window, void *player_img);
void cleanup_player(Player *player);

#endif
