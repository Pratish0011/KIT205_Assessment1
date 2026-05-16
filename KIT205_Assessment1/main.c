#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "proto1.h"
#include "proto2.h"
#include "test.h"

static void make_id(char* buf, char prefix, int num) {
    sprintf(buf, "%c%04d", prefix, num);
}

static void run_evaluation() {
    printf("=============================\n");
    printf("     PERFORMANCE EVAL\n");
    printf("  Timed: print papers for A0000\n");
    printf("=============================\n");

    int sizes[] = { 1000, 5000, 10000, 50000, 100000 };
    int s, r, i;
    char aid[20], pid[20];

    printf("  %-10s  %-12s  %-12s\n", "Relations", "P1 AVL(us)", "P2 List(us)");
    printf("  %-10s  %-12s  %-12s\n", "---------", "---------", "----------");

    for (s = 0; s < 5; s++) {
        int total = sizes[s];

        P1Table* a1 = p1_create();
        P1Table* p1t = p1_create();
        srand(42);
        for (i = 0; i < total; i++) {
            make_id(aid, 'A', rand() % 200);
            make_id(pid, 'P', rand() % 500);
            p1_add_relation(a1, p1t, aid, pid);
        }

        P2Table* a2 = p2_create();
        P2Table* p2t = p2_create();
        srand(42);
        for (i = 0; i < total; i++) {
            make_id(aid, 'A', rand() % 200);
            make_id(pid, 'P', rand() % 500);
            p2_add_relation(a2, p2t, aid, pid);
        }

        /* Time P1 - suppress output by using a counter trick */
        clock_t t1_start = clock();
        for (r = 0; r < 100; r++) {
            p1_print_relations(a1, "A0000");
        }
        clock_t t1_end = clock();

        clock_t t2_start = clock();
        for (r = 0; r < 100; r++) {
            p2_print_relations(a2, "A0000");
        }
        clock_t t2_end = clock();

        double t1_us = (double)(t1_end - t1_start) / CLOCKS_PER_SEC * 1e6 / 100;
        double t2_us = (double)(t2_end - t2_start) / CLOCKS_PER_SEC * 1e6 / 100;

        printf("  %-10d  %-12.2f  %-12.2f\n", total, t1_us, t2_us);

        p1_free(a1); p1_free(p1t);
        p2_free(a2); p2_free(p2t);
    }

    printf("=============================\n\n");
}

int main() {
    printf("\n== Citation Database ==\n");
    printf("Authors <-> Papers (many-to-many)\n\n");

    run_all_tests();
    run_evaluation();

    return 0;
}