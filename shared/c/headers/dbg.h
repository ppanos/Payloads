#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: "M"\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define set_zero_errno() errno = 0

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); error_code=errno; errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); error_code=errno; errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); error_code=errno; errno=0; goto error; }
#define check_socket_write(A) if(A <= 0) { log_err("ERROR writing to socket"); error_code=errno; errno=0; goto error;}
#define check_dir_open(A) if(!(A)) { log_err("Cannot open directory."); error_code=errno; errno=0; goto error;}
#define COUNT(x)  (sizeof(x) / sizeof((x)[0]))

int error_code;
char *error_message;
size_t error_message_len;

#endif