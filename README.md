# Finite State Machine Simulation

This is a simple interactive program where a sprite moves around a screen on a set time
interval. This simulation is modeled by a finite state machine, where each state
represents an action that the sprite can take.

## Compiling

This simulation depends on the `ncurses` library, which can be installed using your system
package manager.

To compile the simulation, run the following command from this directory:

```sh
make simulation
```

To enable debug mode, run the following command instead. This will enable debug log 
messages to be printed to `stderr` when you run the simulation:

```sh
make simulation DEBUG_ENABLED=1
```

## Running

To run the program, simply run the `simulation` executable.

```sh
./simulation 
```

Run with the `--help` option to see available options.

If you compiled with `DEBUG_ENABLED`, then you may want to redirect `stderr` to a log
file to avoid polluting the window with debug messages.

```sh
./simulation 2> debug.log
```

You can view the log in real-time in another terminal window using the following command:

```sh
tail -f debug.log
```

## Controls

When you run the simulation, you will see humanoid sprite appear on your screen. A small
arrow indicates which direction the sprite is facing. The sprite will automatically move
forward on a set time interval.

Use the **arrow keys** to change the direction of the sprites' movement. You will see the
direction indicator change accordingly.

Press the **space key** to make the sprite move immediately.

Press the **q key** to quit the program.


