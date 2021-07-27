#ifndef ID_MANAGER_H_
#define ID_MANAGER_H_

#include <ONF.h>
#include <list>
#include <set>
#include <vector>
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
    class IdContainer  //TODO: Разобраться с перемещением и копированием.
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
        struct IdInfo
        {
            IdInfo();
            ~IdInfo();

            unsigned    flags;
            int         position;

            BorderRange border;
            bool        state;
            T           value;

            longlong    stepCount;
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
        IdRange(const IdRange& other) = default;
        IdRange(IdRange&& other) = default;
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

        IdRange& operator=(const IdRange& other) = default;
        IdRange& operator=(IdRange&& other) = default;

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
        NotSet,
        Interpolate,
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


    template<class T, class T_Step = T>  //Проверить все функции на unsigned и на наличие проверок возвращаемых err кодов (IDM_ERR_IDS_RUN_OUT и т.д.).
    class RangeIdManager // Проверять на limit. Везде проверять на ошибки (moveBorder, например).
    {
        IdContainer<T> freeIds_;
        IdContainer<T> reservedIds_;  //Не учитывает maxId в idArea_.

        IdRange<T> idRange_;
        T_Step step_;
        size_t size_;   //Не увеличивается.

        bool isHardStep_;
        IdIssuingMethod idIssuingMethod_;

    public:
        RangeIdManager(T start = 0, T_Step step = 1);
        RangeIdManager(const RangeIdManager<T, T_Step>& other);
        virtual ~RangeIdManager();

        std::optional<T> getFreeId();
        bool reserveId(T id, ReservationMethod reservationMethod = ReservationMethod::NotSet);

        bool setBorderLimit(BorderRange borderRange, T value);
        inline T getBorderLimit(BorderRange borderRange) const;

        bool freeId(T id);
        inline void freeAll();

        void setHardStep(bool value);
        inline bool isHardStep() const;

//        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);  //Нормализовывать диапазон.
        inline IdIssuingMethod getIdIssuingMethod() const;

        bool findId(T id) const;
        inline size_t size() const;
        inline bool isStandardId(T id) const;

        inline T getStart() const;
        inline T_Step getStep() const;
        inline T getBorderValue(BorderRange borderRange) const;
        inline bool getBorderState(BorderRange borderRange) const;

//        RangeIdManager<T, T_Step>& operator=(const RangeIdManager<T, T_Step>& other);

    private:
        int interpolateIds(T id);
        int reserveIds(T id);

        T findNearestStandardId(T id);

        unsigned expandRange(BorderRange border);
//        int reduceRange(BorderRange border);
//        int normalizeRange(BorderRange border);
        bool getNextId(BorderRange border, T& id);

//        template<class TF>
//        inline TF onf_abs(TF value) const;
    };
}


#include "IdManager.inl"

#endif
