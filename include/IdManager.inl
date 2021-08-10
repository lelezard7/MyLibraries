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
      step_            (step == 0 ? 1 : onf_abs(step)) {}

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

























template<class T, class T_Step>
ONF::RangeIdManager<T, T_Step>::
RangeIdManager(T start, T_Step step)
    : freeIds_        (IdIssuingMethod::Dynamic),
      idRange_        (start, onf_abs(step)),
      step_           (step == 0 ? 1 : step),
      size_           (0),
      isHardStep_     (true),
      idIssuingMethod_(IdIssuingMethod::Dynamic)
{
    static_assert(is_types_combination_prohibited<T, T_Step> == false);
}

template<class T, class T_Step>
ONF::RangeIdManager<T, T_Step>::
RangeIdManager(RangeIdManager<T, T_Step>&& other)
    : freeIds_        (std::move(other.freeIds_)),
      reservedIds_    (std::move(other.reservedIds_)),
      idRange_        (std::move(other.idRange_)),
      step_           (std::move(other.step_)),
      size_           (std::move(other.size_)),
      isHardStep_     (std::move(other.isHardStep_)),
      idIssuingMethod_(std::move(other.idIssuingMethod_))
{
    other.freeIds_.clear();
    other.reservedIds_.clear();
    other.idRange_.reset();
    other.size_ = 0;
    other.isHardStep_ = true;
    other.idIssuingMethod_ = IdIssuingMethod::Dynamic;
}

template<class T, class T_Step>
ONF::RangeIdManager<T, T_Step>::
~RangeIdManager() {}

template<class T, class T_Step>
std::optional<T>
ONF::RangeIdManager<T, T_Step>::
getFreeId()
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            !idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
            return onBothBorder();
        }

        if (idRange_.getBorderValue(BorderRange::LowerBorder) > idRange_.getStart()) {
            auto result = idRange_.moveBorder(BorderRange::LowerBorder, 1);

            if (!(result.flags & IDRF_ID_OUT_RANGE)) {
                ++size_;
                expandRange(BorderRange::LowerBorder);
                return result.value;
            }
        }

        if (idRange_.getBorderValue(BorderRange::UpperBorder) < idRange_.getStart()) {
            auto result = idRange_.moveBorder(BorderRange::UpperBorder, 1);

            if (!(result.flags & IDRF_ID_OUT_RANGE)) {
                ++size_;
                expandRange(BorderRange::UpperBorder);
                return result.value;
            }
        }

        if (freeIds_.size()) {
            ++size_;
            return *freeIds_.getNext();
        }

        return getNextId();
    }


    if (idIssuingMethod_ == IdIssuingMethod::Ascending) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            !idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
            return onBothBorder();
        }

        if (!idRange_.getBorderState(BorderRange::LowerBorder)) {
            idRange_.setBorderState(BorderRange::LowerBorder, true);

            T id = idRange_.getBorderValue(BorderRange::LowerBorder);
            ++size_;
            return id;
        }

        if (freeIds_.size()) {
            ++size_;
            return *freeIds_.getNext();
        }

        if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
            idRange_.setBorderState(BorderRange::UpperBorder, true);

            T id = idRange_.getBorderValue(BorderRange::UpperBorder);
            ++size_;
            return id;
        }

        return getNextId();
    }


    if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
        !idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
        return onBothBorder();
    }

    if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
        idRange_.setBorderState(BorderRange::UpperBorder, true);

        T id = idRange_.getBorderValue(BorderRange::UpperBorder);
        ++size_;
        return id;
    }

    if (freeIds_.size()) {
        ++size_;
        return *freeIds_.getNext();
    }

    if (!idRange_.getBorderState(BorderRange::LowerBorder)) {
        idRange_.setBorderState(BorderRange::LowerBorder, true);

        T id = idRange_.getBorderValue(BorderRange::LowerBorder);
        ++size_;
        return id;
    }

    return getNextId();
}

template<class T, class T_Step>
std::optional<T>
ONF::RangeIdManager<T, T_Step>::
getNextId()
{
    if (step_ > 0) {
        auto result = idRange_.moveBorder(BorderRange::UpperBorder, 1);

        if (result.flags & IDRF_ID_OUT_RANGE)
            return std::nullopt;

        ++size_;
        expandRange(BorderRange::UpperBorder);
        return result.value;
    }

    if (step_ < 0) {
        auto result = idRange_.moveBorder(BorderRange::LowerBorder, 1);

        if (result.flags & IDRF_ID_OUT_RANGE)
            return std::nullopt;

        ++size_;
        expandRange(BorderRange::LowerBorder);
        return result.value;
    }

    throw std::runtime_error("---------");
}

