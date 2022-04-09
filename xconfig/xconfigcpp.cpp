
#include "xconfigcpp.h"
#include "xconfig_imp.hpp"

#include "xlog.h"

using namespace NS_XTOOLS;

XConfig::XConfig (const std::string &filename, bool readonly)
    : d(new XConfigImp(filename, readonly))
{
}

int XConfig::LoadFile()
{
    int ret = 0;
    ret = d->LoadFile();
    return ret;
}

int XConfig::GetValue(const std::string &section, const std::string &key, std::string &value)
{
    int ret = 0;
    ret = d->GetValue(section, key, value);
    return ret;
}

int XConfig::SetValue(const std::string &section, const std::string &key, const std::string &value)
{
    int ret = 0;
    ret = d->SetValue(section, key, value);
    return ret;
}

bool XConfig::Exist(const std::string &section, const std::string &key)
{
    int ret = 0;
    ret = d->Exist(section, key);
    return ret;
}

int XConfig::Erase(const std::string &section, const std::string &key)
{
    int ret = 0;
    ret = d->Exist(section, key);
    return ret;
}