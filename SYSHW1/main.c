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
#include <math.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>

#define kBIT_WIDTH 8
#define kFILE_NAME "sth"

_Bool *generate_r(const _Bool *bin_buf, long bin_len, const _Bool *rule_buf);

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

_Bool *itoboolarr_f(int rule_nr) {
    _Bool *result = (_Bool *)malloc(sizeof(_Bool) * kBIT_WIDTH);
    memset(result, 0, sizeof(_Bool) * kBIT_WIDTH);
    
    for (int i = kBIT_WIDTH - 1; i >= 0; --i) {
        int x = rule_nr / powf(2.00f, (float)i);
        
        rule_nr -= x * powf(2.00f, (float)i);
        
        result[i] = (_Bool)x;
    }
    
    return result;
}

int main(int argc, const char * argv[]) {
    FILE *f_ptr = NULL;
    int rule_nr = 0;
    int num_generations = 0;
    
    if (!(f_ptr = fopen(kFILE_NAME, "r"))) {
        perror("file couldn't be opened");
        exit(9);
    }
    
    printf("Reading binary buffer from file...");
    
    _Bool bin_buffer[BUFSIZ];
    int bool_qty = 0;
    
    while (!feof(f_ptr)) {
        char ch = getc(f_ptr);
        
        if (bool_qty == BUFSIZ) {
            perror("file too long");
            exit(1);
        }
        
        switch (ch) {
            case '\n':
                goto bailout;
            case ' ':
                continue;
            default:
                bin_buffer[bool_qty++] = (_Bool)ch;
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
    
    _Bool *rule_buf = itoboolarr_f(30);
    
//    generate_r(bin_buffer, bool_qty, rule_buf);
    
    return 0;
}
