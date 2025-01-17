#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "file_ops.h"
#include "pattern.h"
#include "options.h"
#include "utils.h"
#include "data_structures.h"
#include "threading.h"  // Include threading for parallelism
#include "directory_ops.h"  // Include directory operations for file listing

options_t options;
Match *matches = NULL;  // Linked list to store matches

// Callback function for processing lines
int grep_callback(const char *line, int line_number) {
    if (pattern_match(line, options.pattern, options.ignore_case, options.invert_match)) {
        add_match(&matches, line, line_number);
    }
    return 1;
}

// Wrapper for recursive processing
void recursive_wrapper(const char *file_path) {
    process_file(file_path, grep_callback);

    // Print matches only if there are any
    if (matches != NULL) {
        print_matches(matches, &options, file_path);
        free_matches(matches);
        matches = NULL;  // Reset matches for the next file
    }
}


int main(int argc, char *argv[]) {
    // Parse arguments and initialize options
    parse_arguments(argc, argv, &options);

    if (options.file_count == 0) {
        // Process stdin if no files are specified
        process_stdin(grep_callback);

        // Print matches only if there are any
        if (matches != NULL) {
            print_matches(matches, &options, "stdin");
            free_matches(matches);
        }
    } else {
        if (options.recursive) {
            // Recursive directory processing
            for (int i = 0; i < options.file_count; i++) {
                recursive_traversal(options.files[i], recursive_wrapper);
            }
        } else {
            // Process each file
            for (int i = 0; i < options.file_count; i++) {
                process_file(options.files[i], grep_callback);

                // Print matches only if there are any
                if (matches != NULL) {
                    print_matches(matches, &options, options.files[i]);
                    free_matches(matches);
                    matches = NULL;  // Reset matches for the next file
                }
            }
        }
    }

    return 0;
}
