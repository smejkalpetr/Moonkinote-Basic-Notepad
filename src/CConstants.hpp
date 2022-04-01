#ifndef CConstants_hpp
#define CConstants_hpp

#include <string>

/* MACROS */
#define CTRL_KEY(p) ((p) & 0x1f)
#define NOTE_PATH(n, c) ("./Notes/" + (c) + "/" + (n) + ".note")
#define CATEGORY_PATH(c) ("./Notes/" + (c))

/* GENERAL */
const std::string WRONG_OPTION = "This is not a valid option, try again!";
const std::string NOTE_FAIL = "The note couldn't be created.";

/* CATEGORIES */
const std::string CAT_STD = "std";
const std::string CAT_TODO = "todo";
const std::string CAT_SHOPPING = "shopping";
const std::string CAT_NONE = "nocat";

/* FOLDERS */
const std::string NOTE_FOLDER = "./Notes/";
const std::string STD_FOLDER = "./Notes/std/";
const std::string TODO_FOLDER = "./Notes/todo/";
const std::string SHOPPING_FOLDER = "./Notes/shopping/";
const std::string EXPORTED_FOLDER = "./Exported/";

/* FILES */
const std::string FILE_EXISTS = "This file already exists.";
const std::string FILE_N_EXISTS = "This file does not exist.";
const std::string FILE_SAVED = "The file has been saved.";
const std::string SAVING_FAILED = "Saving has failed.";
const std::string CATEGORY_N_EXISTS = "This category does not exist.";
const std::string FILE_CREATE_ERR = "Couldn't create a file.";
const std::string CATEGORY_NAME = "Enter category name: ";
const std::string NOTE_NAME = "Enter the note's name: ";
const std::string NOTE_DEL_OK = "The note has been deleted.";
const std::string NOTE_DEL_FAIL = "Failed to delete the note.";
const std::string TAG_FILE = "./dev_tags";
const std::string NOTE_SUFFIX = ".note";
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

/* OTHERS */
const std::string UNEXPECTED_ERR = "An unexpected error has occured.";

#endif /* CConstants_hpp */
