#include "xconfig_imp.hpp"

#include <stdio.h>
#include <string.h>

#include <xlog.h>

using namespace NS_XTOOLS;

static const char *module_name = "xconfig_imp";

XConfig::XConfig(const std::string &filename, bool readonly)
{
    m_file_loaded__ = false;
    m_filename__ = filename;
    m_readonly__ = readonly;
}

XConfig::~XConfig()
{
}

int XConfig::LoadFile()
{
    std::lock_guard<std::mutex> lock (m_mutex__);

    int ret = 0;

    ret = LoadFromFile__();

    if (0 == ret)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Load file successful\n");
        m_file_loaded__  = true;
    }
    else
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Load file failed\n");
    }

    return m_file_loaded__ ? 0 : -1;
}

int XConfig::GetValue(const std::string &section, const std::string &key,std::string &value)
{
    std::lock_guard<std::mutex> lock (m_mutex__);

    if (! m_file_loaded__)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Not loaded\n");
        return -1;
    }

    if (DataGet__(section, key, value) < 0)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Get data failed\n");
        return -1;
    }

    return 0;
}

int XConfig::SetValue(const std::string &section, const std::string &key, const std::string &value)
{
    std::lock_guard<std::mutex> lock (m_mutex__);

    if (! m_file_loaded__)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Not loaded\n");
        return -1;
    }

    if (m_readonly__)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Readonly mode\n");
        return -1;
    }

    if (DataSet__(section, key, value) < 0)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Data set failed\n");
        return -1;
    }

    if (WriteToFile__() < 0)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Write to file failed\n");
        return -1;
    }

    return 0;
}

bool XConfig::Exist(const std::string &section, const std::string &key)
{
    std::lock_guard<std::mutex> lock (m_mutex__);

    if (! m_file_loaded__)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Not loaded\n");
        return -1;
    }

    if (! DataExist__(section, key))
    {
        return false;
    }

    return true;
}

int XConfig::Erase(const std::string &section, const std::string &key)
{
    std::lock_guard<std::mutex> lock (m_mutex__);

    if (! m_file_loaded__)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Not loaded\n");
        return -1;
    }

    if (m_readonly__)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Readonly mode\n");
        return -1;
    }

    if (DataErase__(section, key) < 0)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Erase failed\n");
        return -1;
    }

    if (WriteToFile__() < 0)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Write to file failed\n");
        return -1;
    }

    return 0;
}

int XConfig::WriteToFile__()
{
    FILE *fp = nullptr;

    if (m_readonly__)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Can't write to file with readonly mode\n");
        return 0;
    }

    if (! m_file_loaded__)
    {
        xlog (module_name, XLOG_LEVEL_DEBUG, "Can't write to file while state not ready\n");
        return -1;
    }

    fp = fopen (m_filename__.c_str(), "wb+");
    if (nullptr == fp)
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Open file to write failed\n");
        return -1;
    }

    for (auto it_map = m_map_data__.cbegin(); it_map != m_map_data__.cend(); ++it_map)
    {
        if (it_map->second.empty())
        {
            xlog (module_name, XLOG_LEVEL_ERROR, "Section with no keys in map found\n");
            continue ;
        }

        fprintf (fp, "[%s]\n", it_map->first.c_str());

        for (auto it_item = it_map->second.cbegin(); it_item != it_map->second.cend(); ++it_item)
        {
            fprintf (fp, "%s=%s\n", 
                it_item->first.c_str(), 
                it_item->second.c_str());
        }

        fprintf (fp, "\n");
    }

    fclose (fp);
    fp = nullptr;

    return 0;
}

