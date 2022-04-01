#include "CNoteToDo.hpp"

void CNoteToDo::RefreshNote()
{
    while(is_running)
    {
        GetInputChar();
        ProcessInput();
    }
}

bool CNoteToDo::NewItem(const std::string & note_name)
{
    PrintHelp();
    
    RefreshNote();
    
    if(!SaveNote(note_name))
    {
        PrintLine(SAVING_FAILED);
        return false;
    }
    
    return true;
}

bool CNoteToDo::EditNote(const std::string & note_name)
{
    std::ifstream input_file(NOTE_PATH(note_name, CAT_TODO).data());
    std::string tmp = {};
    
    if(input_file.is_open())
    {
        while(!input_file.eof())
        {
            std::getline(input_file, tmp);
            records.push_back(tmp);
        }
    }
    else
    {
        return false;
    }
    
    PrintHelp();
    
    RefreshNote();
    
    if(!SaveNote(note_name))
    {
        return false;
    }
    
    return true;
}

void CNoteToDo::ProcessInput()
{
    switch(current_keypress)
    {
        case 'q':
            is_running = false;
            break;
        case 's':
            ShowList();
            break;
        case 'a':
            AddRecord();
            break;
        case 'c':
            MarkDone();
            break;
        case 'd':
            DeleteRecord();
            break;
        default:
            PrintLine(WRONG_OPTION);
            break;
    }
}

void CNoteToDo::ShowList() const
{
    int i = 0;
    
    for(const auto & record: records)
    {
        std::cout << "[" << i << "] " << record << '\n';
        i++;
    }
}

void CNoteToDo::AddRecord()
{
    std::string line = GetInputLine();
    std::string record = "N: " + line;
    
    records.push_back(record);
}

void CNoteToDo::DeleteRecord()
{
    int i = -1;
    std::cin >> std::ws >> i;
    std::getchar();
    
    if(!(i < 0 || i > (int)records.size() - 1))
    {
        records.erase(records.begin() + i);
    }
}

void CNoteToDo::MarkDone()
{
    int i = -1;
    std::cin >> std::ws >> i;
    std::getchar();
    
    if(!(i < 0 || i > (int)records.size() - 1))
    {
        records[i].replace(0, 1, "D");
    }
}

void CNoteToDo::PrintHelp() const
{
    std::cout
    << "Now you are eiditing a ToDo list." << '\n'
    << "Enter 's' to show the list." << '\n'
    << "Enter 'a' to add a record to the list." << '\n'
    << "Enter 'c' to mark a record as 'done'." << '\n'
    << "Enter 'd' to delete a record from the list." << '\n'
    << "Enter 'q' to quit and save the note."
    << std::endl;
}

bool CNoteToDo::SaveNote(const std::string & note_name)
{
    if((int)records.size() < 1)
    {
        return true;
    }

    std::ofstream note_file(NOTE_PATH(note_name, CAT_TODO).data(), std::ostream::trunc);
    
    if(note_file.is_open())
    {
        int i = 0;
        for(; i < (int)records.size() - 1; i++)
        {
            note_file << records[i] << std::endl;
        }
        
        note_file << records[i];
        
        note_file.close();
        
        return true;
    }
    else
    {
        std::cout << SAVING_FAILED << std::endl;
        return false;
    }
}
