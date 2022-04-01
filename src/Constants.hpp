#ifndef Constants_hpp
#define Constants_hpp

#include <string>

/**
 * @brief Contains all macros and constants (such as program's calls, etc.).
 * 
 */

/* MACROS */
#define CTRL_KEY(p) ((p) & 0x1f)
#define NOTE_PATH(n, c) ("./src/Notes/" + (c) + "/" + (n) + ".note")
#define CATEGORY_PATH(c) ("./src/Notes/" + (c))

/* GENERAL */
const std::string WRONG_OPTION = "This is not a valid option, try again!";
const std::string NOTE_FAIL = "The note couldn't be created.";
const std::string UNALLOWED_NAME = "Unallowed name.";
const std::string CATEGORY = "CATEGORY: ";
const std::string NOTE = "NOTE: ";

/* CATEGORIES */
const std::string CAT_STD = "std";
const std::string CAT_TODO = "todo";
const std::string CAT_SHOPPING = "shopping";
const std::string CAT_NONE = "nocat";

/* FOLDERS */
const std::string NOTE_FOLDER = "./src/Notes/";
const std::string STD_FOLDER = "./src/Notes/std/";
const std::string TODO_FOLDER = "./src/Notes/todo/";
const std::string SHOPPING_FOLDER = "./src/Notes/shopping/";
const std::string EXPORTED_FOLDER = "./src/Exported/";

/* NOTES */
const std::string NOTE_NAME = "Enter the note's name: ";
const std::string NOTE_DEL_OK = "The note has been deleted.";
const std::string NOTE_DEL_FAIL = "Failed to delete the note.";
const std::string NOTE_SUFFIX = ".note";

/* OTHER FILES */
const std::string FILE_EXISTS = "This file already exists.";
const std::string FILE_N_EXISTS = "This file does not exist.";
const std::string FILE_SAVED = "The file has been saved.";
const std::string SAVING_FAILED = "Saving has failed.";
const std::string CATEGORY_N_EXISTS = "This category does not exist.";
const std::string FILE_CREATE_ERR = "Couldn't create a file.";
const std::string CATEGORY_NAME = "Enter category name: ";
const std::string TXT_SUFFIX = ".txt";
const std::string HTML_SUFFIX = ".html";
const std::string ENTER_NOTE_NAME = "Enter the note's name.";
const std::string NOTE_N_MODIFIED = "The note couldn't not be modified.";

/* EDITOR */
const std::string NORMAL_MODE = "Normal Mode";
const std::string INSERT_MODE = "Insert Mode";
const std::string PRESS_TO_NORMAL_MODE = "^N = Normal Mode";
const std::string RETURN_NORMAL_MODE = "Press ^N for return to Normal Mode.";
const std::string EDITOR_OPTIONS_NORMAL = "^I = Insert Mode, ^Q = Quit and Discard, ^D = Save and Quit, ^S = Save";
const std::string EDITOR_OPTIONS_INSERT = "^Q = Quit and Discard,^D = Save and Quit, ^S = Save";

/* NCURSES */
const std::string NCURSES_INIT_FAIL = "Couldn't initialize the NCurses library.";
const std::string NCURSES_RAW_FAIL = "Couldn't enter the raw mode.";
const std::string NCURSES_TERMINATE_FAIL = "Couldn't terminate the NCurses library.";

/* IMPORT & EXPORT*/
const std::string IMPORT_PROMPT = "Enter the path to the file to be imported: ";
const std::string IMPORT_SUCCESS = "The note has been imported successfully.";
const std::string EXPORT_PROMPT = "Enter the path to the file to be exported: ";
const std::string EXPORT_SUCCESS = "The note has been exported successfully.";
const std::string EXPORT_FAIL = "Exporting has failed.";
const std::string EXPORT_NAME = "Enter the exported note's name.";
const std::string EXPORT_NAME_EXISTS = "This name already exists, check the 'Exported' folder.";

/* TAGS */
const std::string TAG_FILE = "./src/dev_tags";
const std::string TAGS_PROMPT = "Enter tags (leave empty to skip): ";
const std::string TAG_SEARCH = "Enter the tag you are searching for: ";

/* SEARCH */
const std::string SEARCH_FAIL = "Searching has failed.";
const std::string SEARCH_LINE = "Enter the word/line you are searching for: ";

#endif /* Constants_hpp */
