#ifndef _ID_MANAGER_
#define _ID_MANAGER_

#include <vector>


template<class __T>
class IdManager
{
    std::vector<__T> freeId_;
    __T maxId_;

    const __T startId_;
    const __T step_;

public:
    IdManager();
    IdManager(const IdManager<__T>& other);
    IdManager(__T startId, __T step = (__T)1);
    ~IdManager();

    __T getFreeId();
    bool reserveId(__T id);

    void freeId(__T id);
    void freeAll();

    bool checkId(__T id) const;

    __T getStartId() const;
    __T getMaxId() const;
    __T getStep() const;

    IdManager<__T>& operator=(const IdManager<__T>& other);

};


#include "Id_Manager.inl"

#endif
