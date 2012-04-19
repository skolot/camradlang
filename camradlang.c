#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __linux
# include <bsd/string.h>
#endif

#include <camradlang_def.h>
#include <camradlang_parser.h>
#include <camradlang_log.h>
#include <camradlang_cmd.h>
#include <camradlang.h>

int
cl_wait_cmd(const struct cl_cmd_t *cl_cmd, long sec, long usec, int *err)
{
    struct cl_line l;
    int i;
   
    *err = CL_ERR_SUCCESS;

    if (cl_select(sec, usec, err) < 0) 
        return -1;

    memset(&l, 0, sizeof(struct cl_line));
    
    if (cl_read(&l, err) < 0)
        return -1;

    if (0 != strcasecmp(l.mode, "CMD")) {
        *err = CL_ERR_SYNTAX;
        cl_log(CL_LOG_ERR, CL_ERR_SYNTAX);
        return -1;
    }

    for (i = 0; i < CL_CMD_MAX; i++) {
        if (NULL == cl_cmd[i].name)
            break;
        
        if (0 == strcasecmp(l.key, cl_cmd[i].name)) {
            if (cl_cmd[i].handler(l.val, err) < 0) {
                cl_log(CL_LOG_ERR, *err);
                return -1;
            }

            if (CL_ERR_SUCCESS == *err)
                cl_log(CL_LOG_INFO, CL_ERR_SUCCESS);
            else
                cl_log(CL_LOG_ERR, *err);

            return 0;
        }
    }

    cl_log(CL_LOG_ERR, CL_ERR_UNKCMD);

    return -1;
}
