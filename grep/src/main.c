#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "file_ops.h"
#include "pattern.h"
#include "options.h"
#include "utils.h"
#include "data_structures.h"
#include "threading.h"
#include "directory_ops.h"

options_t options;
Match *matches = NULL;

int grep_callback(const char *line, int line_number) {
    if (pattern_match(line, options.pattern, options.ignore_case, options.invert_match)) {
        add_match(&matches, line, line_number);
    }
    return 1;
}

void recursive_wrapper(const char *file_path) {
    process_file(file_path, grep_callback);

    if (matches != NULL) {
        print_matches(matches, &options, file_path);
        free_matches(matches);
        matches = NULL;
    }
}

int main(int argc, char *argv[]) {
    parse_arguments(argc, argv, &options);

    if (options.file_count == 0) {
        process_stdin(grep_callback);

        if (matches != NULL) {
            print_matches(matches, &options, "stdin");
            free_matches(matches);
        }
    } else {
        if (options.recursive) {
            start_threaded_search((const char **)options.files, options.file_count, recursive_wrapper);
        } else {
            for (int i = 0; i < options.file_count; i++) {
                process_file(options.files[i], grep_callback);

                if (matches != NULL) {
                    print_matches(matches, &options, options.files[i]);
                    free_matches(matches);
                    matches = NULL;
                }
            }
        }
    }

    destroy_mutex(); // Destroy the matches mutex
    return 0;
}
