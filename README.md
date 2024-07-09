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

### Header Files Needed:

Here's a simplified example of how you might structure your project with header files for each `.c` file:

- **game.h**: Main header file defining game-wide structures (`Game`, `Room`, `Player`, etc.) and core function prototypes (`init_game`, `update_game`, `render_game`, etc.).

- **player.h**: Header file defining player-related structures (`Player`, `Inventory`, etc.) and function prototypes (`init_player`, `update_player`, `handle_player_input`, etc.).

- **boss.h**: Header file defining boss-related structures (`Boss`, `BossAttack`, etc.) and function prototypes (`init_boss`, `update_boss`, `handle_boss_room`, etc.).

- **puzzle.h**: Header file defining puzzle-related structures (`Puzzle`, `Button`, etc.) and function prototypes (`init_puzzle`, `handle_puzzle_room`, etc.).

- **room.h**: Header file defining room-related structures (`Room`, `Door`, etc.) and function prototypes (`init_room`, `handle_room_events`, etc.).

- **render.h**: Header file defining rendering-related function prototypes (`render_game`, `render_player`, `render_boss`, `render_ui`, etc.).

- **input.h**: Header file defining input-related function prototypes (`handle_input`, `handle_player_input`, `handle_puzzle_input`, etc.).

- **spawn.h**: Header file defining spawning-related function prototypes (`spawn_key`, `spawn_enemy`, etc.).

- **maps.h**: Header file defining map-related function prototypes (`load_map`, `generate_map`, etc.).

- **ui.h**: Header file defining UI-related structures (`UIElement`, `DialogBox`, `HealthBar`, etc.) and function prototypes (`render_dialog`, `render_health_bar`, etc.).

- **camera.h**: Header file defining camera-related structures (`Camera`, `Viewport`, etc.) and function prototypes (`update_camera`, `set_camera_position`, etc.).

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

### Task 1: Setting up the project structure

Create a new project directory and create the necessary subdirectories for each component (e.g., src, include, assets, etc.).
Create the necessary header files (.h) and source files (.c) according to your provided structure.

### Task 2: Defining game structures and function prototypes

In game.h, define the game-wide structures (e.g., Game, Room, Player, etc.) and core function prototypes (e.g., init_game, update_game, render_game, etc.).
In each respective header file (e.g., player.h, boss.h, puzzle.h, etc.), define the corresponding structures and function prototypes.

### Task 3: Implementing initialization functions

In init.c, implement the initialization functions for game entities (e.g., init_game, init_player, init_boss, etc.).

### Task 4: Implementing rendering functions

In render.c, implement the rendering functions (e.g., render_game, render_player, render_boss, etc.) using MiniLibX.

### Task 5: Handling user input

In input.c, implement functions for handling user input (e.g., handle_input, handle_player_input, etc.).

### Task 6: Updating game state

In update.c, implement update functions (e.g., update_game, update_player, update_boss, etc.) based on user input and time.

### Task 7: Implementing boss and puzzle mechanics

In boss.c, implement boss behavior, attacks, and Dead Man's Volley mechanics.
In puzzle.c, implement puzzle solving mechanics.

### Task 8: Room management

In rooms.c, define different room types (e.g., ROOM_PUZZLE, ROOM_BOSS, etc.) and their initialization.
Handle room transitions and interactions.

### Task 9: Player actions and inventory

In player.c, implement player movement, actions (attacking, interacting), inventory handling, and hotkey healing.

### Task 10: Item spawning

In spawn.c, implement functions for spawning items or enemies.

### Task 11: Map management

In maps.c, load and manage game maps or levels.

### Task 12: User interface

In ui.c, implement UI elements such as health bars, dialog boxes, and inventory displays.

### Task 13: Camera and viewport management

In camera.c, implement camera movement and viewport management functions for scrolling and maintaining focus.

### Additional Considerations:

- **Dialog System**: Implement dialog boxes or text displays within `ui.c` or a dedicated file for managing dialogs.
- **Inventory System**: Simplify as a hotkey healing feature in `player.c`, eliminating the need for a separate inventory system.

### Evaluation Conditions
MANDATORY PART
--------------

Executable name
---------------
Check that the project compiles well (without re-link) when you execute
the `make` command and that the executable name is `so_long`.
If not use the invalid compilation flag at the end of the scale.

Map reading
-----------
- use different maps.
- test with different sizes.
- test with different line sizes.

Also, check that the program returns an error and exits properly when
the configuration file is misconfigured (for example an unknown key,
double keys, an invalid path..).

If not, the defense is over and use the appropriate flag incomplete
work, crash...

Technical elements of the display
---------------------------------
We're going to evaluate the technical elements of the display.
Check that the level is a valid representation of the map used as
parameter.
- A window must open at the launch of the program.
It must stay open during the whole execution.

- Hide all or part of the window either by using another window
or by using the screen's borders, then minimize the windows
and maximize it back. In all cases, the content of the window
must remain consistent.

User basic events
-----------------
In this section, we're going to evaluate the program's user
generated events. Execute the 3 following tests. If at least one
fails, this means that no points will be awarded for this section.

Move to the next one.
---------------------
- Click the red cross at the top left of the window. The
window must close and the program must exit cleanly.

- Press the ESC key. The window must close and the program
must exit cleanly. In the case of this test, we will accept
that another key exits the program, for example, Q.

- Press the four arrow keys (we'll accept WASD or ZQSD keys)
in the order of your liking. Each key press must render a
visible result on the window(player's movement).

Movements
---------
In this section, we'll evaluate the implementation of the player's
movement. Execute the 5 following tests. If at least one fails, this
means that no points will be awarded for this section.

Move to the next one.
---------------------
- The player's spawning position must be in accordance with the map file.

- Press the arrows keys to move in every direction on the map.

- is the game "playable"?

Walls & Sprites
---------------
In this section, we'll evaluate the map representation.
Execute the following tests. If at least one
fails, this means that no points will be awarded for this section.

Move to the next one.
---------------------
- The wall's texture is well placed and the player cannot go through it.

- The collectible's texture is well placed and the player can pick it by
  walking on it.

- The Exit texture is well placed and the player can finish the game by
  walking on it but only after picking every collectible.

- The player texture is well placed and can move in every direction
  except into the walls.

Counter
-------
In this section, we'll evaluate the gameplay elements.
Execute the following tests. If at least one
fails, this means that no points will be awarded for this section.
Move to the next one.

- There's a small counter displayed on the shell that counts how many
  movements the player did.
- The counter can be displayed directly on the game screen (see bonus
  part).

Image usage
-----------
The program use mlx_put_image_to_window and not mlx put pixel!


BONUS
-----
We will look at your bonuses if and only if your mandatory part is
excellent. This means that you must complete the mandatory part,
beginning to end, and your error management must be flawless, even in
cases of twisted or bad usage. So if the mandatory part didn't score all
the points during this defense bonuses will be totally ignored.

Enemies
-------
enemy patrols that cause the player to lose in case of contact.

Draw calls
----------
There's some sprite animation.
You need to explain what it is and how you did it.
Rate it from 0 (failed) through 5 (excellent)

GUI
---
The counter of movement is rendered on the screen using texture or
mlx_string_put.