template<class T, class T_Step>
T
ONF::RangeIdManager<T, T_Step>::
onBothBorder()
{
    idRange_.setBorderState(BorderRange::UpperBorder, true);
    idRange_.setBorderState(BorderRange::LowerBorder, true);

    T id = idRange_.getBorderValue(BorderRange::UpperBorder);
    ++size_;

    return id;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step>::
jumpOver(T id, BorderRange borderRange)
{
    if (!isStandardId(id))
        return false;

    if (borderRange == BorderRange::UpperBorder) {
        T upperBorderBackup = idRange_.getBorderValue(BorderRange::UpperBorder);

        if (!idRange_.setBorderValue(BorderRange::UpperBorder, id))
            return false;

        if (!idRange_.setBorderValue(BorderRange::LowerBorder, id)) {
            if (!idRange_.setBorderValue(BorderRange::UpperBorder, upperBorderBackup))
                throw std::runtime_error("---------");

            return false;
        }

        return true;
    }

    T lowerBorderBackup = idRange_.getBorderValue(BorderRange::LowerBorder);

    if (!idRange_.setBorderValue(BorderRange::LowerBorder, id))
        return false;

    if (!idRange_.setBorderValue(BorderRange::UpperBorder, id)) {
        if (!idRange_.setBorderValue(BorderRange::LowerBorder, lowerBorderBackup))
            throw std::runtime_error("---------");

        return false;
    }

    return true;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step>::
reserveId(T id, ReservationMethod reservationMethod)
{
    if (id > idRange_.getBorderLimit(BorderRange::UpperBorder) || id < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return false;

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (!isStandardId(id)) {
            if (isHardStep_)
                return false;

            if (reservationMethod == ReservationMethod::Interpolate)
                return interpolateIds(id);

            if (reservationMethod == ReservationMethod::ReserveRange)
                return reserveIds(id);  //TODO: runtime_error -> "error message" + __LINE__

            if (reservedIds_.find(id))
                return false;

            reservedIds_.add(id);
            ++size_;
            return true;
        }

        if (reservationMethod == ReservationMethod::Interpolate)
            return interpolateIds(id);

        if (reservationMethod == ReservationMethod::ReserveRange)
            return reserveIds(id);

        if (id == idRange_.getBorderValue(BorderRange::UpperBorder) && id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (idRange_.getBorderState(BorderRange::UpperBorder) && idRange_.getBorderState(BorderRange::LowerBorder))
                return false;

            onBothBorder();
            return true;
        }

        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            !idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
            auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

            if (id == idInfo.value && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
                if (!jumpOver(idInfo.value, BorderRange::UpperBorder))
                    return false;

                onBothBorder();

                expandRange(BorderRange::UpperBorder);
                expandRange(BorderRange::LowerBorder);

                return true;
            }

            idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

            if (id == idInfo.value && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
                if (!jumpOver(idInfo.value, BorderRange::LowerBorder))
                    return false;

                onBothBorder();

                expandRange(BorderRange::UpperBorder);
                expandRange(BorderRange::LowerBorder);

                return true;
            }
        }

        if (id == idRange_.getBorderValue(BorderRange::UpperBorder) || id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return false;

        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (!freeIds_.find(id))
                return false;

            freeIds_.erase(id);
            ++size_;
            return true;
        }

        if (reservedIds_.find(id))
            return false;

        auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

        if (idInfo.value == id && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
            idRange_.moveBorder(BorderRange::UpperBorder, 1);
            ++size_;

            expandRange(BorderRange::UpperBorder);
            return true;
        }

        idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

        if (idInfo.value == id && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
            idRange_.moveBorder(BorderRange::LowerBorder, 1);
            ++size_;

            expandRange(BorderRange::LowerBorder);
            return true;
        }

        reservedIds_.add(id);
        ++size_;
        return true;
    }

    // -------------------------------------

    if (!isStandardId(id)) {
        if (isHardStep_)
            return false;

        if (reservationMethod == ReservationMethod::Interpolate)
            return interpolateIds(id);

        if (reservationMethod == ReservationMethod::ReserveRange)
            return reserveIds(id);

        if (reservedIds_.find(id))
            return false;

        reservedIds_.add(id);
        ++size_;
        return true;
    }

    if (reservationMethod == ReservationMethod::Interpolate)
        return interpolateIds(id);

    if (reservationMethod == ReservationMethod::ReserveRange)
        return reserveIds(id);

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder) && id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (idRange_.getBorderState(BorderRange::UpperBorder) && idRange_.getBorderState(BorderRange::LowerBorder))
            return false;

        onBothBorder();
        return true;
    }

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder)) {
        if (idRange_.getBorderState(BorderRange::UpperBorder))
            return false;

        idRange_.setBorderState(BorderRange::UpperBorder, true);
        ++size_;
        return true;
    }

    if (id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (idRange_.getBorderState(BorderRange::LowerBorder))
            return false;

        idRange_.setBorderState(BorderRange::LowerBorder, true);
        ++size_;
        return true;
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (!freeIds_.find(id))
            return false;

        freeIds_.erase(id);
        ++size_;
        return true;
    }

    if (reservedIds_.find(id))
        return false;

    auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

    if (id == idInfo.value && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
        if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
            idRange_.setBorderState(BorderRange::UpperBorder, true);

            if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
                freeIds_.add(idRange_.getBorderValue(BorderRange::UpperBorder));
        }

        idRange_.moveBorder(BorderRange::UpperBorder, 1);
        ++size_;

        expandRange(BorderRange::UpperBorder);
        return true;
    }

    idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

    if (id == idInfo.value && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
        if (!idRange_.getBorderState(BorderRange::LowerBorder)) {
            idRange_.setBorderState(BorderRange::LowerBorder, true);

            if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
                freeIds_.add(idRange_.getBorderValue(BorderRange::LowerBorder));
        }

        idRange_.moveBorder(BorderRange::LowerBorder, 1);
        ++size_;

        expandRange(BorderRange::LowerBorder);
        return true;
    }

    reservedIds_.add(id);
    ++size_;
    return true;
}


