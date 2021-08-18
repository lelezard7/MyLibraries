#include "../IdManagement.h"


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
IdRange(IdRange&& other)
    : upperBorderState_(std::move(other.upperBorderState_)),
      upperBorder_     (std::move(other.upperBorder_)),
      upperLimit_      (std::move(other.upperLimit_)),
      lowerBorderState_(std::move(other.lowerBorderState_)),
      lowerBorder_     (std::move(other.lowerBorder_)),
      lowerLimit_      (std::move(other.lowerLimit_)),
      start_           (std::move(other.start_)),
      step_            (std::move(other.step_))
{
   other.upperBorderState_ = false;
   other.lowerBorderState_ = false;
   other.upperBorder_ = other.start_;
   other.lowerBorder_ = other.start_;
}

template<class T>
ONF::IdRange<T>::
~IdRange() {}

template<class T>
typename ONF::IdRange<T>::IdInfo
ONF::IdRange<T>::
moveBorder(BorderRange borderRange, dlong n)
{
    if (borderRange == BorderRange::UpperBorder) {
        IdInfo idInfo = getFilledIdInfo(borderRange, upperBorder_, static_cast<ldouble>(n), Action::Move);
        upperBorder_ = idInfo.value;
        return idInfo;
    }

    IdInfo idInfo = getFilledIdInfo(borderRange, lowerBorder_, static_cast<ldouble>(n), Action::Move);
    lowerBorder_ = idInfo.value;
    return idInfo;
}

template<class T>
typename ONF::IdRange<T>::IdInfo
ONF::IdRange<T>::
getIdInfo(BorderRange borderRange, dlong n) const
{
    if (borderRange == BorderRange::UpperBorder)
        return getFilledIdInfo(borderRange, upperBorder_, static_cast<ldouble>(n), Action::GetInfo);

    return getFilledIdInfo(borderRange, lowerBorder_, static_cast<ldouble>(n), Action::GetInfo);
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

    return getFilledIdInfo(borderRange, id, static_cast<ldouble>(n), Action::GetInfo);
}

template<class T>
void
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
T
ONF::IdRange<T>::
getBorderValue(BorderRange borderRange) const
{
    switch (borderRange) {
        case BorderRange::UpperBorder:   return upperBorder_;
        case BorderRange::LowerBorder:   return lowerBorder_;
    }
}

template<class T>
void
ONF::IdRange<T>::
setBorderState(BorderRange borderRange, bool state)
{
    switch (borderRange) {
        case BorderRange::UpperBorder:   upperBorderState_ = state;   return;
        case BorderRange::LowerBorder:   lowerBorderState_ = state;   return;
    }
}

template<class T>
bool
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
        if (value < upperBorder_)
            return false;

        upperLimit_ = value;
        return true;
    }

    if (borderRange == BorderRange::LowerBorder) {
        if (value > lowerBorder_)
            return false;

        lowerLimit_ = value;
        return true;
    }
}

template<class T>
T
ONF::IdRange<T>::
getBorderLimit(BorderRange borderRange) const
{
    switch (borderRange) {
        case BorderRange::UpperBorder:   return upperLimit_;
        case BorderRange::LowerBorder:   return lowerLimit_;
    }
}

template<class T>
T
ONF::IdRange<T>::
getStart() const
{
    return start_;
}

template<class T>
T
ONF::IdRange<T>::
getStep() const
{
    return step_;
}

template<class T>
ONF::IdRange<T>&
ONF::IdRange<T>::
operator=(IdRange&& other)
{
    upperBorderState_ = std::move(other.upperBorderState_);
    upperBorder_      = std::move(other.upperBorder_);
    upperLimit_       = std::move(other.upperLimit_);
    lowerBorderState_ = std::move(other.lowerBorderState_);
    lowerBorder_      = std::move(other.lowerBorder_);
    lowerLimit_       = std::move(other.lowerLimit_);
    start_            = std::move(other.start_);
    step_             = std::move(other.step_);

    other.upperBorderState_ = false;
    other.lowerBorderState_ = false;
    other.upperBorder_ = other.start_;
    other.lowerBorder_ = other.start_;

    return *this;
}

template<class T>
typename ONF::IdRange<T>::IdInfo
ONF::IdRange<T>::
getFilledIdInfo(BorderRange borderRange, T borderValue, ldouble n, Action action) const
{
    IdInfo idInfo;

    if (borderRange == BorderRange::UpperBorder) {
        if (n > 0) {
            if (fillInfoAboutMoveUp(idInfo, borderRange, borderValue, upperLimit_, n, action)) {
                return idInfo;
            }
        }

        if (n < 0) {
            if (fillInfoAboutMoveDown(idInfo, borderRange, borderValue, lowerBorder_, n, action)) {
                return idInfo;
            }
        }
    }
    else {
        if (n > 0) {
            if (fillInfoAboutMoveDown(idInfo, borderRange, borderValue, lowerLimit_, n, action)) {
                return idInfo;
            }
        }

        if (n < 0) {
            if (fillInfoAboutMoveUp(idInfo, borderRange, borderValue, upperBorder_, n, action)) {
                return idInfo;
            }
        }
    }

    /*
     * Сюда мы попадаем если n == 0 или если fillInfoAboutMoveUp или fillInfoAboutMoveDown вернет false.
     * В первом случае все понятно.
     * Во втором случае мы попадем сюда потому что fillInfoAboutMoveUp или fillInfoAboutMoveDown вернет false,
     * что значит что мы ХОТЕЛИ передвинуть границу, но у нас не получилось сдвинуть ее ни на один шаг.
     * Отсюда и операции вроде этой:
     * idInfo.flags += (n > 0 ? IDRF_ID_OUT_OF_LIMIT : IDRF_RANGE_ARE_BENT);
     */

    idInfo.position += IDRP_AT_BORDER;

    if (borderValue == start_)
        idInfo.position += IDRP_AT_START;

    idInfo.value = borderValue;
    idInfo.stepCount = 0;

    if (n == 0)
        idInfo.flags += IDRF_SUCCESSFULLY;
    else
        idInfo.flags += (n > 0 ? IDRF_ID_OUT_OF_LIMIT : IDRF_RANGE_ARE_BENT);

    fillInfoAboutTerritory(idInfo, borderRange, borderValue);
    return idInfo;
}

