
/**
 * @brief 
 * Some concepts here:
 * 
 * - No buffer read and write.
 * - Only file pointer.
 * 
 */

#include "xconfig.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <xlog.h>

#include "xconfig_strtools.h"

typedef struct 
{
    int bReadOnly;
    FILE *fp;
} XConfigCtx;

static void xconfig_close__(XConfigCtx *pCtx)
{
    if (NULL != pCtx)
    {
        if (NULL != pCtx->fp)
        {
            fclose (pCtx->fp);
            pCtx->fp = NULL;
        }
        free (pCtx);
        pCtx = NULL;
    }

    return ;
}

XCONFIG_HANDLE xconfig_open(const char *file, int readonly)
{
    int bError = false;

    XConfigCtx *pCtx = NULL;
    FILE *fp = NULL;

    do 
    {
        pCtx = (XConfigCtx*) malloc (sizeof(XConfigCtx));

        if (NULL == pCtx)
        {
            xlog_critical("Malloc failed\n");
            bError = true;
            break;
        }

        memset (pCtx, 0, sizeof(*pCtx));

        if (readonly)
        {
            fp = fopen (file, "rb");
        }
        else
        {
            fp = fopen (file, "wb+");
        }

        if (NULL == fp)
        {
            xlog_error ("Open file failed\n");
            bError = true;
            break;
        }

        pCtx->fp = fp;
        fp = NULL;

        break;    
    }
    while (0);

    if (bError)
    {
        xconfig_close__ (pCtx);
        pCtx = NULL;
    }

    return bError ? (XCONFIG_HANDLE)NULL : (XCONFIG_HANDLE)pCtx;
}

int xconfig_close(XCONFIG_HANDLE handle)
{
    XConfigCtx *pCtx = (XConfigCtx*)handle;

    xconfig_close__ (pCtx);

    return 0;
}

int xconfig_getvalue(XCONFIG_HANDLE handle, const char *section, const char *key, char *value, int *size)
{
    XConfigCtx *pCtx = (XConfigCtx*)handle;

    if (NULL == pCtx)
    {
        xlog_error ("NULL handle\n");
        return -1;
    }

    return 0;
}

int xconfig_setvalue(XCONFIG_HANDLE handle, const char *section, const char *key, const char *value)
{
    XConfigCtx *pCtx = (XConfigCtx*)handle;

    if (NULL == pCtx)
    {
        xlog_error ("NULL handle\n");
        return -1;
    }



    return 0;
}

int xconfig_exist(XCONFIG_HANDLE handle, const char *section, const char *key)
{
    XConfigCtx *pCtx = (XConfigCtx*)handle;

    if (NULL == pCtx)
    {
        xlog_error ("NULL handle\n");
        return -1;
    }
    
    return 0;
}

