#include "xlog.h"

#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
#include <stdlib.h>

static pthread_mutex_t s_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief lock for xlog
 * 
 */
static void xlog_lock()
{
    pthread_mutex_lock (& s_mutex);
}

/**
 * @brief unlock for xlog
 * 
 */
static void xlog_unlock ()
{
    pthread_mutex_unlock(& s_mutex);
}

static const char *xlog_getlevel (XLOG_LEVEL level)
{
    const char *array_level[XLOG_LEVEL_BUTT] = {
        "dbg",
        "log",
        "inf",
        "err",
        "cri",
    };

    if (level >= XLOG_LEVEL_DEBUG && level < XLOG_LEVEL_BUTT)
    {
        return array_level[level];
    }

    return "unknown";
}

void xlog(const char *module, XLOG_LEVEL level, const char *file, int line, const char *function, const char *format, ...)
{
    va_list ap;
    char *pstr = NULL;
    int ret = 0;

    va_start (ap, format);

    ret = vasprintf (&pstr, format, ap);

    va_end (ap);

    if (ret < 0)
    {
        printf ("[xlog error]fail to alloc\n");
        return ;
    }

    xlog_lock ();
    if (NULL != file)
    {
        if (NULL != module)
        {
            printf ("[%s][%s][%s %d %s]", module, xlog_getlevel(level), file, line, function);
        }
        else
        {
            printf ("[%s][%s %d %s]", xlog_getlevel(level), file, line, function);
        }
    }
    else
    {
        if (NULL != module)
        {
            printf ("[%s][%s]", module, xlog_getlevel(level));
        }
        else
        {
            printf ("[%s]", xlog_getlevel(level));
        }
    }
    printf ("%s", pstr);
    xlog_unlock ();

    free (pstr);
    pstr = NULL;

    return ;
}