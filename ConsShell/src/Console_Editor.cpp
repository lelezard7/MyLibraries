#include "Console_IO.h"

#include <vector>
#include <codecvt>
#include <locale>

typedef std::vector<e_string> Description;

static WINDOW* wnd_body_;
static WINDOW* wnd_editArea_;
static WINDOW* wnd_dialogueArea_;


static void loadData(
        ai_string data,
        Description& description);

static void key_right(
        size_t& currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t editAreaSize_X,
        size_t externalRowCount,
        const Description& description);

static void key_left(
        size_t& currentCursorPos_X,
        size_t currentCursorPos_Y);

static void key_up(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t& externalRowCount,
        const Description& description);

static void key_down(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t& externalRowCount,
        const Description& description);

static void key_backspace(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t& externalRowCount,
        Description& description);

static void key_delete(
        size_t currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t externalRowCount,
        Description& description);

static void key_enter(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t& externalRowCount,
        Description& description);

static void editor_resize(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t& dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t& externalRowCount,
        const Description& description);

static void key_F5(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t& dialogueAreaSize,
        size_t& externalRowCount_messageHistory,
        size_t externalRowCount,
        const Description& description);

static void key_F6(
        size_t currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t& dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t externalRowCount,
        const Description& description);

static void key_F7(
        size_t currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t& externalRowCount_messageHistory,
        size_t externalRowCount,
        const Description& description);

static void key_F8(
        size_t currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t& externalRowCount_messageHistory,
        size_t externalRowCount,
        const Description& description);

static ErrCode key_F1(
        size_t currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        ai_string* buffer,
        size_t externalRowCount,
        const Description& description);

static void refreshEditor(
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t externalRowCount,
        const Description& description);

