#ifndef CWindow_hpp
#define CWindow_hpp

#include "Constants.hpp"
#include "CBuffer.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <ncurses.h>

/**
 * @brief This class is used for Text Editor. It's the main window and it's functions. Also handles the ncurses init and term.
 * 
 */
class CWindow
{
public:
                                CWindow                 ();
    virtual                     ~CWindow                ();
    /**
     * @brief Starts the windows and initializes ncurses library.
     * 
     * @return true 
     * @return false 
     */
    bool                        RunWindow               ();
    
protected:
    /**
     * @brief Buffer of the window.
     * 
     */
    CBuffer buffer;
    /**
     * @brief Represents the mode of the window.
     * 
     */
    std::string                 window_status;
    /**
     * @brief If this is false the window terminates.
     * 
     */
    bool                        window_running;
    /**
     * @brief Current position of cursor on the x axis.
     * 
     */
    int                         cursor_x;
    /**
     * @brief Current position of cursor on the y axis.
     * 
     */
    int                         cursor_y;
    /**
     * @brief Current key press value.
     * 
     */
    int                         current_keypress;
    /**
     * @brief Status line displayed at the bottom of the screen.
     * 
     */
    std::string                 status_line;
    
    /**
     * @brief While loop that refreshes and updates the screen.
     * 
     */
    void                        RenderScreen            ();
    /**
     * @brief Reads a keypress from the user.
     * 
     */
    void                        GetInputKey             ();
    /**
     * @brief Moves cursor upwards.
     * 
     */
    void                        MoveCursorUp            ();
    /**
     * @brief Moves cursor downwards.
     * 
     */
    void                        MoveCursorDown          ();
        /**
     * @brief Moves cursor to the right.
     * 
     */
    void                        MoveCursorRight         ();
        /**
     * @brief Moves cursor to the left.
     * 
     */
    void                        MoveCursorLeft          ();

    /**
     * @brief Interface for checking current status and decide what to do.
     * 
     */
    virtual void                ChangeStatusCheck       () = 0;
    /**
     * @brief Interface to decide what to do if a key has been pressed.
     * 
     */
    virtual void                ProcessControlKey       () = 0;
    /**
     * @brief Interface to process a key stroke.
     * 
     */
    virtual void                ProcessInputKey         () = 0;
    /**
     * @brief Iterface to process a standard key.
     * 
     */
    virtual void                ProcessNormalKey        () = 0;
    /**
     * @brief Interface of implementation of standard key.
     * 
     */
    virtual void                StandardKey             () = 0;
        /**
     * @brief Interface of implementation of tab key.
     * 
     */
    virtual void                TabKey                  () = 0;
        /**
     * @brief Interface of implementation of backspace key.
     * 
     */
    virtual void                BackspaceKey            () = 0;
        /**
     * @brief Interface of implementation of delete key.
     * 
     */
    virtual void                DeleteKey               () = 0;
        /**
     * @brief Interface of implementation of enter key.
     * 
     */
    virtual void                EnterKey                () = 0;
        /**
     * @brief Prints out all the contents of the buffer to the screen.
     * 
     */
    virtual void                PrintContent            () const = 0;
    /**
     * @brief Prints out the whole status line to the screen.
     * 
     */
    virtual void                PrintStatus             () const = 0;

private:
    /**
     * @brief Initializes ncurses.
     * 
     * @return true 
     * @return false 
     */
    bool                        InitWindow              ();
    /**
     * @brief Terminates ncurses library.
     * 
     */
    void                        TerminateWindow         ();
    /**
     * @brief Prints out an error message that varies depending on the error_text.
     * 
     * @param error_text 
     */
    void                        ErrorMessage            (const std::string & error_text) const;
    
};

#endif /* CWindow */
