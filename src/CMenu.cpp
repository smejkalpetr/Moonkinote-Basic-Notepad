#include "CMenu.hpp"

CMenu::CMenu()
{
    app_running = true;
    menu_input = -1;
}

void CMenu::RunApp()
{
    PrintWelcomeMessage();
    RefreshMenu();
    PrintGoodbyeMessage();
}

void CMenu::PrintMoonkin() const
{
    std::cout
    << '\n'
    << "   Y__Y" << '\n'
    << "  (O.o)" << '\n'
    << "(/(^^^)\\)" << '\n'
    << " _//''\\\\_" << '\n'
    << std::endl;
}

void CMenu::PrintWelcomeMessage() const
{
    PrintMoonkin();
    std::cout
    << "Welcome to Moonkinote!" << '\n'
    << "Type m and press enter to show the menu."
    << std::endl;
}

void CMenu::PrintGoodbyeMessage() const
{
    std::cout << "Goodbye, have a nice day!" << std::endl;
    PrintMoonkin();
}

void CMenu::PrintLine(const std::string & line) const
{
    std::cout << line << std::endl;
}

void CMenu::RefreshMenu()
{
    while(app_running)
    {
        GetInputKey();
        ProcessInput();
    }
}

void CMenu::ShowMenu() const
{
    std::cout
    << "n: New Note" << '\n'
    << "e: Edit a Note" << '\n'
    << "l: List a Category" << '\n'
    << "d: Delete a Note" << '\n'
    << "t: Export as a Text File" << '\n'
    << "h: Export as an HTML File" << '\n'
    << "i: Import a Text File" << '\n'
    << "f: Search by Name or Tag" << '\n'
    << "s: Search by Content" << '\n'
    << "p: Show Help"
    << std::endl;
}

void CMenu::GetInputKey()
{
    std::string input_string = {};
    char c = 0;
    
    std::cout << "> ";
    
    c = std::getchar();
    
    while(c != '\n')
    {
        input_string.push_back(c);
        c = std::getchar();
    }

    if((int)input_string.size() > 1 || (int)input_string.size() < 1)
    {
        menu_input = 0;
    }
    else
    {
        menu_input = input_string[0];
    }
}

std::string CMenu::GetInputWord(const std::string & prompt_message) const
{
    PrintLine(prompt_message);
    
    std::string input_line = {};
    char c = 'a';
    int err_flag = 0;
    
    std::cout << "> ";
    
    c = std::getchar();
    
    while(c != '\n')
    {
        if(!std::isalnum(c) && c != '\n')
        {
            err_flag = 1;
        }
        
        input_line.push_back(c);
        c = std::getchar();
    }
    
    if(err_flag)
    {
        return "?";
    }
    else
    {
        return input_line;
    }
}

std::string CMenu::GetInputLine(const std::string & prompt_message) const
{
    PrintLine(prompt_message);
    
    std::string input_line = {};
    char c = 0;
    
    std::cout << "> ";
    
    c = std::getchar();
    
    while(c != '\n')
    {
        input_line.push_back(c);
        c = std::getchar();
    }

    return input_line;
}

void CMenu::ProcessInput()
{
    switch(menu_input)
    {
        case 'm':
            ShowMenu();
            break;
        case 'n':
            NewNote();
            break;
        case 'e':
            EditNote();
            break;
        case 'l':
            ListCategory();
            break;
        case 'd':
            DeleteNote();
            break;
        case 't':
            ExportTF();
            break;
        case 'h':
            ExportHTML();
            break;
        case 'i':
            ImportNote();
            break;
        case 'f':
            SearchTag();
            break;
        case 's':
            SearchContent();
            break;
        case 'p':
            ShowHelp();
            break;
        case 'q':
            app_running = false;
            break;
        default:
            PrintLine(WRONG_OPTION);
            break;
    }
}

void CMenu::NewNote() const
{
    Note_Def note_def;
    GetNoteID(note_def);
    
    if(note_def.err_flag)
    {
        PrintLine(UNALLOWED_NAME);
        return;
    }
    
    if(!note_def.category_exists)
    {
        PrintLine(CATEGORY_N_EXISTS);
        return;
    }
    
    if(note_def.note_exists)
    {
        PrintLine(FILE_EXISTS);
        return;
    }
    
    AddTags(note_def.note_name, note_def.category_name);
    
    if(!utility.CreateFile(NOTE_PATH(note_def.note_name, note_def.category_name)))
    {
        PrintLine(FILE_CREATE_ERR);
        return;
    }
    
    CNote * note = CheckNote(note_def);
    
    if(!note->NewItem(note_def.note_name))
    {
        PrintLine(NOTE_FAIL);
    }
    
    if(note != NULL)
    {
        delete note;
    }
}

