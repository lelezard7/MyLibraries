////#define UNICODE


//#include "Console_IO.h"

//#include <vector>
//#include <codecvt>
//#include <locale>

//typedef std::vector<e_string> History;

//static WINDOW* wnd_body_;
//static WINDOW* wnd_messagesArea_;

//static WINDOW* wnd_dataInput_;
//static FIELD*  field_dataInput_[2];
//static FORM*   form_dataInput_;

//static History dialogueHistory_;
//static History commandHistory_;


//static void loadData(
//        size_t& currentCursorPos_X,
//        e_string& inputtedText,
//        ai_string data);

//static void key_right(
//        size_t& currentCursorPos_X,
//        e_string inputtedText);

//static void key_left(
//        size_t& currentCursorPos_X);

//static void key_up(
//        size_t& currentCursorPos_X,
//        e_string& inputtedText,
//        size_t& currentHistoryMoment,
//        const History* history);

//static void key_down(
//        size_t& currentCursorPos_X,
//        e_string& inputtedText,
//        size_t& currentHistoryMoment,
//        const History* history);

//static void key_backspace(
//        size_t& currentCursorPos_X,
//        e_string& inputtedText);

//static void key_enter(
//        e_string& inputtedText,
//        ai_string* buffer,
//        History* history);

//static void key_F1();

//static void console_resize(
//        size_t& messagesAreaSize_X,
//        size_t& messagesAreaSize_Y,
//        size_t& messageHistoryStart,
//        e_string inputtedText);

//static void key_F7(
//        size_t currentCursorPos_X,
//        size_t& messagesAreaSize_X,
//        size_t& messagesAreaSize_Y,
//        size_t& messageHistoryStart,
//        e_string inputtedText);

//static void key_F8(
//        size_t currentCursorPos_X,
//        size_t& messagesAreaSize_X,
//        size_t& messagesAreaSize_Y,
//        size_t& messageHistoryStart,
//        e_string inputtedText);

//static void refreshConsole(
//        size_t& messagesAreaSize_X,
//        size_t& messagesAreaSize_Y,
//        size_t messageHistoryStart,
//        e_string inputtedText);

//ErrCode console_say(ai_string data, ai_string* buffer)
//{
//    if (buffer == nullptr)
//        return ERRCODE_ERROR;

//    size_t _messageHistoryStart = 0;
//    size_t _currentCursorPos_X = 0;
//    e_string _inputtedText;

////    hardCleaning_begin<wchar_t>(L"_inputtedText");

//    size_t _messagesAreaSize_X;
//    size_t _messagesAreaSize_Y;

//    History* _history;

//    if (getInputMode() == DialogueMode) {
//        _history = &dialogueHistory_;
//    }
//    else {
//        _history = &commandHistory_;
//    }
//    _history->push_back(es(""));

//    size_t _currentHistoryMoment = _history->size() - 1;

//    if (data != ais("")) {
//        loadData(_currentCursorPos_X, _inputtedText, data);
//    }

//    refreshConsole(_messagesAreaSize_X, _messagesAreaSize_Y, _messageHistoryStart, _inputtedText);
//    pos_form_cursor(form_dataInput_);


//    wint_t _ch;
//    while (true) {
//        wget_wch(wnd_body_, &_ch);

//        switch (_ch)
//        {
//        case KEY_RIGHT:
//            key_right(_currentCursorPos_X, _inputtedText);
//            continue;

//        case KEY_LEFT:
//            key_left(_currentCursorPos_X);
//            continue;

//        case KEY_UP:
//            key_up(_currentCursorPos_X, _inputtedText, _currentHistoryMoment, _history);
//            continue;

//        case KEY_DOWN:
//            key_down(_currentCursorPos_X, _inputtedText, _currentHistoryMoment, _history);
//            continue;

//        case KEY_BACKSPACE:
//            key_backspace(_currentCursorPos_X, _inputtedText);
//            continue;

//        case '\n':
//            key_enter(_inputtedText, buffer, _history);
//            return ERRCODE_TRUE;

//        case KEY_RESIZE:
//            console_resize(_messagesAreaSize_X, _messagesAreaSize_Y, _messageHistoryStart, _inputtedText);
//            continue;

