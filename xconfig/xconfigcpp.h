/**
 * @file xconfigcpp.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <string>
#include <memory>

namespace NS_XTOOLS {
    class XConfig;
    class XConfigImp;
};

class NS_XTOOLS::XConfig
{
public:
    XConfig(const std::string &filename, bool readonly);

    int LoadFile();

    int GetValue (const std::string &section, const std::string &key, std::string &value);
    int SetValue (const std::string &section, const std::string &key, const std::string &value);
    bool Exist (const std::string &section, const std::string &key);
    int Erase (const std::string &section, const std::string &key);
private:
    XConfig (const XConfig& ) = delete;
    XConfig &operator= (const XConfig &) = delete;
private:
    std::unique_ptr<XConfigImp> d;
};