void CMenu::EditNote() const
{
    Note_Def note_def;
    GetNoteID(note_def);
    
    if(note_def.err_flag)
    {
        PrintLine(UNALLOWED_NAME);
        return;
    }
    
    if(!note_def.category_exists)
    {
        PrintLine(CATEGORY_N_EXISTS);
        return;
    }
    
    if(!note_def.note_exists)
    {
        PrintLine(FILE_N_EXISTS);
        return;
    }
    
    CNote * note = CheckNote(note_def);
    
    if(!note->EditNote(note_def.note_name))
    {
        PrintLine(NOTE_N_MODIFIED);
    }
    
    if(note != NULL)
    {
        delete note;
    }
}

void CMenu::ListCategory() const
{
    std::string category_name = GetInputWord(CATEGORY_NAME);
    
    if(category_name == "?" || category_name == "")
    {
        PrintLine(UNALLOWED_NAME);
        return;
    }
    
    std::vector<std::string> category_content = {};
    
    if(!utility.FileExists(CATEGORY_PATH(category_name)))
    {
        PrintLine(CATEGORY_N_EXISTS);
        return;
    }
    
    category_content = utility.GetDirContent(CATEGORY_PATH(category_name));
    
    for(const auto & note: category_content)
    {
        if(note.substr((int)note.length() - 5, (int)note.length()) == NOTE_SUFFIX)
        {
            std::cout << note.substr(0, (int)note.length() - 5) << " ";
        }
    }
    
    std::cout << std::endl;
}

void CMenu::DeleteNote() const
{
    Note_Def note_def;
    GetNoteID(note_def);
    
    if(note_def.err_flag)
    {
        PrintLine(UNALLOWED_NAME);
        return;
    }
    
    if(!note_def.category_exists)
    {
        PrintLine(CATEGORY_N_EXISTS);
        return;
    }
    
    if(!note_def.note_exists)
    {
        PrintLine(FILE_N_EXISTS);
        return;
    }

    if(remove(NOTE_PATH(note_def.note_name, note_def.category_name).data()) != 0)
    {
        PrintLine(NOTE_DEL_FAIL);
    }
    else
    {
        RemoveTag(note_def.note_name, note_def.category_name);
        PrintLine(NOTE_DEL_OK);
    }
}

void CMenu::ImportNote() const
{
    std::string path = GetInputLine(IMPORT_PROMPT);
    std::string note_name = GetInputWord(NOTE_NAME);
    
    if(note_name == "?" || note_name == "")
    {
        PrintLine(UNALLOWED_NAME);
        return;
    }
    
    if(utility.FileExists(NOTE_PATH(note_name, CAT_STD)))
    {
        PrintLine(FILE_EXISTS);
        return;
    }
    
    CNote * note = new CNoteStd();
    
    if(note->ImportNote(note_name, path))
    {
        AddTags(note_name, CAT_STD);
    }

    if(note != NULL)
    {
        delete note;
    }
}

void CMenu::ExportTF() const
{
    Note_Def note_def;
    GetNoteID(note_def);
    
    if(note_def.err_flag)
    {
        PrintLine(UNALLOWED_NAME);
        return;
    }
    
    if(!note_def.note_exists)
    {
        PrintLine(FILE_N_EXISTS);
        return;
    }
    
    std::string export_name = GetInputLine(EXPORT_NAME);
    
    CNote * note = new CNoteStd();
    
    note->ExportTF(note_def.category_name, note_def.note_name, export_name);

    if(note != NULL)
    {
        delete note;
    }
}

void CMenu::ExportHTML() const
{
    Note_Def note_def;
    GetNoteID(note_def);
    
    if(note_def.err_flag)
    {
        PrintLine(UNALLOWED_NAME);
        return;
    }
    
    if(!note_def.note_exists)
    {
        PrintLine(FILE_N_EXISTS);
        return;
    }
    
    std::string export_name = GetInputLine(EXPORT_NAME);
    
    CNote * note = CheckNote(note_def);
    
    note->GenHTML(note_def.category_name, note_def.note_name, export_name);
    
    if(note != NULL)
    {
        delete note;
    }
}

void CMenu::SearchTag() const
{    
    CNote * note = new CNoteStd();
    
    note->SearchTag();
    
    if(note != NULL)
    {
        delete note;
    }
}

void CMenu::SearchContent() const
{    
    CNote * note = new CNoteStd();
    
    note->SearchContent();
    
    if(note != NULL)
    {
        delete note;
    }
}

