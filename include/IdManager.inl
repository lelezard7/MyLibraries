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
      reservedIds_    (),
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
RangeIdManager(const RangeIdManager<T, T_Step>& other)
    : freeIds_        (other.freeIds_),
      reservedIds_    (other.reservedIds_),
      idRange_        (other.idRange_),
      step_           (other.step_),
      size_           (other.size_),
      isHardStep_     (other.isHardStep),
      idIssuingMethod_(other.idIssuingMethod_) {}

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
            idRange_.getBorderState(BorderRange::UpperBorder) == false &&
            idRange_.getBorderState(BorderRange::LowerBorder) == false) {

            idRange_.setBorderState(BorderRange::UpperBorder, true);
            idRange_.setBorderState(BorderRange::LowerBorder, true);

            T id = idRange_.getBorderValue(BorderRange::UpperBorder);
            size_++;

            expandRange(BorderRange::UpperBorder);
            expandRange(BorderRange::LowerBorder);

            return id;
        }

        if (idRange_.getBorderValue(BorderRange::LowerBorder) > idRange_.getStart()) {
            auto result = idRange_.moveBorder(BorderRange::LowerBorder, 1);

            if (!(result.flags & IDRF_ID_OUT_RANGE)) {
                expandRange(BorderRange::LowerBorder);
                size_++;
                return result.value;
            }
        }

        if (idRange_.getBorderValue(BorderRange::UpperBorder) < idRange_.getStart()) {
            auto result = idRange_.moveBorder(BorderRange::UpperBorder, 1);

            if (!(result.flags & IDRF_ID_OUT_RANGE)) {
                expandRange(BorderRange::UpperBorder);
                size_++;
                return result.value;
            }
        }

        if (freeIds_.size()) {
            size_++;
            return *freeIds_.getNext();
        }

        if (step_ > 0) {
            auto result = idRange_.moveBorder(BorderRange::UpperBorder, 1);

            if (!(result.flags & IDRF_ID_OUT_RANGE)) {
                expandRange(BorderRange::UpperBorder);
                size_++;
                return result.value;
            }
        }

        if (step_ < 0) {
            auto result = idRange_.moveBorder(BorderRange::LowerBorder, 1);

            if (!(result.flags & IDRF_ID_OUT_RANGE)) {
                expandRange(BorderRange::LowerBorder);
                size_++;
                return result.value;
            }
        }

        return std::nullopt;
    }

    // ---------------------------------

    if (idIssuingMethod_ == IdIssuingMethod::Ascending) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            idRange_.getBorderState(BorderRange::UpperBorder) == false &&
            idRange_.getBorderState(BorderRange::LowerBorder) == false) {

            idRange_.setBorderState(BorderRange::UpperBorder, true);
            idRange_.setBorderState(BorderRange::LowerBorder, true);

            T id = idRange_.getBorderValue(BorderRange::UpperBorder);
            size_++;

            expandRange(BorderRange::UpperBorder);
            expandRange(BorderRange::LowerBorder);

            return id;
        }

        if (idRange_.getBorderState(BorderRange::LowerBorder) == false) {
            idRange_.setBorderState(BorderRange::LowerBorder, true);

            T id = idRange_.getBorderValue(BorderRange::LowerBorder);
            expandRange(BorderRange::LowerBorder);

            size_++;
            return id;
        }

        if (freeIds_.size()) {
            size_++;
            return *freeIds_.getNext();
        }

        if (idRange_.getBorderState(BorderRange::UpperBorder) == false) {
            idRange_.setBorderState(BorderRange::UpperBorder, true);

            T id = idRange_.getBorderValue(BorderRange::UpperBorder);
            expandRange(BorderRange::UpperBorder);

            size_++;
            return id;
        }

        if (step_ > 0) {
            auto result = idRange_.moveBorder(BorderRange::UpperBorder, 1);

            if (!(result.flags & IDRF_ID_OUT_RANGE)) {
                expandRange(BorderRange::UpperBorder);
                size_++;
                return result.value;
            }
        }

        if (step_ < 0) {
            auto result = idRange_.moveBorder(BorderRange::LowerBorder, 1);

            if (!(result.flags & IDRF_ID_OUT_RANGE)) {
                expandRange(BorderRange::LowerBorder);
                size_++;
                return result.value;
            }
        }

        return std::nullopt;
    }

    // ---------------------------------

    if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
        idRange_.getBorderState(BorderRange::UpperBorder) == false &&
        idRange_.getBorderState(BorderRange::LowerBorder) == false) {

        idRange_.setBorderState(BorderRange::UpperBorder, true);
        idRange_.setBorderState(BorderRange::LowerBorder, true);

        T id = idRange_.getBorderValue(BorderRange::UpperBorder);
        size_++;

        expandRange(BorderRange::UpperBorder);
        expandRange(BorderRange::LowerBorder);

        return id;
    }

    if (idRange_.getBorderState(BorderRange::UpperBorder) == false) {
        idRange_.setBorderState(BorderRange::UpperBorder, true);

        T id = idRange_.getBorderValue(BorderRange::UpperBorder);
        expandRange(BorderRange::UpperBorder);

        size_++;
        return id;
    }

    if (freeIds_.size()) {
        size_++;
        return *freeIds_.getNext();
    }

    if (idRange_.getBorderState(BorderRange::LowerBorder) == false) {
        idRange_.setBorderState(BorderRange::LowerBorder, true);

        T id = idRange_.getBorderValue(BorderRange::LowerBorder);
        expandRange(BorderRange::LowerBorder);

        size_++;
        return id;
    }

    if (step_ > 0) {
        auto result = idRange_.moveBorder(BorderRange::UpperBorder, 1);

        if (!(result.flags & IDRF_ID_OUT_RANGE)) {
            expandRange(BorderRange::UpperBorder);
            size_++;
            return result.value;
        }
    }

    if (step_ < 0) {
        auto result = idRange_.moveBorder(BorderRange::LowerBorder, 1);

        if (!(result.flags & IDRF_ID_OUT_RANGE)) {
            expandRange(BorderRange::LowerBorder);
            size_++;
            return result.value;
        }
    }

    return std::nullopt;
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

            if (reservationMethod == ReservationMethod::Interpolate) {
                int errCode = interpolateIds(id);

                if (errCode == -1)
                    throw std::runtime_error("---------");

                return errCode;
            }

            if (reservationMethod == ReservationMethod::ReserveRange) {
                int errCode = reserveIds(id);

                if (errCode == -1)
                    throw std::runtime_error("---------");

                return errCode;
            }

            if (reservedIds_.find(id))
                return false;

            reservedIds_.add(id);
            size_++;
            return true;
        }


        if (reservationMethod == ReservationMethod::Interpolate) {
            int errCode = interpolateIds(id);

            if (errCode == -1)
                throw std::runtime_error("---------");

            return errCode;
        }

        if (reservationMethod == ReservationMethod::ReserveRange) {
            int errCode = reserveIds(id);

            if (errCode == -1)
                throw std::runtime_error("---------");

            return errCode;
        }

        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            idRange_.getBorderValue(BorderRange::UpperBorder) == id) {
            if (idRange_.getBorderState(BorderRange::UpperBorder) == true &&
                idRange_.getBorderState(BorderRange::LowerBorder) == true)
                return false;

            idRange_.setBorderState(BorderRange::UpperBorder, true);
            idRange_.setBorderState(BorderRange::LowerBorder, true);

            expandRange(BorderRange::UpperBorder);
            expandRange(BorderRange::LowerBorder);

            size_++;
            return true;
        }

        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            idRange_.getBorderState(BorderRange::UpperBorder) == false &&
            idRange_.getBorderState(BorderRange::LowerBorder) == false) {

            if (id == idRange_.getIdInfo(BorderRange::UpperBorder, 1).value &&
                !(idRange_.getIdInfo(BorderRange::UpperBorder, 1).flags & IDRF_ID_OUT_RANGE)) {

                if (!(idRange_.moveBorder(BorderRange::UpperBorder, 1).flags & IDRF_SUCCESSFULLY))
                    return 0;

                if (!(idRange_.moveBorder(BorderRange::LowerBorder, -1).flags & IDRF_SUCCESSFULLY)) {
                    if (!(idRange_.moveBorder(BorderRange::UpperBorder, -1).flags & IDRF_SUCCESSFULLY))
                        throw std::runtime_error("---------");

                    return 0;
                }

                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);

                expandRange(BorderRange::UpperBorder);
                expandRange(BorderRange::LowerBorder);

                size_++;
                return 1;
            }

            if (id == idRange_.getIdInfo(BorderRange::LowerBorder, 1).value &&
                !(idRange_.getIdInfo(BorderRange::LowerBorder, 1).flags & IDRF_ID_OUT_RANGE)) {

                if (!(idRange_.moveBorder(BorderRange::LowerBorder, 1).flags & IDRF_SUCCESSFULLY))
                    return 0;

                if (!(idRange_.moveBorder(BorderRange::UpperBorder, -1).flags & IDRF_SUCCESSFULLY)) {
                    if (!(idRange_.moveBorder(BorderRange::LowerBorder, -1).flags & IDRF_SUCCESSFULLY))
                        throw std::runtime_error("---------");

                    return 0;
                }

                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);

                expandRange(BorderRange::UpperBorder);
                expandRange(BorderRange::LowerBorder);

                size_++;
                return 1;
            }
        }

        if (id == idRange_.getBorderValue(BorderRange::UpperBorder) || id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return false;

        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (!freeIds_.find(id))
                return false;

            freeIds_.erase(id);
            size_++;
            return true;
        }

        if (reservedIds_.find(id))
            return false;

        if (id == idRange_.getIdInfo(BorderRange::UpperBorder, 1).value &&
            !(idRange_.getIdInfo(BorderRange::UpperBorder, 1).flags & IDRF_ID_OUT_RANGE)) {

            idRange_.moveBorder(BorderRange::UpperBorder, 1);
            expandRange(BorderRange::UpperBorder);
            size_++;
            return true;
        }

        if (id == idRange_.getIdInfo(BorderRange::LowerBorder, 1).value &&
            !(idRange_.getIdInfo(BorderRange::LowerBorder, 1).flags & IDRF_ID_OUT_RANGE)) {

            idRange_.moveBorder(BorderRange::LowerBorder, 1);
            expandRange(BorderRange::LowerBorder);
            size_++;
            return true;
        }

        reservedIds_.add(id);
        size_++;
        return true;
    }

    // -------------------------------------

    if (!isStandardId(id)) {
        if (isHardStep_)
            return false;

        if (reservationMethod == ReservationMethod::Interpolate) {
            int errCode = interpolateIds(id);

            if (errCode == -1)
                throw std::runtime_error("---------");

            return errCode;
        }

        if (reservationMethod == ReservationMethod::ReserveRange) {
            int errCode = reserveIds(id);

            if (errCode == -1)
                throw std::runtime_error("---------");

            return errCode;
        }

        if (reservedIds_.find(id))
            return false;

        reservedIds_.add(id);
        size_++;
        return true;
    }

    if (reservationMethod == ReservationMethod::Interpolate) {
        int errCode = interpolateIds(id);

        if (errCode == -1)
            throw std::runtime_error("---------");

        return errCode;
    }

    if (reservationMethod == ReservationMethod::ReserveRange) {
        int errCode = reserveIds(id);

        if (errCode == -1)
            throw std::runtime_error("---------");

        return errCode;
    }

    if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
        idRange_.getBorderValue(BorderRange::UpperBorder) == id) {
        if (idRange_.getBorderState(BorderRange::UpperBorder) == true &&
            idRange_.getBorderState(BorderRange::LowerBorder) == true)
            return false;

        idRange_.setBorderState(BorderRange::UpperBorder, true);
        idRange_.setBorderState(BorderRange::LowerBorder, true);

        expandRange(BorderRange::UpperBorder);
        expandRange(BorderRange::LowerBorder);

        size_++;
        return true;
    }

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder)) {
        if (idRange_.getBorderState(BorderRange::UpperBorder))
            return false;

        idRange_.setBorderState(BorderRange::UpperBorder, true);
        expandRange(BorderRange::UpperBorder);   // В этом нету смысла, так как следующее число всегда свободно.

        size_++;
        return true;
    }

    if (id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (idRange_.getBorderState(BorderRange::LowerBorder))
            return false;

        idRange_.setBorderState(BorderRange::LowerBorder, true);
        expandRange(BorderRange::LowerBorder);   // В этом нету смысла, так как следующее число всегда свободно.

        size_++;
        return true;
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (!freeIds_.find(id))
            return false;

        freeIds_.erase(id);
        size_++;
        return true;
    }

    if (reservedIds_.find(id))
        return false;

    if (id == idRange_.getIdInfo(BorderRange::UpperBorder, 1).value &&
        !(idRange_.getIdInfo(BorderRange::UpperBorder, 1).flags & IDRF_ID_OUT_RANGE)) {  // <-- TODO: Не корректно. В случае ошибки программа сочтет что
                                                                                         //id != idRange_.getIdInfo(BorderRange::UpperBorder, 1).value
                                                                                         //Хотя это может быть не так. Исправить везде.
        if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
            idRange_.setBorderState(BorderRange::UpperBorder, true);

            if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
                freeIds_.add(idRange_.getBorderValue(BorderRange::UpperBorder));
        }

        idRange_.moveBorder(BorderRange::UpperBorder, 1);
        expandRange(BorderRange::UpperBorder);

        size_++;
        return true;
    }

    if (id == idRange_.getIdInfo(BorderRange::LowerBorder, 1).value &&
        !(idRange_.getIdInfo(BorderRange::LowerBorder, 1).flags & IDRF_ID_OUT_RANGE)) {

        if (!idRange_.getBorderState(BorderRange::LowerBorder)) {
            idRange_.setBorderState(BorderRange::LowerBorder, true);

            if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
                freeIds_.add(idRange_.getBorderValue(BorderRange::LowerBorder));
        }

        idRange_.moveBorder(BorderRange::LowerBorder, 1);
        expandRange(BorderRange::LowerBorder);

        size_++;
        return true;
    }

    reservedIds_.add(id);
    size_++;
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
        T id = reservedIds_.findIdByIndex(i);

        if (!isStandardId(id)) {
            reservedIds_.erase(id);
            --size_;
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
        auto result = idRange_.getIdInfo(border, 1);

        if (idRange_.getBorderState(border)) {
            return IDRF_SUCCESSFULLY;
        }

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
int
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
                return -1;

            if(id == idRange_.getBorderValue(BorderRange::UpperBorder)) {
                if (idRange_.getBorderState(BorderRange::UpperBorder) == true && idRange_.getBorderState(BorderRange::LowerBorder) == true)
                    return 0;

                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);

                expandRange(BorderRange::UpperBorder);
                expandRange(BorderRange::LowerBorder);

                ++size_;
                return 1;
            }
        }

        if (id == idRange_.getBorderValue(BorderRange::UpperBorder) || id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return 0;

        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
            return 0;

        if (isStandardId(id)) {
            if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
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

            return -1;
        }


        if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
            int i = 1;

            while (true) {
                auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, i);

                if (idInfo.value > id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                    break;

                if (reservedIds_.find(idInfo.value))
                    reservedIds_.erase(idInfo.value);
                else
                    ++size_;

                idRange_.moveBorder(BorderRange::UpperBorder, 1);
                ++i;
            }

            idRange_.setBorderState(BorderRange::UpperBorder, true);
            idRange_.setBorderState(BorderRange::LowerBorder, true);

            expandRange(BorderRange::UpperBorder);
            expandRange(BorderRange::LowerBorder);

            return 1;
        }

        if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
            int i = 1;

            while (true) {
                auto idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, i);

                if (idInfo.value < id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                    break;

                if (reservedIds_.find(idInfo.value))
                    reservedIds_.erase(idInfo.value);
                else
                    ++size_;

                idRange_.moveBorder(BorderRange::LowerBorder, 1);
                ++i;
            }

            //      ub---->\
            // .....lb.....@...
            //ub и lb могут быть на старте и при перемещении одной из границ обе активируются,
            //а потому expandRange делаем с обоими границами.
            idRange_.setBorderState(BorderRange::UpperBorder, true);
            idRange_.setBorderState(BorderRange::LowerBorder, true);

            expandRange(BorderRange::UpperBorder);
            expandRange(BorderRange::LowerBorder);

            return 1;
        }

        return -1;
    }

    // ----------------------------------

    if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
        id == idRange_.getBorderValue(BorderRange::UpperBorder)) {

        if (idRange_.getBorderState(BorderRange::UpperBorder) == true && idRange_.getBorderState(BorderRange::LowerBorder) == true)
            return 0;

        if (idRange_.getBorderState(BorderRange::UpperBorder) != idRange_.getBorderState(BorderRange::LowerBorder))
            return -1;

        idRange_.setBorderState(BorderRange::UpperBorder, true);
        idRange_.setBorderState(BorderRange::LowerBorder, true);

        expandRange(BorderRange::UpperBorder);
        expandRange(BorderRange::LowerBorder);

        ++size_;
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

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
        return 0;

    if (isStandardId(id)) {
        if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
            if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder)) {
                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);
            }
            else {
                idRange_.setBorderState(BorderRange::UpperBorder, true);
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
                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);
            }
            else {
                idRange_.setBorderState(BorderRange::LowerBorder, true);
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

        return -1;
    }

    if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder)) {
            idRange_.setBorderState(BorderRange::UpperBorder, true);
            idRange_.setBorderState(BorderRange::LowerBorder, true);
        }
        else {
            idRange_.setBorderState(BorderRange::UpperBorder, true);
        }

        int i = 1;

        while (true) {
            auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, i);

            if (idInfo.value > id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                break;

            if (reservedIds_.find(idInfo.value))
                reservedIds_.erase(idInfo.value);
            else
                ++size_;

            idRange_.moveBorder(BorderRange::UpperBorder, 1);
            ++i;
        }

        expandRange(BorderRange::UpperBorder);
        return 1;
    }

    if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder)) {
            idRange_.setBorderState(BorderRange::UpperBorder, true);
            idRange_.setBorderState(BorderRange::LowerBorder, true);
        }
        else {
            idRange_.setBorderState(BorderRange::LowerBorder, true);
        }

        int i = 1;

        while (true) {
            auto idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, i);

            if (idInfo.value < id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                break;

            if (reservedIds_.find(idInfo.value))
                reservedIds_.erase(idInfo.value);
            else
                ++size_;

            idRange_.moveBorder(BorderRange::LowerBorder, 1);
            ++i;
        }

        expandRange(BorderRange::LowerBorder);
        return 1;
    }

    return -1;
}

