#ifndef PUZZLE_ROOM_H
# define PUZZLE_ROOM_H

# define NUM_BUTTONS 4
# define NUM_STELES 4
# define MAX_CLUE_LENGTH 100

typedef struct s_puzzle_room {
    int     buttons[NUM_BUTTONS];      // Button states (pressed/unpressed)
    int     solution[NUM_BUTTONS];     // Current solution combination
    char    clues[NUM_STELES][MAX_CLUE_LENGTH]; // Clues on the steles
    int     solved;                    // Is the puzzle solved?
}               t_puzzle_room;

// Initialize the puzzle room with random solution and clues
void    init_puzzle_room(t_puzzle_room *room);

// Handle button press (returns 1 if puzzle is solved, 0 otherwise)
int     press_button(t_puzzle_room *room, int button_index);

// Check if current button combination matches solution
int     check_solution(t_puzzle_room *room);

// Generate random clues based on the solution
void    generate_clues(t_puzzle_room *room);

// Helper function to shuffle an array
void    shuffle_array(int *array, int size);

#endif
