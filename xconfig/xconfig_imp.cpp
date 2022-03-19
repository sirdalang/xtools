#include "xconfig_imp.hpp"

#include <stdio.h>
#include <string.h>

#include <xlog.h>

using namespace NS_XTOOLS;

const char *module_name = "xconfig_imp";

XConfig::XConfig(const std::string &filename, bool readonly)
{
    m_fp__ = nullptr;
    m_state_ok__ = false;
    m_filename__ = filename;
    m_readonly__ = readonly;

    m_filename_bak__ = m_filename__ + ".bak";
}

XConfig::~XConfig()
{
    if (nullptr != m_fp__)
    {
        fclose (m_fp__);
        m_fp__ = nullptr;
    }
}

int XConfig::WriteToFile__()
{
    if (! m_state_ok__)
    {
        xlog (module_name, XLOG_LEVEL_DEBUG, "Can't write to file while state not ready\n");
        return -1;
    }

    for (auto it_map = m_map_data__.cbegin(); it_map != m_map_data__.cend(); ++it)
    {
        if (it_map->second.empty())
        {
            xlog (module_name, XLOG_LEVEL_ERROR, "Section with no keys in map found\n");
            continue ;
        }

        

        for (auto it_item = it_map->second.cbegin(); it_item != it_map->second.cend(); ++it_item)
        {

        }
    }
}

int XConfig::LoadFromFile__()
{
    if (! m_state_ok__)
    {
        /* Open file. */
        if (nullptr == m_fp__)
        {
            if (m_readonly__)
            {
                m_fp__ = fopen (m_filename__.c_str(), "rb");
            }
            else
            {
                m_fp__ = fopen (m_filename__.c_str(), "wb+");
            }

            if (nullptr == m_fp__)
            {
                xlog_error ("open file failed\n");
                xlog (module_name, XLOG_LEVEL_ERROR, )
            }
        }

        /* Loading file. */
        if (nullptr != m_fp__)
        {
            if (0 == ParseFile__())
            {
                m_state_ok__ = true;
            }
        }
    }

    return m_state_ok__ ? 0 : -1;
}

int XConfig::ParseFile__()
{
    size_t size = 0;
    ssize_t ret_ssize = 0;
    std::string cur_section;

    char *pc_line = nullptr;

    char *pc_line_section_head = nullptr;
    char *pc_line_section_tail = nullptr;
    char *pc_line_equal_sign = nullptr;
    char *pc_line_end = nullptr;

    xlog (module_name, XLOG_LEVEL_DEBUG, "Data clear\n");
    m_map_data__.clear();

    if (nullptr == m_fp__)
    {
        xlog_error ("File is not opened\n");
        return -1;
    }

    /* Parse file line by line. */
    while ( (ret_ssize = getline (& pc_line, & size, m_fp__)) >= 0)
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

            DataSet(cur_section, key_tmp, value_tmp);
        }
    }

    if (nullptr != pc_line)
    {
        free (pc_line);
        pc_line = nullptr;
    }

    return 0;
}