#include "puzzle_room.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Initialize the puzzle room with a random solution and clues
void init_puzzle_room(t_puzzle_room *room) {
    // Seed the random number generator
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    // Reset all buttons to unpressed (0)
    for (int i = 0; i < NUM_BUTTONS; i++) {
        room->buttons[i] = 0;
    }

    // Generate a random solution (1-4 for each button)
    for (int i = 0; i < NUM_BUTTONS; i++) {
        room->solution[i] = (rand() % 4) + 1; // Numbers 1-4
    }

    // Generate clues based on the solution
    generate_clues(room);
    
    // Reset solved state
    room->solved = 0;
}

// Handle button press
int press_button(t_puzzle_room *room, int button_index) {
    if (button_index < 0 || button_index >= NUM_BUTTONS) {
        return 0; // Invalid button
    }
    
    // Toggle button state (0 or 1)
    room->buttons[button_index] = !room->buttons[button_index];
    
    // Check if the current combination is correct
    if (check_solution(room)) {
        room->solved = 1;
        return 1; // Puzzle solved!
    }
    
    return 0; // Puzzle not solved yet
}

// Check if current button combination matches solution
int check_solution(t_puzzle_room *room) {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        // For this example, let's say the solution is when buttons match
        // the even/odd pattern of the solution numbers
        int expected_state = (room->solution[i] % 2);
        if (room->buttons[i] != expected_state) {
            return 0; // Incorrect
        }
    }
    return 1; // Correct!
}

// Generate random clues based on the solution
void generate_clues(t_puzzle_room *room) {
    const char *clue_templates[NUM_STELES] = {
        "The %s button must be %s",
        "Press the %s button %s",
        "The %s symbol should be %s",
        "Only the %s needs to be %s"
    };
    
    const char *button_names[NUM_BUTTONS] = {"red", "blue", "green", "yellow"};
    const char *states[2] = {"pressed", "unpressed"};
    
    for (int i = 0; i < NUM_STELES; i++) {
        int button_idx = i % NUM_BUTTONS;
        int expected_state = room->solution[button_idx] % 2;
        
        // Format the clue
        snprintf(room->clues[i], MAX_CLUE_LENGTH, 
                clue_templates[i], 
                button_names[button_idx],
                states[expected_state]);
    }
}

// Helper function to shuffle an array (Fisher-Yates algorithm)
void shuffle_array(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
