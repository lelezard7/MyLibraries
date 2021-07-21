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

        unorderedIds_.push_back(std::move(id));
        return true;
    }

    if (orderedIds_.find(id) != orderedIds_.end())
        return false;

    orderedIds_.insert(std::move(id));
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
        auto it = std::find(unorderedIds_.begin(), unorderedIds_.end(), std::move(id));

        if (it != unorderedIds_.end())
            unorderedIds_.erase(std::move(it));

        return;
    }

    auto it = orderedIds_.find(std::move(id));

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
        idIssuingMethod_ = std::move(idIssuingMethod);
        return;
    }

    idIssuingMethod_ = std::move(idIssuingMethod);

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
        return std::find(unorderedIds_.begin(), unorderedIds_.end(), std::move(id)) != unorderedIds_.end();

    return orderedIds_.find(std::move(id)) != orderedIds_.end();
}

template<class T>
std::optional<T>
ONF::IdContainer<T>::
findByIndex(size_t index) const
{
    if (index < 0)
        return std::nullopt;

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (index >= unorderedIds_.size())
            return std::nullopt;

        auto it = unorderedIds_.begin();
        std::advance(it, std::move(index));
        return *it;
    }

    if (index >= orderedIds_.size())
        return std::nullopt;

    if (idIssuingMethod_ == IdIssuingMethod::Ascending) {
        auto it = orderedIds_.begin();
        std::advance(it, std::move(index));
        return *it;
    }

    auto it = orderedIds_.end();
    std::advance(it, -(std::move(index) + 1));
    return *it;
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
    unorderedIds_ = other.unorderedIds_;
    orderedIds_ = other.orderedIds_;
    idIssuingMethod_ = other.idIssuingMethod_;

    return *this;
}

