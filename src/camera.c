#include "game.h"
#include "camera.h"
#include "player.h"

void init_camera(Camera *camera, int width, int height, int min_x, int min_y, int max_x, int max_y);
void update_camera(Game *game);
void set_camera_position(Game *game, int x, int y);
void set_camera_target(Camera *camera, GameObject *target);
void set_camera_speed(Camera *camera, float speed);