template<class T, class T_Step>
inline bool
ONF::RangeIdManager<T, T_Step>::
isStandardId(T id) const
{
    return ONF::isStandardId(static_cast<ldouble>(id), static_cast<ldouble>(idRange_.getStart()), static_cast<ldouble>(step_));
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step>::
setBorderLimit(BorderRange borderRange, T value)
{
    if (borderRange == BorderRange::UpperBorder) {
        if (value == idRange_.getBorderLimit(BorderRange::UpperBorder))
            return true;

        if (value > idRange_.getBorderLimit(BorderRange::UpperBorder))
            return idRange_.setBorderLimit(BorderRange::UpperBorder, value);

        if (value < idRange_.getBorderValue(BorderRange::UpperBorder))
            return false;

        std::vector<T> buffer;

        for (size_t i = 0; i < reservedIds_.size(); ++i) {
            T id = *reservedIds_.findByIndex(i);

            if (id > value) {
                reservedIds_.erase(id);
                buffer.push_back(id);
            }
        }

        if (!idRange_.setBorderLimit(BorderRange::UpperBorder, value)) {
            for (size_t i = 0; i < buffer.size(); ++i) {
                reservedIds_.add(buffer[i]);
            }

            return false;
        }

        size_ -= buffer.size();
        return true;
    }

    if (value == idRange_.getBorderLimit(BorderRange::LowerBorder))
        return true;

    if (value < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return idRange_.setBorderLimit(BorderRange::LowerBorder, value);

    if (value > idRange_.getBorderValue(BorderRange::LowerBorder))
        return false;

    std::vector<T> buffer;

    for (size_t i = 0; i < reservedIds_.size(); ++i) {
        T id = *reservedIds_.findByIndex(i);

        if (id < value) {
            reservedIds_.erase(id);
            buffer.push_back(id);
        }
    }

    if (!idRange_.setBorderLimit(BorderRange::LowerBorder, value)) {
        for (size_t i = 0; i < buffer.size(); ++i) {
            reservedIds_.add(buffer[i]);
        }

        return false;
    }

    size_ -= buffer.size();
    return true;
}

template<class T, class T_Step>
inline T
ONF::RangeIdManager<T, T_Step>::
getBorderLimit(BorderRange borderRange) const
{
    return idRange_.getBorderLimit(borderRange);
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step>::
freeId(T id)
{
    if (id > idRange_.getBorderLimit(BorderRange::UpperBorder) || id < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return false;

    if (!isStandardId(id)) {
        if (!reservedIds_.find(id))
            return false;

        reservedIds_.erase(id);
        --size_;
        return true;
    }

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (id == idRange_.getBorderValue(BorderRange::UpperBorder) &&
            id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (idRange_.getBorderState(BorderRange::UpperBorder) == false &&
                idRange_.getBorderState(BorderRange::LowerBorder) == false) {
                return false;
            }

            idRange_.setBorderState(BorderRange::UpperBorder, false);
            idRange_.setBorderState(BorderRange::LowerBorder, false);

            --size_;
            return true;
        }

        if (id == idRange_.getBorderValue(BorderRange::UpperBorder)) {
            auto idInfo = idRange_.moveBorder(BorderRange::UpperBorder, -1);

            if (idInfo.flags & IDRF_RANGE_ARE_BENT)
                return false;

            reduceRange(BorderRange::UpperBorder);
            --size_;
            return true;
        }

        if (id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
            auto idInfo = idRange_.moveBorder(BorderRange::LowerBorder, -1);

            if (idInfo.flags & IDRF_RANGE_ARE_BENT)
                return false;

            reduceRange(BorderRange::LowerBorder);
            --size_;
            return true;
        }

        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) &&
            id > idRange_.getBorderValue(BorderRange::LowerBorder)) {

            if (freeIds_.find(id))
                return false;

            freeIds_.add(id);
            --size_;
            return true;
        }

        if (!reservedIds_.find(id))
            return false;

        reservedIds_.erase(id);
        --size_;
        return true;
    }

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder) &&
        id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (idRange_.getBorderState(BorderRange::UpperBorder) == false &&
            idRange_.getBorderState(BorderRange::LowerBorder) == false) {
            return false;
        }

        if (idRange_.getBorderState(BorderRange::UpperBorder) !=
            idRange_.getBorderState(BorderRange::LowerBorder))
            throw std::runtime_error("---------------");

        idRange_.setBorderState(BorderRange::UpperBorder, false);
        idRange_.setBorderState(BorderRange::LowerBorder, false);

        --size_;
        return true;
    }

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder)) {
        if (!idRange_.getBorderState(BorderRange::UpperBorder))
            return false;

        idRange_.setBorderState(BorderRange::UpperBorder, false);
        --size_;

        return true;
    }

    if (id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (!idRange_.getBorderState(BorderRange::LowerBorder))
            return false;

        idRange_.setBorderState(BorderRange::LowerBorder, false);
        --size_;

        return true;
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) &&
        id > idRange_.getBorderValue(BorderRange::LowerBorder)) {

        if (freeIds_.find(id))
            return false;

        freeIds_.add(id);
        --size_;
        return true;
    }

    if (!reservedIds_.find(id))
        return false;

    reservedIds_.erase(id);
    --size_;
    return true;
}

template<class T, class T_Step>
inline void
ONF::RangeIdManager<T, T_Step>::
freeAll()
{
    freeIds_.clear();
    reservedIds_.clear();
    idRange_.reset();
    size_ = 0;
}

template<class T, class T_Step>
void
ONF::RangeIdManager<T, T_Step>::
setHardStep(bool value)
{
    if (value == isHardStep_)
        return;

    isHardStep_ = value;

    if (value == false)
        return;

    for (size_t i = 0; i < reservedIds_.size(); ++i) {
        T id = *reservedIds_.findByIndex(i);

        if (!isStandardId(id)) {
            reservedIds_.erase(id);
            --size_;
            --i;
        }
    }
}

template<class T, class T_Step>
inline bool
ONF::RangeIdManager<T, T_Step>::
isHardStep() const
{
    return isHardStep_;
}

