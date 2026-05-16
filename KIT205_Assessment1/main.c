#include <stdio.h>
#include "test.h"

int main() {
    printf("\n== Citation Database ==\n");
    printf("Authors <-> Papers (many-to-many)\n\n");

    run_all_tests();

    return 0;
}
