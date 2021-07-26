#include "IdManager.h"
#include "ONF.h"
#include <cmath>
#include <cstdlib>
#include <type_traits>
#include <algorithm>
#include <limits>
#include <exception>
#include <string>
#include <utility>


template<class T>
ONF::IdContainer<T>::
IdContainer(IdIssuingMethod idIssuingMethod)
    : idIssuingMethod_(idIssuingMethod) {}

template<class T>
ONF::IdContainer<T>::
IdContainer(const IdContainer<T>& other)
    : unorderedIds_   (other.unorderedIds_),
      orderedIds_     (other.orderedIds_),
      idIssuingMethod_(other.idIssuingMethod_) {}

template<class T>
ONF::IdContainer<T>::
IdContainer(IdContainer<T>&& other)
    : unorderedIds_   (std::move(other.unorderedIds_)),
      orderedIds_     (std::move(other.orderedIds_)),
      idIssuingMethod_(std::move(other.idIssuingMethod_))
{
    other.unorderedIds_.clear();
    other.orderedIds_.clear();
    other.idIssuingMethod_ = IdIssuingMethod::Dynamic;
}

template<class T>
ONF::IdContainer<T>::
~IdContainer() {}

template<class T>
bool
ONF::IdContainer<T>::
add(T id)
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (std::find(unorderedIds_.begin(), unorderedIds_.end(), id) != unorderedIds_.end())
            return false;

        unorderedIds_.push_back(id);
        return true;
    }

    if (orderedIds_.find(id) != orderedIds_.end())
        return false;

    orderedIds_.insert(id);
    return true;
}

template<class T>
std::optional<T>
ONF::IdContainer<T>::
getNext()
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        auto it = unorderedIds_.begin();

        if (it == unorderedIds_.end())
            return std::nullopt;

        T id = *it;
        unorderedIds_.erase(std::move(it));
        return id;
    }

    if (!orderedIds_.size())
        return std::nullopt;

    if (idIssuingMethod_ == IdIssuingMethod::Ascending) {
        auto it = orderedIds_.begin();
        T id = *it;
        orderedIds_.erase(std::move(it));
        return id;
    }

    auto it = orderedIds_.end();
    --it;
    T id = *it;
    orderedIds_.erase(std::move(it));
    return id;
}

template<class T>
void
ONF::IdContainer<T>::
erase(T id)
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        auto it = std::find(unorderedIds_.begin(), unorderedIds_.end(), id);

        if (it != unorderedIds_.end())
            unorderedIds_.erase(std::move(it));

        return;
    }

    auto it = orderedIds_.find(id);

    if (it != orderedIds_.end())
        orderedIds_.erase(std::move(it));
}

template<class T>
inline void
ONF::IdContainer<T>::
clear()
{
    unorderedIds_.clear();
    orderedIds_.clear();
}

template<class T>
void
ONF::IdContainer<T>::
setIdIssuingMethod(IdIssuingMethod idIssuingMethod)
{
    if (idIssuingMethod == idIssuingMethod_)
        return;

    if ((idIssuingMethod == IdIssuingMethod::Ascending || idIssuingMethod == IdIssuingMethod::Descending) &&
        (idIssuingMethod_ == IdIssuingMethod::Ascending || idIssuingMethod_ == IdIssuingMethod::Descending)) {
        idIssuingMethod_ = idIssuingMethod;
        return;
    }

    idIssuingMethod_ = idIssuingMethod;

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        for (auto it = orderedIds_.begin(); it != orderedIds_.end(); ++it) {
            unorderedIds_.push_back(*it);
        }

        orderedIds_.clear();
        return;
    }

    for (auto it = unorderedIds_.begin(); it != unorderedIds_.end(); ++it) {
        orderedIds_.insert(*it);
    }

    unorderedIds_.clear();
}

template<class T>
inline ONF::IdIssuingMethod
ONF::IdContainer<T>::
getIdIssuingMethod() const
{
    return idIssuingMethod_;
}

template<class T>
inline bool
ONF::IdContainer<T>::
find(T id) const
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic)
        return std::find(unorderedIds_.begin(), unorderedIds_.end(), id) != unorderedIds_.end();

    return orderedIds_.find(id) != orderedIds_.end();
}

template<class T>
std::optional<T>
ONF::IdContainer<T>::
findByIndex(size_t index) const
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (index >= unorderedIds_.size())
            return std::nullopt;

        return *std::next(unorderedIds_.begin(), index);
    }

    if (index >= orderedIds_.size())
        return std::nullopt;

    if (idIssuingMethod_ == IdIssuingMethod::Ascending)
        return *std::next(orderedIds_.begin(), index);

    return *std::prev(orderedIds_.end(), index + 1);
}

template<class T>
inline size_t
ONF::IdContainer<T>::
size() const
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic)
        return unorderedIds_.size();

    return orderedIds_.size();
}

template<class T>
ONF::IdContainer<T>&
ONF::IdContainer<T>::
operator=(const IdContainer<T>& other)
{
    unorderedIds_    = other.unorderedIds_;
    orderedIds_      = other.orderedIds_;
    idIssuingMethod_ = other.idIssuingMethod_;

    return *this;
}

template<class T>
ONF::IdContainer<T>&
ONF::IdContainer<T>::
operator=(IdContainer<T>&& other)
{
    unorderedIds_    = std::move(other.unorderedIds_);
    orderedIds_      = std::move(other.orderedIds_);
    idIssuingMethod_ = std::move(other.idIssuingMethod_);

    other.unorderedIds_.clear();
    other.orderedIds_.clear();
    other.idIssuingMethod_ = IdIssuingMethod::Dynamic;

    return *this;
}

template<class T>
inline size_t
ONF::IdContainer<T>::
getUnorderedIdsSize() const
{
    return unorderedIds_.size();
}

template<class T>
inline size_t
ONF::IdContainer<T>::
getOrderedIdsSize() const
{
    return orderedIds_.size();
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
IdInfo(const IdInfo& other)
    : flags    (other.flags),
      position (other.position),
      border   (other.border),
      state    (other.state),
      value    (other.value),
      stepCount(other.stepCount) {}

template<class T>
ONF::IdRange<T>::IdInfo::
IdInfo(IdInfo&& other)
    : flags    (std::move(other.flags)),
      position (std::move(other.position)),
      border   (std::move(other.border)),
      state    (std::move(other.state)),
      value    (std::move(other.value)),
      stepCount(std::move(other.stepCount))
{
    other.flags     = IDRF_NOT_SET;
    other.position  = IDRP_NOT_SET;
    other.border    = BorderRange::UpperBorder;
    other.state     = false;
    other.value     = 0;
    other.stepCount = 0;
}

template<class T>
ONF::IdRange<T>::IdInfo::
~IdInfo() {}

template<class T>
typename ONF::IdRange<T>::IdInfo&
ONF::IdRange<T>::IdInfo::
operator=(const IdInfo& other)
{
    flags     = other.flags;
    position  = other.position;
    border    = other.border;
    state     = other.state;
    value     = other.value;
    stepCount = other.stepCount;

    return *this;
}

template<class T>
typename ONF::IdRange<T>::IdInfo&
ONF::IdRange<T>::IdInfo::
operator=(IdInfo&& other)
{
    flags     = std::move(other.flags);
    position  = std::move(other.position);
    border    = std::move(other.border);
    state     = std::move(other.state);
    value     = std::move(other.value);
    stepCount = std::move(other.stepCount);

    other.flags     = IDRF_NOT_SET;
    other.position  = IDRP_NOT_SET;
    other.border    = BorderRange::UpperBorder;
    other.state     = false;
    other.value     = 0;
    other.stepCount = 0;

    return *this;
}


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
      step_            (step == 0 ? 1 : onf_abs(step)) {}

template<class T>
ONF::IdRange<T>::
IdRange(const IdRange<T>& other)
    : upperBorderState_(other.upperBorderState_),
      upperBorder_     (other.upperBorder_),
      upperLimit_      (other.upperLimit_),
      lowerBorderState_(other.lowerBorderState_),
      lowerBorder_     (other.lowerBorder_),
      lowerLimit_      (other.lowerLimit_),
      start_           (other.start_),
      step_            (other.step_) {}

template<class T>
ONF::IdRange<T>::
IdRange(IdRange<T>&& other)
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
    other.upperBorder_      = other.start_;
    other.upperLimit_       = std::numeric_limits<T>::max();
    other.lowerBorderState_ = false;
    other.lowerBorder_      = other.start_;
    other.lowerLimit_       = std::numeric_limits<T>::lowest();
}

