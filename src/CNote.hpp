#ifndef CNote_hpp
#define CNote_hpp

#include "CUtilities.hpp"
#include "CTextEditor.hpp"

#include <string>
#include <vector>
#include <fstream>

/**
 * @brief This class is a superclass for any type of note.
 * 
 */
class CNote
{
public:
    CNote();
    virtual ~CNote() = default;

    /**
     * @brief Creates new note of its type.
     * 
     * @param note_name 
     * @return true 
     * @return false 
     */
    virtual bool                NewItem                 (const std::string & note_name) = 0;
    /**
     * @brief Edits note of its type.
     * 
     * @param note_name 
     * @return true 
     * @return false 
     */
    virtual bool                EditNote                (const std::string & note_name) = 0;
    /**
     * @brief Reads a note and saves it a an HTML File in the right format.
     * 
     * @param category_name 
     * @param note_name 
     * @param export_name 
     */
    void                        GenHTML                 (const std::string & category_name,
                                                         const std::string & note_name,
                                                         const std::string & export_name);
    /**
     * @brief Searches through tag_dev file and attempts to find a category and note match.
     * 
     */
    void                        SearchTag               () const;
    /**
     * @brief Reads what you are searching for. Searches throught all files and retruns all matches.
     * 
     */
    void                        SearchContent           ();
    /**
     * @brief Copies a note content into a new text file.
     * 
     * @param category_name 
     * @param note_name 
     * @param export_name 
     * @return true 
     * @return false 
     */
    bool                        ExportTF                (const std::string & category_name,
                                                         const std::string & note_name,
                                                         const std::string & export_name);
    /**
     * @brief Attempts to read a text file and if possible copies it into a note file and saves it.
     * 
     * @param note_name 
     * @param path 
     * @return true 
     * @return false 
     */
    bool                        ImportNote              (const std::string & note_name,
                                                         const std::string & path);

protected:
    /**
     * @brief Help to work with files.
     * 
     */
    CUtilities                  utility;
    /**
     * @brief When this gets false, you are out of the note editing menu.
     * 
     */
    bool                        is_running;
    /**
     * @brief Value of the last keypress.
     * 
     */
    int                         current_keypress;
    /**
     * @brief Contains all records of the current note.
     * 
     */
    std::vector<std::string>    records;
    
    /**
     * @brief Refreshes the note editing menu. Reads keypresses and decieds, what will be done.
     * 
     */
    virtual void                RefreshNote             () = 0;
    /**
     * @brief Processes current keypress.
     * 
     */
    virtual void                ProcessInput            () = 0;
    /**
     * @brief Adds new record or its kind to the records vector in the right format.
     * 
     */
    virtual void                AddRecord               () = 0;
    /**
     * @brief Deletes a record of it's kind in the records vector in the right format.
     * 
     */
    virtual void                DeleteRecord            () = 0;
    /**
     * @brief Shows the content of the records vector in the right format.
     * 
     */
    virtual void                ShowList                () const = 0;
    /**
     * @brief Prints a manual on how to work with the current note type.
     * 
     */
    virtual void                PrintHelp               () const = 0;
    /**
     * @brief Saves the current note in the right format.
     * 
     * @param note_name 
     * @return true 
     * @return false 
     */
    virtual bool                SaveNote                (const std::string & note_name) = 0;
    
    /**
     * @brief Reads a char from stdin and puts it into current_keypress variable.
     * 
     */
    void                        GetInputChar            ();
    /**
     * @brief Prints a line to stdout from the argument string.
     * 
     * @param line 
     */
    void                        PrintLine               (const std::string & line) const;
    /**
     * @brief Reads a line from stdin and returns it.
     * 
     * @return std::string 
     */
    std::string                 GetInputLine            () const;
    
private:
    /**
     * @brief Searches throught a category of notes that is being specified in arguments and searches for math of 'searched_content' in the notes.
     * 
     * @param found_notes 
     * @param searched_content 
     * @param category 
     */
    void                        SearchInCategory        (std::vector<std::string> & found_notes,
                                                         const std::string        & searched_content,
                                                         const std::string        & category);
    
};

#endif /* CNote_hpp */
