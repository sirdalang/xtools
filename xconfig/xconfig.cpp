
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
#include <string.h>

#include <xlog.h>

#include "xconfig_imp.hpp"

using namespace NS_XTOOLS;

static const char* module_name = "xconfig";

static void xconfig_close__(XConfig *pConfig)
{
    if (NULL != pConfig)
    {
        delete pConfig;
    }

    return ;
}

XCONFIG_HANDLE xconfig_open(const char *file, int readonly)
{
    bool bError = false;

    XConfig *pConfig = NULL;

    do 
    {
        pConfig = new XConfig (std::string (file), readonly);

        if (pConfig->LoadFile())
        {
            bError = true;
        }
    }
    while (0);

    if (bError)
    {
        xconfig_close__ (pConfig);
    }

    return bError ? (XCONFIG_HANDLE)NULL : (XCONFIG_HANDLE)pConfig;
}

int xconfig_close(XCONFIG_HANDLE handle)
{
    XConfig *pConfig = (XConfig*)handle;

    xconfig_close__ (pConfig);

    return 0;
}

int xconfig_getvalue(XCONFIG_HANDLE handle, const char *section, const char *key, char *value, int size)
{
    XConfig *pConfig = (XConfig*)handle;
    std::string str_value;

    if (nullptr == pConfig)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Null handle\n");;
        return -1;
    }

    if (pConfig->GetValue(std::string(section), std::string(key), str_value) < 0)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Get value failed\n");
        return -1;
    }

    if (str_value.length() >= size)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Buffer too small\n");
        return -1;
    }

    strcpy (value, str_value.c_str());
    size = str_value.length();

    return 0;
}

int xconfig_setvalue(XCONFIG_HANDLE handle, const char *section, const char *key, const char *value)
{
    XConfig *pConfig = (XConfig*)handle;

    if (nullptr == pConfig)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "NULL handle\n");
        return -1;
    }

    if (pConfig->SetValue(std::string(section), std::string(key), std::string(value)) < 0)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Set value failed\n");
        return -1;
    }

    return 0;
}

int xconfig_exist(XCONFIG_HANDLE handle, const char *section, const char *key)
{
    XConfig *pConfig = (XConfig*)handle;

    if (nullptr == pConfig)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "NULL handle\n");
        return -1;
    }

    if (pConfig->Exist(std::string(section), std::string(key)))
    {
        return true;
    }
    
    return false;
}

