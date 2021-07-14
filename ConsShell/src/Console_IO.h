/**
 * Console_IO.h определяет функции ввода/вывода для консоли.
 */

#ifndef _CONSOLE_IO_
#define _CONSOLE_IO_

//#define UNICODE

#include "../core/include/AI.h"

#define DialogAreaFormatting   (es('#'))

#define FormattedArea          (es('#'))
#define UnformattedArea        (es('~'))

#define Answer_Yes             (es('y'))
#define Answer_No              (es('n'))
#define Answer_Edit            (es('e'))

#define InputField_Command     (es('>'))
#define InputField_Dialogue    (es('#'))

#define DialogueMode	       (es('D'))
#define CommandMode		       (es('C'))

#define Character_Control	   (es('#'))
#define Character_Apply		   (es('#'))
#define Character_TextPhrase   (es('"'))
#define Character_Cancel	   (es('!'))

//#ifdef __AI_LINUX__
#   include <ncursesw/ncurses.h>
#   include <ncursesw/form.h>

    typedef std::wstring    e_string;
    typedef wchar_t         e_char;

#   define to_e_string(var) (std::to_wstring(var))
#   define es(value)        (L##value)
//#endif

ai_char getInputMode();
bool changeInputMode(ai_char inputMode);

bool findCharacter_textPhrase(ai_string text, ai_string* buffer);
ErrCode findCharacter_modeChange(ai_string text, ai_string* buffer, ai_char* mode);
//ErrCode findCharacter_cancel(ai_string text, ai_string* buffer);

void refreshTextWrapping(size_t wndSize_X);
size_t getFreeMessageGroup();

void setWindowPrompt(e_string prompt);
e_string getWindowPrompt();
void clearWindowPrompt();

struct ConsoleMessage
{
    e_string message;
    size_t messageGroup;
    int color;

    ConsoleMessage();
    ~ConsoleMessage();
};

void addConsoleMessage(e_string message, int textColor);
bool insertConsoleMessage(e_string message, int textColor, size_t messageGroup, size_t index);
bool insertConsoleMessage(const ConsoleMessage& consoleMessage, size_t messageGroup, size_t index);
bool deleteConsoleMessage(size_t index);
void clearConsoleMessageHistory();
ConsoleMessage* getConsoleMessage(size_t index);
size_t consoleMessageCount();

ErrCode console_editor(ai_string message, ai_string* buffer);
ErrCode console_say(ai_string data, ai_string* buffer);

ErrCode console_quote(ai_string prompt, ai_string* buffer);

ErrCode console_system_info(ai_string message, ai_string* buffer);
ErrCode console_error(ai_string message, ai_string* buffer);
ErrCode console_warning(ai_string message, ai_string* buffer);
ErrCode console_info(ai_string message, ai_string* buffer);

#define NPAIR_MESSAGE   1
#define NPAIR_ERROR     2
#define NPAIR_WARNING   3
#define NPAIR_INFO      4
#define NPAIR_USER_SAY  5
#define NPAIR_AI_SAY    6

void console_io_start();
void console_io_stop();


#endif //_CONSOLE_IO_
