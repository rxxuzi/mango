#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
#include "api.h"
#include "console.h"

#define VERSION "1.2"

static Mango mango = {0, 0, 1, 0};

void help(void) {
    c256f(C_INFO, "mango.exe!\n");
    c256f(C_INFO, "Usage: mango.exe [options] <file-path>\n");
    c256f(C_INFO, "Options:\n");
    c256f(C_INFO, "  -p, --pad <value>    Set padding (default: %d)\n", mango.p);
    c256f(C_INFO, "  -w, --width <value>  Set maximum width (default: console width)\n");
    c256f(C_INFO, "  -h, --help           Display this help message\n");
    c256f(C_INFO, "  -v, --version        Display version information\n");
}

int main(int argc, char **argv) {
    mango_init();

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
                    c256f(C_ERR, "Error: Invalid padding value\n");
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
                    c256f(C_ERR, "Error: Invalid width value\n");
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
                c256f(C_INFO,"mango.exe version %s\n", VERSION);
                return 0;
            case '?':
                c256f(C_ERR, "Error: Unknown option or missing argument\n");
                help();
                return 1;
            default:
                c256f(C_ERR, "Error: Unexpected option\n");
                help();
                return 1;
        }
    }

    // If width is not specified, use console width
    if (!user_specified_width) {
        mango.max_w = getConsoleWidth();
        if (mango.max_w == -1) {
            c256f(C_ERR, "Error: Unable to get console width\n");
            return 1;
        }
    }

    if (optind < argc) {
        path = argv[optind];
    } else {
        c256f(C_ERR, "Error: No input file specified\n");
        help();
        return 1;
    }

    if (!mango_process(path, &mango)) {
        return 1;
    }

    return 0;
}