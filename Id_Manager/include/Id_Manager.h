#ifndef _ID_MANAGER_
#define _ID_MANAGER_

#include <vector>
#include <set>

#define ID_MANAGER_VER_MAJOR   0
#define ID_MANAGER_VER_MINOR   0
#define ID_MANAGER_VER_PATCH   0


namespace Id_M
{
    enum class ReservationMethod
    {
        Interpolate,
        NonInterpolate,
        AutoSelect,

        ReserveRange,
        ExpandRange
    };

    enum class IdIssuingMethod
    {
        Dynamic,
        Ascending,
        Descending
    };


    template<class __T>
    class IdContainer
    {
        std::vector<__T> unorderedFreeIds_;
        std::set<__T> orderedFreeIds_;

        IdIssuingMethod idIssuingMethod_;

    public:
        IdContainer(IdIssuingMethod idIssuingMethod = IdIssuingMethod::Dynamic);
        IdContainer(const IdContainer<__T>& other);
        virtual ~IdContainer();

        bool getNextId(__T* id);
        bool add(__T id);

        bool find(__T id) const;
        size_t size() const;

        void freeId(__T id);
        void clear();

        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);
        IdIssuingMethod getIdIssuingMethod() const;

        IdContainer<__T>& operator=(const IdContainer<__T>& other);

    protected:
        size_t getOrderedFreeIdsSize() const;
        size_t getUnorderedFreeIdsSize() const;

    };


    template<class __T, class __Step>
    class IdManager
    {
        IdContainer<__T> freeIds_;
        std::vector<__T> reservedIds_;

        __T maxId_;
        __T minId_;
        __T startId_;

        __Step step_;
        bool isHardStep_;
        IdIssuingMethod idIssuingMethod_;

    public:
        IdManager();
        IdManager(const IdManager<__T, __Step>& other);
        IdManager(__T startId,
                  __Step step = (__Step)1,
                  IdIssuingMethod idIssuingMethod = IdIssuingMethod::Dynamic,
                  bool isHardStep = false);
        ~IdManager();

        __T getFreeId();
        bool reserveId(__T id, ReservationMethod reservationMethod = ReservationMethod::AutoSelect);

        void freeId(__T id);
        void freeAll();

        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);

        bool findId(__T id) const;
        bool isStandardId(__T id) const;

        __T getStartId() const;
        __Step getStep() const;
        __T getMaxId() const;
        __T getMinId() const;
        bool isHardStep() const;

        IdManager<__T, __Step>& operator=(const IdManager<__T, __Step>& other);

    };
}


#include "../src/Id_Manager.inl"

#endif













//template<class __T>
//class IdManager
//{
//public:
//    enum ReservationMethod
//    {
//        Interpolate,
//        NonInterpolate,
//        AutoSelect
//    };

//private:
//    std::vector<__T> freeIds_;
//    std::vector<__T> reservedIds_;
//    __T maxId_;
//    __T minId_;

//    __T startId_;
//    __T step_;
//    bool isHardStep_;

//public:
//    IdManager();
//    IdManager(const IdManager<__T>& other);
//    IdManager(__T startId, __T step = (__T)1, bool isHardStep = false);
//    ~IdManager();

//    __T getFreeId();
//    bool reserveId(__T id, ReservationMethod reservationMethod = AutoSelect);

//    void freeId(__T id);
//    void freeAll();

//    bool findId(__T id) const;

//    __T getStartId() const;
//    __T getStep() const;
//    __T getMaxId() const;
//    __T getMinId() const;
//    bool isHardStep() const;
//    bool isStandardId(__T id) const;

//    IdManager<__T>& operator=(const IdManager<__T>& other);

//};


//#include "../src/Id_Manager.inl"

//#endif
