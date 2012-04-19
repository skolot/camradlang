#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

#include <camradlang_def.h>
#include <camradlang_parser.h>

int
cl_select(long sec, long usec, int *err)
{
    fd_set fds_stdin;
    struct timeval tv;
    int ret;

    *err = CL_ERR_SUCCESS;

    FD_ZERO(&fds_stdin);
    FD_SET(STDIN, &fds_stdin);

    tv.tv_sec = sec;
    tv.tv_usec = usec;

    if ((ret = select(STDIN + 1, &fds_stdin, NULL, NULL, &tv)) < 0) {
        *err = CL_ERR_SELECT;
        return -1;
    }
    
    if (ret)
        return FD_ISSET(STDIN, &fds_stdin);
    
    return 0;
}

int
cl_read(struct cl_line *l, int *err)
{
    char buf[MAX_BUF_LEN] = {0}, *p, *pl;

    *err = 0;
    
    if (NULL == fgets(buf, MAX_BUF_LEN, stdin)) {
        *err = CL_ERR_READ;
        return -1;
    }

    p = strrchr(buf, '\n');
    
    if (p)
        *p = '\0';
    
    p = strrchr(buf, '\r');
    
    if (p)
        *p = '\0';

    if (strlen(buf) == 0)
    {
        *err = CL_ERR_EMPTY_LINE;
        return -1;
    }
    pl = strchr(buf, ':');

    if (NULL == pl) {
        *err = CL_ERR_SYNTAX;
        return -1;
    }

    strncpy(l->mode, buf, pl - buf);
    l->mode[pl - buf] = '\0';
    
    pl++;

    if (strlen(pl)) {
        p = strchr(pl, '=');
        
        if (p && (strlen(p) != 0)) {
            if ((p - pl) > (KEY_LEN - 1)) {
                *err = CL_ERR_OVERFLOW;
                return -1;
            }

            strncpy(l->key, pl, p - pl);
            l->key[p - pl] = '\0';

            if (strlen(p + 1) > VAL_LEN) {
                *err = CL_ERR_OVERFLOW;
                return -1;
            }
            
            strcpy(l->val, p + 1);
        } else {
            if (strlen(pl) > KEY_LEN) {
                *err = CL_ERR_OVERFLOW;
                return -1;
            }

            strcpy(l->key, pl);
        }
    }

    return 0;
}

int
cl_write(const struct cl_line *l, int *err)
{
    *err = CL_ERR_SUCCESS;
    int i = atoi((char *)l->val);

    if (0 == strlen(l->key)) 
        return 0;
    
    if (strlen(l->val)) {
        if ((fprintf(stderr, "%s:%s=%s\n", l->mode, l->key, l->val)) < 0) {
            *err = CL_ERR_WRITE;
            return -1;
        }
    } else {
        if ((fprintf(stderr, "%s:%s\n", l->mode, l->key)) < 0) {
            *err = CL_ERR_WRITE;
            return -1;
        }
    }
    if (fwrite(&i, 1, sizeof(int), stdout) < sizeof(int))
    {
        *err = CL_ERR_WRITE;
        return -1;
    }

    fflush(stdout);
    fflush(stderr);

    return 0;
}
