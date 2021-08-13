#include "../IdManagement.h"

//std::find
#include <algorithm>


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
getNextId()
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

    if (idIssuingMethod_ == IdIssuingMethod::Static_Ascending) {
        auto it = orderedIds_.begin();
        T id = *it;
        orderedIds_.erase(std::move(it));
        return id;
    }

    auto it = orderedIds_.end();
    T id = *(--it);

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
void
ONF::IdContainer<T>::
clear()
{
    unorderedIds_.clear();
    orderedIds_.clear();
}

template<class T>
bool
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

    if (idIssuingMethod_ == IdIssuingMethod::Static_Ascending)
        return *std::next(orderedIds_.begin(), index);

    return *std::prev(orderedIds_.end(), index + 1);
}

template<class T>
void
ONF::IdContainer<T>::
setIdIssuingMethod(IdIssuingMethod idIssuingMethod)
{
    if (idIssuingMethod == idIssuingMethod_)
        return;

    if ((idIssuingMethod == IdIssuingMethod::Static_Ascending || idIssuingMethod == IdIssuingMethod::Static_Descending) &&
        (idIssuingMethod_ == IdIssuingMethod::Static_Ascending || idIssuingMethod_ == IdIssuingMethod::Static_Descending)) {
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
ONF::IdIssuingMethod
ONF::IdContainer<T>::
getIdIssuingMethod() const
{
    return idIssuingMethod_;
}

template<class T>
size_t
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
size_t
ONF::IdContainer<T>::
getUnorderedIdsSize() const
{
    return unorderedIds_.size();
}

template<class T>
size_t
ONF::IdContainer<T>::
getOrderedIdsSize() const
{
    return orderedIds_.size();
}
