#ifndef CNoteToDo_hpp
#define CNoteToDo_hpp

#include "CNote.hpp"

/**
 * @brief Represent a ToDo list. A specific note type that is being a subclass of CNote.
 * 
 */
class CNoteToDo : public CNote
{
public:
    CNoteToDo() = default;
    ~CNoteToDo() = default;
    
    /**
     * @brief Prints out the help and starts the loop that is waiting for a key to control the options. In the end saves the note.
     * 
     * @param note_name 
     * @return true 
     * @return false 
     */
    virtual bool                NewItem                 (const std::string & note_name) override;
    /**
     * @brief Reads a note from a file and starts the editing loop. In the end saves changes.
     * 
     * @param note_name 
     * @return true 
     * @return false 
     */
    virtual bool                EditNote                (const std::string & note_name) override;
    
protected:
    /**
     * @brief This is the main loop that handles input (by funtion) and then calls another fucntion to decide what will be done.
     * 
     */
    virtual void                RefreshNote             () override;
    /**
     * @brief Decides what will be done based on input key and calls adiquite function.
     * 
     */
    virtual void                ProcessInput            () override;
    /**
     * @brief Reads a line and add it as a new record to the vector of records in the right format.
     * 
     */
    virtual void                AddRecord               () override;
    /**
     * @brief Deletes a record from the vector.
     * 
     */
    virtual void                DeleteRecord            () override;
    /**
     * @brief Prints content of the records vector in the right format.
     * 
     */
    virtual void                ShowList                () const override;
    /**
     * @brief Prints out a manual.
     * 
     */
    virtual void                PrintHelp               () const override;
    /**
     * @brief Attempts to save content of the records vector into a file.
     * 
     * @param note_name 
     * @return true 
     * @return false 
     */
    virtual bool                SaveNote                (const std::string & note_name) override;
    
private:
    /**
     * @brief Changes a letter in a record which marks a record done.
     * 
     */
    void                        MarkDone                ();
};

#endif /* CNoteToDo_hpp */
