#include "../include/Id_Manager.h"
#include <cmath>
#include <cstdlib>


template<class __T>
IdManager<__T>::
IdManager()
    : IdManager((__T)0, (__T)1, false) {}

template<class __T>
IdManager<__T>::
IdManager(const IdManager<__T>& other)
    : freeIds_(other.freeIds_),
      reservedIds_(other.reservedIds_),
      maxId_(other.maxId_),
      minId_(other.minId_),
      startId_(other.startId_),
      step_(other.step_),
      isHardStep_(other.isHardStep) {}

template<class __T>
IdManager<__T>::
IdManager(__T startId, __T step, bool isHardStep)
    : maxId_(startId),
      minId_(startId),
      startId_(startId),
      isHardStep_(isHardStep)
{
    step_ = ((step == (__T)0) ? (__T)1 : step);
}

template<class __T>
IdManager<__T>::
~IdManager() {}

//template<class __T>
//__T
//IdManager<__T>::
//getFreeId()
//{
//    __T _freeId = (__T)0;


//}





























template<class __T>
__T
IdManager<__T>::
getFreeId()
{
    __T _freeId = (__T)0;

    if (maxId_ < startId_) {
        _freeId = maxId_;
        maxId_ += std::abs(step_);

        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
            if (*it == maxId_) {
                reservedIds_.erase(it);
                maxId_ += std::abs(step_);
                it = reservedIds_.begin();
                continue;
            }

            ++it;
        }

        return _freeId;
    }
    else if (minId_ > startId_) {
        _freeId = minId_;
        minId_ -= std::abs(step_);

        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
            if (*it == minId_) {
                reservedIds_.erase(it);
                minId_ -= std::abs(step_);
                it = reservedIds_.begin();
                continue;
            }

            ++it;
        }

        return _freeId;
    }


    if (freeIds_.size() != 0) {
        auto _it = freeIds_.begin();
        _freeId = *_it;
        freeIds_.erase(_it);

        if (_freeId == maxId_) {
            maxId_ += std::abs(step_);

            for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
                if (*it == maxId_) {
                    reservedIds_.erase(it);
                    maxId_ += std::abs(step_);
                    it = reservedIds_.begin();
                    continue;
                }

                ++it;
            }
        }

        if (_freeId == minId_) {
            minId_ -= std::abs(step_);

            for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
                if (*it == minId_) {
                    reservedIds_.erase(it);
                    minId_ -= std::abs(step_);
                    it = reservedIds_.begin();
                    continue;
                }

                ++it;
            }
        }


        return _freeId;
    }

    if (maxId_ == startId_ && minId_ == startId_) {
        maxId_ += std::abs(step_);
        minId_ -= std::abs(step_);

        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
            if (*it == maxId_) {
                reservedIds_.erase(it);
                maxId_ += std::abs(step_);
                it = reservedIds_.begin();
                continue;
            }

            if (*it == minId_) {
                reservedIds_.erase(it);
                minId_ -= std::abs(step_);
                it = reservedIds_.begin();
                continue;
            }

            ++it;
        }

        return startId_;
    }

    if (step_ < (__T)0) {
        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
            if (*it == minId_) {
                reservedIds_.erase(it);
                minId_ += step_;
                it = reservedIds_.begin();
                continue;
            }
            ++it;
        }

        _freeId = minId_;
        minId_ += step_;
    }
    else {
        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
            if (*it == maxId_) {
                reservedIds_.erase(it);
                maxId_ += step_;
                it = reservedIds_.begin();
                continue;
            }
            ++it;
        }

        _freeId = maxId_;
        maxId_ += step_;
    }

    for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
        if (*it == maxId_) {
            reservedIds_.erase(it);
            maxId_ += std::abs(step_);
            it = reservedIds_.begin();
            continue;
        }

        if (*it == minId_) {
            reservedIds_.erase(it);
            minId_ -= std::abs(step_);
            it = reservedIds_.begin();
            continue;
        }

        ++it;
    }

    return _freeId;
}

