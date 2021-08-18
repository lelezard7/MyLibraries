#include "../IdManagement.h"

#include <vector>

using ONF::is_forbidden_types_combination;


template<class T, class T_Step>
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
RangeIdManager(T start, T_Step step)
    : idRange_        (start, ONF::abs(step)),
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

            T id = idRange_.getBorderValue(BorderRange::LowerBorder);
            ++size_;
            return id;
        }

        if (freeIds_.size()) {
            ++size_;
            return *freeIds_.getNextId();
        }

        if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
            idRange_.setBorderState(BorderRange::UpperBorder, true);

            T id = idRange_.getBorderValue(BorderRange::UpperBorder);
            ++size_;
            return id;
        }

        return getNextId();
    }

    if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
        idRange_.setBorderState(BorderRange::UpperBorder, true);

        T id = idRange_.getBorderValue(BorderRange::UpperBorder);
        ++size_;
        return id;
    }

    if (freeIds_.size()) {
        ++size_;
        return *freeIds_.getNextId();
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
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
reserve(T id, ReservationMethod reservationMethod)
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

            activateBothBorders();
            return true;
        }

        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            !idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
            auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

            if (id == idInfo.value && !(idInfo.flags & IDRF_ID_OUT_OF_LIMIT)) {
                if (!jumpOver(idInfo.value, BorderRange::UpperBorder))
                    return false;

                activateBothBordersWithExpending();
                return true;
            }

            idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

            if (id == idInfo.value && !(idInfo.flags & IDRF_ID_OUT_OF_LIMIT)) {
                if (!jumpOver(idInfo.value, BorderRange::LowerBorder))
                    return false;

                activateBothBordersWithExpending();
                return true;
            }
        }

        if (id == idRange_.getBorderValue(BorderRange::UpperBorder) || id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return false;

        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
            return reserveIdInRange(id);

        if (reservedIds_.find(id))
            return false;

        auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

        if (idInfo.value == id && !(idInfo.flags & IDRF_ID_OUT_OF_LIMIT)) {
            idRange_.moveBorder(BorderRange::UpperBorder, 1);
            ++size_;

            expandRangeIfPossible(BorderRange::UpperBorder);
            return true;
        }

        idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

        if (idInfo.value == id && !(idInfo.flags & IDRF_ID_OUT_OF_LIMIT)) {
            idRange_.moveBorder(BorderRange::LowerBorder, 1);
            ++size_;

            expandRangeIfPossible(BorderRange::LowerBorder);
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

        activateBothBorders();
        return true;
    }

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder))
        return reserveBorderRange(BorderRange::UpperBorder);

    if (id == idRange_.getBorderValue(BorderRange::LowerBorder))
        return reserveBorderRange(BorderRange::LowerBorder);

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
        return reserveIdInRange(id);

    if (reservedIds_.find(id))
        return false;

    auto idInfo = idRange_.getIdInfo(BorderRange::UpperBorder, 1);

    if (id == idInfo.value && !(idInfo.flags & IDRF_ID_OUT_OF_LIMIT)) {
        if (!idRange_.getBorderState(BorderRange::UpperBorder)) {
            idRange_.setBorderState(BorderRange::UpperBorder, true);

            if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
                freeIds_.add(idRange_.getBorderValue(BorderRange::UpperBorder));
        }

        idRange_.moveBorder(BorderRange::UpperBorder, 1);
        ++size_;

        expandRangeIfPossible(BorderRange::UpperBorder);
        return true;
    }

    idInfo = idRange_.getIdInfo(BorderRange::LowerBorder, 1);

    if (id == idInfo.value && !(idInfo.flags & IDRF_ID_OUT_OF_LIMIT)) {
        if (!idRange_.getBorderState(BorderRange::LowerBorder)) {
            idRange_.setBorderState(BorderRange::LowerBorder, true);

            if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
                freeIds_.add(idRange_.getBorderValue(BorderRange::LowerBorder));
        }

        idRange_.moveBorder(BorderRange::LowerBorder, 1);
        ++size_;

        expandRangeIfPossible(BorderRange::LowerBorder);
        return true;
    }

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

    std::vector<T> buffer;
    T id = 0;

    for (size_t i = 0; i < reservedIds_.size();) {
        id = *reservedIds_.findByIndex(i);

        if ((id > value && borderRange == BorderRange::UpperBorder) || (id < value && borderRange == BorderRange::LowerBorder)) {
            reservedIds_.erase(id);
            buffer.push_back(id);
            continue;
        }

        ++i;
    }

    if (!idRange_.setBorderLimit(borderRange, value)) {
        for (size_t i = 0; i < buffer.size(); ++i)
            reservedIds_.add(buffer[i]);

        return false;
    }

    size_ -= buffer.size();
    return true;
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
        if (normalizeBorderRange(BorderRange::UpperBorder) == IDRF_RANGE_ARE_BENT ||
            normalizeBorderRange(BorderRange::LowerBorder) == IDRF_RANGE_ARE_BENT) {

            idRange_.setBorderState(BorderRange::UpperBorder, false);
            idRange_.setBorderState(BorderRange::LowerBorder, false);
        }

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
std::optional<T>
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
findClosestStdId(T id) const
{
    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
        return std::nullopt;

    if (isStandardId(id))
        return id;

    IdRange<T> idRange(idRange_.getStart(), idRange_.getStep());

    if (!idRange.setBorderValue(BorderRange::UpperBorder, idRange_.getBorderValue(BorderRange::UpperBorder)) ||
        !idRange.setBorderValue(BorderRange::LowerBorder, idRange_.getBorderValue(BorderRange::LowerBorder)))
        return std::nullopt;

    BorderRange borderRange = getExpandableBorderRange(id);
    typename IdRange<T>::IdInfo idInfo;
    size_t i = 1;

    while (true) {
        idInfo = idRange.getIdInfo(borderRange, i);

        if (idInfo.flags & IDRF_ID_OUT_OF_LIMIT)
            return idInfo.value;

        if ((id < idInfo.value && borderRange == BorderRange::UpperBorder) ||
            (id > idInfo.value && borderRange == BorderRange::LowerBorder)) {
            return idRange.getIdInfo(borderRange, i - 1).value;
        }

        ++i;
    }
}

