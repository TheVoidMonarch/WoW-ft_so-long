#include "game.h"
#include "camera.h"

void init_camera(Camera *camera, int width, int height, int min_x, int min_y, int max_x, int max_y, float speed, GameObject *target)
{
	camera->width = width;
	camera->height = height;
	camera->min_x = min_x;
	camera->min_y = min_y;
	camera->max_x = max_x;
	camera->max_y = max_y;
	camera->is_moving = false;
	camera->speed = speed;
	camera->target = target;
	camera->zoom = 1.0f; // Default zoom level
	camera->x = target->x - width / 2;
	camera->y = target->y - height / 2;
}
