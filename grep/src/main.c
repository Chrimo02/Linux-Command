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
options_t options;
Match *matches = NULL;  // Linked list to store matches

// Callback-Funktion für die Verarbeitung von Zeilen
int grep_callback(const char *line, int line_number) {

    // Prüfe, ob die Zeile das Muster erfüllt
    if (pattern_match(line, options.pattern, options.ignore_case, options.invert_match)) {
        add_match(&matches, line, line_number);  // Zeilennummer übergeben
    }

    return 1;
}

// Wrapper für die rekursive Verarbeitung
void recursive_wrapper(const char *file_path) {
    process_file(file_path, grep_callback);
}

int main(int argc, char *argv[]) {
    // Argumente parsen und Optionen initialisieren
    parse_arguments(argc, argv, &options);

    if (options.file_count == 0) {
        // Verarbeite stdin, falls keine Dateien angegeben wurden
        process_stdin(grep_callback);
    } else {
        for (int i = 0; i < options.file_count; i++) {
            if (options.recursive) {
                // Rekursive Verarbeitung
                recursive_traversal(options.files[i], recursive_wrapper);
            } else {
                // Verarbeite einzelne Datei
                process_file(options.files[i], grep_callback);
            }
        }
    }

    // Ausgabe der Ergebnisse basierend auf den Optionen
    print_matches(matches, &options);

    // Speicher freigeben
    free_matches(matches);

    return 0;
}
