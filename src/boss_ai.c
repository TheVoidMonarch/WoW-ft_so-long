#include "boss_ai.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdio.h>  // For debug prints

// Personality decay rates (per second)
#define SAVAGERY_DECAY_RATE 0.1f
#define CUNNING_DECAY_RATE 0.05f

// Personality thresholds
#define RAGE_THRESHOLD 0.7f
#define GENIUS_THRESHOLD 0.7f
#define RAGE_DURATION 10.0f
#define GENIUS_DURATION 8.0f

// Move cooldowns (in seconds)
static const float MOVE_COOLDOWNS[] = {
    [MOVE_MELEE_ATTACK] = 1.2f,
    [MOVE_BLOCK] = 0.5f,
    [MOVE_DODGE] = 1.0f,
    [MOVE_RUSH_ATTACK] = 5.0f,
    [MOVE_PARRY] = 3.0f,
    [MOVE_OMEGA_BEAM] = 8.0f,
    [MOVE_AOE_ATTACK] = 10.0f,
    [MOVE_APPROACH] = 0.5f,
    [MOVE_RETREAT] = 0.5f,
    [MOVE_CIRCLE] = 0.5f
};

// Move ranges (min, max distance)
static const float MOVE_RANGES[][2] = {
    [MOVE_MELEE_ATTACK] = {0.0f, 1.5f},
    [MOVE_BLOCK] = {0.0f, 2.0f},
    [MOVE_DODGE] = {0.0f, 3.0f},
    [MOVE_RUSH_ATTACK] = {2.0f, 10.0f},
    [MOVE_PARRY] = {0.0f, 2.0f},
    [MOVE_OMEGA_BEAM] = {3.0f, 20.0f},
    [MOVE_AOE_ATTACK] = {0.0f, 15.0f},
    [MOVE_APPROACH] = {0.0f, 20.0f},
    [MOVE_RETREAT] = {0.0f, 20.0f},
    [MOVE_CIRCLE] = {2.0f, 8.0f}
};

// Personality-based move weights
typedef struct s_personality_weights {
    t_boss_move move;
    float base_weight;
    float savagery_weight;  // How much savagery affects this move
    float cunning_weight;   // How much cunning affects this move
} t_personality_weights;

static const t_personality_weights MOVE_WEIGHTS[] = {
    {MOVE_MELEE_ATTACK, 0.7f, 0.8f, 0.2f},  // High savagery weight
    {MOVE_BLOCK, 0.5f, -0.3f, 0.5f},        // More defensive
    {MOVE_DODGE, 0.6f, -0.2f, 0.7f},        // High cunning weight
    {MOVE_RUSH_ATTACK, 0.8f, 0.9f, 0.4f},   // Very high savagery
    {MOVE_PARRY, 0.6f, 0.1f, 0.9f},         // Very high cunning
    {MOVE_OMEGA_BEAM, 0.7f, 0.5f, 0.8f},    // Balanced but favors cunning
    {MOVE_AOE_ATTACK, 0.9f, 0.7f, 0.6f},    // Balanced but favors savagery
    {MOVE_APPROACH, 0.5f, 0.6f, 0.3f},      // Slight savagery bias
    {MOVE_RETREAT, 0.4f, -0.5f, 0.2f},      // Negative savagery (less likely when enraged)
    {MOVE_CIRCLE, 0.3f, -0.2f, 0.7f}        // High cunning (tactical positioning)
};

// Elemental attack weights based on personality
static const float ELEMENT_WEIGHTS[3][3] = {
    // Fire, Ice, Lightning
    {0.7f, 0.5f, 0.3f},  // Low savagery, low cunning
    {0.4f, 0.6f, 0.5f},  // Medium savagery, medium cunning
    {0.3f, 0.4f, 0.8f}   // High savagery, high cunning
};

// Initialize the boss AI with default values
void init_boss_ai(t_boss_ai *ai) {
    if (!ai) return;
    
    // Initialize move history
    memset(ai->move_history, 0, sizeof(ai->move_history));
    ai->move_count = 0;
    
    // Initialize behavior parameters
    ai->learning_rate = 50;  // Medium learning rate
    ai->aggression = 70;     // Slightly aggressive
    ai->mirroring = 30;      // Some mirroring but not too much
    ai->last_move_time = 0;
    
    // Initialize personality
    ai->boss_state.personality.savagery = 0.0f;
    ai->boss_state.personality.cunning = 0.0f;
    ai->boss_state.personality.rage_threshold = RAGE_THRESHOLD;
    ai->boss_state.personality.genius_threshold = GENIUS_THRESHOLD;
    ai->boss_state.personality.last_rage_time = 0;
    ai->boss_state.personality.last_genius_time = 0;
    ai->boss_state.personality.rage_duration = RAGE_DURATION;
    ai->boss_state.personality.genius_duration = GENIUS_DURATION;
}

