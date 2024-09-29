#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
#include "api.h"
#include "console.h"

#define VERSION "2.0"
#define BUILD_DATE __DATE__

static Mango mango = {0, 0, 1, 0};

void print_version(void) {
    c_hexf("#ff8243","mango %s\n",VERSION);
    printf("Built on %s\n", BUILD_DATE);
    printf("Copyright (c) 2024 rxxuzi\n");
    printf("This is free software; see the source for copying conditions.\n");
    printf("There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
}


void help(void) {
    c_hexf("#ff8243","mango %s\n",VERSION);
    printf("Usage: mango [options] <file-path>\n");
    c_hexf("#feb435","Options:\n");
    printf("  -p, --pad <value>    Set padding (default: %d)\n", mango.p);
    printf("  -w, --width <value>  Set maximum width (default: console width)\n");
    printf("  -h, --help           Display this help message\n");
    printf("  -v, --version        Display version information\n");
}

int main(int argc, char **argv) {
    evtp();
    if (argc == 1) {
        help();
        return 1;
    }

    int c;
    char *path = NULL;
    int user_specified_width = 0;    // Flag to check if user specified width

    static struct option long_options[] = {
            {"pad",    required_argument, 0, 'p'},
            {"width",  required_argument, 0, 'w'},
            {"help",   no_argument,       0, 'h'},
            {"version", no_argument, 0, 'v'},
            {0, 0, 0, 0}
    };

    while ((c = getopt_long(argc, argv, "p:w:hv", long_options, NULL)) != -1) {
        switch (c) {
            case 'p':
            {
                char *endptr;
                long pad_value = strtol(optarg, &endptr, 10);
                if (*endptr != '\0' || pad_value < 1 || pad_value > INT_MAX) {
                    c_256f(C_ERR, "Error: Invalid padding value\n");
                    help();
                    return 1;
                }
                mango.p = (int)pad_value;
            }
                break;
            case 'w':
            {
                char *endptr;
                long width_value = strtol(optarg, &endptr, 10);
                if (*endptr != '\0' || width_value < 1 || width_value > INT_MAX) {
                    c_256f(C_ERR, "Error: Invalid width value\n");
                    help();
                    return 1;
                }
                mango.max_w = (int)width_value;
                user_specified_width = 1;
            }
                break;
            case 'h':
                help();
                return 0;
            case 'v':
                print_version();
                return 0;
            case '?':
                c_256f(C_ERR, "Error: Unknown option or missing argument\n");
                help();
                return 1;
            default:
                c_256f(C_ERR, "Error: Unexpected option\n");
                help();
                return 1;
        }
    }

    // If width is not specified, use console width
    if (!user_specified_width) {
        mango.max_w = getConsoleWidth();
        if (mango.max_w == -1) {
            c_256f(C_ERR, "Error: Unable to get console width\n");
            return 1;
        }
    }

    if (optind < argc) {
        path = argv[optind];
    } else {
        c_256f(C_ERR, "Error: No input file specified\n");
        help();
        return 1;
    }

    if (!mango_process(path, &mango)) {
        return 1;
    }

    return 0;
}