#ifndef EDITINGSTRINGS_H_
#define EDITINGSTRINGS_H_


namespace ONF
{
    /**
     * @brief Содержит стороны для обрезки строк. Применяются функцией @ref trimString.
     *
     * Данные перечислители могут комбинироваться.
     *
     * @see trimString
     */
    enum TrimmingSide : unsigned {
        TrimmingSide_Left    = 0x0001,   ///<@brief Говорит функции @ref trimString что нужно
                                         /// удалять символы слева.
        TrimmingSide_Right   = 0x0002    ///<@brief Говорит функции @ref trimString что нужно
                                         /// удалять символы справа.
    };

    /**
     * @brief Удаляет заданные символы с указанной стороны до тех пор, пока не встретится иной символ.
     *
     * В **str** передается строка которую нужно обработать и в которую будет записан результат
     * обработки. <br>
     * В **rule** передается строка с символами которые нужно удалить. <br>
     * В **trimmingSide** передается перечислитель из перечисления @ref TrimmingSide, который говорит
     * с какой стороны нужно удалять указанные в **rule** символы. <br>
     * Если указать в **trimmingSide** перечислитель @ref TrimmingSide_Left, данная функция начнет
     * перебирать все символы слева направо. Если символ равен одному из символов строки **rule**,
     * он удаляется, если нет, то операция прерывается, и функция возвращает результаты. <br>
     * Если указать в **trimmingSide** перечислитель @ref TrimmingSide_Right, будет происходить тоже
     * что описано выше только символы перебираться будут справа налево. <br>
     * Если @ref TrimmingSide_Left и @ref TrimmingSide_Right указать вместе, то сперва функция удалит
     * указанные в **rule** символы слева, а потом справа. Потом функция вернет результаты.
     *
     * @param str - строка для обработки. Так же в нее будет записан конечный результат.
     * @param rule - символы которые нужно удалить.
     * @param trimmingSide - сторона с которой нужно удалить указанные символы.
     * @return Возвращает количество удаленных символов.
     *
     * @see
     * TrimmingSide <br>
     * trimSpace
     */
    // decltype нужен здесь для того что бы функция ориентировалась на тип передаваемый в str и
    // нам не приходилось бы уточнять какой тип мы имеем в виду ( trimString<std::string>(...) ).
    // Так как str может быть std::string, а rule - массив char.
    template<class T>
    int trimString(T& str, const decltype(T())& rule, unsigned trimmingSide);

    /**
     * @brief Вызывает @ref ONF::trimString который удалит пробельные символы.
     *
     * Список удаляемых символов:
     * - ``' '``
     * - ``'\f'``
     * - ``'\n'``
     * - ``'\r'``
     * - ``'\t'``
     * - ``'\v'``
     *
     * @see
     * ONF::trimString <br>
     * trimSpaceW
     */
    #define trimSpace(str, trimmingSide)   ONF::trimString(str, " \f\n\r\t\v", trimmingSide)

    /**
     * @brief Вызывает @ref ONF::trimString который удалит пробельные символы.
     *
     * То же что и @ref trimSpace только для широких символов.
     *
     * @see
     * ONF::trimString <br>
     * trimSpace
     */
    #define trimSpaceW(str, trimmingSide)   ONF::trimString(str, L" \f\n\r\t\v", trimmingSide)
}

#include "EditingStrings/EditingStrings.inl"

#endif