// Personality system implementation
void update_personality(t_boss_ai *ai, bool was_hit, bool did_hit) {
    if (!ai) return;
    
    time_t now = time(NULL);
    float delta_time = 1.0f; // Default delta time (will be calculated if needed)
    
    // Update savagery based on damage taken
    if (was_hit) {
        update_savagery(ai, 0.1f); // Increase savagery when hit
    }
    
    // Update cunning based on successful predictions
    if (did_hit) {
        update_cunning(ai, true);
    }
    
    // Apply decay over time
    float decay = delta_time * SAVAGERY_DECAY_RATE;
    ai->boss_state.personality.savagery = fmaxf(0.0f, ai->boss_state.personality.savagery - decay);
    
    decay = delta_time * CUNNING_DECAY_RATE;
    ai->boss_state.personality.cunning = fmaxf(0.0f, ai->boss_state.personality.cunning - decay);
    
    // Check for rage mode
    if (ai->boss_state.personality.savagery >= RAGE_THRESHOLD && 
        now - ai->boss_state.personality.last_rage_time > RAGE_DURATION) {
        ai->boss_state.personality.last_rage_time = now;
    }
    
    // Check for genius mode
    if (ai->boss_state.personality.cunning >= GENIUS_THRESHOLD &&
        now - ai->boss_state.personality.last_genius_time > GENIUS_DURATION) {
        ai->boss_state.personality.last_genius_time = now;
    }
}

void update_savagery(t_boss_ai *ai, float damage_taken) {
    if (!ai) return;
    
    // Increase savagery based on damage taken
    float increase = damage_taken * 0.5f; // Scale factor
    ai->boss_state.personality.savagery = fminf(1.0f, 
        ai->boss_state.personality.savagery + increase);
    
    // If savagery crosses threshold, enter rage mode
    if (ai->boss_state.personality.savagery >= RAGE_THRESHOLD) {
        ai->boss_state.personality.last_rage_time = time(NULL);
    }
}

void update_cunning(t_boss_ai *ai, bool prediction_correct) {
    if (!ai) return;
    
    // Update cunning based on prediction success
    if (prediction_correct) {
        ai->boss_state.personality.cunning = fminf(1.0f, 
            ai->boss_state.personality.cunning + 0.1f);
    } else {
        ai->boss_state.personality.cunning = fmaxf(0.0f, 
            ai->boss_state.personality.cunning - 0.05f);
    }
    
    // If cunning crosses threshold, enter genius mode
    if (ai->boss_state.personality.cunning >= GENIUS_THRESHOLD) {
        ai->boss_state.personality.last_genius_time = time(NULL);
    }
}

float get_savagery_modifier(const t_boss_ai *ai) {
    if (!ai) return 0.0f;
    
    float modifier = ai->boss_state.personality.savagery;
    
    // Boost during rage mode
    if (is_in_rage_mode(ai)) {
        modifier *= 1.5f;
    }
    
    return modifier;
}

float get_cunning_modifier(const t_boss_ai *ai) {
    if (!ai) return 0.0f;
    
    float modifier = ai->boss_state.personality.cunning;
    
    // Boost during genius mode
    if (is_in_genius_mode(ai)) {
        modifier *= 1.3f;
    }
    
    return modifier;
}

bool is_in_rage_mode(const t_boss_ai *ai) {
    if (!ai) return false;
    
    time_t now = time(NULL);
    return (ai->boss_state.personality.savagery >= RAGE_THRESHOLD &&
           (now - ai->boss_state.personality.last_rage_time) < RAGE_DURATION);
}

bool is_in_genius_mode(const t_boss_ai *ai) {
    if (!ai) return false;
    
    time_t now = time(NULL);
    return (ai->boss_state.personality.cunning >= GENIUS_THRESHOLD &&
           (now - ai->boss_state.personality.last_genius_time) < GENIUS_DURATION);
}

// Debug functions
void debug_print_personality(const t_boss_ai *ai) {
    if (!ai) return;
    
    printf("Boss Personality:\n");
    printf("Savagery: %.2f%% (Rage: %s)\n", 
           ai->boss_state.personality.savagery * 100.0f,
           is_in_rage_mode(ai) ? "ACTIVE" : "Inactive");
    printf("Cunning: %.2f%% (Genius: %s)\n", 
           ai->boss_state.personality.cunning * 100.0f,
           is_in_genius_mode(ai) ? "ACTIVE" : "Inactive");
    printf("\n");
}

