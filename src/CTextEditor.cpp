#include "CTextEditor.hpp"

CTextEditor::CTextEditor()
{
    window_status = NORMAL_MODE;
    status_line = EDITOR_OPTIONS_INSERT;
}

bool CTextEditor::RunEditor(const std::string & f_name)
{
    file_name = f_name;
    
    if(!readFile())
    {
        return false;
    }
    
    if(!RunWindow())
    {
        return false;
    }
    
    return true;
}

void CTextEditor::ChangeStatusCheck()
{
    std::string old_status = window_status;
    
    ProcessControlKey();
    
    if(old_status != window_status)
    {
        return;
    }
    else if(window_status == NORMAL_MODE)
    {
        ProcessNormalKey();
    }
    else if(window_status == INSERT_MODE)
    {
        ProcessInputKey();
    }
}

void CTextEditor::ProcessControlKey()
{
    switch(current_keypress)
    {
        case CTRL_KEY('i'):
            window_status = INSERT_MODE;
            status_line = PRESS_TO_NORMAL_MODE;
            break;
        case CTRL_KEY('n'):
            window_status = NORMAL_MODE;
            status_line = EDITOR_OPTIONS_NORMAL;
            break;
    }
}

void CTextEditor::ProcessInputKey()
{
    switch(current_keypress)
    {
        case KEY_UP:
            MoveCursorUp();
            break;
        case KEY_DOWN:
            MoveCursorDown();
            break;
        case KEY_RIGHT:
            MoveCursorRight();
            break;
        case KEY_LEFT:
            MoveCursorLeft();
            break;
        case KEY_BACKSPACE:
        case 127:
            BackspaceKey();
            break;
        case KEY_DC:
            DeleteKey();
            break;
        case KEY_ENTER:
        case 10:
            EnterKey();
            break;
        case KEY_BTAB:
        case KEY_CTAB:
        case KEY_STAB:
        case KEY_CATAB:
        case 9:
            TabKey();
            break;
        default:
            StandardKey();
            break;
    }
}

void CTextEditor::ProcessNormalKey()
{
    switch(current_keypress)
    {
        case CTRL_KEY('q'):
            window_running = false;
            break;
        case CTRL_KEY('s'):
            saveFile();
            break;
        case CTRL_KEY('d'):
            saveFile();
            window_running = false;
            break;
    }
}

void CTextEditor::StandardKey()
{
    
    if(cursor_x >= COLS)
    {
        return;
    }
    
    if(COLS <= (int)buffer.lines[cursor_y].length())
    {
        return;
    }
    
    buffer.lines[cursor_y].insert(cursor_x, 1, current_keypress);
    MoveCursorRight();
}

void CTextEditor::TabKey()
{
    buffer.lines[cursor_y].insert(cursor_x, "    ");
    cursor_x += 4;
}

void CTextEditor::BackspaceKey()
{
    if(cursor_x == 0 && cursor_y == 0)
    {
        return;
    }
    else if(cursor_x == 0 && cursor_y > 0)
    {
        cursor_x = (int)buffer.lines[cursor_y - 1].length();
        buffer.lines[cursor_y - 1] += buffer.lines[cursor_y];
        buffer.DeleteLine(cursor_y);
        MoveCursorUp();
    }
    else
    {
        buffer.lines[cursor_y].erase(--cursor_x, 1);
    }
}

void CTextEditor::DeleteKey()
{
    if(cursor_x == (int)buffer.lines[cursor_y].length() && cursor_y != (int)buffer.lines.size() - 1)
    {
        buffer.lines[cursor_y] += buffer.lines[cursor_y + 1];
        buffer.DeleteLine(cursor_y + 1);
    }
    else
    {
        buffer.lines[cursor_y].erase(cursor_x, 1);
    }
}

void CTextEditor::EnterKey()
{
    if(cursor_x < (int)buffer.lines[cursor_y].length())
    {
        buffer.InsertLine(buffer.lines[cursor_y].substr(cursor_x, buffer.lines[cursor_y].length() - cursor_x), cursor_y + 1);
        buffer.lines[cursor_y].erase(cursor_x, buffer.lines[cursor_y].length() - cursor_x);
    }
    else
    {
        buffer.InsertLine("", cursor_y + 1);
    }
    
    cursor_x = 0;
    MoveCursorDown();
}

void CTextEditor::PrintContent() const
{
    for(int i = 0; i < LINES - 1; i++)
    {
        if((int)buffer.lines.size() <= i)
        {
            move(i, 0);
            clrtoeol();
        }
        else
        {
            mvprintw(i, 0, buffer.lines[i].data());
        }
        
        clrtoeol();
    }
    
    move(cursor_y, cursor_x);
}

void CTextEditor::PrintStatus() const
{
    std::string printed_line = "~ " + window_status + ": " + status_line + " ~";
    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, printed_line.data());
    clrtoeol();
    attroff(A_REVERSE);
}

bool CTextEditor::readFile()
{
    std::ifstream input_file(file_name.data());
    
    if(input_file.is_open())
    {
        while(!input_file.eof())
        {
            buffer.current_line.clear();
            std::getline(input_file, buffer.current_line);
            buffer.AppendLine();
        }
        
        return true;
    }
    else
    {
        return false;
    }
}

bool CTextEditor::saveFile()
{
    std::ofstream note_file(file_name.data(), std::ostream::trunc);
    
    if(note_file.is_open())
    {
        for(int i = 0; i < (int)buffer.lines.size(); i++)
        {
            note_file << buffer.lines[i] << std::endl;
        }
        
        note_file.close();
        
        window_status = FILE_SAVED;
        status_line = RETURN_NORMAL_MODE;
        
        return true;
    }
    else
    {
        window_status = SAVING_FAILED;
        return false;
    }
}
