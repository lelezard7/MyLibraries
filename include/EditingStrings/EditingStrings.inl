#include "../EditingStrings.h"

#include <algorithm>


template<class T>
int
ONF::
trimString(T& str, const decltype(T())& rule, unsigned trimmingSide) {
    if (str.size() == 0 || rule.size() == 0)
        return 0;

    auto findChar = [&rule](const auto& strChar) {
        return std::count(rule.cbegin(), rule.cend(), strChar);
    };

    int chRemovedCount = 0;

    if (trimmingSide & ONF::TrimmingSide_Left) {
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

    if (trimmingSide & ONF::TrimmingSide_Right) {
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
