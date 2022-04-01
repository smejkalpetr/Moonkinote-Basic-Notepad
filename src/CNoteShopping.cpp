#include "CNoteShopping.hpp"

void CNoteShopping::RefreshNote()
{
    while(is_running)
    {
        GetInputChar();
        ProcessInput();
    }
}

bool CNoteShopping::NewItem(const std::string & note_name)
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

bool CNoteShopping::EditNote(const std::string & note_name)
{
    
    
    std::ifstream input_file(NOTE_PATH(note_name, CAT_SHOPPING).data());
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

void CNoteShopping::ProcessInput()
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
        case 'd':
            DeleteRecord();
            break;
        default:
            PrintLine(WRONG_OPTION);
            break;
    }
}

void CNoteShopping::PrintHelp() const
{
    std::cout
    << "Now you are eiditing a shopping list." << '\n'
    << "Enter 's' to show the list." << '\n'
    << "Enter 'a' to add a record to the list." << '\n'
    << "Enter 'd' to delete a record from the list." << '\n'
    << "Enter 'q' to quit and save the note."

    << std::endl;
}

void CNoteShopping::ShowList() const 
{
    int i = 0;
    
    for(const auto & record: records)
    {
        std::cout << "[" << i << "] " << record << '\n';
        i++;
    }
}

void CNoteShopping::AddRecord()
{
    std::string record = GetInputLine();
    records.push_back(record);
}

void CNoteShopping::DeleteRecord()
{
    int i = -1;
    std::cin >> std::ws >> i;
    std::getchar();
    
    if(!(i < 0 || i > (int)records.size() - 1))
    {
        records.erase(records.begin() + i);
    }
}

bool CNoteShopping::SaveNote(const std::string & note_name)
{
    if((int)records.size() < 1)
    {
        return true;
    }

    std::ofstream note_file(NOTE_PATH(note_name, CAT_SHOPPING).data(), std::ostream::trunc);
    
    if(note_file.is_open())
    {
        for(int i = 0; i < (int)records.size(); i++)
        {
            note_file << records[i] << std::endl;
        }
        
        note_file.close();
        
        return true;
    }
    else
    {
        std::cout << SAVING_FAILED << std::endl;
        return false;
    }
}
