/*
 * Copyright (C) 2026
 * Created by asuyer-wpi, asuyer@wpi.edu
 */

#include <curses.h>
#include <getopt.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Helpful macro for printing debug messages when compiled with -DDEBUG
#ifdef DEBUG
#include <stdio.h>
#define DEBUG_PRINTF(...)                                  \
    fprintf(stderr, "DEBUG: %s:%d: ", __FILE__, __LINE__); \
    fprintf(stderr, __VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif

/// The states of the state machine
typedef enum
{
    READY,
    MOVE_FORWARD,
    CHANGE_DIRECTION,
    EXIT,
} machine_state_t;

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
} direction_t;

typedef struct
{
    int xpos;
    int ypos;
    direction_t direction_facing;
} sprite_state_t;

// ----- Global State ----- //

/// The current state of the machine
static machine_state_t g_current_state;

/// The next state to transition to
static machine_state_t g_next_state;

/// The next direction for the sprite to face
static direction_t g_next_direction;

/// The timestep of the simulation
static float g_timestep = 1;

/// Current state of the sprite
static sprite_state_t g_current_sprite_state;

// ----- Init functions ----- //

/// Prints the program usage using `program` as the invocation command.
void print_usage(char const* program);

/// Sets the simulation timestep to `seconds` seconds.
void set_timestep(float seconds);

/// Initializes ncurses
void init_ncurses();

void init_states();

// ----- Game loop functions ----- //

/// Handle the input `key` pressed
void handle_input(int key);

/// Updates the state of the machine
void update(float delta_time);

/// Renders the updated state to the screen
void render();

// ----- State functions ----- //

/// Update the position of the sprite to move forward one step in the direction its facing
void move_forward();

/// Update the direction which the sprite is facing
void change_direction();

/// Exit the program, uninitializing ncurses in the process;
void exit_program();

/// Draws the sprite on screen
void draw_sprite();

int main(int argc, char* argv[])
{
    // Define allowed options
    static struct option long_options[] = { { "help", no_argument, NULL, 'h' },
                                            { "timestep", required_argument, NULL, 't' },
                                            { 0, 0, 0, 0 } };

    // Iterate over the command line arguments
    int opt_val;
    while ((opt_val = getopt_long(argc, argv, "ht:", long_options, NULL)) != -1)
    {
        float seconds;
        switch (opt_val)
        {
        case 'h':
            print_usage(argv[0]);
            return EXIT_SUCCESS;
        case 't':
            seconds = atof(optarg);
            set_timestep(seconds);
            break;
        case '?':
            break;
        default:
            abort();
        }
    }

    // Setup ncurses and states
    init_ncurses();
    init_states();

    /// Stores the time of the last iteration
    struct timespec last_time;
    clock_gettime(CLOCK_MONOTONIC, &last_time);

    // Start game loop
    while (1)
    {
        struct timespec current_time;
        clock_gettime(CLOCK_MONOTONIC, &current_time);

        // Handle input key
        int key = getch();
        handle_input(key);

        // Get the number of seconds that has elapsed since the last iteration
        double seconds_elapsed = (current_time.tv_sec - last_time.tv_sec)
          + (current_time.tv_nsec - last_time.tv_nsec) / 1e9;

        update(seconds_elapsed);
        render();

        last_time = current_time;
    }

    return EXIT_SUCCESS;
}

// ----- Init functions ----- //

void print_usage(char const* program)
{
    printf("Usages:\n\t%s [-h|--help]\n\t%s [-t|--timestep timestep]\n\n", program, program);
    printf("Options:\n");
    printf("\t-h|--help: shows this help message\n");
    printf("\t-t|--timestep: sets the timestep to `timestep` seconds\n");
}

void set_timestep(float seconds)
{
    DEBUG_PRINTF("Setting timestep to %f seconds\n", seconds);
    g_timestep = seconds;
}

void init_ncurses()
{
    DEBUG_PRINTF("Initializing ncurses\n");
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    set_escdelay(0);
    curs_set(0);  // Make the cursor invisible
}

