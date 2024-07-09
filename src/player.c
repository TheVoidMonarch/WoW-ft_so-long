
#include "player.h"
#include "game.h"
#include "mlx.h"

void init_player(Player *player)
{
	// Initialize player position
	player->base.x = 100;
	player->base.y = 100;

	// Initialize player size
	player->base.width = 32;
	player->base.height = 32;

	// Initialize player health and attack
	player->health = 100;
	player->attack = 10;
}

void update_player(Player *player, float delta_time)
{
	int key_state[256]; // array to store key states

	// Get the current key states
	mlx_get_key_state(key_state, 256);

	// Check for key presses
	if (key_state[MLX_KEY_LEFT])
	{
		player->base.x -= 5; // move left
	}
	else if (key_state[MLX_KEY_RIGHT])
	{
		player->base.x += 5; // move right
	}
	else if (key_state[MLX_KEY_UP])
	{
		player->base.y -= 5; // move up
	}
	else if (key_state[MLX_KEY_DOWN])
	{
		player->base.y += 5; // move down
	}

	// Update player position based on delta time
	// (we'll revisit this part later)

	// Check for collisions with walls or other game objects
	// (TO DO: implement collision detection logic)
}

void render_player(Player *player, mlx_t *mlx)
{
	// Render the player's sprite
	mlx_put_image_to_window(mlx, mlx_new_image(mlx, player->base.width, player->base.height), player->base.x, player->base.y);
}
