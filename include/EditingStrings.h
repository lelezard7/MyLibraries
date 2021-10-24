#ifndef EDITINGSTRINGS_H_
#define EDITINGSTRINGS_H_

#include <algorithm>


enum TrimmingSide : unsigned {
    TrimmingSide_Left    = 0x0001,
    TrimmingSide_Right   = 0x0002
};

// decltype нужен здесь для того что бы функция ориентировалась на тип передаваемый в str и
// нам не приходилосьбы уточнять какой тип мы имеем ввиду ( trimString<std::string>(...) ).
// Так как str может быть std::string, а rule - массив char.
template<class T>
int
trimString(T& str, const decltype(T())& rule, unsigned trimmingSide) {
    if (str.size() == 0 || rule.size() == 0)
        return 0;

    auto findChar = [&rule](const auto& strChar) {
        return std::count(rule.cbegin(), rule.cend(), strChar);
    };

    int chRemovedCount = 0;

    if (trimmingSide & TrimmingSide_Left) {
        auto itBegin = str.begin();
        auto itEnd   = str.end();
        auto it      = str.begin();

        while (true) {
            if (it == itEnd) {
                chRemovedCount += str.size();
                str.clear();
                return chRemovedCount;
            }

            if (!findChar(*it)) {
                if (it != itBegin) {
                    chRemovedCount += std::distance(itBegin, it);
                    str.erase(itBegin, it);
                }

                break;
            }

            ++it;
        }
    }

    if (trimmingSide & TrimmingSide_Right) {
        auto itBegin = str.begin();
        auto itEnd   = str.end();
        auto it      = itEnd - 1;

        while (true) {
            if (!findChar(*it)) {
                if (it != itEnd - 1) {
                    ++it;
                    chRemovedCount += std::distance(it, itEnd);
                    str.erase(it, itEnd);
                }

                break;
            }

            if (it == itBegin) {
                chRemovedCount += str.size();
                str.clear();
                return chRemovedCount;
            }

            --it;
        }
    }

    return chRemovedCount;
}

#define trimSpace(str, trimmingSide) \
    trimString(str, " \f\n\r\t\v", trimmingSide)

#endif
