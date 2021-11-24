#ifndef ONF_H_
#define ONF_H_

#include "VersionNames.h"

#define ONF_VER         ONF_VER_0_0
#define ONF_VER_PATCH   0x0000


namespace ONF
{
    #include "UniversalDefinitions.h"

    typedef unsigned long long udlong;
    typedef long long dlong;
    typedef long double ldouble;


    /**
     * @brief Возвращает абсолютное значение числа.
     *
     * Эта функция является заменой [std::abs](https://en.cppreference.com/w/cpp/numeric/math/abs). <br>
     * Это необходимо для поддержки *unsigned* типов.
     *
     * @param value - число, абсолютное значение которого надо найти.
     * @return Если **value** >= 0, возвращает **value**. Если **value** < 0, возвращает **-value**.
     */
    template<class T>
    T abs(T value)
    { return value < 0 ? -value : value; }
}


#include "IdManagement.h"
#include "EditingStrings.h"
#include "Stylesheet.h"
#include "UniversalDefinitions.h"
//#include "ConsoleConstructor.h"

#endif
