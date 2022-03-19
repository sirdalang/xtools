/**
 * @file xconfig_imp.hpp
 * @author xxx
 * @brief 
 * @version 0.1
 * @date 2022-03-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <stdio.h>

#include <string>
#include <map>
#include <vector>
#include <mutex>

namespace NS_XTOOLS {
    class XConfig;
};

class NS_XTOOLS::XConfig
{
public:
    XConfig(const std::string &filename, bool readonly);
    ~XConfig();
    
    /**
     * @brief Load file into memory.
     * 
     * @return int Return 0 if successful or -1 if failed.
     */
    int LoadFile ();

    /**
     * @brief Get the Value object
     * 
     * @param section 
     * @param key 
     * @param default_value 
     * @param value 
     * @return int Return 0 if successful or -1 if failed.
     */
    int GetValue(const std::string &section, const std::string &key, const std::string &default_value, std::string &value);

    /**
     * @brief Set the Value object
     * 
     * @param section 
     * @param key 
     * @param value 
     * @return int Return 0 if successful or -1 if failed.
     */
    int SetValue (const std::string &section, const std::string &key, const std::string &value);

    /**
     * @brief Test if key exist.
     * 
     * @param section 
     * @param key 
     * @return true Exist.
     * @return false Not Exist.
     */
    bool Exist(const std::string &section, const std::string &key);

    /**
     * @brief Remove a key from config. If the section is empty after this key is 
     * removed, then the section will also be removed.
     * 
     * @param section 
     * @param key 
     * @return Return 0 if successful or -1 if failed.
     */
    int Remove(const std::string &section, const std::string &key);
private:
    int SyncFromBackFile__ ();
    int WriteToBackFile__ ();
    int LoadFromFile__ ();
    int ParseFile__();

    int DataSet (const std::string &section, const std::string &key, const std::string &value);
    int DataDelete (const std::string &section, const std::string &key);

private:
    const XConfig & operator= (const XConfig &) = delete;
    XConfig & operator= (XConfig &) = delete;
    XConfig (const XConfig &) = delete;
private:
    FILE *m_fp__;
    std::string m_filename__;
    std::string m_filename_bak__;
    bool m_readonly__;

    bool m_state_ok__;  // Indicate file load successfully.
    bool m_modify_state__;  // Indicate content changed but hasn't write to file yet.
    std::map<std::string, std::vector<std::string> > m_map_data__;
    std::mutex m_mutex__;
};