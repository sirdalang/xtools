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
    XLOG_LEVEL_DEBUG = 0,
    XLOG_LEVEL_LOG,
    XLOG_LEVEL_INFORMATION,
    XLOG_LEVEL_ERROR,
    XLOG_LEVEL_CRITICAL,
    XLOG_LEVEL_BUTT,
} XLOG_LEVEL;

void xlog(XLOG_LEVEL level, const char *file, int line, const char *function, const char *format, ...);

#define xlog_debug(format, ...) xlog(XLOG_LEVEL_DEBUG,__FILE__,__LINE__,__FUNCTION__,format,...)
#define xlog_log(format, ...) xlog(XLOG_LEVEL_DEBUG,__FILE__,__LINE__,__FUNCTION__,format,...)
#define xlog_infomation(format, ...) xlog(XLOG_LEVEL_DEBUG,__FILE__,__LINE__,__FUNCTION__,format,...)
#define xlog_error(format, ...) xlog(XLOG_LEVEL_DEBUG,__FILE__,__LINE__,__FUNCTION__,format,...)
#define xlog_critical(format, ...) xlog(XLOG_LEVEL_DEBUG,__FILE__,__LINE__,__FUNCTION__,format,...)

#ifdef __cplusplus
}
#endif // __cplusplus