template<class T>
ONF::IdRange<T>::
~IdRange() {}

template<class T>
typename ONF::IdRange<T>::IdInfo
ONF::IdRange<T>::
moveBorder(BorderRange borderRange, longlong n)
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
getIdInfo(BorderRange borderRange, longlong n) const
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
getIdInfo(BorderRange borderRange, T id, longlong n) const
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
ONF::IdRange<T>&
ONF::IdRange<T>::
operator=(const IdRange<T>& other)
{
    upperBorderState_ = other.upperBorderState_;
    upperBorder_      = other.upperBorder_;
    upperLimit_       = other.upperLimit_;
    lowerBorderState_ = other.lowerBorderState_;
    lowerBorder_      = other.lowerBorder_;
    lowerLimit_       = other.lowerLimit_;
    start_            = other.start_;
    step_             = other.step_;

    return *this;
}

template<class T>
ONF::IdRange<T>&
ONF::IdRange<T>::
operator=(IdRange<T>&& other)
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
    other.upperBorder_      = other.start_;
    other.upperLimit_       = std::numeric_limits<T>::max();
    other.lowerBorderState_ = false;
    other.lowerBorder_      = other.start_;
    other.lowerLimit_       = std::numeric_limits<T>::lowest();

    return *this;
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
    if (static_cast<ldouble>(borderValue) + static_cast<ldouble>(onf_abs(n) * step_) <= static_cast<ldouble>(borderLimit)) {
        idInfo.flags = IDRF_SUCCESSFULLY;
        idInfo.value = borderValue + (onf_abs(n) * step_);
        idInfo.stepCount = n;
        return true;
    }

    for(ldouble i = onf_abs(n) - 1; i > 0; --i) {
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
    if (static_cast<ldouble>(borderValue) - static_cast<ldouble>(onf_abs(n) * step_) >= static_cast<ldouble>(borderLimit)) {
        idInfo.flags = IDRF_SUCCESSFULLY;
        idInfo.value = borderValue - (onf_abs(n) * step_);
        idInfo.stepCount = n;
        return true;
    }

    for(ldouble i = onf_abs(n) - 1; i > 0; --i) {
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



template<class __T, class __Step>
ONF::IdManager<__T, __Step>::
IdManager(__T startId,
          __Step step,
          IdIssuingMethod idIssuingMethod,
          bool isHardStep)
    : freeIds_        (idIssuingMethod),
      reservedIds_    (),
      isHardStep_     (isHardStep),
      idIssuingMethod_(idIssuingMethod)
{
    static_assert(is_types_combination_prohibited<__T, __Step> == false);

    step_ = (step == 0 ? 1 : step);
    idArea_ = IdRange<__T>(startId, step_);
}

template<class __T, class __Step>
ONF::IdManager<__T, __Step>::
IdManager(const IdManager<__T, __Step>& other)
    : freeIds_        (other.freeIds_),
      reservedIds_    (other.reservedIds_),
      idArea_         (other.idArea_),
      step_           (other.step_),
      isHardStep_     (other.isHardStep),
      idIssuingMethod_(other.idIssuingMethod_) {}

template<class __T, class __Step>
ONF::IdManager<__T, __Step>::
~IdManager() {}


template<class __T, class __Step>
int
ONF::IdManager<__T, __Step>::
getFreeId(__T& id)
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (idArea_.getBorderValue(BorderRange::UpperBorder) == idArea_.getBorderValue(BorderRange::LowerBorder) &&
            idArea_.getBorderState(BorderRange::UpperBorder) == false &&
            idArea_.getBorderState(BorderRange::LowerBorder) == false) {

            idArea_.setBorderState(BorderRange::UpperBorder, true);
            idArea_.setBorderState(BorderRange::LowerBorder, true);

            id = idArea_.getBorderValue(BorderRange::UpperBorder);

            expandRange(BorderRange::UpperBorder);
            expandRange(BorderRange::LowerBorder);

            return IDRF_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::LowerBorder) == false) {
            idArea_.setBorderState(BorderRange::LowerBorder, true);
            id = idArea_.getBorderValue(BorderRange::LowerBorder);
            expandRange(BorderRange::LowerBorder);
            return IDRF_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::UpperBorder) == false) {
            idArea_.setBorderState(BorderRange::UpperBorder, true);
            id = idArea_.getBorderValue(BorderRange::UpperBorder);
            expandRange(BorderRange::UpperBorder);
            return IDRF_SUCCESSFULLY;
        }

        if (idArea_.getBorderValue(BorderRange::UpperBorder) < idArea_.getStart()) {
            getNextId(BorderRange::UpperBorder, id);
            return IDRF_SUCCESSFULLY;
        }

        if (idArea_.getBorderValue(BorderRange::LowerBorder) > idArea_.getStart()) {
            getNextId(BorderRange::LowerBorder, id);
            return IDRF_SUCCESSFULLY;
        }

        if (freeIds_.size()) {
            freeIds_.getNextId(id);
            return IDRF_SUCCESSFULLY;
        }

        if (step_ > 0) {
            getNextId(BorderRange::UpperBorder, id);
            return IDRF_SUCCESSFULLY;
        }

        if (step_ < 0) {
            getNextId(BorderRange::LowerBorder, id);
            return IDRF_SUCCESSFULLY;
        }

        return IDRF_RANGE_ARE_BENT;
    }

    if (idIssuingMethod_ == IdIssuingMethod::Ascending) {
        if (idArea_.getBorderValue(BorderRange::UpperBorder) == idArea_.getBorderValue(BorderRange::LowerBorder) &&
            idArea_.getBorderState(BorderRange::UpperBorder) == false &&
            idArea_.getBorderState(BorderRange::LowerBorder) == false) {

            idArea_.setBorderState(BorderRange::UpperBorder, true);
            idArea_.setBorderState(BorderRange::LowerBorder, true);

            id = idArea_.getBorderValue(BorderRange::UpperBorder);

            expandRange(BorderRange::UpperBorder);
            expandRange(BorderRange::LowerBorder);

            return IDRF_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::LowerBorder) == false) {
            idArea_.setBorderState(BorderRange::LowerBorder, true);
            id = idArea_.getBorderValue(BorderRange::LowerBorder);
            expandRange(BorderRange::LowerBorder);
            return IDRF_SUCCESSFULLY;
        }

        if (freeIds_.size()) {
            freeIds_.getNextId(id);
            return IDRF_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::UpperBorder) == false) {
            idArea_.setBorderState(BorderRange::UpperBorder, true);
            id = idArea_.getBorderValue(BorderRange::UpperBorder);
            expandRange(BorderRange::UpperBorder);
            return IDRF_SUCCESSFULLY;
        }

        if (step_ > 0) {
            getNextId(BorderRange::UpperBorder, id);
            return IDRF_SUCCESSFULLY;
        }

        if (step_ < 0) {
            getNextId(BorderRange::LowerBorder, id);
            return IDRF_SUCCESSFULLY;
        }

        return IDRF_RANGE_ARE_BENT;
    }

    if (idIssuingMethod_ == IdIssuingMethod::Descending) {
        if (idArea_.getBorderValue(BorderRange::UpperBorder) == idArea_.getBorderValue(BorderRange::LowerBorder) &&
            idArea_.getBorderState(BorderRange::UpperBorder) == false &&
            idArea_.getBorderState(BorderRange::LowerBorder) == false) {

            idArea_.setBorderState(BorderRange::UpperBorder, true);
            idArea_.setBorderState(BorderRange::LowerBorder, true);

            id = idArea_.getBorderValue(BorderRange::UpperBorder);

            expandRange(BorderRange::UpperBorder);
            expandRange(BorderRange::LowerBorder);

            return IDRF_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::UpperBorder) == false) {
            idArea_.setBorderState(BorderRange::UpperBorder, true);
            id = idArea_.getBorderValue(BorderRange::UpperBorder);
            expandRange(BorderRange::UpperBorder);
            return IDRF_SUCCESSFULLY;
        }

        if (freeIds_.size()) {
            freeIds_.getNextId(id);
            return IDRF_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::LowerBorder) == false) {
            idArea_.setBorderState(BorderRange::LowerBorder, true);
            id = idArea_.getBorderValue(BorderRange::LowerBorder);
            expandRange(BorderRange::LowerBorder);
            return IDRF_SUCCESSFULLY;
        }

        if (step_ < 0) {
            getNextId(BorderRange::LowerBorder, id);
            return IDRF_SUCCESSFULLY;
        }

        if (step_ > 0) {
            getNextId(BorderRange::UpperBorder, id);
            return IDRF_SUCCESSFULLY;
        }

        return IDRF_RANGE_ARE_BENT;
    }
}