template<class T, class T_Step>
void
ONF::RangeIdManager<T, T_Step>::
setIdIssuingMethod(IdIssuingMethod idIssuingMethod)
{
    if (idIssuingMethod == idIssuingMethod_)
        return;

    if ((idIssuingMethod_ == IdIssuingMethod::Ascending || idIssuingMethod_ == IdIssuingMethod::Descending) &&
        (idIssuingMethod == IdIssuingMethod::Ascending || idIssuingMethod == IdIssuingMethod::Descending)) {

        freeIds_.setIdIssuingMethod(idIssuingMethod);
        idIssuingMethod_ = idIssuingMethod;
        return;
    }

    freeIds_.setIdIssuingMethod(idIssuingMethod);
    idIssuingMethod_ = idIssuingMethod;

    if (idIssuingMethod == IdIssuingMethod::Dynamic) {
        if (normalizeRange(BorderRange::UpperBorder, IdIssuingMethod::Dynamic) == IDRF_RANGE_ARE_BENT ||
            normalizeRange(BorderRange::LowerBorder, IdIssuingMethod::Dynamic) == IDRF_RANGE_ARE_BENT) {
            idRange_.setBorderState(BorderRange::UpperBorder, false);
            idRange_.setBorderState(BorderRange::LowerBorder, false);
        }

        return;
    }

    normalizeRange(BorderRange::UpperBorder, idIssuingMethod);
}

template<class T, class T_Step>
int
ONF::RangeIdManager<T, T_Step>::
normalizeRange(BorderRange border, IdIssuingMethod idIssuingMethod)
{
    if (idIssuingMethod == IdIssuingMethod::Dynamic) {
        if (idRange_.getBorderState(border)) {
            return IDRF_SUCCESSFULLY;
        }

        idRange_.moveBorder(border, -1);
        idRange_.setBorderState(border, true);
        return reduceRange(border);
    }

    if (idRange_.getBorderValue(BorderRange::UpperBorder) < idRange_.getStart()) {
        while (true) {
            auto result = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

            if (result.flags & IDRF_ID_OUT_RANGE)
                return result.flags;

            if (result.value > idRange_.getStart())
                return result.flags;

            if (reservedIds_.find(result.value)) {
                reservedIds_.erase(result.value);
                idRange_.moveBorder(BorderRange::UpperBorder, 1);
                idRange_.setBorderState(BorderRange::UpperBorder, true);
            }
            else {
                idRange_.moveBorder(BorderRange::UpperBorder, 1);
                idRange_.setBorderState(BorderRange::UpperBorder, false);

                auto result2 = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

                if (result2.flags & IDRF_ID_OUT_RANGE)
                    return result2.flags;

                if (result2.value > idRange_.getStart())
                    return result2.flags;

                freeIds_.add(result.value);
            }
        }
    }

    if (idRange_.getBorderValue(BorderRange::LowerBorder) > idRange_.getStart()) {
        while (true) {
            auto result = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

            if (result.flags & IDRF_ID_OUT_RANGE)
                return result.flags;

            if (result.value < idRange_.getStart())
                return result.flags;

            if (reservedIds_.find(result.value)) {
                reservedIds_.erase(result.value);
                idRange_.moveBorder(BorderRange::LowerBorder, 1);
                idRange_.setBorderState(BorderRange::LowerBorder, true);
            }
            else {
                idRange_.moveBorder(BorderRange::LowerBorder, 1);
                idRange_.setBorderState(BorderRange::LowerBorder, false);

                auto result2 = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

                if (result2.flags & IDRF_ID_OUT_RANGE)
                    return result2.flags;

                if (result2.value < idRange_.getStart())
                    return result2.flags;

                freeIds_.add(result.value);
            }
        }
    }

    return IDRF_SUCCESSFULLY;
}

template<class T, class T_Step>
inline ONF::IdIssuingMethod
ONF::RangeIdManager<T, T_Step>::
getIdIssuingMethod() const
{
    return idIssuingMethod_;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step>::
findId(T id) const
{
    if (id > idRange_.getBorderLimit(BorderRange::UpperBorder) || id < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return false;

    if (!isStandardId(id)) {
        if (isHardStep_)
            return false;

        return reservedIds_.find(id);
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) &&
        id > idRange_.getBorderValue(BorderRange::LowerBorder))
        return !freeIds_.find(id);

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder))
        return idRange_.getBorderState(BorderRange::UpperBorder);

    if (id == idRange_.getBorderValue(BorderRange::LowerBorder))
        return idRange_.getBorderState(BorderRange::LowerBorder);

    return reservedIds_.find(id);
}

template<class T, class T_Step>
inline size_t
ONF::RangeIdManager<T, T_Step>::
size() const
{
    return size_;
}

template<class T, class T_Step>
inline T
ONF::RangeIdManager<T, T_Step>::
getStart() const
{
    return idRange_.getStart();
}

template<class T, class T_Step>
inline T_Step
ONF::RangeIdManager<T, T_Step>::
getStep() const
{
    return step_;
}

template<class T, class T_Step>
inline T
ONF::RangeIdManager<T, T_Step>::
getBorderValue(BorderRange borderRange) const
{
    return idRange_.getBorderValue(borderRange);
}

template<class T, class T_Step>
inline bool
ONF::RangeIdManager<T, T_Step>::
getBorderState(BorderRange borderRange) const
{
    return idRange_.getBorderState(borderRange);
}

