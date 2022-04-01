#ifndef CNoteShopping_hpp
#define CNoteShopping_hpp

#include "CNote.hpp"

/**
 * @brief Represent a type of note - shopping list - and its functoins. CNote subclass.
 * 
 */
class CNoteShopping : public CNote
{
public:
                                CNoteShopping() = default;
                                ~CNoteShopping() = default;

    /**
     * @brief Handles the editing process and in the end saves the note.
     * 
     * @param note_name 
     * @return true 
     * @return false 
     */
    virtual bool                NewItem                 (const std::string & note_name) override;
    /**
     * @brief Loads a note from a file into a vector and then goes throught editing process. In the end saves changes.
     * 
     * @param note_name 
     * @return true 
     * @return false 
     */
    virtual bool                EditNote                (const std::string & note_name) override;
    
protected:
    /**
     * @brief Handles the input and decision what will be done.
     * 
     */
    virtual void                RefreshNote             () override;
    /**
     * @brief Decides what function will be called based on input key.
     * 
     */
    virtual void                ProcessInput            () override;
    /**
     * @brief Adds a new records into the vector in the right format.
     * 
     */
    virtual void                AddRecord               () override;
    /**
     * @brief Deletes a record from the vector of records.
     * 
     */
    virtual void                DeleteRecord            () override;
    /**
     * @brief Shows content of the records vector in the right format.
     * 
     */
    virtual void                ShowList                () const override;
    /**
     * @brief Prints out a manutal on how to work with the the note editing.
     * 
     */
    virtual void                PrintHelp               () const override;
    /**
     * @brief Attempts to save content of the records vector into a note file.
     * 
     * @param note_name 
     * @return true 
     * @return false 
     */
    virtual bool                SaveNote                (const std::string & note_name) override;
};

#endif /* CNoteShopping_hpp */
