/*
MIT License

Copyright (c) 2021 sirdalang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


/**
 * @file xlog.h
 * @author xlog's author
 * @brief 
 * @version x.x
 * @date 2021-12-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum XLOG_LEVEL
{
    XLOG_LEVEL_TRACE        = 1 << 0,
    XLOG_LEVEL_DEBUG        = 1 << 1,
    XLOG_LEVEL_LOG          = 1 << 2,
    XLOG_LEVEL_INFORMATION  = 1 << 3,
    XLOG_LEVEL_ERROR        = 1 << 4,
    XLOG_LEVEL_CRITICAL     = 1 << 5,
    XLOG_LEVEL_BUTT         = 1 << 6,
} XLOG_LEVEL;

void xlog(const char *module, XLOG_LEVEL level, const char *format, ...);
void xlog_1(const char *module, XLOG_LEVEL level, const char *file, int line, const char *function, const char *format, ...);
void xlog_setmask(unsigned int mask);

#define xlog_debug(format, args...) xlog_1(0,XLOG_LEVEL_DEBUG,__FILE__,__LINE__,__FUNCTION__,format,##args)
#define xlog_log(format, args...) xlog_1(0,XLOG_LEVEL_LOG,__FILE__,__LINE__,__FUNCTION__,format,##args)
#define xlog_information(format, args...) xlog_1(0,XLOG_LEVEL_INFORMATION,__FILE__,__LINE__,__FUNCTION__,format,##args)
#define xlog_error(format, args...) xlog_1(0,XLOG_LEVEL_ERROR,__FILE__,__LINE__,__FUNCTION__,format,##args)
#define xlog_critical(format, args...) xlog_1(0, XLOG_LEVEL_CRITICAL,__FILE__,__LINE__,__FUNCTION__,format,##args)

#ifdef __cplusplus
}
#endif // __cplusplus