//        case KEY_F(7):
//            key_F7(_currentCursorPos_X, _messagesAreaSize_X, _messagesAreaSize_Y, _messageHistoryStart, _inputtedText);
//            continue;

//        case KEY_F(8):
//            key_F8(_currentCursorPos_X, _messagesAreaSize_X, _messagesAreaSize_Y, _messageHistoryStart, _inputtedText);
//            continue;

//        case KEY_F(1):
//            key_F1();
//            return ERRCODE_FALSE;
//        }

//        _inputtedText.insert(_currentCursorPos_X, 1, _ch);
//        _currentCursorPos_X++;
//        form_driver_w(form_dataInput_, 0, _ch);
//    }

//    return ERRCODE_EXIT;
//}

//static void loadData(
//        size_t& currentCursorPos_X,
//        e_string& inputtedText,
//        ai_string data)
//{
//    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> _converter;
//    e_string _data = _converter.from_bytes(data);

//    size_t _dataSize = _data.size();
//    for (size_t i = 0; i < _dataSize; ++i) {

//        if (_data[0] == '\n') {
//            break;
//        }

//        if (_data[0] == '\t') {
//            _data.erase(0, 1);
//            inputtedText += es("    ");
//            currentCursorPos_X += 4;
//            continue;
//        }

//        inputtedText += _data[0];
//        currentCursorPos_X++;
//        _data.erase(0, 1);
//    }
//}

//static void key_right(
//        size_t& currentCursorPos_X,
//        e_string inputtedText)
//{
//    if(currentCursorPos_X == inputtedText.size())
//        return;

//    currentCursorPos_X++;
//    form_driver(form_dataInput_, REQ_NEXT_CHAR);
//}

//static void key_left(
//        size_t& currentCursorPos_X)
//{
//    if(currentCursorPos_X == 0)
//        return;

//    currentCursorPos_X--;
//    form_driver(form_dataInput_, REQ_PREV_CHAR);
//}

//static void key_up(
//        size_t& currentCursorPos_X,
//        e_string& inputtedText,
//        size_t& currentHistoryMoment,
//        const History* history)
//{
//    if (currentHistoryMoment == 0)
//        return;

//    currentHistoryMoment--;
//    inputtedText = (*history)[currentHistoryMoment];
//    form_driver(form_dataInput_, REQ_CLR_FIELD);

//    for (auto i : inputtedText) {
//        form_driver_w(form_dataInput_, 0, i);
//    }

//    currentCursorPos_X = 0;
//    form_driver(form_dataInput_, REQ_BEG_FIELD);
//}

//static void key_down(
//        size_t& currentCursorPos_X,
//        e_string& inputtedText,
//        size_t& currentHistoryMoment,
//        const History* history)
//{
//    if (currentHistoryMoment == history->size() - 1)
//        return;

//    currentHistoryMoment++;
//    inputtedText = (*history)[currentHistoryMoment];
//    form_driver(form_dataInput_, REQ_CLR_FIELD);

//    for (auto i : inputtedText) {
//        form_driver_w(form_dataInput_, 0, i);
//    }

//    currentCursorPos_X = 0;
//    form_driver(form_dataInput_, REQ_BEG_FIELD);
//}

//static void key_backspace(
//        size_t& currentCursorPos_X,
//        e_string& inputtedText)
//{
//    if (inputtedText.size() == 0 || currentCursorPos_X == 0)
//        return;

//    currentCursorPos_X--;

//    inputtedText.erase(currentCursorPos_X, 1);
//    form_driver(form_dataInput_, REQ_DEL_PREV);
//}

//static void closeInput();

//static void key_enter(
//        e_string& inputtedText,
//        ai_string* buffer,
//        History* history)
//{
//    form_driver(form_dataInput_, REQ_CLR_FIELD);
//    size_t _historySize = history->size();

//    if (inputtedText != es("") && inputtedText != (*history)[_historySize - 2]) {
//        (*history)[_historySize - 1] = inputtedText;
//    }

//    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> _converter;
//    *buffer = _converter.to_bytes(inputtedText);

//    e_string _prompt = getWindowPrompt();
//    if (_prompt == es("Сказать:"))
//        addConsoleMessage(es("Я: ") + inputtedText, NPAIR_USER_SAY);
//    else
//        addConsoleMessage(_prompt + es(" ") + inputtedText, NPAIR_USER_SAY);

