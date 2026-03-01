/*
 * Copyright (C) 2026
 * Created by asuyer-wpi, asuyer@wpi.edu
 */

#include <getopt.h>
#include <ncursesw/ncurses.h>
// #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Helpful macro for printing debug messages when compiled with -DDEBUG
#ifdef DEBUG
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
} state_t;

/// The current state of the machine
static state_t g_current_state = READY;

/// The timestep of the simulation
static float g_timestep = 1;

/// Prints the program usage using `program` as the invocation command.
void print_usage(char const* program);

/// Sets the simulation timestep to `seconds` seconds.
void set_timestep(float seconds);

/// Initializes ncurses
void init_ncurses();

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

    // Setup ncurses
    init_ncurses();

    /// Stores the time of the last state transition.
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    g_current_state = READY;

    // Start game loop
    while (1)
    {
        struct timespec elapsed_time;
        clock_gettime(CLOCK_MONOTONIC, &elapsed_time);

        // Get the number of seconds that has elapsed since the last state transition
        double seconds_elapsed = (elapsed_time.tv_sec - start_time.tv_sec)
          + (elapsed_time.tv_nsec - start_time.tv_nsec) / 1e9;

        // Exit loop if `q` key is pressed
        int key = getch();
        if (key == 'q')
        {
            break;
        }

        if (seconds_elapsed < g_timestep) continue;

        printw("One time step has elapsed\n");
        clock_gettime(CLOCK_MONOTONIC, &start_time);
    }

    endwin();
    return EXIT_SUCCESS;
}

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
}
