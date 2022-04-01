#include "CWindow.hpp"

CWindow::CWindow()
{
    window_status = "Normal Mode";
    window_running = true;
    current_keypress = 0;
    status_line = {};
    cursor_x = 0;
    cursor_y = 0;
}

CWindow::~CWindow()
{
    TerminateWindow();
}

bool CWindow::RunWindow()
{
    if(!InitWindow())
    {
        return false;
    }
    
    RenderScreen();
    
    return true;
}

void CWindow::ErrorMessage(const std::string & error_text) const
{
    std::cout << "Error: " << error_text << std::endl;
}

bool CWindow::InitWindow()
{
    
    if(initscr() == NULL)
    {
        ErrorMessage(NCURSES_INIT_FAIL);
        return false;
    }
    
    if(raw() != OK)
    {
        ErrorMessage(NCURSES_RAW_FAIL);
        return false;
    }
    
    if(keypad(stdscr, true) != OK)
    {
        ErrorMessage(NCURSES_RAW_FAIL);
        return false;
    }
    
    return true;
}

void CWindow::TerminateWindow()
{
    if(endwin() != OK)
    {
        ErrorMessage(NCURSES_TERMINATE_FAIL);
    }
}

void CWindow::RenderScreen()
{
    while(window_running)
    {
        PrintStatus();
        PrintContent();
        GetInputKey();
        ChangeStatusCheck();
    }
}

void CWindow::GetInputKey()
{
    current_keypress = getch();
}

void CWindow::MoveCursorUp()
{
    if(cursor_y > 0)
    {
        cursor_y -= 1;
    }
    
    if(cursor_x >= (int)buffer.lines[cursor_y].length())
    {
        cursor_x = (int)buffer.lines[cursor_y].length();
    }
    
    move(cursor_y, cursor_x);
}

void CWindow::MoveCursorDown()
{
    if(cursor_y < (int)buffer.lines.size() - 1 && cursor_y + 1 < LINES - 1)
    {
        cursor_y += 1;
    }
    
    if(cursor_x >= (int)buffer.lines[cursor_y].length())
    {
        cursor_x = (int)buffer.lines[cursor_y].length();
    }
}

void CWindow::MoveCursorRight()
{
    if(cursor_x + 1 <= (int)buffer.lines[cursor_y].length() && COLS - 1 > cursor_x)
    {
        cursor_x += 1;
    }
    
    move(cursor_y, cursor_x);
}

void CWindow::MoveCursorLeft()
{
    if(cursor_x > 0)
    {
        cursor_x -= 1;
    }
    
    move(cursor_y, cursor_x);
}
