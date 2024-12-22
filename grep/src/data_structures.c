#include "data_structures.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Define the linked list node structure
typedef struct Match {
    char *line;        // The matching line
    int line_number;   // Line number of the match
    struct Match *next; // Pointer to the next match
} Match;

// Create a new match node
Match* create_match(const char *line, int line_number) {
    Match *new_match = malloc(sizeof(Match));
    new_match->line = strdup(line); // Copy the line
    new_match->line_number = line_number;
    new_match->next = NULL;
    return new_match;
}

// Add a match to the linked list
void add_match(Match **head, const char *line, int line_number) {
    Match *new_match = create_match(line, line_number);
    new_match->next = *head;  // Insert at the beginning
    *head = new_match;
}

// Print all matches in the list
void print_matches(Match *head) {
    Match *current = head;
    while (current != NULL) {
        printf("Line %d: %s\n", current->line_number, current->line);
        current = current->next;
    }
}

// Free the linked list memory
void free_matches(Match *head) {
    Match *current = head;
    while (current != NULL) {
        Match *temp = current;
        current = current->next;
        free(temp->line); // Free the line string
        free(temp);        // Free the node
    }
}
