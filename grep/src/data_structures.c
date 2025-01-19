#include "data_structures.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "options.h"
#include "pattern.h"
#include "threading.h" // For locking/unlocking mutex

typedef struct Match {
    char *line;
    int line_number;
    struct Match *next;
} Match;

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

void add_match(Match **head, const char *line, int line_number) {
    Match *new_match = create_match(line, line_number);

    lock_matches(); // Lock the mutex before modifying the list

    if (*head == NULL) {
        *head = new_match;
    } else {
        Match *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_match;
    }

    unlock_matches(); // Unlock the mutex after modifying the list
}

void highlight_match(const char *line, const char *pattern, int ignore_case) {
    const char *start = line;
    const char *match;

    while ((match = (ignore_case ? pattern_case_insensitive_find(start, pattern) : strstr(start, pattern))) != NULL) {
        fwrite(start, 1, match - start, stdout);  // Print text before the match
        printf("\033[31m%.*s\033[0m", (int)strlen(pattern), match);  // Highlight match in red
        start = match + strlen(pattern);  // Move pointer forward
    }

    printf("%s", start);  // Print remaining part of the line
}

void print_matches(Match *head, const options_t *opts, const char *file_name) {
    lock_matches(); // Lock the mutex before reading the list

    if (head == NULL) {
        unlock_matches();
        return;
    }

    if (opts->count_matches) {
        int count = 0;
        Match *current = head;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        printf("%s:%d\n", file_name, count);
        unlock_matches();
        return;
    }

    Match *current = head;
    while (current != NULL) {
        if (opts->file_count > 1 || opts->recursive) {
            printf("%s:", file_name);
        }

        if (opts->show_line_number) {
            printf("%d:", current->line_number);
        }

        highlight_match(current->line, opts->pattern, opts->ignore_case);
        current = current->next;
    }

    unlock_matches(); // Unlock the mutex after reading the list
}

void free_matches(Match *head) {
    lock_matches(); // Lock the mutex before modifying the list

    Match *current = head;
    while (current != NULL) {
        Match *temp = current;
        current = current->next;
        free(temp->line);
        free(temp);
    }

    unlock_matches(); // Unlock the mutex after modifying the list
}
