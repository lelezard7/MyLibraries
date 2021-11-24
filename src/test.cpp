#include "ONF.h"

CreateSpecialNameRules(QssNameRules, std::string, "", "", "");
CreateSpecialNameRules(StdWNameRules, std::wstring, L"", L"", L"");

int main()
{
    QssNameRules d;
    StdWNameRules ff;
    ONF::StylesheetBuffer<std::string> buffer;
    ONF::StylesheetExBuffer<std::wstring> exBuffer;
    auto stdNameRules = CreateStdNameRulesObj;

    ONF::divideStylesheet<std::string>("", nullptr);
    ONF::divideStylesheet<std::string>("", nullptr, ONF::StdNameRules());
    ONF::divideStylesheet<std::wstring>(L"", nullptr, CreateTNameRulesObj(std::wstring, L"", L"", L""));
    ONF::divideStylesheet<std::wstring>(L"", nullptr, StdWNameRules());
    ONF::divideStylesheet<std::string>("", nullptr, d);
    ONF::divideStylesheet<std::string>("", &buffer, d);
    ONF::divideStylesheetEx<std::wstring>(L"", &exBuffer, ff);
}
