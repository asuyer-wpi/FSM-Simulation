---
aliases:
  - FSM-simulation-project
---
# Final Project: Planning

ECE 2039 - C01
Andrew Suyer

## The Program

I will be creating a simple interactive program where a sprite moves around a screen. The sprite will move forward one step at a time on a set time interval. The user can change the direction of motion using the arrow keys and can manually cause the sprite to move by pressing the space key.

The user interface will be quite simple. It will be a large blank terminal window with a single glyph representing the sprite. The sprite will progress forward one character width at a time in the direction that it's facing. If time allows, I can implement some more elaborate features, such as sprites that are made up of multiple glyphs, or symbols that indicate which direction the sprite is facing (see below).

```
  O
 /|\ ->
  |
 / \
```


## State Machine

My state machine will have the following states:
- **Ready**: The sprite is ready to move and is waiting for the next time step or the space key to be pressed 
- **Move Forward**: Upon transitioning to this state, the sprite will move forward one step in the direction its facing then switch back to the Ready state.
- **Change Direction**: Upon transitioning to this state, the sprite will change the direction its facing then switch back to the Ready state.

The state diagram is as shown:

![State machine](State-machine.png)

A state machine is a natural model for this program since each state represents an *action* that the sprite takes.

## Development plan

### Milestone 1

**Due**: Wednesday 3/4/26 at midnight.

**Working features**:
- [ ] Program compiles successfully with `make`
- [ ] Program successfully creates a window using `ncurses`
- [ ] A glyph representing the sprite is rendered on screen
- [ ] Program supports the `-h` / `--help` command line option
- [ ] Global variables exist for sprite position and direction
- [ ] If `q` key is pressed, program terminates gracefully

**Tests**:
- Compiling with `make` succeeds without errors
- When `-h` / `--help` is passed to the program, it prints the help message (without rendering the window)
- When the program is run without arguments:
    - The program takes up the entire terminal window
    - A sprite character is position on the window at the coordinates specified by the `position` global variable
    - If `q` key is pressed, program terminates gracefully

### Milestone 2

**Due**: Friday 3/6/26 at midnight.

**Working features**:
- [ ] Sprite automatically moves forward on a set time interval
- [ ] User can cause sprite to move forward with space key
- [ ] User can change sprite direction with arrow keys
- [ ] Program supports setting a custom time interval using command line arguments
- [ ] Finish reflection write-up

**Tests**:
- All the tests from milestone 1
- While the program is running:
    - Without any user input, the sprite moves slowly in one direction
    - Pressing the space key causes the sprite to move immediately
        - Should also reset the timer, so sprite should not move on its own until one full time step after the space key is pressed
    - Pressing an arrow key causes the next movement to be in the direction chosen
- Run the program with different time interval arguments (e.g., 0.5s, 0.1s) and verify that it works