template<class T, class T_Step>
int
ONF::RangeIdManager<T, T_Step>::
interpolateIds(T id)
{
    if (id > idRange_.getBorderLimit(BorderRange::UpperBorder) || id < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return 0;

    if (reservedIds_.find(id))
        return 0;

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            idRange_.getBorderState(BorderRange::UpperBorder) == false &&
            idRange_.getBorderState(BorderRange::LowerBorder) == false) {

            if (isStandardId(id)) {
                T upperBorderValue = idRange_.getBorderValue(BorderRange::UpperBorder);
                T lowerBorderValue = idRange_.getBorderValue(BorderRange::LowerBorder);

                if (id > upperBorderValue) {
                    if (!idRange_.setBorderValue(BorderRange::UpperBorder, id))
                        return 0;

                    if (!idRange_.setBorderValue(BorderRange::LowerBorder, id)) {
                        if (!idRange_.setBorderValue(BorderRange::UpperBorder, upperBorderValue))
                            return -1;

                        return 0;
                    }

                    idRange_.setBorderState(BorderRange::UpperBorder, true);
                    idRange_.setBorderState(BorderRange::LowerBorder, true);

                    expandRange(BorderRange::UpperBorder);
                    expandRange(BorderRange::LowerBorder);

                    ++size_;
                    return 1;
                }

                if (id < lowerBorderValue) {
                    if (!idRange_.setBorderValue(BorderRange::LowerBorder, id))
                        return 0;

                    if (!idRange_.setBorderValue(BorderRange::UpperBorder, id)) {
                        if (!idRange_.setBorderValue(BorderRange::LowerBorder, lowerBorderValue))
                            return -1;

                        return 0;
                    }

                    idRange_.setBorderState(BorderRange::UpperBorder, true);
                    idRange_.setBorderState(BorderRange::LowerBorder, true);

                    expandRange(BorderRange::UpperBorder);
                    expandRange(BorderRange::LowerBorder);

                    ++size_;
                    return 1;
                }

                if (id == idRange_.getBorderValue(BorderRange::UpperBorder)) {  // UpperBorder == LowerBorder
                    idRange_.setBorderState(BorderRange::UpperBorder, true);
                    idRange_.setBorderState(BorderRange::LowerBorder, true);

                    expandRange(BorderRange::UpperBorder);
                    expandRange(BorderRange::LowerBorder);

                    ++size_;
                    return 1;
                }

                return 0;
            }


            T upperBorderValue = idRange_.getBorderValue(BorderRange::UpperBorder);
            T lowerBorderValue = idRange_.getBorderValue(BorderRange::LowerBorder);

            if (id > upperBorderValue) {
                T standardId = findNearestStandardId(id);

                if (standardId == idRange_.getBorderValue(BorderRange::UpperBorder)) {  // UpperBorder == LowerBorder
                    idRange_.setBorderState(BorderRange::UpperBorder, true);
                    idRange_.setBorderState(BorderRange::LowerBorder, true);

                    expandRange(BorderRange::UpperBorder);
                    expandRange(BorderRange::LowerBorder);

                    ++size_;
                    return 1;
                }

                if (reservedIds_.find(standardId))
                    return 0;

                if (!idRange_.setBorderValue(BorderRange::UpperBorder, standardId))
                    return 0;

                if (!idRange_.setBorderValue(BorderRange::LowerBorder, standardId)) {
                    if (!idRange_.setBorderValue(BorderRange::UpperBorder, upperBorderValue))
                        return -1;

                    return 0;
                }

                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);

                expandRange(BorderRange::UpperBorder);
                expandRange(BorderRange::LowerBorder);

                ++size_;
                return 1;
            }

            if (id < lowerBorderValue) {
                T standardId = findNearestStandardId(id);

                if (standardId == idRange_.getBorderValue(BorderRange::LowerBorder)) {  // UpperBorder == LowerBorder
                    idRange_.setBorderState(BorderRange::UpperBorder, true);
                    idRange_.setBorderState(BorderRange::LowerBorder, true);

                    expandRange(BorderRange::UpperBorder);
                    expandRange(BorderRange::LowerBorder);

                    ++size_;
                    return 1;
                }

                if (reservedIds_.find(standardId))
                    return 0;

                if (!idRange_.setBorderValue(BorderRange::LowerBorder, standardId))
                    return 0;

                if (!idRange_.setBorderValue(BorderRange::UpperBorder, standardId)) {
                    if (!idRange_.setBorderValue(BorderRange::LowerBorder, lowerBorderValue))
                        return -1;

                    return 0;
                }

                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);

                expandRange(BorderRange::UpperBorder);
                expandRange(BorderRange::LowerBorder);

                ++size_;
                return 1;
            }

            return 0;
        }

        if (isStandardId(id)) {
            if (id <= idRange_.getBorderValue(BorderRange::UpperBorder) || id >= idRange_.getBorderValue(BorderRange::LowerBorder))
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

        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) || id > idRange_.getBorderValue(BorderRange::LowerBorder))
            return 0;

        if ((id < idRange_.getIdInfo(BorderRange::UpperBorder, 1).value || id > idRange_.getIdInfo(BorderRange::LowerBorder, 1).value) &&
            !(idRange_.getIdInfo(BorderRange::UpperBorder, 1).flags & IDRF_ID_OUT_RANGE) &&
            !(idRange_.getIdInfo(BorderRange::LowerBorder, 1).flags & IDRF_ID_OUT_RANGE))
            return 0;

        if (id > idRange_.getBorderValue(BorderRange::UpperBorder)) {
            int i = 1;

            while (true) {
                auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, i);

                if (idInfo.value > id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                    break;

                auto idInfo2 = idRange_.getIdInfo(BorderRange::UpperBorder, i + 1);

                if (idInfo2.value < id && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
                    if (!reservedIds_.find(idInfo.value))
                        freeIds_.add(idInfo.value);
                    else
                        reservedIds_.erase(idInfo.value);

                    idRange_.moveBorder(BorderRange::UpperBorder, 1);
                    ++i;
                    continue;
                }

                if (reservedIds_.find(idInfo.value))
                    reservedIds_.erase(idInfo.value);

                idRange_.moveBorder(BorderRange::UpperBorder, 1);
                break;
            }

            expandRange(BorderRange::UpperBorder);
            ++size_;
            return 1;
        }

        if (id < idRange_.getBorderValue(BorderRange::LowerBorder)) {
            int i = 1;  //TODO: int заменить на longlong

            while (true) {
                auto idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, i);

                if (idInfo.value < id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                    break;

                auto idInfo2 = idRange_.getIdInfo(BorderRange::LowerBorder, i + 1);

                if (idInfo2.value > id && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
                    if (!reservedIds_.find(idInfo.value))
                        freeIds_.add(idInfo.value);
                    else
                        reservedIds_.erase(idInfo.value);

                    idRange_.moveBorder(BorderRange::LowerBorder, 1);
                    ++i;
                    continue;
                }

                if (reservedIds_.find(idInfo.value))
                    reservedIds_.erase(idInfo.value);

                idRange_.moveBorder(BorderRange::LowerBorder, 1);
                break;
            }

            expandRange(BorderRange::LowerBorder);
            ++size_;
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
            return -1;

        idRange_.setBorderState(BorderRange::UpperBorder, true);
        idRange_.setBorderState(BorderRange::LowerBorder, true);

        expandRange(BorderRange::UpperBorder);
        expandRange(BorderRange::LowerBorder);

        ++size_;
        return 1;
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
        return 0;

    if (isStandardId(id)) {
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

    if ( (id < idRange_.getIdInfo(BorderRange::UpperBorder, 1).value) &&
        !(idRange_.getIdInfo(BorderRange::UpperBorder, 1).flags & IDRF_ID_OUT_RANGE)) {

        if (idRange_.getBorderState(BorderRange::UpperBorder))
            return 0;

        idRange_.setBorderState(BorderRange::UpperBorder, true);
        ++size_;
        return 1;
    }

    if ( (id > idRange_.getIdInfo(BorderRange::LowerBorder, 1).value) &&
        !(idRange_.getIdInfo(BorderRange::LowerBorder, 1).flags & IDRF_ID_OUT_RANGE)) {

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

        int i = 1;

        while (true) {
            auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, i);

            if (idInfo.value > id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                break;

            auto idInfo2 = idRange_.getIdInfo(BorderRange::UpperBorder, i + 1);

            if (idInfo2.value < id && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
                if (!reservedIds_.find(idInfo.value))
                    freeIds_.add(idInfo.value);
                else
                    reservedIds_.erase(idInfo.value);

                idRange_.moveBorder(BorderRange::UpperBorder, 1);
                ++i;
                continue;
            }

            if (reservedIds_.find(idInfo.value))
                reservedIds_.erase(idInfo.value);

            idRange_.moveBorder(BorderRange::UpperBorder, 1);
            break;
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

        int i = 1;  //TODO: int заменить на longlong

        while (true) {
            auto idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, i);

            if (idInfo.value < id || (idInfo.flags & IDRF_ID_OUT_RANGE))
                break;

            auto idInfo2 = idRange_.getIdInfo(BorderRange::LowerBorder, i + 1);

            if (idInfo2.value > id && !(idInfo.flags & IDRF_ID_OUT_RANGE)) {
                if (!reservedIds_.find(idInfo.value))
                    freeIds_.add(idInfo.value);
                else
                    reservedIds_.erase(idInfo.value);

                idRange_.moveBorder(BorderRange::LowerBorder, 1);
                ++i;
                continue;
            }

            if (reservedIds_.find(idInfo.value))
                reservedIds_.erase(idInfo.value);

            idRange_.moveBorder(BorderRange::LowerBorder, 1);
            break;
        }

        expandRange(BorderRange::LowerBorder);
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















//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//interpolateIds(BorderRange border, T id)
//{
//    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
//        int _count = 0;
//        int _i = 1;

//        while (true) {
//            auto _result = idArea_.getIdInfo(border, _i);

//            if (reservedIds_.find(_result.value)) {
//                reservedIds_.freeId(_result.value);
//                _count = _i;
//            }
//            else {
//                if (_result.value > id)
//                    break;

//                freeIds_.add(_result.value);
//            }

//            ++_i;
//        }

//        idArea_.moveBorder(border, _count);

//        if (!isStandardId(id))
//            reservedIds_.add(id);

//        return true;
//    }

//    T _startValueU = idArea_.getBorderValue(BorderRange::UpperBorder);
//    T _startValueL = idArea_.getBorderValue(BorderRange::LowerBorder);
//    bool _startState = idArea_.getBorderState(border);


//    T _lastValue = (border == BorderRange::UpperBorder ? _startValueU : _startValueL);
//    bool _currentState = _startState;

//    int _i = 0;

//    while (true) {
//        auto _result = idArea_.getIdInfo(border, 1);

//        if (reservedIds_.find(_result.value)) {
//            reservedIds_.freeId(_result.value);
//            _currentState = true;
//        }
//        else {
//            if (_result.value > id)
//                break;

//            freeIds_.add(_result.value);
//            _lastValue = _result.value;
//            _currentState = false;
//        }

//        idArea_.moveBorder(border, 1);
//        ++_i;
//    }

//    if (_i != 0) {
//        idArea_.setBorderState(border, _currentState);
//        if (_currentState == false) {
//            freeIds_.freeId(_lastValue);
//        }

//        if (_startValueU != _startValueL && !_startState) {
//            if (border == BorderRange::UpperBorder)
//                freeIds_.add(_startValueU);
//            else
//                freeIds_.add(_startValueL);
//        }
//    }

//    if (!isStandardId(id))
//        reservedIds_.add(id);

//    return true;
//}


















//template<class T, class T_Step>
//int
//ONF::IdManager<T, T_Step>::
//getFreeId(T& id)
//{
//    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
//        if (idArea_.getBorderValue(BorderRange::UpperBorder) == idArea_.getBorderValue(BorderRange::LowerBorder) &&
//            idArea_.getBorderState(BorderRange::UpperBorder) == false &&
//            idArea_.getBorderState(BorderRange::LowerBorder) == false) {

//            idArea_.setBorderState(BorderRange::UpperBorder, true);
//            idArea_.setBorderState(BorderRange::LowerBorder, true);

//            id = idArea_.getBorderValue(BorderRange::UpperBorder);

//            expandRange(BorderRange::UpperBorder);
//            expandRange(BorderRange::LowerBorder);

//            return IDRF_SUCCESSFULLY;
//        }

//        if (idArea_.getBorderState(BorderRange::LowerBorder) == false) {
//            idArea_.setBorderState(BorderRange::LowerBorder, true);
//            id = idArea_.getBorderValue(BorderRange::LowerBorder);
//            expandRange(BorderRange::LowerBorder);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (idArea_.getBorderState(BorderRange::UpperBorder) == false) {
//            idArea_.setBorderState(BorderRange::UpperBorder, true);
//            id = idArea_.getBorderValue(BorderRange::UpperBorder);
//            expandRange(BorderRange::UpperBorder);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (idArea_.getBorderValue(BorderRange::UpperBorder) < idArea_.getStart()) {
//            getNextId(BorderRange::UpperBorder, id);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (idArea_.getBorderValue(BorderRange::LowerBorder) > idArea_.getStart()) {
//            getNextId(BorderRange::LowerBorder, id);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (freeIds_.size()) {
//            freeIds_.getNextId(id);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (step_ > 0) {
//            getNextId(BorderRange::UpperBorder, id);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (step_ < 0) {
//            getNextId(BorderRange::LowerBorder, id);
//            return IDRF_SUCCESSFULLY;
//        }

//        return IDRF_RANGE_ARE_BENT;
//    }

//    if (idIssuingMethod_ == IdIssuingMethod::Ascending) {
//        if (idArea_.getBorderValue(BorderRange::UpperBorder) == idArea_.getBorderValue(BorderRange::LowerBorder) &&
//            idArea_.getBorderState(BorderRange::UpperBorder) == false &&
//            idArea_.getBorderState(BorderRange::LowerBorder) == false) {

//            idArea_.setBorderState(BorderRange::UpperBorder, true);
//            idArea_.setBorderState(BorderRange::LowerBorder, true);

//            id = idArea_.getBorderValue(BorderRange::UpperBorder);

//            expandRange(BorderRange::UpperBorder);
//            expandRange(BorderRange::LowerBorder);

//            return IDRF_SUCCESSFULLY;
//        }

//        if (idArea_.getBorderState(BorderRange::LowerBorder) == false) {
//            idArea_.setBorderState(BorderRange::LowerBorder, true);
//            id = idArea_.getBorderValue(BorderRange::LowerBorder);
//            expandRange(BorderRange::LowerBorder);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (freeIds_.size()) {
//            freeIds_.getNextId(id);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (idArea_.getBorderState(BorderRange::UpperBorder) == false) {
//            idArea_.setBorderState(BorderRange::UpperBorder, true);
//            id = idArea_.getBorderValue(BorderRange::UpperBorder);
//            expandRange(BorderRange::UpperBorder);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (step_ > 0) {
//            getNextId(BorderRange::UpperBorder, id);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (step_ < 0) {
//            getNextId(BorderRange::LowerBorder, id);
//            return IDRF_SUCCESSFULLY;
//        }

//        return IDRF_RANGE_ARE_BENT;
//    }

//    if (idIssuingMethod_ == IdIssuingMethod::Descending) {
//        if (idArea_.getBorderValue(BorderRange::UpperBorder) == idArea_.getBorderValue(BorderRange::LowerBorder) &&
//            idArea_.getBorderState(BorderRange::UpperBorder) == false &&
//            idArea_.getBorderState(BorderRange::LowerBorder) == false) {

//            idArea_.setBorderState(BorderRange::UpperBorder, true);
//            idArea_.setBorderState(BorderRange::LowerBorder, true);

//            id = idArea_.getBorderValue(BorderRange::UpperBorder);

//            expandRange(BorderRange::UpperBorder);
//            expandRange(BorderRange::LowerBorder);

//            return IDRF_SUCCESSFULLY;
//        }

//        if (idArea_.getBorderState(BorderRange::UpperBorder) == false) {
//            idArea_.setBorderState(BorderRange::UpperBorder, true);
//            id = idArea_.getBorderValue(BorderRange::UpperBorder);
//            expandRange(BorderRange::UpperBorder);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (freeIds_.size()) {
//            freeIds_.getNextId(id);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (idArea_.getBorderState(BorderRange::LowerBorder) == false) {
//            idArea_.setBorderState(BorderRange::LowerBorder, true);
//            id = idArea_.getBorderValue(BorderRange::LowerBorder);
//            expandRange(BorderRange::LowerBorder);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (step_ < 0) {
//            getNextId(BorderRange::LowerBorder, id);
//            return IDRF_SUCCESSFULLY;
//        }

//        if (step_ > 0) {
//            getNextId(BorderRange::UpperBorder, id);
//            return IDRF_SUCCESSFULLY;
//        }

//        return IDRF_RANGE_ARE_BENT;
//    }
//}

//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//reserveId(T id, ReservationMethod reservationMethod)
//{
//    if (id < std::numeric_limits<T>::lowest() || id > std::numeric_limits<T>::max())
//        return false;

//    if (!isStandardId(id)) {
//        if (isHardStep_)
//            return false;

//        if (reservedIds_.find(id))
//            return false;

//        if (reservationMethod == ReservationMethod::Interpolate) {
//            if (id > idArea_.getBorderValue(BorderRange::UpperBorder))
//                return interpolateIds(BorderRange::UpperBorder, id);

//            if (id < idArea_.getBorderValue(BorderRange::LowerBorder))
//                return interpolateIds(BorderRange::LowerBorder, id);

//            reservedIds_.add(id);
//            return true;
//        }

//        if (reservationMethod == ReservationMethod::ReserveRange) {
//            if (id > idArea_.getBorderValue(BorderRange::UpperBorder))
//                return reserveIds(BorderRange::UpperBorder, id);

//            if (id < idArea_.getBorderValue(BorderRange::LowerBorder))
//                return reserveIds(BorderRange::LowerBorder, id);

//            reservedIds_.add(id);
//            return true;
//        }

//        reservedIds_.add(id);
//        return true;
//    }


//    if (idArea_.getBorderValue(BorderRange::UpperBorder) == idArea_.getBorderValue(BorderRange::LowerBorder) &&
//        idArea_.getBorderValue(BorderRange::UpperBorder) == id) {
//        if (idArea_.getBorderState(BorderRange::UpperBorder) == true &&
//            idArea_.getBorderState(BorderRange::LowerBorder) == true)
//            return false;

//        idArea_.setBorderState(BorderRange::UpperBorder, true);
//        idArea_.setBorderState(BorderRange::LowerBorder, true);

//        expandRange(BorderRange::UpperBorder);
//        expandRange(BorderRange::LowerBorder);

//        return true;
//    }

//    if (id == idArea_.getBorderValue(BorderRange::UpperBorder)) {
//        if (idArea_.getBorderState(BorderRange::UpperBorder))
//            return false;

//        idArea_.setBorderState(BorderRange::UpperBorder, true);
//        expandRange(BorderRange::UpperBorder);

//        return true;
//    }

//    if (id == idArea_.getBorderValue(BorderRange::LowerBorder)) {
//        if (idArea_.getBorderState(BorderRange::LowerBorder))
//            return false;

//        idArea_.setBorderState(BorderRange::LowerBorder, true);
//        expandRange(BorderRange::LowerBorder);

//        return true;
//    }

//    if (id > idArea_.getBorderValue(BorderRange::UpperBorder) || id < idArea_.getBorderValue(BorderRange::LowerBorder))
//        if (reservedIds_.find(id))
//            return false;

//    if (id < idArea_.getBorderValue(BorderRange::UpperBorder) && id > idArea_.getBorderValue(BorderRange::LowerBorder)) {
//        if (!freeIds_.find(id))
//            return false;

//        freeIds_.freeId(id);
//        return true;
//    }

//    if (reservationMethod == ReservationMethod::Interpolate || reservationMethod == ReservationMethod::AutoSelect) {
//        if (id > idArea_.getBorderValue(BorderRange::UpperBorder))
//            return interpolateIds(BorderRange::UpperBorder, id);

//        return interpolateIds(BorderRange::LowerBorder, id);
//    }

//    if (reservationMethod == ReservationMethod::ReserveRange) {
//        if (id > idArea_.getBorderValue(BorderRange::UpperBorder))
//            return reserveIds(BorderRange::UpperBorder, id);

//        return reserveIds(BorderRange::LowerBorder, id);
//    }

//    reservedIds_.add(id);
//    return true;
//}

//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//interpolateIds(BorderRange border, T id)
//{
//    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
//        int _count = 0;
//        int _i = 1;

//        while (true) {
//            auto _result = idArea_.getIdInfo(border, _i);

//            if (reservedIds_.find(_result.value)) {
//                reservedIds_.freeId(_result.value);
//                _count = _i;
//            }
//            else {
//                if (_result.value > id)
//                    break;

//                freeIds_.add(_result.value);
//            }

//            ++_i;
//        }

//        idArea_.moveBorder(border, _count);

//        if (!isStandardId(id))
//            reservedIds_.add(id);

//        return true;
//    }

//    T _startValueU = idArea_.getBorderValue(BorderRange::UpperBorder);
//    T _startValueL = idArea_.getBorderValue(BorderRange::LowerBorder);
//    bool _startState = idArea_.getBorderState(border);


//    T _lastValue = (border == BorderRange::UpperBorder ? _startValueU : _startValueL);
//    bool _currentState = _startState;

//    int _i = 0;

//    while (true) {
//        auto _result = idArea_.getIdInfo(border, 1);

//        if (reservedIds_.find(_result.value)) {
//            reservedIds_.freeId(_result.value);
//            _currentState = true;
//        }
//        else {
//            if (_result.value > id)
//                break;

//            freeIds_.add(_result.value);
//            _lastValue = _result.value;
//            _currentState = false;
//        }

//        idArea_.moveBorder(border, 1);
//        ++_i;
//    }

//    if (_i != 0) {
//        idArea_.setBorderState(border, _currentState);
//        if (_currentState == false) {
//            freeIds_.freeId(_lastValue);
//        }

//        if (_startValueU != _startValueL && !_startState) {
//            if (border == BorderRange::UpperBorder)
//                freeIds_.add(_startValueU);
//            else
//                freeIds_.add(_startValueL);
//        }
//    }

//    if (!isStandardId(id))
//        reservedIds_.add(id);

//    return true;
//}

//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//reserveIds(BorderRange border, T id)
//{
//    if (idArea_.getBorderValue(BorderRange::UpperBorder) == idArea_.getBorderValue(BorderRange::LowerBorder)) {
//        idArea_.setBorderState(BorderRange::UpperBorder, true);
//        idArea_.setBorderState(BorderRange::LowerBorder, true);
//    }

//    while (true) {
//        auto _result = idArea_.getIdInfo(border, 1);

//        if (reservedIds_.find(_result.value)) {
//            reservedIds_.freeId(_result.value);
//        }
//        else {
//            if (_result.value > id)
//                break;
//        }

//        idArea_.moveBorder(border, 1);
//    }

//    if (!isStandardId(id))
//        reservedIds_.add(id);

//    if (idIssuingMethod_ == IdIssuingMethod::Ascending || idIssuingMethod_ == IdIssuingMethod::Descending) {
//        idArea_.setBorderState(border, true);
//    }

//    return true;
//}


//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//freeId(T id)
//{
//    if (id < std::numeric_limits<T>::lowest() || id > std::numeric_limits<T>::max())
//        return false;

//    if (!isStandardId(id)) {
//        if (!reservedIds_.find(id))
//            return false;

//        reservedIds_.freeId(id);
//        return true;
//    }

//    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
//        if (id == idArea_.getBorderValue(BorderRange::UpperBorder)) {
//            if (reduceRange(BorderRange::UpperBorder) == IDRF_RANGE_ARE_BENT) {
//                idArea_.setBorderState(BorderRange::UpperBorder, false);
//                idArea_.setBorderState(BorderRange::LowerBorder, false);
//                return true;
//            }

//            return true;
//        }

//        if (id == idArea_.getBorderValue(BorderRange::LowerBorder)) {
//            if (reduceRange(BorderRange::LowerBorder) == IDRF_RANGE_ARE_BENT) {
//                idArea_.setBorderState(BorderRange::UpperBorder, false);
//                idArea_.setBorderState(BorderRange::LowerBorder, false);
//                return true;
//            }

//            return true;
//        }
//    }
//    else {
//        if (id == idArea_.getBorderValue(BorderRange::UpperBorder) &&
//            id == idArea_.getBorderValue(BorderRange::LowerBorder)) {

//            if (!idArea_.getBorderState(BorderRange::UpperBorder) &&
//                !idArea_.getBorderState(BorderRange::LowerBorder))
//                return false;

//            if (idArea_.getBorderState(BorderRange::UpperBorder) !=
//                idArea_.getBorderState(BorderRange::LowerBorder))
//                throw "---------------";

//            idArea_.setBorderState(BorderRange::UpperBorder, false);
//            idArea_.setBorderState(BorderRange::LowerBorder, false);
//            return true;
//        }

//        if (id == idArea_.getBorderValue(BorderRange::UpperBorder)) {
//            if (!idArea_.getBorderState(BorderRange::UpperBorder))
//                return false;

//            idArea_.setBorderState(BorderRange::UpperBorder, false);
//            return true;
//        }

//        if (id == idArea_.getBorderValue(BorderRange::LowerBorder)) {
//            if (!idArea_.getBorderState(BorderRange::LowerBorder))
//                return false;

//            idArea_.setBorderState(BorderRange::LowerBorder, false);
//            return true;
//        }
//    }

//    if (id < idArea_.getBorderValue(BorderRange::UpperBorder) &&
//        id > idArea_.getBorderValue(BorderRange::LowerBorder)) {

//        if (freeIds_.find(id))
//            return false;

//        freeIds_.add(id);
//        return true;
//    }

//    if (!reservedIds_.find(id))
//        return false;

//    reservedIds_.freeId(id);
//    return true;
//}

//template<class T, class T_Step>
//void
//ONF::IdManager<T, T_Step>::
//freeAll()
//{
//    freeIds_.clear();
//    reservedIds_.clear();
//    idArea_.reset();
//}

//template<class T, class T_Step>
//void
//ONF::IdManager<T, T_Step>::
//setHardStep(bool value)
//{
//    if (value == isHardStep_)
//        return;

//    isHardStep_ = value;

//    if (value == false)
//        return;

//    // i итерируется таким образом для простой поддержки unsigned.
//    for (T i = 0; i < reservedIds_.size();) {
//        T _id = reservedIds_.findIdByIndex(i);
//        if (!isStandardId(_id)) {
//            reservedIds_.freeId(_id);
//            continue;
//        }

//        ++i;
//    }
//}

//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//isHardStep() const
//{
//    return isHardStep_;
//}

//template<class T, class T_Step>
//void
//ONF::IdManager<T, T_Step>::
//setIdIssuingMethod(IdIssuingMethod idIssuingMethod)
//{
//    if (idIssuingMethod == idIssuingMethod_)
//        return;

//    freeIds_.setIdIssuingMethod(idIssuingMethod);
//    idIssuingMethod_ = idIssuingMethod;

//    if (idIssuingMethod == IdIssuingMethod::Dynamic) {
//        if (normalizeRange(BorderRange::UpperBorder, IdIssuingMethod::Dynamic) == IDRF_RANGE_ARE_BENT ||
//            normalizeRange(BorderRange::LowerBorder, IdIssuingMethod::Dynamic) == IDRF_RANGE_ARE_BENT) {
//            idArea_.setBorderState(BorderRange::UpperBorder, false);
//            idArea_.setBorderState(BorderRange::LowerBorder, false);
//        }

//        return;
//    }
//}

//template<class T, class T_Step>
//inline ONF::IdIssuingMethod
//ONF::IdManager<T, T_Step>::
//getIdIssuingMethod() const
//{
//    return idIssuingMethod_;
//}

//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//findId(T id) const
//{
//    if (id < std::numeric_limits<T>::lowest() || id > std::numeric_limits<T>::max())
//        return false;

//    if (!isStandardId(id)) {
//        if (isHardStep_)
//            return false;

//        return reservedIds_.find(id);
//    }

//    if (id < idArea_.getBorderValue(BorderRange::UpperBorder) &&
//        id > idArea_.getBorderValue(BorderRange::LowerBorder))
//        return !freeIds_.find(id);

//    if (id == idArea_.getBorderValue(BorderRange::UpperBorder))
//        return idArea_.getBorderState(BorderRange::UpperBorder);

//    if (id == idArea_.getBorderValue(BorderRange::LowerBorder))
//        return idArea_.getBorderState(BorderRange::LowerBorder);

//    return reservedIds_.find(id);
//}

//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//isStandardId(T id) const
//{
//    ldouble _An = static_cast<ldouble>(id);
//    ldouble _A1 = static_cast<ldouble>(idArea_.getStart());
//    ldouble _d = static_cast<ldouble>(step_);

//    ldouble n = std::abs((_An - _A1 + _d) / _d);
//    return (n - static_cast<ulonglong>(n) == static_cast<ldouble>(0.0));
//}

//template<class T, class T_Step>
//T_Step
//ONF::IdManager<T, T_Step>::
//getStep() const
//{
//    return step_;
//}

//template<class T, class T_Step>
//ONF::IdManager<T, T_Step>&
//ONF::IdManager<T, T_Step>::
//operator=(const IdManager<T, T_Step>& other)
//{
//    freeIds_ = other.freeIds_;
//    reservedIds_ = other.reservedIds_;
//    idArea_ = other.idArea_;

//    step_ = other.step_;
//    isHardStep_ = other.isHardStep_;
//    idIssuingMethod_ = other.idIssuingMethod_;

//    return *this;
//}

//template<class T, class T_Step>
//int
//ONF::IdManager<T, T_Step>::
//expandRange(BorderRange border)
//{
//    while (true) {
//        auto _result = idArea_.getIdInfo(border, 1);
//        if (reservedIds_.find(_result.value)) {
//            reservedIds_.freeId(_result.value);
//            idArea_.moveBorder(border, 1);
//            continue;
//        }

//        return _result.errCode;
//    }
//}

//template<class T, class T_Step>
//int
//ONF::IdManager<T, T_Step>::
//reduceRange(BorderRange border)
//{
//    while (true) {
//        auto _result = idArea_.moveBorder(border, -1);

//        if (_result.errCode == IDRF_RANGE_ARE_BENT)
//            return IDRF_RANGE_ARE_BENT;

//        if (freeIds_.find(_result.value))
//            continue;

//        return _result.errCode;
//    }
//}

//template<class T, class T_Step>
//int
//ONF::IdManager<T, T_Step>::
//normalizeRange(BorderRange border)
//{
//    auto _result = idArea_.getIdInfo(border, 1);

//    if (reservedIds_.find(_result.value)) {
//        if (!idArea_.getBorderState(border)) {
//            freeIds_.add(idArea_.getBorderValue(border));
//            idArea_.setBorderState(border, true);
//        }

//        return expandRange(border);
//    }

//    if (idArea_.getBorderState(border)) {
//        return IDRF_SUCCESSFULLY;
//    }

//    idArea_.setBorderState(border, true);
//    return reduceRange(border);
//}

//template<class T, class T_Step>
//int
//ONF::IdManager<T, T_Step>::
//getNextId(BorderRange border, T& id)
//{
//    while (true) {
//        auto _result = idArea_.moveBorder(border, 1);
//        if (reservedIds_.find(_result.value)) {
//            reservedIds_.freeId(_result.value);
//            continue;
//        }

//        id = _result.value;
//        return _result.errCode;
//    }
//}

//template<class T, class T_Step>
//template<class TF>
//inline TF
//ONF::IdManager<T, T_Step>::
//onf_abs(TF value) const
//{
//    return value < 0 ? -value : value;
//}








































//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//reserveId(T id, ReservationMethod reservationMethod)
//{
//    if (!isStandardId(id)) {
//        if (isHardStep_)
//            return false;

//        if (reservedIds_.find(id))
//            return false;

//        if (id < std::numeric_limits<T>::min() || id > std::numeric_limits<T>::max())
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
//                T _id = 0;
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
//                T _id = 0;
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
//                T _id = 0;
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
//                    for (T i = idArea_.getMinId() + idArea_.getStep(); i < id; i += idArea_.getStep()) {
//                        if (freeIds_.find(i))
//                            freeIds_.freeId(i);
//                    }

//                    return true;
//                }

//                if (step_ > 0) {
//                    for (T i = idArea_.getMaxId() - idArea_.getStep(); i > id; i -= idArea_.getStep()) {
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
//                T _id = 0;
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
//                T _id = 0;
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

//    if (id < std::numeric_limits<T>::min() || id > std::numeric_limits<T>::max())
//        return false;

//    if (reservedIds_.find(id))
//        return false;

//    if (reservationMethod == ReservationMethod::Interpolate || reservationMethod == ReservationMethod::AutoSelect) {
//        if (id > idArea_.getMaxId()) {
//            T _id = 0;
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
//            T _id = 0;
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
//            T _id = 0;
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
//            T _id = 0;
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
//            T _id = 0;
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
//            T _id = 0;
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

//template<class T, class T_Step>
//int
//ONF::IdManager<T, T_Step>::
//expandRangeToTop(BorderRange border, T* id)
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

//template<class T, class T_Step>
//int
//ONF::IdManager<T, T_Step>::
//expandRangeToTopWithowtReserv(BorderRange border, T* id)
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

//template<class T, class T_Step>
//int
//ONF::IdManager<T, T_Step>::
//expandRangeToBottom(BorderRange border, T* id)
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

//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//checkRangeBorder(T value, BorderRange border) const
//{
//    switch (border) {
//        case BorderRange::LowerBorder:    return (static_cast<long long>(value) - static_cast<long long>(onf_abs(step_)) < std::numeric_limits<T>::min());
//        case BorderRange::UpperBorder:    return (static_cast<long long>(value) + static_cast<long long>(onf_abs(step_)) > std::numeric_limits<T>::max());

//    default:    throw "Unknown enumerator: " + std::to_string(static_cast<int>(border)) + " in checkRangeBorder function.";
//    }
//}


















//template<class T, class T_Step>
//ONF::IdManager<T, T_Step>::
//IdManager(T startId,
//          T_Step step,
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
//    static_assert(is_types_combination_prohibited<T, T_Step> == false);

//    step_ = (step == 0 ? 1 : step);
//    isCrossingUpperBorder_ = checkRangeBorder(startId, UpperBorder);
//    isCrossingLowerBorder_ = checkRangeBorder(startId, LowerBorder);
//}

//template<class T, class T_Step>
//ONF::IdManager<T, T_Step>::
//IdManager(const IdManager<T, T_Step>& other)
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

//template<class T, class T_Step>
//ONF::IdManager<T, T_Step>::
//~IdManager() {}

//template<class T, class T_Step>
//int
//ONF::IdManager<T, T_Step>::
//getFreeId(T& id)
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
//        maxId_ += static_cast<T>(step_);
//        expandRange();
//        return IDRF_SUCCESSFULLY;
//    }

//    if (step_ < 0) {
//        if (isCrossingLowerBorder_)
//            return IDRF_ID_OUT_RANGE;

//        id = minId_;
//        minId_ += static_cast<T>(step_);
//        expandRange();
//        return IDRF_SUCCESSFULLY;
//    }
//}

//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//isStandardId(T id) const
//{
//    long double _An = static_cast<long double>(id);
//    long double _A1 = static_cast<long double>(startId_);
//    long double _d = static_cast<long double>(step_);

//    long double n = std::abs((_An - _A1 + _d) / _d);
//    return (n - static_cast<unsigned long long>(n) == static_cast<long double>(0.0));
//}

//template<class T, class T_Step>
//void
//ONF::IdManager<T, T_Step>::
//expandRange()
//{
//    isCrossingUpperBorder_ = checkRangeBorder(maxId_, UpperBorder);
//    isCrossingLowerBorder_ = checkRangeBorder(minId_, LowerBorder);

//    while (true) {
//        if (reservedIds_.find(maxId_)) {
//            reservedIds_.freeId(maxId_);
//            isCrossingUpperBorder_ = checkRangeBorder(maxId_, UpperBorder);
//            if (!isCrossingUpperBorder_) {
//                maxId_ += static_cast<T>(onf_abs(step_));
//            }
//            continue;
//        }

//        if (reservedIds_.find(minId_)) {
//            reservedIds_.freeId(minId_);
//            isCrossingLowerBorder_ = checkRangeBorder(minId_, LowerBorder);
//            if (!isCrossingLowerBorder_) {
//                minId_ -= static_cast<T>(onf_abs(step_));
//            }
//            continue;
//        }

//        isCrossingUpperBorder_ = checkRangeBorder(maxId_, UpperBorder);
//        isCrossingLowerBorder_ = checkRangeBorder(minId_, LowerBorder);

//        break;
//    }
//}

//template<class T, class T_Step>
//bool
//ONF::IdManager<T, T_Step>::
//checkRangeBorder(T value, Borders border) const
//{
//    switch (border) {
//        case LowerBorder:    return (static_cast<long long>(value) - static_cast<long long>(onf_abs(step_)) < std::numeric_limits<T>::min());
//        case UpperBorder:    return (static_cast<long long>(value) + static_cast<long long>(onf_abs(step_)) > std::numeric_limits<T>::max());

//    default:    throw "Unknown enumerator: " + std::to_string(border) + " in checkRangeBorder function.";
//    }
//}

//template<class T, class T_Step>
//template<class TF>
//inline TF
//ONF::IdManager<T, T_Step>::
//onf_abs(TF value) const
//{
//    return value < 0 ? -value : value;
//}

























//template<class T, class T_Step>
//T
//ONF::IdManager<T, T_Step>::
//getFreeId()
//{




















//    if (std::is_unsigned<T>::value)
//        return 1;
//    else
//        return 0;
//}










//template<class T, class T_Step>
//T
//ONF::IdManager<T, T_Step>::
//getStartId() const
//{
//    return startId_;
//}

//template<class T, class T_Step>
//T
//ONF::IdManager<T, T_Step>::
//getMaxId() const
//{
//    return maxId_;
//}

//template<class T, class T_Step>
//T
//ONF::IdManager<T, T_Step>::
//getMinId() const
//{
//    return minId_;
//}

































//template<class T>
//IdManager<T>::
//IdManager()
//    : IdManager((T)0, (T)1, false) {}

//template<class T>
//IdManager<T>::
//IdManager(const IdManager<T>& other)
//    : freeIds_(other.freeIds_),
//      reservedIds_(other.reservedIds_),
//      maxId_(other.maxId_),
//      minId_(other.minId_),
//      startId_(other.startId_),
//      step_(other.step_),
//      isHardStep_(other.isHardStep) {}

//template<class T>
//IdManager<T>::
//IdManager(T startId, T step, bool isHardStep)
//    : maxId_(startId),
//      minId_(startId),
//      startId_(startId),
//      isHardStep_(isHardStep)
//{
//    step_ = ((step == (T)0) ? (T)1 : step);
//}

//template<class T>
//IdManager<T>::
//~IdManager() {}



//template<class T>
//T
//IdManager<T>::
//getFreeId()
//{
//    T _freeId = (T)0;

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

//    if (step_ < (T)0) {
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

//template<class T>
//bool
//IdManager<T>::
//reserveId(T id, ReservationMethod reservationMethod)
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
//                for (T i = maxId_; i < id; i += std::abs(step_)) {

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
//                for (T i = minId_; i > id; i -= std::abs(step_)) {

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
//            for (T i = maxId_; i < id; i += std::abs(step_)) {

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
//            for (T i = minId_; i > id; i -= std::abs(step_)) {

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

//template<class T>
//void
//IdManager<T>::
//freeId(T id)
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

//template<class T>
//void
//IdManager<T>::
//freeAll()
//{
//    freeIds_.clear();
//    reservedIds_.clear();
//    maxId_ = startId_;
//    minId_ = startId_;
//}

//template<class T>
//bool
//IdManager<T>::
//findId(T id) const
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

//template<class T>
//T
//IdManager<T>::
//getStartId() const
//{
//    return startId_;
//}

//template<class T>
//T
//IdManager<T>::
//getStep() const
//{
//    return step_;
//}

//template<class T>
//T
//IdManager<T>::
//getMaxId() const
//{
//    return maxId_;
//}

//template<class T>
//T
//IdManager<T>::
//getMinId() const
//{
//    return minId_;
//}

//template<class T>
//bool
//IdManager<T>::
//isHardStep() const
//{
//    return isHardStep_;
//}

//template<class T>
//bool
//IdManager<T>::
//isStandardId(T id) const
//{
//    float n = std::abs((float)(id - startId_ + step_) / (float)step_);
//    return (float)n - (size_t)n == (float)0.0;
//}

//template<class T>
//IdManager<T>&
//IdManager<T>::
//operator=(const IdManager<T>& other)
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
