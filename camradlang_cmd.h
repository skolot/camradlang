#ifndef __CAMRADLANG_CMD_H__
# define __CAMRADLANG_CMD_H__

#define CL_CMD_MAX 32

typedef int (*cl_cmd_handler_t)(const char *param, int *err);

struct cl_cmd_t {
    char *name;
    cl_cmd_handler_t handler;
};

# define CL_CMD_DECLAR(name) struct cl_cmd_t name[CL_CMD_MAX] = { {NULL, NULL} }

# define CL_CMD_ADD(cl_cmd, cmd_name, cmd_handler) {                    \
        int i;                                                          \
        for (i = 0; i < CL_CMD_MAX; i++) {                              \
            if (NULL == cl_cmd[i].name) {                               \
                cl_cmd[i].name = cmd_name;                              \
                cl_cmd[i].handler = cmd_handler;                        \
                break;                                                  \
            }                                                           \
        }                                                               \
    }                                                                   \
        
#endif /* __CAMRADLANG_CMD_H__ */
