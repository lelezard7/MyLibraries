#include "../include/Id_Manager.h"
#include <cmath>
#include <cstdlib>
#include <type_traits>
#include <algorithm>
#include <limits>
#include <exception>
#include <string>


template<class __T>
Id_M::IdContainer<__T>::
IdContainer(IdIssuingMethod idIssuingMethod)
    : idIssuingMethod_(idIssuingMethod) {}

template<class __T>
Id_M::IdContainer<__T>::
IdContainer(const IdContainer<__T>& other)
    : unorderedFreeIds_(other.unorderedFreeIds_),
      orderedFreeIds_  (other.orderedFreeIds_),
      idIssuingMethod_ (other.idIssuingMethod_) {}

template<class __T>
Id_M::IdContainer<__T>::
~IdContainer() {}

template<class __T>
bool
Id_M::IdContainer<__T>::
getNextId(__T& id)
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        auto _it = unorderedFreeIds_.begin();

        if (_it != unorderedFreeIds_.end()) {
            id = *_it;
            unorderedFreeIds_.erase(_it);
            return true;
        }

        return false;
    }

    if (orderedFreeIds_.size()) {
        if (idIssuingMethod_ == IdIssuingMethod::Ascending) {
            auto _it = orderedFreeIds_.begin();
            id = *_it;
            orderedFreeIds_.erase(_it);
            return true;
        }

        if (idIssuingMethod_ == IdIssuingMethod::Descending) {
            auto _it = orderedFreeIds_.end();
            --_it;
            id = *_it;
            orderedFreeIds_.erase(_it);
            return true;
        }
    }

    return false;
}

template<class __T>
bool
Id_M::IdContainer<__T>::
add(__T id)
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        if (std::find(unorderedFreeIds_.begin(), unorderedFreeIds_.end(), id) != unorderedFreeIds_.end())
            return false;

        unorderedFreeIds_.push_back(id);
        return true;
    }

    if (orderedFreeIds_.find(id) != orderedFreeIds_.end())
        return false;

    orderedFreeIds_.insert(id);
    return true;
}

template<class __T>
bool
Id_M::IdContainer<__T>::
find(__T id) const
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        return std::find(unorderedFreeIds_.begin(), unorderedFreeIds_.end(), id) != unorderedFreeIds_.end();
    }

    return orderedFreeIds_.find(id) != orderedFreeIds_.end();
}

template<class __T>
size_t
Id_M::IdContainer<__T>::
size() const
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic)
        return unorderedFreeIds_.size();

    return orderedFreeIds_.size();
}

template<class __T>
void
Id_M::IdContainer<__T>::
freeId(__T id)
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        auto _it = std::find(unorderedFreeIds_.begin(), unorderedFreeIds_.end(), id);

        if (_it != unorderedFreeIds_.end())
            unorderedFreeIds_.erase(_it);

        return;
    }

    auto _it = orderedFreeIds_.find(id);

    if (_it != orderedFreeIds_.end())
        orderedFreeIds_.erase(_it);
}

template<class __T>
void
Id_M::IdContainer<__T>::
clear()
{
    unorderedFreeIds_.clear();
    orderedFreeIds_.clear();
}

template<class __T>
void
Id_M::IdContainer<__T>::
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

    if (idIssuingMethod == IdIssuingMethod::Dynamic) {
        for (auto it = orderedFreeIds_.begin(); it != orderedFreeIds_.end(); ++it) {
            unorderedFreeIds_.push_back(*it);
        }

        orderedFreeIds_.clear();
        return;
    }

    for (auto it = unorderedFreeIds_.begin(); it != unorderedFreeIds_.end(); ++it) {
        orderedFreeIds_.insert(*it);
    }

    unorderedFreeIds_.clear();
}

template<class __T>
Id_M::IdIssuingMethod
Id_M::IdContainer<__T>::
getIdIssuingMethod() const
{
    return idIssuingMethod_;
}

template<class __T>
Id_M::IdContainer<__T>&
Id_M::IdContainer<__T>::
operator=(const IdContainer<__T>& other)
{
    unorderedFreeIds_ = other.unorderedFreeIds_;
    orderedFreeIds_ = other.orderedFreeIds_;
    idIssuingMethod_ = other.idIssuingMethod_;

    return *this;
}

template<class __T>
size_t
Id_M::IdContainer<__T>::
getOrderedFreeIdsSize() const
{
    return orderedFreeIds_.size();
}

template<class __T>
size_t
Id_M::IdContainer<__T>::
getUnorderedFreeIdsSize() const
{
    return unorderedFreeIds_.size();
}
















template<class __T>
Id_M::IdArea<__T>::
IdArea(__T start, __T step)
    : upperBorderState_(false),
      upperBorder_     (start),
      upperLimit_      (std::numeric_limits<__T>::max()),
      lowerBorderState_(false),
      lowerBorder_     (start),
      lowerLimit_      (std::numeric_limits<__T>::min()),
      start_           (start)
{
    step_ = idm_abs((step == 0 ? 1 : step));
}

template<class __T>
Id_M::IdArea<__T>::
IdArea(const IdArea<__T>& other)
    : upperBorderState_(other.upperBorderState_),
      upperBorder_     (other.upperBorder_),
      upperLimit_      (other.upperLimit_),
      lowerBorderState_(other.lowerBorderState_),
      lowerBorder_     (other.lowerBorder_),
      lowerLimit_      (other.lowerLimit_),
      start_           (other.start_),
      step_            (other.step_) {}

template<class __T>
Id_M::IdArea<__T>::
~IdArea() {}