// Record a player move to the history
void record_player_move(t_boss_ai *ai, t_move_type move) {
    time_t current_time = time(NULL);
    
    // Shift old moves
    if (ai->move_count >= MAX_MOVE_HISTORY) {
        memmove(&ai->move_history[0], &ai->move_history[1], 
               sizeof(t_move) * (MAX_MOVE_HISTORY - 1));
        ai->move_count--;
    }
    
    // Add new move
    ai->move_history[ai->move_count].type = move;
    ai->move_history[ai->move_count].timestamp = current_time;
    ai->move_count++;
    ai->last_move_time = current_time;
}

// Get the frequency of a specific move in the recent time window
float get_move_frequency(t_boss_ai *ai, t_move_type move_type, time_t time_window) {
    if (ai->move_count == 0) return 0.0f;
    
    time_t current_time = time(NULL);
    time_t cutoff_time = current_time - time_window;
    int count = 0;
    int total = 0;
    
    for (size_t i = 0; i < ai->move_count; i++) {
        if (ai->move_history[i].timestamp >= cutoff_time) {
            total++;
            if (ai->move_history[i].type == move_type) {
                count++;
            }
        }
    }
    
    return (total > 0) ? (float)count / total : 0.0f;
}

// Predict the player's next move based on patterns
t_move_type predict_player_move(t_boss_ai *ai) {
    // If we don't have enough data, return a random move
    if (ai->move_count < 3) {
        return (rand() % (MOVE_JUMP + 1));
    }
    
    // Look for recent patterns (last 5 moves)
    int pattern_length = (ai->move_count > 5) ? 5 : ai->move_count;
    int best_match_length = 0;
    t_move_type predicted_move = MOVE_NONE;
    
    // Simple pattern matching - look for repeated sequences
    for (int len = pattern_length - 1; len > 1; len--) {
        int start = ai->move_count - len;
        
        // Look for previous occurrences of this pattern
        for (int i = 0; i <= start - len; i++) {
            int match = 1;
            for (int j = 0; j < len; j++) {
                if (ai->move_history[i + j].type != ai->move_history[start + j].type) {
                    match = 0;
                    break;
                }
            }
            
            // If we found a match, predict the next move in the sequence
            if (match && i + len < (int)ai->move_count) {
                predicted_move = ai->move_history[i + len].type;
                best_match_length = len;
                break;
            }
        }
        
        if (best_match_length > 0) break;
    }
    
    // If no pattern found, use frequency-based prediction
    if (best_match_length == 0) {
        float max_freq = 0;
        
        for (t_move_type move = MOVE_UP; move <= MOVE_JUMP; move++) {
            float freq = get_move_frequency(ai, move, MOVE_WINDOW_MS / 1000);
            if (freq > max_freq) {
                max_freq = freq;
                predicted_move = move;
            }
        }
    }

// Get the boss's next move based on AI
t_boss_move get_boss_move(t_boss_ai *ai) {
    if (!ai) return MOVE_NONE;
    
    t_boss_move move = MOVE_NONE;
    time_t now = time(NULL);
    
    // Check if we can act
    if (now - ai->last_move_time < 0.2f) {
        return MOVE_NONE; // Minimum time between moves
    }
    
    // Evaluate combat state
    t_combat_state state = evaluate_combat_state(ai);
// Update AI behavior based on success/failure
void update_ai_behavior(t_boss_ai *ai, int was_successful) {
    if (was_successful) {
        // If the AI was successful, increase mirroring and aggression slightly
        ai->mirroring = (ai->mirroring + 5 > 100) ? 100 : ai->mirroring + 5;
        ai->aggression = (ai->aggression + 3 > 100) ? 100 : ai->aggression + 3;
    } else {
        // If the AI failed, reduce mirroring and adjust aggression
        ai->mirroring = (ai->mirroring - 10 < 0) ? 0 : ai->mirroring - 10;
        
        // Randomly decide whether to become more or less aggressive
        if (rand() % 2) {
            ai->aggression = (ai->aggression + 10 > 100) ? 100 : ai->aggression + 10;
        } else {
            ai->aggression = (ai->aggression - 5 < 0) ? 0 : ai->aggression - 5;
        }
    }
    
    // Ensure values stay within bounds
    ai->mirroring = (ai->mirroring < 0) ? 0 : (ai->mirroring > 100) ? 100 : ai->mirroring;
    ai->aggression = (ai->aggression < 0) ? 0 : (ai->aggression > 100) ? 100 : ai->aggression;
}
