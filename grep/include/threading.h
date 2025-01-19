#ifndef THREADING_H
#define THREADING_H

int start_threaded_search(const char *dir_paths[], int dir_count, void (*callback)(const char *file_path));

#endif // THREADING_H
