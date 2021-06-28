#include "Id_Manager.h"


template<class __T>
IdManager<__T>::
IdManager()
    : maxId_((__T)0),
      startId_((__T)0),
      step_((__T)1) {}

template<class __T>
IdManager<__T>::
IdManager(const IdManager<__T>& other)
    : freeId_(other.freeId_),
      maxId_(other.maxId_),
      startId_(other.startId_),
      step_(other.step_) {}

template<class __T>
IdManager<__T>::
IdManager(__T startId, __T step)
    : maxId_(startId),
      startId_(startId),
      step_(step) {}

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

    _freeId = maxId_;
    maxId_ += step_;
    return _freeId;
}

template<class __T>
bool
IdManager<__T>::
reserveId(__T id)
{
    if (id < startId_)
        return false;

    if (id >= maxId_) {
        for (__T i = maxId_; i < id; i += step_) {
            freeId_.push_back(i);
        }

        maxId_ = id + step_;
        return true;
    }

    for (auto it = freeId_.begin(); it != freeId_.end(); ++it) {
        if (*it == id) {
            freeId_.erase(it);
            return true;
        }
    }

    return false;
}

template<class __T>
void
IdManager<__T>::
freeId(__T id)
{
    if (id < startId_)
        return;

    if (id >= maxId_)
        return;

    for (size_t i = 0; i < freeId_.size(); ++i) {
        if (freeId_[i] == id)
            return;
    }

    if (maxId_ - step_ == id) {
        maxId_ -= step_;
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
}

template<class __T>
bool
IdManager<__T>::
checkId(__T id) const
{
    if (id < startId_)
        return false;

    if (id >= maxId_)
        return true;

    for (size_t i = 0; i < freeId_.size(); ++i) {
        if (freeId_[i] == id)
            return true;
    }

    return false;
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
getMaxId() const
{
    return maxId_;
}

template<class __T>
__T
IdManager<__T>::
getStep() const
{
    return step_;
}

template<class __T>
IdManager<__T>&
IdManager<__T>::
operator=(const IdManager<__T>& other)
{
    freeId_ = other.freeId_;
    maxId_ = other.maxId_;
    startId_ = other.startId_;
    step_ = other.step_;

    return *this;
}
