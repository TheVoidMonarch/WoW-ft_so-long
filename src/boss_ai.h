#ifndef BOSS_AI_H
# define BOSS_AI_H

# include <stddef.h>
# include <time.h>
# include <stdbool.h>

// Maximum number of moves to remember
# define MAX_MOVE_HISTORY 50
# define MOVE_WINDOW_MS 3000  // Time window for move prediction (ms)
# define PHASE2_HP_THRESHOLD 0.5f  // 50% HP triggers phase 2

// Boss move types for phase 2
typedef enum {
    // Phase 1 moves (Dark Link style)
    MOVE_MELEE_ATTACK,    // Basic sword attack
    MOVE_BLOCK,           // Block incoming attacks
    MOVE_DODGE,           // Quick dodge/roll
    
    // Phase 2 moves
    MOVE_RUSH_ATTACK,     // Charge at player
    MOVE_PARRY,           // Parry and counterattack
    MOVE_OMEGA_BEAM,      // Tracking projectile attack
    MOVE_AOE_ATTACK,      // Elemental AOE attack
    
    // Movement (shared)
    MOVE_APPROACH,        // Move toward player
    MOVE_RETREAT,         // Move away from player
    MOVE_CIRCLE,          // Circle around player
    
    MOVE_NONE
} t_boss_move;

// Elemental types for AOE attacks
typedef enum {
    ELEMENT_FIRE,    // Stuns player (0.7s)
    ELEMENT_ICE,     // Freezes player (0.2-1.3s)
    ELEMENT_LIGHTNING // Disarms player (0.3s)
} t_element_type;

// Player state tracking
typedef struct s_player_state {
    float health;              // 0.0 to 1.0
    float distance;            // Distance from boss
    bool is_attacking;         // Is player currently attacking?
    bool is_blocking;          // Is player blocking?
    bool is_stunned;           // Is player stunned?
    bool is_immune;            // Is player in iframes?
    time_t last_hit_time;      // When was player last hit?
    int consecutive_hits;      // Number of consecutive hits on player
    int damage_taken;          // Total damage taken in this phase
}               t_player_state;

// Personality metrics
typedef struct s_boss_personality {
    float savagery;            // 0.0 to 1.0 - increases with damage taken
    float cunning;             // 0.0 to 1.0 - increases with successful predictions
    float rage_threshold;      // 0.7 - when savagery exceeds this, enter rage mode
    float genius_threshold;    // 0.7 - when cunning exceeds this, enter genius mode
    time_t last_rage_time;     // When rage was last triggered
    time_t last_genius_time;   // When genius mode was last triggered
    int rage_duration;         // How long rage lasts (seconds)
    int genius_duration;       // How long genius mode lasts (seconds)
} t_boss_personality;

// Boss state tracking
typedef struct s_boss_state {
    // Core state
    float health;              // 0.0 to 1.0
    float phase;               // 1.0 = phase 1, 2.0 = phase 2
    bool is_attacking;         // Is boss currently attacking?
    bool is_vulnerable;        // Can boss be damaged?
    t_boss_move last_move;     // Last move used
    
    // Phase tracking
    int phase2_entered;        // Has phase 2 started? (0=no, 1=yes)
    
    // Cooldowns
    time_t last_aoe_time;      // When was last AOE used?
    time_t last_rush_time;     // When was last rush attack?
    time_t last_parry_time;    // When was last parry?
    time_t last_hit_time;      // When was boss last hit?
    time_t last_hit_player;    // When did boss last hit player?
    
    // Combat metrics
    int consecutive_misses;    // Number of consecutive missed attacks
    int consecutive_hits;      // Number of consecutive hits on player
    float time_since_last_hit; // Seconds since last hit player
    
    // Personality
    t_boss_personality personality;
} t_boss_state;

// Move history for pattern recognition
typedef struct s_move_history {
    t_boss_move  move;
    time_t       timestamp;
    bool         was_successful;
}              t_move_history;

typedef struct s_boss_ai {
    // Core AI state
    t_move_history move_history[MAX_MOVE_HISTORY];
    size_t         move_count;
    
    // Behavior parameters (0-100)
    int aggression;         // How aggressive the AI is
    int caution;            // How defensive the AI is
    int adaptability;       // How quickly AI adapts to player
    
    // Phase 2 specific
    t_element_type last_element_used;  // For AOE attacks
    int phase2_transition;  // 0=not started, 1=in progress, 2=complete
    
    // Cooldowns
    time_t last_move_time;
    time_t last_aoe_time;
    time_t last_rush_time;
    time_t last_parry_time;
    
    // State tracking
    t_boss_state boss_state;
    t_player_state player_state;
    
    // Move weights (probability adjustments)
    float move_weights[10]; // Indexed by t_boss_move enum
    
} t_boss_ai;

