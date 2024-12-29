#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// Function declarations for managing the linked list of matches
typedef struct Match Match;

// Function to create a new match node
Match* create_match(const char *line, int line_number);

// Function to add a match to the list
void add_match(Match **head, const char *line, int line_number);

// Function to print all matches
void print_matches(Match *head);

// Function to free the allocated memory for the list
void free_matches(Match *head);

void highlight_match(const char *line, const char *pattern);

void print_matches(Match *head, const char *pattern);

void print_matches_with_lines(Match *head, const char *pattern);


#endif
