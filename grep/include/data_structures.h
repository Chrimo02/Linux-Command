#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "options.h"

typedef struct Match Match;

Match* create_match(const char *line, int line_number);

void add_match(Match **head, const char *line, int line_number);

void free_matches(Match *head);

void highlight_match(const char *line, const char *pattern, int ignore_case);

void print_matches(Match *head, const options_t *opts, const char *file_name);

void free_matches(Match *head);

#endif
