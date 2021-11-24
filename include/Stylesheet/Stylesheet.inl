#include "../Stylesheet.h"
#include "../EditingStrings.h"

#include <regex>


template <class T>
bool
ONF::
isRegexCorrect(const T& regex)
{
    try {
        T regexCopy = regex;
        std::regex r(std::move(regexCopy));
    }
    catch (...) {
        return false;
    }

    return true;
}

#define URegex(T, Name, Param)   \
    if constexpr (std::is_same_v<T, std::string>) {   \
        std::regex Name(Param);                             \
    }                                                  \
    else {                                                  \
        std::wregex Name(Param);                            \
    }

template <class T>
bool
isRegexCorrect(const T& regex)
{
    try {
        T regexCopy = regex;
        MRegex(T, r, std::move(regexCopy))
    }
    catch (...) {
        return false;
    }

    return true;
}


template <class T>
ONF::NameRules<T>::
NameRules(const T& selector, const T& property, const T& value)
    : selector_(selector)
    , property_(property)
    , value_   (value) {};

template <class T>
void
ONF::NameRules<T>::
setRule(const T& rule)
{ rule_ = rule; }

template <class T>
T
ONF::NameRules<T>::
getRule() const
{ return rule_; }

template <class T>
std::optional<T>
ONF::NameRules<T>::
buildRule() const
{

}

template <class T>
void
ONF::NameRules<T>::
setDeclaration(const T& declaration)
{ declaration_ = declaration; }

template <class T>
T
ONF::NameRules<T>::
getDeclaration() const
{ return declaration_; }

template <class T>
std::optional<T>
ONF::NameRules<T>::
buildDeclaration() const
{

}

template <class T>
void
ONF::NameRules<T>::
setSelector(const T& selector)
{ selector_ = selector; }

template <class T>
T
ONF::NameRules<T>::
getSelector() const
{ return selector_; }

template <class T>
void
ONF::NameRules<T>::
setProperty(const T& property)
{ property_ = property; }

template <class T>
T
ONF::NameRules<T>::
getProperty() const
{ return property_; }

template <class T>
void
ONF::NameRules<T>::
setValue(const T& value)
{ value_ = value; }

template <class T>
T
ONF::NameRules<T>::
getValue() const
{ return value_; }


template <class T>
bool
ONF::
divideStylesheet(const T& stylesheet, StylesheetBuffer<T>* buffer, const NameRules<T>& nameRules)
{










    QString copyStylesheet = stylesheet;
    trimSpace(copyStylesheet, ONF::TrimmingSide_Left | ONF::TrimmingSide_Left);

    if (copyStylesheet == "")
        return false;

    std::string s = copyStylesheet.toStdString();
    std::regex r("[" + gSelector.toStdString() + "]+" +
                 "\\{" +
                 "[" + gProperty.toStdString() + ":" + gValue.toStdString() + ";\\s]*" +
                 "\\}");

    std::vector<std::smatch> matches {
        std::sregex_iterator(s.begin(), s.end(), r),
        std::sregex_iterator()
    };

    std::string stylesheetRemainder;
    std::regex_replace(std::back_insert_iterator(stylesheetRemainder), s.begin(), s.end(), r, "");

    trimSpace(stylesheetRemainder, ONF::TrimmingSide_Left | ONF::TrimmingSide_Left);

    if (stylesheetRemainder != "")
        return false;

    bool isCorrect = true;
    buffer.clear();

    std::for_each(matches.begin(), matches.end(), [&buffer, &isCorrect](const std::smatch& m) {
        std::string str = m.str(0);
        trimSpace(str, ONF::TrimmingSide_Left | ONF::TrimmingSide_Left);

        QString buff1;
        QString buff2;
        if (!divideRule(QString::fromStdString(str), buff1, buff2))
            isCorrect = false;

        buffer.push_back(QString::fromStdString(str));
    });

    return isCorrect;
}

template <class T>
bool
ONF::
divideStylesheetEx(const T& stylesheet, StylesheetExBuffer<T>* buffer, const NameRules<T>& nameRules)
{

}

template <class T>
bool
ONF::
divideRule(const T& rule, T* selector, T* declarations, const NameRules<T>& nameRules)
{

}

template <class T>
bool
ONF::
divideDeclarationsGroup(const T& declarationsGroup, StylesheetBuffer<T>* buffer, const NameRules<T>& nameRules)
{

}

template <class T>
bool
ONF::
divideDeclarationsGroupEx(const T& declarationsGroup, StylesheetExBuffer<T>* buffer, const NameRules<T>& nameRules)
{

}

template <class T>
bool
ONF::
divideDeclaration(const T& declaration, T* property, T* value, const NameRules<T>& nameRules)
{

}







//#include <regex>

//static QString gSelector;
//static QString gProperty;
//static QString gValue;

//void
//setNamesRule(const NamesRule& namesRule)
//{
//    gSelector = namesRule.selector;
//    gProperty = namesRule.property;
//    gValue = namesRule.value;
//}

//NamesRule
//getNamesRule()
//{ return NamesRule(gSelector, gProperty, gValue); }