ErrCode console_editor(ai_string data, ai_string* buffer)
{
    if(buffer == nullptr)
        return ERRCODE_ERROR;

    Description _description (1);
    size_t _externalRowCount = 0;

    size_t _dialogueAreaSize = 1;
    size_t _externalRowCount_messageHistory = 0;

    size_t _editAreaSize_X = 0;
    size_t _editAreaSize_Y = 0;
    size_t _currentCursorPos_X = 2;
    size_t _currentCursorPos_Y = 1;

    if (data != ais("")) {
        loadData(data, _description);
    }

    refreshEditor(_editAreaSize_X,
                  _editAreaSize_Y,
                  _dialogueAreaSize,
                  _externalRowCount_messageHistory,
                  _externalRowCount,
                  _description);
    wmove(wnd_editArea_, _currentCursorPos_Y , _currentCursorPos_X);
    wrefresh(wnd_editArea_);

    size_t _sizeCurrentTextLine;
    wint_t _ch;
    while (true) {
        wget_wch(wnd_body_, &_ch);

        switch (_ch)
        {
        case KEY_RIGHT:
            key_right(_currentCursorPos_X,
                      _currentCursorPos_Y,
                      _editAreaSize_X,
                      _externalRowCount,
                      _description);
            continue;

        case KEY_LEFT:
            key_left(_currentCursorPos_X,
                     _currentCursorPos_Y);
            continue;

        case KEY_UP:
            key_up(_currentCursorPos_X,
                   _currentCursorPos_Y,
                   _editAreaSize_X,
                   _editAreaSize_Y,
                   _dialogueAreaSize,
                   _externalRowCount_messageHistory,
                   _externalRowCount,
                   _description);
            continue;

        case KEY_DOWN:
            key_down(_currentCursorPos_X,
                     _currentCursorPos_Y,
                     _editAreaSize_X,
                     _editAreaSize_Y,
                     _dialogueAreaSize,
                     _externalRowCount_messageHistory,
                     _externalRowCount,
                     _description);
            continue;

        case KEY_BACKSPACE:
            key_backspace(_currentCursorPos_X,
                          _currentCursorPos_Y,
                          _editAreaSize_X,
                          _editAreaSize_Y,
                          _dialogueAreaSize,
                          _externalRowCount_messageHistory,
                          _externalRowCount,
                          _description);
            continue;

        case KEY_DC:
            key_delete(_currentCursorPos_X,
                       _currentCursorPos_Y,
                       _editAreaSize_X,
                       _editAreaSize_Y,
                       _dialogueAreaSize,
                       _externalRowCount_messageHistory,
                       _externalRowCount,
                       _description);
            continue;

        case '\n':
            key_enter(_currentCursorPos_X,
                      _currentCursorPos_Y,
                      _editAreaSize_X,
                      _editAreaSize_Y,
                      _dialogueAreaSize,
                      _externalRowCount_messageHistory,
                      _externalRowCount,
                      _description);
            continue;

        case KEY_RESIZE:
            editor_resize(_currentCursorPos_X,
                          _currentCursorPos_Y,
                          _editAreaSize_X,
                          _editAreaSize_Y,
                          _dialogueAreaSize,
                          _externalRowCount_messageHistory,
                          _externalRowCount,
                          _description);
            continue;

        case KEY_F(5):
            key_F5(_currentCursorPos_X,
                   _currentCursorPos_Y,
                   _editAreaSize_X,
                   _editAreaSize_Y,
                   _dialogueAreaSize,
                   _externalRowCount_messageHistory,
                   _externalRowCount,
                   _description);
            continue;

        case KEY_F(6):
            key_F6(_currentCursorPos_X,
                   _currentCursorPos_Y,
                   _editAreaSize_X,
                   _editAreaSize_Y,
                   _dialogueAreaSize,
                   _externalRowCount_messageHistory,
                   _externalRowCount,
                   _description);
            continue;

        case KEY_F(7):
            key_F7(_currentCursorPos_X,
                   _currentCursorPos_Y,
                   _editAreaSize_X,
                   _editAreaSize_Y,
                   _dialogueAreaSize,
                   _externalRowCount_messageHistory,
                   _externalRowCount,
                   _description);
            continue;

        case KEY_F(8):
            key_F8(_currentCursorPos_X,
                   _currentCursorPos_Y,
                   _editAreaSize_X,
                   _editAreaSize_Y,
                   _dialogueAreaSize,
                   _externalRowCount_messageHistory,
                   _externalRowCount,
                   _description);
            continue;

        case KEY_F(1):
            ErrCode _errCode = key_F1(_currentCursorPos_X,
                                        _currentCursorPos_Y,
                                        _editAreaSize_X,
                                        _editAreaSize_Y,
                                        _dialogueAreaSize,
                                        _externalRowCount_messageHistory,
                                        buffer,
                                        _externalRowCount,
                                        _description);

            if (_errCode == ERRCODE_1) {
                continue;
            }
            else {
                return _errCode;
            }
        }

        _sizeCurrentTextLine = _description[_currentCursorPos_Y - 1 + _externalRowCount].size();
        if (_currentCursorPos_X == _editAreaSize_X - 2 || _sizeCurrentTextLine + 2 >= _editAreaSize_X - 2)
            continue;

        _description[_currentCursorPos_Y - 1 + _externalRowCount].insert(_currentCursorPos_X - 2, 1, _ch);
        _currentCursorPos_X++;

        refreshEditor(_editAreaSize_X,
                      _editAreaSize_Y,
                      _dialogueAreaSize,
                      _externalRowCount_messageHistory,
                      _externalRowCount,
                      _description);
        wmove(wnd_editArea_, _currentCursorPos_Y , _currentCursorPos_X);
        wrefresh(wnd_editArea_);
    }

    return ERRCODE_EXIT;
}

static void loadData(
        ai_string data,
        Description& description)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> _converter;
    e_string _data = _converter.from_bytes(data);

    size_t _currentRow = 0;
    size_t _dataSize = _data.size();
    for (size_t i = 0; i < _dataSize; ++i) {

        if (_data[0] == '\n') {
            _data.erase(0, 1);
            description.push_back(es(""));
            _currentRow++;
            continue;
        }

        if (_data[0] == '\t') {
            _data.erase(0, 1);
            description[_currentRow] += es("    ");
            continue;
        }

        description[_currentRow] += _data[0];
        _data.erase(0, 1);
    }
}

static void key_right(
        size_t& currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t editAreaSize_X,
        size_t externalRowCount,
        const Description& description)
{
    size_t sizeCurrentTextLine = description[currentCursorPos_Y - 1 + externalRowCount].size();

    if (currentCursorPos_X == editAreaSize_X - 2 || currentCursorPos_X - 2 == sizeCurrentTextLine)
        return;

    currentCursorPos_X++;
    wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
    wrefresh(wnd_editArea_);
}

static void key_left(
        size_t& currentCursorPos_X,
        size_t currentCursorPos_Y)
{
    if (currentCursorPos_X == 2)
        return;

    currentCursorPos_X--;
    wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
    wrefresh(wnd_editArea_);
}

