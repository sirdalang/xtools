#include "xlog.h"

#define __STDC_WANT_LIB_EXT2__ 1

#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
#include <stdlib.h>

static pthread_mutex_t s_mutex = PTHREAD_MUTEX_INITIALIZER;
static int s_log_mask = 0xffffffff;

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
    int i = 0;

    /* Make sure this two arrays has the same length. */

    const char *array_name[XLOG_LEVEL_BUTT] = {
        "dbg",
        "log",
        "inf",
        "err",
        "cri",
    };
    const XLOG_LEVEL array_level[XLOG_LEVEL_BUTT] = {
        XLOG_LEVEL_DEBUG,
        XLOG_LEVEL_LOG,
        XLOG_LEVEL_INFORMATION,
        XLOG_LEVEL_ERROR,
        XLOG_LEVEL_CRITICAL,
    };

    for (i = 0; i < XLOG_LEVEL_BUTT; ++i)
    {
        if (array_level[i] == level)
        {
            return array_name[i];
        }
    }

    return "unknown";
}

void xlog_setmask(unsigned int mask)
{
    s_log_mask = mask;
    return ;
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

    if (! (level & s_log_mask))
    {
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