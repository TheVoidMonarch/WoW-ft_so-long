
#ifndef RENDER_H
#define RENDER_H

#include "game.h"

void render_game(const Game *game);
void render_player(const Player *player, void *mlx, void *window, void *player_img);
void render_boss(const Boss *boss, void *mlx, void *window, void *boss_img);
void render_puzzle(const Puzzle *puzzle, void *mlx, void *window, void *puzzle_img);
void render_room(const Room *room, void *mlx, void *window, void *room_img);
void render_camera(Game *game);

#endif /* RENDER_H */