// Initialize the boss AI system
void init_boss_ai(t_boss_ai *ai);

// Update AI with current game state
void update_ai_state(t_boss_ai *ai, t_boss_state *boss, t_player_state *player);

// Get the boss's next move based on AI
t_boss_move get_boss_move(t_boss_ai *ai);

// Handle phase transition (when boss reaches 50% HP)
void handle_phase_transition(t_boss_ai *ai);

// Phase 1: Dark Link style (mirroring player)
t_boss_move get_phase1_move(t_boss_ai *ai);

// Phase 2: Elemental Lord style (advanced moves)
t_boss_move get_phase2_move(t_boss_ai *ai);

// Calculate move desirability score (0.0-1.0)
float calculate_move_score(t_boss_ai *ai, t_boss_move move);

// Apply move cooldowns and update internal state
void finalize_move_selection(t_boss_ai *ai, t_boss_move move);

// Update AI behavior based on success/failure of last move
void update_ai_behavior(t_boss_ai *ai, bool was_successful);

// Get a random elemental type for AOE attacks
t_element_type get_random_element();

// Get stun duration for an elemental effect (in seconds)
float get_element_stun_duration(t_element_type element, float player_input);

// Check if a move is available (off cooldown)
bool is_move_available(t_boss_ai *ai, t_boss_move move);

// Calculate distance-based move weights
void update_distance_weights(t_boss_ai *ai);

// Update move weights based on player state
void update_player_state_weights(t_boss_ai *ai);

// Reset cooldowns for phase transition
void reset_cooldowns(t_boss_ai *ai);

// Get move cooldown in seconds
float get_move_cooldown(t_boss_move move);

// Get move range (min/max distance)
void get_move_range(t_boss_move move, float *min_dist, float *max_dist);

// Check if player is in range for a move
bool is_player_in_range(t_boss_ai *ai, t_boss_move move);

// Get move priority (0.0-1.0) based on current state
float get_move_priority(t_boss_ai *ai, t_boss_move move);

// Personality system
void update_personality(t_boss_ai *ai, bool was_hit, bool did_hit);
void update_savagery(t_boss_ai *ai, float damage_taken);
void update_cunning(t_boss_ai *ai, bool prediction_correct);
float get_savagery_modifier(const t_boss_ai *ai);
float get_cunning_modifier(const t_boss_ai *ai);
bool is_in_rage_mode(const t_boss_ai *ai);
bool is_in_genius_mode(const t_boss_ai *ai);

// Move selection weights based on personality
typedef struct s_move_weights {
    t_boss_move move;
    float base_weight;
    float savagery_weight;  // How much savagery affects this move
    float cunning_weight;   // How much cunning affects this move
} t_move_weights;

// Combat state evaluation
typedef enum {
    COMBAT_STATE_NEUTRAL,
    COMBAT_STATE_AGGRESSIVE,
    COMBAT_STATE_DEFENSIVE,
    COMBAT_STAGE_EVASIVE,
    COMBAT_STATE_DESPERATE
} t_combat_state;

t_combat_state evaluate_combat_state(const t_boss_ai *ai);
bool should_use_desperate_move(const t_boss_ai *ai);

// Move selection
void select_attack_pattern(t_boss_ai *ai);
t_boss_move select_best_move(const t_boss_ai *ai, const t_move_weights *weights, size_t count);

// Move patterns
typedef struct s_move_pattern {
    t_boss_move moves[5];  // Up to 5 moves in a pattern
    size_t count;          // Number of moves in pattern
    float weight;          // Base weight of this pattern
} t_move_pattern;

void execute_move_pattern(t_boss_ai *ai, const t_move_pattern *pattern);

// Elemental attacks
t_element_type select_elemental_attack(const t_boss_ai *ai);
void apply_elemental_effect(t_boss_ai *ai, t_element_type element);

// Adaptive learning
typedef struct s_player_pattern {
    t_boss_move sequence[3];  // Last 3 player moves
    t_boss_move likely_next;  // Most likely next move
    int confidence;           // 0-100 confidence in prediction
} t_player_pattern;

void update_player_patterns(t_boss_ai *ai, t_boss_move player_move);
t_boss_move predict_player_move(const t_boss_ai *ai);

// Debug
void debug_print_ai_state(const t_boss_ai *ai);
void debug_print_personality(const t_boss_ai *ai);

#endif