template<class T, class T_Step>
std::optional<T>
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
findClosestStdId(T id, BorderRange borderRange) const
{
    if (id > idRange_.getBorderValue(BorderRange::UpperBorder) || id < idRange_.getBorderValue(BorderRange::LowerBorder))
        return std::nullopt;

    if (isStandardId(id))
        return id;

    typename IdRange<T>::IdInfo idInfo;
    size_t i = 1;

    while (true) {
        idInfo = idRange_.getIdInfo(borderRange, -i);

        if ((id > idInfo.value && borderRange == BorderRange::UpperBorder) ||
            (id < idInfo.value && borderRange == BorderRange::LowerBorder)) {
            return idRange_.getIdInfo(borderRange, -(i - 1)).value;
        }

        ++i;
    }
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

    throw std::runtime_error("---------");
}

/*
 * TODO: Проверить какой способ перемещения границы быстрее: expandRangeIfPossible или reduceRangeIfPossible
 *
 * В expandRangeIfPossible после каждого getIdInfo мы подтягиваем границу с помощью moveBorder,
 * а это 2 вызова почти одной и той же функции для захвата одного id.
 * Если нам нужно передвинуть границу на 6 id, expandRange вызовет getIdInfo и moveBorder
 * в сумме 12 раз.
 *
 * reduceRangeIfPossible подтягивает границу в самом конце. Если нам нужно передвинуть границу на все те же 6 id,
 * reduceRange вызовет getIdInfo и moveBorder в сумме 7 раз. Это меньше чем в expandRange, но быстрее ли это?
 * getIdInfo и moveBorder в reduceRangeIfPossible будут вынуждены работать с более большими i (от 1 до limit) нежели в expandRangeIfPossible
 * где getIdInfo и moveBorder всегда передвигаются на 1.
 */

