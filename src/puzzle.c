#include "puzzle.h"
#include <stdlib.h>
#include <time.h>

// Initialize a new puzzle
void init_puzzle(Puzzle *puzzle, int size) {
    puzzle->size = size;
    puzzle->empty_pos = size * size - 1;  // Start with empty at bottom-right
    
    // Fill the puzzle with numbers 1 to (size²-1), with 0 as empty space
    for (int i = 0; i < size * size - 1; i++) {
        puzzle->tiles[i] = i + 1;
    }
    puzzle->tiles[size * size - 1] = 0;  // Empty space
    
    // Initialize random seed
    srand(time(NULL));
}

// Fisher-Yates shuffle to randomize the puzzle
void shuffle_puzzle(Puzzle *puzzle) {
    int n = puzzle->size * puzzle->size;
    
    // Perform Fisher-Yates shuffle
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        
        // Skip the empty space
        if (puzzle->tiles[i] == 0 || puzzle->tiles[j] == 0) {
            puzzle->empty_pos = (puzzle->tiles[i] == 0) ? i : j;
            i++;  // Retry this position
            continue;
        }
        
        // Swap tiles
        int temp = puzzle->tiles[i];
        puzzle->tiles[i] = puzzle->tiles[j];
        puzzle->tiles[j] = temp;
    }
    
    // Ensure the puzzle is solvable
    if (!is_solvable(puzzle)) {
        // If not solvable, make it solvable by swapping two non-empty tiles
        int i = 0, j = 1;
        if (puzzle->tiles[i] == 0) i++;
        if (puzzle->tiles[j] == 0) j++;
        
        int temp = puzzle->tiles[i];
        puzzle->tiles[i] = puzzle->tiles[j];
        puzzle->tiles[j] = temp;
    }
}

// Check if the puzzle is solvable
int is_solvable(Puzzle *puzzle) {
    int inversions = 0;
    int n = puzzle->size * puzzle->size;
    
    // Count inversions
    for (int i = 0; i < n - 1; i++) {
        if (puzzle->tiles[i] == 0) continue;
        
        for (int j = i + 1; j < n; j++) {
            if (puzzle->tiles[j] != 0 && puzzle->tiles[i] > puzzle->tiles[j]) {
                inversions++;
            }
        }
    }
    
    // For odd-sized puzzles, number of inversions must be even
    if (puzzle->size % 2 == 1) {
        return inversions % 2 == 0;
    }
    // For even-sized puzzles, the row of the empty space matters
    else {
        int empty_row = puzzle->empty_pos / puzzle->size;
        return (inversions + empty_row) % 2 == 1;
    }
}

// Check if the puzzle is solved
int is_solved(Puzzle *puzzle) {
    for (int i = 0; i < puzzle->size * puzzle->size - 1; i++) {
        if (puzzle->tiles[i] != i + 1) {
            return 0;  // Not solved
        }
    }
    return puzzle->tiles[puzzle->size * puzzle->size - 1] == 0;  // Last tile should be empty
}

// Move a tile to the empty space if possible
int move_tile(Puzzle *puzzle, int tile_value) {
    int tile_pos = -1;
    int n = puzzle->size * puzzle->size;
    
    // Find the position of the tile
    for (int i = 0; i < n; i++) {
        if (puzzle->tiles[i] == tile_value) {
            tile_pos = i;
            break;
        }
    }
    
    if (tile_pos == -1) return 0;  // Tile not found
    
    int empty_row = puzzle->empty_pos / puzzle->size;
    int empty_col = puzzle->empty_pos % puzzle->size;
    int tile_row = tile_pos / puzzle->size;
    int tile_col = tile_pos % puzzle->size;
    
    // Check if the tile is adjacent to the empty space
    if ((abs(empty_row - tile_row) == 1 && empty_col == tile_col) ||
        (abs(empty_col - tile_col) == 1 && empty_row == tile_row)) {
        
        // Swap the tile with the empty space
        puzzle->tiles[puzzle->empty_pos] = puzzle->tiles[tile_pos];
        puzzle->tiles[tile_pos] = 0;
        puzzle->empty_pos = tile_pos;
        return 1;  // Move successful
    }
    
    return 0;  // Move not possible
}
