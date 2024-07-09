
#ifndef ROOM_H
#define ROOM_H

#include "game.h"

struct Room
{
	GameObject door_up, door_down;
	RoomType type;
	union
	{
		Puzzle puzzle;
		Boss boss;
	} room_data;
	void *background_img;
};

void init_room(Room *room);
void update_room(Room *room, float delta_time);
void render_room(const Room *room, void *mlx, void *window, void *room_img);
void cleanup_room(Room *room);

#endif /* ROOM_H */
