# Limited Linux grep Command Implementation

## Overview
This project implements a limited version of the `grep` command in C as part of a portfolio assignment for the System-Oriented Programming course. The program allows users to search for patterns within files and directories, supporting concurrency, dynamic data structures, and integration with Linux pipelines.

## Features
- Search for a pattern in one or multiple files.
- Support for command-line arguments to configure behavior.
- Integration with standard input (`stdin`) and output (`stdout`) for piping.
- Concurrent directory traversal using threads.
- Dynamic data structures for efficient pattern matching.
- Thread safety via mutexes and synchronization mechanisms.
- Modular structure with separate source and header files.
- Build system using `gcc` and a `Makefile`.

## Supported Options
This limited implementation of the `grep` command supports the following options:
- `-h` or `-help`: Displays a help-message with possible options 
- `-i`: Perform a case-insensitive search.
- `-v`: Invert match; only display lines that do not match the pattern.
- `-r`: Recursively search directories for files matching the pattern.
- `-c`: Count the number of matching lines instead of displaying them.
- `-n`: Display the line numbers of matching lines.

Options that are not implemented will result in an error message when attempted.

## File Structure
### Source Code Files:
- **main.c**: Entry point of the program. Handles argument parsing and orchestrates program execution.
- **pattern.c**: Implements pattern matching logic.
- **file_ops.c**: Handles file input/output operations.
- **directory_ops.c**: Traverses directories and manages file discovery.
- **sync_mechanisms.c**: Implements thread synchronization using mutexes or semaphores.
- **threading.c**: Manages threading and parallel execution of tasks.
- **data_structures.c**: Provides dynamic data structures like linked lists.
- **utils.c**: Contains utility functions for common operations.
- **error_handling.c**: Centralized error reporting and handling logic.
- **options.c**: Processes and validates command-line options.

### Header Files:
Each `.c` file is paired with a corresponding `.h` file that declares its functions and data structures.

## Build and Run
### Prerequisites
- **Compiler**: GCC
- **Operating System**: Linux

### Build Process
1. Open a terminal in the project root directory.
2. Run the following command to compile the project:
   ```bash
   make all
   ```
   This will generate an executable named `grep`.

### Running the Program
Run the executable with the following syntax:
```bash
./grep [OPTIONS] PATTERN [FILE...]
```
- **PATTERN**: The string to search for.
- **FILE**: One or more files to search. If omitted, the program reads from `stdin`.

### Example Usage
- Search for "example" in a single file:
  ```bash
  ./grep example file.txt
  ```
- Search in multiple files:
  ```bash
  ./grep example file1.txt file2.txt
  ```
- Pipe input to the program:
  ```bash
  echo "This is a test" | ./grep test
  ```

### Clean Up
To remove compiled files:
```bash
make clean
```

## Code Structure and Design
The program follows modular design principles:
- **Separation of Concerns**: Each component handles a specific aspect of the functionality (e.g., threading, file operations).
- **Thread Safety**: Shared resources are protected using mutexes or semaphores to ensure concurrent execution integrity.
- **Dynamic Allocation**: Data structures are dynamically allocated and freed to prevent memory leaks.
- **Error Handling**: Errors are centrally managed for consistent reporting and debugging.

## Testing
The `Makefile` includes a target to run test cases:
```bash
make test
```
This will execute predefined test cases and validate the program’s behavior against expected outputs.

## Contributing
For suggestions or contributions, please submit a pull request to the project repository.

## Authors
- Steffen Krutzsch
- Christian Model
- Gülsüm Erboğa
- Glison Doci


