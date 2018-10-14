#include "DebugLog.h"
#include <sys/time.h>

void current_time_str(char *buf, int size) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    struct tm result;
    localtime_r(&tv.tv_sec, &result);
    snprintf(buf,
             size,
             "%04d-%02d-%02d %02d:%02d:%02d.%06lu",
             result.tm_year + 1900,
             result.tm_mon + 1,
             result.tm_mday,
             result.tm_hour,
             result.tm_min,
             result.tm_sec,
             tv.tv_usec);
}