//    closeInput();
//}

//static void key_F1()
//{
//    form_driver(form_dataInput_, REQ_CLR_FIELD);
//    closeInput();
//}


//static void closeInput()
//{
//    clearWindowPrompt();

//    unpost_form(form_dataInput_);
//    free_form(form_dataInput_);
//    form_dataInput_ = nullptr;

//    free_field(field_dataInput_[0]);
//    free_field(field_dataInput_[1]);
//    field_dataInput_[0] = nullptr;
//    field_dataInput_[1] = nullptr;

//    delwin(wnd_dataInput_);
//    wnd_dataInput_ = nullptr;

//    delwin(wnd_messagesArea_);
//    wnd_messagesArea_ = nullptr;

//    delwin(wnd_body_);
//    wnd_body_ = nullptr;
//}

//static void console_resize(
//        size_t& messagesAreaSize_X,
//        size_t& messagesAreaSize_Y,
//        size_t& messageHistoryStart,
//        e_string inputtedText)
//{
//    int _newWndSize_Y = getmaxy(stdscr);

//    if (_newWndSize_Y > messagesAreaSize_Y) {
//        if (consoleMessageCount() + 1 - messageHistoryStart == _newWndSize_Y - 4) {
//            if (messageHistoryStart != 0) {
//                messageHistoryStart--;
//            }
//        }
//    }

//    form_driver(form_dataInput_, REQ_CLR_FIELD);
//    refreshConsole(messagesAreaSize_X, messagesAreaSize_Y, messageHistoryStart, inputtedText);
//}

//static void key_F7(
//        size_t currentCursorPos_X,
//        size_t& messagesAreaSize_X,
//        size_t& messagesAreaSize_Y,
//        size_t& messageHistoryStart,
//        e_string inputtedText)
//{
//    if (messageHistoryStart == 0)
//        return;

//    messageHistoryStart--;

//    refreshConsole(messagesAreaSize_X, messagesAreaSize_Y, messageHistoryStart, inputtedText);
//    form_driver(form_dataInput_, REQ_BEG_FIELD);

//    for (size_t i = 0; i < currentCursorPos_X; ++i) {
//        form_driver(form_dataInput_, REQ_NEXT_CHAR);
//    }
//}

//static void key_F8(
//        size_t currentCursorPos_X,
//        size_t& messagesAreaSize_X,
//        size_t& messagesAreaSize_Y,
//        size_t& messageHistoryStart,
//        e_string inputtedText)
//{
//    if (consoleMessageCount() - messageHistoryStart <= messagesAreaSize_Y - 1)
//        return;

//    if (messageHistoryStart == consoleMessageCount() - 1)
//        return;

//    messageHistoryStart++;

//    refreshConsole(messagesAreaSize_X, messagesAreaSize_Y, messageHistoryStart, inputtedText);
//    form_driver(form_dataInput_, REQ_BEG_FIELD);

//    for (size_t i = 0; i < currentCursorPos_X; ++i) {
//        form_driver(form_dataInput_, REQ_NEXT_CHAR);
//    }
//}


//static void drawWindows(
//        size_t stdscrSize_X,
//        size_t stdscrSize_Y);

//static void refreshConsole(
//        size_t& messagesAreaSize_X,
//        size_t& messagesAreaSize_Y,
//        size_t messageHistoryStart,
//        e_string inputtedText)
//{
//    size_t _stdscrSize_X = getmaxx(stdscr);
//    size_t _stdscrSize_Y = getmaxy(stdscr);

//    drawWindows(_stdscrSize_X, _stdscrSize_Y);

//    messagesAreaSize_X = getmaxx(wnd_messagesArea_);
//    messagesAreaSize_Y = getmaxy(wnd_messagesArea_);


//    //Обновление содержимого поля ввода.
//    if (inputtedText != es("")) {
//        for (auto i : inputtedText) {
//            form_driver_w(form_dataInput_, 0, i);
//        }
//    }

//    //Обновляем переносы текста.
//    refreshTextWrapping(messagesAreaSize_X);

//    //Заполнение окна сообщений сообщениями.
//    size_t _messageIndex = consoleMessageCount() - 1;
//    ConsoleMessage* _consoleMessage;

