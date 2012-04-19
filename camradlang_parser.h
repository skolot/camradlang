#ifndef __CAMRADLANG_PARSER_H__
# define __CAMRADLANG_PARSER_H__

# include <stdint.h>

struct cl_line {
    char mode[MODE_LEN];
    char key[KEY_LEN];
    char val[VAL_LEN];
};

int
cl_select(long sec, long usec, int *err);

int
cl_read(struct cl_line *l, int *err);

int
cl_write(const struct cl_line *l, int *err);

#endif /* __CAMRADLANG_H__ */
