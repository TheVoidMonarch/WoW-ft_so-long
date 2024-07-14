#include "game.h"
#include "player.h"
#include "boss.h"
#include "input.h"
#include "puzzle.h"
#include "camera.h"
#include "room.h"
#include "spawn.h"
#include "maps.h"
#include "ui.h"
#include "render.h"

void init_game(Game *game, int width, int height);
void init_camera(Camera *camera, int width, int height, int min_x, int min_y, int max_x, int max_y);