template<class __T>
Id_M::IdArea<__T>::Result<__T>
Id_M::IdArea<__T>::
moveBorder(BorderRange borderRange, long long n)
{
    Result<__T> _result;

    _result.position = IDM_POS_ON_BORDER;

    if (borderRange == BorderRange::UpperBorder) {
        if (n > 0) {
            if (static_cast<long long>(upperBorder_) + static_cast<long long>(n * step_) < static_cast<long long>(upperLimit_)) {
                upperBorder_ += n * step_;

                _result.errCode = IDM_ERR_SUCCESSFULLY;
                _result.value = upperBorder_;
                _result.stepCount = n;

                if (upperBorder_ < start_) {
                    _result.border = BorderRange::LowerBorder;
                    _result.state = lowerBorderState_;
                }
                else {
                    _result.border = BorderRange::UpperBorder;
                    _result.state = upperBorderState_;
                }

                return _result;
            }

            for(long long i = n - 1; i > 0; --i) {
                if (static_cast<long long>(upperBorder_) + static_cast<long long>(i * step_) < static_cast<long long>(upperLimit_)) {
                    upperBorder_ += i * step_;

                    _result.errCode = IDM_ERR_IDS_RUN_OUT;
                    _result.value = upperBorder_;
                    _result.stepCount = i;

                    if (upperBorder_ < start_) {
                        _result.border = BorderRange::LowerBorder;
                        _result.state = lowerBorderState_;
                    }
                    else {
                        _result.border = BorderRange::UpperBorder;
                        _result.state = upperBorderState_;
                    }

                    return _result;
                }
            }

            _result.errCode = IDM_ERR_IDS_RUN_OUT;
            _result.value = upperBorder_;
            _result.stepCount = 0;

            if (upperBorder_ < start_) {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }
            else {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }

            return _result;
        }

        if (n < 0) {
            if (static_cast<long long>(upperBorder_) - static_cast<long long>(idm_abs(n) * step_) > static_cast<long long>(lowerBorder_)) {
                upperBorder_ -= idm_abs(n) * step_;

                _result.errCode = IDM_ERR_SUCCESSFULLY;
                _result.value = upperBorder_;
                _result.stepCount = n;

                if (upperBorder_ < start_) {
                    _result.border = BorderRange::LowerBorder;
                    _result.state = lowerBorderState_;
                }
                else {
                    _result.border = BorderRange::UpperBorder;
                    _result.state = upperBorderState_;
                }

                return _result;
            }

            for(long long i = idm_abs(n) - 1; i > 0; --i) {
                if (static_cast<long long>(upperBorder_) - static_cast<long long>(idm_abs(i) * step_) > static_cast<long long>(lowerBorder_)) {
                    upperBorder_ -= i * step_;

                    _result.errCode = IDM_ERR_IMPOSSIBLE_REDUCE_RANGE;
                    _result.value = upperBorder_;
                    _result.stepCount = -i;

                    if (upperBorder_ < start_) {
                        _result.border = BorderRange::LowerBorder;
                        _result.state = lowerBorderState_;
                    }
                    else {
                        _result.border = BorderRange::UpperBorder;
                        _result.state = upperBorderState_;
                    }

                    return _result;
                }
            }

            _result.errCode = IDM_ERR_IMPOSSIBLE_REDUCE_RANGE;
            _result.value = upperBorder_;
            _result.stepCount = 0;

            if (upperBorder_ < start_) {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }
            else {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }

            return _result;
        }

        if (n == 0) {
            _result.errCode = IDM_ERR_SUCCESSFULLY;
            _result.value = upperBorder_;
            _result.stepCount = 0;

            if (upperBorder_ < start_) {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }
            else {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }

            return _result;
        }
    }

    if (borderRange == BorderRange::LowerBorder) {
        if (n > 0) {
            if (static_cast<long long>(lowerBorder_) - static_cast<long long>(n * step_) > static_cast<long long>(lowerLimit_)) {
                lowerBorder_ -= n * step_;

                _result.errCode = IDM_ERR_SUCCESSFULLY;
                _result.value = lowerBorder_;
                _result.stepCount = n;

                if (lowerBorder_ > start_) {
                    _result.border = BorderRange::UpperBorder;
                    _result.state = upperBorderState_;
                }
                else {
                    _result.border = BorderRange::LowerBorder;
                    _result.state = lowerBorderState_;
                }

                return _result;
            }

            for(long long i = n - 1; i > 0; --i) {
                if (static_cast<long long>(lowerBorder_) - static_cast<long long>(i * step_) > static_cast<long long>(lowerLimit_)) {
                    lowerBorder_ -= i * step_;

                    _result.errCode = IDM_ERR_IDS_RUN_OUT;
                    _result.value = lowerBorder_;
                    _result.stepCount = i;

                    if (lowerBorder_ > start_) {
                        _result.border = BorderRange::UpperBorder;
                        _result.state = upperBorderState_;
                    }
                    else {
                        _result.border = BorderRange::LowerBorder;
                        _result.state = lowerBorderState_;
                    }

                    return _result;
                }
            }

            _result.errCode = IDM_ERR_IDS_RUN_OUT;
            _result.value = lowerBorder_;
            _result.stepCount = 0;

            if (lowerBorder_ > start_) {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }
            else {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }

            return _result;
        }

        if (n < 0) {
            if (static_cast<long long>(lowerBorder_) + static_cast<long long>(idm_abs(n) * step_) < static_cast<long long>(upperBorder_)) {
                lowerBorder_ += idm_abs(n) * step_;

                _result.errCode = IDM_ERR_SUCCESSFULLY;
                _result.value = lowerBorder_;
                _result.stepCount = n;

                if (lowerBorder_ > start_) {
                    _result.border = BorderRange::UpperBorder;
                    _result.state = upperBorderState_;
                }
                else {
                    _result.border = BorderRange::LowerBorder;
                    _result.state = lowerBorderState_;
                }

                return _result;
            }

            for(long long i = idm_abs(n) - 1; i > 0; --i) {
                if (static_cast<long long>(lowerBorder_) + static_cast<long long>(i * step_) < static_cast<long long>(upperBorder_)) {
                    lowerBorder_ += i * step_;

                    _result.errCode = IDM_ERR_IMPOSSIBLE_REDUCE_RANGE;
                    _result.value = lowerBorder_;
                    _result.stepCount = -i;

                    if (lowerBorder_ > start_) {
                        _result.border = BorderRange::UpperBorder;
                        _result.state = upperBorderState_;
                    }
                    else {
                        _result.border = BorderRange::LowerBorder;
                        _result.state = lowerBorderState_;
                    }

                    return _result;
                }
            }

            _result.errCode = IDM_ERR_IMPOSSIBLE_REDUCE_RANGE;
            _result.value = lowerBorder_;
            _result.stepCount = 0;

            if (lowerBorder_ > start_) {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }
            else {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }

            return _result;
        }

        if (n == 0) {
            _result.errCode = IDM_ERR_SUCCESSFULLY;
            _result.value = lowerBorder_;
            _result.stepCount = 0;

            if (lowerBorder_ > start_) {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }
            else {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }

            return _result;
        }
    }
}