static void key_up(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t& externalRowCount,
        const Description& description)
{
    if (currentCursorPos_Y == 1) {
        if (externalRowCount == 0)
            return;

        externalRowCount--;
        refreshEditor(editAreaSize_X,
                      editAreaSize_Y,
                      dialogueAreaSize,
                      externalRowCount_messageHistory,
                      externalRowCount,
                      description);
    }
    else {
        currentCursorPos_Y--;
    }

    size_t sizeCurrentTextLine = description[currentCursorPos_Y - 1 + externalRowCount].size();
    if (currentCursorPos_X - 2 > sizeCurrentTextLine) {
        currentCursorPos_X = sizeCurrentTextLine + 2;
    }

    wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
    wrefresh(wnd_editArea_);
}

static void key_down(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t& externalRowCount,
        const Description& description)
{
    if (currentCursorPos_Y + externalRowCount == description.size()) {
        return;
    }

    if (currentCursorPos_Y == editAreaSize_Y - 2) {
        externalRowCount++;
        refreshEditor(editAreaSize_X,
                      editAreaSize_Y,
                      dialogueAreaSize,
                      externalRowCount_messageHistory,
                      externalRowCount,
                      description);
    }
    else {
        currentCursorPos_Y++;
    }

    size_t sizeCurrentTextLine = description[currentCursorPos_Y - 1 + externalRowCount].size();
    if (currentCursorPos_X - 2 > sizeCurrentTextLine) {
        currentCursorPos_X = sizeCurrentTextLine + 2;
    }

    wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
    wrefresh(wnd_editArea_);
}

static void key_backspace(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t& externalRowCount,
        Description& description)
{
    if (currentCursorPos_X != 2) {
        currentCursorPos_X--;
        description[currentCursorPos_Y - 1 + externalRowCount].erase(currentCursorPos_X - 2, 1);

        refreshEditor(editAreaSize_X,
                      editAreaSize_Y,
                      dialogueAreaSize,
                      externalRowCount_messageHistory,
                      externalRowCount,
                      description);
        wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
        wrefresh(wnd_editArea_);
        return;
    }

    if (currentCursorPos_Y == 1) {
        if (externalRowCount == 0) {
            return;
        }

        externalRowCount--;
    }

    size_t _sizeCurrentTextLine = description[currentCursorPos_Y - 1 + externalRowCount].size();

    if (_sizeCurrentTextLine == 0) {
        auto _it = description.begin();
        std::advance(_it, currentCursorPos_Y - 1 + externalRowCount);
        description.erase(_it);

        if (currentCursorPos_Y != 1) {
            currentCursorPos_Y--;
        }

        currentCursorPos_X = description[currentCursorPos_Y - 1 + externalRowCount].size() + 2;
    }
    else {
        if (currentCursorPos_Y != 1) {
            currentCursorPos_Y--;
        }

        _sizeCurrentTextLine = description[currentCursorPos_Y - 1 + externalRowCount].size();
        size_t _freePositions = (editAreaSize_X - 2) - (_sizeCurrentTextLine + 2);
        e_string _attachedText = description[currentCursorPos_Y + externalRowCount];

        if (_freePositions < _attachedText.size())
            _attachedText.erase(_freePositions);

        description[currentCursorPos_Y - 1 + externalRowCount] += _attachedText;
        description[currentCursorPos_Y + externalRowCount].erase(0, _freePositions);

        currentCursorPos_X = _sizeCurrentTextLine + 2;

        if (description[currentCursorPos_Y + externalRowCount].size() == 0) {
            auto _it = description.begin();
            std::advance(_it, currentCursorPos_Y + externalRowCount);
            description.erase(_it);
        }
    }

    refreshEditor(editAreaSize_X,
                  editAreaSize_Y,
                  dialogueAreaSize,
                  externalRowCount_messageHistory,
                  externalRowCount,
                  description);
    wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
    wrefresh(wnd_editArea_);
}

