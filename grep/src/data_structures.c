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

// Add a match to the linked list (append to the end)
void add_match(Match **head, const char *line, int line_number) {
    Match *new_match = create_match(line, line_number);

    if (*head == NULL) {
        // Liste ist leer, füge das erste Element hinzu
        *head = new_match;
    } else {
        // An das Ende der Liste anhängen
        Match *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_match;
    }
}

// Highlight the matched word in a line using ANSI escape sequences
void highlight_match(const char *line, const char *pattern) {
    const char *start = line;
    const char *match;

    while ((match = strstr(start, pattern)) != NULL) {
        // Print the part of the line before the match
        fwrite(start, 1, match - start, stdout);

        // Print the match in red
        printf("\033[31m%s\033[0m", pattern);

        // Move the pointer forward
        start = match + strlen(pattern);
    }

    // Print the remaining part of the line
    printf("%s", start);
}

// Print all matches in the list with highlighted matches
void print_matches(Match *head, const char *pattern) {
    Match *current = head;
    while (current != NULL) {
        highlight_match(current->line, pattern);
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
