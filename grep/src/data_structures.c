#include "data_structures.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "options.h"
#include "pattern.h"

// Define the linked list node structure
typedef struct Match {
    char *line;        // The matching line
    int line_number;   // Line number of the match
    struct Match *next; // Pointer to the next match
} Match;

// Create a new match node
Match* create_match(const char *line, int line_number) {
    Match *new_match = malloc(sizeof(Match));
    if (!new_match) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_match->line = strdup(line);
    if (!new_match->line) {
        perror("strdup");
        free(new_match);
        exit(EXIT_FAILURE);
    }

    new_match->line_number = line_number;
    new_match->next = NULL;
    return new_match;
}

// Add a match to the linked list (append to the end)
void add_match(Match **head, const char *line, int line_number) {
    Match *new_match = create_match(line, line_number);

    if (*head == NULL) {
        *head = new_match;
    } else {
        Match *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_match;
    }
}

// Highlight the matched word in a line using ANSI escape sequences
void highlight_match(const char *line, const char *pattern, int ignore_case) {
    const char *start = line;
    const char *match;

    while ((match = (ignore_case ? pattern_case_insensitive_find(start, pattern) : strstr(start, pattern))) != NULL) {
        fwrite(start, 1, match - start, stdout);  // Print text before the match
        printf("\033[31m%.*s\033[0m", (int)strlen(pattern), match);  // Highlight match in red
        start = match + strlen(pattern);  // Move pointer forward
    }

    printf("%s", start);  // Print remaining part of the line (without adding a newline)
}



// Print all matches based on options
void print_matches(Match *head, const options_t *opts, const char *file_name) {
    if (head == NULL) {
        return;  // No matches, skip output
    }

    if (opts->count_matches) {
        // Count matches per file
        int count = 0;
        Match *current = head;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        printf("%s:%d\n", file_name, count);  // Prepend file name to match count
        return;
    }

    Match *current = head;
    while (current != NULL) {
        if (opts->file_count > 1 || opts->recursive) {
            printf("%s:", file_name);  // Prepend file name if recursive or multiple files
        }

        if (opts->show_line_number) {
            printf("%d:", current->line_number);  // Print line number
        }

        highlight_match(current->line, opts->pattern, opts->ignore_case);
        current = current->next;
    }
}


// Free the linked list memory
void free_matches(Match *head) {
    Match *current = head;
    while (current != NULL) {
        Match *temp = current;
        current = current->next;
        free(temp->line);
        free(temp);
    }
}
