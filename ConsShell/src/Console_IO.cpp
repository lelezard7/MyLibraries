//#define UNICODE

#include "Console_IO.h"

#include <vector>
#include <codecvt>
#include <locale>


static e_string windowPrompt_;
static std::vector<ConsoleMessage> consoleMessageHistory_;
static size_t messageGroup_;
static ai_char inputMode_ = DialogueMode;


ai_char getInputMode()
{
    return inputMode_;
}

bool changeInputMode(ai_char inputMode)
{
    if (inputMode != DialogueMode && inputMode != CommandMode)
        return false;

    inputMode_ = inputMode;
    return true;
}


bool findCharacter_textPhrase(ai_string text, ai_string* buffer)
{
    text = hardCleaning_begin(text);
    text = hardCleaning_end(text);

    if (text == ais(""))
        return false;

    if (text.size() < 2)
        return false;

    if (text[0] != Character_Control || text[1] != Character_TextPhrase)
        return false;

    text.erase(0, 2);

    if (buffer != nullptr)
        *buffer = text;

    return true;
}

ErrCode findCharacter_modeChange(ai_string text, ai_string* buffer, ai_char* mode)
{
    text = hardCleaning_begin(text);
    text = hardCleaning_end(text);

    if (text == ais(""))
        return ERRCODE_1;

    if (text.size() < 2)
        return ERRCODE_1;

    if (text[0] != Character_Control)
        return ERRCODE_1;

    ai_char _mode;
    switch (text[1])
    {
    case DialogueMode:	_mode = DialogueMode;	break;
    case CommandMode:	_mode = CommandMode;	break;

    default: return ERRCODE_2;
    }

    text.erase(0, 2);
    text = hardCleaning_begin(text);

    if (text.size() != 0)
        return ERRCODE_3;

    if (buffer != nullptr)
        *buffer = text;
    if (mode != nullptr)
        *mode = _mode;

    return ERRCODE_TRUE;
}

//bool findCharacter_cancel(ai_string text, ai_string* buffer)
//{
//    text = hardCleaning_begin(text);
//    text = hardCleaning_end(text);

//    if (text == ais(""))
//        return false;

//    if (text.size() < 2)
//        return false;

//    if (text[0] != Character_Control || text[1] != Character_Cancel)
//        return 0;

//    text.erase(0, 2);
////    text = removeSpaces_begin(text, true);

//    if (text.size() != 0)
//        return 3;

//    if (buffer != nullptr)
//        *buffer = text;

//    return 1;
//}

//ErrCode findCharacter_apply(ai_string text, ai_string* buffer)
//{
////    text = removeSpaces_begin(text, true);
////    text = removeSpaces_end(text, true);

//    if (text == ais(""))
//        return 0;
//    if (text.size() < 2)
//        return 0;

//    if (text[0] != character_control || text[1] != character_apply)
//        return 0;

//    text.erase(0, 2);
////    text = removeSpaces_begin(text, true);

//    if (text.size() != 0)
//        return 3;

//    if (buffer != nullptr)
//        *buffer = text;

//    return 1;
//}

//ErrCode find_command(ai_string text, ai_string* buffer)
//{
////    text = removeSpaces_begin(text, true);
////    text = removeSpaces_end(text, true);

//    if (text == ais(""))
//        return 0;

//    ai_string _command;
//    size_t _textSize = text.size();

//    for (size_t i = 0; i < _textSize; ++i) {
//        if (text[0] == ais(' ') || text[0] == ais('\t') || text[0] == ais('\0')) {
//            text.erase(0, 1);
////            text = removeSpaces_begin(text, true);
//            break;
//        }
//        _command += text[0];
//        text.erase(0, 1);
//    }

//    if (text.size() != 0)
//        return 3;

//    if (buffer != nullptr)
//        *buffer = _command;

//    return 1;
//}


void refreshTextWrapping(size_t wndSize_X)
{
    ConsoleMessage* _consoleMessage;
    ConsoleMessage* _nextConsoleMessage;
    e_string _messagePart;
    size_t _messageGroup;

    for (size_t i = 0; i < consoleMessageHistory_.size(); ++i) {
        _consoleMessage = &consoleMessageHistory_[i];

        //Создание переносов.
        if (_consoleMessage->message.size() > wndSize_X - 4) {
            _messageGroup = _consoleMessage->messageGroup;
            int _insertPadding = 0;

            while(true) {
                _messagePart = _consoleMessage->message;

                if (_messagePart.size() > wndSize_X - 4) {
                    _messagePart.erase(wndSize_X - 4);
                    _consoleMessage->message.erase(0, wndSize_X - 4);

                    ConsoleMessage _newConsoleMessage;
                    _newConsoleMessage.message = _messagePart;
                    _newConsoleMessage.color = _consoleMessage->color;
                    _newConsoleMessage.messageGroup = _messageGroup;

                    auto _it = consoleMessageHistory_.begin();
                    std::advance(_it, i + _insertPadding);
                    consoleMessageHistory_.insert(_it, _newConsoleMessage);

                    _insertPadding++;
                }
                else {
                    break;
                }
            }

            continue;
        }

        //Удаление переносов.
        if (_consoleMessage->message.size() < wndSize_X - 4 && i != consoleMessageHistory_.size() - 1) {
            _nextConsoleMessage = &consoleMessageHistory_[i + 1];

            if (_nextConsoleMessage->messageGroup != _consoleMessage->messageGroup)
                continue;

            size_t _freePos = (wndSize_X - 4) - _consoleMessage->message.size();
            _messagePart = _nextConsoleMessage->message;

            if (_messagePart.size() > _freePos) {
                _messagePart.erase(_freePos);

                _nextConsoleMessage->message.erase(0, _freePos);
                _consoleMessage->message += _messagePart;
            }
            else {
                _consoleMessage->message += _messagePart;
                _nextConsoleMessage->message.erase(0);
            }

            if (_nextConsoleMessage->message.size() == 0) {
                auto _it = consoleMessageHistory_.begin();
                std::advance(_it, i + 1);

                consoleMessageHistory_.erase(_it);
            }
        }
    }
}

