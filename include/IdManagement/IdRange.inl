#include "../IdManagement.h"


template<class T>
ONF::IdRange<T>::IdInfo::
IdInfo()
    : flags    (IDRF_NOT_SET),
      position (IDRP_NOT_SET),
      border   (BorderRange::UpperBorder),
      state    (false),
      value    (0),
      stepCount(0) {}

template<class T>
ONF::IdRange<T>::IdInfo::
~IdInfo() {}


template<class T>
ONF::IdRange<T>::
IdRange(T start, T step)
    : upperBorderState_(false),
      upperBorder_     (start),
      upperLimit_      (std::numeric_limits<T>::max()),
      lowerBorderState_(false),
      lowerBorder_     (start),
      lowerLimit_      (std::numeric_limits<T>::lowest()),
      start_           (start),
      step_            (step == 0 ? 1 : ONF::abs(step)) {}

template<class T>
ONF::IdRange<T>::
~IdRange() {}

template<class T>
typename ONF::IdRange<T>::IdInfo
ONF::IdRange<T>::
moveBorder(BorderRange borderRange, dlong n)
{
    IdInfo idInfo;

    if (borderRange == BorderRange::UpperBorder) {
        if (fillIdInfo(idInfo, borderRange, upperBorder_, static_cast<ldouble>(n), Action::Move))
            upperBorder_ = idInfo.value;

        return idInfo;
    }

    if (fillIdInfo(idInfo, borderRange, lowerBorder_, static_cast<ldouble>(n), Action::Move))
        lowerBorder_ = idInfo.value;

    return idInfo;
}

template<class T>
typename ONF::IdRange<T>::IdInfo
ONF::IdRange<T>::
getIdInfo(BorderRange borderRange, dlong n) const
{
    IdInfo idInfo;

    if (borderRange == BorderRange::UpperBorder) {
        fillIdInfo(idInfo, borderRange, upperBorder_, static_cast<ldouble>(n), Action::GetInfo);
        return idInfo;
    }

    fillIdInfo(idInfo, borderRange, lowerBorder_, static_cast<ldouble>(n), Action::GetInfo);
    return idInfo;
}

template<class T>
std::optional<typename ONF::IdRange<T>::IdInfo>
ONF::IdRange<T>::
getIdInfo(BorderRange borderRange, T id, dlong n) const
{
    if (!isStandardId(id, start_, step_))
        return std::nullopt;

    if (borderRange == BorderRange::UpperBorder) {
        if (id < lowerBorder_ || id > upperLimit_)
            return std::nullopt;
    }
    else {
        if (id > upperBorder_ || id < lowerLimit_)
            return std::nullopt;
    }

    IdInfo idInfo;
    fillIdInfo(idInfo, borderRange, id, static_cast<ldouble>(n), Action::GetInfo);
    return idInfo;
}

template<class T>
inline void
ONF::IdRange<T>::
reset()
{
    upperBorderState_ = false;
    lowerBorderState_ = false;
    upperBorder_ = start_;
    lowerBorder_ = start_;
}

template<class T>
bool
ONF::IdRange<T>::
setBorderValue(BorderRange borderRange, T value)
{
    if (value > upperLimit_ || value < lowerLimit_)
        return false;

    if (!isStandardId(value, start_, step_))
        return false;

    if (borderRange == BorderRange::UpperBorder) {
        if (value < lowerBorder_)
            return false;

        upperBorder_ = value;
        return true;
    }

    if (value > upperBorder_)
        return false;

    lowerBorder_ = value;
    return true;
}

template<class T>
inline T
ONF::IdRange<T>::
getBorderValue(BorderRange borderRange) const
{
    switch (borderRange) {
        case BorderRange::UpperBorder:   return upperBorder_;
        case BorderRange::LowerBorder:   return lowerBorder_;
    }
}

template<class T>
inline void
ONF::IdRange<T>::
setBorderState(BorderRange borderRange, bool state)
{
    switch (borderRange) {
        case BorderRange::UpperBorder:   upperBorderState_ = state;   return;
        case BorderRange::LowerBorder:   lowerBorderState_ = state;   return;
    }
}

template<class T>
inline bool
ONF::IdRange<T>::
getBorderState(BorderRange borderRange) const
{
    switch (borderRange) {
        case BorderRange::UpperBorder:   return upperBorderState_;
        case BorderRange::LowerBorder:   return lowerBorderState_;
    }
}

template<class T>
bool
ONF::IdRange<T>::
setBorderLimit(BorderRange borderRange, T value)
{
    if (borderRange == BorderRange::UpperBorder) {
        if (upperBorder_ > value)
            return false;

        upperLimit_ = value;
        return true;
    }

    if (borderRange == BorderRange::LowerBorder) {
        if (lowerBorder_ < value)
            return false;

        lowerLimit_ = value;
        return true;
    }
}

template<class T>
inline T
ONF::IdRange<T>::
getBorderLimit(BorderRange borderRange) const
{
    switch (borderRange) {
        case BorderRange::UpperBorder:   return upperLimit_;
        case BorderRange::LowerBorder:   return lowerLimit_;
    }
}

template<class T>
inline T
ONF::IdRange<T>::
getStart() const
{
    return start_;
}

template<class T>
inline T
ONF::IdRange<T>::
getStep() const
{
    return step_;
}