template<class __T, class __Step>
bool
ONF::IdManager<__T, __Step>::
reserveId(__T id, ReservationMethod reservationMethod)
{
    if (id < std::numeric_limits<__T>::lowest() || id > std::numeric_limits<__T>::max())
        return false;

    if (!isStandardId(id)) {
        if (isHardStep_)
            return false;

        if (reservedIds_.find(id))
            return false;

        if (reservationMethod == ReservationMethod::Interpolate) {
            if (id > idArea_.getBorderValue(BorderRange::UpperBorder))
                return interpolateIds(BorderRange::UpperBorder, id);

            if (id < idArea_.getBorderValue(BorderRange::LowerBorder))
                return interpolateIds(BorderRange::LowerBorder, id);

            reservedIds_.add(id);
            return true;
        }

        if (reservationMethod == ReservationMethod::ReserveRange) {
            if (id > idArea_.getBorderValue(BorderRange::UpperBorder))
                return reserveIds(BorderRange::UpperBorder, id);

            if (id < idArea_.getBorderValue(BorderRange::LowerBorder))
                return reserveIds(BorderRange::LowerBorder, id);

            reservedIds_.add(id);
            return true;
        }

        reservedIds_.add(id);
        return true;
    }


    if (idArea_.getBorderValue(BorderRange::UpperBorder) == idArea_.getBorderValue(BorderRange::LowerBorder) &&
        idArea_.getBorderValue(BorderRange::UpperBorder) == id) {
        if (idArea_.getBorderState(BorderRange::UpperBorder) == true &&
            idArea_.getBorderState(BorderRange::LowerBorder) == true)
            return false;

        idArea_.setBorderState(BorderRange::UpperBorder, true);
        idArea_.setBorderState(BorderRange::LowerBorder, true);

        expandRange(BorderRange::UpperBorder);
        expandRange(BorderRange::LowerBorder);

        return true;
    }

    if (id == idArea_.getBorderValue(BorderRange::UpperBorder)) {
        if (idArea_.getBorderState(BorderRange::UpperBorder))
            return false;

        idArea_.setBorderState(BorderRange::UpperBorder, true);
        expandRange(BorderRange::UpperBorder);

        return true;
    }

    if (id == idArea_.getBorderValue(BorderRange::LowerBorder)) {
        if (idArea_.getBorderState(BorderRange::LowerBorder))
            return false;

        idArea_.setBorderState(BorderRange::LowerBorder, true);
        expandRange(BorderRange::LowerBorder);

        return true;
    }

    if (id > idArea_.getBorderValue(BorderRange::UpperBorder) || id < idArea_.getBorderValue(BorderRange::LowerBorder))
        if (reservedIds_.find(id))
            return false;

    if (id < idArea_.getBorderValue(BorderRange::UpperBorder) && id > idArea_.getBorderValue(BorderRange::LowerBorder)) {
        if (!freeIds_.find(id))
            return false;

        freeIds_.freeId(id);
        return true;
    }

    if (reservationMethod == ReservationMethod::Interpolate || reservationMethod == ReservationMethod::AutoSelect) {
        if (id > idArea_.getBorderValue(BorderRange::UpperBorder))
            return interpolateIds(BorderRange::UpperBorder, id);

        return interpolateIds(BorderRange::LowerBorder, id);
    }

    if (reservationMethod == ReservationMethod::ReserveRange) {
        if (id > idArea_.getBorderValue(BorderRange::UpperBorder))
            return reserveIds(BorderRange::UpperBorder, id);

        return reserveIds(BorderRange::LowerBorder, id);
    }

    reservedIds_.add(id);
    return true;
}

template<class __T, class __Step>
bool
ONF::IdManager<__T, __Step>::
interpolateIds(BorderRange border, __T id)
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        int _count = 0;
        int _i = 1;

        while (true) {
            auto _result = idArea_.getIdInfo(border, _i);

            if (reservedIds_.find(_result.value)) {
                reservedIds_.freeId(_result.value);
                _count = _i;
            }
            else {
                if (_result.value > id)
                    break;

                freeIds_.add(_result.value);
            }

            ++_i;
        }

        idArea_.moveBorder(border, _count);

        if (!isStandardId(id))
            reservedIds_.add(id);

        return true;
    }

    __T _startValueU = idArea_.getBorderValue(BorderRange::UpperBorder);
    __T _startValueL = idArea_.getBorderValue(BorderRange::LowerBorder);
    bool _startState = idArea_.getBorderState(border);


    __T _lastValue = (border == BorderRange::UpperBorder ? _startValueU : _startValueL);
    bool _currentState = _startState;

    int _i = 0;

    while (true) {
        auto _result = idArea_.getIdInfo(border, 1);

        if (reservedIds_.find(_result.value)) {
            reservedIds_.freeId(_result.value);
            _currentState = true;
        }
        else {
            if (_result.value > id)
                break;

            freeIds_.add(_result.value);
            _lastValue = _result.value;
            _currentState = false;
        }

        idArea_.moveBorder(border, 1);
        ++_i;
    }

    if (_i != 0) {
        idArea_.setBorderState(border, _currentState);
        if (_currentState == false) {
            freeIds_.freeId(_lastValue);
        }

        if (_startValueU != _startValueL && !_startState) {
            if (border == BorderRange::UpperBorder)
                freeIds_.add(_startValueU);
            else
                freeIds_.add(_startValueL);
        }
    }

    if (!isStandardId(id))
        reservedIds_.add(id);

    return true;
}

template<class __T, class __Step>
bool
ONF::IdManager<__T, __Step>::
reserveIds(BorderRange border, __T id)
{
    if (idArea_.getBorderValue(BorderRange::UpperBorder) == idArea_.getBorderValue(BorderRange::LowerBorder)) {
        idArea_.setBorderState(BorderRange::UpperBorder, true);
        idArea_.setBorderState(BorderRange::LowerBorder, true);
    }

    while (true) {
        auto _result = idArea_.getIdInfo(border, 1);

        if (reservedIds_.find(_result.value)) {
            reservedIds_.freeId(_result.value);
        }
        else {
            if (_result.value > id)
                break;
        }

        idArea_.moveBorder(border, 1);
    }

    if (!isStandardId(id))
        reservedIds_.add(id);

    if (idIssuingMethod_ == IdIssuingMethod::Ascending || idIssuingMethod_ == IdIssuingMethod::Descending) {
        idArea_.setBorderState(border, true);
    }

    return true;
}


