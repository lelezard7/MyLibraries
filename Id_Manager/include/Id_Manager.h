#ifndef _ID_MANAGER_
#define _ID_MANAGER_

#include <vector>
#include <set>
#include <type_traits>

#define ID_MANAGER_VER_MAJOR   0
#define ID_MANAGER_VER_MINOR   0
#define ID_MANAGER_VER_PATCH   0

#define IDM_ERR_NO_SUCH_ID                1 //TODO: Сделать возможность совмещать.
#define IDM_ERR_SUCCESSFULLY              0
#define IDM_ERR_IDS_RUN_OUT              -1
#define IDM_ERR_IMPOSSIBLE_REDUCE_RANGE  -2

#define IDM_POS_IN_RANGE                  0
#define IDM_POS_OUT_RANGE                 1
#define IDM_POS_ON_BORDER                 2


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

        bool getNextId(__T& id);
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

    //TODO: Добавить float_t, double_t.

    template<class __T, class __Step>
    constexpr bool is_types_combination_prohibited =
            (!std::is_same<__T, float>::value           &&
             !std::is_same<__T, double>::value          &&
             !std::is_same<__T, long double>::value)
                                                        &&
            ( std::is_same<__Step, float>::value        ||
              std::is_same<__Step, double>::value       ||
              std::is_same<__Step, long double>::value);




    enum class BorderRange
    {
        UpperBorder,
        LowerBorder
    };



    template<class __T>
    class IdArea
    {
    public:
        template<class __TC>
        struct Result
        {
            int errCode;
            int position;

            BorderRange border;
            bool state;
            __TC value;

            long long stepCount;
        };

    private:
        bool upperBorderState_;
        __T upperBorder_;
        __T upperLimit_;

        bool lowerBorderState_;
        __T lowerBorder_;
        __T lowerLimit_;

        __T start_;
        __T step_;

    public:
        IdArea(__T start = 0, __T step = 1);
        IdArea(const IdArea<__T>& other);
        ~IdArea();

        Result<__T> moveBorder(BorderRange borderRange, long long n);

        Result<__T> getIdInfo(BorderRange borderRange, long long n) const;
        Result<__T> getIdInfo(__T id) const;

        bool setBorderValue(BorderRange borderRange, __T value);
        inline __T getBorderValue(BorderRange borderRange) const;

        void setBorderState(BorderRange borderRange, bool state);
        inline bool getBorderState(BorderRange borderRange) const;

        bool setBorderLimit(BorderRange borderRange, __T limit);
        inline __T getBorderLimit(BorderRange borderRange) const;

        inline __T getStart() const;
        inline __T getStep() const;

        IdArea<__T>& operator=(const IdArea<__T>& other);

    private:
        template<class __TF>
        inline __TF idm_abs(__TF value) const;

        template<class __TF>
        inline bool isStandardId(__TF id, __TF start, __TF step) const;

    };


    template<class __T, class __Step = __T>
    class IdManager
    {
        IdContainer<__T> freeIds_;
        IdContainer<__T> reservedIds_;

        IdArea<__T> idArea_;

        __Step step_;
        bool isHardStep_;
        IdIssuingMethod idIssuingMethod_;

    public:
        IdManager(__T startId = 0,
                  __Step step = 1,
                  IdIssuingMethod idIssuingMethod = IdIssuingMethod::Dynamic,
                  bool isHardStep = false);
        IdManager(const IdManager<__T, __Step>& other);
        ~IdManager();

        int getFreeId(__T& id);
        bool reserveId(__T id, ReservationMethod reservationMethod = ReservationMethod::AutoSelect);

        void freeId(__T id);
        void freeAll();

        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);
        IdIssuingMethod getIdIssuingMethod();

        bool findId(__T id) const;

        bool isStandardId(__T id) const;

//        __T getStartId() const;
        __Step getStep() const;
//        __T getMaxId() const;
//        __T getMinId() const;
        bool isHardStep() const;

        IdManager<__T, __Step>& operator=(const IdManager<__T, __Step>& other);

    private:
        int expandRangeToTop(BorderRange border, __T* id);
        int expandRangeToTopWithowtReserv(BorderRange border, __T* id);

        int expandRangeToBottom(BorderRange border, __T* id);


        int expandRange(__T* id);
        bool checkRangeBorder(__T value, BorderRange border) const;

        template<class __TF>
        inline __TF idm_abs(__TF value) const;

    };










//    template<class __T, class __Step = __T>
//    class IdManager
//    {
//        enum Borders
//        {
//            LowerBorder,
//            UpperBorder
//        };

//    private:
//        IdContainer<__T> freeIds_;
//        IdContainer<__T> reservedIds_;

//        __T maxId_;
//        __T minId_;
//        __T startId_;

//        bool isCrossingUpperBorder_;
//        bool isCrossingLowerBorder_;

//        __Step step_;
//        bool isHardStep_;
//        IdIssuingMethod idIssuingMethod_;

//    public:
//        IdManager(__T startId = 0,
//                  __Step step = 1,
//                  IdIssuingMethod idIssuingMethod = IdIssuingMethod::Dynamic,
//                  bool isHardStep = false);
//        IdManager(const IdManager<__T, __Step>& other);
//        ~IdManager();

//        int getFreeId(__T& id);
//        bool reserveId(__T id, ReservationMethod reservationMethod = ReservationMethod::AutoSelect);

//        void freeId(__T id);
//        void freeAll();

//        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);
//        IdIssuingMethod getIdIssuingMethod();

//        bool findId(__T id) const;

//        bool isStandardId(__T id) const;

//        __T getStartId() const;
//        __Step getStep() const;
//        __T getMaxId() const;
//        __T getMinId() const;
//        bool isHardStep() const;

//        IdManager<__T, __Step>& operator=(const IdManager<__T, __Step>& other);

//    private:
//        void expandRange();
//        bool checkRangeBorder(__T value, Borders border) const;

//        template<class __TF>
//        inline __TF idm_abs(__TF value) const;

//    };
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
