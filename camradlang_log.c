#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <camradlang_def.h>
#include <camradlang_parser.h>
#include <camradlang_log.h>

const char *loglevel_str[] = { "INFO", "ERR", "WARN", "DEBUG", NULL };

int
cl_log_str(int level, const char *fmt,...) 
{
    va_list arg;
    int werr;
    struct cl_line l;
    
    memset(&l, 0, sizeof(struct cl_line));

    strcpy(l.mode, "LOG");
    strcpy(l.key, loglevel_str[level]);

    va_start(arg, fmt);
    vsnprintf(l.val, VAL_LEN, fmt, arg);
    va_end(arg);

    if (cl_write(&l, &werr) < 0)
        return -1;
    
    return 0;
}

int
cl_log(int level, int err)
{
    int werr;
    struct cl_line l;

    memset(&l, 0, sizeof(struct cl_line));
    
    strcpy(l.mode, "LOG");
    strcpy(l.key, loglevel_str[level]);

    snprintf(l.val, VAL_LEN, "%d", err);

    if (cl_write(&l, &werr) < 0)
        return -1;

    return 0;
}
