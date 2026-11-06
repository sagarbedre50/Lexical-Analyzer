
#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H
#include <stdio.h>

void check_error(void);

void print_output(const char problem[],
                  const char answer[]);

int check_keyword(char str[]);

int read_char(FILE *fp);

#endif
