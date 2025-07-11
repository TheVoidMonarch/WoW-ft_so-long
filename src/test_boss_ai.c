#include "boss_ai.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char* move_to_str(t_move_type move) {
    static const char* move_names[] = {
        "UP   ", "DOWN ", "LEFT ", "RIGHT", 
        "ATTACK", "BLOCK", "JUMP ", "NONE "
    };
    return (move >= MOVE_UP && move <= MOVE_NONE) ? move_names[move] : "UNKNOWN";
}

void print_game_state(t_boss_ai *ai, t_move_type player_move, t_move_type boss_move, int round) {
    printf("\n=== ROUND %d ===\n", round);
    printf("Player's move: %s\n", move_to_str(player_move));
    printf("Boss's move:   %s\n", move_to_str(boss_move));
    
    // Calculate success (simple rock-paper-scissors logic)
    int player_wins = 0;
    if ((player_move == MOVE_ATTACK && boss_move == MOVE_BLOCK) ||
        (player_move == MOVE_BLOCK && boss_move == MOVE_ATTACK)) {
        printf("Boss blocked the attack!\n");
    } else if (player_move == MOVE_ATTACK && boss_move != MOVE_BLOCK) {
        printf("Player hits the boss!\n");
        player_wins = 1;
    } else if (boss_move == MOVE_ATTACK && player_move != MOVE_BLOCK) {
        printf("Boss hits the player!\n");
        player_wins = -1;
    } else {
        printf("No effect.\n");
    }
    
    // Update AI behavior based on success
    update_ai_behavior(ai, (player_wins <= 0));
    
    printf("\nBoss AI State:\n");
    printf("Learning: %d%%, Aggression: %d%%, Mirroring: %d%%\n", 
           ai->learning_rate, ai->aggression, ai->mirroring);
    
    // Show move history (last 5 moves)
    printf("\nLast 5 moves: ");
    int start = (ai->move_count > 5) ? ai->move_count - 5 : 0;
    for (size_t i = start; i < ai->move_count; i++) {
        printf("%s ", move_to_str(ai->move_history[i].type));
    }
    printf("\n");
}

int main() {
    t_boss_ai ai;
    init_boss_ai(&ai);
    
    printf("=== DARK LINK BOSS BATTLE ===\n");
    printf("Commands: w=UP, s=DOWN, a=LEFT, d=RIGHT, j=JUMP, k=ATTACK, l=BLOCK, q=QUIT\n");
    printf("The boss will learn from your moves and adapt its strategy!\n\n");
    
    int round = 1;
    char input;
    t_move_type player_move, boss_move;
    
    while (1) {
        // Clear screen
        printf("\033[H\033[J");
        
        // Get player input
        printf("Your move (wasd-jkl): ");
        scanf(" %c", &input);
        
        // Convert input to move
        switch (input) {
            case 'w': player_move = MOVE_UP; break;
            case 's': player_move = MOVE_DOWN; break;
            case 'a': player_move = MOVE_LEFT; break;
            case 'd': player_move = MOVE_RIGHT; break;
            case 'j': player_move = MOVE_JUMP; break;
            case 'k': player_move = MOVE_ATTACK; break;
            case 'l': player_move = MOVE_BLOCK; break;
            case 'q': return 0;
            default: 
                printf("Invalid move! Use wasd to move, j to jump, k to attack, l to block.\n");
                sleep(1);
                continue;
        }
        
        // Record player move and get boss move
        record_player_move(&ai, player_move);
        boss_move = get_boss_move(&ai);
        
        // Print game state
        print_game_state(&ai, player_move, boss_move, round);
        
        // Wait for next round
        printf("\nPress Enter to continue...");
        while (getchar() != '\n'); // Clear input buffer
        getchar(); // Wait for Enter
        
        round++;
    }
    
    return 0;
}
