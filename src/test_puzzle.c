#include "puzzle.h"
#include <stdio.h>
#include <unistd.h>

// Function to print the puzzle in a grid format
void print_puzzle(Puzzle *puzzle) {
    printf("\n");
    for (int i = 0; i < puzzle->size; i++) {
        for (int j = 0; j < puzzle->size; j++) {
            int val = puzzle->tiles[i * puzzle->size + j];
            if (val == 0) {
                printf("   ");  // Empty space
            } else {
                printf("%2d ", val);
            }
        }
        printf("\n");
    }
    printf("\nUse number keys to move tiles (0 to quit): ");
}

int main() {
    Puzzle puzzle;
    int size = 3;  // 3x3 puzzle
    
    printf("Welcome to the Sliding Puzzle Game!\n");
    printf("Arrange the numbers in order with the empty space at the end.\n");
    
    // Initialize and shuffle the puzzle
    init_puzzle(&puzzle, size);
    shuffle_puzzle(&puzzle);
    
    int move;
    int moves = 0;
    
    // Game loop
    while (1) {
        // Clear the screen (works on Unix-like systems)
        printf("\033[H\033[J");
        
        // Print the current state
        printf("Moves: %d\n", moves);
        print_puzzle(&puzzle);
        
        // Check if the puzzle is solved
        if (is_solved(&puzzle)) {
            printf("\nCongratulations! You solved the puzzle in %d moves!\n", moves);
            break;
        }
        
        // Get user input
        printf("\nEnter a number to move (0 to quit): ");
        if (scanf("%d", &move) != 1) {
            // Clear input buffer
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            sleep(1);
            continue;
        }
        
        // Check if user wants to quit
        if (move == 0) {
            printf("\nThanks for playing!\n");
            break;
        }
        
        // Try to make the move
        if (move < 1 || move >= size * size) {
            printf("Invalid move. Please enter a number between 1 and %d.\n", size * size - 1);
            sleep(1);
            continue;
        }
        
        if (move_tile(&puzzle, move)) {
            moves++;
        } else {
            printf("Invalid move. That tile can't be moved.\n");
            sleep(1);
        }
    }
    
    return 0;
}
