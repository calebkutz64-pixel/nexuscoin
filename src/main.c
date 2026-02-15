#include "nexus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_usage(void)
{
    printf("Usage:\n");
    printf("  ./nexuscoin <module> <args>\n\n");
    printf("Modules:\n");
    printf("  keygen   Generate a private key\n");
    printf("\nExample:\n");
    printf("  ./nexuscoin keygen --out signingkey.dat\n");
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        print_usage();
        return EXIT_FAILURE;
    }

    const char *module = argv[1];

    if (strcmp(module, "keygen") == 0)
    {
        if (!module_keygen(argc - 2, &argv[2]))
        {
            return EXIT_FAILURE;
        }
    }
    else if (strcmp(module, "sign") == 0)
    {
        return module_sign(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    else
    {
        fprintf(stderr, "Unknown module: %s\n\n", module);
        print_usage();
        return EXIT_FAILURE;
    }
}