template<class __T, class __Step>
bool
ONF::IdManager<__T, __Step>::
freeId(__T id)
{
    if (id < std::numeric_limits<__T>::lowest() || id > std::numeric_limits<__T>::max())
        return false;

    if (!isStandardId(id)) {
        if (!reservedIds_.find(id))
            return false;

        reservedIds_.freeId(id);
        return true;
    }

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (id == idArea_.getBorderValue(BorderRange::UpperBorder)) {
            if (reduceRange(BorderRange::UpperBorder) == IDRF_RANGE_ARE_BENT) {
                idArea_.setBorderState(BorderRange::UpperBorder, false);
                idArea_.setBorderState(BorderRange::LowerBorder, false);
                return true;
            }

            return true;
        }

        if (id == idArea_.getBorderValue(BorderRange::LowerBorder)) {
            if (reduceRange(BorderRange::LowerBorder) == IDRF_RANGE_ARE_BENT) {
                idArea_.setBorderState(BorderRange::UpperBorder, false);
                idArea_.setBorderState(BorderRange::LowerBorder, false);
                return true;
            }

            return true;
        }
    }
    else {
        if (id == idArea_.getBorderValue(BorderRange::UpperBorder) &&
            id == idArea_.getBorderValue(BorderRange::LowerBorder)) {

            if (!idArea_.getBorderState(BorderRange::UpperBorder) &&
                !idArea_.getBorderState(BorderRange::LowerBorder))
                return false;

            if (idArea_.getBorderState(BorderRange::UpperBorder) !=
                idArea_.getBorderState(BorderRange::LowerBorder))
                throw "---------------";

            idArea_.setBorderState(BorderRange::UpperBorder, false);
            idArea_.setBorderState(BorderRange::LowerBorder, false);
            return true;
        }

        if (id == idArea_.getBorderValue(BorderRange::UpperBorder)) {
            if (!idArea_.getBorderState(BorderRange::UpperBorder))
                return false;

            idArea_.setBorderState(BorderRange::UpperBorder, false);
            return true;
        }

        if (id == idArea_.getBorderValue(BorderRange::LowerBorder)) {
            if (!idArea_.getBorderState(BorderRange::LowerBorder))
                return false;

            idArea_.setBorderState(BorderRange::LowerBorder, false);
            return true;
        }
    }

    if (id < idArea_.getBorderValue(BorderRange::UpperBorder) &&
        id > idArea_.getBorderValue(BorderRange::LowerBorder)) {

        if (freeIds_.find(id))
            return false;

        freeIds_.add(id);
        return true;
    }

    if (!reservedIds_.find(id))
        return false;

    reservedIds_.freeId(id);
    return true;
}

template<class __T, class __Step>
void
ONF::IdManager<__T, __Step>::
freeAll()
{
    freeIds_.clear();
    reservedIds_.clear();
    idArea_.reset();
}

template<class __T, class __Step>
void
ONF::IdManager<__T, __Step>::
setHardStep(bool value)
{
    if (value == isHardStep_)
        return;

    isHardStep_ = value;

    if (value == false)
        return;

    // i итерируется таким образом для простой поддержки unsigned.
    for (__T i = 0; i < reservedIds_.size();) {
        __T _id = reservedIds_.findIdByIndex(i);
        if (!isStandardId(_id)) {
            reservedIds_.freeId(_id);
            continue;
        }

        ++i;
    }
}

template<class __T, class __Step>
bool
ONF::IdManager<__T, __Step>::
isHardStep() const
{
    return isHardStep_;
}

template<class __T, class __Step>
void
ONF::IdManager<__T, __Step>::
setIdIssuingMethod(IdIssuingMethod idIssuingMethod)
{
    if (idIssuingMethod == idIssuingMethod_)
        return;

    freeIds_.setIdIssuingMethod(idIssuingMethod);
    idIssuingMethod_ = idIssuingMethod;

    if (idIssuingMethod == IdIssuingMethod::Dynamic) {
        if (normalizeRange(BorderRange::UpperBorder, IdIssuingMethod::Dynamic) == IDRF_RANGE_ARE_BENT ||
            normalizeRange(BorderRange::LowerBorder, IdIssuingMethod::Dynamic) == IDRF_RANGE_ARE_BENT) {
            idArea_.setBorderState(BorderRange::UpperBorder, false);
            idArea_.setBorderState(BorderRange::LowerBorder, false);
        }

        return;
    }
}

template<class __T, class __Step>
inline ONF::IdIssuingMethod
ONF::IdManager<__T, __Step>::
getIdIssuingMethod() const
{
    return idIssuingMethod_;
}

template<class __T, class __Step>
bool
ONF::IdManager<__T, __Step>::
findId(__T id) const
{
    if (id < std::numeric_limits<__T>::lowest() || id > std::numeric_limits<__T>::max())
        return false;

    if (!isStandardId(id)) {
        if (isHardStep_)
            return false;

        return reservedIds_.find(id);
    }

    if (id < idArea_.getBorderValue(BorderRange::UpperBorder) &&
        id > idArea_.getBorderValue(BorderRange::LowerBorder))
        return !freeIds_.find(id);

    if (id == idArea_.getBorderValue(BorderRange::UpperBorder))
        return idArea_.getBorderState(BorderRange::UpperBorder);

    if (id == idArea_.getBorderValue(BorderRange::LowerBorder))
        return idArea_.getBorderState(BorderRange::LowerBorder);

    return reservedIds_.find(id);
}

template<class __T, class __Step>
bool
ONF::IdManager<__T, __Step>::
isStandardId(__T id) const
{
    ldouble _An = static_cast<ldouble>(id);
    ldouble _A1 = static_cast<ldouble>(idArea_.getStart());
    ldouble _d = static_cast<ldouble>(step_);

    ldouble n = std::abs((_An - _A1 + _d) / _d);
    return (n - static_cast<ulonglong>(n) == static_cast<ldouble>(0.0));
}

template<class __T, class __Step>
__Step
ONF::IdManager<__T, __Step>::
getStep() const
{
    return step_;
}

template<class __T, class __Step>
ONF::IdManager<__T, __Step>&
ONF::IdManager<__T, __Step>::
operator=(const IdManager<__T, __Step>& other)
{
    freeIds_ = other.freeIds_;
    reservedIds_ = other.reservedIds_;
    idArea_ = other.idArea_;

    step_ = other.step_;
    isHardStep_ = other.isHardStep_;
    idIssuingMethod_ = other.idIssuingMethod_;

    return *this;
}

template<class __T, class __Step>
int
ONF::IdManager<__T, __Step>::
expandRange(BorderRange border)
{
    while (true) {
        auto _result = idArea_.getIdInfo(border, 1);
        if (reservedIds_.find(_result.value)) {
            reservedIds_.freeId(_result.value);
            idArea_.moveBorder(border, 1);
            continue;
        }

        return _result.errCode;
    }
}

template<class __T, class __Step>
int
ONF::IdManager<__T, __Step>::
reduceRange(BorderRange border)
{
    while (true) {
        auto _result = idArea_.moveBorder(border, -1);

        if (_result.errCode == IDRF_RANGE_ARE_BENT)
            return IDRF_RANGE_ARE_BENT;

        if (freeIds_.find(_result.value))
            continue;

        return _result.errCode;
    }
}

template<class __T, class __Step>
int
ONF::IdManager<__T, __Step>::
normalizeRange(BorderRange border)
{
    auto _result = idArea_.getIdInfo(border, 1);

    if (reservedIds_.find(_result.value)) {
        if (!idArea_.getBorderState(border)) {
            freeIds_.add(idArea_.getBorderValue(border));
            idArea_.setBorderState(border, true);
        }

        return expandRange(border);
    }

    if (idArea_.getBorderState(border)) {
        return IDRF_SUCCESSFULLY;
    }

    idArea_.setBorderState(border, true);
    return reduceRange(border);
}

template<class __T, class __Step>
int
ONF::IdManager<__T, __Step>::
getNextId(BorderRange border, __T& id)
{
    while (true) {
        auto _result = idArea_.moveBorder(border, 1);
        if (reservedIds_.find(_result.value)) {
            reservedIds_.freeId(_result.value);
            continue;
        }

        id = _result.value;
        return _result.errCode;
    }
}

template<class __T, class __Step>
template<class __TF>
inline __TF
ONF::IdManager<__T, __Step>::
onf_abs(__TF value) const
{
    return value < 0 ? -value : value;
}


























//template<class __T, class __Step>
//bool
//ONF::IdManager<__T, __Step>::
//reserveId(__T id, ReservationMethod reservationMethod)
//{
//    if (!isStandardId(id)) {
//        if (isHardStep_)
//            return false;