static void key_delete(
        size_t currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t externalRowCount,
        Description& description)
{
    size_t _sizeCurrentTextLine = description[currentCursorPos_Y - 1 + externalRowCount].size();

    //Если курсор находится в строке.
    if (currentCursorPos_X - 2 < _sizeCurrentTextLine) {
        description[currentCursorPos_Y - 1 + externalRowCount].erase(currentCursorPos_X - 2, 1);

        refreshEditor(editAreaSize_X,
                      editAreaSize_Y,
                      dialogueAreaSize,
                      externalRowCount_messageHistory,
                      externalRowCount,
                      description);
        wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
        wrefresh(wnd_editArea_);
        return;
    }

    //Если курсор находится в конце строки и следующей строки нету.
    size_t _rowCount = description.size();
    if (currentCursorPos_Y + externalRowCount == _rowCount) {
        return;
    }

    size_t _sizeNextTextLine = description[currentCursorPos_Y + externalRowCount].size();

    //Если курсор находится в конце строки, следующяя строка есть
    //и ее можно полностью перенести на эту строку.
    if (_sizeCurrentTextLine + 2 + _sizeNextTextLine <= editAreaSize_X - 2) {
        description[currentCursorPos_Y - 1 + externalRowCount] += description[currentCursorPos_Y + externalRowCount];

        auto _it = description.begin();
        std::advance(_it, currentCursorPos_Y + externalRowCount);
        description.erase(_it);

        refreshEditor(editAreaSize_X,
                      editAreaSize_Y,
                      dialogueAreaSize,
                      externalRowCount_messageHistory,
                      externalRowCount,
                      description);
        wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
        wrefresh(wnd_editArea_);
        return;
    }

    //Если курсор находится в конце экрана и следующяя строка есть.
    if (currentCursorPos_X == editAreaSize_X - 2) {

        if (_sizeNextTextLine == 0) {
            auto _it = description.begin();
            std::advance(_it, currentCursorPos_Y + externalRowCount);
            description.erase(_it);
        }
        else {
            description[currentCursorPos_Y + externalRowCount].erase(0, 1);
        }

        refreshEditor(editAreaSize_X,
                      editAreaSize_Y,
                      dialogueAreaSize,
                      externalRowCount_messageHistory,
                      externalRowCount,
                      description);
        wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
        wrefresh(wnd_editArea_);
        return;
    }

    //Если курсор находится в конце строки, следующяя строка есть,
    //но ее нельзя полностью перенести на эту строку.
    size_t _freePositions = (editAreaSize_X - 2) - (_sizeCurrentTextLine + 2);
    e_string _attachedText = description[currentCursorPos_Y + externalRowCount];

    _attachedText.erase(_freePositions);
    description[currentCursorPos_Y - 1 + externalRowCount] += _attachedText;
    description[currentCursorPos_Y + externalRowCount].erase(0, _freePositions);

    refreshEditor(editAreaSize_X,
                  editAreaSize_Y,
                  dialogueAreaSize,
                  externalRowCount_messageHistory,
                  externalRowCount,
                  description);
    wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
    wrefresh(wnd_editArea_);
}

static void key_enter(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t& externalRowCount,
        Description& description)
{
    e_string _textPart;

    //Если курсор находится внутри слова.
    size_t _sizeCurrentTextLine = description[currentCursorPos_Y - 1 + externalRowCount].size();

    if (currentCursorPos_X - 2 < _sizeCurrentTextLine) {
        _textPart = description[currentCursorPos_Y - 1 + externalRowCount];
        _textPart.erase(0, currentCursorPos_X - 2);
        description[currentCursorPos_Y - 1 + externalRowCount].erase(currentCursorPos_X - 2);
    }

    currentCursorPos_X = 2;

    //Если курсор находится на последней существующей строке.
    if (currentCursorPos_Y + externalRowCount >= description.size()) {

        if (currentCursorPos_Y == editAreaSize_Y - 2) {
            externalRowCount++;
        }
        else {
            currentCursorPos_Y++;
        }

        description.push_back(_textPart);

        refreshEditor(editAreaSize_X,
                      editAreaSize_Y,
                      dialogueAreaSize,
                      externalRowCount_messageHistory,
                      externalRowCount,
                      description);
        wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
        wrefresh(wnd_editArea_);
        return;
    }

    //Если курсор находится не на последней существующей строке.
    if (currentCursorPos_Y == editAreaSize_Y - 2) {
        externalRowCount++;
    }
    else {
        currentCursorPos_Y++;
    }

    auto _it = description.begin();
    std::advance(_it, currentCursorPos_Y - 1 + externalRowCount);
    description.insert(_it, _textPart);

    refreshEditor(editAreaSize_X,
                  editAreaSize_Y,
                  dialogueAreaSize,
                  externalRowCount_messageHistory,
                  externalRowCount,
                  description);
    wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
    wrefresh(wnd_editArea_);
}

