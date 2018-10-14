#ifndef AHO_CORASICK_PROJECT_DEBUGLOG_H
#define AHO_CORASICK_PROJECT_DEBUGLOG_H

#include <string.h>
#include <stdio.h>
#include <string>

void current_time_str(char* data, int size);

#define LOG_DEBUG(format, ...) do { \
    char buffer[64];     \
    current_time_str(buffer, sizeof(buffer));    \
    fprintf(stdout, "%s [DEBUG] [%s:%d] " format "\n", buffer, strrchr(__FILE__, '/') + 1, __LINE__, ##__VA_ARGS__); } while(0);

#endif //AHO_CORASICK_PROJECT_DEBUGLOG_H