size_t getFreeMessageGroup()
{
    size_t _messageGroup = messageGroup_;
    messageGroup_++;
    return _messageGroup;
}


void setWindowPrompt(e_string prompt)
{
    windowPrompt_ = prompt;
}

e_string getWindowPrompt()
{
    return windowPrompt_;
}

void clearWindowPrompt()
{
    windowPrompt_.clear();
}


ConsoleMessage::ConsoleMessage()
{
    message = es("");
    messageGroup = 0;
    color = -2;
}

ConsoleMessage::~ConsoleMessage()
{
    message.clear();
    messageGroup = 0;
    color = -2;
}


void addConsoleMessage(e_string message, int textColor)
{
    ConsoleMessage _consoleMessage;
    _consoleMessage.color = textColor;

    if (message[message.size() - 1] == '\n') {
        message.pop_back();
    }

    e_string _pair;
    for (size_t i = 0; i < message.size();) {
        if (message[i] == es('\t')) {
            message.erase(i, 1);

            message.insert(i, 4, es(' '));
            continue;
        }

        if (message[i] == es('\n')) {
            message.erase(i, 1);

            if (message.size() == 0)
                continue;

            _pair = message;
            _pair.erase(i);
            message.erase(0, i);

            _consoleMessage.message = _pair;
            _consoleMessage.messageGroup = getFreeMessageGroup();
            consoleMessageHistory_.push_back(_consoleMessage);
            i = 0;
            _pair.clear();
            continue;
        }
        ++i;
    }

    if (message.size() != 0) {
        _consoleMessage.message = message;
        _consoleMessage.messageGroup = getFreeMessageGroup();
        consoleMessageHistory_.push_back(_consoleMessage);
    }
}

bool insertConsoleMessage(e_string message, int textColor, size_t messageGroup, size_t index)
{
    if (index >= consoleMessageHistory_.size())
        return false;

    ConsoleMessage _consoleMessage;
    _consoleMessage.message = message;
    _consoleMessage.color = textColor;
    _consoleMessage.messageGroup = messageGroup;

    auto _it = consoleMessageHistory_.begin();
    std::advance(_it, index);
    consoleMessageHistory_.insert(_it, _consoleMessage);

    return true;
}

bool insertConsoleMessage(const ConsoleMessage& consoleMessage, size_t messageGroup, size_t index)
{
    if (index >= consoleMessageHistory_.size())
        return false;

    auto _it = consoleMessageHistory_.begin();
    std::advance(_it, index);
    consoleMessageHistory_.insert(_it, consoleMessage);

    return true;
}

bool deleteConsoleMessage(size_t index)
{
    if (index >= consoleMessageHistory_.size())
        return false;

    auto _it = consoleMessageHistory_.begin();
    std::advance(_it, index);

    consoleMessageHistory_.erase(_it);
    return true;
}

void clearConsoleMessageHistory()
{
    consoleMessageHistory_.clear();
}

ConsoleMessage* getConsoleMessage(size_t index)
{
    if (index >= consoleMessageHistory_.size())
        return nullptr;

    return &consoleMessageHistory_[index];
}

size_t consoleMessageCount()
{
    return consoleMessageHistory_.size();
}


void console_io_start()
{
//#ifdef __AI_LINUX__
    setlocale(LC_ALL, "ru_Ru.UTF-8");
    setlocale(LC_CTYPE, "ru_RU.UTF-8");
//#else
//    setlocale(LC_ALL, "ru_Ru");
//#endif

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    IOMessagesCollection iomessagesCollection;

    iomessagesCollection.flags		 = IOMC_ALL;
    iomessagesCollection.say		 = console_say;
    iomessagesCollection.editor		 = console_editor;
    iomessagesCollection.quote		 = console_quote;
    iomessagesCollection.error		 = console_error;
    iomessagesCollection.warning	 = console_warning;
    iomessagesCollection.info		 = console_info;
    iomessagesCollection.system_info = console_system_info;

    registerIOMessages(iomessagesCollection);

    if (!has_colors()) {
        addConsoleMessage(es("Консоль не поддерживает цвета!"), NPAIR_WARNING);
        return;
    }

    start_color();

    init_color(5, 0, 0, 0);   //TODO: Нестабильный способ создать черный фон.
    assume_default_colors(COLOR_WHITE, 5);

    init_pair(NPAIR_ERROR,     COLOR_RED,    5);
    init_pair(NPAIR_WARNING,   COLOR_YELLOW, 5);
    init_pair(NPAIR_INFO,      COLOR_BLUE,   5);
    init_pair(NPAIR_MESSAGE,   COLOR_WHITE,  5);
    init_pair(NPAIR_USER_SAY,  COLOR_WHITE,  COLOR_BLACK);
    init_pair(NPAIR_AI_SAY,    COLOR_WHITE,  COLOR_GREEN);
}

void console_io_stop()
{
    endwin();
}
