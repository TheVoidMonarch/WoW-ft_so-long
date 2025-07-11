#include "mlx.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

// Game structure to hold all game data
typedef struct s_game
{
    void    *mlx;
    void    *win;
    int     width;
    int     height;
    char    *title;
    int     running;
}           t_game;

// Function to initialize the game
static int  init_game(t_game *game)
{
    game->width = 800;      // Window width
    game->height = 600;     // Window height
    game->title = "Whisper of the Wind";
    game->running = 1;      // Game is running
    
    // Initialize MLX
    game->mlx = mlx_init();
    if (!game->mlx)
        return (0);
        
    // Create window
    game->win = mlx_new_window(game->mlx, game->width, game->height, game->title);
    if (!game->win)
    {
        free(game->mlx);
        return (0);
    }
    return (1);
}

// Function to handle key presses
static int  key_press(int keycode, t_game *game)
{
    if (keycode == 53) // ESC key
        game->running = 0;
    return (0);
}

// Main game loop
static int  game_loop(t_game *game)
{
    // Update game state
    
    // Render game
    
    return (0);
}

int main()
{
    t_game  game;
    
    // Initialize game
    if (!init_game(&game))
    {
        printf("Error: Failed to initialize game\n");
        return (1);
    }
    
    // Set up event hooks
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);
    mlx_hook(game.win, 17, 0, (void *)exit, 0);  // Handle window close button
    
    // Start game loop
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
    
    // Clean up
    mlx_destroy_window(game.mlx, game.win);
    return (0);
}