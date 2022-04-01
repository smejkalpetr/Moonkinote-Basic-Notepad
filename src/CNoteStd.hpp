#ifndef CNoteStd_hpp
#define CNoteStd_hpp

#include "CNote.hpp"

/**
 * @brief Represent a standard note. It's another type of note - subclass of CNote.
 * 
 */
class CNoteStd : public CNote
{
public:
                                CNoteStd() = default;
                                ~CNoteStd() = default;

    /**
     * @brief Opens the Text Editor for the new note specified in argument.
     * 
     * @param note_name 
     * @return true 
     * @return false 
     */
    virtual bool                NewItem                 (const std::string & note_name) override;
    /**
     * @brief Opens the Text Editor of an existing note.
     * 
     * @param note_name 
     * @return true 
     * @return false 
     */
    virtual bool                EditNote                (const std::string & note_name) override;
    
protected:    
    virtual void                RefreshNote             () override{};
    virtual void                ProcessInput            () override{};
    virtual void                AddRecord               () override{};
    virtual void                DeleteRecord            () override{};
    virtual void                ShowList                () const override{};
    virtual void                PrintHelp               () const override{};
    virtual bool                SaveNote                (const std::string & note_name) override
                                                        {return true;};
};

#endif /* CNoteStd_hpp */
