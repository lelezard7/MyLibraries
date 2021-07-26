#ifndef ID_MANAGER_H_
#define ID_MANAGER_H_

#include <ONF.h>
#include <list>
#include <set>
#include <type_traits>
#include <optional>

#define IDRF_NOT_SET                    0x00000
#define IDRF_SUCCESSFULLY               0x00001
#define IDRF_ID_OUT_RANGE               0x00002
#define IDRF_RANGE_ARE_BENT             0x00004
#define IDRF_ID_AT_START                0x00008

#define IDRP_NOT_SET                   -1
#define IDRP_IN_RANGE                   0
#define IDRP_ON_BORDER                  1
#define IDRP_OUT_RANGE                  2


namespace ONF
{
    enum class IdIssuingMethod
    {
        Dynamic,
        Ascending,
        Descending
    };


    template<class T>
    class IdContainer
    {
        std::list<T> unorderedIds_;
        std::set<T> orderedIds_;

        IdIssuingMethod idIssuingMethod_;

    public:
        IdContainer(IdIssuingMethod idIssuingMethod = IdIssuingMethod::Dynamic);
        IdContainer(const IdContainer<T>& other);
        IdContainer(IdContainer<T>&& other);
        virtual ~IdContainer();

        bool add(T id);
        std::optional<T> getNext();

        void erase(T id);
        inline void clear();

        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);
        inline IdIssuingMethod getIdIssuingMethod() const;

        inline bool find(T id) const;
        std::optional<T> findByIndex(size_t index) const;

        inline size_t size() const;

        IdContainer<T>& operator=(const IdContainer<T>& other);
        IdContainer<T>& operator=(IdContainer<T>&& other);

    protected:
        inline size_t getUnorderedIdsSize() const;
        inline size_t getOrderedIdsSize() const;

    };


    enum class BorderRange
    {
        UpperBorder,
        LowerBorder
    };


    template<class T>
    inline bool isStandardId(T target, T start, T step) {
        ldouble An = static_cast<ldouble>(target);
        ldouble A1 = static_cast<ldouble>(start);
        ldouble d  = static_cast<ldouble>(step);

        ldouble n = std::abs((An - A1 + d) / d);
        return (n - static_cast<ulonglong>(n) == static_cast<ldouble>(0.0));
    }

    template<class T>
    inline T moveFromId(T start, T step, longlong n) {
        return start + (n * step);
    }


    template<class T>
    class IdRange
    {
    public:
        class IdInfo
        {
        public:
            IdInfo();
            IdInfo(const IdInfo& other);
            IdInfo(IdInfo&& other);
            ~IdInfo();

            unsigned    flags;
            int         position;

            BorderRange border;
            bool        state;
            T           value;

            longlong    stepCount;

            IdInfo& operator=(const IdInfo& other);
            IdInfo& operator=(IdInfo&& other);
        };

    private:
        enum class Action
        {
            Move,
            GetInfo
        };

        bool upperBorderState_;
        T upperBorder_;
        T upperLimit_;

        bool lowerBorderState_;
        T lowerBorder_;
        T lowerLimit_;

        T start_;
        T step_;

    public:
        IdRange(T start = 0, T step = 1);
        IdRange(const IdRange<T>& other);
        IdRange(IdRange<T>&& other);
        virtual ~IdRange();

        IdInfo moveBorder(BorderRange borderRange, longlong n);

        IdInfo getIdInfo(BorderRange borderRange, longlong n) const;
        std::optional<IdInfo> getIdInfo(BorderRange borderRange, T id, longlong n) const;

        inline void reset();

        bool setBorderValue(BorderRange borderRange, T value);
        inline T getBorderValue(BorderRange borderRange) const;

        inline void setBorderState(BorderRange borderRange, bool state);
        inline bool getBorderState(BorderRange borderRange) const;

        bool setBorderLimit(BorderRange borderRange, T value);
        inline T getBorderLimit(BorderRange borderRange) const;

        inline T getStart() const;
        inline T getStep() const;

        IdRange<T>& operator=(const IdRange<T>& other);
        IdRange<T>& operator=(IdRange<T>&& other);

    private:
        //TODO: Написать в документации почему я поставил возращаемый тип int, а не bool.
        int fillIdInfo(IdInfo& idInfo, BorderRange borderRange, T borderValue, ldouble n, Action action) const;

        bool fillInfoAboutMoveUp(IdInfo& idInfo, T borderValue, T borderLimit, ldouble n) const;
        bool fillInfoAboutMovemDown(IdInfo& idInfo, T borderValue, T borderLimit, ldouble n) const;

        void fillInfoAboutTerritory(IdInfo& idInfo, BorderRange borderRange, T borderValue) const;
        void fillInfoAboutPos(IdInfo& idInfo, ldouble n, Action action) const;

    };


    enum class ReservationMethod
    {
        Interpolate,
        NonInterpolate,
        AutoSelect,

        ReserveRange
    };

    template<class T, class T_Step>
    constexpr bool is_types_combination_prohibited =
            (!std::is_same<T, float>::value             &&
             !std::is_same<T, double>::value            &&
             !std::is_same<T, ldouble>::value     )
                                                        &&
            ( std::is_same<T_Step, float>::value        ||
              std::is_same<T_Step, double>::value       ||
              std::is_same<T_Step, ldouble>::value);


    template<class __T, class __Step = __T>  //Проверить все функции на unsigned и на наличие проверок возвращаемых err кодов (IDM_ERR_IDS_RUN_OUT и т.д.).
    class IdManager
    {
        IdContainer<__T> freeIds_;
        IdContainer<__T> reservedIds_;  //Не учитывает maxId в idArea_.

        IdRange<__T> idArea_; //Rename.

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

        bool freeId(__T id);
        void freeAll();

        void setHardStep(bool value);
        bool isHardStep() const;

        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);  //Нормализовывать диапазон.
        inline IdIssuingMethod getIdIssuingMethod() const;

        bool findId(__T id) const;

        bool isStandardId(__T id) const;

//        __T getStartId() const;
        __Step getStep() const;
//        __T getMaxId() const;
//        __T getMinId() const;

        IdManager<__T, __Step>& operator=(const IdManager<__T, __Step>& other);

    private:
        bool interpolateIds(BorderRange border, __T id);
        bool reserveIds(BorderRange border, __T id);

        int expandRange(BorderRange border);
        int reduceRange(BorderRange border);
        int normalizeRange(BorderRange border);
        int getNextId(BorderRange border, __T& id);

        template<class __TF>
        inline __TF onf_abs(__TF value) const;
    };
}


#include "IdManager.inl"

#endif
