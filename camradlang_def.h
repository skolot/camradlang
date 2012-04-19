#ifndef __CAMRADLANG_DEF_H__
# define __CAMRADLANG_DEF_H__

# define DEV_NAME_LEN 128

# define STDIN  0
# define STDOUT 1
# define STDERR 2
# define MAX_BUF_LEN 4096
# define MODE_LEN 8
# define KEY_LEN 32
# define VAL_LEN (MAX_BUF_LEN - MODE_LEN - KEY_LEN)

/* log level */
# define CL_LOG_INFO      0
# define CL_LOG_ERR       1
# define CL_LOG_WARN      2
# define CL_LOG_DEBUG     3

/* err code */

enum cl_errs
{
    CL_ERR_SUCCESS = 0,
    CL_ERR_OVERFLOW = 1,
    CL_ERR_READ = 2,
    CL_ERR_WRITE = 3,
    CL_ERR_SYNTAX = 4,
    CL_ERR_CONFIG = 5,
    CL_ERR_SELECT = 6,
    CL_ERR_ABORT = 7,
    CL_ERR_UNKOPT = 8,
    CL_ERR_UNKCMD = 9,
    CL_ERR_FATAL = 10,
    CL_ERR_EMPTY_LINE = 11,
    CL_ERR_CANT_OPEN_SOURCE = 12,
    CL_ERR_CANT_GET_INFO = 13,
    CL_ERR_CANT_FIND_VIDEO_CODEC = 14,
    CL_ERR_CANT_FIND_AUDIO_CODEC = 15,
    CL_ERR_MANY_AUDIO_CHANNELS = 16,
    CL_ERR_NOW_PLAYING = 17,
    CL_ERR_CANT_INIT_SDI_DK = 18
};

/* cart type */
# define C_CARD_DECLINK 1
# define C_CARD_DVEO    2

#define CL_MODE_CMD     "CMD"
#define CL_MODE_LOG     "LOG"
#define CL_MODE_DATA    "DATA"

#endif 