template<class T, class T_Step>
ONF::RangeIdManager<T, T_Step>&
ONF::RangeIdManager<T, T_Step>::
operator=(RangeIdManager<T, T_Step>&& other)
{
    freeIds_         = std::move(other.freeIds_);
    reservedIds_     = std::move(other.reservedIds_);
    idRange_         = std::move(other.idRange_);
    step_            = std::move(other.step_);
    size_            = std::move(other.size_);
    isHardStep_      = std::move(other.isHardStep_);
    idIssuingMethod_ = std::move(other.idIssuingMethod_);

    other.freeIds_.clear();
    other.reservedIds_.clear();
    other.idRange_.reset();
    other.size_ = 0;
    other.isHardStep_ = true;
    other.idIssuingMethod_ = IdIssuingMethod::Dynamic;

    return *this;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step>::
reserveIds(T id)
{
    if (id > idRange_.getBorderLimit(BorderRange::UpperBorder) || id < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return 0;

    if (reservedIds_.find(id))
        return 0;

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (idRange_.getBorderState(BorderRange::UpperBorder) != idRange_.getBorderState(BorderRange::LowerBorder))
                throw std::runtime_error("---------");

            if(id == idRange_.getBorderValue(BorderRange::UpperBorder)) {
                if (idRange_.getBorderState(BorderRange::UpperBorder) == true && idRange_.getBorderState(BorderRange::LowerBorder) == true)
                    return 0;

                onBothBorder();
                return 1;
            }
        }

        if (id == idRange_.getBorderValue(BorderRange::UpperBorder) || id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return 0;

        if (isStandardId(id)) {
            if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
                if (freeIds_.find(id)) {
                    freeIds_.erase(id);
                    ++size_;
                    return 1;
                }

                return 0;
            }

            if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
                if (!idRange_.getBorderState(BorderRange::UpperBorder) || !idRange_.getBorderState(BorderRange::LowerBorder)) {
                    auto idInfo = idRange_.moveBorder(BorderRange::UpperBorder, 0);

                    if (reservedIds_.find(idInfo.value))
                        reservedIds_.erase(idInfo.value);
                    else
                        ++size_;
                }

                while (true) {
                    auto idInfo = idRange_.moveBorder(BorderRange::UpperBorder, 1);

                    if (reservedIds_.find(idInfo.value))
                        reservedIds_.erase(idInfo.value);
                    else
                        ++size_;

                    if (idInfo.value == id)
                        break;
                }

                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);

                expandRange(BorderRange::UpperBorder);
                expandRange(BorderRange::LowerBorder);

                return 1;
            }

            if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
                if (!idRange_.getBorderState(BorderRange::UpperBorder) || !idRange_.getBorderState(BorderRange::LowerBorder)) {
                    auto idInfo = idRange_.moveBorder(BorderRange::LowerBorder, 0);

                    if (reservedIds_.find(idInfo.value))
                        reservedIds_.erase(idInfo.value);
                    else
                        ++size_;
                }

                while (true) {
                    auto idInfo = idRange_.moveBorder(BorderRange::LowerBorder, 1);

                    if (reservedIds_.find(idInfo.value))
                        reservedIds_.erase(idInfo.value);
                    else
                        ++size_;

                    if (idInfo.value == id)
                        break;
                }

                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);

                expandRange(BorderRange::UpperBorder);
                expandRange(BorderRange::LowerBorder);

                return 1;
            }

            throw std::runtime_error("---------");
        }


        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (!reservedIds_.find(id)) {
                reservedIds_.add(id);
                ++size_;
                return 1;
            }

            return 0;
        }

        if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
            while (true) {
                auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

                if (idInfo.value > id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                    break;

                if (reservedIds_.find(idInfo.value))
                    reservedIds_.erase(idInfo.value);
                else
                    ++size_;

                idRange_.moveBorder(BorderRange::UpperBorder, 1);
            }

            onBothBorder();

            expandRange(BorderRange::UpperBorder);
            expandRange(BorderRange::LowerBorder);

            reservedIds_.add(id);
            return 1;
        }

        if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
            while (true) {
                auto idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

                if (idInfo.value < id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                    break;

                if (reservedIds_.find(idInfo.value))
                    reservedIds_.erase(idInfo.value);
                else
                    ++size_;

                idRange_.moveBorder(BorderRange::LowerBorder, 1);
            }

            //      ub---->\
            // .....lb.....@...
            //ub и lb могут быть на старте и при перемещении одной из границ обе активируются,
            //а потому expandRange делаем с обоими границами.
            onBothBorder();

            expandRange(BorderRange::UpperBorder);
            expandRange(BorderRange::LowerBorder);

            reservedIds_.add(id);
            return 1;
        }

        throw std::runtime_error("---------");
    }

    // ----------------------------------

    if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
        id == idRange_.getBorderValue(BorderRange::UpperBorder)) {

        if (idRange_.getBorderState(BorderRange::UpperBorder) == true && idRange_.getBorderState(BorderRange::LowerBorder) == true)
            return 0;

        if (idRange_.getBorderState(BorderRange::UpperBorder) != idRange_.getBorderState(BorderRange::LowerBorder))
            throw std::runtime_error("---------");

        onBothBorder();
        return 1;
    }

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder)) {
        if (idRange_.getBorderState(BorderRange::UpperBorder))
            return 0;

        idRange_.setBorderState(BorderRange::UpperBorder, true);
        ++size_;
        return 1;
    }

    if (id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (idRange_.getBorderState(BorderRange::LowerBorder))
            return 0;

        idRange_.setBorderState(BorderRange::LowerBorder, true);
        ++size_;
        return 1;
    }

    if (isStandardId(id)) {
        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (freeIds_.find(id)) {
                freeIds_.erase(id);
                ++size_;
                return 1;
            }

            return 0;
        }

        if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
            if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder)) {
                if (!idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
                    idRange_.setBorderState(BorderRange::UpperBorder, true);
                    idRange_.setBorderState(BorderRange::LowerBorder, true);
                    ++size_;
                }
            }
            else {
                if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
                    idRange_.setBorderState(BorderRange::UpperBorder, true);
                    ++size_;
                }
            }

            while (true) {
                auto idInfo = idRange_.moveBorder(BorderRange::UpperBorder, 1);

                if (reservedIds_.find(idInfo.value))
                    reservedIds_.erase(idInfo.value);
                else
                    ++size_;

                if (idInfo.value == id)
                    break;
            }

            expandRange(BorderRange::UpperBorder);
            return 1;
        }

        if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder)) {
                if (!idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
                    idRange_.setBorderState(BorderRange::UpperBorder, true);
                    idRange_.setBorderState(BorderRange::LowerBorder, true);
                    ++size_;
                }
            }
            else {
                if (!idRange_.getBorderState(BorderRange::LowerBorder)) {
                    idRange_.setBorderState(BorderRange::LowerBorder, true);
                    ++size_;
                }
            }

            while (true) {
                auto idInfo = idRange_.moveBorder(BorderRange::LowerBorder, 1);

                if (reservedIds_.find(idInfo.value))
                    reservedIds_.erase(idInfo.value);
                else
                    ++size_;

                if (idInfo.value == id)
                    break;
            }

            expandRange(BorderRange::LowerBorder);
            return 1;
        }

        throw std::runtime_error("---------");
    }


    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (!reservedIds_.find(id)) {
            reservedIds_.add(id);
            ++size_;
            return 1;
        }

        return 0;
    }

    if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (!idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);
                ++size_;
            }
        }
        else {
            if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
                idRange_.setBorderState(BorderRange::UpperBorder, true);
                ++size_;
            }
        }

        while (true) {
            auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

            if (idInfo.value > id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                break;

            if (reservedIds_.find(idInfo.value))
                reservedIds_.erase(idInfo.value);
            else
                ++size_;

            idRange_.moveBorder(BorderRange::UpperBorder, 1);
        }

        expandRange(BorderRange::UpperBorder);

        reservedIds_.add(id);
        size_++;
        return 1;
    }

    if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (!idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);
                ++size_;
            }
        }
        else {
            if (!idRange_.getBorderState(BorderRange::LowerBorder)) {
                idRange_.setBorderState(BorderRange::LowerBorder, true);
                ++size_;
            }
        }

        while (true) {
            auto idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

            if (idInfo.value < id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                break;

            if (reservedIds_.find(idInfo.value))
                reservedIds_.erase(idInfo.value);
            else
                ++size_;

            idRange_.moveBorder(BorderRange::LowerBorder, 1);
        }

        expandRange(BorderRange::LowerBorder);

        reservedIds_.add(id);
        size_++;
        return 1;
    }

    throw std::runtime_error("---------");
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step>::
interpolateIds(T id)
{
    if (id > idRange_.getBorderLimit(BorderRange::UpperBorder) || id < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return 0;

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            idRange_.getBorderState(BorderRange::UpperBorder) == false &&
            idRange_.getBorderState(BorderRange::LowerBorder) == false) {

            if (isStandardId(id)) {
                T upperBorderValue = idRange_.getBorderValue(BorderRange::UpperBorder);
                T lowerBorderValue = idRange_.getBorderValue(BorderRange::LowerBorder);

                if (id > upperBorderValue) {
                    if (!jumpOver(id, BorderRange::UpperBorder))
                        return 0;

                    idRange_.setBorderState(BorderRange::UpperBorder, true);
                    idRange_.setBorderState(BorderRange::LowerBorder, true);

                    expandRange(BorderRange::UpperBorder);
                    expandRange(BorderRange::LowerBorder);

                    if (!reservedIds_.find(id))
                        ++size_;
                    else
                        reservedIds_.erase(id);

                    return 1;
                }

                if (id < lowerBorderValue) {
                    if (!jumpOver(id, BorderRange::LowerBorder))
                        return 0;

                    idRange_.setBorderState(BorderRange::UpperBorder, true);
                    idRange_.setBorderState(BorderRange::LowerBorder, true);

                    expandRange(BorderRange::UpperBorder);
                    expandRange(BorderRange::LowerBorder);

                    if (!reservedIds_.find(id))
                        ++size_;
                    else
                        reservedIds_.erase(id);

                    return 1;
                }

                if (id == idRange_.getBorderValue(BorderRange::UpperBorder)) {  // UpperBorder == LowerBorder
                    onBothBorder();
                    return 1;
                }

                return 0;
            }

            if (reservedIds_.find(id))
                return 0;

            T upperBorderValue = idRange_.getBorderValue(BorderRange::UpperBorder);
            T lowerBorderValue = idRange_.getBorderValue(BorderRange::LowerBorder);

            if (id > upperBorderValue) {
                T standardId = findNearestStandardId(id);

                if (standardId == idRange_.getBorderValue(BorderRange::UpperBorder)) {  // UpperBorder == LowerBorder
                    onBothBorder();
                    reservedIds_.add(id);
                    ++size_;
                    return 1;
                }

                if (!jumpOver(standardId, BorderRange::UpperBorder))
                    return 0;

                onBothBorder();

                expandRange(BorderRange::UpperBorder);
                expandRange(BorderRange::LowerBorder);

                reservedIds_.add(id);

                if (!reservedIds_.find(standardId))
                    ++size_;
                else
                    reservedIds_.erase(standardId);

                return 1;
            }

            if (id < lowerBorderValue) {
                T standardId = findNearestStandardId(id);

                if (standardId == idRange_.getBorderValue(BorderRange::LowerBorder)) {  // UpperBorder == LowerBorder
                    onBothBorder();
                    reservedIds_.add(id);
                    ++size_;
                    return 1;
                }

                if (!jumpOver(standardId, BorderRange::LowerBorder))
                    return 0;

                onBothBorder();

                expandRange(BorderRange::UpperBorder);
                expandRange(BorderRange::LowerBorder);

                reservedIds_.add(id);

                if (!reservedIds_.find(standardId))
                    ++size_;
                else
                    reservedIds_.erase(standardId);

                return 1;
            }

            return 0;
        }

        if (reservedIds_.find(id))
            return 0;

        if (isStandardId(id)) {
            if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
                if (freeIds_.find(id)) {
                    freeIds_.erase(id);
                    ++size_;
                    return 1;
                }

                return 0;
            }

            if (id == idRange_.getBorderValue(BorderRange::UpperBorder) || id == idRange_.getBorderValue(BorderRange::LowerBorder))
                return 0;

            if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
                while (true) {
                    auto idInfo = idRange_.moveBorder(BorderRange::UpperBorder, 1);

                    if (idInfo.value == id)
                        break;

                    if (!reservedIds_.find(idInfo.value))
                        freeIds_.add(idInfo.value);
                    else
                        reservedIds_.erase(idInfo.value);
                }

                expandRange(BorderRange::UpperBorder);
                ++size_;
                return 1;
            }

            if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
                while (true) {
                    auto idInfo = idRange_.moveBorder(BorderRange::LowerBorder, 1);

                    if (idInfo.value == id)
                        break;

                    if (!reservedIds_.find(idInfo.value))
                        freeIds_.add(idInfo.value);
                    else
                        reservedIds_.erase(idInfo.value);
                }

                expandRange(BorderRange::LowerBorder);
                ++size_;
                return 1;
            }

            throw std::runtime_error("---------");
        }

        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (!reservedIds_.find(id)) {
                reservedIds_.add(id);
                ++size_;
                return 1;
            }

            return 0;
        }

        if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
            if (id < idRange_.getIdInfo(BorderRange::UpperBorder, 1).value &&
                !(idRange_.getIdInfo(BorderRange::UpperBorder, 1).flags & IDRF_ID_OUT_RANGE)) {
                reservedIds_.add(id);
                size_++;
                return 1;
            }

            while (true) {
                auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

                if (idInfo.value > id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                    break;

                auto idInfo2 = idRange_.getIdInfo(BorderRange::UpperBorder, 2);

                if (idInfo2.value < id && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
                    if (!reservedIds_.find(idInfo.value))
                        freeIds_.add(idInfo.value);
                    else
                        reservedIds_.erase(idInfo.value);

                    idRange_.moveBorder(BorderRange::UpperBorder, 1);
                    continue;
                }

                if (reservedIds_.find(idInfo.value))
                    reservedIds_.erase(idInfo.value);

                idRange_.moveBorder(BorderRange::UpperBorder, 1);
                break;
            }

            expandRange(BorderRange::UpperBorder);

            reservedIds_.add(id);
            size_ += 2;
            return 1;
        }

        if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (id > idRange_.getIdInfo(BorderRange::LowerBorder, 1).value &&
                !(idRange_.getIdInfo(BorderRange::LowerBorder, 1).flags & IDRF_ID_OUT_RANGE)) {
                reservedIds_.add(id);
                size_++;
                return 1;
            }

            while (true) {
                auto idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

                if (idInfo.value < id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                    break;

                auto idInfo2 = idRange_.getIdInfo(BorderRange::LowerBorder, 2);

                if (idInfo2.value > id && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
                    if (!reservedIds_.find(idInfo.value))
                        freeIds_.add(idInfo.value);
                    else
                        reservedIds_.erase(idInfo.value);

                    idRange_.moveBorder(BorderRange::LowerBorder, 1);
                    continue;
                }

                if (reservedIds_.find(idInfo.value))
                    reservedIds_.erase(idInfo.value);

                idRange_.moveBorder(BorderRange::LowerBorder, 1);
                break;
            }

            expandRange(BorderRange::LowerBorder);

            reservedIds_.add(id);
            size_ += 2;
            return 1;
        }

        throw std::runtime_error("---------");
    }

    // ----------------------------------

    if (reservedIds_.find(id))
        return 0;

    if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
        id == idRange_.getBorderValue(BorderRange::UpperBorder)) {

        if (idRange_.getBorderState(BorderRange::UpperBorder) == true && idRange_.getBorderState(BorderRange::LowerBorder) == true)
            return 0;

        if (idRange_.getBorderState(BorderRange::UpperBorder) != idRange_.getBorderState(BorderRange::LowerBorder))
            throw std::runtime_error("---------");

        onBothBorder();
        return 1;
    }

    if (isStandardId(id)) {
        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (freeIds_.find(id)) {
                freeIds_.erase(id);
                ++size_;
                return 1;
            }

            return 0;
        }

        if (id == idRange_.getBorderValue(BorderRange::UpperBorder)) {
            if (idRange_.getBorderState(BorderRange::UpperBorder))
                return 0;

            idRange_.setBorderState(BorderRange::UpperBorder, true);
            ++size_;
            return 1;
        }

        if (id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (idRange_.getBorderState(BorderRange::LowerBorder))
                return 0;

            idRange_.setBorderState(BorderRange::LowerBorder, true);
            ++size_;
            return 1;
        }

        if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
            if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
                idRange_.setBorderState(BorderRange::UpperBorder, true);

                if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
                    freeIds_.add(idRange_.getBorderValue(BorderRange::UpperBorder));
            }

            while (true) {
                auto idInfo = idRange_.moveBorder(BorderRange::UpperBorder, 1);

                if (idInfo.value == id)
                    break;

                if (!reservedIds_.find(idInfo.value))
                    freeIds_.add(idInfo.value);
                else
                    reservedIds_.erase(idInfo.value);
            }

            expandRange(BorderRange::UpperBorder);
            ++size_;
            return 1;
        }

        if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (!idRange_.getBorderState(BorderRange::LowerBorder)) {
                idRange_.setBorderState(BorderRange::LowerBorder, true);

                if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
                    freeIds_.add(idRange_.getBorderValue(BorderRange::LowerBorder));
            }

            while (true) {
                auto idInfo = idRange_.moveBorder(BorderRange::LowerBorder, 1);

                if (idInfo.value == id)
                    break;

                if (!reservedIds_.find(idInfo.value))
                    freeIds_.add(idInfo.value);
                else
                    reservedIds_.erase(idInfo.value);
            }

            expandRange(BorderRange::LowerBorder);
            ++size_;
            return 1;
        }

        throw std::runtime_error("---------");
    }


    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (!reservedIds_.find(id)) {
            reservedIds_.add(id);
            ++size_;
            return 1;
        }

        return 0;
    }

    if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
        if ( (id < idRange_.getIdInfo(BorderRange::UpperBorder, 1).value) &&
            !(idRange_.getIdInfo(BorderRange::UpperBorder, 1).flags & IDRF_ID_OUT_RANGE)) {

            reservedIds_.add(id);
            ++size_;
            return 1;
        }

        if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
            if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
                freeIds_.add(idRange_.getBorderValue(BorderRange::UpperBorder));
        }

        idRange_.setBorderState(BorderRange::UpperBorder, false);

        while (true) {
            auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, 1);
            auto idInfo2 = idRange_.getIdInfo(BorderRange::UpperBorder, 2);

            if (idInfo2.value < id && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
                if (!reservedIds_.find(idInfo.value))
                    freeIds_.add(idInfo.value);
                else
                    reservedIds_.erase(idInfo.value);

                idRange_.moveBorder(BorderRange::UpperBorder, 1);
                continue;
            }

            if (reservedIds_.find(idInfo.value)) {
                reservedIds_.erase(idInfo.value);
                idRange_.setBorderState(BorderRange::UpperBorder, true);
            }

            idRange_.moveBorder(BorderRange::UpperBorder, 1);
            break;
        }

        expandRange(BorderRange::UpperBorder);

        reservedIds_.add(id);
        ++size_;
        return 1;
    }

    if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if ( (id > idRange_.getIdInfo(BorderRange::LowerBorder, 1).value) &&
            !(idRange_.getIdInfo(BorderRange::LowerBorder, 1).flags & IDRF_ID_OUT_RANGE)) {

            reservedIds_.add(id);
            ++size_;
            return 1;
        }

        if (!idRange_.getBorderState(BorderRange::LowerBorder)) {
            if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
                freeIds_.add(idRange_.getBorderValue(BorderRange::LowerBorder));
        }

        idRange_.setBorderState(BorderRange::LowerBorder, false);

        while (true) {
            auto idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, 1);
            auto idInfo2 = idRange_.getIdInfo(BorderRange::LowerBorder, 2);

            if (idInfo2.value > id && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
                if (!reservedIds_.find(idInfo.value))
                    freeIds_.add(idInfo.value);
                else
                    reservedIds_.erase(idInfo.value);

                idRange_.moveBorder(BorderRange::LowerBorder, 1);
                continue;
            }

            if (reservedIds_.find(idInfo.value)) {
                reservedIds_.erase(idInfo.value);
                idRange_.setBorderState(BorderRange::LowerBorder, true);
            }

            idRange_.moveBorder(BorderRange::LowerBorder, 1);
            break;
        }

        expandRange(BorderRange::LowerBorder);

        reservedIds_.add(id);
        ++size_;
        return 1;
    }

    throw std::runtime_error("---------");
}

