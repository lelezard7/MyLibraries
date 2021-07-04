#ifndef _ID_MANAGER_
#define _ID_MANAGER_

#include <vector>

#define ID_MANAGER_VER_MAJOR   0
#define ID_MANAGER_VER_MINOR   0
#define ID_MANAGER_VER_PATCH   0


//TODO: Добавить поддержку unsigned
//TODO: Добавить возможность резервировать диапазон


template<class __T>
class IdManager
{
public:
    enum ReservationMethod
    {
        Interpolate,
        NonInterpolate,
        AutoSelect
        //InterpolateWithReserving  TODO: Добавить в следующей версии
    };

private:
    std::vector<__T> freeIds_;
    std::vector<__T> reservedIds_;
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
    bool reserveId(__T id, ReservationMethod reservationMethod = AutoSelect);

    void freeId(__T id);
    void freeAll();

    bool findId(__T id) const;

    __T getStartId() const;
    __T getStep() const;
    __T getMaxId() const;
    __T getMinId() const;
    bool isHardStep() const;
    bool isStandardId(__T id) const;

    IdManager<__T>& operator=(const IdManager<__T>& other);

};


#include "../src/Id_Manager.inl"

#endif
