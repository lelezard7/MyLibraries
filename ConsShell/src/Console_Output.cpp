#include "Console_IO.h"

#include <codecvt>
#include <locale>


ErrCode console_quote(ai_string prompt, ai_string* buffer)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> _converter;
    setWindowPrompt(_converter.from_bytes(prompt));

    return ERRCODE_TRUE;
}

ErrCode console_system_info(ai_string message, ai_string* buffer)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> _converter;
    addConsoleMessage(_converter.from_bytes(message), NPAIR_MESSAGE);

    return ERRCODE_TRUE;
}

ErrCode console_error(ai_string message, ai_string* buffer)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> _converter;
    addConsoleMessage(_converter.from_bytes(message), NPAIR_ERROR);

    return ERRCODE_TRUE;
}

ErrCode console_warning(ai_string message, ai_string* buffer)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> _converter;
    addConsoleMessage(_converter.from_bytes(message), NPAIR_WARNING);

    return ERRCODE_TRUE;
}

ErrCode console_info(ai_string message, ai_string* buffer)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> _converter;
    addConsoleMessage(_converter.from_bytes(message), NPAIR_INFO);

    return ERRCODE_TRUE;
}
