#include "../IdManagement.h"

#include <vector>

using ONF::is_forbidden_types_combination;


template<class T, class T_Step>
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
RangeIdManager(T start, T_Step step)
    : idRange_        (start, ONF::abs(step)), //TODO: Если T будет char, а T_Step будет long long то long long ужмется до char.
      step_           (step == 0 ? 1 : step),
      size_           (0),
      isHardStep_     (true),
      idIssuingMethod_(IdIssuingMethod::Dynamic) {}

template<class T, class T_Step>
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
RangeIdManager(const RangeIdManager<T, T_Step>& other)
    : freeIds_        (other.freeIds_),
      reservedIds_    (other.reservedIds_),
      idRange_        (other.idRange_),
      step_           (other.step_),
      size_           (other.size_),
      isHardStep_     (other.isHardStep_),
      idIssuingMethod_(other.idIssuingMethod_) {}

template<class T, class T_Step>
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
RangeIdManager(RangeIdManager<T, T_Step>&& other)
    : freeIds_        (std::move(other.freeIds_)),
      reservedIds_    (std::move(other.reservedIds_)),
      idRange_        (std::move(other.idRange_)),
      step_           (std::move(other.step_)),
      size_           (std::move(other.size_)),
      isHardStep_     (std::move(other.isHardStep_)),
      idIssuingMethod_(std::move(other.idIssuingMethod_))
{
    other.size_ = 0;
}

template<class T, class T_Step>
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
~RangeIdManager() {}

