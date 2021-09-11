#include "../IdManagement.h"

//std::find, std::binary_search
#include <algorithm>


template<class T>
ONF::IdContainer<T>::
IdContainer(IdIssuingMethod idIssuingMethod)
    : idIssuingMethod_(idIssuingMethod) {}

template<class T>
ONF::IdContainer<T>::
~IdContainer() {}

template<class T>
bool
ONF::IdContainer<T>::
add(T id)
{
    if (std::find(container_.begin(), container_.end(), id) != container_.end())
        return false;

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        container_.push_back(id);
        return true;
    }

    if (idIssuingMethod_ == IdIssuingMethod::Static_Ascending) {
        container_.insert(std::lower_bound(container_.begin(), container_.end(), id), id);
        return true;
    }

    container_.insert(std::lower_bound(container_.begin(), container_.end(), id, std::greater<T>()), id);
    return true;
}

template<class T>
std::optional<T>
ONF::IdContainer<T>::
getNextId()
{
    auto it = container_.begin();

    if (it == container_.end())
        return std::nullopt;

    T id = *it;
    container_.erase(std::move(it));
    return id;
}

template<class T>
void
ONF::IdContainer<T>::
erase(T id)
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic) {
        auto it = std::find(container_.begin(), container_.end(), id);

        if (it != container_.end())
            container_.erase(std::move(it));

        return;
    }

    if (idIssuingMethod_ == IdIssuingMethod::Static_Ascending) {
        auto it = std::lower_bound(container_.begin(), container_.end(), id);

        if (it != container_.end() && !(id < *it))
            container_.erase(std::move(it));

        return;
    }

    auto it = std::lower_bound(container_.begin(), container_.end(), id, std::greater<T>());

    if (it != container_.end() && !std::greater<T>()(id, *it))
        container_.erase(std::move(it));
}

template<class T>
void
ONF::IdContainer<T>::
clear()
{
    container_.clear();
}

template<class T>
bool
ONF::IdContainer<T>::
find(T id) const
{
    if (idIssuingMethod_ == IdIssuingMethod::Dynamic)
        return std::find(container_.begin(), container_.end(), id) != container_.end();

    if (idIssuingMethod_ == IdIssuingMethod::Static_Ascending)
        return std::binary_search(container_.begin(), container_.end(), id);

    return std::binary_search(container_.begin(), container_.end(), id, std::greater<T>());
}

template<class T>
std::optional<T>
ONF::IdContainer<T>::
findByIndex(size_t index) const
{
    if (index >= container_.size())
        return std::nullopt;

    return *std::next(container_.begin(), index);
}

template<class T>
void
ONF::IdContainer<T>::
setIdIssuingMethod(IdIssuingMethod idIssuingMethod)
{
    if (idIssuingMethod == idIssuingMethod_)
        return;

    idIssuingMethod_ = idIssuingMethod;

    if (idIssuingMethod_ == IdIssuingMethod::Dynamic)
        return;

    if (idIssuingMethod_ == IdIssuingMethod::Static_Ascending) {
        container_.sort();
        return;
    }

    container_.sort(std::greater<T>());
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
    return container_.size();
}
