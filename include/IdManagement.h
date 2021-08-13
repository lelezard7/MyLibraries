#ifndef ID_MANAGEMENT_H_
#define ID_MANAGEMENT_H_

#include "ONF.h"

#include <optional>
#include <list>
#include <set>


namespace ONF
{
    /**
     * Это перечисление отвечает за задание метода выдачи ID в классе IdContainer и RangeIdManager. <br>
     * В RangeIdManager оно так же отвечает за поведение границ которые создаются в нем классом IdRange.
     *
     * @warning
     * IdIssuingMethod имеет пару НО. Подробнее о каждом перечислителе см. IdContainer и RangeIdManager.
     *
     * @see IdRange
     */
    enum class IdIssuingMethod
    {
        Dynamic,            ///<ID выдаются в порядке их добавления. <br>
                            ///<В классе RangeIdManager границы имеют плавающий характер.
        Static_Ascending,   ///<ID выдаются в порядке возрастания. <br>
                            ///<В классе RangeIdManager границы имеют фиксированный характер.
        Static_Descending   ///<ID выдаются в порядке убывания. <br>
                            ///<В классе RangeIdManager границы имеют фиксированный характер.
    };


    /**
     * @brief Контейнер с настраиваемым способом выдачи ID.
     *
     * По сути IdContainer это объединение [std::list](https://en.cppreference.com/w/cpp/container/list)
     * и [std::set](https://en.cppreference.com/w/cpp/container/set). <br>
     * IdContainer хранит все записанные в него уникальные ID и выдает их в порядке возрастания,
     * убывания или добавления. <br>
     * Если метод выдачи ID равен IdIssuingMethod::Static_Ascending то
     * ID выдаются в порядке возрастания. <br>
     * Если метод выдачи ID равен IdIssuingMethod::Static_Descending то
     * ID выдаются в порядке убывания. <br>
     * Если метод выдачи ID равен IdIssuingMethod::Dynamic то
     * ID выдаются в порядке их добавления в контейнер. <br>
     * По умолчанию метод выдачи ID равен IdIssuingMethod::Dynamic. <br>
     * Мы можем задать способ выдачи ID в конструкторе при создании и менять через метод
     * setIdIssuingMethod(IdIssuingMethod).
     *
     * Когда метод выдачи ID равен IdIssuingMethod::Dynamic, все ID хранятся в **unorderedIds_**,
     * а при IdIssuingMethod::Static_Ascending и IdIssuingMethod::Static_Descending в
     * **orderedIds_**:
     *
     * ``` Cxx
     * std::list<T> unorderedIds_;
     * std::set<T> orderedIds_;
     * ```
     *
     * @warning
     * IdContainer не хранит порядок добавления ID, он просто перекидывает все хранимые ID
     * в [std::list](https://en.cppreference.com/w/cpp/container/list)
     * в случае если способ выдачи ID равен IdIssuingMethod::Dynamic
     * и в [std::set](https://en.cppreference.com/w/cpp/container/set)
     * если способ выдачи ID равен IdIssuingMethod::Static_Ascending
     * или IdIssuingMethod::Static_Descending. <br>
     * Отсюда вытекает проблема при которой после смены режима выдачи с IdIssuingMethod::Dynamic
     * на IdIssuingMethod::Static_Ascending или IdIssuingMethod::Static_Descending,
     * а затем обратно на IdIssuingMethod::Dynamic,
     * IdContainer уже не будет выдавать ранее добавленные ID в том порядке
     * в котором мы их добавляли в него. Но вновь добавленные ID будут выдаваться в порядке добавления. <br>
     * Сейчас это скорее баг нежели фича. В будущих версиях этот момент будет доработан
     * (будет обратно совместим).
     *
     * @see
     * IdContainer(IdIssuingMethod idIssuingMethod) <br>
     * setIdIssuingMethod(IdIssuingMethod) <br>
     * IdIssuingMethod
     */
    template<class T>
    class IdContainer
    {
        std::list<T> unorderedIds_;
        std::set<T> orderedIds_;

        IdIssuingMethod idIssuingMethod_;

    public:
        /**
         * @param idIssuingMethod - метод выдачи ID.
         */
        IdContainer(IdIssuingMethod idIssuingMethod = IdIssuingMethod::Dynamic);

        /**
         * @param other - копируемый объект класса.
         */
        IdContainer(const IdContainer<T>& other);

        /**
         * После перемещения other остается пустым и
         * переводится в режим выдачи ID: IdIssuingMethod::Dynamic.
         *
         * @param other - перемещаемый объект класса.
         */
        IdContainer(IdContainer<T>&& other);
        virtual ~IdContainer();

        /**
         * @brief Добавляет уникальные ID в IdContainer.
         * @param id - ID для добавления.
         * @return В случае успеха возвращает true, иначе false.
         */
        bool add(T id);

        /**
         * @brief Возвращает ID в соответствии с методом выдачи ID.
         * @return
         * Если ID для возврата был найден, возвращает ID,
         * иначе [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt).
         */
        std::optional<T> getNextId();

        /**
         * @brief Удаляет ID из IdContainer.
         *
         * Если ID переданный для удаления найден, метод удалит его.
         * Если же ID не был найден, метод проигнорирует его.
         *
         * @param id - ID для удаления.
         */
        void erase(T id);

        /**
         * @brief Очищает IdContainer.
         *
         * Все ID при очистке будут удалены, но метод выдачи ID останется прежним
         * и не сбросится до значения по умолчанию.
         */
        void clear();

        /**
         * @brief Проверяет наличие ID в IdContainer.
         * @param id - Проверяемое ID.
         * @return Если ID найдено, возвращает true, иначе false.
         */
        bool find(T id) const;

        /**
         * @brief Возвращает ID по указанному индексу.
         * @param index - индекс по которому нужно найти ID.
         * @return
         * Если ID по указанному индексу найден, возвращает ID,
         * иначе [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt).
         */
        std::optional<T> findByIndex(size_t index) const;

        /**
         * @brief Задает метод выдачи ID для IdContainer.
         *
         * @bug
         * На момент версии 0.0.0 вызов этого метода может быть очень затратным по времени.<br>
         * Это связанно с тем что IdContainer переписывает все ID
         * из [std::list](https://en.cppreference.com/w/cpp/container/list)
         * в [std::set](https://en.cppreference.com/w/cpp/container/set)
         * или обратно.
         *
         * @param idIssuingMethod - метод выдачи ID который нужно установить.
         */
        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);

        /**
         * @brief Возвращает метод выдачи ID заданный для IdContainer.
         * @return Возвращает один из перечислителей @ref IdIssuingMethod.
         */
        IdIssuingMethod getIdIssuingMethod() const;

        /**
         * @return Возвращает количество хранимых ID.
         */
        size_t size() const;

        IdContainer<T>& operator=(const IdContainer<T>& other);
        IdContainer<T>& operator=(IdContainer<T>&& other);

    protected:
        /**
         * @return Возвращает количество ID хранимых в unorderedIds_.
         */
        size_t getUnorderedIdsSize() const;

        /**
         * @return Возвращает количество ID хранимых в orderedIds_.
         */
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
        return (n - static_cast<udlong>(n) == static_cast<ldouble>(0.0));
    }

    template<class T>
    T moveFromId(T start, T step, dlong n) {
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

            dlong    stepCount;
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

        IdInfo moveBorder(BorderRange borderRange, dlong n);

        IdInfo getIdInfo(BorderRange borderRange, dlong n) const;
        std::optional<IdInfo> getIdInfo(BorderRange borderRange, T id, dlong n) const;

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
