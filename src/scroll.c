#include "camera.h"

void move_camera(Camera *camera, int dx, int dy);
void center_camera_on_target(Camera *camera);
void check_camera_boundaries(Camera *camera);
void clamp_camera_position(Camera *camera);