void CMenu::ShowHelp() const
{
    std::cout << "MOONKINOTE HELP" << '\n' << std::endl;
    
    std::cout << "n: Creates a new note. You will be asked" << '\n'
              << "to set the category at first (there are" << '\n'
              << "3 categories, which are std, todo and shopping)." << '\n'
              << "Then you will have to fill in the note" << '\n'
              << "name and optionally tags. Tags are only" << '\n'
              <<  "used for a more convinient search." << '\n' <<
    std::endl;
    
    std::cout << "l: Shows a list of notes of a category." << '\n' <<
    std::endl;
    
    std::cout << "e: Asks for the category and note name. Then" << '\n'
              << "you can start editing your note." << '\n' <<
    std::endl;
    
    std::cout << "d: After stating the note category and" << '\n'
              << "name, the note shall be deleted." << '\n' <<
    std::endl;
    
    std::cout << "t: This exports a note as a Text File." << '\n'
              << "The exported note can be found in ./Exported." << '\n' <<
    std::endl;

    std::cout << "h: Exports a note as an HTML File." << '\n'
              << "This file can be found in ./Exported dir." << '\n' <<
    std::endl;
    
    std::cout << "i: Only a text file can be imprted." << '\n'
              << "An imported note will always be assigned" << '\n'
              << "to the std category." << '\n' <<
    std::endl;

    std::cout << "f: This allows you to search a note" << '\n'
              << "by it's tags or name. Found notes are shown" << '\n'
              << "in category:note format." << '\n' <<
    std::endl;
    
    std::cout << "s: Searching by a word or part of a" << '\n'
              << "text in all notes. Found notes are displayed" << '\n'
              << "in the same format as mentioned above." << '\n' <<
    std::endl;
    
    std::cout << "ABOUT: " << '\n'
    << "Moonkinote was created as a semstral project" << '\n'
    << "for programming subject (PA2). I hope you are" << '\n'
    << "enjoying using Moonkinote." << '\n' <<
    std::endl;
}

void CMenu::GetNoteID(Note_Def & note_def) const
{
    note_def.category_name = GetInputWord(CATEGORY_NAME);
    note_def.note_name = GetInputWord(NOTE_NAME);
    note_def.category_exists = false;
    note_def.note_exists = false;
    note_def.err_flag = false;
    
    if(note_def.category_name == "?" || note_def.note_name == "?" ||
       note_def.category_name == ""  || note_def.note_name == "")
    {
        note_def.err_flag = true;
    }
    
    if(utility.FileExists(CATEGORY_PATH(note_def.category_name)))
    {
        note_def.category_exists = true;
    }

    if(utility.FileExists(NOTE_PATH(note_def.note_name, note_def.category_name)))
    {
        note_def.note_exists = true;
    }
}

void CMenu::AddTags(const std::string & note_name,
                    const std::string & category_name) const
{
    std::string tags = GetInputLine(TAGS_PROMPT);
    
    if(tags == "")
    {
        return;
    }
    
    std::ofstream tag_file;
    tag_file.open(TAG_FILE.data(), std::ios::app);
    
    if(tag_file.is_open())
    {
        tag_file << category_name + ":" + note_name + ' ' + tags + '\n';
        
        tag_file.close();
    }
}

void CMenu::RemoveTag(const std::string & note_name,
                      const std::string & category_name) const
{
    std::vector<std::string> tmp_vector = {};
    std::string tmp_string = {};
    
    std::ifstream tag_file_in(TAG_FILE.data());
    
    if(tag_file_in.is_open())
    {
        while(!tag_file_in.eof())
        {
            std::getline(tag_file_in, tmp_string);
            tmp_vector.push_back(tmp_string);
        }
    }
    else
    {
        return;
    }
    
    int i = 0;
    
    for(const auto & tag : tmp_vector)
    {
        if(tag.find(category_name + ":" + note_name) != std::string::npos)
        {
            tmp_vector[i].erase();
        }
        i++;
    }
    
    std::ofstream tag_file_out;
    tag_file_out.open(TAG_FILE.data());
    
    if(tag_file_out.is_open())
    {
        for(const auto & tagline : tmp_vector)
        {
            tag_file_out << tagline;
        }
        
        tag_file_out.close();
    }
}

CNote * CMenu::CheckNote(Note_Def & note_def) const
{
    if(note_def.category_name == CAT_STD)
    {
        return new CNoteStd();
    }
    else if(note_def.category_name == CAT_TODO)
    {
        return new CNoteToDo();
    }
    else if(note_def.category_name == CAT_SHOPPING)
    {
        return new CNoteShopping();
    }
    
    return NULL;
}
