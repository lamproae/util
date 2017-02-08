#include "leak-checker.h"
#include <inttypes.h>
#include "backtrace.h"
#include <stdarg.h>
#include "util.h"

#include "llog.h"

#define HAVE_MALLOC_HOOKS

#ifndef HAVE_MALLOC_HOOKS
void
leak_checker_start(const char *file_name)
{
    llog(WARN, "not enabling leak checker because the libc in use does not "
              "have the required hooks");
}

void
leak_checker_set_limit(off_t max_size)
{
}

void
leak_checker_claim(const void *p)
{
}

void
leak_checker_usage(void)
{
    printf("  --check-leaks=FILE      (accepted but ignored in this build)\n");
}
#else /* HAVE_MALLOC_HOOKS */
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <sys/stat.h>

typedef void *malloc_hook_type(size_t, const void *);
typedef void *realloc_hook_type(void *, size_t, const void *);
typedef void free_hook_type(void *, const void *);

struct hooks {
    malloc_hook_type *malloc_hook_func;
    realloc_hook_type *realloc_hook_func;
    free_hook_type *free_hook_func;
};

static malloc_hook_type hook_malloc;
static realloc_hook_type hook_realloc;
static free_hook_type hook_free;

static struct hooks libc_hooks;
static const struct hooks our_hooks = { hook_malloc, hook_realloc, hook_free };

static FILE *file;
static off_t limit = 10 * 1000 * 1000;

static void
get_hooks(struct hooks *hooks)
{
    hooks->malloc_hook_func = __malloc_hook;
    hooks->realloc_hook_func = __realloc_hook;
    hooks->free_hook_func = __free_hook;
}

static void
set_hooks(const struct hooks *hooks)
{
    __malloc_hook = hooks->malloc_hook_func;
    __realloc_hook = hooks->realloc_hook_func;
    __free_hook = hooks->free_hook_func;
}

void
leak_checker_start(const char *file_name)
{
    if (!file) {
        file = fopen(file_name, "w");
        if (!file) {
            llog(WARN, "failed to create \"%s\": %s",
                      file_name, strerror(errno));
            return;
        }
        setvbuf(file, NULL, _IONBF, 0);
        llog(WARN, "enabled memory leak logging to \"%s\"", file_name);
        get_hooks(&libc_hooks);
        set_hooks(&our_hooks);
    }
}

void
leak_checker_stop(void)
{
    if (file) {
        fclose(file);
        file = NULL;
        set_hooks(&libc_hooks);
        llog(WARN, "disabled memory leak logging");
    }
}

void
leak_checker_set_limit(off_t limit_)
{
    limit = limit_;
}

void
leak_checker_usage(void)
{
    printf("  --check-leaks=FILE      log malloc and free calls to FILE\n");
}

static void PRINTF_FORMAT(1, 2)
log_callers(const char *format, ...)
{
    struct backtrace backtrace;
    va_list args;
    int i;

    va_start(args, format);
    vfprintf(file, format, args);
    va_end(args);

    putc(':', file);
    backtrace_capture(&backtrace);
    for (i = 0; i < backtrace.n_frames; i++) {
        fprintf(file, " 0x%x", backtrace.frames[i]);
    }
    putc('\n', file);
}

static void
reset_hooks(void)
{
    static int count;

    if (count++ >= 100 && limit && file) {
        struct stat s;
        count = 0;
        if (fstat(fileno(file), &s) < 0) {
            llog(WARN, "cannot fstat leak checker log file: %s",
                      strerror(errno));
            return;
        }
        if (s.st_size > limit) {
            llog(WARN, "leak checker log file size exceeded limit");
            leak_checker_stop();
            return;
        }
    }
    if (file) {
        set_hooks(&our_hooks);
    }
}

static void *
hook_malloc(size_t size, const void *caller)
{
    void *p;

    set_hooks(&libc_hooks);
    p = malloc(size);
    get_hooks(&libc_hooks);

    log_callers("malloc(%zu) -> %p", size, p);

    reset_hooks();
    return p;
}

void
leak_checker_claim(const void *p)
{
    if (!file) {
        return;
    }

    if (p) {
        set_hooks(&libc_hooks);
        log_callers("claim(%p)", p);
        reset_hooks();
    }
}

static void
hook_free(void *p, const void *caller)
{
    if (!p) {
        return;
    }

    set_hooks(&libc_hooks);
    free(p);
    get_hooks(&libc_hooks);

    log_callers("free(%p)", p);

    reset_hooks();
}

static void *
hook_realloc(void *p, size_t size, const void *caller)
{
    void *q;

    set_hooks(&libc_hooks);
    q = realloc(p, size);
    get_hooks(&libc_hooks);

    if (p != q) {
        log_callers("realloc(%p, %zu) -> %p", p, size, q);
    }

    reset_hooks();

    return q;
}
#endif /* HAVE_MALLOC_HOOKS */