template<class __T>
Id_M::IdArea<__T>::Result<__T>
Id_M::IdArea<__T>::
getIdInfo(BorderRange borderRange, long long n) const
{
    Result<__T> _result;

    if (borderRange == BorderRange::UpperBorder) {
        if (n > 0) {
            if (static_cast<long long>(upperBorder_) + static_cast<long long>(n * step_) < static_cast<long long>(upperLimit_)) {
                _result.errCode = IDM_ERR_SUCCESSFULLY;
                _result.position = IDM_POS_OUT_RANGE;
                _result.value = upperBorder_ + (n * step_);
                _result.stepCount = n;

                if (upperBorder_ + (n * step_) < start_) {
                    _result.border = BorderRange::LowerBorder;
                    _result.state = lowerBorderState_;
                }
                else {
                    _result.border = BorderRange::UpperBorder;
                    _result.state = upperBorderState_;
                }

                return _result;
            }

            for(long long i = n - 1; i > 0; --i) {
                if (static_cast<long long>(upperBorder_) + static_cast<long long>(i * step_) < static_cast<long long>(upperLimit_)) {
                    _result.errCode = IDM_ERR_IDS_RUN_OUT;
                    _result.position = IDM_POS_OUT_RANGE;
                    _result.value = upperBorder_ + (i * step_);
                    _result.stepCount = i;

                    if (upperBorder_ + (i * step_) < start_) {
                        _result.border = BorderRange::LowerBorder;
                        _result.state = lowerBorderState_;
                    }
                    else {
                        _result.border = BorderRange::UpperBorder;
                        _result.state = upperBorderState_;
                    }

                    return _result;
                }
            }

            _result.errCode = IDM_ERR_IDS_RUN_OUT;
            _result.position = IDM_POS_ON_BORDER;
            _result.value = upperBorder_;
            _result.stepCount = 0;

            if (upperBorder_ < start_) {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }
            else {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }

            return _result;
        }

        if (n < 0) {
            if (static_cast<long long>(upperBorder_) - static_cast<long long>(idm_abs(n) * step_) > static_cast<long long>(lowerBorder_)) {
                _result.errCode = IDM_ERR_SUCCESSFULLY;
                _result.position = IDM_POS_IN_RANGE;
                _result.value = upperBorder_ - (idm_abs(n) * step_);
                _result.stepCount = n;

                if (upperBorder_ - (idm_abs(n) * step_) < start_) {
                    _result.border = BorderRange::LowerBorder;
                    _result.state = lowerBorderState_;
                }
                else {
                    _result.border = BorderRange::UpperBorder;
                    _result.state = upperBorderState_;
                }

                return _result;
            }

            for(long long i = idm_abs(n) - 1; i > 0; --i) {
                if (static_cast<long long>(upperBorder_) - static_cast<long long>(idm_abs(i) * step_) > static_cast<long long>(lowerBorder_)) {
                    _result.errCode = IDM_ERR_IMPOSSIBLE_REDUCE_RANGE;
                    _result.position = IDM_POS_IN_RANGE;
                    _result.value = upperBorder_ - (i * step_);
                    _result.stepCount = -i;

                    if (upperBorder_ - (i * step_) < start_) {
                        _result.border = BorderRange::LowerBorder;
                        _result.state = lowerBorderState_;
                    }
                    else {
                        _result.border = BorderRange::UpperBorder;
                        _result.state = upperBorderState_;
                    }

                    return _result;
                }
            }

            _result.errCode = IDM_ERR_IMPOSSIBLE_REDUCE_RANGE;
            _result.position = IDM_POS_ON_BORDER;
            _result.value = upperBorder_;
            _result.stepCount = 0;

            if (upperBorder_ < start_) {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }
            else {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }

            return _result;
        }

        if (n == 0) {
            _result.errCode = IDM_ERR_SUCCESSFULLY;
            _result.position = IDM_POS_ON_BORDER;
            _result.value = upperBorder_;
            _result.stepCount = 0;

            if (upperBorder_ < start_) {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }
            else {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }

            return _result;
        }
    }

    if (borderRange == BorderRange::LowerBorder) {
        if (n > 0) {
            if (static_cast<long long>(lowerBorder_) - static_cast<long long>(n * step_) > static_cast<long long>(lowerLimit_)) {
                _result.errCode = IDM_ERR_SUCCESSFULLY;
                _result.position = IDM_POS_OUT_RANGE;
                _result.value = lowerBorder_ - (n * step_);
                _result.stepCount = n;

                if (lowerBorder_ - (n * step_) > start_) {
                    _result.border = BorderRange::UpperBorder;
                    _result.state = upperBorderState_;
                }
                else {
                    _result.border = BorderRange::LowerBorder;
                    _result.state = lowerBorderState_;
                }

                return _result;
            }

            for(long long i = n - 1; i > 0; --i) {
                if (static_cast<long long>(lowerBorder_) - static_cast<long long>(i * step_) > static_cast<long long>(lowerLimit_)) {
                    _result.errCode = IDM_ERR_IDS_RUN_OUT;
                    _result.position = IDM_POS_OUT_RANGE;
                    _result.value = lowerBorder_ - (i * step_);
                    _result.stepCount = i;

                    if (lowerBorder_ - (i * step_) > start_) {
                        _result.border = BorderRange::UpperBorder;
                        _result.state = upperBorderState_;
                    }
                    else {
                        _result.border = BorderRange::LowerBorder;
                        _result.state = lowerBorderState_;
                    }

                    return _result;
                }
            }

            _result.errCode = IDM_ERR_IDS_RUN_OUT;
            _result.position = IDM_POS_ON_BORDER;
            _result.value = lowerBorder_;
            _result.stepCount = 0;

            if (lowerBorder_ > start_) {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }
            else {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }

            return _result;
        }

        if (n < 0) {
            if (static_cast<long long>(lowerBorder_) + static_cast<long long>(idm_abs(n) * step_) < static_cast<long long>(upperBorder_)) {
                _result.errCode = IDM_ERR_SUCCESSFULLY;
                _result.position = IDM_POS_IN_RANGE;
                _result.value = lowerBorder_ + (idm_abs(n) * step_);
                _result.stepCount = n;

                if (lowerBorder_ + (idm_abs(n) * step_) > start_) {
                    _result.border = BorderRange::UpperBorder;
                    _result.state = upperBorderState_;
                }
                else {
                    _result.border = BorderRange::LowerBorder;
                    _result.state = lowerBorderState_;
                }

                return _result;
            }

            for(long long i = idm_abs(n) - 1; i > 0; --i) {
                if (static_cast<long long>(lowerBorder_) + static_cast<long long>(i * step_) < static_cast<long long>(upperBorder_)) {
                    _result.errCode = IDM_ERR_IMPOSSIBLE_REDUCE_RANGE;
                    _result.position = IDM_POS_IN_RANGE;
                    _result.value = lowerBorder_ + (i * step_);
                    _result.stepCount = -i;

                    if (lowerBorder_ + (i * step_) > start_) {
                        _result.border = BorderRange::UpperBorder;
                        _result.state = upperBorderState_;
                    }
                    else {
                        _result.border = BorderRange::LowerBorder;
                        _result.state = lowerBorderState_;
                    }

                    return _result;
                }
            }

            _result.errCode = IDM_ERR_IMPOSSIBLE_REDUCE_RANGE;
            _result.position = IDM_POS_ON_BORDER;
            _result.value = lowerBorder_;
            _result.stepCount = 0;

            if (lowerBorder_ > start_) {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }
            else {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }

            return _result;
        }

        if (n == 0) {
            _result.errCode = IDM_ERR_SUCCESSFULLY;
            _result.position = IDM_POS_ON_BORDER;
            _result.value = lowerBorder_;
            _result.stepCount = 0;

            if (lowerBorder_ > start_) {
                _result.border = BorderRange::UpperBorder;
                _result.state = upperBorderState_;
            }
            else {
                _result.border = BorderRange::LowerBorder;
                _result.state = lowerBorderState_;
            }

            return _result;
        }
    }
}

