/*
 * =====================================================================================
 *
 *       Filename:  llog.h
 *
 *    Description:  A colorful syslog library for C language.
 *
 *        Version:  1.0
 *        Created:  02/12/16 13:01:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kkkmmu, 
 *   Organization:  
 *
 * =====================================================================================
 */

#if !defined __LLOG_H__
#define __LLOG_H__
#include <stdio.h>
#include <errno.h>
#include <string.h>

enum llog_level {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    LEVEL_MAX,
};

void llog(enum llog_level level, const char *fmt, ...);

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) llog(DEBUG, " (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) llog(ERROR, " (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) llog(WARN, " (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) llog(INFO, " (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif /* __LLOG_H__ */
