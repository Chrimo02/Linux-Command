#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "options.h" // Für den Zugriff auf options_t

// Function declarations for managing the linked list of matches
typedef struct Match Match;

// Function to create a new match node
Match* create_match(const char *line, int line_number);

// Function to add a match to the list
void add_match(Match **head, const char *line, int line_number);

// Function to free the allocated memory for the list
void free_matches(Match *head);

// Highlight matched words in a line
void highlight_match(const char *line, const char *pattern, int ignore_case);

// Print matches with options (e.g., line numbers, file names, counts)
void print_matches(Match *head, const options_t *opts, const char *file_name);

#endif // DATA_STRUCTURES_H
