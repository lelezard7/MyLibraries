#ifndef ID_MANAGER_H_
#define ID_MANAGER_H_

#include <list>
#include <set>
#include <type_traits>
#include <optional>

#define IDAREA_ERRC_SUCCESSFULLY               0x00001
#define IDAREA_ERRC_IDS_RUN_OUT                0x00002
#define IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE    0x00004
#define IDAREA_ERRC_NO_SUCH_ID                 0x00008

#define IDM_POS_IN_RANGE                  0
#define IDM_POS_OUT_RANGE                 1
#define IDM_POS_ON_BORDER                 2


namespace ONF
{
    typedef unsigned long long ulonglong;
    typedef long long longlong;
    typedef long double ldouble;

    enum class IdIssuingMethod
    {
        Dynamic,
        Ascending,
        Descending
    };


    template<class T>
    class IdContainer //TODO: Заменить advance на next и prev.
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


    enum class ReservationMethod
    {
        Interpolate,
        NonInterpolate,
        AutoSelect,

        ReserveRange
    };

    enum class BorderRange
    {
        UpperBorder,
        LowerBorder
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


    template<class T>
    inline bool isStandardId(T target, T start, T step);

    template<class T>
    inline T makeStep(T start, T step, longlong n);


    template<class T>
    class IdArea //TODO: Увеличить макс. и мин. значение с long long на что-то побольше.
    {
    public:
        struct Result
        {
            unsigned    errCode;
            int         position;

            BorderRange border;  //TODO: GetIdInfo рандомно устанавливает это значение если нужно получить информацию о об id == start id.
            bool        state;
            T           value;

            longlong    stepCount;

            Result& operator=(const Result& other);
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

        const T start_;
        const T step_;

    public:
        IdArea(T start = 0, T step = 1);
        IdArea(const IdArea<T>& other);
        IdArea(const IdArea<T>&& other);
        virtual ~IdArea();

        Result moveBorder(BorderRange borderRange, longlong n);

        Result getIdInfo(BorderRange borderRange, longlong n) const;
        std::optional<Result> getIdInfo(BorderRange borderRange, T id, longlong n) const;
        std::optional<Result> getIdInfo(T id) const;

        void reset();

        bool setBorderValue(BorderRange borderRange, T value);
        inline T getBorderValue(BorderRange borderRange) const;

        void setBorderState(BorderRange borderRange, bool state);
        inline bool getBorderState(BorderRange borderRange) const;

        bool setBorderLimit(BorderRange borderRange, T limit);
        inline T getBorderLimit(BorderRange borderRange) const;

        inline T getStart() const;
        inline T getStep() const;

        IdArea<T>& operator=(const IdArea<T>& other);
        IdArea<T>& operator=(IdArea<T>&& other);

    private:
        std::optional<Result> moveToBottom(T border, T limit, ldouble n, Action actio, BorderRange borderRangen) const;
        std::optional<Result> moveToTop(T border, T limit, ldouble n, Action action, BorderRange borderRange) const;
        Result motionless(T border, BorderRange borderRange) const;
        Result findMotionless(T border, ldouble n, BorderRange borderRange) const;

        void fillBorderAndState(T border, Result& result, BorderRange borderRange) const;
        void fillPositionAndChangeBorder(Action action, Result& result, ldouble n) const;

        int isSucces(BorderRange borderRange, ldouble n, Result& result, Action action, T* alterBorder = nullptr) const;

    };


    template<class __T, class __Step = __T>  //Проверить все функции на unsigned и на наличие проверок возвращаемых err кодов (IDM_ERR_IDS_RUN_OUT и т.д.).
    class IdManager
    {
        IdContainer<__T> freeIds_;
        IdContainer<__T> reservedIds_;  //Не учитывает maxId в idArea_.

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
