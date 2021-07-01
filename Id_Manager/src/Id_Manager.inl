#include "../include/Id_Manager.h"
#include <cmath>


template<class __T>
IdManager<__T>::
IdManager()
    : IdManager((__T)0, (__T)1, false) {}

template<class __T>
IdManager<__T>::
IdManager(const IdManager<__T>& other)
    : freeId_(other.freeId_),
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

template<class __T>
__T
IdManager<__T>::
getFreeId()
{
    __T _freeId;

    if (freeId_.size() != 0) {
        auto _it = freeId_.begin();
        _freeId = *_it;
        freeId_.erase(_it);
        return _freeId;
    }

    if (maxId_ == startId_ && minId_ == startId_) {
        _freeId = startId_;
        maxId_ += std::abs(step_);
        minId_ -= std::abs(step_);
    }
    else if (step_ < (__T)0) {
        _freeId = minId_;
        minId_ += step_;
    }
    else {
        _freeId = maxId_;
        maxId_ += step_;
    }

    return _freeId;
}

template<class __T>
bool
IdManager<__T>::
reserveId(__T id)
{
    if (isHardStep_) {
        if (std::fmod(id, step_) != (__T)0) {
            return false;
        }
    }

    for (auto it = freeId_.begin(); it != freeId_.end(); ++it) {
        if (*it == id) {
            freeId_.erase(it);
            return true;
        }
    }



    if (id >= maxId_) { //TODO: Добавить во всех функциях
//        if (std::fmod(id, step_) != (__T)0) {
//            return false;
//        }

        for (__T i = maxId_; i < id; i += std::abs(step_)) {
            freeId_.push_back(i);
        }

        maxId_ = id + std::abs(step_);
        return true;
    }

    if (id <= minId_) {
        //        if (std::fmod(id, step_) != (__T)0) {
        //            return false;
        //        }

        for (__T i = minId_; i > id; i -= std::abs(step_)) {
            freeId_.push_back(i);
        }

        minId_ = id - std::abs(step_);
        return true;
    }

    return false;
}

template<class __T>
void
IdManager<__T>::
freeId(__T id)
{
    if (isHardStep_) {
        if (std::fmod(id, step_) != (__T)0) {
            return;
        }
    }

    if (id >= maxId_ || id <= minId_)
        return;

    for (size_t i = 0; i < freeId_.size(); ++i) {
        if (freeId_[i] == id)
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

    freeId_.push_back(id);
}

template<class __T>
void
IdManager<__T>::
freeAll()
{
    freeId_.clear();
    maxId_ = startId_;
    minId_ = startId_;
}

template<class __T>
bool
IdManager<__T>::
findId(__T id) const
{
    if (isHardStep_) {
        if (std::fmod(id, step_) != (__T)0) {
            return false;
        }
    }

    if (id >= maxId_ || id <= minId_)
        return false;

    for (size_t i = 0; i < freeId_.size(); ++i) {
        if (freeId_[i] == id)
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
IdManager<__T>&
IdManager<__T>::
operator=(const IdManager<__T>& other)
{
    freeId_ = other.freeId_;
    maxId_ = other.maxId_;
    minId_ = other.minId_;
    startId_ = other.startId_;
    step_ = other.step_;
    isHardStep_ = other.isHardStep_;

    return *this;
}