////   ([a-zA-Z\d:\-\*#\[\]=",!\.>\s]+)\{([a-zA-Z\d:;\s\.\(\)\-%,/"#]*)\}
////   std::regex r(gSelector.toStdString() + "{" + gProperty.toStdString() + ":" +
////                gValue.toStdString() + ";\\s" + "}");

//bool
//divideStylesheet(const QString& stylesheet, QVector<QString>& buffer)
//{
//    QString copyStylesheet = stylesheet;
//    trimSpace(copyStylesheet, ONF::TrimmingSide_Left | ONF::TrimmingSide_Left);

//    if (copyStylesheet == "")
//        return false;

//    std::string s = copyStylesheet.toStdString();
//    std::regex r("[" + gSelector.toStdString() + "]+" +
//                 "\\{" +
//                 "[" + gProperty.toStdString() + ":" + gValue.toStdString() + ";\\s]*" +
//                 "\\}");

//    std::vector<std::smatch> matches {
//        std::sregex_iterator(s.begin(), s.end(), r),
//        std::sregex_iterator()
//    };

//    std::string stylesheetRemainder;
//    std::regex_replace(std::back_insert_iterator(stylesheetRemainder), s.begin(), s.end(), r, "");

//    trimSpace(stylesheetRemainder, ONF::TrimmingSide_Left | ONF::TrimmingSide_Left);

//    if (stylesheetRemainder != "")
//        return false;

//    bool isCorrect = true;
//    buffer.clear();

//    std::for_each(matches.begin(), matches.end(), [&buffer, &isCorrect](const std::smatch& m) {
//        std::string str = m.str(0);
//        trimSpace(str, ONF::TrimmingSide_Left | ONF::TrimmingSide_Left);

//        QString buff1;
//        QString buff2;
//        if (!divideRule(QString::fromStdString(str), buff1, buff2))
//            isCorrect = false;

//        buffer.push_back(QString::fromStdString(str));
//    });

//    return isCorrect;
//}

//bool
//divideRule(const QString& rule, QString& selector, QString& declarations)
//{
//    QString copyRule = rule;
//    trimSpace(copyRule, ONF::TrimmingSide_Left | ONF::TrimmingSide_Left);

//    if (copyRule == "")
//        return false;

//    std::string s = copyRule.toStdString();
//    std::regex r("([" + gSelector.toStdString() + "]+)" +
//                 "\\{(" +
//                 "[" + gProperty.toStdString() + ":" + gValue.toStdString() + ";\\s]*" +
//                 ")\\}");
//    std::smatch m;

//    if (!std::regex_match(s, m, r))
//        return false;

//    s = m[1];
//    trimSpace(s, ONF::TrimmingSide_Left | ONF::TrimmingSide_Right);
//    selector = QString::fromStdString(s);

//    s = m[2];
//    trimSpace(s, ONF::TrimmingSide_Left | ONF::TrimmingSide_Right);
//    declarations = QString::fromStdString(s);
//    return true;
//}

//bool
//divideDeclarations(const QString& declarations, QVector<QString>& buffer)
//{
//    QString copyDeclarations = declarations;
//    trimSpace(copyDeclarations, ONF::TrimmingSide_Left | ONF::TrimmingSide_Left);

//    if (copyDeclarations == "")
//        return false;

//    std::string s = copyDeclarations.toStdString();
//    std::regex r("[" + gProperty.toStdString() + "]+:[" + gValue.toStdString() + "]+;");

//    std::vector<std::smatch> matches {
//        std::sregex_iterator(s.begin(), s.end(), r),
//        std::sregex_iterator()
//    };

//    std::string declarationsRemainder;
//    std::regex_replace(std::back_insert_iterator(declarationsRemainder), s.begin(), s.end(), r, "");

//    trimSpace(declarationsRemainder, ONF::TrimmingSide_Left | ONF::TrimmingSide_Left);

//    if (declarationsRemainder != "")
//        return false;

//    buffer.clear();
//    std::for_each(matches.begin(), matches.end(), [&buffer](const std::smatch& m) {
//        std::string str = m.str(0);
//        trimSpace(str, ONF::TrimmingSide_Left | ONF::TrimmingSide_Left);
//        buffer.push_back(QString::fromStdString(str));
//    });

//    return true;
//}

//bool
//divideDeclaration(const QString& declaration, QString& property, QString& value)
//{
//    QString copyDeclaration = declaration;
//    trimSpace(copyDeclaration, ONF::TrimmingSide_Left | ONF::TrimmingSide_Left);

//    if (copyDeclaration == "")
//        return false;

//    std::string s = copyDeclaration.toStdString();
//    std::regex r("([" + gProperty.toStdString() + "]+):([" + gValue.toStdString() + "]+);");
//    std::smatch m;

//    if (!std::regex_match(s, m, r))
//        return false;

//    s = m[1];
//    trimSpace(s, ONF::TrimmingSide_Left | ONF::TrimmingSide_Right);
//    property = QString::fromStdString(s);

//    s = m[2];
//    trimSpace(s, ONF::TrimmingSide_Left | ONF::TrimmingSide_Right);
//    value = QString::fromStdString(s);
//    return true;
//}