//        if (reservedIds_.find(id))
//            return false;

//        if (id < std::numeric_limits<__T>::min() || id > std::numeric_limits<__T>::max())
//            return false;

//        if (reservationMethod == ReservationMethod::Interpolate) {
//            if (id > idArea_.getBorderValue(BorderRange::UpperBorder)) {
//                auto _result = idArea_.getIdInfo(BorderRange::UpperBorder, 1);

//                while (_result.value < id || reservedIds_.find(_result.value) == true) {
//                    if (reservedIds_.find(_result.value))
//                        reservedIds_.freeId(_result.value);
//                    else
//                        freeIds_.add(_result.value);

//                    idArea_.moveBorder(BorderRange::UpperBorder, 1);
//                    _result = idArea_.getIdInfo(BorderRange::UpperBorder, 1);
//                }

//                reservedIds_.add(id);
//                return true;
//            }

//            if (id < idArea_.getMinId()) {
//                __T _id = 0;
//                idArea_.checkBorder(BorderRange::LowerBorder, _id);

//                while (_id > id  || reservedIds_.find(_id) == true) {
//                    if (reservedIds_.find(_id))
//                        reservedIds_.freeId(_id);
//                    else
//                        freeIds_.add(_id);

//                    idArea_.pushBorder(BorderRange::LowerBorder);
//                    idArea_.checkBorder(BorderRange::LowerBorder, _id);
//                }

//                reservedIds_.add(id);
//                return true;
//            }

//            if (id > idArea_.getMinId() && id < idArea_.getMaxId()) {
//                reservedIds_.add(id);
//                return true;
//            }

//            throw "-----------------------";
//        }

//        if (reservationMethod == ReservationMethod::ReserveRange) {
//            if (id > idArea_.getMaxId()) {
//                __T _id = 0;
//                idArea_.checkBorder(BorderRange::UpperBorder, _id);

//                while (_id < id || reservedIds_.find(_id) == true) {
//                    if (reservedIds_.find(_id))
//                        reservedIds_.freeId(_id);

//                    idArea_.pushBorder(BorderRange::UpperBorder);
//                    idArea_.checkBorder(BorderRange::UpperBorder, _id);
//                }

//                return true;
//            }

//            if (id < idArea_.getMinId()) {
//                __T _id = 0;
//                idArea_.checkBorder(BorderRange::LowerBorder, _id);

//                while (_id > id || reservedIds_.find(_id) == true) {
//                    if (reservedIds_.find(_id))
//                        reservedIds_.freeId(_id);

//                    idArea_.pushBorder(BorderRange::LowerBorder);
//                    idArea_.checkBorder(BorderRange::LowerBorder, _id);
//                }

//                return true;
//            }

//            if (id > idArea_.getMinId() && id < idArea_.getMaxId()) {
//                if (step_ < 0) {
//                    for (__T i = idArea_.getMinId() + idArea_.getStep(); i < id; i += idArea_.getStep()) {
//                        if (freeIds_.find(i))
//                            freeIds_.freeId(i);
//                    }

//                    return true;
//                }

//                if (step_ > 0) {
//                    for (__T i = idArea_.getMaxId() - idArea_.getStep(); i > id; i -= idArea_.getStep()) {
//                        if (freeIds_.find(i))
//                            freeIds_.freeId(i);
//                    }

//                    return true;
//                }
//            }

//            throw "-----------------------";
//        }

//        if (reservationMethod == ReservationMethod::ExpandRange) { //Контролировать флаги границ и чтобы в динамическом режиме нельзя было создаить пустые границы ExpandRange.
//            if (id > idArea_.getMaxId()) {
//                __T _id = 0;
//                idArea_.checkBorder(BorderRange::UpperBorder, _id);

//                while (_id < id || reservedIds_.find(_id) == true) {
//                    if (reservedIds_.find(_id))
//                        reservedIds_.freeId(_id);
//                    else
//                        freeIds_.add(_id);

//                    idArea_.pushBorder(BorderRange::UpperBorder);
//                    idArea_.checkBorder(BorderRange::UpperBorder, _id);
//                }

//                return true;
//            }

//            if (id < idArea_.getMinId()) {
//                __T _id = 0;
//                idArea_.checkBorder(BorderRange::LowerBorder, _id);

//                while (_id > id || reservedIds_.find(_id) == true) {
//                    if (reservedIds_.find(_id))
//                        reservedIds_.freeId(_id);
//                    else
//                        freeIds_.add(_id);

//                    idArea_.pushBorder(BorderRange::LowerBorder);
//                    idArea_.checkBorder(BorderRange::LowerBorder, _id);
//                }

//                return true;
//            }

//            if (id > idArea_.getMinId() && id < idArea_.getMaxId()) {
//                return true;
//            }

//            throw "-----------------------";
//        }

//        reservedIds_.add(id);
//        return true;
//    }


//    if (id == idArea_.getMinId() && idArea_.isMinIdOn() == true)
//        return false;

//    if (id == idArea_.getMaxId() && idArea_.isMaxIdOn() == true)
//        return false;

//    if (id == idArea_.getMinId()) {
//        idArea_.turnOnBorder(BorderRange::LowerBorder, true);
//        return true;
//    }

//    if (id == idArea_.getMaxId()) {
//        idArea_.turnOnBorder(BorderRange::UpperBorder, true);
//        return true;
//    }

//    if (id > idArea_.getMinId() && id < idArea_.getMaxId()) {
//        if (!freeIds_.find(id))
//            return false;

//        freeIds_.freeId(id);
//        return true;
//    }

//    if (id < std::numeric_limits<__T>::min() || id > std::numeric_limits<__T>::max())
//        return false;

//    if (reservedIds_.find(id))
//        return false;

//    if (reservationMethod == ReservationMethod::Interpolate || reservationMethod == ReservationMethod::AutoSelect) {
//        if (id > idArea_.getMaxId()) {
//            __T _id = 0;
//            idArea_.checkBorder(BorderRange::UpperBorder, _id);

//            while (_id <= id) {
//                if (reservedIds_.find(_id))
//                    reservedIds_.freeId(_id);
//                else
//                    freeIds_.add(_id);

//                idArea_.pushBorder(BorderRange::UpperBorder);
//                idArea_.checkBorder(BorderRange::UpperBorder, _id);
//            }

//            return true;
//        }

//        if (id < idArea_.getMinId()) {
//            __T _id = 0;
//            idArea_.checkBorder(BorderRange::LowerBorder, _id);

//            while (_id >= id) {
//                if (reservedIds_.find(_id))
//                    reservedIds_.freeId(_id);
//                else
//                    freeIds_.add(_id);

//                idArea_.pushBorder(BorderRange::LowerBorder);
//                idArea_.checkBorder(BorderRange::LowerBorder, _id);
//            }

//            return true;
//        }

//        throw "-----------------------";
//    }

//    if (reservationMethod == ReservationMethod::ReserveRange) {
//        if (id > idArea_.getMaxId()) {
//            __T _id = 0;
//            idArea_.checkBorder(BorderRange::UpperBorder, _id);

//            while (_id <= id) {
//                if (reservedIds_.find(_id))
//                    reservedIds_.freeId(_id);

//                idArea_.pushBorder(BorderRange::UpperBorder);
//                idArea_.checkBorder(BorderRange::UpperBorder, _id);
//            }

//            return true;
//        }

//        if (id < idArea_.getMinId()) {
//            __T _id = 0;
//            idArea_.checkBorder(BorderRange::LowerBorder, _id);

//            while (_id >= id) {
//                if (reservedIds_.find(_id))
//                    reservedIds_.freeId(_id);

//                idArea_.pushBorder(BorderRange::LowerBorder);
//                idArea_.checkBorder(BorderRange::LowerBorder, _id);
//            }

//            return true;
//        }

//        throw "-----------------------";
//    }

//    if (reservationMethod == ReservationMethod::ExpandRange) {
//        if (id > idArea_.getMaxId()) {
//            __T _id = 0;
//            idArea_.checkBorder(BorderRange::UpperBorder, _id);