template<class __T>
Id_M::IdArea<__T>::Result<__T>
Id_M::IdArea<__T>::
getIdInfo(__T id) const
{
    Result<__T> _result;

    _result.errCode = ((id > upperLimit_ || id < lowerLimit_) ? IDM_ERR_IDS_RUN_OUT : IDM_ERR_SUCCESSFULLY);

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
        _result.errCode = IDM_ERR_NO_SUCH_ID;
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

template<class __T>
bool
Id_M::IdArea<__T>::
setBorderValue(BorderRange borderRange, __T value)
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

template<class __T>
inline __T
Id_M::IdArea<__T>::
getBorderValue(BorderRange borderRange) const
{
    switch (borderRange) {
        case BorderRange::UpperBorder:  return upperBorder_;
        case BorderRange::LowerBorder:  return lowerBorder_;
    }
}

template<class __T>
void
Id_M::IdArea<__T>::
setBorderState(BorderRange borderRange, bool state)
{
    switch (borderRange) {
        case BorderRange::UpperBorder:  upperBorderState_ = state;  return;
        case BorderRange::LowerBorder:  lowerBorderState_ = state;  return;
    }
}

template<class __T>
inline bool
Id_M::IdArea<__T>::
getBorderState(BorderRange borderRange) const
{
    switch (borderRange) {
        case BorderRange::UpperBorder:  return upperBorderState_;
        case BorderRange::LowerBorder:  return lowerBorderState_;
    }
}

template<class __T>
bool
Id_M::IdArea<__T>::
setBorderLimit(BorderRange borderRange, __T limit)
{
    if (borderRange == BorderRange::UpperBorder) {
        if (upperBorder_ > limit)
            return false;

        if (limit > std::numeric_limits<__T>::max())
            return false;

        upperLimit_ = limit;
        return true;
    }

    if (borderRange == BorderRange::LowerBorder) {
        if (lowerBorder_ < limit)
            return false;

        if (limit < std::numeric_limits<__T>::min())
            return false;

        lowerLimit_ = limit;
        return true;
    }
}

template<class __T>
inline __T
Id_M::IdArea<__T>::
getBorderLimit(BorderRange borderRange) const
{
    switch (borderRange) {
        case BorderRange::UpperBorder:  return upperLimit_;
        case BorderRange::LowerBorder:  return lowerLimit_;
    }
}

template<class __T>
inline __T
Id_M::IdArea<__T>::
getStart() const
{
    return start_;
}

template<class __T>
inline __T
Id_M::IdArea<__T>::
getStep() const
{
    return step_;
}

template<class __T>
Id_M::IdArea<__T>&
Id_M::IdArea<__T>::
operator=(const IdArea<__T>& other)
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

template<class __T>
template<class __TF>
inline __TF
Id_M::IdArea<__T>::
idm_abs(__TF value) const
{
    return value < 0 ? -value : value;
}

template<class __T>
template<class __TF>
inline bool
Id_M::IdArea<__T>::
isStandardId(__TF id, __TF start, __TF step) const
{
    long double _An = static_cast<long double>(id);
    long double _A1 = static_cast<long double>(start);
    long double _d = static_cast<long double>(step);

    long double n = std::abs((_An - _A1 + _d) / _d);
    return (n - static_cast<unsigned long long>(n) == static_cast<long double>(0.0));
}
















template<class __T, class __Step>
Id_M::IdManager<__T, __Step>::
IdManager(__T startId,
          __Step step,
          IdIssuingMethod idIssuingMethod,
          bool isHardStep)
    : freeIds_(idIssuingMethod),
      reservedIds_(),
      isHardStep_(isHardStep),
      idIssuingMethod_(idIssuingMethod)
{
    static_assert(is_types_combination_prohibited<__T, __Step> == false);

    step_ = (step == 0 ? 1 : step);
    idArea_ = IdArea<__T>(startId, step_);
}

template<class __T, class __Step>
Id_M::IdManager<__T, __Step>::
IdManager(const IdManager<__T, __Step>& other)
    : freeIds_(other.freeIds_),
      reservedIds_(other.reservedIds_),
      idArea_(other.idArea_),
      step_(other.step_),
      isHardStep_(other.isHardStep),
      idIssuingMethod_(other.idIssuingMethod_) {}

template<class __T, class __Step>
Id_M::IdManager<__T, __Step>::
~IdManager() {}




template<class __T, class __Step>
bool
Id_M::IdManager<__T, __Step>::
isStandardId(__T id) const
{
    long double _An = static_cast<long double>(id);
    long double _A1 = static_cast<long double>(idArea_.getStart());
    long double _d = static_cast<long double>(step_);

    long double n = std::abs((_An - _A1 + _d) / _d);
    return (n - static_cast<unsigned long long>(n) == static_cast<long double>(0.0));
}

template<class __T, class __Step>
int
Id_M::IdManager<__T, __Step>::
getFreeId(__T& id)
{
    if (idArea_.getMaxId() < idArea_.getStartId()) {
        if (idArea_.pushBorder(BorderRange::UpperBorder, &id) == IDM_ERR_IDS_RUN_OUT)       //преобразование в static_cast<__T> ведет к ошибкам из-за минуса.
            return IDM_ERR_IDS_RUN_OUT;
        if (expandRangeToTop(BorderRange::UpperBorder, &id) == IDM_ERR_IDS_RUN_OUT)
            return IDM_ERR_IDS_RUN_OUT;

        return IDM_ERR_SUCCESSFULLY;
    }

    if (idArea_.getMinId() > idArea_.getStartId()) {
        if (idArea_.pushBorder(BorderRange::LowerBorder, &id) == IDM_ERR_IDS_RUN_OUT)       //преобразование в static_cast<__T> ведет к ошибкам из-за минуса.
            return IDM_ERR_IDS_RUN_OUT;
        if (expandRangeToTop(BorderRange::LowerBorder, &id) == IDM_ERR_IDS_RUN_OUT)
            return IDM_ERR_IDS_RUN_OUT;

        return IDM_ERR_SUCCESSFULLY;
    }

    if (freeIds_.size()) {
        freeIds_.getNextId(id);
        return IDM_ERR_SUCCESSFULLY;
    }

    if (idArea_.getMaxId() == idArea_.getStartId() && idArea_.getStartId() == idArea_.getMinId() &&
        idArea_.isMaxIdOn() == false && idArea_.isMinIdOn() == false) {
        idArea_.turnOnBorder(BorderRange::UpperBorder, true);
        idArea_.turnOnBorder(BorderRange::LowerBorder, true);
        id = idArea_.getStartId();
        __T _id = 0;
        idArea_.checkBorder(BorderRange::UpperBorder, &_id);
        if (expandRangeToTopWithowtReserv(BorderRange::UpperBorder, &_id) == IDM_ERR_IDS_RUN_OUT)
            return IDM_ERR_IDS_RUN_OUT;
        idArea_.checkBorder(BorderRange::LowerBorder, &_id);
        if (expandRangeToTopWithowtReserv(BorderRange::LowerBorder, &_id) == IDM_ERR_IDS_RUN_OUT)
            return IDM_ERR_IDS_RUN_OUT;

        return IDM_ERR_SUCCESSFULLY;
    }

    if (step_ > 0) {
        if (idArea_.pushBorder(BorderRange::UpperBorder, &id) == IDM_ERR_IDS_RUN_OUT)       //преобразование в static_cast<__T> ведет к ошибкам из-за минуса.
            return IDM_ERR_IDS_RUN_OUT;
        if (expandRangeToTop(BorderRange::UpperBorder, &id) == IDM_ERR_IDS_RUN_OUT)
            return IDM_ERR_IDS_RUN_OUT;

        return IDM_ERR_SUCCESSFULLY;
    }

    if (step_ < 0) {
        if (idArea_.pushBorder(BorderRange::LowerBorder, &id) == IDM_ERR_IDS_RUN_OUT)       //преобразование в static_cast<__T> ведет к ошибкам из-за минуса.
            return IDM_ERR_IDS_RUN_OUT;
        if (expandRangeToTop(BorderRange::LowerBorder, &id) == IDM_ERR_IDS_RUN_OUT)
            return IDM_ERR_IDS_RUN_OUT;

        return IDM_ERR_SUCCESSFULLY;
    }
}

template<class __T, class __Step>
bool
Id_M::IdManager<__T, __Step>::
reserveId(__T id, ReservationMethod reservationMethod)
{
    if (!isStandardId(id)) {
        if (isHardStep_)
            return false;

        if (reservedIds_.find(id))
            return false;

        if (id < std::numeric_limits<__T>::min() || id > std::numeric_limits<__T>::max())
            return false;

        if (reservationMethod == ReservationMethod::Interpolate) {
            if (id > idArea_.getBorderValue(BorderRange::UpperBorder)) {
                auto _result = idArea_.getIdInfo(BorderRange::UpperBorder, 1);

                while (_result.value < id || reservedIds_.find(_result.value) == true) {
                    if (reservedIds_.find(_result.value))
                        reservedIds_.freeId(_result.value);
                    else
                        freeIds_.add(_result.value);

                    idArea_.moveBorder(BorderRange::UpperBorder, 1);
                    _result = idArea_.getIdInfo(BorderRange::UpperBorder, 1);
                }

                reservedIds_.add(id);
                return true;
            }

            if (id < idArea_.getMinId()) {
                __T _id = 0;
                idArea_.checkBorder(BorderRange::LowerBorder, _id);

                while (_id > id  || reservedIds_.find(_id) == true) {
                    if (reservedIds_.find(_id))
                        reservedIds_.freeId(_id);
                    else
                        freeIds_.add(_id);

                    idArea_.pushBorder(BorderRange::LowerBorder);
                    idArea_.checkBorder(BorderRange::LowerBorder, _id);
                }

                reservedIds_.add(id);
                return true;
            }

            if (id > idArea_.getMinId() && id < idArea_.getMaxId()) {
                reservedIds_.add(id);
                return true;
            }

            throw "-----------------------";
        }

        if (reservationMethod == ReservationMethod::ReserveRange) {
            if (id > idArea_.getMaxId()) {
                __T _id = 0;
                idArea_.checkBorder(BorderRange::UpperBorder, _id);

                while (_id < id || reservedIds_.find(_id) == true) {
                    if (reservedIds_.find(_id))
                        reservedIds_.freeId(_id);

                    idArea_.pushBorder(BorderRange::UpperBorder);
                    idArea_.checkBorder(BorderRange::UpperBorder, _id);
                }

                return true;
            }

            if (id < idArea_.getMinId()) {
                __T _id = 0;
                idArea_.checkBorder(BorderRange::LowerBorder, _id);

                while (_id > id || reservedIds_.find(_id) == true) {
                    if (reservedIds_.find(_id))
                        reservedIds_.freeId(_id);

                    idArea_.pushBorder(BorderRange::LowerBorder);
                    idArea_.checkBorder(BorderRange::LowerBorder, _id);
                }

                return true;
            }

            if (id > idArea_.getMinId() && id < idArea_.getMaxId()) {
                if (step_ < 0) {
                    for (__T i = idArea_.getMinId() + idArea_.getStep(); i < id; i += idArea_.getStep()) {
                        if (freeIds_.find(i))
                            freeIds_.freeId(i);
                    }

                    return true;
                }

                if (step_ > 0) {
                    for (__T i = idArea_.getMaxId() - idArea_.getStep(); i > id; i -= idArea_.getStep()) {
                        if (freeIds_.find(i))
                            freeIds_.freeId(i);
                    }

                    return true;
                }
            }

            throw "-----------------------";
        }

        if (reservationMethod == ReservationMethod::ExpandRange) { //Контролировать флаги границ и чтобы в динамическом режиме нельзя было создаить пустые границы ExpandRange.
            if (id > idArea_.getMaxId()) {
                __T _id = 0;
                idArea_.checkBorder(BorderRange::UpperBorder, _id);

                while (_id < id || reservedIds_.find(_id) == true) {
                    if (reservedIds_.find(_id))
                        reservedIds_.freeId(_id);
                    else
                        freeIds_.add(_id);

                    idArea_.pushBorder(BorderRange::UpperBorder);
                    idArea_.checkBorder(BorderRange::UpperBorder, _id);
                }

                return true;
            }

            if (id < idArea_.getMinId()) {
                __T _id = 0;
                idArea_.checkBorder(BorderRange::LowerBorder, _id);

                while (_id > id || reservedIds_.find(_id) == true) {
                    if (reservedIds_.find(_id))
                        reservedIds_.freeId(_id);
                    else
                        freeIds_.add(_id);

                    idArea_.pushBorder(BorderRange::LowerBorder);
                    idArea_.checkBorder(BorderRange::LowerBorder, _id);
                }

                return true;
            }

            if (id > idArea_.getMinId() && id < idArea_.getMaxId()) {
                return true;
            }

            throw "-----------------------";
        }

        reservedIds_.add(id);
        return true;
    }


    if (id == idArea_.getMinId() && idArea_.isMinIdOn() == true)
        return false;

    if (id == idArea_.getMaxId() && idArea_.isMaxIdOn() == true)
        return false;

    if (id == idArea_.getMinId()) {
        idArea_.turnOnBorder(BorderRange::LowerBorder, true);
        return true;
    }

    if (id == idArea_.getMaxId()) {
        idArea_.turnOnBorder(BorderRange::UpperBorder, true);
        return true;
    }

    if (id > idArea_.getMinId() && id < idArea_.getMaxId()) {
        if (!freeIds_.find(id))
            return false;

        freeIds_.freeId(id);
        return true;
    }

    if (id < std::numeric_limits<__T>::min() || id > std::numeric_limits<__T>::max())
        return false;

    if (reservedIds_.find(id))
        return false;

    if (reservationMethod == ReservationMethod::Interpolate || reservationMethod == ReservationMethod::AutoSelect) {
        if (id > idArea_.getMaxId()) {
            __T _id = 0;
            idArea_.checkBorder(BorderRange::UpperBorder, _id);

            while (_id <= id) {
                if (reservedIds_.find(_id))
                    reservedIds_.freeId(_id);
                else
                    freeIds_.add(_id);

                idArea_.pushBorder(BorderRange::UpperBorder);
                idArea_.checkBorder(BorderRange::UpperBorder, _id);
            }

            return true;
        }

        if (id < idArea_.getMinId()) {
            __T _id = 0;
            idArea_.checkBorder(BorderRange::LowerBorder, _id);

            while (_id >= id) {
                if (reservedIds_.find(_id))
                    reservedIds_.freeId(_id);
                else
                    freeIds_.add(_id);

                idArea_.pushBorder(BorderRange::LowerBorder);
                idArea_.checkBorder(BorderRange::LowerBorder, _id);
            }

            return true;
        }

        throw "-----------------------";
    }

    if (reservationMethod == ReservationMethod::ReserveRange) {
        if (id > idArea_.getMaxId()) {
            __T _id = 0;
            idArea_.checkBorder(BorderRange::UpperBorder, _id);

            while (_id <= id) {
                if (reservedIds_.find(_id))
                    reservedIds_.freeId(_id);

                idArea_.pushBorder(BorderRange::UpperBorder);
                idArea_.checkBorder(BorderRange::UpperBorder, _id);
            }

            return true;
        }

        if (id < idArea_.getMinId()) {
            __T _id = 0;
            idArea_.checkBorder(BorderRange::LowerBorder, _id);

            while (_id >= id) {
                if (reservedIds_.find(_id))
                    reservedIds_.freeId(_id);

                idArea_.pushBorder(BorderRange::LowerBorder);
                idArea_.checkBorder(BorderRange::LowerBorder, _id);
            }

            return true;
        }

        throw "-----------------------";
    }

    if (reservationMethod == ReservationMethod::ExpandRange) {
        if (id > idArea_.getMaxId()) {
            __T _id = 0;
            idArea_.checkBorder(BorderRange::UpperBorder, _id);

            while (_id <= id) {
                if (reservedIds_.find(_id))
                    reservedIds_.freeId(_id);
                else
                    freeIds_.add(_id);

                idArea_.pushBorder(BorderRange::UpperBorder);
                idArea_.checkBorder(BorderRange::UpperBorder, _id);
            }

            return true;
        }

        if (id < idArea_.getMinId()) {
            __T _id = 0;
            idArea_.checkBorder(BorderRange::LowerBorder, _id);

            while (_id >= id) {
                if (reservedIds_.find(_id))
                    reservedIds_.freeId(_id);
                else
                    freeIds_.add(_id);

                idArea_.pushBorder(BorderRange::LowerBorder);
                idArea_.checkBorder(BorderRange::LowerBorder, _id);
            }

            return true;
        }

        throw "-----------------------";
    }

    reservedIds_.add(id);   //isMaxIdOn_ не учитывается.
    return true;
}

template<class __T, class __Step>
int
Id_M::IdManager<__T, __Step>::
expandRangeToTop(BorderRange border, __T* id)
{
    int _errCode = IDM_ERR_SUCCESSFULLY;

    if (border == BorderRange::UpperBorder) {
        while (true) {
            if (reservedIds_.find(*id)) {
                reservedIds_.freeId(*id);
                _errCode = idArea_.pushBorder(BorderRange::UpperBorder, id);
                continue;
            }

            return _errCode;
        }
    }

    if (border == BorderRange::LowerBorder) {
        while (true) {
            if (reservedIds_.find(*id)) {
                reservedIds_.freeId(*id);
                _errCode = idArea_.pushBorder(BorderRange::LowerBorder, id);
                continue;
            }

            return _errCode;
        }
    }
}

template<class __T, class __Step>
int
Id_M::IdManager<__T, __Step>::
expandRangeToTopWithowtReserv(BorderRange border, __T* id)
{
    int _errCode = IDM_ERR_SUCCESSFULLY;

    if (border == BorderRange::UpperBorder) {
        while (true) {
            if (reservedIds_.find(*id)) {
                reservedIds_.freeId(*id);
                _errCode = idArea_.pushBorder(BorderRange::UpperBorder, id);
                idArea_.checkBorder(BorderRange::UpperBorder, id);
                continue;
            }

            return _errCode;
        }
    }

    if (border == BorderRange::LowerBorder) {
        while (true) {
            if (reservedIds_.find(*id)) {
                reservedIds_.freeId(*id);
                _errCode = idArea_.pushBorder(BorderRange::LowerBorder, id);
                idArea_.checkBorder(BorderRange::LowerBorder, id);
                continue;
            }

            return _errCode;
        }
    }
}

template<class __T, class __Step>
int
Id_M::IdManager<__T, __Step>::
expandRangeToBottom(BorderRange border, __T* id)
{
//    int _errCode = IDM_ERR_SUCCESSFULLY;

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
}

template<class __T, class __Step>
bool
Id_M::IdManager<__T, __Step>::
checkRangeBorder(__T value, BorderRange border) const
{
    switch (border) {
        case BorderRange::LowerBorder:    return (static_cast<long long>(value) - static_cast<long long>(idm_abs(step_)) < std::numeric_limits<__T>::min());
        case BorderRange::UpperBorder:    return (static_cast<long long>(value) + static_cast<long long>(idm_abs(step_)) > std::numeric_limits<__T>::max());

    default:    throw "Unknown enumerator: " + std::to_string(static_cast<int>(border)) + " in checkRangeBorder function.";
    }
}

template<class __T, class __Step>
template<class __TF>
inline __TF
Id_M::IdManager<__T, __Step>::
idm_abs(__TF value) const
{
    return value < 0 ? -value : value;
}


















//template<class __T, class __Step>
//Id_M::IdManager<__T, __Step>::
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
//Id_M::IdManager<__T, __Step>::
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
//Id_M::IdManager<__T, __Step>::
//~IdManager() {}

//template<class __T, class __Step>
//int
//Id_M::IdManager<__T, __Step>::
//getFreeId(__T& id)
//{
//    if (freeIds_.size()) {
//        freeIds_.getNextId(id);
//        return IDM_ERR_SUCCESSFULLY;
//    }

//    if (maxId_ == startId_ && startId_ == minId_) {

//    }

//    if (step_ > 0) {
//        if (isCrossingUpperBorder_)
//            return IDM_ERR_IDS_RUN_OUT;

//        id = maxId_;
//        maxId_ += static_cast<__T>(step_);
//        expandRange();
//        return IDM_ERR_SUCCESSFULLY;
//    }

//    if (step_ < 0) {
//        if (isCrossingLowerBorder_)
//            return IDM_ERR_IDS_RUN_OUT;

//        id = minId_;
//        minId_ += static_cast<__T>(step_);
//        expandRange();
//        return IDM_ERR_SUCCESSFULLY;
//    }
//}

//template<class __T, class __Step>
//bool
//Id_M::IdManager<__T, __Step>::
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
//Id_M::IdManager<__T, __Step>::
//expandRange()
//{
//    isCrossingUpperBorder_ = checkRangeBorder(maxId_, UpperBorder);
//    isCrossingLowerBorder_ = checkRangeBorder(minId_, LowerBorder);

//    while (true) {
//        if (reservedIds_.find(maxId_)) {
//            reservedIds_.freeId(maxId_);
//            isCrossingUpperBorder_ = checkRangeBorder(maxId_, UpperBorder);
//            if (!isCrossingUpperBorder_) {
//                maxId_ += static_cast<__T>(idm_abs(step_));
//            }
//            continue;
//        }

//        if (reservedIds_.find(minId_)) {
//            reservedIds_.freeId(minId_);
//            isCrossingLowerBorder_ = checkRangeBorder(minId_, LowerBorder);
//            if (!isCrossingLowerBorder_) {
//                minId_ -= static_cast<__T>(idm_abs(step_));
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
//Id_M::IdManager<__T, __Step>::
//checkRangeBorder(__T value, Borders border) const
//{
//    switch (border) {
//        case LowerBorder:    return (static_cast<long long>(value) - static_cast<long long>(idm_abs(step_)) < std::numeric_limits<__T>::min());
//        case UpperBorder:    return (static_cast<long long>(value) + static_cast<long long>(idm_abs(step_)) > std::numeric_limits<__T>::max());

//    default:    throw "Unknown enumerator: " + std::to_string(border) + " in checkRangeBorder function.";
//    }
//}

//template<class __T, class __Step>
//template<class __TF>
//inline __TF
//Id_M::IdManager<__T, __Step>::
//idm_abs(__TF value) const
//{
//    return value < 0 ? -value : value;
//}

























//template<class __T, class __Step>
//__T
//Id_M::IdManager<__T, __Step>::
//getFreeId()
//{




















//    if (std::is_unsigned<__T>::value)
//        return 1;
//    else
//        return 0;
//}


















template<class __T, class __Step>
void
Id_M::IdManager<__T, __Step>::
freeId(__T id)
{

}

template<class __T, class __Step>
void
Id_M::IdManager<__T, __Step>::
freeAll()
{

}

template<class __T, class __Step>
void
Id_M::IdManager<__T, __Step>::
setIdIssuingMethod(IdIssuingMethod idIssuingMethod)
{

}

template<class __T, class __Step>
Id_M::IdIssuingMethod
Id_M::IdManager<__T, __Step>::
getIdIssuingMethod()
{

}

template<class __T, class __Step>
bool
Id_M::IdManager<__T, __Step>::
findId(__T id) const
{
    return true;
}

//template<class __T, class __Step>
//__T
//Id_M::IdManager<__T, __Step>::
//getStartId() const
//{
//    return startId_;
//}

template<class __T, class __Step>
__Step
Id_M::IdManager<__T, __Step>::
getStep() const
{
    return step_;
}

//template<class __T, class __Step>
//__T
//Id_M::IdManager<__T, __Step>::
//getMaxId() const
//{
//    return maxId_;
//}

//template<class __T, class __Step>
//__T
//Id_M::IdManager<__T, __Step>::
//getMinId() const
//{
//    return minId_;
//}

template<class __T, class __Step>
bool
Id_M::IdManager<__T, __Step>::
isHardStep() const
{
    return isHardStep_;
}



template<class __T, class __Step>
Id_M::IdManager<__T, __Step>&
Id_M::IdManager<__T, __Step>::
operator=(const IdManager<__T, __Step>& other)
{
    return *this;
}

































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