static void editor_resize(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t& dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t& externalRowCount,
        const Description& description)
{
    size_t _newEditAreaSize_Y = getmaxy(wnd_editArea_);

    if (_newEditAreaSize_Y < editAreaSize_Y) {
        if (_newEditAreaSize_Y - 2 < description.size()) {

            size_t _stdscrSize = getmaxy(stdscr);
            if (dialogueAreaSize >= (_stdscrSize - 1) / 2 && dialogueAreaSize != 1) {
                dialogueAreaSize--;
            }
            else {
                externalRowCount++;

                if (currentCursorPos_Y > 1) {
                    currentCursorPos_Y--;
                }

                size_t sizeCurrentTextLine = description[currentCursorPos_Y - 1 + externalRowCount].size();
                if (currentCursorPos_X - 2 > sizeCurrentTextLine) {
                    currentCursorPos_X = sizeCurrentTextLine + 2;
                }
            }
        }
    }
    else {
        if (externalRowCount > 0) {
            externalRowCount--;
            currentCursorPos_Y++;

            size_t sizeCurrentTextLine = description[currentCursorPos_Y - 1 + externalRowCount].size();
            if (currentCursorPos_X - 2 > sizeCurrentTextLine) {
                currentCursorPos_X = sizeCurrentTextLine + 2;
            }
        }
    }

    refreshEditor(editAreaSize_X,
                  editAreaSize_Y,
                  dialogueAreaSize,
                  externalRowCount_messageHistory,
                  externalRowCount,
                  description);
    wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
    wrefresh(wnd_editArea_);
}

static void key_F5(
        size_t& currentCursorPos_X,
        size_t& currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t& dialogueAreaSize,
        size_t& externalRowCount_messageHistory,
        size_t externalRowCount,
        const Description& description)
{
    size_t _stdscrSize = getmaxy(stdscr);
    if (dialogueAreaSize >= (_stdscrSize - 1) / 2)
        return;

    if (currentCursorPos_Y >= editAreaSize_Y - 2) {
        currentCursorPos_Y--;

        if (dialogueAreaSize == 1) {
            currentCursorPos_Y--;
        }

        size_t sizeCurrentTextLine = description[currentCursorPos_Y - 1 + externalRowCount].size();
        if (currentCursorPos_X - 2 > sizeCurrentTextLine) {
            currentCursorPos_X = sizeCurrentTextLine + 2;
        }
    }

    dialogueAreaSize++;

    size_t _dialogAreaSize_Y = getmaxy(wnd_dialogueArea_);
    if (_dialogAreaSize_Y - 1 + externalRowCount_messageHistory >= consoleMessageCount()) {
        if (externalRowCount_messageHistory > 0)
            externalRowCount_messageHistory--;
    }

    refreshEditor(editAreaSize_X,
                  editAreaSize_Y,
                  dialogueAreaSize,
                  externalRowCount_messageHistory,
                  externalRowCount,
                  description);
    wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
    wrefresh(wnd_editArea_);
}

static void key_F6(
        size_t currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t& dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t externalRowCount,
        const Description& description)
{
    if (dialogueAreaSize == 1)
        return;

    dialogueAreaSize--;

    refreshEditor(editAreaSize_X,
                  editAreaSize_Y,
                  dialogueAreaSize,
                  externalRowCount_messageHistory,
                  externalRowCount,
                  description);
    wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
    wrefresh(wnd_editArea_);
}

static void key_F7(
        size_t currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t& externalRowCount_messageHistory,
        size_t externalRowCount,
        const Description& description)
{
    size_t _dialogAreaSize_Y = getmaxy(wnd_dialogueArea_);

    if (_dialogAreaSize_Y - 1 + externalRowCount_messageHistory < consoleMessageCount()) {
        externalRowCount_messageHistory++;

        refreshEditor(editAreaSize_X,
                      editAreaSize_Y,
                      dialogueAreaSize,
                      externalRowCount_messageHistory,
                      externalRowCount,
                      description);
        wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
        wrefresh(wnd_editArea_);
    }
}