template<class T, class T_Step>
std::optional<T>
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
getFreeId()
{
    if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
        !idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
        return activateBothBorders();
    }

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (idRange_.getBorderValue(BorderRange::LowerBorder) > idRange_.getStart()) {
            auto result = idRange_.moveBorder(BorderRange::LowerBorder, 1);

            if (!(result.flags & IDRF_ID_OUT_OF_LIMIT)) {
                ++size_;
                expandRangeIfPossible(BorderRange::LowerBorder);
                return result.value;
            }
        }

        if (idRange_.getBorderValue(BorderRange::UpperBorder) < idRange_.getStart()) {
            auto result = idRange_.moveBorder(BorderRange::UpperBorder, 1);

            if (!(result.flags & IDRF_ID_OUT_OF_LIMIT)) {
                ++size_;
                expandRangeIfPossible(BorderRange::UpperBorder);
                return result.value;
            }
        }

        if (freeIds_.size()) {
            ++size_;
            return *freeIds_.getNextId();
        }

        return getNextId();
    }

    if (idIssuingMethod_ == IdIssuingMethod::Static_Ascending) {
        if (!idRange_.getBorderState(BorderRange::LowerBorder)) {
            idRange_.setBorderState(BorderRange::LowerBorder, true);
            ++size_;
            return idRange_.getBorderValue(BorderRange::LowerBorder);
        }

        if (freeIds_.size()) {
            ++size_;
            return *freeIds_.getNextId();
        }

        if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
            idRange_.setBorderState(BorderRange::UpperBorder, true);
            ++size_;
            return idRange_.getBorderValue(BorderRange::UpperBorder);
        }

        return getNextId();
    }

    if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
        idRange_.setBorderState(BorderRange::UpperBorder, true);
        ++size_;
        return idRange_.getBorderValue(BorderRange::UpperBorder);
    }

    if (freeIds_.size()) {
        ++size_;
        return *freeIds_.getNextId();
    }

    if (!idRange_.getBorderState(BorderRange::LowerBorder)) {
        idRange_.setBorderState(BorderRange::LowerBorder, true);
        ++size_;
        return idRange_.getBorderValue(BorderRange::LowerBorder);
    }

    return getNextId();
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
reserve(T id, ReservationMethod reservationMethod)
{
    if (id > idRange_.getBorderLimit(BorderRange::UpperBorder) || id < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return false;

    if (!isStandardId(id)) {
        if (isHardStep_)
            return false;

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

        activateBothBorders();
        return true;
    }

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            !idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
            auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

            if (id == idInfo.value && !(idInfo.flags & IDRF_ID_OUT_OF_LIMIT)) {
                if (!jumpOver(idInfo.value))
                    return false;

                activateBothBordersWithExpending();
                return true;
            }

            idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

            if (id == idInfo.value && !(idInfo.flags & IDRF_ID_OUT_OF_LIMIT)) {
                if (!jumpOver(idInfo.value))
                    return false;

                activateBothBordersWithExpending();
                return true;
            }
        }

        if (id == idRange_.getBorderValue(BorderRange::UpperBorder) || id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return false;
    }
    else {
        if (id == idRange_.getBorderValue(BorderRange::UpperBorder))
            return reserveBorderRange(BorderRange::UpperBorder);

        if (id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return reserveBorderRange(BorderRange::LowerBorder);
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
        return reserveIdInRange(id);

    if (reservedIds_.find(id))
        return false;

    if (moveBorder(BorderRange::UpperBorder, id))
        return true;

    if (moveBorder(BorderRange::LowerBorder, id))
        return true;

    reservedIds_.add(id);
    ++size_;
    return true;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
free(T id)
{
    if (id > idRange_.getBorderLimit(BorderRange::UpperBorder) || id < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return false;

    if (!isStandardId(id)) {
        if (isHardStep_)
            return false;

        if (!reservedIds_.find(id))
            return false;

        reservedIds_.erase(id);
        --size_;
        return true;
    }

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder) && id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (!idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder))
            return false;

        idRange_.setBorderState(BorderRange::UpperBorder, false);
        idRange_.setBorderState(BorderRange::LowerBorder, false);

        --size_;
        return true;
    }

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (id == idRange_.getBorderValue(BorderRange::UpperBorder)) {
            auto idInfo = reduceRangeIfPossible(BorderRange::UpperBorder);

            if (id == idInfo.value && (idInfo.flags & IDRF_RANGE_ARE_BENT))
                return false;

            --size_;
            return true;
        }

        if (id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
            auto idInfo = reduceRangeIfPossible(BorderRange::LowerBorder);

            if (id == idInfo.value && (idInfo.flags & IDRF_RANGE_ARE_BENT))
                return false;

            --size_;
            return true;
        }
    }
    else {
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
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder)) {
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
void
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
freeAll()
{
    freeIds_.clear();
    reservedIds_.clear();
    idRange_.reset();
    size_ = 0;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
find(T id) const
{
    if (id > idRange_.getBorderLimit(BorderRange::UpperBorder) || id < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return false;

    if (!isStandardId(id)) {
        if (isHardStep_)
            return false;

        return reservedIds_.find(id);
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
        return !freeIds_.find(id);

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder))
        return idRange_.getBorderState(BorderRange::UpperBorder);

    if (id == idRange_.getBorderValue(BorderRange::LowerBorder))
        return idRange_.getBorderState(BorderRange::LowerBorder);

    return reservedIds_.find(id);
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
setBorderLimit(BorderRange borderRange, T value)
{
    if (borderRange == BorderRange::UpperBorder) {
        if (value > idRange_.getBorderLimit(BorderRange::UpperBorder))
            return idRange_.setBorderLimit(BorderRange::UpperBorder, value);

        if (value < idRange_.getBorderValue(BorderRange::UpperBorder))
            return false;
    }
    else {
        if (value < idRange_.getBorderLimit(BorderRange::LowerBorder))
            return idRange_.setBorderLimit(BorderRange::LowerBorder, value);

        if (value > idRange_.getBorderValue(BorderRange::LowerBorder))
            return false;
    }

    if (value == idRange_.getBorderLimit(borderRange))
        return true;

    T id = 0;

    for (size_t i = 0; i < reservedIds_.size();) {
        id = *reservedIds_.findByIndex(i);

        if ((id > value && borderRange == BorderRange::UpperBorder) ||
            (id < value && borderRange == BorderRange::LowerBorder)) {

            reservedIds_.erase(id);
            --size_;
            continue;
        }

        ++i;
    }

    if (idRange_.setBorderLimit(borderRange, value))
        return true;

    throw std::runtime_error(
                "Where: ONF::RangeIdManager::setBorderLimit\n"
                "Message: Failed to set a new Limit, and all IDs larger than the new Limit were deleted\n"
                "UpperBorder limit: " + std::to_string(idRange_.getBorderLimit(BorderRange::UpperBorder)) + "\n"
                "LowerBorder limit: " + std::to_string(idRange_.getBorderLimit(BorderRange::LowerBorder)) + "\n"
                "UpperBorder value: " + std::to_string(idRange_.getBorderValue(BorderRange::UpperBorder)) + "\n"
                "LowerBorder value: " + std::to_string(idRange_.getBorderValue(BorderRange::LowerBorder)) + "\n"
                "BorderRange: " + std::to_string(static_cast<int>(borderRange)) + "\n"
                "value: " + std::to_string(value) + "\n"
          );
}

template<class T, class T_Step>
T
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
getBorderLimit(BorderRange borderRange) const
{
    return idRange_.getBorderLimit(borderRange);
}

template<class T, class T_Step>
void
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
setHardStep(bool value)
{
    if (value == isHardStep_)
        return;

    isHardStep_ = value;

    if (!value)
        return;

    T id = 0;

    for (size_t i = 0; i < reservedIds_.size();) {
        id = *reservedIds_.findByIndex(i);

        if (!isStandardId(id)) {
            reservedIds_.erase(id);
            --size_;
            continue;
        }

        ++i;
    }
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
isHardStep() const
{
    return isHardStep_;
}

template<class T, class T_Step>
void
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
setIdIssuingMethod(IdIssuingMethod idIssuingMethod)
{
    if (idIssuingMethod == idIssuingMethod_)
        return;

    freeIds_.setIdIssuingMethod(idIssuingMethod);

    if ((idIssuingMethod_ == IdIssuingMethod::Static_Ascending || idIssuingMethod_ == IdIssuingMethod::Static_Descending) &&
        (idIssuingMethod == IdIssuingMethod::Static_Ascending || idIssuingMethod == IdIssuingMethod::Static_Descending)) {

        idIssuingMethod_ = idIssuingMethod;
        return;
    }

    idIssuingMethod_ = idIssuingMethod;

    if (idIssuingMethod == IdIssuingMethod::Dynamic) {
        normalizeBorderRange(BorderRange::UpperBorder);
        normalizeBorderRange(BorderRange::LowerBorder);
        return;
    }

    if (idRange_.getBorderValue(BorderRange::UpperBorder) < idRange_.getStart()) {
        normalizeBorderRange(BorderRange::UpperBorder);
        return;
    }

    if (idRange_.getBorderValue(BorderRange::LowerBorder) > idRange_.getStart()) {
        normalizeBorderRange(BorderRange::LowerBorder);
        return;
    }
}

template<class T, class T_Step>
ONF::IdIssuingMethod
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
getIdIssuingMethod() const
{
    return idIssuingMethod_;
}

template<class T, class T_Step>
size_t
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
size() const
{
    return size_;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
isStandardId(T id) const
{
    return ONF::isStandardId(static_cast<ldouble>(id), static_cast<ldouble>(idRange_.getStart()), static_cast<ldouble>(step_));
}

template<class T, class T_Step>
T
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
getStart() const
{
    return idRange_.getStart();
}

template<class T, class T_Step>
T_Step
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
getStep() const
{
    return step_;
}

template<class T, class T_Step>
T
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
getBorderValue(BorderRange borderRange) const
{
    return idRange_.getBorderValue(borderRange);
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
getBorderState(BorderRange borderRange) const
{
    return idRange_.getBorderState(borderRange);
}

template<class T, class T_Step>
T
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
findNearestStdId(T id, BorderRange borderRange) const
{
    return ONF::findNearestStdId(
                static_cast<ldouble>(id),
                static_cast<ldouble>(idRange_.getBorderValue(borderRange)),
                static_cast<ldouble>(step_)
           );
}

template<class T, class T_Step>
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>&
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
operator=(const RangeIdManager<T, T_Step>& other)
{
    freeIds_         = other.freeIds_;
    reservedIds_     = other.reservedIds_;
    idRange_         = other.idRange_;
    step_            = other.step_;
    size_            = other.size_;
    isHardStep_      = other.isHardStep_;
    idIssuingMethod_ = other.idIssuingMethod_;

    return *this;
}

template<class T, class T_Step>
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>&
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
operator=(RangeIdManager<T, T_Step>&& other)
{
    freeIds_         = std::move(other.freeIds_);
    reservedIds_     = std::move(other.reservedIds_);
    idRange_         = std::move(other.idRange_);
    step_            = std::move(other.step_);
    size_            = std::move(other.size_);
    isHardStep_      = std::move(other.isHardStep_);
    idIssuingMethod_ = std::move(other.idIssuingMethod_);

    other.size_ = 0;

    return *this;
}


template<class T, class T_Step>
size_t
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
getFreeIdsSize() const
{
    return freeIds_.size();
}

template<class T, class T_Step>
size_t
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
getReservedIdsSize() const
{
    return reservedIds_.size();
}


template<class T, class T_Step>
std::optional<T>
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
getNextId()
{
    if (step_ > 0) {
        auto result = idRange_.moveBorder(BorderRange::UpperBorder, 1);

        if (result.flags & IDRF_ID_OUT_OF_LIMIT)
            return std::nullopt;

        ++size_;
        expandRangeIfPossible(BorderRange::UpperBorder);
        return result.value;
    }

    if (step_ < 0) {
        auto result = idRange_.moveBorder(BorderRange::LowerBorder, 1);

        if (result.flags & IDRF_ID_OUT_OF_LIMIT)
            return std::nullopt;

        ++size_;
        expandRangeIfPossible(BorderRange::LowerBorder);
        return result.value;
    }
}

template<class T, class T_Step>
typename ONF::IdRange<T>::IdInfo
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
expandRangeIfPossible(BorderRange border)
{
    typename IdRange<T>::IdInfo idInfo;
    dlong i = 1;

    while (true) {
        idInfo = idRange_.getIdInfo(border, i);

        if (idInfo.flags & IDRF_ID_OUT_OF_LIMIT) {
            idRange_.moveBorder(border, i - 1);
            return idInfo;
        }

        if (reservedIds_.find(idInfo.value)) {
            reservedIds_.erase(idInfo.value);
            ++i;
            continue;
        }

        idRange_.moveBorder(border, i - 1);
        return idInfo;
    }
}

template<class T, class T_Step>
typename ONF::IdRange<T>::IdInfo
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
reduceRangeIfPossible(BorderRange border)
{
    typename IdRange<T>::IdInfo idInfo;
    dlong i = 1;

    while (true) {
        idInfo = idRange_.getIdInfo(border, -i);

        if (idInfo.flags & IDRF_RANGE_ARE_BENT)
            return idInfo;

        if (freeIds_.find(idInfo.value)) {
            freeIds_.erase(idInfo.value);
            ++i;
            continue;
        }

        idRange_.moveBorder(border, -i);
        return idInfo;
    }
}

template<class T, class T_Step>
T
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
activateBothBorders()
{
    idRange_.setBorderState(BorderRange::UpperBorder, true);
    idRange_.setBorderState(BorderRange::LowerBorder, true);

    ++size_;

    return idRange_.getBorderValue(BorderRange::UpperBorder);
}

template<class T, class T_Step>
T
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
activateBothBordersWithExpending()
{
    idRange_.setBorderState(BorderRange::UpperBorder, true);
    idRange_.setBorderState(BorderRange::LowerBorder, true);

    T id = idRange_.getBorderValue(BorderRange::UpperBorder);
    ++size_;

    expandRangeIfPossible(BorderRange::UpperBorder);
    expandRangeIfPossible(BorderRange::LowerBorder);

    return id;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
jumpOver(T id)
{
    if (id == idRange_.getBorderValue(BorderRange::UpperBorder))
        return true;

    BorderRange borderRange = getExpandableBorderRange(id);
    T borderRangeBackup = idRange_.getBorderValue(borderRange);

    if (!idRange_.setBorderValue(borderRange, id))
        return false;

    if (borderRange == BorderRange::UpperBorder) {
        if (idRange_.setBorderValue(BorderRange::LowerBorder, id))
            return true;
    }

    if (idRange_.setBorderValue(BorderRange::UpperBorder, id))
        return true;

    /*
     * Если мы здесь, значит границам не удалось перепрыгнуть на id.
     * Далее идет попытка восстановления. В случае провала кидаем исключение.
     */

    if (idRange_.setBorderValue(borderRange, borderRangeBackup))
        return false;

    throw std::runtime_error(
            "Where: ONF::RangeIdManager::jumpOver\n"
            "Message: There was some kind of error in which it is impossible to return the border back\n"
            "UpperBorder value: " + std::to_string(idRange_.getBorderValue(BorderRange::UpperBorder)) + "\n"
            "LowerBorder value: " + std::to_string(idRange_.getBorderValue(BorderRange::LowerBorder)) + "\n"
            "BorderRange: " + std::to_string(static_cast<int>(borderRange)) + "\n"
            "BorderRange backup: " + std::to_string(borderRangeBackup) + "\n"
            "id: " + std::to_string(id) + "\n"
          );
}

template<class T, class T_Step>
unsigned
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
normalizeBorderRange(BorderRange borderRange)
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder))
            return IDRF_SUCCESSFULLY;

        if (idRange_.getBorderState(borderRange))
            return IDRF_SUCCESSFULLY;

        idRange_.setBorderState(borderRange, true);
        return reduceRangeIfPossible(borderRange).flags;
    }

    typename IdRange<T>::IdInfo idInfo;
    std::optional<T> lastId;

    while (true) {
        idInfo = idRange_.getIdInfo(borderRange, 1);

        if (idInfo.flags & IDRF_ID_OUT_OF_LIMIT)
            return idInfo.flags;

        if ((idInfo.value > idRange_.getStart() && borderRange == BorderRange::UpperBorder) ||
            (idInfo.value < idRange_.getStart() && borderRange == BorderRange::LowerBorder))
            return idInfo.flags;

        if (lastId.has_value()) {
            freeIds_.add(*lastId);
            lastId.reset();
        }

        idRange_.moveBorder(borderRange, 1);

        if (reservedIds_.find(idInfo.value)) {
            idRange_.setBorderState(borderRange, true);
            reservedIds_.erase(idInfo.value);
        }
        else {
            idRange_.setBorderState(borderRange, false);
            lastId = idInfo.value;
        }
    }

    return IDRF_SUCCESSFULLY;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
reserveIdInRange(T id)
{
    if (isStandardId(id)) {
        if (!freeIds_.find(id))
            return false;

        freeIds_.erase(id);
        ++size_;
        return true;
    }

    if (reservedIds_.find(id))
        return false;

    reservedIds_.add(id);
    ++size_;
    return true;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
reserveBorderRange(BorderRange borderRange)
{
    if (idRange_.getBorderState(borderRange))
        return false;

    idRange_.setBorderState(borderRange, true);
    ++size_;
    return true;
}

template<class T, class T_Step>
ONF::BorderRange
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
getExpandableBorderRange(T id) const
{
    return (id > idRange_.getBorderValue(BorderRange::UpperBorder)) ? BorderRange::UpperBorder : BorderRange::LowerBorder;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
moveBorder(BorderRange borderRange, T id)
{
    auto idInfo = idRange_.getIdInfo(borderRange, 1);

    if (idInfo.value != id || (idInfo.flags & IDRF_ID_OUT_OF_LIMIT))
        return false;

    if (idIssuingMethod_ != IdIssuingMethod::Dynamic) {
        /*
         * Так как мы передвигаем границу на зарезервированный ID надо озаботится тем
         * чтобы в статическом режиме граница была включена когда мы ее передвиним
         * на этот ID.
         */
        if (!idRange_.getBorderState(borderRange)) {
            idRange_.setBorderState(borderRange, true);

            /*
             * Если UpperBorder == LowerBorder и мы, например, передвигаем UpperBorder,
             * то LowerBorder останется на прежнем месте и ID на котором она стоит
             * находится под ее ответственностью. Это значит что такой ID не должен
             * быть во freeIds_. А если UpperBorder != LowerBorder то после перемещения
             * UpperBorder, ID на котором она до сих пор стояла останется не занесенной
             * в список freeIds_. Такой ID будет считаться зарезервированым, что неверно,
             * так как мы проверили это выше.
             * Потому данная проверка необходима.
             */
            if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
                freeIds_.add(idRange_.getBorderValue(borderRange));
        }
    }

    idRange_.moveBorder(borderRange, 1);
    expandRangeIfPossible(borderRange);
    ++size_;
    return true;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
interpolateIds(T id)
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            !idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {

            //UpperBorder value == LowerBorder value
            if (id == idRange_.getBorderValue(BorderRange::UpperBorder)) {
                activateBothBorders();
                return true;
            }

            if (reservedIds_.find(id))
                return false;

            if (!jumpOver(id))
                return false;

            activateBothBordersWithExpending();
            return true;
        }

        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
            return reserveIdInRange(id);

        if (id == idRange_.getBorderValue(BorderRange::UpperBorder) || id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return false;

        if (reservedIds_.find(id))
            return false;

        BorderRange borderRange = getExpandableBorderRange(id);
        typename IdRange<T>::IdInfo idInfo;

        while (true) {
            idInfo = idRange_.moveBorder(borderRange, 1);

            if (idInfo.value == id)
                break;

            if (reservedIds_.find(idInfo.value)) {
                reservedIds_.erase(idInfo.value);
            }
            else {
                freeIds_.add(idInfo.value);
            }
        }

        ++size_;
        expandRangeIfPossible(borderRange);
        return true;
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
        return reserveIdInRange(id);

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder) && id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (idRange_.getBorderState(BorderRange::UpperBorder) && idRange_.getBorderState(BorderRange::LowerBorder))
            return false;

        activateBothBorders();
        return true;
    }

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder))
        return reserveBorderRange(BorderRange::UpperBorder);

    if (id == idRange_.getBorderValue(BorderRange::LowerBorder))
        return reserveBorderRange(BorderRange::LowerBorder);

    if (reservedIds_.find(id))
        return false;

    BorderRange borderRange = getExpandableBorderRange(id);

    if (!idRange_.getBorderState(borderRange)) {
        idRange_.setBorderState(borderRange, true);

        if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
            freeIds_.add(idRange_.getBorderValue(borderRange));
    }

    typename IdRange<T>::IdInfo idInfo;

    while (true) {
        idInfo = idRange_.moveBorder(borderRange, 1);

        if (idInfo.value == id)
            break;

        if (reservedIds_.find(idInfo.value)) {
            reservedIds_.erase(idInfo.value);
        }
        else {
            freeIds_.add(idInfo.value);
        }
    }

    ++size_;
    expandRangeIfPossible(borderRange);
    return true;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
reserveIds(T id)
{
    if (id == idRange_.getBorderValue(BorderRange::UpperBorder) && id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (idRange_.getBorderState(BorderRange::UpperBorder) && idRange_.getBorderState(BorderRange::LowerBorder))
            return false;

        activateBothBorders();
        return true;
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
        return reserveIdInRange(id);

    if (reservedIds_.find(id))
        return false;

    BorderRange borderRange = getExpandableBorderRange(id);

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (id == idRange_.getBorderValue(BorderRange::UpperBorder) || id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return false;

        if (!idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder))
            activateBothBorders();
    }
    else {
        if (id == idRange_.getBorderValue(BorderRange::UpperBorder))
            return reserveBorderRange(BorderRange::UpperBorder);

        if (id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return reserveBorderRange(BorderRange::LowerBorder);

        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder)) {
            if (!idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder))
                activateBothBorders();
        }
        else {
            if (!idRange_.getBorderState(borderRange))
                reserveBorderRange(borderRange);
        }
    }

    typename IdRange<T>::IdInfo idInfo;

    while (true) {
        idInfo = idRange_.getIdInfo(borderRange, 1);

        if (idInfo.flags & IDRF_ID_OUT_OF_LIMIT)
            break;

        if ((idInfo.value > id && borderRange == BorderRange::UpperBorder) ||
            (idInfo.value < id && borderRange == BorderRange::LowerBorder))
            break;

        if (reservedIds_.find(idInfo.value)) {
            reservedIds_.erase(idInfo.value);
        }
        else {
            ++size_;
        }

        idRange_.moveBorder(borderRange, 1);

        if (idInfo.value == id)
            break;
    }

    expandRangeIfPossible(borderRange);

    if (!isStandardId(id)) {
        reservedIds_.add(id);
        ++size_;
    }

    return true;
}