template<class T, class T_Step>
T
ONF::RangeIdManager<T, T_Step>::
findNearestStandardId(T id) const
{
    if (isStandardId(id))
        return id;

    //Если вне диапазона.
    if (id > idRange_.getBorderValue(BorderRange::UpperBorder) || id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
            size_t i = 1;

            while (true) {
                auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, i);

                if (idInfo.flags == IDRF_ID_OUT_RANGE)
                    return idInfo.value;

                if (id < idInfo.value) {
                    idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, i - 1);
                    return idInfo.value;
                }

                ++i;
            }
        }

        if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
            size_t i = 1;

            while (true) {
                auto idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, i);

                if (idInfo.flags == IDRF_ID_OUT_RANGE)
                    return idInfo.value;

                if (id > idInfo.value) {
                    idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, i - 1);
                    return idInfo.value;
                }

                ++i;
            }
        }
    }

    //Если в диапазоне. На границе быть не может, иначе это будет стандартное число и оно вернется в начале функции.

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getStart()) {
        size_t i = 1;

        while (true) {
            auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, -i);

            if (idInfo.flags == IDRF_ID_OUT_RANGE)
                return idInfo.value;

            if (id > idInfo.value) {
                idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, -(i - 1));
                return idInfo.value;
            }

            ++i;
        }
    }

    if (id > idRange_.getBorderValue(BorderRange::LowerBorder) && id < idRange_.getStart()) {
        size_t i = 1;

        while (true) {
            auto idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, -i);

            if (idInfo.flags == IDRF_ID_OUT_RANGE)
                return idInfo.value;

            if (id < idInfo.value) {
                idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, -(i - 1));
                return idInfo.value;
            }

            ++i;
        }
    }

    throw std::runtime_error("---------");
}

