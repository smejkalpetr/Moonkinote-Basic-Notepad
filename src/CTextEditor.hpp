#ifndef CTextEditor_hpp
#define CTextEditor_hpp

#include "CWindow.hpp"
#include "CBuffer.hpp"

/**
 * @brief This class is a Text Editor with all its functions.
 * 
 */
class CTextEditor : public CWindow
{
public:
                                CTextEditor             ();
                                ~CTextEditor            () = default;
    /**
     * @brief Starts the editor and controls its process.
     * 
     * @param fname 
     * @return true 
     * @return false 
     */
    bool                        RunEditor               (const std::string & fname = "");
    
protected:
    /**
     * @brief Changes check if window mode has changes and decides what to do next.
     * 
     */
    virtual void                ChangeStatusCheck       () override;
    /**
     * @brief Decides what to do if a control key + key was pressed.
     * 
     */
    virtual void                ProcessControlKey       () override;
    /**
     * @brief Processes if the window mode should be changed or not.
     * 
     */
    virtual void                ProcessInputKey         () override;
    /**
     * @brief Decides what to do if a normal key is pressed.
     * 
     */
    virtual void                ProcessNormalKey        () override;
    /**
     * @brief Implementaion of standard key - if ctrl+'key' - decides what function will be called to execute such keystroke.
     * 
     */
    virtual void                StandardKey             () override;
    /**
     * @brief Implementation of tab key - same if four spaces were pressed.
     * 
     */
    virtual void                TabKey                  () override;
    /**
     * @brief Implementation of backspace key - if possible, deletes a char (left from cursor). Possibly moves one line leftwards.
     * 
     */
    virtual void                BackspaceKey            () override;
    /**
     * @brief Implementation of backspace key - if possible, deletes a char (right from cursor). Possibly moves one line rightwards.
     * 
     */
    virtual void                DeleteKey               () override;
    /**
     * @brief Implementation of enter key - moves the curor to the next line to its default position. Possibly moves the line down as well.
     * 
     */
    virtual void                EnterKey                () override;
    /**
     * @brief Prints out the whole buffer.
     * 
     */
    virtual void                PrintContent            () const override;
    /**
     * @brief Displays a status line in the bottom of the editor.
     * 
     */
    virtual void                PrintStatus             () const override;
    
private:
    /**
     * @brief Stores name of the current file that is being edited.
     * 
     */
    std::string                 file_name;
    
    /**
     * @brief Reads a file and stores it in buffer.
     * 
     * @return true 
     * @return false 
     */
    bool                        readFile                ();
    /**
     * @brief Save the buffer content into a file.
     * 
     * @return true 
     * @return false 
     */
    bool                        saveFile                ();
};

#endif /* CTextEditor_hpp */
