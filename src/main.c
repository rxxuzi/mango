#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
#include "api.h"
#include "console.h"

static int padding = 3;

void help(void) {
    c256f(C_INFO, "mango.exe!\n");
    c256f(C_INFO, "Usage: mango.exe [options] <file-path>\n");
    c256f(C_INFO, "Options:\n");
    c256f(C_INFO, "  -p, --pad <value>   Set padding (default: %d)\n", padding);
    c256f(C_INFO, "  -h, --help          Display this help message\n");
}

int main(int argc, char **argv) {
    mango_init();

    if (argc == 1) {
        help();
        return 1;
    }

    int c;
    char *path = NULL;

    static struct option long_options[] = {
            {"pad", required_argument, 0, 'p'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
    };

    while ((c = getopt_long(argc, argv, "p:h", long_options, NULL)) != -1) {
        switch (c) {
            case 'p':
            {
                char *endptr;
                long pad_value = strtol(optarg, &endptr, 10);
                if (*endptr != '\0' || pad_value < 1 || pad_value > INT_MAX) {
                    c256f(196, "Error: Invalid padding value\n");
                    help();
                    return 1;
                }
                padding = (int)pad_value;
            }
                break;
            case 'h':
                help();
                return 0;
            case '?':
                c256f(9, "Error: Unknown option or missing argument\n");
                help();
                return 1;
            default:
                c256f(9, "Error: Unexpected option\n");
                help();
                return 1;
        }
    }

    if (optind < argc) {
        path = argv[optind];
    } else {
        c256f(196, "Error: No input file specified\n");
        help();
        return 1;
    }

    if (!mango_process(path, padding)) {
        return 1;
    }

    return 0;
}