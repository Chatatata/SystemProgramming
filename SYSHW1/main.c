//
//  main.c
//  SYSHW1
//
//  Created by Buğra Ekuklu on 14.10.2016.
//  Copyright © 2016 The Digital Warehouse. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>

#define kBIT_WIDTH 8
#define kFILE_NAME "input1d.txt"

void generate_r(const _Bool *bin_buf, long bin_len, const _Bool *rule_buf, const _Bool *draw_buf);

int fetch_rule_nr_f() {
    char *rule_nr_buffer = (char *)malloc(sizeof(char) * 7);
    memset(rule_nr_buffer, 0, sizeof(char) * 7);
    fgets(rule_nr_buffer, 6, stdin);

    int result = atoi(rule_nr_buffer);

    free(rule_nr_buffer);

    return result;
}

int fetch_num_generations_f() {
    char *num_generations_buffer = (char *)malloc(sizeof(char) * 7);
    memset(num_generations_buffer, 0, sizeof(char) * 7);
    fgets(num_generations_buffer, 6, stdin);

    int result = atoi(num_generations_buffer);

    free(num_generations_buffer);

    return result;
}

int pown_m_f(const int base, const int power) {
    if (power >= 1) {
        return base * pown_m_f(base, power - 1);
    } else {
        return 1;
    }
}

void itoboolarr_f(_Bool *rule_buf, int rule_nr) {
    for (int i = kBIT_WIDTH - 1; i >= 0; --i) {
        int x = rule_nr / pown_m_f(2, i);

        rule_nr -= x * pown_m_f(2, i);

        rule_buf[i] = (_Bool)x;
    }
}

int main(int argc, const char * argv[]) {
    FILE *f_ptr = NULL;
    int rule_nr = 0;
    int num_generations = 0;

    if (!(f_ptr = fopen(kFILE_NAME, "r"))) {
        perror("file couldn't be openedz");
        exit(9);
    }

    printf("Reading binary buffer from file...");

    _Bool bin_buffer[BUFSIZ];
    _Bool draw_buffer[BUFSIZ];
    _Bool rule_buffer[8];
    int bool_qty = 0;

    while (!feof(f_ptr)) {
        char ch = getc(f_ptr);

        if (bool_qty == BUFSIZ) {
            perror("file too long");
            exit(1);
        }

        switch (ch) {
            case '\n':
            case -1:
                goto bailout;
            case ' ':
                continue;
	        case '0':
                bin_buffer[bool_qty++] = (_Bool)0;
                break;
            case '1':
                bin_buffer[bool_qty++] = (_Bool)1;
                break;
            default:
                perror("unexpected input sequence");
                exit(1);
        }
    }

bailout:
    //  Release the file handle
    fclose(f_ptr);

    //  Fetch the rule number from stdin
    printf("\nPlease enter the rule number: ");
    rule_nr = fetch_rule_nr_f();
    printf("\n");

    //  Fetch the number of generations from stdin
    printf("Please enter the number of generations: ");
    num_generations = fetch_num_generations_f();
    printf("\n");

    itoboolarr_f(rule_buffer, rule_nr);

    printf("Rule buffer: ");

    for (size_t i = 0; i < 8; i++) {
        printf("%x", rule_buffer[i]);
    }

    printf("\n");

    printf("Binary buffer : ");

    for (size_t i = 0; i < bool_qty; i++) {
        printf("%x", bin_buffer[i]);
    }

    printf("\n");

    printf("Binary buffer addr: %x\nBool_qty addr: %x\nRule buffer addr: %x\nDraw buffer addr: %x\n", &bin_buffer, &bool_qty, &rule_buffer, &draw_buffer);

    printf("\n");

    printf("Draw buffer   : ");

    for (size_t i = 0; i < bool_qty; i++) {
        printf("%x", draw_buffer[i]);
    }

    printf("\n");

    printf("Buffer address: %d", bin_buffer[15]);

    printf("\n");

    //printf("Subroutine: %d\n", generate_r(bin_buffer, bool_qty, rule_buf, draw_buffer));
    generate_r(bin_buffer, bool_qty, rule_buffer, draw_buffer);
    printf("\n");
    for (size_t i = 0; i < bool_qty; i++) {
        printf("%x", draw_buffer[i]);
    }

    return 0;
}
