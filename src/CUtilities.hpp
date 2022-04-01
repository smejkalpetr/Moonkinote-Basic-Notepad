#ifndef CUtilities_hpp
#define CUtilities_hpp

#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>

/**
 * @brief This class contains small utilities that help to work with files.
 * 
 */
class CUtilities
{
public:
    CUtilities() = default;
    ~CUtilities() = default;
    /**
     * @brief Checks if a file (for example a note) exists.
     * 
     * @param file_path 
     * @return true 
     * @return false 
     */
    bool                        FileExists              (const std::string & file_path) const;
    /**
     * @brief Creates an empty file on the given path.
     * 
     * @param file_path 
     * @return true 
     * @return false 
     */
    bool                        CreateFile              (const std::string & file_path) const;
    /**
     * @brief Iterates through all files in a folder and then returns those filenames.
     * 
     * @param dir_path 
     * @return std::vector<std::string> 
     */
    std::vector<std::string>    GetDirContent           (const std::string & dir_path) const;
};

#endif /* CUtilities_hpp */
