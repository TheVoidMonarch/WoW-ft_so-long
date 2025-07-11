#include "puzzle_room.h"
#include <stdio.h>
#include <unistd.h>

void print_room_state(t_puzzle_room *room) {
    printf("\n=== Puzzle Room ===\n");
    
    // Print clues
    printf("\nClues on the steles:\n");
    for (int i = 0; i < NUM_STELES; i++) {
        printf("%d. %s\n", i + 1, room->clues[i]);
    }
    
    // Print button states
    printf("\nButton States (1-4, 0=unpressed, 1=pressed):\n");
    for (int i = 0; i < NUM_BUTTONS; i++) {
        printf("Button %d: %s\n", i + 1, room->buttons[i] ? "PRESSED" : "unpressed");
    }
    
    printf("\nEnter button number to press (1-4), or 0 to reset: ");
}

int main() {
    t_puzzle_room room;
    
    printf("Welcome to the Puzzle Room!\n");
    printf("Solve the puzzle by pressing the correct buttons based on the clues.\n");
    printf("Each time you play, the solution will be different!\n\n");
    
    // Initialize the puzzle room
    init_puzzle_room(&room);
    
    int choice;
    while (!room.solved) {
        // Clear screen (Unix-like systems)
        printf("\033[H\033[J");
        
        // Print current room state
        print_room_state(&room);
        
        // Get user input
        if (scanf("%d", &choice) != 1) {
            // Clear input buffer on error
            while (getchar() != '\n');
            printf("Please enter a number.\n");
            sleep(1);
            continue;
        }
        
        // Handle input
        if (choice == 0) {
            // Reset the room
            init_puzzle_room(&room);
            printf("\nPuzzle room reset! New clues generated.\n");
        } else if (choice >= 1 && choice <= NUM_BUTTONS) {
            // Press the selected button
            if (press_button(&room, choice - 1)) {
                printf("\n\n=== PUZZLE SOLVED! ===\n");
                printf("Congratulations! You've solved the puzzle!\n");
                room.solved = 1;
            }
        } else {
            printf("Invalid choice. Please enter a number between 0 and %d.\n", NUM_BUTTONS);
            sleep(1);
        }
    }
    
    printf("Press any key to exit...\n");
    getchar(); // Wait for any key
    
    return 0;
}
