#include "game.h"
#include "ui.h"
#include "spawn.h"
#include "room.h"
#include "input.h"
void update_camera(Camera *camera)
{
	if (camera->target)
	{
		// Calculate the new camera position to center the target
		camera->x = camera->target->x - camera->width / 2;
		camera->y = camera->target->y - camera->height / 2;

		// Ensure camera stays within boundaries
		if (camera->x < camera->min_x)
			camera->x = camera->min_x;
		if (camera->y < camera->min_y)
			camera->y = camera->min_y;
		if (camera->x + camera->width > camera->max_x)
			camera->x = camera->max_x - camera->width;
		if (camera->y + camera->height > camera->max_y)
			camera->y = camera->max_y - camera->height;
	}
}
