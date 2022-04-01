#include "CNote.hpp"

CNote::CNote()
{
    is_running = true;
    current_keypress = 0;
    records = {};
}

void CNote::GetInputChar()
{
    std::string input_string = {};
    char c = 0;
    
    std::cout << "~ ";
    
    c = std::getchar();
    
    while(c != '\n')
    {
        input_string.push_back(c);
        c = std::getchar();
    }
    
    if((int)input_string.size() > 1 || (int)input_string.size() < 1)
    {
        current_keypress = 0;
    }
    else
    {
        current_keypress = input_string[0];
    }
}

void CNote::PrintLine(const std::string & line) const
{
    std::cout << line << std::endl;
}

std::string CNote::GetInputLine() const
{
    std::string input_line = {};
    char c = 0;
    
    c = std::getchar();
    
    while(c != '\n')
    {
        input_line.push_back(c);
        c = std::getchar();
    }
    
    return input_line;
}

void CNote::GenHTML(const std::string & category_name,
                    const std::string & note_name,
                    const std::string & export_name)
{
    if(utility.FileExists(EXPORTED_FOLDER + export_name + HTML_SUFFIX))
    {
        PrintLine(EXPORT_NAME_EXISTS);
        return;
    }
       
    std::ofstream html_output((EXPORTED_FOLDER + export_name + HTML_SUFFIX).data(), std::ostream::trunc);
    
    if(html_output.is_open())
    {
        html_output << "<HTML>" << '\n'
        << "<HEAD>" << '\n'
        << "<TITLE>" << export_name << "</TITLE>" << '\n'
        << "</HEAD>" << std::endl;
        
        html_output << "<BODY BGCOLOR=\"#FFFFCC\">" << '\n'
        << "<H1>" << export_name << "</H1>" << '\n';
        
        html_output << "<P>" << std::endl;
        
        
        std::ifstream input_file(NOTE_PATH(note_name, category_name).data());
        std::string tmp_string;
        
        while(!input_file.eof())
        {
            tmp_string.clear();
            std::getline(input_file, tmp_string);
            html_output << tmp_string.data() << "<br>" << std::endl;
        }
        
        html_output << "</P>" << std::endl;
        html_output << "</BODY>" << std::endl;
        html_output << "</HTML>" << std::endl;
        
        html_output.close();
    }
    else
    {
        PrintLine(EXPORT_FAIL);
        return;
    }
    
    PrintLine(EXPORT_SUCCESS);
}

void CNote::SearchTag() const
{
    PrintLine(TAG_SEARCH);
    std::string searched_tag = GetInputLine();
    
    if(searched_tag == "")
    {
        return;
    }
    
    std::vector<std::string> found_notes = {};
    std::vector<std::string> tmp_vector = {};
    std::string found_note = {};
    std::string tmp_string = {};
    
    std::ifstream tag_file(TAG_FILE.data());
    
    if(tag_file.is_open())
    {
        while(!tag_file.eof())
        {
            std::getline(tag_file, tmp_string);
            tmp_vector.push_back(tmp_string);
        }
    }
    else
    {
        PrintLine(SEARCH_FAIL);
        return;
    }
    
    for(const auto & line: tmp_vector)
    {
        if(line.find(searched_tag) != std::string::npos)
        {
            tmp_string.clear();
            int i = 0;
            
            while(line[i] != ' ')
            {
                tmp_string.push_back(line[i]);
                i++;
            }
            
            found_notes.push_back(tmp_string);
        }
    }
    
    for(const auto & res: found_notes)
    {
        std::cout << res << " ";
    }
    
    std::cout << std::endl;
}

void CNote::SearchContent()
{
    PrintLine(SEARCH_LINE);
    std::string searched_content = GetInputLine();
    
    if(searched_content == "")
    {
        return;
    }
    
    std::vector<std::string> found_notes = {};

        // std::cout << NOTE_PATH("note_name", CAT_STD) << std::endl;

    SearchInCategory(found_notes, searched_content, CAT_STD);
    SearchInCategory(found_notes, searched_content, CAT_TODO);
    SearchInCategory(found_notes, searched_content, CAT_SHOPPING);
    
    for(const auto & found_note : found_notes)
    {
        std::cout << found_note << " ";
    }
    
    std::cout << std::endl;
}

bool CNote::ExportTF(const std::string & category_name,
                     const std::string & note_name,
                     const std::string & export_name)
{    
    if(!utility.FileExists(NOTE_PATH(note_name, category_name)))
    {
        PrintLine(FILE_N_EXISTS);
        return false;
    }
    
    if(utility.FileExists(EXPORTED_FOLDER + export_name + TXT_SUFFIX))
    {
        PrintLine(EXPORT_NAME_EXISTS);
        return false;
    }
    
    std::ifstream note_file(NOTE_PATH(note_name, category_name));
    
    if(!note_file.is_open())
    {
        PrintLine(FILE_N_EXISTS);
        return false;
    }
    
    std::ofstream exp_file(EXPORTED_FOLDER + export_name + TXT_SUFFIX);

    if(!exp_file.is_open())
    {
        std::cout << "TADY FIAL" << std::endl;
        PrintLine(EXPORT_FAIL);
        return false;
    }
    
    exp_file <<
    CATEGORY <<
    category_name <<
    '\n' <<
    NOTE <<
    note_name <<
    '\n' <<
    note_file.rdbuf ();
    
    note_file.close();
    exp_file.close();
    
    PrintLine(EXPORT_SUCCESS);
    
    return true;
}

bool CNote::ImportNote(const std::string & note_name,
                       const std::string & path)
{
    std::ifstream imp_file(path);
    
    if(!imp_file.is_open())
    {
        PrintLine(FILE_N_EXISTS);
        return false;
    }
    
    std::ofstream note(NOTE_PATH(note_name, CAT_STD));
    
    if(!note.is_open())
    {
        PrintLine(FILE_CREATE_ERR);
        return false;
    }
    
    note << imp_file.rdbuf();
    
    imp_file.close();
    note.close();
    
    PrintLine(IMPORT_SUCCESS);
    return true;
}

void CNote::SearchInCategory(std::vector<std::string> & found_notes,
                             const std::string        & searched_content,
                             const std::string        & category)
{
    std::vector<std::string> folder_content = utility.GetDirContent(NOTE_FOLDER + category);
    
    for(const auto & note_file_txt : folder_content)
    {
        std::vector<std::string> lines = {};
        std::string tmp = {};
        std::string note = {};
        
        note = note_file_txt.substr(0, note_file_txt.length() - 5);
        
        std::ifstream note_file(NOTE_PATH(note, category));

        if(note_file.is_open())
        {
            while(!note_file.eof())
            {
                tmp.clear();
                std::getline(note_file, tmp);
                lines.push_back(tmp);
            }
        }
        
        int found_flag = 0;
        
        for(const auto & note_line : lines)
        {
            if(note_line.find(searched_content) != std::string::npos)
            {
                found_flag = 1;
            }
        }
        
        if(found_flag)
        {
            found_notes.push_back(category + ":" + note);
        }
    }
}