template<class T>
ONF::IdContainer<T>&
ONF::IdContainer<T>::
operator=(IdContainer<T>&& other)
{
    unorderedIds_ = std::move(other.unorderedIds_);
    orderedIds_ = std::move(other.orderedIds_);
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
inline bool
ONF::
isStandardId(T target, T start, T step)
{
    ldouble An = static_cast<ldouble>(std::move(target));
    ldouble A1 = static_cast<ldouble>(std::move(start));
    ldouble d  = static_cast<ldouble>(std::move(step));

    ldouble n = std::abs((An - A1 + d) / d);
    return (n - static_cast<ulonglong>(n) == static_cast<ldouble>(0.0));
}



template<class T>
ONF::IdArea<T>::
IdArea(T start, T step)
    : upperBorderState_(false),
      upperBorder_     (start),
      upperLimit_      (std::numeric_limits<T>::max()),
      lowerBorderState_(false),
      lowerBorder_     (start),
      lowerLimit_      (std::numeric_limits<T>::min()),
      start_           (start)
{
    step_ = onf_abs((step == 0 ? 1 : step));
}

template<class T>
ONF::IdArea<T>::
IdArea(const IdArea<T>& other)
    : upperBorderState_(other.upperBorderState_),
      upperBorder_     (other.upperBorder_),
      upperLimit_      (other.upperLimit_),
      lowerBorderState_(other.lowerBorderState_),
      lowerBorder_     (other.lowerBorder_),
      lowerLimit_      (other.lowerLimit_),
      start_           (other.start_),
      step_            (other.step_) {}

template<class T>
ONF::IdArea<T>::
~IdArea() {}


template<class T>
typename ONF::IdArea<T>::Result&
ONF::IdArea<T>::Result::
operator=(const Result& other)
{
    errCode = other.errCode;
    position = other.position;

    border = other.border;
    state = other.state;
    value = other.value;

    stepCount = other.stepCount;

    return *this;
}


template<class T>
std::optional<typename ONF::IdArea<T>::Result>
ONF::IdArea<T>::
moveToBottom(T border, T limit, ldouble n, Action action) const
{
    if (static_cast<ldouble>(border) - static_cast<ldouble>(onf_abs(n) * step_) >= static_cast<ldouble>(limit)) {
        Result result;

        result.errCode = IDAREA_ERRC_SUCCESSFULLY;
        result.value = border - (onf_abs(n) * step_);
        result.stepCount = n;

        fillPositionAndChangeBorder(action, result, n);
        fillBorderAndState(result.value, result);

        return result;
    }

    for(ldouble i = onf_abs(n) - 1; i > 0; --i) {
        if (static_cast<ldouble>(border) - static_cast<ldouble>(onf_abs(i) * step_) >= static_cast<ldouble>(limit)) {
            Result result;

            result.value = border - (onf_abs(i) * step_);

            if (n > 0) {
                result.errCode = IDAREA_ERRC_IDS_RUN_OUT;
                result.stepCount = i;
            }
            else {
                result.errCode = IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE;
                result.stepCount = -i;
            }

            fillPositionAndChangeBorder(action, result, n);
            fillBorderAndState(result.value, result);

            return result;
        }
    }

    return std::nullopt;
}

template<class T>
std::optional<typename ONF::IdArea<T>::Result>
ONF::IdArea<T>::
moveToTop(T border, T limit, ldouble n, Action action) const
{
    if (static_cast<ldouble>(border) + static_cast<ldouble>(onf_abs(n) * step_) <= static_cast<ldouble>(limit)) {
        Result result;

        result.errCode = IDAREA_ERRC_SUCCESSFULLY;
        result.value = border + (onf_abs(n) * step_);
        result.stepCount = n;

        fillPositionAndChangeBorder(action, result, n);
        fillBorderAndState(result.value, result);

        return result;
    }

    for(ldouble i = onf_abs(n) - 1; i > 0; --i) {
        if (static_cast<ldouble>(border) + static_cast<ldouble>(i * step_) <= static_cast<ldouble>(limit)) {
            Result result;

            result.value = border + (i * step_);

            if (n > 0) {
                result.errCode = IDAREA_ERRC_IDS_RUN_OUT;
                result.stepCount = i;
            }
            else {
                result.errCode = IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE;
                result.stepCount = -i;
            }

            fillPositionAndChangeBorder(action, result, n);
            fillBorderAndState(result.value, result);

            return result;
        }
    }

    return std::nullopt;
}

template<class T>
typename ONF::IdArea<T>::Result
ONF::IdArea<T>::
motionless(T border) const
{
    Result result;
    result.position = IDM_POS_ON_BORDER;
    result.errCode = IDAREA_ERRC_SUCCESSFULLY;
    result.value = border;
    result.stepCount = 0;

    fillBorderAndState(border, result);

    return result;
}

template<class T>
typename ONF::IdArea<T>::Result
ONF::IdArea<T>::
findMotionless(T border, ldouble n) const
{
    Result result;
    result.position = IDM_POS_ON_BORDER;
    result.value = border;
    result.stepCount = 0;
    result.errCode = (n > 0 ? IDAREA_ERRC_IDS_RUN_OUT : IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);

    fillBorderAndState(border, result);

    return result;
}

template<class T>
void
ONF::IdArea<T>::
fillBorderAndState(T border, Result& result) const
{
    if (border < start_) {
        result.border = BorderRange::LowerBorder;
        result.state = lowerBorderState_;
    }
    else {
        result.border = BorderRange::UpperBorder;
        result.state = upperBorderState_;
    }
}

template<class T>
void
ONF::IdArea<T>::
fillPositionAndChangeBorder(Action action, Result& result, ldouble n) const
{
    if (action == Action::Move) {
        result.position = IDM_POS_ON_BORDER;
    }
    else {
        result.position = (n > 0 ? IDM_POS_OUT_RANGE : IDM_POS_IN_RANGE);
    }
}

template<class T>
int
ONF::IdArea<T>::
isSucces(BorderRange borderRange, ldouble n, Result& result, Action action) const
{
    if (borderRange == BorderRange::UpperBorder) {
        if (n > 0) {
            auto localResult = moveToTop(upperBorder_, upperLimit_, n, action);
            if (localResult.has_value()) {
                result = *localResult;
                return 1;
            }

            result = findMotionless(upperBorder_, n);
            return 0;
        }

        if (n < 0) {
            auto localResult = moveToBottom(upperBorder_, lowerBorder_, n, action);
            if (localResult.has_value()) {
                result = *localResult;
                return 1;
            }

            result = findMotionless(upperBorder_, n);
            return 0;
        }

        result = motionless(upperBorder_);
        return 0;
    }

    if (n > 0) {
        auto localResult = moveToBottom(lowerBorder_, lowerLimit_, n, action);
        if (localResult.has_value()) {
            result = *localResult;
            return 2;
        }

        result = findMotionless(lowerBorder_, n);
        return 0;
    }

    if (n < 0) {
        auto localResult = moveToTop(lowerBorder_, upperBorder_, n, action);
        if (localResult.has_value()) {
            result = *localResult;
            return 2;
        }

        result = findMotionless(lowerBorder_, n);
        return 0;
    }

    result = motionless(lowerBorder_);
    return 0;
}


template<class T>
typename ONF::IdArea<T>::Result
ONF::IdArea<T>::
moveBorder(BorderRange borderRange, longlong n)
{
    Result result;

    int whatToDo = isSucces(borderRange, static_cast<ldouble>(n), result, Action::Move);

    if (whatToDo == 1)
        upperBorder_ = result.value;

    if (whatToDo == 2)
        lowerBorder_ = result.value;

    return result;
}

template<class T>
typename ONF::IdArea<T>::Result
ONF::IdArea<T>::
getIdInfo(BorderRange borderRange, longlong n) const
{
    Result result;

    isSucces(borderRange, static_cast<ldouble>(n), result, Action::GetInfo);

    return result;
}

template<class T>
typename ONF::IdArea<T>::Result
ONF::IdArea<T>::
getIdInfo(const Result& result, longlong n) const
{

}

template<class T>
typename ONF::IdArea<T>::Result
ONF::IdArea<T>::
getIdInfo(T id, longlong n) const
{

}

template<class T>
typename ONF::IdArea<T>::Result
ONF::IdArea<T>::
getIdInfo(T id) const
{
    Result _result;

    _result.errCode = ((id > upperLimit_ || id < lowerLimit_) ? IDAREA_ERRC_IDS_RUN_OUT : IDAREA_ERRC_SUCCESSFULLY);

    if (id == upperBorder_ || id == lowerBorder_)
        _result.position = IDM_POS_ON_BORDER;
    else if (id > upperBorder_ || id < lowerBorder_)
        _result.position = IDM_POS_OUT_RANGE;
    else
        _result.position = IDM_POS_IN_RANGE;

    _result.border = (id >= start_ ? BorderRange::UpperBorder : BorderRange::LowerBorder);
    _result.state = (_result.border == BorderRange::UpperBorder ? upperBorderState_ : lowerBorderState_);
    _result.value = id;

    if (!isStandardId(id, start_, step_)) {
        _result.errCode = IDAREA_ERRC_NO_SUCH_ID;
        _result.stepCount = 0;
        return _result;
    }

    if (_result.position == IDM_POS_ON_BORDER) {
        _result.stepCount = 0;
        return _result;
    }

    if (_result.border == BorderRange::UpperBorder) {
        if (_result.position == IDM_POS_OUT_RANGE) {
            _result.stepCount = (id - upperBorder_) / step_;
            return _result;
        }

        _result.stepCount = (upperBorder_ - id) / step_;
        return _result;
    }
    else {
        if (_result.position == IDM_POS_OUT_RANGE) {
            _result.stepCount = (lowerBorder_ - id) / step_;
            return _result;
        }

        _result.stepCount = (id - lowerBorder_) / step_;
        return _result;
    }
}

template<class T>
void
ONF::IdArea<T>::
reset()
{
    upperBorderState_ = false;
    lowerBorderState_ = false;

    upperBorder_ = start_;
    lowerBorder_ = start_;
}

template<class T>
bool
ONF::IdArea<T>::
setBorderValue(BorderRange borderRange, T value)
{
    if (value > upperLimit_ || value < lowerLimit_)
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
ONF::IdArea<T>::
getBorderValue(BorderRange borderRange) const
{
    switch (borderRange) {
        case BorderRange::UpperBorder:  return upperBorder_;
        case BorderRange::LowerBorder:  return lowerBorder_;
    }
}

template<class T>
void
ONF::IdArea<T>::
setBorderState(BorderRange borderRange, bool state)
{
    switch (borderRange) {
        case BorderRange::UpperBorder:  upperBorderState_ = state;  return;
        case BorderRange::LowerBorder:  lowerBorderState_ = state;  return;
    }
}

template<class T>
inline bool
ONF::IdArea<T>::
getBorderState(BorderRange borderRange) const
{
    switch (borderRange) {
        case BorderRange::UpperBorder:  return upperBorderState_;
        case BorderRange::LowerBorder:  return lowerBorderState_;
    }
}

template<class T>
bool
ONF::IdArea<T>::
setBorderLimit(BorderRange borderRange, T limit)
{
    if (borderRange == BorderRange::UpperBorder) {
        if (upperBorder_ > limit)
            return false;

        if (limit > std::numeric_limits<T>::max())
            return false;

        upperLimit_ = limit;
        return true;
    }

    if (borderRange == BorderRange::LowerBorder) {
        if (lowerBorder_ < limit)
            return false;

        T d = std::numeric_limits<T>::min();
        if (limit < d)
            return false;

        lowerLimit_ = limit;
        return true;
    }
}

template<class T>
inline T
ONF::IdArea<T>::
getBorderLimit(BorderRange borderRange) const
{
    switch (borderRange) {
        case BorderRange::UpperBorder:  return upperLimit_;
        case BorderRange::LowerBorder:  return lowerLimit_;
    }
}

template<class T>
inline T
ONF::IdArea<T>::
getStart() const
{
    return start_;
}

template<class T>
inline T
ONF::IdArea<T>::
getStep() const
{
    return step_;
}

template<class T>
ONF::IdArea<T>&
ONF::IdArea<T>::
operator=(const IdArea<T>& other)
{
    upperBorderState_ = other.upperBorderState_;
    upperBorder_ = other.upperBorder_;
    upperLimit_ = other.upperLimit_;

    lowerBorderState_ = other.lowerBorderState_;
    lowerBorder_ = other.lowerBorder_;
    lowerLimit_ = other.lowerLimit_;

    start_ = other.start_;
    step_ = other.step_;

    return *this;
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
    idArea_ = IdArea<__T>(startId, step_);
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

            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::LowerBorder) == false) {
            idArea_.setBorderState(BorderRange::LowerBorder, true);
            id = idArea_.getBorderValue(BorderRange::LowerBorder);
            expandRange(BorderRange::LowerBorder);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::UpperBorder) == false) {
            idArea_.setBorderState(BorderRange::UpperBorder, true);
            id = idArea_.getBorderValue(BorderRange::UpperBorder);
            expandRange(BorderRange::UpperBorder);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (idArea_.getBorderValue(BorderRange::UpperBorder) < idArea_.getStart()) {
            getNextId(BorderRange::UpperBorder, id);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (idArea_.getBorderValue(BorderRange::LowerBorder) > idArea_.getStart()) {
            getNextId(BorderRange::LowerBorder, id);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (freeIds_.size()) {
            freeIds_.getNextId(id);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (step_ > 0) {
            getNextId(BorderRange::UpperBorder, id);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (step_ < 0) {
            getNextId(BorderRange::LowerBorder, id);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        return IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE;
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

            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::LowerBorder) == false) {
            idArea_.setBorderState(BorderRange::LowerBorder, true);
            id = idArea_.getBorderValue(BorderRange::LowerBorder);
            expandRange(BorderRange::LowerBorder);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (freeIds_.size()) {
            freeIds_.getNextId(id);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::UpperBorder) == false) {
            idArea_.setBorderState(BorderRange::UpperBorder, true);
            id = idArea_.getBorderValue(BorderRange::UpperBorder);
            expandRange(BorderRange::UpperBorder);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (step_ > 0) {
            getNextId(BorderRange::UpperBorder, id);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (step_ < 0) {
            getNextId(BorderRange::LowerBorder, id);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        return IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE;
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

            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::UpperBorder) == false) {
            idArea_.setBorderState(BorderRange::UpperBorder, true);
            id = idArea_.getBorderValue(BorderRange::UpperBorder);
            expandRange(BorderRange::UpperBorder);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (freeIds_.size()) {
            freeIds_.getNextId(id);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (idArea_.getBorderState(BorderRange::LowerBorder) == false) {
            idArea_.setBorderState(BorderRange::LowerBorder, true);
            id = idArea_.getBorderValue(BorderRange::LowerBorder);
            expandRange(BorderRange::LowerBorder);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (step_ < 0) {
            getNextId(BorderRange::LowerBorder, id);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        if (step_ > 0) {
            getNextId(BorderRange::UpperBorder, id);
            return IDAREA_ERRC_SUCCESSFULLY;
        }

        return IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE;
    }
}

template<class __T, class __Step>
bool
ONF::IdManager<__T, __Step>::
reserveId(__T id, ReservationMethod reservationMethod)
{
    if (id < std::numeric_limits<__T>::min() || id > std::numeric_limits<__T>::max())
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
    if (id < std::numeric_limits<__T>::min() || id > std::numeric_limits<__T>::max())
        return false;

    if (!isStandardId(id)) {
        if (!reservedIds_.find(id))
            return false;

        reservedIds_.freeId(id);
        return true;
    }

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (id == idArea_.getBorderValue(BorderRange::UpperBorder)) {
            if (reduceRange(BorderRange::UpperBorder) == IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE) {
                idArea_.setBorderState(BorderRange::UpperBorder, false);
                idArea_.setBorderState(BorderRange::LowerBorder, false);
                return true;
            }

            return true;
        }

        if (id == idArea_.getBorderValue(BorderRange::LowerBorder)) {
            if (reduceRange(BorderRange::LowerBorder) == IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE) {
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
        if (normalizeRange(BorderRange::UpperBorder, IdIssuingMethod::Dynamic) == IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE ||
            normalizeRange(BorderRange::LowerBorder, IdIssuingMethod::Dynamic) == IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE) {
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
    if (id < std::numeric_limits<__T>::min() || id > std::numeric_limits<__T>::max())
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

        if (_result.errCode == IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE)
            return IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE;

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
        return IDAREA_ERRC_SUCCESSFULLY;
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
//    int _errCode = IDAREA_ERRC_SUCCESSFULLY;

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
//    int _errCode = IDAREA_ERRC_SUCCESSFULLY;

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
//    int _errCode = IDAREA_ERRC_SUCCESSFULLY;

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
//        return IDAREA_ERRC_SUCCESSFULLY;
//    }

//    if (maxId_ == startId_ && startId_ == minId_) {

//    }

//    if (step_ > 0) {
//        if (isCrossingUpperBorder_)
//            return IDAREA_ERRC_IDS_RUN_OUT;

//        id = maxId_;
//        maxId_ += static_cast<__T>(step_);
//        expandRange();
//        return IDAREA_ERRC_SUCCESSFULLY;
//    }

//    if (step_ < 0) {
//        if (isCrossingLowerBorder_)
//            return IDAREA_ERRC_IDS_RUN_OUT;

//        id = minId_;
//        minId_ += static_cast<__T>(step_);
//        expandRange();
//        return IDAREA_ERRC_SUCCESSFULLY;
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
