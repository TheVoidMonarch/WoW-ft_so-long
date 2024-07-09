# WoW ft_so-long
 A 42 School project that started delving into graphic and game development


### Files Needed:

1. **game.h** - Header file defining game structures, enums, and function prototypes.
2. **main.c** - Main entry point of the program.
3. **init.c** - Initialization functions for game entities (player, rooms, puzzles, etc.).
4. **render.c** - Functions for rendering game elements.
5. **input.c** - Handling user input.
6. **update.c** - Updating game state based on user input and time.
7. **boss.c** - Logic and behavior for the boss enemy, including Dead Man's Volley.
8. **puzzle.c** - Logic and behavior for puzzles and interactive elements.
9. **rooms.c** - Initialization and handling of different types of rooms.
10. **player.c** - Player-specific functionality (movement, actions, inventory, etc.), including hotkey healing.
11. **spawn.c** - Handling spawning of items or enemies.
12. **maps.c** - Loading and managing game maps or levels.
13. **ui.c** - Implementation of user interface elements (health bars, dialog boxes, etc.).
14. **camera.c** - Managing camera movement and viewports.

### Concepts and Features:

1. **Game Initialization and Structures**:
   - Define structures like `Player`, `Boss`, `Puzzle`, `Room`, etc., in `game.h`.
   - Implement initialization functions (`init_game`, `init_player`, `init_boss`, etc.) in `init.c`.

2. **Rendering**:
   - Implement rendering functions (`render_game`, `render_player`, `render_boss`, etc.) in `render.c`.
   - Utilize graphics libraries like `mlx` for rendering if using C graphics.

3. **User Input Handling**:
   - Implement functions (`handle_input`, `handle_player_input`, etc.) in `input.c`.

4. **Game State Updates**:
   - Implement update functions (`update_game`, `update_player`, `update_boss`, etc.) in `update.c`.

5. **Boss and Puzzle Mechanics**:
   - Implement boss behavior, attacks, and Dead Man's Volley mechanics in `boss.c`.
   - Implement puzzle solving mechanics in `puzzle.c`.

6. **Room Management**:
   - Define different room types (`ROOM_PUZZLE`, `ROOM_BOSS`, etc.) and their initialization in `rooms.c`.
   - Handle room transitions and interactions.

7. **Player Actions**:
   - Define player movement, actions (attacking, interacting), inventory handling, and hotkey healing in `player.c`.

8. **Item Spawning**:
   - Implement functions for spawning items or enemies in `spawn.c`.

9. **Map Management**:
   - Load and manage game maps or levels using `maps.c`.

10. **User Interface**:
    - Implement UI elements such as health bars, dialog boxes, and inventory displays in `ui.c`.

11. **Camera and Viewport Management**:
    - Implement camera movement and viewport management functions in `camera.c` for scrolling and maintaining focus.

### Project Management:

- **Modular Design**: Keep each functionality isolated in its respective file for easier debugging and maintenance.
- **Documentation**: Add comments and documentation within your code to explain complex logic or algorithms.
- **Testing**: Test each component incrementally to ensure they work as expected before integrating them into the main game loop.
- **Refinement**: Fine-tune gameplay mechanics and balance based on testing feedback.

### Additional Considerations:

- **Dialog System**: Implement dialog boxes or text displays within `ui.c` or a dedicated file for managing dialogs.
- **Inventory System**: Simplify as a hotkey healing feature in `player.c`, eliminating the need for a separate inventory system.
