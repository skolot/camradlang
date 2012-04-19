#ifndef __CAMRADLANG_H__
# define __CAMRADLANG_H__

# include <stdint.h>
# include <unistd.h> 

int
cl_wait_cmd(const struct cl_cmd_t *cl_cmd, long sec, long usec, int *err);

#endif /* __CAMRADLANG_H__ */
