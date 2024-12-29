#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "file_ops.h"
#include "pattern.h"
#include "options.h"
#include "utils.h"
#include "data_structures.h"
#include "threading.h"  // Include threading for possible parallelism
#include "directory_ops.h"  // Include directory operations for file listing

Match *matches = NULL;  // Linked list to store matches

int grep_callback(const char *line, int line_number) {
    extern options_t options;

    if (pattern_match(line, options.pattern, options.ignore_case, options.invert_match)) {
        add_match(&matches, line, line_number);  // Zeilennummer übergeben
    }

    return 1;
}

options_t options;

void recursive_wrapper(const char *file_path) {
    process_file(file_path, grep_callback);  // Passe hier an, was 'grep_callback' sein soll
}

int main(int argc, char *argv[]) {
    parse_arguments(argc, argv, &options);

    if (options.file_count == 0) {
        process_stdin(grep_callback);  // Process stdin if no files are provided
    } else {
        for (int i = 0; i < options.file_count; i++) {
            if (options.recursive) {
                // Nutze die Wrapper-Funktion für rekursive Durchsuchung
                recursive_traversal(options.files[i], recursive_wrapper);
            } else {
                process_file(options.files[i], grep_callback);
            }
        }
    }

    // Highlight matches in the output
    print_matches(matches, options.pattern);

    free_matches(matches);   // Free allocated memory

    return 0;
}