//            while (_id <= id) {
//                if (reservedIds_.find(_id))
//                    reservedIds_.freeId(_id);
//                else
//                    freeIds_.add(_id);

//                idArea_.pushBorder(BorderRange::UpperBorder);
//                idArea_.checkBorder(BorderRange::UpperBorder, _id);
//            }

//            return true;
//        }

//        if (id < idArea_.getMinId()) {
//            __T _id = 0;
//            idArea_.checkBorder(BorderRange::LowerBorder, _id);

//            while (_id >= id) {
//                if (reservedIds_.find(_id))
//                    reservedIds_.freeId(_id);
//                else
//                    freeIds_.add(_id);

//                idArea_.pushBorder(BorderRange::LowerBorder);
//                idArea_.checkBorder(BorderRange::LowerBorder, _id);
//            }

//            return true;
//        }

//        throw "-----------------------";
//    }

//    reservedIds_.add(id);   //isMaxIdOn_ не учитывается.
//    return true;
//}

//template<class __T, class __Step>
//int
//ONF::IdManager<__T, __Step>::
//expandRangeToTop(BorderRange border, __T* id)
//{
//    int _errCode = IDRF_SUCCESSFULLY;

//    if (border == BorderRange::UpperBorder) {
//        while (true) {
//            if (reservedIds_.find(*id)) {
//                reservedIds_.freeId(*id);
//                _errCode = idArea_.pushBorder(BorderRange::UpperBorder, id);
//                continue;
//            }

//            return _errCode;
//        }
//    }

//    if (border == BorderRange::LowerBorder) {
//        while (true) {
//            if (reservedIds_.find(*id)) {
//                reservedIds_.freeId(*id);
//                _errCode = idArea_.pushBorder(BorderRange::LowerBorder, id);
//                continue;
//            }

//            return _errCode;
//        }
//    }
//}

//template<class __T, class __Step>
//int
//ONF::IdManager<__T, __Step>::
//expandRangeToTopWithowtReserv(BorderRange border, __T* id)
//{
//    int _errCode = IDRF_SUCCESSFULLY;

//    if (border == BorderRange::UpperBorder) {
//        while (true) {
//            if (reservedIds_.find(*id)) {
//                reservedIds_.freeId(*id);
//                _errCode = idArea_.pushBorder(BorderRange::UpperBorder, id);
//                idArea_.checkBorder(BorderRange::UpperBorder, id);
//                continue;
//            }

//            return _errCode;
//        }
//    }

//    if (border == BorderRange::LowerBorder) {
//        while (true) {
//            if (reservedIds_.find(*id)) {
//                reservedIds_.freeId(*id);
//                _errCode = idArea_.pushBorder(BorderRange::LowerBorder, id);
//                idArea_.checkBorder(BorderRange::LowerBorder, id);
//                continue;
//            }

//            return _errCode;
//        }
//    }
//}

//template<class __T, class __Step>
//int
//ONF::IdManager<__T, __Step>::
//expandRangeToBottom(BorderRange border, __T* id)
//{
//    int _errCode = IDRF_SUCCESSFULLY;

//    if (border == UpperBorder) {
//        while (true) {
//            if (reservedIds_.find(id)) {
//                reservedIds_.freeId(id);
//                _errCode = idArea_.narrowBorder(UpperBorder, id);
//                continue;
//            }

//            return _errCode;
//        }
//    }

//    if (border == LowerBorder) {
//        while (true) {
//            if (reservedIds_.find(id)) {
//                reservedIds_.freeId(id);
//                _errCode = idArea_.narrowBorder(LowerBorder, id);
//                continue;
//            }

//            return _errCode;
//        }
//    }
//}

//template<class __T, class __Step>
//bool
//ONF::IdManager<__T, __Step>::
//checkRangeBorder(__T value, BorderRange border) const
//{
//    switch (border) {
//        case BorderRange::LowerBorder:    return (static_cast<long long>(value) - static_cast<long long>(onf_abs(step_)) < std::numeric_limits<__T>::min());
//        case BorderRange::UpperBorder:    return (static_cast<long long>(value) + static_cast<long long>(onf_abs(step_)) > std::numeric_limits<__T>::max());

//    default:    throw "Unknown enumerator: " + std::to_string(static_cast<int>(border)) + " in checkRangeBorder function.";
//    }
//}


















//template<class __T, class __Step>
//ONF::IdManager<__T, __Step>::
//IdManager(__T startId,
//          __Step step,
//          IdIssuingMethod idIssuingMethod,
//          bool isHardStep)
//    : freeIds_(idIssuingMethod),
//      reservedIds_(),
//      maxId_(startId),
//      minId_(startId),
//      startId_(startId),
//      isHardStep_(isHardStep),
//      idIssuingMethod_(idIssuingMethod)
//{
//    static_assert(is_types_combination_prohibited<__T, __Step> == false);

//    step_ = (step == 0 ? 1 : step);
//    isCrossingUpperBorder_ = checkRangeBorder(startId, UpperBorder);
//    isCrossingLowerBorder_ = checkRangeBorder(startId, LowerBorder);
//}

//template<class __T, class __Step>
//ONF::IdManager<__T, __Step>::
//IdManager(const IdManager<__T, __Step>& other)
//    : freeIds_(other.freeIds_),
//      reservedIds_(other.reservedIds_),
//      maxId_(other.maxId_),
//      minId_(other.minId_),
//      startId_(other.startId_),
//      isCrossingUpperBorder_(other.isCrossingUpperBorder_),
//      isCrossingLowerBorder_(other.isCrossingLowerBorder_),
//      step_(other.step_),
//      isHardStep_(other.isHardStep),
//      idIssuingMethod_(other.idIssuingMethod_) {}

//template<class __T, class __Step>
//ONF::IdManager<__T, __Step>::
//~IdManager() {}

//template<class __T, class __Step>
//int
//ONF::IdManager<__T, __Step>::
//getFreeId(__T& id)
//{
//    if (freeIds_.size()) {
//        freeIds_.getNextId(id);
//        return IDRF_SUCCESSFULLY;
//    }

//    if (maxId_ == startId_ && startId_ == minId_) {

//    }

//    if (step_ > 0) {
//        if (isCrossingUpperBorder_)
//            return IDRF_ID_OUT_RANGE;

//        id = maxId_;
//        maxId_ += static_cast<__T>(step_);
//        expandRange();
//        return IDRF_SUCCESSFULLY;
//    }

//    if (step_ < 0) {
//        if (isCrossingLowerBorder_)
//            return IDRF_ID_OUT_RANGE;

//        id = minId_;
//        minId_ += static_cast<__T>(step_);
//        expandRange();
//        return IDRF_SUCCESSFULLY;
//    }
//}

//template<class __T, class __Step>
//bool
//ONF::IdManager<__T, __Step>::
//isStandardId(__T id) const
//{
//    long double _An = static_cast<long double>(id);
//    long double _A1 = static_cast<long double>(startId_);
//    long double _d = static_cast<long double>(step_);

//    long double n = std::abs((_An - _A1 + _d) / _d);
//    return (n - static_cast<unsigned long long>(n) == static_cast<long double>(0.0));
//}

//template<class __T, class __Step>
//void
//ONF::IdManager<__T, __Step>::
//expandRange()
//{
//    isCrossingUpperBorder_ = checkRangeBorder(maxId_, UpperBorder);
//    isCrossingLowerBorder_ = checkRangeBorder(minId_, LowerBorder);

//    while (true) {
//        if (reservedIds_.find(maxId_)) {
//            reservedIds_.freeId(maxId_);
//            isCrossingUpperBorder_ = checkRangeBorder(maxId_, UpperBorder);
//            if (!isCrossingUpperBorder_) {
//                maxId_ += static_cast<__T>(onf_abs(step_));
//            }
//            continue;
//        }

//        if (reservedIds_.find(minId_)) {
//            reservedIds_.freeId(minId_);
//            isCrossingLowerBorder_ = checkRangeBorder(minId_, LowerBorder);
//            if (!isCrossingLowerBorder_) {
//                minId_ -= static_cast<__T>(onf_abs(step_));
//            }
//            continue;
//        }