int XConfig::LoadFromFile__()
{
    size_t size = 0;
    ssize_t ret_ssize = 0;
    std::string cur_section;
    FILE *fp = nullptr;

    char *pc_line = nullptr;

    char *pc_line_section_head = nullptr;
    char *pc_line_section_tail = nullptr;
    char *pc_line_equal_sign = nullptr;
    char *pc_line_end = nullptr;

    fp = fopen (m_filename__.c_str(), "rb");
    if (nullptr == fp)
    {
        xlog (module_name, XLOG_LEVEL_DEBUG, "Open file failed trying loading file(%s)\n",
            m_filename__.c_str());
        return -1;
    }

    xlog (module_name, XLOG_LEVEL_DEBUG, "Data clear\n");
    m_map_data__.clear();

    /* Parse file line by line. */
    while ( (ret_ssize = getline (& pc_line, & size, fp)) >= 0)
    {
        if (ret_ssize == 0)
        {
            continue ;
        }

        pc_line_section_head = strstr (pc_line, "[");
        pc_line_section_tail = strstr (pc_line, "]");
        pc_line_equal_sign = strstr(pc_line, "=");
        pc_line_end = pc_line + strlen (pc_line);
        
        /* section */
        if (pc_line_section_head != nullptr
            && pc_line_section_tail != nullptr
            && pc_line_section_head < pc_line_section_tail)
        {
            cur_section = std::string (pc_line_section_head, pc_line_section_tail - pc_line_section_head);
            continue ;
        }

        if (cur_section.empty())
        {
            xlog (module_name, XLOG_LEVEL_ERROR, "Line without section found\n");
            continue;
        }

        /* key */
        if (pc_line_equal_sign != nullptr
            && pc_line < pc_line_equal_sign
            && pc_line_equal_sign + 1 < pc_line_end)
        {
            std::string key_tmp(pc_line, pc_line_equal_sign - pc_line);
            std::string value_tmp (pc_line_equal_sign + 1, pc_line_end - pc_line_equal_sign - 1);

            DataSet__(cur_section, key_tmp, value_tmp);
        }
    }

    if (nullptr != pc_line)
    {
        free (pc_line);
        pc_line = nullptr;
    }

    if (nullptr != fp)
    {
        fclose (fp);
        fp = nullptr;
    }

    return 0;
}

int XConfig::DataGet__ (const std::string &section, const std::string &key, std::string &value)
{
    auto it_section = m_map_data__.find (section);
    if (it_section == m_map_data__.cend())
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Get [%s.%s]: section not exist\n",
            section.c_str(), key.c_str());
        return -1;
    }

    auto it_item = it_section->second.find (key);
    if (it_item == it_section->second.cend())
    {
        xlog (module_name, XLOG_LEVEL_ERROR, "Get [%s.%s]: key not exist\n",
            section.c_str(), key.c_str());
        return -1;
    }

    if (it_item->second.empty())
    {
        xlog (module_name, XLOG_LEVEL_INFORMATION, "Value is empty\n");
    }

    value = it_item->second;

    return 0;
}

int XConfig::DataSet__ (const std::string &section, const std::string &key, const std::string &value)
{
    auto it_section = m_map_data__.find (section);
    if (it_section == m_map_data__.cend())
    {
        std::map<std::string, std::string> itemsMapTmp = {{key, value}};
        m_map_data__[section] = itemsMapTmp;
    }
    else
    {
        auto it_item = it_section->second.find (key);
        it_section->second[key] = value;
    }

    return 0;
}

bool XConfig::DataExist__ (const std::string &section, const std::string &key)
{
    auto it_section = m_map_data__.find (section);
    if (it_section == m_map_data__.cend())
    {
        xlog (module_name, XLOG_LEVEL_DEBUG, "Section not exist\n");
        return false;
    }

    auto it_item = it_section->second.find (key);
    if (it_item == it_section->second.cend())
    {
        xlog (module_name, XLOG_LEVEL_DEBUG, "Key not exist\n");
        return false;
    }

    return true;
}

int XConfig::DataErase__ (const std::string &section, const std::string &key)
{
    auto it_section = m_map_data__.find (section);
    if (it_section == m_map_data__.cend())
    {
        xlog (module_name, XLOG_LEVEL_DEBUG, "Section not exist\n");
        return 0;
    }

    auto it_item = it_section->second.find (key);
    if (it_item == it_section->second.cend())
    {
        xlog (module_name, XLOG_LEVEL_DEBUG, "Key not exist\n");
        return 0;
    }

    it_section->second.erase (it_item);
    if (it_section->second.empty())
    {
        m_map_data__.erase (it_section);
    }

    return 0;
}