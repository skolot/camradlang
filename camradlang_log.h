#ifndef __CAMRADLANG_LOG_H__
# define __CAMRADLANG_LOG_H__

int
cl_log_str(int level, const char *fmt,...);

# define cl_log_v(level, err, fmt,...)       \
    cl_log_str(level,"%d "fmt, err, ##__VA_ARGS__);

int
cl_log(int level, int err);


#endif /* __CAMRADLANG_LOG_H__ */
