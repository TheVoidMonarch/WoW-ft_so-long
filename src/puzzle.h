#ifndef PUZZLE_H
#define PUZZLE_H

// Maximum size for the puzzle (4x4 grid)
#define MAX_PUZZLE_SIZE 4

// Puzzle structure
typedef struct Puzzle {
    int size;                           // Size of the puzzle (e.g., 3 for 3x3)
    int tiles[MAX_PUZZLE_SIZE * MAX_PUZZLE_SIZE];  // Grid of tiles
    int empty_pos;                      // Position of the empty tile (0)
} Puzzle;

// Initialize a new puzzle with the given size (e.g., 3 for 3x3)
void init_puzzle(Puzzle *puzzle, int size);

// Shuffle the puzzle using Fisher-Yates algorithm
void shuffle_puzzle(Puzzle *puzzle);

// Check if the current puzzle configuration is solvable
int is_solvable(Puzzle *puzzle);

// Check if the puzzle is solved
int is_solved(Puzzle *puzzle);

// Move a tile to the empty space if possible
// Returns 1 if the move was successful, 0 otherwise
int move_tile(Puzzle *puzzle, int tile_value);

#endif