template<class T, class T_Step>
unsigned
ONF::RangeIdManager<T, T_Step>::
expandRange(BorderRange border)
{
    while (true) {
        auto result = idRange_.getIdInfo(border, 1);

        if (result.flags & IDRF_ID_OUT_RANGE)
            return result.flags;

        if (reservedIds_.find(result.value)) {
            reservedIds_.erase(result.value);
            idRange_.moveBorder(border, 1);
            continue;
        }

        return result.flags;
    }
}

template<class T, class T_Step>
unsigned
ONF::RangeIdManager<T, T_Step>::
reduceRange(BorderRange border)
{
    if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
        idRange_.getBorderState(BorderRange::UpperBorder) == false &&
        idRange_.getBorderState(BorderRange::LowerBorder) == false) {
        return 0xFFFF;
    }

    longlong i = 0;

    while (true) {
        auto result = idRange_.getIdInfo(border, -i);

        if (result.flags & IDRF_RANGE_ARE_BENT)
            return result.flags;

        if (freeIds_.find(result.value)) {
            freeIds_.erase(result.value);
            ++i;
            continue;
        }

        idRange_.moveBorder(border, -i);
        return result.flags;
    }
}

template<class T, class T_Step>
inline size_t
ONF::RangeIdManager<T, T_Step>::
getFreeIdsSize() const
{
    return freeIds_.size();
}

template<class T, class T_Step>
inline size_t
ONF::RangeIdManager<T, T_Step>::
getReservedIdsSize() const
{
    return reservedIds_.size();
}