//    size_t _start;
//    if ((messagesAreaSize_Y - 1) > consoleMessageCount()) {
//        _start = (messagesAreaSize_Y - 1) - ((messagesAreaSize_Y - 1) - consoleMessageCount());
//    }
//    else {
//        _start = messagesAreaSize_Y - 1;
//    }

//    for (size_t i = _start; i > 0 && _messageIndex - messageHistoryStart >= 0; --i, --_messageIndex) {
//        _consoleMessage = getConsoleMessage(_messageIndex - messageHistoryStart);

//        if (_consoleMessage == nullptr)
//            break;

//        wattrset(wnd_messagesArea_, COLOR_PAIR(_consoleMessage->color));
//        mvwprintw(wnd_messagesArea_, i, 2, "%ls", _consoleMessage->message.c_str());
//        wattrset(wnd_messagesArea_, COLOR_PAIR(NPAIR_MESSAGE));

//        wrefresh(wnd_messagesArea_);
//        continue;
//    }
//}

//static void drawWindows(size_t stdscrSize_X, size_t stdscrSize_Y)
//{
//    if (wnd_dataInput_ != nullptr) {
//        unpost_form(form_dataInput_);
//        free_form(form_dataInput_);
//        form_dataInput_ = nullptr;

//        free_field(field_dataInput_[0]);
//        free_field(field_dataInput_[1]);
//        field_dataInput_[0] = nullptr;
//        field_dataInput_[1] = nullptr;

//        delwin(wnd_dataInput_);
//        wnd_dataInput_ = nullptr;
//    }

//    if (wnd_messagesArea_ != nullptr) {
//        delwin(wnd_messagesArea_);
//        wnd_messagesArea_ = nullptr;
//    }

//    if (wnd_body_ != nullptr) {
//        delwin(wnd_body_);
//        wnd_body_ = nullptr;
//    }

//    //Главное окно.
//    wnd_body_ = newwin(stdscrSize_Y, stdscrSize_X, 0, 0);
//    keypad(wnd_body_, TRUE);

//    refresh();

//    //Окно сообщений.
//    wnd_messagesArea_ = derwin(wnd_body_, stdscrSize_Y - 3, stdscrSize_X, 0, 0);
//    mvwhline(wnd_messagesArea_, 0, 1, 0, stdscrSize_X - 2);
//    mvwhline(wnd_messagesArea_, 0, 0, ACS_ULCORNER, 1);
//    mvwhline(wnd_messagesArea_, 0, stdscrSize_X - 1, ACS_URCORNER, 1);

//    mvwvline(wnd_messagesArea_, 1, 0, DialogAreaFormatting, stdscrSize_Y - 4);
//    mvwvline(wnd_messagesArea_, 1, stdscrSize_X - 1, 0, stdscrSize_Y - 4);

//    wrefresh(wnd_messagesArea_);

//    //Поле ввода.
//    field_dataInput_[0] = new_field(1, stdscrSize_X - 4, 1, 1, 30, 0);
//    field_dataInput_[1] = NULL;

//    field_opts_off(field_dataInput_[0], O_AUTOSKIP);

//    form_dataInput_ = new_form(field_dataInput_);
//    set_form_sub(form_dataInput_, derwin(wnd_body_, 3, stdscrSize_X - 3, stdscrSize_Y - 3, 1));

//    post_form(form_dataInput_);

//    //Рамка для однострочного поля ввода.
//    wnd_dataInput_ = derwin(wnd_body_, 3, stdscrSize_X, stdscrSize_Y - 3, 0);

//    if (getInputMode() == DialogueMode) {
//        wborder(wnd_dataInput_, InputField_Dialogue, 0, 0, 0, 0, 0, 0, 0);
//    }
//    else {
//        wborder(wnd_dataInput_, InputField_Command, 0, 0, 0, 0, 0, 0, 0);
//    }

//    e_string _windowPrompt = getWindowPrompt();
//    if (_windowPrompt != es("")) {
//        _windowPrompt = es(" ") + _windowPrompt + es(" ");
//        mvwprintw(wnd_dataInput_, 0, 3, "%ls", _windowPrompt.c_str());
//    }

//    wrefresh(wnd_dataInput_);
//}
