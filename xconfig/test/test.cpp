#include <stdio.h>

#include "xconfig.h"

int main()
{
    char buffer[64] = {};

    XCONFIG_HANDLE handle = xconfig_open ("xconfig_test.ini", false);

    xconfig_setvalue (handle, "window", "window_width", "800");
    xconfig_setvalue (handle, "window", "window_height", "600");

    xconfig_getvalue (handle, "window", "window_width", buffer, sizeof(buffer));
    printf ("window_width=%s\n", buffer);

    xconfig_getvalue (handle, "window", "window_height", buffer, sizeof(buffer));
    printf ("window_height=%s\n", buffer);

    xconfig_close (handle);

    return 0;
}