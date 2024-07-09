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

