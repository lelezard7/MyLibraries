#ifndef _ID_MANAGER_
#define _ID_MANAGER_

#include <vector>


template<class __T>
class IdManager
{
    std::vector<__T> freeId_;
    __T maxId_;
    __T minId_;

    __T startId_;
    __T step_;
    bool isHardStep_;

public:
    IdManager();
    IdManager(const IdManager<__T>& other);
    IdManager(__T startId, __T step = (__T)1, bool isHardStep = false);
    ~IdManager();

    __T getFreeId();
    bool reserveId(__T id);

    void freeId(__T id);
    void freeAll();

    bool findId(__T id) const;

    __T getStartId() const;
    __T getStep() const;
    __T getMaxId() const;
    __T getMinId() const;
    bool isHardStep() const;

    IdManager<__T>& operator=(const IdManager<__T>& other);

};


#include "../src/Id_Manager.inl"

#endif