void init_states()
{
    DEBUG_PRINTF("Initializing states\n");
    g_current_state = READY;
    g_next_state = READY;
    g_next_direction = RIGHT;
    g_current_sprite_state.xpos = 5;
    g_current_sprite_state.ypos = 5;
    g_current_sprite_state.direction_facing = RIGHT;
}

// ----- Game loop functions ----- //

void handle_input(int key)
{
    switch (key)
    {
    case ' ':  // space key
        g_next_state = MOVE_FORWARD;
        break;
    case 'q':
        g_next_state = EXIT;
        break;
    case KEY_LEFT:
        g_next_state = CHANGE_DIRECTION;
        g_next_direction = LEFT;
        break;
    case KEY_RIGHT:
        g_next_state = CHANGE_DIRECTION;
        g_next_direction = RIGHT;
        break;
    case KEY_UP:
        g_next_state = CHANGE_DIRECTION;
        g_next_direction = UP;
        break;
    case KEY_DOWN:
        g_next_state = CHANGE_DIRECTION;
        g_next_direction = DOWN;
        break;
    }
}

void update(float delta_time)
{
    static float elapsed_time = 0;
    elapsed_time += delta_time;

    g_current_state = g_next_state;
    switch (g_current_state)
    {
    case READY:
        if (elapsed_time < g_timestep)
        {
            break;
        }
        // If elapsed time is greater than the timestep, fall into MOVE_FORWARD state
    case MOVE_FORWARD:
        move_forward();
        elapsed_time = 0;
        break;
    case CHANGE_DIRECTION:
        change_direction();
        break;
    case EXIT:
        exit_program();
        break;
    }
}

void render()
{
    erase();
    draw_sprite();
    refresh();
}

// ----- State functions ----- //

void move_forward()
{
    switch (g_current_sprite_state.direction_facing)
    {
    case UP:
        g_current_sprite_state.ypos -= 1;
        break;
    case DOWN:
        g_current_sprite_state.ypos += 1;
        break;
    case LEFT:
        g_current_sprite_state.xpos -= 2;
        break;
    case RIGHT:
        g_current_sprite_state.xpos += 2;
        break;
    }
    g_next_state = READY;
}

void change_direction()
{
    DEBUG_PRINTF("Changing direction to %d\n", g_next_direction);
    g_current_sprite_state.direction_facing = g_next_direction;
    g_next_state = READY;
}

void exit_program()
{
    DEBUG_PRINTF("Quitting\n");
    endwin();
    exit(EXIT_SUCCESS);
}

void draw_sprite()
{
    mvaddstr(g_current_sprite_state.ypos, g_current_sprite_state.xpos, " O ");
    mvaddstr(g_current_sprite_state.ypos + 1, g_current_sprite_state.xpos, "/|\\");
    mvaddstr(g_current_sprite_state.ypos + 2, g_current_sprite_state.xpos, " | ");
    mvaddstr(g_current_sprite_state.ypos + 3, g_current_sprite_state.xpos, "/ \\");

    // Draw the direction indicator
    switch (g_current_sprite_state.direction_facing)
    {
    case UP:
        mvaddstr(g_current_sprite_state.ypos - 2, g_current_sprite_state.xpos + 1, "|");
        mvaddstr(g_current_sprite_state.ypos - 3, g_current_sprite_state.xpos + 1, "^");
        break;
    case DOWN:
        mvaddstr(g_current_sprite_state.ypos + 5, g_current_sprite_state.xpos + 1, "|");
        mvaddstr(g_current_sprite_state.ypos + 6, g_current_sprite_state.xpos + 1, "v");
        break;
    case LEFT:
        mvaddstr(g_current_sprite_state.ypos + 1, g_current_sprite_state.xpos - 4, "<-");
        break;
    case RIGHT:
        mvaddstr(g_current_sprite_state.ypos + 1, g_current_sprite_state.xpos + 5, "->");
        break;
    }
}
