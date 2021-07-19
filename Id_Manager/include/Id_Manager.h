#ifndef ID_MANAGER_H_
#define ID_MANAGER_H_

#include <list>
#include <set>
#include <type_traits>
#include <optional>

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


namespace IdM
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
            (!std::is_same<T, float>::value           &&
             !std::is_same<T, double>::value          &&
             !std::is_same<T, long double>::value)
                                                        &&
            ( std::is_same<T_Step, float>::value        ||
              std::is_same<T_Step, double>::value       ||
              std::is_same<T_Step, long double>::value);

    template<class T>
    inline T idm_abs(T value);

    template<class T>
    inline bool isStandardId(T id, T start, T step);


    template<class __T>
    class IdArea //TODO: Увеличить макс. и мин. значение с long long на что-то побольше.
    {
    public:
        struct Result
        {
            int errCode;
            int position;

            BorderRange border;
            bool state;
            __T value;

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
        virtual ~IdArea();

        Result moveBorder(BorderRange borderRange, long long n);

        Result getIdInfo(BorderRange borderRange, long long n) const;
        Result getIdInfo(__T id) const;

        void reset();

        bool setBorderValue(BorderRange borderRange, __T value);
        inline __T getBorderValue(BorderRange borderRange) const;

        void setBorderState(BorderRange borderRange, bool state);
        inline bool getBorderState(BorderRange borderRange) const;

        bool setBorderLimit(BorderRange borderRange, __T limit);
        inline __T getBorderLimit(BorderRange borderRange) const;

        inline __T getStart() const;
        inline __T getStep() const;

        IdArea<__T>& operator=(const IdArea<__T>& other);

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
        inline __TF idm_abs(__TF value) const;
    };
}


#include "../src/Id_Manager.inl"

#endif
