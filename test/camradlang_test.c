#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>
#include <getopt.h>

#include "camradlang_def.h"
#include "camradlang_parser.h"
#include "camradlang_cmd.h"
#include "camradlang.h"


#define KEY_SIZE 32
#define VAL_SIZE 1024

void
test_parser();

void
test_cmd();

void
legend();

int
main(int argc, char **argv)
{
    char c;
    int run_parser_f = 0, run_cmd_f = 0;

    if (1 == argc) {
        legend();
        exit(EX_USAGE);
    }
    
    while ((c = getopt(argc, argv, "hpcC")) != -1) {
        switch(c) {
        case 'h':
            legend();
            exit(EX_OK);
            
        case 'p':
            run_parser_f = 1;
            break;
            
        case 'c':
            run_cmd_f = 1;
            break;
            
        default:
            fprintf(stderr, "unknow opt '%c'\n", c);
            exit(EX_USAGE);
        }
    }
    
    if (run_parser_f) {
        test_parser();
        exit(EX_OK);
    }

    if (run_cmd_f) {
        test_cmd();
        exit(EX_OK);
    }

    exit(EX_OK);
}

void
test_parser()
{
    struct cl_line l;
    int err;

    while (1) {
        if (cl_select(1, 0, &err) < 0) {
            perror("select");
            exit(EX_OSERR);
        }

        if (cl_read(&l, &err) < 0) {
            fprintf(stderr, "cl_read exit with code %d\n", err);
            continue;
        }

        fprintf(stderr, "mode = '%s' key = '%s' val='%s'\n", l.mode, l.key, l.val);

        if (strlen(l.key)) {
            if (0 == strcmp(l.key, "err")) {
                memset(&l, 0, sizeof(struct cl_line));

                strcpy(l.mode, "LOG");
                strcpy(l.key, "ERR");
                
                l.val[0] = err + '0';
                
                if (cl_write(&l, &err) < 0) {
                    perror("read");
                    exit(EX_OSERR);
                }
            } else {
                memset(&l, 0, sizeof(struct cl_line));

                strcpy(l.mode, "LOG");
                strcpy(l.key, "OK");
                
                l.val[0] = err + '0';

                if (cl_write(&l, &err) < 0) {
                    perror("read");
                    exit(EX_OSERR);
                }
            }

            if (0 == strcmp(l.key, "quit"))
                break;
        }

        memset(&l, 0, sizeof(struct cl_line));
    }
}

int
_test_cmd(const char *param, int *err)
{
    fprintf(stderr, "run test command param = '%s'\n", param);
    *err = CL_ERR_SUCCESS;
    return 0;
}

int
_err_cmd(const char *param, int *err)
{
    *err = CL_ERR_OVERFLOW;
    return 0;
}

int
_quit_cmd(const char *param, int *err)
{
    *err = CL_ERR_SUCCESS;
    exit(EX_OK);
    return 0;
}

void
test_cmd()
{
    int err, i;
    CL_CMD_DECLAR(cl_cmd);

    CL_CMD_ADD(cl_cmd, "test", _test_cmd);
    CL_CMD_ADD(cl_cmd, "err", _err_cmd);
    CL_CMD_ADD(cl_cmd, "quit", _quit_cmd);

    for (i = 0; i < CL_CMD_MAX; i++)
        printf("cmd %d '%s'\n", i, cl_cmd[i].name);

    while (1) {
        cl_wait_cmd(cl_cmd, 1, 0, &err);
    }
}

void
legend()
{
    printf("test program for camradlang library\n");
    printf("  -h    print this screen\n");
    printf("  -p    run parser test\n");
    printf("  -c    run command test\n");
}