//        isCrossingUpperBorder_ = checkRangeBorder(maxId_, UpperBorder);
//        isCrossingLowerBorder_ = checkRangeBorder(minId_, LowerBorder);

//        break;
//    }
//}

//template<class __T, class __Step>
//bool
//ONF::IdManager<__T, __Step>::
//checkRangeBorder(__T value, Borders border) const
//{
//    switch (border) {
//        case LowerBorder:    return (static_cast<long long>(value) - static_cast<long long>(onf_abs(step_)) < std::numeric_limits<__T>::min());
//        case UpperBorder:    return (static_cast<long long>(value) + static_cast<long long>(onf_abs(step_)) > std::numeric_limits<__T>::max());

//    default:    throw "Unknown enumerator: " + std::to_string(border) + " in checkRangeBorder function.";
//    }
//}

//template<class __T, class __Step>
//template<class __TF>
//inline __TF
//ONF::IdManager<__T, __Step>::
//onf_abs(__TF value) const
//{
//    return value < 0 ? -value : value;
//}

























//template<class __T, class __Step>
//__T
//ONF::IdManager<__T, __Step>::
//getFreeId()
//{




















//    if (std::is_unsigned<__T>::value)
//        return 1;
//    else
//        return 0;
//}










//template<class __T, class __Step>
//__T
//ONF::IdManager<__T, __Step>::
//getStartId() const
//{
//    return startId_;
//}

//template<class __T, class __Step>
//__T
//ONF::IdManager<__T, __Step>::
//getMaxId() const
//{
//    return maxId_;
//}

//template<class __T, class __Step>
//__T
//ONF::IdManager<__T, __Step>::
//getMinId() const
//{
//    return minId_;
//}

































//template<class __T>
//IdManager<__T>::
//IdManager()
//    : IdManager((__T)0, (__T)1, false) {}

//template<class __T>
//IdManager<__T>::
//IdManager(const IdManager<__T>& other)
//    : freeIds_(other.freeIds_),
//      reservedIds_(other.reservedIds_),
//      maxId_(other.maxId_),
//      minId_(other.minId_),
//      startId_(other.startId_),
//      step_(other.step_),
//      isHardStep_(other.isHardStep) {}

//template<class __T>
//IdManager<__T>::
//IdManager(__T startId, __T step, bool isHardStep)
//    : maxId_(startId),
//      minId_(startId),
//      startId_(startId),
//      isHardStep_(isHardStep)
//{
//    step_ = ((step == (__T)0) ? (__T)1 : step);
//}

//template<class __T>
//IdManager<__T>::
//~IdManager() {}



//template<class __T>
//__T
//IdManager<__T>::
//getFreeId()
//{
//    __T _freeId = (__T)0;

//    if (maxId_ < startId_) {
//        _freeId = maxId_;
//        maxId_ += std::abs(step_);

//        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//            if (*it == maxId_) {
//                reservedIds_.erase(it);
//                maxId_ += std::abs(step_);
//                it = reservedIds_.begin();
//                continue;
//            }

//            ++it;
//        }

//        return _freeId;
//    }
//    else if (minId_ > startId_) {
//        _freeId = minId_;
//        minId_ -= std::abs(step_);

//        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//            if (*it == minId_) {
//                reservedIds_.erase(it);
//                minId_ -= std::abs(step_);
//                it = reservedIds_.begin();
//                continue;
//            }

//            ++it;
//        }

//        return _freeId;
//    }


//    if (freeIds_.size() != 0) {
//        auto _it = freeIds_.begin();
//        _freeId = *_it;
//        freeIds_.erase(_it);

//        if (_freeId == maxId_) {
//            maxId_ += std::abs(step_);

//            for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//                if (*it == maxId_) {
//                    reservedIds_.erase(it);
//                    maxId_ += std::abs(step_);
//                    it = reservedIds_.begin();
//                    continue;
//                }

//                ++it;
//            }
//        }

//        if (_freeId == minId_) {
//            minId_ -= std::abs(step_);

//            for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//                if (*it == minId_) {
//                    reservedIds_.erase(it);
//                    minId_ -= std::abs(step_);
//                    it = reservedIds_.begin();
//                    continue;
//                }

//                ++it;
//            }
//        }


//        return _freeId;
//    }

//    if (maxId_ == startId_ && minId_ == startId_) {
//        maxId_ += std::abs(step_);
//        minId_ -= std::abs(step_);

//        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//            if (*it == maxId_) {
//                reservedIds_.erase(it);
//                maxId_ += std::abs(step_);
//                it = reservedIds_.begin();
//                continue;
//            }

//            if (*it == minId_) {
//                reservedIds_.erase(it);
//                minId_ -= std::abs(step_);
//                it = reservedIds_.begin();
//                continue;
//            }

//            ++it;
//        }

//        return startId_;
//    }

//    if (step_ < (__T)0) {
//        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//            if (*it == minId_) {
//                reservedIds_.erase(it);
//                minId_ += step_;
//                it = reservedIds_.begin();
//                continue;
//            }
//            ++it;
//        }

//        _freeId = minId_;
//        minId_ += step_;
//    }
//    else {
//        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//            if (*it == maxId_) {
//                reservedIds_.erase(it);
//                maxId_ += step_;
//                it = reservedIds_.begin();
//                continue;
//            }
//            ++it;
//        }

//        _freeId = maxId_;
//        maxId_ += step_;
//    }

//    for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//        if (*it == maxId_) {
//            reservedIds_.erase(it);
//            maxId_ += std::abs(step_);
//            it = reservedIds_.begin();
//            continue;
//        }

//        if (*it == minId_) {
//            reservedIds_.erase(it);
//            minId_ -= std::abs(step_);
//            it = reservedIds_.begin();
//            continue;
//        }

//        ++it;
//    }

//    return _freeId;
//}

//template<class __T>
//bool
//IdManager<__T>::
//reserveId(__T id, ReservationMethod reservationMethod)
//{
//    if (!isStandardId(id)) {
//        if (isHardStep_) {
//            return false;
//        }

//        for (size_t i = 0; i < reservedIds_.size(); ++i) {
//            if (reservedIds_[i] == id)
//                return false;
//        }

//        if (reservationMethod == Interpolate) {
//            if (id > maxId_) {
//                for (__T i = maxId_; i < id; i += std::abs(step_)) {

//                    bool _isBreak = false;

//                    for (size_t j = 0; j < freeIds_.size(); ++j) {
//                        if (freeIds_[j] == i) {
//                            maxId_ += std::abs(step_);
//                            _isBreak = true;
//                            break;
//                        }
//                    }

//                    if (_isBreak == true)
//                        continue;

//                    if (reservedIds_.size() != 0) {
//                        for (size_t j = 0; j < reservedIds_.size(); ++j) {
//                            if (reservedIds_[j] == i) {
//                                auto _it = reservedIds_.begin();
//                                std::advance(_it, j);
//                                reservedIds_.erase(_it);
//                                break;
//                            }

//                            if (reservedIds_.size() - 1 == j)
//                                freeIds_.push_back(i);
//                        }
//                    }
//                    else {
//                        freeIds_.push_back(i);
//                    }

//                    maxId_ += std::abs(step_);
//                }
//            }

//            if (id < minId_) {
//                for (__T i = minId_; i > id; i -= std::abs(step_)) {

//                    bool _isBreak = false;

//                    for (size_t j = 0; j < freeIds_.size(); ++j) {
//                        if (freeIds_[j] == i) {
//                            minId_ -= std::abs(step_);
//                            _isBreak = true;
//                            break;
//                        }
//                    }

//                    if (_isBreak == true)
//                        continue;

//                    if (reservedIds_.size() != 0) {
//                        for (size_t j = 0; j < reservedIds_.size(); ++j) {
//                            if (reservedIds_[j] == i) {
//                                auto _it = reservedIds_.begin();
//                                std::advance(_it, j);
//                                reservedIds_.erase(_it);
//                                break;
//                            }

