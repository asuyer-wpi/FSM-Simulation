/*
 * Copyright (C) 2026
 * Created by asuyer-wpi, asuyer@wpi.edu
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/// Prints the program usage using `program` as the invocation command.
void print_usage(char const* program);

/// Sets the simulation timestep to `seconds` seconds.
void set_timestep(float seconds);

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
    printf("Set timestep to %f seconds\n", seconds);
}


