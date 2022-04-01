#ifndef CMenu_hpp
#define CMenu_hpp

#include "Constants.hpp"
#include "CUtilities.hpp"
#include "CNote.hpp"
#include "CNoteStd.hpp"
#include "CNoteToDo.hpp"
#include "CNoteShopping.hpp"

#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <locale>

/**
 * @brief Starting point of the app. From here you go to the other parts of the program.
 * 
 */
class CMenu
{
public:
                                CMenu                   ();
                                ~CMenu                  () = default;

    /**
     * @brief Starts the whole application - gets you into the main menu at first.
     * 
     */
    void                        RunApp                  ();

private:
    /**
     * @brief Declares class CUtilities. Is used for modifying and reading files.
     * 
     */
    CUtilities                  utility;
    /**
     * @brief This struct holds information about a note (defines it by note name and category). Also holds an unallowed char was read.
     * 
     */
    struct Note_Def
    {
        std::string             category_name;
        std::string             note_name;
        bool                    category_exists;
        bool                    note_exists;
        bool                    err_flag;
    };
    /**
     * @brief When this gets false, the app will close.
     * 
     */
    bool                        app_running;
    /**
     * @brief Current keypress of the user while in menu.
     * 
     */
    int                         menu_input;
    /**
     * @brief Prints the 'ASCII Art' moonkin picture to stdout.
     * 
     */
    void                        PrintMoonkin            () const;
    /**
     * @brief Prints the welcome message to stdout.
     * 
     */
    void                        PrintWelcomeMessage     () const;
    /**
     * @brief Print the gb message to stdout.
     * 
     */
    void                        PrintGoodbyeMessage     () const;
    /**
     * @brief Prints the line in argument to stdout.
     * 
     * @param line 
     */
    void                        PrintLine               (const std::string & line) const;
    /**
     * @brief Prints the menu options to stdout.
     * 
     */
    void                        ShowMenu                () const;
    /**
     * @brief Does the menu refresing after each keypress and decides what to do.
     * 
     */
    void                        RefreshMenu             ();
    /**
     * @brief Reads users input from stdin (one key).
     * 
     */
    void                        GetInputKey             ();
    /**
     * @brief Prints a message and then waits until newline. Only alfanumeral char are allowed and must be one word.  
     *   The word is then returned.
     * 
     * @param prompt_message 
     * @return std::string 
     */
    std::string                 GetInputWord            (const std::string & prompt_message) const;
    /**
     * @brief Prints out a message and reads until newline. Returns read string.
     * 
     * @param prompt_message 
     * @return std::string 
     */
    std::string                 GetInputLine            (const std::string & prompt_message) const;
    /**
     * @brief Decides what to do accoarding to input char.
     * 
     */
    void                        ProcessInput            ();
    
    /**
     * @brief Calls function on class CNote and creates a note that suits circumstances.
     * 
     */
    void                        NewNote                 () const;
    /**
     * @brief Calls function on class CNote and starts editig a note of a type.
     * 
     */
    void                        EditNote                () const;
    /**
     * @brief After reading category name, lists all notes in a category.
     * 
     */
    void                        ListCategory            () const;
    /**
     * @brief After identifying a note attempts to delete it.
     * 
     */
    void                        DeleteNote              () const;
    /**
     * @brief Calls method on CNote and imports a text note after getting it name from the user.
     * 
     */
    void                        ImportNote              () const;
    /**
     * @brief Reads note's path. Calls method on CNote and attempts to import a note as of std category.
     * 
     */
    void                        ExportTF                () const;
    /**
     * @brief Reads note category and name and then calls method on CNote and exoports the note as a text file.
     * 
     */
    void                        ExportHTML              () const;
    /**
     * @brief After reading the tag goes through dev_tags file and attpemts to find matches. Prints out the result.
     * 
     */
    void                        SearchTag               () const;
    /**
     * @brief Reads searched string and then goes throught all notes and searches for matches. Prints result.
     * 
     */
    void                        SearchContent           () const;
    /**
     * @brief Prints out help to stdout.
     * 
     */
    void                        ShowHelp                () const;
    /**
     * @brief Asks for category and note name. Check if only right characters were input. Checks if category and name exist.
     * 
     * @param note_id 
     */
    void                        GetNoteID               (Note_Def & note_id) const;
    /**
     * @brief Reads a string from the user and the puts it into dev_tags file.
     * 
     * @param note_name 
     * @param category_name 
     */
    void                        AddTags                 (const std::string & note_name,
                                                         const std::string & category_name) const;
    /**
     * @brief Removes a line in dev_tags file.
     * 
     * @param note_name 
     * @param category_name 
     */
    void                        RemoveTag               (const std::string & note_name,
                                                         const std::string & category_name) const;
    /**
     * @brief Checks what category of note is in struct note_id and returns ptr to object of the right note category. If no match, returns NULL.
     * 
     * @param note_id 
     * @return CNote* 
     */
    CNote *                     CheckNote               (Note_Def & note_id) const;
};

#endif /* CMenu_hpp */
