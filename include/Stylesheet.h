/**
 * QPushButton:pressed { color: #ffffff; }
 *
 * QPushButton:pressed { color: #ffffff; } - rule
 * color: #ffffff;                         - declaration
 * QPushButton:pressed                     - selector
 * color                                   - property
 * value                                   - value
 *
 */

#ifndef STYLESHEET_H_
#define STYLESHEET_H_

#include "UniversalDefinitions.h"

#include <optional>
#include <string>
#include <vector>


namespace ONF
{
    template <class T>
    bool isRegexCorrect(const T& regex);

    template <class T>
    class NameRules
    {
        T rule_;
        T declaration_;
        T selector_;
        T property_;
        T value_;

    public:
        NameRules(const T& selector, const T& property, const T& value);
        NameRules() = default;
        virtual ~NameRules() = default;

        void setRule(const T& rule);
        T getRule() const;
        std::optional<T> buildRule() const;

        void setDeclaration(const T& declaration);
        T getDeclaration() const;
        std::optional<T> buildDeclaration() const;

        void setSelector(const T& selector);
        T getSelector() const;

        void setProperty(const T& property);
        T getProperty() const;

        void setValue(const T& value);
        T getValue() const;

    };

    #define CreateSpecialNameRules(Name, Type, Selector, Property, Value)   \
        struct Name : public ONF::NameRules<Type>                           \
        {                                                                   \
            Name() : NameRules<Type>(Selector, Property, Value) {};         \
            virtual ~Name() = default;                                      \
        }

    #define CreateTNameRulesObj(Type, Selector, Property, Value)   \
        ONF::NameRules<Type>(Selector, Property, Value)


    #define SelectorStdName   ""
    #define PropertyStdName   ""
    #define ValueStdName      ""

    #define CreateTStdNameRulesObj(Type)   \
        CreateTNameRulesObj(Type, SelectorStdName, PropertyStdName, ValueStdName)

    #define CreateStdNameRulesObj   CreateTStdNameRulesObj(std::string)
    CreateSpecialNameRules(StdNameRules, std::string, SelectorStdName, PropertyStdName, ValueStdName);


    template <class T>
    using StylesheetBuffer = std::vector<T>;

    template <class T>
    using StylesheetExBuffer = std::vector<std::pair<T, T>>;


    template <class T>
    bool
    divideStylesheet(
            const T& stylesheet,
            StylesheetBuffer<T>* buffer,
            const NameRules<T>& nameRules = CreateTStdNameRulesObj(T)
    );

    template <class T>
    bool
    divideStylesheetEx(
            const T& stylesheet,
            StylesheetExBuffer<T>* buffer,
            const NameRules<T>& nameRules = new CreateTStdNameRulesObj(T)
    );

    template <class T>
    bool
    divideRule(
            const T& rule,
            T* selector,
            T* declarations,
            const NameRules<T>& nameRules = new CreateTStdNameRulesObj(T)
    );

    template <class T>
    bool
    divideDeclarationsGroup(
            const T& declarationsGroup,
            StylesheetBuffer<T>* buffer,
            const NameRules<T>& nameRules = new CreateTStdNameRulesObj(T)
    );

    template <class T>
    bool
    divideDeclarationsGroupEx(
            const T& declarationsGroup,
            StylesheetExBuffer<T>* buffer,
            const NameRules<T>& nameRules = new CreateTStdNameRulesObj(T)
    );

    template <class T>
    bool
    divideDeclaration(
            const T& declaration,
            T* property,
            T* value,
            const NameRules<T>& nameRules = new CreateTStdNameRulesObj(T)
    );
}

#include "Stylesheet/Stylesheet.inl"


namespace ONF
{
    class StylesheetRuleCreator
    {

    };
}

#include "Stylesheet/StylesheetRuleCreator.inl"


namespace ONF
{
    class StylesheetCreator
    {

    };
}

#include "Stylesheet/StylesheetCreator.inl"

#endif
