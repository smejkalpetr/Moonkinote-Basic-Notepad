#ifndef CBuffer_hpp
#define CBuffer_hpp

#include <vector>
#include <string>

/**
 * @brief Represents the buffer that is used by the CWindow class.
 * 
 */
class CBuffer
{
public:
                                CBuffer                 ();
                                ~CBuffer                () = default;
    /**
     * @brief Current line that you are working with in the class.
     * 
     */
    std::string                 current_line;
    /**
     * @brief This vector contains all lines that all together make the buffer.
     * 
     */
    std::vector<std::string>    lines;
    /**
     * @brief Appens a line to the end of the buffer (vector lines).
     * 
     */
    void                        AppendLine              ();
    /**
     * @brief Inserts line to some position in the buffer.
     * 
     * @param line 
     * @param pos 
     */
    void                        InsertLine              (std::string line,
                                                         const int & pos);
    /**
     * @brief Deletes a line in the buffer.
     * 
     * @param cursor_y 
     */
    void                        DeleteLine              (const int cursor_y);
};

#endif /* CBuffer_hpp */
