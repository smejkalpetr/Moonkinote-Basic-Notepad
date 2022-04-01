#include "CNoteStd.hpp"

bool CNoteStd::NewItem(const std::string & note_name)
{
    CTextEditor editor;
    editor.RunEditor(NOTE_PATH(note_name, CAT_STD));

    return true;
}

bool CNoteStd::EditNote(const std::string & note_name)
{
    CTextEditor editor;
    
    if(!editor.RunEditor(NOTE_PATH(note_name, CAT_STD)))
    {
        return false;
    }
    
    return true;
}