template<class T>
bool
ONF::IdRange<T>::
fillInfoAboutMoveUp(IdInfo& idInfo, BorderRange borderRange, T borderValue, T borderLimit, ldouble n, Action action) const
{
    if (static_cast<ldouble>(borderValue) + static_cast<ldouble>(ONF::abs(n) * step_) <= static_cast<ldouble>(borderLimit)) { 
        idInfo.value = borderValue + (ONF::abs(n) * step_);
        idInfo.flags += IDRF_SUCCESSFULLY;
        idInfo.stepCount = n;

        fillInfoAboutTerritory(idInfo, borderRange, idInfo.value);
        fillInfoAboutPos(idInfo, idInfo.value, n, action);
        return true;
    }

    /*
     * Если мы попали сюда, значит нам не удалось успешно сделать столько шагов сколько мы хотели,
     * потому в idInfo.flags мы записываем IDRF_ID_OUT_OF_LIMIT или IDRF_RANGE_ARE_BENT (зависит от ситуации),
     * но не IDRF_SUCCESSFULLY.
     */
    for(ldouble i = ONF::abs(n) - 1; i > 0; --i) {
        if (static_cast<ldouble>(borderValue) + static_cast<ldouble>(i * step_) <= static_cast<ldouble>(borderLimit)) {
            idInfo.value = borderValue + (i * step_);

            fillInfoAboutTerritory(idInfo, borderRange, idInfo.value);
            fillInfoAboutPos(idInfo, idInfo.value, n, action);

            if (n > 0) {
                idInfo.flags += IDRF_ID_OUT_OF_LIMIT;
                idInfo.stepCount = i;
                return true;
            }

            idInfo.flags += IDRF_RANGE_ARE_BENT;
            idInfo.stepCount = -i;
            return true;
        }
    }

    return false;
}

template<class T>
bool
ONF::IdRange<T>::
fillInfoAboutMoveDown(IdInfo& idInfo, BorderRange borderRange, T borderValue, T borderLimit, ldouble n, Action action) const
{
    if (static_cast<ldouble>(borderValue) - static_cast<ldouble>(ONF::abs(n) * step_) >= static_cast<ldouble>(borderLimit)) {
        idInfo.value = borderValue - (ONF::abs(n) * step_);
        idInfo.flags += IDRF_SUCCESSFULLY;
        idInfo.stepCount = n;

        fillInfoAboutTerritory(idInfo, borderRange, idInfo.value);
        fillInfoAboutPos(idInfo, idInfo.value, n, action);
        return true;
    }

    /*
     * Если мы попали сюда, значит нам не удалось успешно сделать столько шагов сколько мы хотели,
     * потому в idInfo.flags мы записываем IDRF_ID_OUT_OF_LIMIT или IDRF_RANGE_ARE_BENT (зависит от ситуации),
     * но не IDRF_SUCCESSFULLY.
     */
    for(ldouble i = ONF::abs(n) - 1; i > 0; --i) {
        if (static_cast<ldouble>(borderValue) - static_cast<ldouble>(i * step_) >= static_cast<ldouble>(borderLimit)) {
            idInfo.value = borderValue - (i * step_);

            fillInfoAboutTerritory(idInfo, borderRange, idInfo.value);
            fillInfoAboutPos(idInfo, idInfo.value, n, action);

            if (n > 0) {
                idInfo.flags += IDRF_ID_OUT_OF_LIMIT;
                idInfo.stepCount = i;
                return true;
            }

            idInfo.flags += IDRF_RANGE_ARE_BENT;
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
}

template<class T>
void
ONF::IdRange<T>::
fillInfoAboutPos(IdInfo& idInfo, T borderValue, ldouble n, Action action) const
{
    if (borderValue == start_)
        idInfo.position += IDRP_AT_START;

    if (action == Action::Move) {
        idInfo.position += IDRP_AT_BORDER;
        return;
    }

    if (idInfo.value == upperBorder_ || idInfo.value == lowerBorder_) {
        idInfo.position += IDRP_AT_BORDER;
        return;
    }

    idInfo.position += (n > 0 ? IDRP_OUT_OF_RANGE : IDRP_WITHIN_RANGE);
}


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