//                            if (reservedIds_.size() - 1 == j)
//                                freeIds_.push_back(i);
//                        }
//                    }
//                    else {
//                        freeIds_.push_back(i);
//                    }

//                    minId_ -= std::abs(step_);
//                }
//            }
//        }

//        reservedIds_.push_back(id);
//        return true;
//    }

//    if (id == startId_) {
//        if (maxId_ == startId_ && minId_ == startId_) {
//            maxId_ += std::abs(step_);
//            minId_ -= std::abs(step_);

//            for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//                if (*it == maxId_) {
//                    reservedIds_.erase(it);
//                    maxId_ += std::abs(step_);
//                    it = reservedIds_.begin();
//                    continue;
//                }

//                if (*it == minId_) {
//                    reservedIds_.erase(it);
//                    minId_ -= std::abs(step_);
//                    it = reservedIds_.begin();
//                    continue;
//                }

//                ++it;
//            }

//            return true;
//        }
//    }

//    for (auto it = freeIds_.begin(); it != freeIds_.end(); ++it) {
//        if (*it == id) {
//            freeIds_.erase(it);

//            if (id == startId_) {
//                if (maxId_ == startId_)
//                    maxId_ += std::abs(step_);

//                if (minId_ == startId_)
//                    minId_ -= std::abs(step_);

//                for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//                    if (*it == maxId_) {
//                        reservedIds_.erase(it);
//                        maxId_ += std::abs(step_);
//                        it = reservedIds_.begin();
//                        continue;
//                    }

//                    if (*it == minId_) {
//                        reservedIds_.erase(it);
//                        minId_ -= std::abs(step_);
//                        it = reservedIds_.begin();
//                        continue;
//                    }

//                    ++it;
//                }
//            }

//            return true;
//        }
//    }

//    for (size_t i = 0; i < reservedIds_.size(); ++i) {
//        if (reservedIds_[i] == id)
//            return false;
//    }

//    if (id < maxId_ && id > minId_)
//        return false;

//    if (id == maxId_) {
//        maxId_ += std::abs(step_);

//        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//            if (*it == maxId_) {
//                reservedIds_.erase(it);
//                maxId_ += std::abs(step_);
//                it = reservedIds_.begin();
//                continue;
//            }

//            ++it;
//        }

//        return true;
//    }

//    if (id == minId_) {
//        minId_ -= std::abs(step_);

//        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
//            if (*it == minId_) {
//                reservedIds_.erase(it);
//                minId_ -= std::abs(step_);
//                it = reservedIds_.begin();
//                continue;
//            }

////            bool _isBreak = false;

////            for (size_t j = 0; j < freeIds_.size(); ++j) {
////                if (freeIds_[j] == i) {
////                    _isBreak = true;
////                    break;
////                }
////            }

////            if (_isBreak == true)
////                continue;

//            ++it;
//        }

//        return true;
//    }

//    if (reservationMethod == AutoSelect || reservationMethod == Interpolate) {
//        if (id > maxId_) {
//            for (__T i = maxId_; i < id; i += std::abs(step_)) {

//                bool _isBreak = false;

//                for (size_t j = 0; j < freeIds_.size(); ++j) {
//                    if (freeIds_[j] == i) {
//                        _isBreak = true;
//                        break;
//                    }
//                }

//                if (_isBreak == true)
//                    continue;

//                if (reservedIds_.size() != 0) {
//                    for (size_t j = 0; j < reservedIds_.size(); ++j) {
//                        if (reservedIds_[j] == i) {
//                            auto _it = reservedIds_.begin();
//                            std::advance(_it, j);
//                            reservedIds_.erase(_it);
//                            break;
//                        }

//                        if (reservedIds_.size() - 1 == j)
//                            freeIds_.push_back(i);
//                    }
//                }
//                else {
//                    freeIds_.push_back(i);
//                }
//            }

//            maxId_ = id + std::abs(step_);
//            return true;
//        }

//        if (id < minId_) {
//            for (__T i = minId_; i > id; i -= std::abs(step_)) {

//                bool _isBreak = false;

//                for (size_t j = 0; j < freeIds_.size(); ++j) {
//                    if (freeIds_[j] == i) {
//                        _isBreak = true;
//                        break;
//                    }
//                }

//                if (_isBreak == true)
//                    continue;

//                if (reservedIds_.size() != 0) {
//                    for (size_t j = 0; j < reservedIds_.size(); ++j) {
//                        if (reservedIds_[j] == i) {
//                            auto _it = reservedIds_.begin();
//                            std::advance(_it, j);
//                            reservedIds_.erase(_it);
//                            break;
//                        }

//                        if (reservedIds_.size() - 1 == j)
//                            freeIds_.push_back(i);
//                    }
//                }
//                else {
//                    freeIds_.push_back(i);
//                }
//            }

//            minId_ = id - std::abs(step_);
//            return true;
//        }
//    }

//    reservedIds_.push_back(id);
//    return true;
//}

//template<class __T>
//void
//IdManager<__T>::
//freeId(__T id)
//{
//    if (!isStandardId(id)) {
//        if (isHardStep_) {
//            return;
//        }

//        for (auto it = reservedIds_.begin(); it != reservedIds_.end(); ++it) {
//            if (*it == id) {
//                reservedIds_.erase(it);
//                return;
//            }
//        }

//        return;
//    }

//    for (auto it = reservedIds_.begin(); it != reservedIds_.end(); ++it) {
//        if (*it == id) {
//            reservedIds_.erase(it);
//            return;
//        }
//    }

//    if (id >= maxId_ || id <= minId_)
//        return;

//    for (size_t i = 0; i < freeIds_.size(); ++i) {
//        if (freeIds_[i] == id)
//            return;
//    }

//    if (maxId_ - std::abs(step_) == id) {
//        maxId_ -= std::abs(step_);
//        return;
//    }

//    if (minId_ + std::abs(step_) == id) {
//        minId_ += std::abs(step_);
//        return;
//    }

//    freeIds_.push_back(id);
//}

//template<class __T>
//void
//IdManager<__T>::
//freeAll()
//{
//    freeIds_.clear();
//    reservedIds_.clear();
//    maxId_ = startId_;
//    minId_ = startId_;
//}

//template<class __T>
//bool
//IdManager<__T>::
//findId(__T id) const
//{
//    if (!isStandardId(id)) {
//        if (isHardStep_) {
//            return false;
//        }

//        for (size_t i = 0; i < reservedIds_.size(); ++i) {
//            if (reservedIds_[i] == id)
//                return true;
//        }

//        return false;
//    }

//    for (size_t i = 0; i < reservedIds_.size(); ++i) {
//        if (reservedIds_[i] == id)
//            return true;
//    }

//    if (id >= maxId_ || id <= minId_)
//        return false;

//    for (size_t i = 0; i < freeIds_.size(); ++i) {
//        if (freeIds_[i] == id)
//            return false;
//    }

//    return true;
//}

//template<class __T>
//__T
//IdManager<__T>::
//getStartId() const
//{
//    return startId_;
//}

//template<class __T>
//__T
//IdManager<__T>::
//getStep() const
//{
//    return step_;
//}

//template<class __T>
//__T
//IdManager<__T>::
//getMaxId() const
//{
//    return maxId_;
//}

//template<class __T>
//__T
//IdManager<__T>::
//getMinId() const
//{
//    return minId_;
//}

//template<class __T>
//bool
//IdManager<__T>::
//isHardStep() const
//{
//    return isHardStep_;
//}

//template<class __T>
//bool
//IdManager<__T>::
//isStandardId(__T id) const
//{
//    float n = std::abs((float)(id - startId_ + step_) / (float)step_);
//    return (float)n - (size_t)n == (float)0.0;
//}

//template<class __T>
//IdManager<__T>&
//IdManager<__T>::
//operator=(const IdManager<__T>& other)
//{
//    freeIds_ = other.freeIds_;
//    reservedIds_ = other.reservedIds_;
//    maxId_ = other.maxId_;
//    minId_ = other.minId_;
//    startId_ = other.startId_;
//    step_ = other.step_;
//    isHardStep_ = other.isHardStep_;

//    return *this;
//}
