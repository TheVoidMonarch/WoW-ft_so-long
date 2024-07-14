#ifndef CAMERA_H
#define CAMERA_H

#include "game.h"

void init_camera(Camera *camera, int width, int height, int min_x, int min_y, int max_x, int max_y);
void update_camera(Game *game);
void set_camera_position(Game *game, int x, int y);
void set_camera_target(Camera *camera, GameObject *target);
void set_camera_speed(Camera *camera, float speed);
void move_camera(Camera *camera, int dx, int dy);
void center_camera_on_target(Camera *camera);
void check_camera_boundaries(Camera *camera);
void clamp_camera_position(Camera *camera);

#endif /* CAMERA_H */