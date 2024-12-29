#include "data_structures.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "options.h"
#include "pattern.h" // Für Zugriff auf pattern_match

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
void highlight_match(const char *line, const char *pattern, int ignore_case) {
    const char *start = line;
    const char *match;

    while ((match = (ignore_case ? pattern_case_insensitive_find(start, pattern) : strstr(start, pattern))) != NULL) {
        // Print the part of the line before the match
        fwrite(start, 1, match - start, stdout);

        // Print the match in red
        printf("\033[31m");
        for (size_t i = 0; i < strlen(pattern); i++) {
            putchar(match[i]);
        }
        printf("\033[0m");

        // Move the pointer forward
        start = match + strlen(pattern);
    }

    // Print the remaining part of the line
    printf("%s", start);
}

// Print all matches based on options
void print_matches(Match *head, const options_t *opts) {
    if (opts->count_matches) {
        // Count matches instead of printing them
        int count = 0;
        Match *current = head;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        printf("Total matches: %d\n", count);
        return;
    }

    // Print matches line by line
    Match *current = head;
    while (current != NULL) {
        if (opts->show_line_number) {
            printf("%d:", current->line_number); // Print line number
        }

        // Entferne potenzielle überflüssige \n am Ende der Zeile
        char *cleaned_line = strdup(current->line);
        size_t len = strlen(cleaned_line);
        if (len > 0 && cleaned_line[len - 1] == '\n') {
            cleaned_line[len - 1] = '\0';
        }

        // Highlight matches und gebe die Zeile aus
        highlight_match(cleaned_line, opts->pattern, opts->ignore_case);
        printf("\n");

        // Speicher freigeben
        free(cleaned_line);
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