template<class T>
int
ONF::IdRange<T>::
fillIdInfo(IdInfo& idInfo, BorderRange borderRange, T borderValue, ldouble n, Action action) const
{
    if (borderRange == BorderRange::UpperBorder) {
        if (n > 0) {
            if (fillInfoAboutMoveUp(idInfo, borderValue, upperLimit_, n)) {
                fillInfoAboutTerritory(idInfo, borderRange, idInfo.value);
                fillInfoAboutPos(idInfo, n, action);
                return 1;
            }
        }

        if (n < 0) {
            if (fillInfoAboutMovemDown(idInfo, borderValue, lowerBorder_, n)) {
                fillInfoAboutTerritory(idInfo, borderRange, idInfo.value);
                fillInfoAboutPos(idInfo, n, action);
                return 1;
            }
        }
    }
    else {
        if (n > 0) {
            if (fillInfoAboutMovemDown(idInfo, borderValue, lowerLimit_, n)) {
                fillInfoAboutTerritory(idInfo, borderRange, idInfo.value);
                fillInfoAboutPos(idInfo, n, action);
                return 1;
            }
        }

        if (n < 0) {
            if (fillInfoAboutMoveUp(idInfo, borderValue, upperBorder_, n)) {
                fillInfoAboutTerritory(idInfo, borderRange, idInfo.value);
                fillInfoAboutPos(idInfo, n, action);
                return 1;
            }
        }
    }

    idInfo.position = IDRP_ON_BORDER;
    idInfo.value = borderValue;
    idInfo.stepCount = 0;

    if (n == 0)
        idInfo.flags = IDRF_SUCCESSFULLY;
    else
        idInfo.flags = (n > 0 ? IDRF_ID_OUT_RANGE : IDRF_RANGE_ARE_BENT);

    fillInfoAboutTerritory(idInfo, borderRange, borderValue);
    return 0;
}

template<class T>
bool
ONF::IdRange<T>::
fillInfoAboutMoveUp(IdInfo& idInfo, T borderValue, T borderLimit, ldouble n) const
{
    if (static_cast<ldouble>(borderValue) + static_cast<ldouble>(ONF::abs(n) * step_) <= static_cast<ldouble>(borderLimit)) {
        idInfo.flags = IDRF_SUCCESSFULLY;
        idInfo.value = borderValue + (ONF::abs(n) * step_);
        idInfo.stepCount = n;
        return true;
    }

    for(ldouble i = ONF::abs(n) - 1; i > 0; --i) {
        if (static_cast<ldouble>(borderValue) + static_cast<ldouble>(i * step_) <= static_cast<ldouble>(borderLimit)) {
            idInfo.value = borderValue + (i * step_);

            if (n > 0) {
                idInfo.flags = IDRF_ID_OUT_RANGE;
                idInfo.stepCount = i;
                return true;
            }

            idInfo.flags = IDRF_RANGE_ARE_BENT;
            idInfo.stepCount = -i;
            return true;
        }
    }

    return false;
}

template<class T>
bool
ONF::IdRange<T>::
fillInfoAboutMovemDown(IdInfo& idInfo, T borderValue, T borderLimit, ldouble n) const
{
    if (static_cast<ldouble>(borderValue) - static_cast<ldouble>(ONF::abs(n) * step_) >= static_cast<ldouble>(borderLimit)) {
        idInfo.flags = IDRF_SUCCESSFULLY;
        idInfo.value = borderValue - (ONF::abs(n) * step_);
        idInfo.stepCount = n;
        return true;
    }

    for(ldouble i = ONF::abs(n) - 1; i > 0; --i) {
        if (static_cast<ldouble>(borderValue) - static_cast<ldouble>(i * step_) >= static_cast<ldouble>(borderLimit)) {
            idInfo.value = borderValue - (i * step_);

            if (n > 0) {
                idInfo.flags = IDRF_ID_OUT_RANGE;
                idInfo.stepCount = i;
                return true;
            }

            idInfo.flags = IDRF_RANGE_ARE_BENT;
            idInfo.stepCount = -i;
            return true;
        }
    }

    return false;
}

template<class T>
void
ONF::IdRange<T>::
fillInfoAboutTerritory(IdInfo& idInfo, BorderRange borderRange, T borderValue) const
{
    if (borderValue < start_) {
        idInfo.border = BorderRange::LowerBorder;
        idInfo.state = lowerBorderState_;
        return;
    }

    if (borderValue > start_) {
        idInfo.border = BorderRange::UpperBorder;
        idInfo.state = upperBorderState_;
        return;
    }

    idInfo.state = (borderRange == BorderRange::UpperBorder ? upperBorderState_ : lowerBorderState_);
    idInfo.border = borderRange;
    idInfo.flags += IDRF_ID_AT_START;
}

template<class T>
void
ONF::IdRange<T>::
fillInfoAboutPos(IdInfo& idInfo, ldouble n, Action action) const
{
    if (action == Action::Move) {
        idInfo.position = IDRP_ON_BORDER;
        return;
    }

    if (idInfo.value == upperBorder_ || idInfo.value == lowerBorder_) {
        idInfo.position = IDRP_ON_BORDER;
        return;
    }

    idInfo.position = (n > 0 ? IDRP_OUT_RANGE : IDRP_IN_RANGE);
}