static void key_F8(
        size_t currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t& externalRowCount_messageHistory,
        size_t externalRowCount,
        const Description& description)
{
    if (externalRowCount_messageHistory > 0) {
        externalRowCount_messageHistory--;

        refreshEditor(editAreaSize_X,
                      editAreaSize_Y,
                      dialogueAreaSize,
                      externalRowCount_messageHistory,
                      externalRowCount,
                      description);
        wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
        wrefresh(wnd_editArea_);
    }
}


static void closeEditor();

static ErrCode key_F1(
        size_t currentCursorPos_X,
        size_t currentCursorPos_Y,
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        ai_string* buffer,
        size_t externalRowCount,
        const Description& description)
{
    e_string _oldWndPrompt = getWindowPrompt();

    while (true) {
        wchar_t _question[50];
        swprintf(_question, 50, L"Coхранить? %lc-Да, %lc-Нет, %lc-Редактировать:", Answer_Yes, Answer_No, Answer_Edit);
        setWindowPrompt(e_string(_question));

        ai_string _answer;
        ErrCode _errCode = console_say(ais(""), &_answer);

        if (_errCode == ERRCODE_ERROR || _errCode == ERRCODE_EXIT) {
            closeEditor();
            return _errCode;
        }

        if (_answer == "y" && _errCode != ERRCODE_FALSE) {
            e_string _newBuffer;

            //Приводим введеные нами данные к нужному состоянию.
            for (e_string i : description) {
                _newBuffer += i + es('\n');
            }

            for (size_t i = _newBuffer.size() - 1; i >= 0; --i) {
                if (_newBuffer[i] == es(' ') || _newBuffer[i] == es('\t') || _newBuffer[i] == es('\0') || _newBuffer[i] == es('\n'))
                    _newBuffer.erase(i, 1);
                else
                    break;
            }
            _newBuffer +=  es("\n");

            //Возвращаем данные из Editor.
            buffer->clear();
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> _converter;
            *buffer = _converter.to_bytes(_newBuffer);

            closeEditor();
            return ERRCODE_TRUE;
        }

        else if (_answer == "e" && _errCode != ERRCODE_FALSE) {
            setWindowPrompt(_oldWndPrompt);

            refreshEditor(editAreaSize_X,
                          editAreaSize_Y,
                          dialogueAreaSize,
                          externalRowCount_messageHistory,
                          externalRowCount,
                          description);
            wmove(wnd_editArea_, currentCursorPos_Y , currentCursorPos_X);
            wrefresh(wnd_editArea_);

            return ERRCODE_1;
        }

        else if (_answer == "n" || _errCode == ERRCODE_FALSE) {
            closeEditor();
            return ERRCODE_FALSE;
        }

        else {
            wchar_t _errMessage[100];
            swprintf(_errMessage, 100,
                     L"Неверный ввод. Введите %lc(Да), %lc(Нет) или %lc(Редактировать)",
                     Answer_Yes, Answer_No, Answer_Edit);
            addConsoleMessage(e_string(_errMessage), NPAIR_WARNING);
            continue;
        }
    }
}


static void closeEditor()
{
    clearWindowPrompt();

    delwin(wnd_dialogueArea_);
    wnd_dialogueArea_ = nullptr;

    delwin(wnd_editArea_);
    wnd_editArea_ = nullptr;

    delwin(wnd_body_);
    wnd_body_ = nullptr;
}


static void drawWindows(
        size_t stdscrSize_X,
        size_t stdscrSize_Y,
        size_t dialogueAreaSize);

