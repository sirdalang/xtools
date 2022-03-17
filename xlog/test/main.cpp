#include "xlog.h"

int main()
{
    xlog_debug ("this is a debug log: %d\n", 0);
    xlog_log ("this is a log log: %d\n", 0);
    xlog_information ("this is a information log: %d\n", 0);
    xlog_error ("this is a error log: %d\n", 0);
    xlog_critical ("this is a critical log: %d\n", 0);

    return 0;
}