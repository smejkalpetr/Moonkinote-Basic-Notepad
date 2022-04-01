#include "CUtilities.hpp"

bool CUtilities::FileExists(const std::string & file_path) const
{
    std::ifstream file(file_path.data());
    
    if(file.good() && file_path.length() != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CUtilities::CreateFile(const std::string & file_path) const
{
    std::ofstream file(file_path.data(), std::ostream::trunc);
    
    if(file.is_open())
    {
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string> CUtilities::GetDirContent(const std::string & dir_path) const
{
    std::vector<std::string> dir_content = {};
    
    DIR * dir_notes = opendir(dir_path.data());
    
    struct dirent * dir;
    
    while((dir = readdir(dir_notes)) != NULL)
    {
        std::string dir_name(dir->d_name);
        if(dir_name == "." || dir_name == "..")
        {
            continue;
        }
        else
        {
            dir_content.push_back(dir_name);
        }
    }
    
    closedir(dir_notes);
    
    return dir_content;
}
