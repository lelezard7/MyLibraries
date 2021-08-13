#ifndef ID_MANAGEMENT_H_
#define ID_MANAGEMENT_H_

#include "ONF.h"

#include <optional>
#include <list>
#include <set>


namespace ONF
{
    enum class IdIssuingMethod
    {
        Dynamic,
        Static_Ascending,
        Static_Descending
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
        std::optional<T> getNextId();

        void erase(T id);
        void clear();

        bool find(T id) const;
        std::optional<T> findByIndex(size_t index) const;

        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);
        IdIssuingMethod getIdIssuingMethod() const;

        size_t size() const;

        IdContainer<T>& operator=(const IdContainer<T>& other);
        IdContainer<T>& operator=(IdContainer<T>&& other);

    protected:
        size_t getUnorderedIdsSize() const;
        size_t getOrderedIdsSize() const;

    };
}

#include "IdManagement/IdContainer.inl"


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
    enum class BorderRange
    {
        UpperBorder,
        LowerBorder
    };


    template<class T>
    bool isStandardId(T target, T start, T step) {
        ldouble An = static_cast<ldouble>(target);
        ldouble A1 = static_cast<ldouble>(start);
        ldouble d  = static_cast<ldouble>(step);

        ldouble n = std::abs((An - A1 + d) / d);
        return (n - static_cast<ulonglong>(n) == static_cast<ldouble>(0.0));
    }

    template<class T>
    T moveFromId(T start, T step, longlong n) {
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
}

#include "IdManagement/IdRange.inl"


namespace ONF
{
    enum class ReservationMethod
    {
        NotSet,
        Interpolate,
        ReserveRange
    };

    template<class T, class T_Step>
    constexpr bool is_forbidden_types_combination =
            !std::is_floating_point_v<T> && std::is_floating_point_v<T_Step>;


    template<class T, class T_Step = T, class T_Access = void>
    class RangeIdManager;

    template<class T, class T_Step>
    class RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>
    {
        IdContainer<T> reservedIds_;
        IdContainer<T> freeIds_;
        IdRange<T> idRange_;

        T_Step step_;
        size_t size_;
        bool isHardStep_;
        IdIssuingMethod idIssuingMethod_;

    public:
        RangeIdManager(T start = 0, T_Step step = 1);
        RangeIdManager(const RangeIdManager<T, T_Step>& other);
        RangeIdManager(RangeIdManager<T, T_Step>&& other);
        virtual ~RangeIdManager();

        std::optional<T> getFreeId();
        bool reserve(T id, ReservationMethod reservationMethod = ReservationMethod::NotSet);

        bool free(T id);
        inline void freeAll();

        bool find(T id) const; // TODO: Протестировать в разных ситуациях.

        bool setBorderLimit(BorderRange borderRange, T value);
        inline T getBorderLimit(BorderRange borderRange) const;

        void setHardStep(bool value);
        inline bool isHardStep() const;

        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);
        inline IdIssuingMethod getIdIssuingMethod() const;

        inline size_t size() const;
        inline bool isStandardId(T id) const;

        inline T getStart() const;
        inline T_Step getStep() const;
        inline T getBorderValue(BorderRange borderRange) const;
        inline bool getBorderState(BorderRange borderRange) const;

        // limit не распространяется на них.
        std::optional<T> findClosestStdId(T id) const;
        std::optional<T> findClosestStdId(T id, BorderRange borderRange) const;

        RangeIdManager& operator=(const RangeIdManager<T, T_Step>& other);
        RangeIdManager& operator=(RangeIdManager<T, T_Step>&& other);

    protected:
        inline size_t getFreeIdsSize() const;
        inline size_t getReservedIdsSize() const;

    private:
        std::optional<T> getNextId();

        typename IdRange<T>::IdInfo expandRangeIfPossible(BorderRange border); // TODO в .inl
        typename IdRange<T>::IdInfo reduceRangeIfPossible(BorderRange border);

        inline T activateBothBorders();
        inline T activateBothBordersWithExpending();

        bool jumpOver(T id, BorderRange borderRange);
        unsigned normalizeBorderRange(BorderRange borderRange);
        bool reserveIdInRange(T id);
        inline bool reserveBorderRange(BorderRange borderRange);

        // Написать о том что эта функция не отлавливает ошибки связзанные с нахождением id
        // в диапазоне или на границе.
        BorderRange getExpandableBorderRange(T id) const;

        bool interpolateIds(T id);
        bool reserveIds(T id);

    };
}

#include "IdManagement/RangeIdManager.inl"

#endif