static void refreshEditor(
        size_t& editAreaSize_X,
        size_t& editAreaSize_Y,
        size_t dialogueAreaSize,
        size_t externalRowCount_messageHistory,
        size_t externalRowCount,
        const Description& description)
{
    //Отрисовка всех окон.
    size_t _stdscrSize_X = getmaxx(stdscr);
    size_t _stdscrSize_Y = getmaxy(stdscr);

    drawWindows(_stdscrSize_X, _stdscrSize_Y, dialogueAreaSize);

    //Обновление размеров окна редактирования.
    editAreaSize_X = getmaxx(wnd_editArea_);
    editAreaSize_Y = getmaxy(wnd_editArea_);

    //Заполнение окна редактирования.
    e_string _currentTextLine;

    for (size_t i = 1; i <= editAreaSize_Y - 2; ++i) {
        if (i + externalRowCount > description.size())
            break;

        mvwprintw(wnd_editArea_, i, 0, "%lc", FormattedArea);
        _currentTextLine = description[i - 1 + externalRowCount];
        mvwprintw(wnd_editArea_, i, 2, "%ls", _currentTextLine.c_str());
    }
    wrefresh(wnd_editArea_);

    //Обновляем переносы текста.
    size_t _dialogueAreaSize_X = getmaxx(wnd_dialogueArea_);
    refreshTextWrapping(_dialogueAreaSize_X);

    //Заполнение окна диалога.
    size_t _dialogueAreaSize_Y = getmaxy(wnd_dialogueArea_);

    for (size_t i = 1; i <= _dialogueAreaSize_Y && i - 1 + externalRowCount_messageHistory < consoleMessageCount(); ++i) {
        ConsoleMessage* _consoleMessage = getConsoleMessage(i - 1 + externalRowCount_messageHistory);

        wattrset(wnd_dialogueArea_, COLOR_PAIR(_consoleMessage->color));
        mvwprintw(wnd_dialogueArea_, i, 2, "%ls", _consoleMessage->message.c_str());
        wattrset(wnd_dialogueArea_, COLOR_PAIR(NPAIR_MESSAGE));
    }
    wrefresh(wnd_dialogueArea_);
}

static void drawWindows(
        size_t stdscrSize_X,
        size_t stdscrSize_Y,
        size_t dialogueAreaSize)
{
    //Главное окно.
    if (wnd_body_ != nullptr) {
        delwin(wnd_body_);
        wnd_body_ = nullptr;
    }

    wnd_body_ = newwin(stdscrSize_Y, stdscrSize_X, 0, 0);
    keypad(wnd_body_, TRUE);

    refresh();
    wrefresh(wnd_body_);

    //Окно редактирования.
    if (wnd_editArea_ != nullptr) {
        delwin(wnd_editArea_);
        wnd_editArea_ = nullptr;
    }

    if (dialogueAreaSize > 1) {
        size_t _editAreaSize_Y = stdscrSize_Y - dialogueAreaSize;
        wnd_editArea_ = derwin(wnd_body_, _editAreaSize_Y, stdscrSize_X, dialogueAreaSize, 0);
    }
    else {
        wnd_editArea_ = derwin(wnd_body_, stdscrSize_Y, stdscrSize_X, 0, 0);
    }

    wborder(wnd_editArea_, UnformattedArea, 0, 0, 0, 0, 0, 0, 0);

    if (getWindowPrompt() != es("")) {
        e_string _prompt = getWindowPrompt();
        _prompt = es(' ') + _prompt + es(' ');
        mvwprintw(wnd_editArea_, 0, 6, "%ls", _prompt.c_str());
    }

    if (dialogueAreaSize == 1) {
        if (getInputMode() == DialogueMode) {
            mvwprintw(wnd_editArea_, 0, stdscrSize_X - 23, "%ls", es("{ Режим диалога }"));
        }
        else {
            mvwprintw(wnd_editArea_, 0, stdscrSize_X - 23, "%ls", es("{ Командный режим }"));
        }
    }

    wrefresh(wnd_editArea_);

    //Окно диалога.
    if (dialogueAreaSize != 0) {
        if (wnd_dialogueArea_ != nullptr) {
            delwin(wnd_dialogueArea_);
            wnd_dialogueArea_ = nullptr;
        }

        if (dialogueAreaSize > 1) {
            wnd_dialogueArea_ = derwin(wnd_body_, dialogueAreaSize, stdscrSize_X, 0, 0);

            mvwvline(wnd_dialogueArea_, 1, 0, DialogAreaFormatting, dialogueAreaSize - 1);
            mvwvline(wnd_dialogueArea_, 1, stdscrSize_X - 1, 0, dialogueAreaSize - 1);

            mvwhline(wnd_dialogueArea_, 0, 1, 0, stdscrSize_X - 2);
            mvwhline(wnd_dialogueArea_, 0, 0, ACS_ULCORNER, 1);
            mvwhline(wnd_dialogueArea_, 0, stdscrSize_X - 1, ACS_URCORNER, 1);

            if (getInputMode() == DialogueMode) {
                mvwprintw(wnd_dialogueArea_, 0, stdscrSize_X - 23, "%ls", es("{ Режим диалога }"));
            }
            else {
                mvwprintw(wnd_dialogueArea_, 0, stdscrSize_X - 23, "%ls", es("{ Командный режим }"));
            }

            wrefresh(wnd_dialogueArea_);
        }
    }

}