template<class __T>
bool
IdManager<__T>::
reserveId(__T id, ReservationMethod reservationMethod)
{
    if (!isStandardId(id)) {
        if (isHardStep_) {
            return false;
        }

        for (size_t i = 0; i < reservedIds_.size(); ++i) {
            if (reservedIds_[i] == id)
                return false;
        }

        if (reservationMethod == Interpolate) {
            if (id > maxId_) {
                for (__T i = maxId_; i < id; i += std::abs(step_)) {

                    bool _isBreak = false;

                    for (size_t j = 0; j < freeIds_.size(); ++j) {
                        if (freeIds_[j] == i) {
                            maxId_ += std::abs(step_);
                            _isBreak = true;
                            break;
                        }
                    }

                    if (_isBreak == true)
                        continue;

                    if (reservedIds_.size() != 0) {
                        for (size_t j = 0; j < reservedIds_.size(); ++j) {
                            if (reservedIds_[j] == i) {
                                auto _it = reservedIds_.begin();
                                std::advance(_it, j);
                                reservedIds_.erase(_it);
                                break;
                            }

                            if (reservedIds_.size() - 1 == j)
                                freeIds_.push_back(i);
                        }
                    }
                    else {
                        freeIds_.push_back(i);
                    }

                    maxId_ += std::abs(step_);
                }
            }

            if (id < minId_) {
                for (__T i = minId_; i > id; i -= std::abs(step_)) {

                    bool _isBreak = false;

                    for (size_t j = 0; j < freeIds_.size(); ++j) {
                        if (freeIds_[j] == i) {
                            minId_ -= std::abs(step_);
                            _isBreak = true;
                            break;
                        }
                    }

                    if (_isBreak == true)
                        continue;

                    if (reservedIds_.size() != 0) {
                        for (size_t j = 0; j < reservedIds_.size(); ++j) {
                            if (reservedIds_[j] == i) {
                                auto _it = reservedIds_.begin();
                                std::advance(_it, j);
                                reservedIds_.erase(_it);
                                break;
                            }

                            if (reservedIds_.size() - 1 == j)
                                freeIds_.push_back(i);
                        }
                    }
                    else {
                        freeIds_.push_back(i);
                    }

                    minId_ -= std::abs(step_);
                }
            }
        }

        reservedIds_.push_back(id);
        return true;
    }

    if (id == startId_) {
        if (maxId_ == startId_ && minId_ == startId_) {
            maxId_ += std::abs(step_);
            minId_ -= std::abs(step_);

            for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
                if (*it == maxId_) {
                    reservedIds_.erase(it);
                    maxId_ += std::abs(step_);
                    it = reservedIds_.begin();
                    continue;
                }

                if (*it == minId_) {
                    reservedIds_.erase(it);
                    minId_ -= std::abs(step_);
                    it = reservedIds_.begin();
                    continue;
                }

                ++it;
            }

            return true;
        }
    }

    for (auto it = freeIds_.begin(); it != freeIds_.end(); ++it) {
        if (*it == id) {
            freeIds_.erase(it);

            if (id == startId_) {
                if (maxId_ == startId_)
                    maxId_ += std::abs(step_);

                if (minId_ == startId_)
                    minId_ -= std::abs(step_);

                for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
                    if (*it == maxId_) {
                        reservedIds_.erase(it);
                        maxId_ += std::abs(step_);
                        it = reservedIds_.begin();
                        continue;
                    }

                    if (*it == minId_) {
                        reservedIds_.erase(it);
                        minId_ -= std::abs(step_);
                        it = reservedIds_.begin();
                        continue;
                    }

                    ++it;
                }
            }

            return true;
        }
    }

    for (size_t i = 0; i < reservedIds_.size(); ++i) {
        if (reservedIds_[i] == id)
            return false;
    }

    if (id < maxId_ && id > minId_)
        return false;

    if (id == maxId_) {
        maxId_ += std::abs(step_);

        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
            if (*it == maxId_) {
                reservedIds_.erase(it);
                maxId_ += std::abs(step_);
                it = reservedIds_.begin();
                continue;
            }

            ++it;
        }

        return true;
    }

    if (id == minId_) {
        minId_ -= std::abs(step_);

        for (auto it = reservedIds_.begin(); it != reservedIds_.end();) {
            if (*it == minId_) {
                reservedIds_.erase(it);
                minId_ -= std::abs(step_);
                it = reservedIds_.begin();
                continue;
            }

//            bool _isBreak = false;

//            for (size_t j = 0; j < freeIds_.size(); ++j) {
//                if (freeIds_[j] == i) {
//                    _isBreak = true;
//                    break;
//                }
//            }

//            if (_isBreak == true)
//                continue;

            ++it;
        }

        return true;
    }

    if (reservationMethod == AutoSelect || reservationMethod == Interpolate) {
        if (id > maxId_) {
            for (__T i = maxId_; i < id; i += std::abs(step_)) {

                bool _isBreak = false;

                for (size_t j = 0; j < freeIds_.size(); ++j) {
                    if (freeIds_[j] == i) {
                        _isBreak = true;
                        break;
                    }
                }

                if (_isBreak == true)
                    continue;

                if (reservedIds_.size() != 0) {
                    for (size_t j = 0; j < reservedIds_.size(); ++j) {
                        if (reservedIds_[j] == i) {
                            auto _it = reservedIds_.begin();
                            std::advance(_it, j);
                            reservedIds_.erase(_it);
                            break;
                        }

                        if (reservedIds_.size() - 1 == j)
                            freeIds_.push_back(i);
                    }
                }
                else {
                    freeIds_.push_back(i);
                }
            }

            maxId_ = id + std::abs(step_);
            return true;
        }

        if (id < minId_) {
            for (__T i = minId_; i > id; i -= std::abs(step_)) {

                bool _isBreak = false;

                for (size_t j = 0; j < freeIds_.size(); ++j) {
                    if (freeIds_[j] == i) {
                        _isBreak = true;
                        break;
                    }
                }

                if (_isBreak == true)
                    continue;

                if (reservedIds_.size() != 0) {
                    for (size_t j = 0; j < reservedIds_.size(); ++j) {
                        if (reservedIds_[j] == i) {
                            auto _it = reservedIds_.begin();
                            std::advance(_it, j);
                            reservedIds_.erase(_it);
                            break;
                        }

                        if (reservedIds_.size() - 1 == j)
                            freeIds_.push_back(i);
                    }
                }
                else {
                    freeIds_.push_back(i);
                }
            }

            minId_ = id - std::abs(step_);
            return true;
        }
    }

    reservedIds_.push_back(id);
    return true;
}