template<class T, class T_Step>
typename ONF::IdRange<T>::IdInfo
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
expandRangeIfPossible(BorderRange border)
{
    typename IdRange<T>::IdInfo idInfo;

    while (true) {
        idInfo = idRange_.getIdInfo(border, 1);

        if (idInfo.flags & IDRF_ID_OUT_OF_LIMIT)
            return idInfo;

        if (reservedIds_.find(idInfo.value)) {
            reservedIds_.erase(idInfo.value);
            idRange_.moveBorder(border, 1);
            continue;
        }

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
interpolateIds(T id)
{
    if (id > idRange_.getBorderLimit(BorderRange::UpperBorder) || id < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return false;

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder) &&
            !idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {

            if (isStandardId(id)) {
                if (id == idRange_.getBorderValue(BorderRange::UpperBorder)) {  // UpperBorder == LowerBorder
                    activateBothBorders();
                    return true;
                }

                if (id > idRange_.getBorderValue(BorderRange::UpperBorder))
                    if (!jumpOver(id, BorderRange::UpperBorder))
                        return false;

                if (id < idRange_.getBorderValue(BorderRange::LowerBorder))
                    if (!jumpOver(id, BorderRange::LowerBorder))
                        return false;

                idRange_.setBorderState(BorderRange::UpperBorder, true);
                idRange_.setBorderState(BorderRange::LowerBorder, true);

                expandRangeIfPossible(BorderRange::UpperBorder);
                expandRangeIfPossible(BorderRange::LowerBorder);

                if (reservedIds_.find(id)) {
                    reservedIds_.erase(id);
                }
                else {
                    ++size_;
                }

                return true;
            }


            if (reservedIds_.find(id))
                return false;

            T standardId = *findClosestStdId(id);

            if (standardId == idRange_.getBorderValue(BorderRange::UpperBorder) ||
                standardId == idRange_.getBorderValue(BorderRange::LowerBorder)) {

                reservedIds_.add(id);
                ++size_;

                activateBothBordersWithExpending();
                return true;
            }

            if (id > idRange_.getBorderValue(BorderRange::UpperBorder))
                if (!jumpOver(standardId, BorderRange::UpperBorder))
                    return false;

            if (id < idRange_.getBorderValue(BorderRange::LowerBorder))
                if (!jumpOver(standardId, BorderRange::LowerBorder))
                    return false;

            activateBothBordersWithExpending();
            reservedIds_.add(id);

            if (reservedIds_.find(standardId)) {
                reservedIds_.erase(standardId);
            }
            else {
                ++size_;
            }

            return true;
        }


        if (reservedIds_.find(id))
            return 0;

        if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
            return reserveIdInRange(id);

        if (isStandardId(id)) {
            if (id == idRange_.getBorderValue(BorderRange::UpperBorder) || id == idRange_.getBorderValue(BorderRange::LowerBorder))
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


        BorderRange borderRange = getExpandableBorderRange(id);

        if (idRange_.getIdInfo(borderRange, 1).flags & IDRF_SUCCESSFULLY) {
            if ((id > idRange_.getBorderValue(BorderRange::UpperBorder) && id < idRange_.getIdInfo(BorderRange::UpperBorder, 1).value) ||
                (id < idRange_.getBorderValue(BorderRange::LowerBorder) && id > idRange_.getIdInfo(BorderRange::LowerBorder, 1).value)) {

                reservedIds_.add(id);
                ++size_;
                return true;
            }
        }

        typename IdRange<T>::IdInfo idInfo;
        std::optional<T> lastId;

        while (true) {
            idInfo = idRange_.getIdInfo(borderRange, 1);

            if (idInfo.flags & IDRF_ID_OUT_OF_LIMIT)
                break;

            if ((idInfo.value > id && borderRange == BorderRange::UpperBorder) ||
                (idInfo.value < id && borderRange == BorderRange::LowerBorder))
                break;

            if (lastId.has_value()) {
                freeIds_.add(*lastId);
            }

            idRange_.moveBorder(borderRange, 1);

            if (reservedIds_.find(idInfo.value)) {
                reservedIds_.erase(idInfo.value); //TODO: test
            }
            else {
                lastId = idInfo.value;
            }
        }

        reservedIds_.add(id);
        size_ += 2;

        expandRangeIfPossible(borderRange);
        return true;
    }


    // ----------------------------------

    if (reservedIds_.find(id))
        return false;

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder) && id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (idRange_.getBorderState(BorderRange::UpperBorder) && idRange_.getBorderState(BorderRange::LowerBorder))
            return false;

        activateBothBorders();
        return true;
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
        return reserveIdInRange(id);

    if (isStandardId(id)) {
        if (id == idRange_.getBorderValue(BorderRange::UpperBorder))
            return reserveBorderRange(BorderRange::UpperBorder);

        if (id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return reserveBorderRange(BorderRange::LowerBorder);

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

    BorderRange borderRange = getExpandableBorderRange(id);

    if (idRange_.getIdInfo(borderRange, 1).flags & IDRF_SUCCESSFULLY) {
        if ((id > idRange_.getBorderValue(BorderRange::UpperBorder) && id < idRange_.getIdInfo(BorderRange::UpperBorder, 1).value) ||
            (id < idRange_.getBorderValue(BorderRange::LowerBorder) && id > idRange_.getIdInfo(BorderRange::LowerBorder, 1).value)) {

            reservedIds_.add(id);
            ++size_;
            return true;
        }
    }

    if (!idRange_.getBorderState(borderRange)) {
        if (idRange_.getBorderValue(BorderRange::UpperBorder) != idRange_.getBorderValue(BorderRange::LowerBorder))
            freeIds_.add(idRange_.getBorderValue(borderRange)); //TODO: test
    }

    typename IdRange<T>::IdInfo idInfo;
    std::optional<T> lastId;

    while (true) {
        idInfo = idRange_.getIdInfo(borderRange, 1);

        if (idInfo.flags & IDRF_ID_OUT_OF_LIMIT)
            break;

        if ((idInfo.value > id && borderRange == BorderRange::UpperBorder) ||
            (idInfo.value < id && borderRange == BorderRange::LowerBorder))
            break;

        if (lastId.has_value()) {
            freeIds_.add(*lastId);
        }

        if (reservedIds_.find(idInfo.value)) {
            reservedIds_.erase(idInfo.value);
            idRange_.setBorderState(borderRange, true);
        }
        else {
            lastId = idInfo.value;
            idRange_.setBorderState(borderRange, false);
        }

        idRange_.moveBorder(borderRange, 1);
    }

    reservedIds_.add(id);
    ++size_;

    expandRangeIfPossible(borderRange);
    return true;
}

template<class T, class T_Step>
bool
ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>::
reserveIds(T id)
{
    if (id > idRange_.getBorderLimit(BorderRange::UpperBorder) || id < idRange_.getBorderLimit(BorderRange::LowerBorder))
        return false;

    if (reservedIds_.find(id))
        return false;

    if (id == idRange_.getBorderValue(BorderRange::UpperBorder) && id == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (idRange_.getBorderState(BorderRange::UpperBorder) && idRange_.getBorderState(BorderRange::LowerBorder))
            return false;

        activateBothBorders();
        return true;
    }

    if (id < idRange_.getBorderValue(BorderRange::UpperBorder) && id > idRange_.getBorderValue(BorderRange::LowerBorder))
        return reserveIdInRange(id);

    BorderRange borderRange = getExpandableBorderRange(id);

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (id == idRange_.getBorderValue(BorderRange::UpperBorder) || id == idRange_.getBorderValue(BorderRange::LowerBorder))
            return false;

        typename IdRange<T>::IdInfo idInfo;

        if (isStandardId(id)) {
            if (!idRange_.getBorderState(borderRange)) {
                idInfo = idRange_.getIdInfo(borderRange, 0);

                if (reservedIds_.find(idInfo.value)) {
                    reservedIds_.erase(idInfo.value);
                }
                else {
                    ++size_;
                }
            }

            do {
                idInfo = idRange_.moveBorder(borderRange, 1);

                if (reservedIds_.find(idInfo.value)) {
                    reservedIds_.erase(idInfo.value);
                }
                else {
                    ++size_;
                }

            } while (idInfo.value != id);

            idRange_.setBorderState(BorderRange::UpperBorder, true);
            idRange_.setBorderState(BorderRange::LowerBorder, true);

            expandRangeIfPossible(BorderRange::UpperBorder);
            expandRangeIfPossible(BorderRange::LowerBorder);

            return true;
        }

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
        }

        //      ub---->\
        // .....lb.....@...
        //ub и lb могут быть на старте и при перемещении одной из границ обе активируются,
        //а потому expandRangeIfPossible делаем с обоими границами.
        activateBothBordersWithExpending();

        reservedIds_.add(id);
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

    if (idRange_.getBorderValue(BorderRange::UpperBorder) == idRange_.getBorderValue(BorderRange::LowerBorder)) {
        if (!idRange_.getBorderState(BorderRange::UpperBorder) && !idRange_.getBorderState(BorderRange::LowerBorder)) {
            activateBothBorders();
        }
    }
    else {
        if (!idRange_.getBorderState(borderRange)) {
            idRange_.setBorderState(borderRange, true);
            ++size_;
        }
    }

    typename IdRange<T>::IdInfo idInfo;

    if (isStandardId(id)) {
        do {
            idInfo = idRange_.moveBorder(borderRange, 1);

            if (reservedIds_.find(idInfo.value)) {
                reservedIds_.erase(idInfo.value);
            }
            else {
                ++size_;
            }

        } while (idInfo.value != id);

        expandRangeIfPossible(borderRange);
        return true;
    }

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
    }

    reservedIds_.add(id);
    ++size_;

    expandRangeIfPossible(borderRange);
    return true;
}
