#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stddef.h>

typedef struct GameObject GameObject;
typedef struct Player Player;
typedef struct Boss Boss;
typedef struct Button Button;
typedef struct Puzzle Puzzle;
typedef struct Room Room;
typedef struct Camera camera;

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

typedef enum
{
	ROOM_PUZZLE,
	ROOM_BOSS,
	ROOM_ALTAR,
	ROOM_COUNT
} RoomType;

struct GameObject
{
	int x;
	int y;
	int width;
	int height;
};

struct Player
{
	GameObject base;
	int health;
	int attack;
};

struct Boss
{
	GameObject base;
	bool is_alive;
	int health;
	int attack;
	int defense;
};

struct Button
{
	GameObject base;
	bool is_pressed;
};

struct Puzzle
{
	GameObject base;
	int num_button;
	char **button_sym;
	int *solution;
	char **prophecies;
};

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

typedef struct
{
	int x;
	int y;
	int width;
	int height;
	int min_x;
	int min_y;
	int max_x;
	int max_y;
	bool is_moving;
	float speed;
	GameObject *target;
	float zoom;
}Camera;

typedef struct
{
	Player *player;
	Button *buttons;
	Room *rooms;
	RoomType current_room;
	bool key_collected;
	Camera *camera_state;
} Game;

void init_game(Game *game);
void update_game(void *mlx);
void render_game(const Game *game);
void handle_input(Game *game, char input);
void cleanup_game(Game *game);

#endif;