template<class __T>
void
IdManager<__T>::
freeId(__T id)
{
    if (!isStandardId(id)) {
        if (isHardStep_) {
            return;
        }

        for (auto it = reservedIds_.begin(); it != reservedIds_.end(); ++it) {
            if (*it == id) {
                reservedIds_.erase(it);
                return;
            }
        }

        return;
    }

    for (auto it = reservedIds_.begin(); it != reservedIds_.end(); ++it) {
        if (*it == id) {
            reservedIds_.erase(it);
            return;
        }
    }

    if (id >= maxId_ || id <= minId_)
        return;

    for (size_t i = 0; i < freeIds_.size(); ++i) {
        if (freeIds_[i] == id)
            return;
    }

    if (maxId_ - std::abs(step_) == id) {
        maxId_ -= std::abs(step_);
        return;
    }

    if (minId_ + std::abs(step_) == id) {
        minId_ += std::abs(step_);
        return;
    }

    freeIds_.push_back(id);
}

template<class __T>
void
IdManager<__T>::
freeAll()
{
    freeIds_.clear();
    reservedIds_.clear();
    maxId_ = startId_;
    minId_ = startId_;
}

template<class __T>
bool
IdManager<__T>::
findId(__T id) const
{
    if (!isStandardId(id)) {
        if (isHardStep_) {
            return false;
        }

        for (size_t i = 0; i < reservedIds_.size(); ++i) {
            if (reservedIds_[i] == id)
                return true;
        }

        return false;
    }

    for (size_t i = 0; i < reservedIds_.size(); ++i) {
        if (reservedIds_[i] == id)
            return true;
    }

    if (id >= maxId_ || id <= minId_)
        return false;

    for (size_t i = 0; i < freeIds_.size(); ++i) {
        if (freeIds_[i] == id)
            return false;
    }

    return true;
}

template<class __T>
__T
IdManager<__T>::
getStartId() const
{
    return startId_;
}

template<class __T>
__T
IdManager<__T>::
getStep() const
{
    return step_;
}

template<class __T>
__T
IdManager<__T>::
getMaxId() const
{
    return maxId_;
}

template<class __T>
__T
IdManager<__T>::
getMinId() const
{
    return minId_;
}

template<class __T>
bool
IdManager<__T>::
isHardStep() const
{
    return isHardStep_;
}

template<class __T>
bool
IdManager<__T>::
isStandardId(__T id) const
{
    float n = std::abs((float)(id - startId_ + step_) / (float)step_);
    return (float)n - (size_t)n == (float)0.0;
}

template<class __T>
IdManager<__T>&
IdManager<__T>::
operator=(const IdManager<__T>& other)
{
    freeIds_ = other.freeIds_;
    reservedIds_ = other.reservedIds_;
    maxId_ = other.maxId_;
    minId_ = other.minId_;
    startId_ = other.startId_;
    step_ = other.step_;
    isHardStep_ = other.isHardStep_;

    return *this;
}
