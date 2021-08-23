#ifndef ID_MANAGEMENT_H_
#define ID_MANAGEMENT_H_

#include "ONF.h"

#include <optional>
#include <list>
#include <set>

//std::floor
#include <cmath>


namespace ONF
{
    /**
     * @brief Содержит методы выдачи ID для IdContainer и характер границ диапазона RangeIdManager.
     *
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
        Dynamic,            ///<@brief ID выдаются в порядке их добавления. <br>
                            /// В классе RangeIdManager границы имеют плавающий характер.

        Static_Ascending,   ///<@brief ID выдаются в порядке возрастания. <br>
                            /// В классе RangeIdManager границы имеют фиксированный характер.

        Static_Descending   ///<@brief ID выдаются в порядке убывания. <br>
                            /// В классе RangeIdManager границы имеют фиксированный характер.
    };


    /**
     * @brief Контейнер с настраиваемым способом выдачи ID.
     *
     * По сути IdContainer это объединение [std::list](https://en.cppreference.com/w/cpp/container/list)
     * и [std::set](https://en.cppreference.com/w/cpp/container/set). <br>
     * IdContainer хранит все записанные в него уникальные ID и выдает их в порядке возрастания,
     * убывания или добавления. <br>
     * Если метод выдачи ID равен IdIssuingMethod::Static_Ascending, то ID выдаются в порядке возрастания. <br>
     * Если метод выдачи ID равен IdIssuingMethod::Static_Descending, то ID выдаются в порядке убывания. <br>
     * Если метод выдачи ID равен IdIssuingMethod::Dynamic, то ID выдаются в порядке их добавления в
     * контейнер. <br>
     * По умолчанию метод выдачи ID равен IdIssuingMethod::Dynamic. <br>
     * Мы можем задать способ выдачи ID в конструкторе при создании и менять через метод
     * setIdIssuingMethod(IdIssuingMethod).
     *
     * Когда метод выдачи ID равен IdIssuingMethod::Dynamic, все ID хранятся в **unorderedIds_**,
     * а при IdIssuingMethod::Static_Ascending и IdIssuingMethod::Static_Descending в **orderedIds_**:
     * @code
     * std::list<T> unorderedIds_;
     * std::set<T> orderedIds_;
     * @endcode
     *
     * @warning
     * IdContainer не хранит порядок добавления ID, он просто перекидывает все хранимые ID в
     * [std::list](https://en.cppreference.com/w/cpp/container/list)
     * в случае если способ выдачи ID равен IdIssuingMethod::Dynamic и в
     * [std::set](https://en.cppreference.com/w/cpp/container/set)
     * если способ выдачи ID равен IdIssuingMethod::Static_Ascending или
     * IdIssuingMethod::Static_Descending. <br>
     * Отсюда вытекает проблема при которой после смены режима выдачи с IdIssuingMethod::Dynamic на
     * IdIssuingMethod::Static_Ascending или IdIssuingMethod::Static_Descending, а затем обратно на
     * IdIssuingMethod::Dynamic, IdContainer уже не будет выдавать ранее добавленные ID в том порядке в
     * котором мы их добавляли в него. Но вновь добавленные ID будут выдаваться в порядке добавления. <br>
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
         * По умолчанию метод выдачи ID равен IdIssuingMethod::Dynamic.
         *
         * @param idIssuingMethod - метод выдачи ID.
         */
        IdContainer(IdIssuingMethod idIssuingMethod = IdIssuingMethod::Dynamic);

        /**
         * @param other - копируемый объект класса.
         */
        IdContainer(const IdContainer<T>& other) = default;

        /**
         * После перемещения, **other** становится пустым, а режим выдачи ID остается прежним.
         *
         * @param other - перемещаемый объект класса.
         */
        IdContainer(IdContainer<T>&& other) = default;

        virtual ~IdContainer();

        /**
         * @brief Добавляет уникальные ID в IdContainer.
         * @param id - ID для добавления.
         * @return В случае успеха возвращает *true*, иначе *false*.
         */
        bool add(T id);

        /**
         * @brief Возвращает ID в соответствии с методом выдачи ID.
         *
         * @return
         * Если ID для возврата был найден, возвращает ID, иначе
         * [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt).
         */
        std::optional<T> getNextId();

        /**
         * @brief Удаляет ID из IdContainer.
         *
         * Если ID переданный для удаления найден, метод удалит его. Если же ID не был найден, метод
         * проигнорирует его.
         *
         * @param id - ID для удаления.
         * @see clear()
         */
        void erase(T id);

        /**
         * @brief Очищает IdContainer.
         *
         * Все ID при очистке будут удалены, но метод выдачи ID останется прежним и не сбросится до значения
         * по умолчанию.
         *
         * @see erase(T)
         */
        void clear();

        /**
         * @brief Проверяет наличие ID в IdContainer.
         * @param id - проверяемое ID.
         * @return Если ID найдено, возвращает *true*, иначе *false*.
         *
         * @see findByIndex(size_t) const
         */
        bool find(T id) const;

        /**
         * @brief Возвращает ID по указанному индексу.
         * @param index - индекс по которому нужно найти ID.
         *
         * @return
         * Если ID по указанному индексу найден, возвращает ID, иначе
         * [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt).
         *
         * @see find(T) const
         */
        std::optional<T> findByIndex(size_t index) const;

        /**
         * @brief Задает метод выдачи ID для IdContainer.
         *
         * @bug
         * На момент версии 0.0.0 вызов этого метода может быть очень затратным по времени. <br>
         * Это связанно с тем что IdContainer переписывает все ID из
         * [std::list](https://en.cppreference.com/w/cpp/container/list) в
         * [std::set](https://en.cppreference.com/w/cpp/container/set) или обратно.
         *
         * @param idIssuingMethod - метод выдачи ID который нужно установить.
         * @see getIdIssuingMethod() const
         */
        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);

        /**
         * @brief Возвращает метод выдачи ID заданный для IdContainer.
         * @return Возвращает один из перечислителей @ref IdIssuingMethod.
         * @see setIdIssuingMethod(IdIssuingMethod)
         */
        IdIssuingMethod getIdIssuingMethod() const;

        /**
         * @brief Возвращает количество выданных ID.
         * @return Возвращает количество выданных ID.
         */
        size_t size() const;

        /**
         * @param other - копируемый объект класса.
         */
        IdContainer<T>& operator=(const IdContainer<T>& other) = default;

        /**
         * После перемещения, **other** становится пустым, а режим выдачи ID остается прежним.
         *
         * @param other - перемещаемый объект класса.
         */
        IdContainer<T>& operator=(IdContainer<T>&& other) = default;

    protected:
        /**
         * @brief Возвращает количество ID хранимых в **unorderedIds_**.
         * @return Возвращает количество ID хранимых в **unorderedIds_**.
         */
        size_t getUnorderedIdsSize() const;

        /**
         * @brief Возвращает количество ID хранимых в **orderedIds_**.
         * @return Возвращает количество ID хранимых в **orderedIds_**.
         */
        size_t getOrderedIdsSize() const;

    };
}

#include "IdManagement/IdContainer.inl"


/// @defgroup IdRange_Flag IdRange_Flag
/// @brief Флаги структуры @ref ONF::IdRange::IdInfo.
///@{
#define IDRF_NOT_SET            0x0000   ///<Флаг не задан.
#define IDRF_SUCCESSFULLY       0x0001   ///<Задача успешно выполнена.
#define IDRF_ID_OUT_OF_LIMIT    0x0002   ///<Граница попыталась выйты за пределы своего Лимита.
#define IDRF_RANGE_ARE_BENT     0x0004   ///<Одна граница попыталась пересечь другую границу.
///@}

/// @defgroup IdRange_Position IdRange_Position
/// @brief Флаги позиции ID структуры @ref ONF::IdRange::IdInfo.
///@{
#define IDRP_NOT_SET            0x0000   ///<Позиция не задана.
#define IDRP_WITHIN_RANGE       0x0001   ///<ID находится в пределах диапазона.
#define IDRP_AT_BORDER          0x0002   ///<ID находится на границе диапазона.
#define IDRP_OUT_OF_RANGE       0x0004   ///<ID находится вне диапазона.
#define IDRP_AT_START           0x0008   ///<ID находится на Стартовой позиции.
///@}

namespace ONF
{
    /**
     * @brief Содержит название границ диапазона создаваемых IdRange.
     */
    enum class BorderRange
    {
        UpperBorder,   ///<@brief Верхняя граница диапазона.
        LowerBorder    ///<@brief Нижняя граница диапазона.
    };


    /**
     * @brief Проверяет, является ID стандартным или же нет.
     *
     * Стандартный ID это число, которое является \f$ n \f$-м членом арифметической прогрессии. <br>
     * \f$ n \f$-й член арифметической прогрессии вычисляется по формуле:
     *
     * \f$ a_n = a_1 + (n - 1)d \f$
     *
     * Отсюда можно вывести формулу:
     *
     * \f$ n = \frac{a_n - a_1}{d} + 1 \f$
     *
     * Где \f$ d \neq 0 \f$
     *
     * Обозначение: <br>
     * \f$ a_n \f$ - ID которое мы должны проверить на то, стандартное ли оно или нет. <br>
     * \f$ a_1 \f$ - начальный ID. <br>
     * \f$ d \f$ - размер шага. <br>
     * \f$ n \f$ - позиция ID в арифметической прогрессии.
     *
     * Если в результате вычислений, \f$ n \f$ окажется целым числом, то проверяемый ID (\f$ a_n \f$)
     * можно считать стандартным. Если \f$ n \f$ окажется дробным, то проверяемый ID будет нестандартным.
     *
     * @param target - ID которое нужно проверить.
     * @param start - начальный ID.
     * @param step - размер шага.
     * @return Если **target** окажется стандартным ID, вернет *ture*, иначе *false*.
     */
    template<class T>
    bool isStandardId(T target, T start, T step) {
        ldouble n = static_cast<ldouble>(target) - static_cast<ldouble>(start);
        n = std::abs((n / static_cast<ldouble>(step)) + 1.0);

        return (n - static_cast<udlong>(n) == 0.0);
    }

    /**
     * @brief Возвращает ближайший к переданному ID, стандартный ID.
     *
     * Под ближайшим стандартным ID подразумевается тот, который находится ближе всего к переданному ID
     * и при этом находится между **target** и **start**. <br>
     * Знак числа шага переданного в **step** не имеет значения.
     *
     * В следующем примере для ID равного -4,3, ближайшим стандартным является -4, но не -5. <br>
     * Для ID равного 5,5, ближайшим стандартным является 5, но не 6.
     * @code
     * findNearestStdId(5.5, 0, 1);   //result: 5
     * findNearestStdId(-4.3, 0, 1);  //result: -4
     *
     *                               ub
     *                lb
     * -6 -5 -4,3 -4 -3 -2 -1  0  1  2  3  4  5  5,5  6
     *  .  .   .   .  .  .  .  @  .  .  .  .  .   .   .
     * @endcode
     *
     * @param target - ID, ближайший стандартный ID к которому нужно найти.
     * @param start - известный стандартный ID.
     * @param step - размер шага.
     *
     * @return
     * Если в **target** передан стандартный ID, возвращает его же. <br>
     * Если в **target** передан нестандартный ID, возвращает ближайший к нему стандартный ID.
     *
     * @see isStandardId(T, T, T)
     */
    template<class T>
    T findNearestStdId(T target, T start, T step) {
        ldouble An = static_cast<ldouble>(target);
        ldouble A1 = static_cast<ldouble>(start);
        ldouble d = static_cast<ldouble>(target > start ? ONF::abs(step) : -ONF::abs(step));

        ldouble n = ((An - A1) / d) + 1.0;

        if (n - static_cast<udlong>(n) == 0.0)
            return target;

        return A1 + (std::floor(n) - 1.0) * d;
    }

    /**
     * @brief Вычисляет ID находящееся на определенном расстоянии от известного ID.
     *
     * Искомый ID вычисляется по простой формуле: <br>
     * \f$ ID = start + (n * step) \f$
     *
     * @param start - начальный ID.
     * @param step - размер шага.
     * @param n - количество шагов.
     * @return Возвращает найденный ID.
     */
    template<class T>
    T moveFromId(T start, T step, udlong n) {
        return start + (n * step);
    }


    /**
     * @brief Динамический диапазон стандартных ID.
     *
     * IdRange это два числа, которые образуют между собой диапазон. <br>
     * Границы диапазона обозначаются:
     * - BorderRange::UpperBorder - верхняя граница диапазона ( *ub* ).
     * - BorderRange::LowerBorder - нижняя граница диапазона ( *lb* ).
     *
     * Так же, каждую границу диапазона можно как включить ( *1* ), так и выключить ( *0* ).
     * При создании IdRange обе границы находятся в одной точке, она задается при создании и
     * называется "Стартовая ID" или просто "Старт" ( @ ). <br>
     * Помимо Старта при создании IdRange мы так же задаем и "Шаг" ( *->* ). <br>
     * Старт и Шаг задаются при создании IdRange и потом не подлежат изменению.
     *
     * После того как мы создали IdRange, мы можем двигать границы как друг от друга:
     * @code
     *                    ub>.->.->.->|                                             ub
     *  |<-.<-.<-.<-.<-.<-lb                          lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6   =>   -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .         .  .  .  .  .  .  @  .  .  .  .  .  .
     * @endcode
     *
     * Так и друг к другу:
     * @code
     *                          |<-.<-.<-ub                                   ub
     *           lb>.->.->.->|                                             lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6   =>   -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .         .  .  .  .  .  .  @  .  .  .  .  .  .
     * @endcode
     *
     * Несмотря на то что границы могут идти навстречу друг другу и могут даже встретиться в одной
     * точке, они никогда не могут пересечь друг друга. <br>
     * Граница, которая попытается пересечь другую границу, остановится там где, находится другая
     * граница:
     * @code
     *              |<x.<x.<-.<-.<-.<-ub                                ub
     *                    lb                                            lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6   =>   -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .         .  .  .  .  .  .  @  .  .  .  .  .  .
     * @endcode
     *
     * Так же для каждой границы можно установить Лимит ( :: ). <br>
     * Лимит можно установить как вне диапазона, так и на границе диапазона, но не внутри диапазона. <br>
     * Граница диапазона не может пересечь установленный для нее Лимит. <br>
     * В случае если граница диапазона попробует это сделать и Лимит установлен на стандартном ID,
     * граница диапазона остановится там где установлен Лимит. <br>
     * Если граница диапазона попробует пересечь Лимит который установлен на нестандартном ID, она
     * остановится на ближайшем к Лимиту стандартном ID. <br>
     * @code
     *                    ub>.->.->.->.xxxxxx>.x>|                                       ub
     *  |<x.<x.<-.<-.<-.<-lb                                     lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  4,3  5  6   =>   -6 -5 -4 -3 -2 -1  0  1  2  3  4  4,3  5  6
     *  .  . ::  .  .  .  @  .  .  .  .  ::   .  .         .  . ::  .  .  .  @  .  .  .  .  ::   .  .
     * @endcode

     * Иными словами границы диапазона могут перемещаться только по стандартным для них ID.
     *
     * ----------
     * ### Получение информации об ID.
     *
     * moveBorder(BorderRange, dlong) после перемещения границы возвращает структуру IdRange::IdInfo,
     * которая содержит информацию об ID на который была перемещена граница. <br>
     * Если нужно получить информацию об ID, но не двигать границу, можно использовать
     * getIdInfo(BorderRange, dlong) const. <br>
     * По сути moveBorder(BorderRange, dlong) и getIdInfo(BorderRange, dlong) const это почти одна и
     * та же функция. <br>
     * Разница в том что в самом конце moveBorder(BorderRange, dlong) все же передвигает границу, тогда как
     * getIdInfo(BorderRange, dlong) const этого не делает. <br>
     * Отсюда вытекает особенность получения информации об ID, а именно то, что
     * getIdInfo(BorderRange, dlong) const подчиняется тем же правилам что и
     * moveBorder(BorderRange, dlong). <br>
     * Если мы не можем передвинуть границу на какой-то ID с помощью moveBorder(BorderRange, dlong),
     * значит мы не можем и получить информацию об этом ID с помощью getIdInfo(BorderRange, dlong) const. <br>
     *
     * moveBorder(BorderRange, dlong) перемещает границу указанную в первом параметре на количество шагов
     * указанных во втором параметре. <br>
     * Если число во втором параметре положительное, диапазон расширяется, если отрицательное, сужается. <br>
     * Рассмотрим первый случай. <br>
     *
     * Пример: <br>
     * Мы хотим расширить диапазон и передвинуть BorderRange::UpperBorder на +3 шага. <br>
     * Сейчас BorderRange::UpperBorder находится на ID равном 10. Шаг равен 2. <br>
     * В итоге BorderRange::UpperBorder передвинется на ID равное 16. <br>
     * Если мы попросим передвинуться ее еще на +3 шага, то BorderRange::UpperBorder будет уже равна 22.
     * Таким образом, не меняя параметров мы можем двигать границу. <br>
     *
     * Теперь рассмотрим такую же ситуацию с getIdInfo(BorderRange, dlong) const: <br>
     * При тех же условиях, в первом случае мы получим информацию об ID равном 16, во втором случае так же
     * о 16, в третьем, четвертом и т.д. тоже о 16. <br>
     * Это из-за того что граница не передвигается и нам придется увеличивать второй параметр
     * getIdInfo(BorderRange, dlong) const что бы получить информацию о более больших ID или все же двигать
     * границу. <br>
     *
     * Если продолжить эту логическую цепочку, можно прийти к выводу о том что если мы не хотим двигать
     * границу, а хотим только получать информацию об ID, то максимальное ID, информацию о котором мы можем
     * получить, ограниченно типом данных второго параметра, если опустить все прочее. <br>
     * Для решения этой проблемы была добавлена перегрузка для
     * @ref getIdInfo - getIdInfo(BorderRange, T, dlong) const. <br>
     * Она работает так же как и обычная getIdInfo(BorderRange, dlong) const, но здесь во втором параметре
     * мы указываем временное значение границы указанной в первом параметре. <br>
     * Это поможет нам почти беспрепятственно перемещаться по числовой оси.
     *
     * Подробнее об этих функциях: <br>
     * moveBorder(BorderRange, dlong) <br>
     * getIdInfo(BorderRange, dlong) const <br>
     * getIdInfo(BorderRange, T, dlong) const
     *
     * @see
     * IdRange::IdInfo <br>
     * BorderRange
     */
    template<class T>
    class IdRange
    {
    public:
        struct IdInfo;

    private:
        /**
         * @see
         * fillInfoAboutMoveUp <br>
         * fillInfoAboutMoveDown <br>
         * getFilledIdInfo
         */
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
        /**
         * По умолчанию обе границы выключены, находятся на ID равном 0 и с размером шага 1. <br>
         * Лимит BorderRange::UpperBorder по умолчанию равен
         * [std::numeric_limits::max()](https://en.cppreference.com/w/cpp/types/numeric_limits/max). <br>
         * Лимит BorderRange::LowerBorder по умолчанию равен
         * [std::numeric_limits::lowest()](https://en.cppreference.com/w/cpp/types/numeric_limits/lowest). <br>
         *
         * Шаг не может быть равен 0. Если вы передадите в **step** 0, он автоматически станет равен 1. <br>
         * Знак числа шага, передаваемого в **step**, не имеет значения, минус автоматически отбрасывается.
         *
         * @param start - стартовый ID.
         * @param step - размер шага.
         */
        IdRange(T start = 0, T step = 1);

        /**
         * @param other - копируемый объект класса.
         */
        IdRange(const IdRange& other) = default;

        /**
         * После перемещения **other** сохраняет установленные Лимиты, а вот границы сбрасываются до
         * начального состояния. <br>
         * Т.е. BorderRange::UpperBorder и BorderRange::LowerBorder будут равны стартовому ID, а состояние
         * границ будет сброшено до *false*.
         *
         * @param other - перемещаемый объект класса.
         */
        IdRange(IdRange&& other);

        virtual ~IdRange();

        /**
         * @brief Передвигает указанную границу диапазона.
         *
         * **n** показывает на какое количество шагов нужно переместить границу диапазона указанную
         * в **borderRange**, а знак числа указывает направление движения. <br>
         * Если **n** имеет знак "+", граница будет идти в сторону расширения диапазона. <br>
         * Если **n** имеет знак "-", граница будет идти в сторону уменьшения диапазона.
         *
         * Более подробно о работе этого метода: <br>
         * - Описание IdRange <br>
         * - IdInfo
         *
         * @param borderRange - граница диапазона, которую нужно передвинуть.
         *
         * @param
         * n - количество шагов, на которое нужно передвинуть указанную границу диапазона, и
         * направление движения.
         *
         * @return
         * Возвращает структуру IdInfo с информацией о последнем ID на который смогла успешно
         * переместиться граница диапазона.
         */
        IdInfo moveBorder(BorderRange borderRange, dlong n);

        /**
         * @brief Возвращает информацию об ID.
         *
         * Данный метод работает так же как и moveBorder(BorderRange, dlong), но в конце своей работы
         * не передвигает границу.
         *
         * @param borderRange - граница диапазона, от которой будет вестись отсчет шагов.
         *
         * @param
         * n - количество шагов, которое нужно сделать от границы диапазона указанной в **borderRange**
         * что бы найти ID, информацию о котором нужно получить.
         *
         * @return
         * Возвращает структуру IdInfo с информацией о последнем ID на который ***может*** переместиться
         * граница диапазона.
         *
         * @see Описание IdRange
         */
        IdInfo getIdInfo(BorderRange borderRange, dlong n) const;

        /**
         * @brief Возвращает информацию об ID.
         *
         * Данный метод работает так же как getIdInfo(BorderRange, dlong) const, но здесь добавляется
         * параметр **id**. <br>
         * В getIdInfo(BorderRange, dlong) const параметр **id** скрыт от взгляда. Он равен текущему
         * значению границы диапазона преданному в первый аргумент. <br>
         * Т.е. данная запись:
         * @code
         * IdRange<int> idRange;
         * idRange.getIdInfo(BorderRange::UpperBorder, 3);
         * @endcode
         *
         * Равна:
         * @code
         * IdRange<int> idRange;
         * idRange.getIdInfo(BorderRange::UpperBorder, idRange.getBorderValue(BorderRange::UpperBorder), 3);
         * @endcode
         *
         * В **id** может быть передан только стандартный ID. <br>
         * ID переданный в **id** не должен вызывать пересечение границ диапазона. <br>
         * ID переданный в **id** не должен находиться за пределами Лимита. <br>
         * Если хотя бы одно из этих требований не выполняется, метод вернет
         * [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt). <br>
         * Если данные требования выполняются, метод вернет структуру IdInfo.
         *
         * @param borderRange - граница диапазона, от которой будет вестись отсчет шагов.
         * @param id - временное значение для границы диапазона указанной в **borderRange**.
         *
         * @param
         * n - количество шагов, которое нужно сделать от границы диапазона указанной в **borderRange**
         * что бы найти ID, информацию о котором нужно получить.
         *
         * @return
         * Если в **id** было передано некорректное значение, вернет
         * [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt), иначе структуру IdInfo.
         */
        std::optional<IdInfo> getIdInfo(BorderRange borderRange, T id, dlong n) const;

        /**
         * @brief Сбрасывает значение и состояние границ диапазона.
         *
         * **reset** сбрасывает только значение и состояние границ диапазона, но лимит установленный для
         * границ диапазона не сбрасывается.
         *
         * @see setBorderLimit(BorderRange, T)
         */
        void reset();

        /**
         * @brief Задает значение для указанной границы диапазона.
         *
         * Невозможно задать значение границы которое будет за пределами Лимита границы. <br>
         * Невозможно задать значение границы которое создаст пересечение границ. <br>
         * В качестве значения границы может быть указан только стандартный ID.
         *
         * @param borderRange - граница диапазона, значение для которой нужно задать.
         * @param value - значение, которое нужно задать указанной границе диапазона.
         * @return Если значение границы было задано успешно возвращает *true*, иначе *false*.
         */
        bool setBorderValue(BorderRange borderRange, T value);

        /**
         * @brief Возвращает текущее значение указанной границы диапазона.
         * @param borderRange - граница диапазона, текущее значение которой нужно получить.
         * @return Возвращает текущее значение указанной границы диапазона.
         */
        T getBorderValue(BorderRange borderRange) const;

        /**
         * @brief Включает или отключает указанную границу диапазона.
         *
         * Если **state** равен *true*, граница диапазона указанная в **borderRange** включается. <br>
         * Если **state** равен *false*, граница диапазона указанная в **borderRange** выключается.
         *
         * @param borderRange - граница диапазона, которую нужно включить или отключить.
         * @param state - состояние, которое нужно задать указанной границе диапазона.
         */
        void setBorderState(BorderRange borderRange, bool state);

        /**
         * @brief Возвращает состояние указанной границы диапазона.
         * @param borderRange - граница диапазона, состояние которой нужно получить.
         * @return Если граница диапазона включена, возвращает *true*, иначе *false*.
         */
        bool getBorderState(BorderRange borderRange) const;

        /**
         * @brief Задает Лимит для указанной границы диапазона.
         *
         * Лимит можно установить только вне диапазона или на границах диапазона. <br>
         * Если Лимит необходимо установить где-то в пределах диапазона, сперва надо передвинуть границу
         * диапазона так, что бы нужное нам значение Лимита в итоге оказалось вне диапазона.
         *
         * @param borderRange - граница диапазона, Лимит для которой нужно установить.
         * @param value - Лимит который нужно установить для границы диапазона.
         * @return В случае успеха возвращает *true*, иначе *false*.
         */
        bool setBorderLimit(BorderRange borderRange, T value);

        /**
         * @brief Возвращает Лимит указанной границы диапазона.
         * @param borderRange - граница диапазона, Лимит которой нужно получить.
         * @return Возвращает Лимит указанной границы диапазона.
         */
        T getBorderLimit(BorderRange borderRange) const;

        /**
         * @brief Возвращает стартовый ID.
         * @return Возвращает стартовый ID.
         */
        T getStart() const;

        /**
         * @brief Возвращает размер шага.
         * @return Возвращает размер шага.
         */
        T getStep() const;

        /**
         * @param other - копируемый объект класса.
         */
        IdRange& operator=(const IdRange& other) = default;

        /**
         * После перемещения **other** сохраняет установленные Лимиты, а вот границы сбрасываются до
         * начального состояния. <br>
         * Т.е. BorderRange::UpperBorder и BorderRange::LowerBorder будут равны стартовому ID, а состояние
         * границ будет сброшено до *false*.
         *
         * @param other - перемещаемый объект класса.
         */
        IdRange& operator=(IdRange&& other);

    private:
        /**
         * @brief Создает структуру IdInfo и заполняет ее в соответствии с данными которые мы в нее передали.
         *
         * Данный метод не проверяет корректность переданных в него данных. В будущих версиях это будет
         * исправлено, а сам метод будет вынесен в protected.
         *
         * В методах getIdInfo(BorderRange, dlong) const и moveBorder(BorderRange, dlong) в аргумент
         * **borderRange** метода getFilledIdInfo идет их первый аргумент, а в аргумент **borderValue**
         * идет текущее значение границы диапазона переданной в первый аргумент. <br>
         * Но вот в методе getIdInfo(BorderRange, T, dlong) const в аргумент **borderValue** метода
         * getFilledIdInfo идет "фальшивое текущее значение", что позволяет нам достать до ID
         * которую не может достать getIdInfo(BorderRange, dlong) const. <br>
         * О различии перегрузок getIdInfo подробнее в описании IdRange. <br>
         * В **n** мы передаем количество шагов которое нужно сделать от границы диапазона
         * и направление движения. <br>
         * В **action** мы передаем одно из 2-х значений: Action::Move или Action::GetInfo. <br>
         * Action::Move несмотря на название не двигает границу. Action::Move и Action::GetInfo
         * нужены лишь для того что бы правильно заполнить структуру IdInfo.
         *
         * @param borderRange - граница диапазона от которой производятся вычисления.
         * @param borderValue - значение указанной в **borderRange** границы диапазона.
         * @param n - количество шагов.
         * @param action - действие выполняемое над границей диапазона.
         * @return Возвращает заполненную IdInfo, содержащую данные об ID
         * которые были вычислены исходя из данных что мы передали.
         */
        IdInfo getFilledIdInfo(BorderRange borderRange, T borderValue, ldouble n, Action action) const;

        /**
         * Проверяет, возможно ли передвиниуть границу на то количество шагов что мы указали в **n**. <br>
         * Если это невозможно, проверяет, возможно ли передвиниуть границу хоть на какое то количество
         * шагов. <br>
         * Если передвинуть границу вообще невозможно, возвращает *false*, иначе заполняет
         * структуру IdInfo и возвращает *true*. <br>
         *
         * В **action** мы уточняем, что мы собираемся делать со структурой IdInfo после ее получения
         * из @ref getFilledIdInfo. <br>
         * Если мы собираемся передвинуть границу, то в **action** стоит передать
         * Action::Move. Если нам нужно просто получить информацию об ID,
         * надо передавать Action::GetInfo. <br>
         * Если мы собираемся передвинуть границу, но в **action**
         * передадим Action::GetInfo, данные записанные в IdInfo будут не совпадать
         * с действительностью. <br>
         * Как минимум IdInfo::position будет иметь занчения IDRP_OUT_OF_RANGE или IDRP_WITHIN_RANGE,
         * тогда как надо что бы было IDRP_AT_BORDER (так как граница диапазона переместиться на этот ID).
         *
         * fillInfoAboutMoveUp передвигает любую из границ вверх. <br>
         * Это значит что если мы передадим в данный метод BorderRange::UpperBorder он будет передвигаться
         * в сторону расширения диапазона. <br>
         * Если же мы передадим в данный метод BorderRange::LowerBorder он будет передвигаться в сторону
         * уменьшения диапазона.
         * @code
         *                          ub>.->.->.->.->...
         *           lb>.->.->.->.->.->.->.->.->.->...
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         * @endcode
         *
         * @param idInfo - структура для заполнения в случае если передвинуть границу диапазона возможно.
         * @param borderRange - граница диапазона от которой ведется отсчет.
         * @param borderValue - временное значение для границы диапазона указанной в **borderRange**.
         *
         * @param
         * borderLimit - ограничение для проверки. Это может быть как Лимит, так и другая граница диапазона.
         *
         * @param n - количество шагов которое нужно сделать.
         * @param action - уточнение о том что будет сделано с полученной информацией.
         */
        bool fillInfoAboutMoveUp(IdInfo& idInfo, BorderRange borderRange, T borderValue, T borderLimit, ldouble n, Action action) const;

        /**
         * fillInfoAboutMoveDown тоже самое что и fillInfoAboutMoveUp, но данный метод передвигает
         * границы диапазона вниз.
         * Это значит что если мы передадим в данный метод BorderRange::UpperBorder он будет передвигаться
         * в сторону уменьшения диапазона. <br>
         * Если же мы передадим в данный метод BorderRange::LowerBorder он будет передвигаться в сторону
         * расширения диапазона.
         * @code
         * ...<-.<-.<-.<-.<-.<-.<-.<-.<-ub
         * ...<-.<-.<-.<-lb
         *     -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *      .  .  .  .  .  .  @  .  .  .  .  .  .
         * @endcode
         */
        bool fillInfoAboutMoveDown(IdInfo& idInfo, BorderRange borderRange, T borderValue, T borderLimit, ldouble n, Action action) const;

        /**
         * @brief Заполняет информацию о том на чьей территории находитcя найденный ID.
         *
         * fillInfoAboutTerritory заполняет поля **border** и **state** структуры IdInfo. <br>
         * Подробнее о территориях: IdRange.
         *
         * @param idInfo - структура для заполнения.
         * @param borderRange - граница от которой ведется отсчет.
         * @param borderValue - полученный ID.
         */
        void fillInfoAboutTerritory(IdInfo& idInfo, BorderRange borderRange, T borderValue) const;

        /**
         * @brief Заполняет информацию о позиции найденного ID.
         *
         * fillInfoAboutPos заполняет поля **position** структуры IdInfo. <br>
         * Подробнее о позициях найденного ID: IdRange.
         *
         * @param idInfo - структура для заполнения.
         * @param borderValue - полученный ID.
         * @param n - количество шагов которое нужно сделать.
         * @param action - уточнение о том что будет сделано с полученной информацией.
         */
        void fillInfoAboutPos(IdInfo& idInfo, T borderValue, ldouble n, Action action) const;

    };


    /**
     * @class ONF::IdRange::IdInfo
     *
     * @brief Структура для предоставления информации об ID, возвращаемая IdRange.
     * @pre Прежде стоит ознакомиться с IdRange.
     */
        /**
         * @var ONF::IdRange::IdInfo::flags
         *
         * @brief
         * Флаги. <br>
         * Значение по умолчанию @ref IDRF_NOT_SET.
         *
         * **flags** может хранить достаточно разные флаги. <br>
         * На данный момент доступны следующие флаги: @ref IdRange_Flag.
         *
         * По умолчанию **flags** имеет значение @ref IDRF_NOT_SET (не путать с @ref IDRP_NOT_SET). <br>
         * Флаги @ref IDRF_SUCCESSFULLY, @ref IDRF_ID_OUT_OF_LIMIT, @ref IDRF_RANGE_ARE_BENT
         * показывают, успешно ли выполнена задача перемещения или получения информации об ID
         * классом IdRange. <br>
         * Если в процессе выполнения одна из границ диапазона попытается выйти за пределы своего
         * Лимита, в **flags** будет записан @ref IDRF_ID_OUT_OF_LIMIT. <br>
         * Если в процессе выполнения одна из границ диапазона попытается пересечь другую границу
         * диапазона, в **flags** будет записан @ref IDRF_RANGE_ARE_BENT. <br>
         * Если задача была выполнена успешно и граница не пытались пересечь ни Лимит ни другую
         * границу в **flags** будет записан @ref IDRF_SUCCESSFULLY. <br>
         * Подробнее о пересечении Лимита или противоположной границы: IdRange.
         *
         * @see
         * IdRange::moveBorder <br>
         * IdRange::getIdInfo <br>
         * value
         */

        /**
         * @var ONF::IdRange::IdInfo::position
         *
         * @brief
         * Позиция ID относительно границ диапазона. <br>
         * Значение по умолчанию @ref IDRP_NOT_SET.
         *
         * **position** хранит информацию о том где располагается полученный ID относительно
         * указанной границы диапазона. Полученный ID хранится в **value**. <br>
         * На данный момент доступны следующие флаги: @ref IdRange_Position.
         *
         * По умолчанию **position** имеет значение @ref IDRP_NOT_SET (не путать с @ref IDRF_NOT_SET). <br>
         * Если полученный ID находится на границе диапазона, в **position** будет записан
         * @ref IDRP_AT_BORDER. <br>
         * Если полученный ID находится вне границ диапазона, в **position** будет записан
         * @ref IDRP_OUT_OF_RANGE. <br>
         * Если полученный ID находится в границах диапазона, в **position** будет записан
         * @ref IDRP_WITHIN_RANGE. <br>
         * Если полученный ID совпадает со Стартовым ID, в **position** будет записан
         * @ref IDRP_AT_START. <br>
         * @ref IDRP_AT_START может быть записан вместе с @ref IDRP_AT_BORDER и @ref IDRP_WITHIN_RANGE. <br>
         * Подробнее о Стартовом ID: IdRange.
         *
         * @see
         * IdRange::moveBorder <br>
         * IdRange::getIdInfo <br>
         * value
         */

        /**
         * @var ONF::IdRange::IdInfo::border
         *
         * @brief
         * Граница диапазона, на территории которой находится полученный ID. <br>
         * Значение по умолчанию BorderRange::UpperBorder.
         *
         * Полученный ID хранится в **value**.
         *
         * **border** хранит информацию о том на чьей территории располагается полученный ID.
         * Полученный ID хранится в **value**. <br>
         * Все ID больше Стартового ID находятся на территории BorderRange::UpperBorder, он и будет
         * записан в **border**. <br>
         * Все ID меньше Стартового ID находятся на территории BorderRange::LowerBorder, он и будет
         * записан в **border**. <br>
         * Стартовый ID является нейтральным. Если полученный ID совпадает со Стартовым ID,
         * в **border** записывается то значение @ref BorderRange которое мы указали в
         * IdRange::moveBorder(BorderRange, dlong) или IdRange::getIdInfo(BorderRange, dlong) const
         * в первом параметре.
         *
         * Например:
         * @code
         * IdRange<int> idRange;
         * ...
         * auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, -4); //idInfo.border == BorderRange::UpperBorder
         *
         *                    |<-.<-.<-.<-ub
         *        lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         *
         *
         * auto idInfo = idRange.getIdInfo(BorderRange::LowerBorder, -4); //idInfo.border == BorderRange::LowerBorder
         *
         *                                ub
         *        lb>.->.->.->|
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         * @endcode
         *
         * @ref getIdInfo вернет @ref IdInfo где в первом варианте **border** равен
         * BorderRange::UpperBorder, а во втором BorderRange::LowerBorder и это несмотря на то что
         * мы запросили один и тот же ID. <br>
         *
         * А вот в остальных случаях **border** будет корректно указывать на то к какой территории
         * принадлежит ID:
         * @code
         * IdRange<int> idRange;
         * ...
         * auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, -3); //idInfo.border == BorderRange::UpperBorder
         *
         *                       |<-.<-.<-ub
         *        lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         *
         *
         * auto idInfo = idRange.getIdInfo(BorderRange::LowerBorder, -5); //idInfo.border == BorderRange::UpperBorder
         *
         *                                ub
         *        lb>.->.->.->.->|
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         * @endcode
         *
         * @see
         * state <br>
         * IdRange::moveBorder <br>
         * IdRange::getIdInfo <br>
         * IdRange <br>
         * value
         */

        /**
         * @var ONF::IdRange::IdInfo::state
         *
         * @brief
         * Состояние границы, на территории которой находится полученный ID. <br>
         * Значение по умолчанию *false*.
         *
         * Полученный ID хранится в **value**.
         *
         * **state** хранит состояние границы диапазона указанной в **border**. <br>
         * Если граница выключена, в **state** записывается *false*. <br>
         * Если граница включена, в **state** записывается *true*.
         *
         * @see
         * border <br>
         * value
         */

        /**
         * @var ONF::IdRange::IdInfo::value
         *
         * @brief
         * Последняя ID на которую успешно смогла переместиться граница. <br>
         * Значение по умолчанию 0.
         *
         * Если граница диапазона ***может*** успешно переместиться и ей ничего не помешает,
         * то **value** примет ожидаемое значение. <br>
         * Если граница диапазона не ***может*** успешно переместиться, в **value** будет записан не
         * ожидаемый ID, а ближайший возможный.
         *
         * Я подчеркнул слово "может" из-за того что @ref getIdInfo не двигает границу, но работает
         * почти так же как и @ref moveBorder который в свою очередь уже двигает границу. <br>
         * Подробнее о правилах перемещения границы: IdRange.
         *
         * Пример:
         * @code
         * IdRange<int> idRange;
         * ...
         * auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, 4); //idInfo.value == 3
         *
         *                       ub>.->.xxxxxx>.x>|
         *        lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  3,5  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  ::   .  .  .
         *
         *
         * auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, 4); //idInfo.value == 5
         *
         *                       ub>.->.->.->|
         *        lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         * @endcode
         *
         * В первом примере Лимит установленный для BorderRange::UpperBorder на 3,5 мешает границе
         * получить информацию о 5. <br>
         * Ближайшее ID к 5, информацию о котором мы можем получить это 3. Значит в **value** будет
         * записана 3. <br>
         * Во втором случае нам ничего не мешает получить информацию о 5. Значит в **value** будет
         * записана 5.
         *
         * @see
         * stepCount <br>
         * IdRange::moveBorder <br>
         * IdRange::getIdInfo
         */

        /**
         * @var ONF::IdRange::IdInfo::stepCount
         *
         * @brief
         * Количество успешно сделанных шагов. <br>
         * Значение по умолчанию 0.
         *
         * **stepCount** повязан с **value**. **stepCount** указывает, какое количество шагов нужно
         * сделать границе до ID записанного в **value**. <br>
         * Если вернуться к примеру из описания **value**:
         * @code
         * IdRange<int> idRange;
         * ...
         * auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, 4); //idInfo.value == 3, idInfo.stepCount == 2
         *
         *                       ub>.->.xxxxxx>.x>|
         *        lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  3,5  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  ::   .  .  .
         *
         *
         * auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, 4); //idInfo.value == 5, idInfo.stepCount == 4
         *
         *                       ub>.->.->.->|
         *        lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         * @endcode
         *
         * В первом случае **stepCount** будет равен 2, так как между 1 и 3 всего 2 шага. <br>
         * Во втором случае **stepCount** будет равен 4, как и ожидалось
         * (во втором аргументе мы просим получить информацию об ID на расстоянии 4 шагов).
         * Между 1 и 5, всего 4 шага, потому **stepCount** равен 4.
         *
         * @see
         * value <br>
         * IdRange::moveBorder <br>
         * IdRange::getIdInfo
         */
    template<class T>
    struct IdRange<T>::IdInfo
    {
        IdInfo();

        /**
         * @param other - копируемый объект класса.
         */
        IdInfo(const IdInfo& other) = default;

        virtual ~IdInfo();

        unsigned    flags;
        unsigned    position;

        BorderRange border;
        bool        state;
        T           value;

        dlong    stepCount;

        /**
         * @param other - копируемый объект класса.
         */
        IdInfo& operator=(const IdInfo& other) = default;
    };
}

#include "IdManagement/IdRange.inl"


namespace ONF
{
    /**
     * @brief Отвечает за способ резервации ID методом RangeIdManager::reserve(T, ReservationMethod).
     *
     * Каждый перечислитель несмотря на описание в придачу подчиняется всем правилам
     * RangeIdManager. <br>
     * Это правила резервации ID, поведения границ диапазона и т.д. <br>
     * Т.е. если где-то нужно передвинуть границу после резервации ID или перепрыгнуть на
     * резервируемый ID, это произойдет.
     *
     * Подробнее о том как каждый из перечислителей влияет на
     * RangeIdManager::reserve(T, ReservationMethod) читайте в описании данного метода.
     */
    enum class ReservationMethod
    {
        NotSet,        ///<@brief Говорит что нужно просто зарезервировать указанный ID.

        Interpolate,   ///<@brief Говорит что нужно зарезервировать указанный ID и интерполировать
                       /// все ID от границы диапазона (включительно) до указанного ID.

        ReserveRange   ///<@brief Говорит что нужно зарезервировать все ID от границы
                       /// диапазона (включительно) до указанного ID (включительно).
    };

    /**
     * @brief Проверяет, не запрещена ли данная комбинация типов.
     *
     * Данная переменная используется в RangeIdManager. <br>
     * Она принимает *true*, что означает что комбинация запрещена, если первый аргумент шаблона не является
     * типом с плавающей точкой, а второй является. Иначе принимает *false*.
     *
     * @see RangeIdManager
     */
    template<class T, class T_Step>
    constexpr bool
    is_forbidden_types_combination = !std::is_floating_point_v<T> && std::is_floating_point_v<T_Step>;


    /**
     * Смотрите: ONF::RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>
     */
    template<class T, class T_Step = T, class T_Access = void>
    class RangeIdManager;

    /**
     * @brief Диапазонный IdManager на основе IdRange.
     *
     * RangeIdManager это IdManager который состоит из IdRange и IdContainer-в. <br>
     * Так как в состав RangeIdManager входит IdRange и IdContainer,
     * то на RangeIdManager распространяются те же правила что и на IdRange с IdContainer. <br>
     * Прежде всего стоит ознакомиться с IdRange и IdContainer. <br>
     *
     * Особенность IdContainer в том что он может выдавать ID разными способами. <br>
     * За то каким образом IdContainer будет выдавать ID отвечает @ref IdIssuingMethod. <br>
     * Но если в IdContainer данное перечисление отвечает только за порядок выдачи ID,
     * то в RangeIdManager оно еще отвечает за поведение границ. <br>
     *
     * Стоит выделить два режима границ: динамический и статический. <br>
     * При динамическом типе границ, эти самые границы могут как раздвигаться, так и сдвигаться:
     * @code
     *                    ub>.->.->.->|                                             ub
     *  |<-.<-.<-.<-.<-.<-lb                          lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6   =>   -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .         .  .  .  .  .  .  @  .  .  .  .  .  .
     *
     *                          |<-.<-.<-ub                                   ub
     *  lb>.->.->.->|                                             lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6   =>   -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .         .  .  .  .  .  .  @  .  .  .  .  .  .
     * @endcode
     *
     * При статическом типе границ, эти самые границы могут только раздвигаться:
     * @code
     *                    ub>.->.->.->|                                             ub
     *  |<-.<-.<-.<-.<-.<-lb                          lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6   =>   -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .         .  .  .  .  .  .  @  .  .  .  .  .  .
     * @endcode
     *
     * К другим особенностям динамического режима стоит отнести наличие так называемого
     * "перепрыгивания", чего нет при статическом режиме, но о Перепрыгивании позже. <br>
     * Так же стоит сказать о том что границы при динамическом режиме синхронизированы между собой. <br>
     * Но это скорее естественный результат, нежели намеренная особенность. <br>
     * В чем суть. Границы как при динамическом, так и при статическом режиме могут иметь два
     * состояния: *true* и *false*. <br>
     * В обоих режимах если граница имеет состояние *true* (граница включена), значит ID на котором
     * она находится зарезервирован. <br>
     * Если граница имеет состояние *false* (граница выключена), значит ID на котором
     * она находится свободен. <br>
     * Если в динамическом режиме освободить ID на который указывает одна из границ, то
     * граница не выключается, как это произошло бы в статическом режиме,
     * она просто сдвинется назад в сторону другой границы. <br>
     * Если после того как граница сдвинулась назад она попадает опять на свободный ID,
     * движение назад продолжается. <br>
     * Так будет до тех пор, пока граница не окажется на зарезервированном ID или пока не столкнется
     * с другой границей. <br>
     * От сюда следует что в динамическом режиме границы всегда показывают на зарезервированный ID
     * и всегда находятся во включенном состоянии, кроме случая когда мы не зарезервировали
     * ни одного ID, тогда границы находятся в одной точке и обе выключены.
     * @code
     * Ситуация 1.
     *
     *           1                    1
     *                                ub
     *           lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  1  1  1  1  1  0  0
     *
     * rangeIdManager.free(4);
     *
     *           1                    0                        1                 1
     *                             |<-ub                                         ub
     *           lb                                            lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  1  1  1  1  0  0  0         0  0  0  1  1  1  1  1  1  1  0  0  0
     *
     *
     * Ситуация 2.
     *
     *           1                    1
     *                                ub
     *           lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  0  0  0  0  1  0  0
     *
     * rangeIdManager.free(4);
     *
     *           1                    0                        1     1
     *                 |<-.<-.<-.<-.<-ub                             ub
     *           lb                                            lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  0  0  0  0  0  0  0         0  0  0  1  1  1  0  0  0  0  0  0  0
     *
     *
     * Ситуация 3.
     *
     *           1                    1
     *                                ub
     *           lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  0  0  0  0  0  0  1  0  0
     *
     * rangeIdManager.free(4);
     *
     *           1                    0                        1
     *           |<-.<-.<-.<-.<-.<-.<-ub                       ub
     *           lb                                            lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  0  0  0  0  0  0  0  0  0         0  0  0  1  0  0  0  0  0  0  0  0  0
     * @endcode
     *
     * Так как в статическом режиме границы не могут сдвигаться, а только раздвигаться, то при
     * освобождении ID на который указывает одна из границ, эта граница просто выключается.
     * @code
     *           1                    1
     *                                ub
     *           lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  0  0  0  0  1  0  0
     *
     * rangeIdManager.free(4);
     *
     *           1                    0
     *                                ub
     *           lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  0  0  0  0  0  0  0
     * @endcode
     *
     * Как и было сказано, в статическом режиме границы не могут сдвигаться.
     * Это сделано для того что бы RangeIdManager мог выдавать ID в порядке возрастания или
     * убывания что невозможно в динамическом режиме. <br>
     * Имеется ввиду что не всегда возможно выдавать освобожденные ID в порядке возрастания
     * или убывания. <br>
     * Это из-за того что при динамическом режиме, освобождая ID находящийся на границе,
     * эта граница сдвигается, что может помешать выдавать ID в нужном порядке.
     *
     * Мы можем получать свободные ID с помощью getFreeId().
     * Этот метод просто раздвигает границы, но если в пределах диапазона есть свободный ID
     * он вернет его. <br>
     * Так же getFreeId() умеет восстанавливать диапазон. Об этом позже. <br>
     * Но мы так же можем резервировать любой ID с помощью reserve(T, ReservationMethod). <br>
     * reserve(T, ReservationMethod) может резервировать ID на границе, в пределах и за
     * пределами диапазона. <br>
     * В обоих режимах следующий за границей ID всегда свободен. <br>
     * Если мы зарезервируем с помощью reserve(T, ReservationMethod) следующий за границей ID,
     * граница рядом с которой находится этот ID, передвинется на него. <br>
     * После это граница проверит, зарезервирован ли следующий ID. Если да, она передвинется на
     * него. И так будет до тех пор, пока следующий ID не окажется пустым.
     * @code
     * Ситуация 1.
     *
     *           1           1
     *                       ub
     *           lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  1  1  0  0  1  0  0
     *
     * rangeIdManager.reserve(2);
     *
     *           1           1                                 1              1
     *                       ub>|                                             ub
     *           lb                                            lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  1  1  1  0  1  0  0         0  0  0  1  1  1  1  1  1  0  1  0  0
     *
     *
     * Ситуация 2.
     *
     *           1           1
     *                       ub
     *           lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  1  1  0  1  1  0  0
     *
     * rangeIdManager.reserve(2);
     *
     *           1           1                                 1                    1
     *                       ub>.->.->|                                             ub
     *           lb                                            lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  1  1  1  1  1  0  0         0  0  0  1  1  1  1  1  1  1  1  0  0
     *
     *
     * Ситуация 3.
     *
     *           1           0
     *                       ub
     *           lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  1  0  0  1  1  0  0
     *
     * rangeIdManager.reserve(2);
     *
     *           1           0                                 1                    1
     *                       ub>.->.->|                                             ub
     *           lb                                            lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  1  1  1  1  0  1  1  1  0  0         0  0  0  1  1  1  1  0  1  1  1  0  0
     * @endcode
     *
     * Из-за того что следующий ID должен быть пустым возникает эффект перепрыгивания. <br>
     * Начнем от обратного. Если границы находятся в точке в выключенном состоянии и при
     * этом выбран статический режим, при резервировании следующего ID,
     * одна граница останется на прежнем месте в выключенном состоянии, а вторая передвинется
     * на зарезервированный ID и включится.
     * @code
     *                    0
     *                    ub
     *                    lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  0  0  0  0  0  0  0
     *
     * rangeIdManager.reserve(1);
     *
     *                    0                                             0  1
     *                    ub>|                                             ub
     *                    lb                                            lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  0  1  0  0  0  0  0         0  0  0  0  0  0  0  1  0  0  0  0  0
     * @endcode
     *
     * В динамическом режиме этого не произойдет из-за того что тогда одна граница будет
     * включена, а другая выключена. <br>
     * Это нормально для статического режима, но не для динамического. <br>
     * Что бы предотвратить это, обе границы перемещаются на зарезервированный ID и
     * включаются.
     * @code
     *                    0
     *                    ub
     *                    lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  0  0  0  0  0  0  0
     *
     * rangeIdManager.reserve(1);
     *
     *                    0                                                1
     *                    ub>|                                             ub
     *                    lb>|                                             lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  0  1  0  0  0  0  0         0  0  0  0  0  0  0  1  0  0  0  0  0
     * @endcode
     *
     * Перепрыгивание возможно и при интерполяции значений. В этом случае границы могут
     * прыгнуть достаточно далеко.
     * @code
     *                    0
     *                    ub
     *                    lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  0  0  0  0  0  0  0
     *
     * rangeIdManager.reserve(5, ReservationMethod::Interpolate);
     *
     *                    0                                                            1
     *                    ub>.->.->.->.->|                                             ub
     *                    lb>.->.->.->.->|                                             lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  0  0  0  0  0  1  0         0  0  0  0  0  0  0  0  0  0  0  1  0
     * @endcode
     *
     * Про интерполяцию читайте: reserve(T, ReservationMethod).
     *
     * Так же хочется отметить еще одну особенность динамического режима. <br>
     * При динамическом режиме границы стремятся находиться на своей территории. <br>
     * О территориях можно узнать из описания IdRange::IdInfo::border. <br>
     * При динамическом режиме возможна ситуация когда обе границы будут по одну сторону от
     * стартового ID, что невозможно при статическом режиме. <br>
     * Когда это произойдет, та граница которая оказалась не на своей территории начнет
     * постепенно возвращаться на свою территорию. Это называется восстановление диапазона. <br>
     * Граница будет считать что на своей территории когда окажется на стартовом ID. <br>
     * Восстановление диапазона будет происходить при вызове getFreeId().
     * @code
     * RangeIdManager<int> rangeIdManager;
     * ...
     *
     *                          1     1
     *                                ub
     *                          lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  0  0  1  1  1  0  0
     *
     * rangeIdManager.getFreeId();
     *
     *                          1     1                                    1        1
     *                                ub                                            ub
     *                       |<-lb                                         lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  0  1  1  1  1  0  0         0  0  0  0  0  0  0  1  1  1  1  0  0
     *
     * rangeIdManager.getFreeId();
     *
     *                       1        1                                 1           1
     *                                ub                                            ub
     *                    |<-lb                                         lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  1  1  1  1  1  0  0         0  0  0  0  0  0  1  1  1  1  1  0  0
     *
     *
     * Теперь когда диапазон восстановлен, getFreeId() продолжит выдавать ID в соответствии с
     * направлением шага.
     *
     *
     * rangeIdManager.getFreeId();
     *
     *                    1           1                                 1              1
     *                                ub>|                                             ub
     *                    lb                                            lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  1  1  1  1  1  1  0         0  0  0  0  0  0  1  1  1  1  1  1  0
     * @endcode
     *
     * Диапазон также можно восстанавливать и с помощью reserve(T, ReservationMethod). <br>
     * Для этого достаточно резервировать следующий за восстанавливаемой границей ID до
     * тех пор, пока диапазон не восстановится. <br>
     * Или можно интерполировать значения от восстанавливаемой границы до стартового ID. <br>
     * Способов восстановить диапазон много.
     * @code
     * RangeIdManager<int> rangeIdManager;
     * ...
     *
     *                          1     1
     *                                ub
     *                          lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  0  0  1  1  1  0  0
     *
     * rangeIdManager.reserve(0, ReservationMethod::Interpolate);
     *
     *                          1     1                                 1           1
     *                                ub                                            ub
     *                    |<-.<-lb                                      lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
     *  0  0  0  0  0  0  1  0  1  1  1  0  0         0  0  0  0  0  0  1  0  1  1  1  0  0
     *
     *
     * Диапазон восстановлен.
     * @endcode
     *
     * Что бы установить динамический режим (установлен по умолчанию) нужно в метод
     * setIdIssuingMethod(IdIssuingMethod) передать IdIssuingMethod::Dynamic. <br>
     * Остальные два перечислителя @ref IdIssuingMethod отвечают за статический режим.
     */
    template<class T, class T_Step>
    class RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>
    {
        /**
         * reservedIds_ хранит все нестандартные ID + стандартные ID вне диапазона.
         * freeIds_ хранит все стандартные ID в пределах диапазона, те что на границах
         * диапазона не в счет.
         *
         * idRange_ уже имеет поле step_ которое мы можем считать, но я решил его здесь
         * дублировать потому что step_ в IdRange не хранит знак числа.
         */
        IdContainer<T> reservedIds_;
        IdContainer<T> freeIds_;
        IdRange<T> idRange_;

        T_Step step_;
        size_t size_;
        bool isHardStep_;
        IdIssuingMethod idIssuingMethod_;

    public:
        /**
         * По умолчанию обе границы выключены, находятся на ID равном 0 и с размером шага 1. <br>
         * Лимит BorderRange::UpperBorder по умолчанию равен
         * [std::numeric_limits::max()](https://en.cppreference.com/w/cpp/types/numeric_limits/max). <br>
         * Лимит BorderRange::LowerBorder по умолчанию равен
         * [std::numeric_limits::lowest()](https://en.cppreference.com/w/cpp/types/numeric_limits/lowest). <br>
         * Метод выдачи ID по умолчанию равен IdIssuingMethod::Dynamic. <br>
         * Так же по умолчанию установлен жесткий шаг.
         *
         * Шаг не может быть равен 0. Если вы передадите в **step** 0,
         * он автоматически станет равен 1. <br>
         * Знак числа шага, передаваемого в **step**, не имеет значения,
         * минус автоматически отбрасывается.
         *
         * @param start - стартовый ID.
         * @param step - размер шага.
         */
        RangeIdManager(T start = 0, T_Step step = 1);

        /**
         * @param other - копируемый объект класса.
         */
        RangeIdManager(const RangeIdManager<T, T_Step>& other);

        /**
         * После перемещения, **other** сохраняет все кроме хранимых ID. <br>
         * Т.е. Лимиты границ, метод выдачи ID и жесткость шага сохраняются.
         *
         * @param other - перемещаемый объект класса.
         */
        RangeIdManager(RangeIdManager<T, T_Step>&& other);

        virtual ~RangeIdManager();

        /**
         * @brief
         * Возвращает свободный ID в соответствии с режимом выдачи ID заданным для данного
         * объекта класса.
         *
         * При первом вызове данного метода он возвращает стартовый ID, а при каждом последующем
         * вызове будет возвращать ID в соответствии с размером и направлением шага. <br>
         * Например, если Стартовый ID равен 3, а шаг равен -2, то при первом вызове данный метод
         * вернет 3, затем 1, -1, -3, -5 и т.д. <br>
         * Если в пределах диапазона появляются свободные ID, метод будет возвращать и их тоже,
         * но это будет происходить в соответствии с заданным режимом выдачи ID. <br>
         * Если однажды граница диапазона упрется в Лимит и свободных ID в пределах диапазона
         * не будет, метод начнет возвращать
         * [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt). <br>
         * Тут важно подчеркнуть тот момент, что данный метод при обычных условиях работает с
         * той границей которая соответствует направлению шага. <br>
         * Если шаг с '-', данный метод будет работать с BorderRange::LowerBorder, а если
         * с '+', то с BorderRange::UpperBorder. <br>
         * Если например мы работаем с BorderRange::UpperBorder и он упирается в Лимит,
         * то данный метод начнет возвращать
         * [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt)
         * даже несмотря на то, что BorderRange::LowerBorder еще не уперся в Лимит.
         *
         * При динамическом режиме, данному методу свойственно восстанавливать диапазон
         * если это необходимо. <br>
         * Порядок действий данного метода при динамическом режиме:
         * 1. Проверяет, не находится ли BorderRange::LowerBorder на территории
         *    BorderRange::UpperBorder. Если да, пытается восстановить. Если нет, переходит к
         *    пункту 2.
         * 2. Проверяет, не находится ли BorderRange::UpperBorder на территории
         *    BorderRange::LowerBorder. Если да, пытается восстановить. Если нет, переходит к
         *    пункту 3.
         * 3. Если в пределах диапазона есть свободный ID, возвращает его, иначе переходит к
         *    пункту 4.
         * 4. Если возможно передвинуть границу в соответствии с размером и направлением шага,
         *    возвращает ID на который была передвинута граница, иначе возвращает
         *    [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt).
         *
         * При статическом режиме выдачи ID равном IdIssuingMethod::Static_Ascending
         * порядок действий данного метода:
         * 1. Проверяет, включена ли нижняя граница. Если нет, включит ее и вернет ее ID.
         *    Если включена, переходит к пункту 2.
         * 2. Если в пределах диапазона есть свободный ID, возвращает его, иначе переходит к
         *    пункту 3.
         * 3. Проверяет, включена ли верхняя граница. Если нет, включит ее и вернет ее ID.
         *    Если включена, переходит к пункту 4.
         * 4. Если возможно передвинуть границу в соответствии с размером и направлением шага,
         *    возвращает ID на который была передвинута граница, иначе возвращает
         *    [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt).
         *
         * При статическом режиме выдачи ID равном IdIssuingMethod::Static_Descending
         * порядок действий данного метода:
         * 1. Проверяет, включена ли верхняя граница. Если нет, включит ее и вернет ее ID.
         *    Если включена, переходит к пункту 2.
         * 2. Если в пределах диапазона есть свободный ID, возвращает его, иначе переходит к
         *    пункту 3.
         * 3. Проверяет, включена ли нижняя граница. Если нет, включит ее и вернет ее ID.
         *    Если включена, переходит к пункту 4.
         * 4. Если возможно передвинуть границу в соответствии с размером и направлением шага,
         *    возвращает ID на который была передвинута граница, иначе возвращает
         *    [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt).
         *
         * @return
         * Если удалось найти свободный ID, возвращает его, иначе возвращает
         * [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt).
         */
        std::optional<T> getFreeId();

        /**
         * @brief Резервирует ID разными способами.
         *
         * Данный метод имеет 2 параметра:  <br>
         * - **id** - ID который нужно зарезервировать, если это возможно, и одновременно цель,
         *   от границы диапазона (включительно) к которой образуется абстрактная область. <br>
         *   Данная область может быть как зарезервирована, так и интерполирована.
         * - **reservationMethod** - Метод резервации ID.
         *
         * За метод резервации ID отвечает перечисление @ref ReservationMethod. <br>
         * О том как влияют его перечислители на процесс резервации ID можно
         * вкратце прочесть здесь: <br>
         * - ReservationMethod::NotSet
         * - ReservationMethod::Interpolate
         * - ReservationMethod::ReserveRange
         *
         * А теперь более подробно об их работе. Далее поочередно в подробностях будет описан
         * каждый перечислитель. <br>
         * Перед использованием метода reserve(T, ReservationMethod) стоит ознакомиться
         * с каждым перечислителем что бы понимать все правила данного метода. <br>
         * Так же стоит помнить что данный метод по сравнению с тем же getFreeId() является
         * очень медленным и к тому же чрезмерное резервирование ID вне диапазона
         * замедляет скорость выдачи ID методом getFreeId().
         *
         * Начнем с ReservationMethod::NotSet. <br>
         * Данный перечислитель будучи переданный в метод reserve(T, ReservationMethod)
         * говорит ему о том что мы просто хотим зарезервировать указанный ID если это
         * возможно.
         *
         * На метод reserve(T, ReservationMethod) распространяются те же правила и
         * обязанности что и на любой другой метод класса RangeIdManager. <br>
         * В эти обязанности входит, в том числе, и обязанность передвинуть границу диапазона
         * в случае если reserve(T, ReservationMethod) резервирует ID являющийся следующим
         * за данной границей ID. <br>
         * Так же, если в динамическом режиме границы диапазона находятся в одной точке
         * будучи выключены, а мы попробуем зарезервировать следующий за одной из границ ID,
         * произойдет перепрыгивание на данный ID. <br>
         * Подробнее обо всем этом в описании данного класса. <br>
         * В остальном данный перечислитель говорит просто зарезервировать указанный ID,
         * будь он в пределах диапазона, за его пределами или на его границах. <br>
         * ID переданный в **id** должен быть свободен.
         *
         * Далее идет ReservationMethod::ReserveRange. <br>
         * Данный перечислитель говорит методу reserve(T, ReservationMethod) зарезервировать
         * все ID от текущей границы до указанного ID. <br>
         * При этом если при резервации промежуточных ID будет встречен уже зарезервированный
         * ID, он просто пропускается. А вот все свободные ID резервируются. <br>
         * Несмотря на то что среди промежуточных ID могут быть уже зарезервированные,
         * ID переданный в **id** должен быть свободен.
         *
         * Если указать в **id** свободный ID находящийся в пределах диапазона или на его
         * границах, данный метод просто зарезервирует данный ID и если этот ID находится
         * на границе диапазона, включит ее. <br>
         * Если указать в **id** свободный ID находящийся за пределами диапазона,
         * все стандартные ID от границы диапазона (включительно) до указанного ID (включительно)
         * резервируются. <br>
         * Т.е. если граница от которой начинается резервация выключена, она включается,
         * тем самым резервируя свой ID. <br>
         * Если границы находятся в точке в выключенном состоянии, при резервации какого либо
         * ID они обе включаются резервируя свой ID.
         * @code
         * Ситуация 1.
         *
         *                    0
         *                    ub
         *                    lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  0  0  0  0  0  0  0  0  0  0
         *
         * rangeIdManager.reserve(3, ReservationMethod::ReserveRange);
         *
         *                    0                                             1        1
         *                    ub>.->.->|                                             ub
         *                    lb                                            lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  0  0  0  0  0  0  1  0  0  0         0  0  0  0  0  0  1  1  1  1  0  0  0
         *
         *
         * Ситуация 2.
         *
         *                    0
         *                    ub
         *                    lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  3,5  4  5  6
         *  .  .  .  .  .  .  @  .  .  .   .   .  .  .
         *  0  0  0  0  0  0  0  0  0  0   0   0  0  0
         *
         * rangeIdManager.reserve(3.5, ReservationMethod::ReserveRange);
         *
         *                    0                                                  1        1
         *                    ub>.->.->|                                                  ub
         *                    lb                                                 lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  3,5  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  3,5  4  5  6
         *  .  .  .  .  .  .  @  .  .  .   .   .  .  .   =>    .  .  .  .  .  .  @  .  .  .   .   .  .  .
         *  0  0  0  0  0  0  0  0  0  0   1   0  0  0         0  0  0  0  0  0  1  1  1  1   1   0  0  0
         *
         *
         * В данных примерах обе границы вначале выключены, но те же результаты будут, если они будут
         * включены.
         *
         *
         * Ситуация 3.
         *
         *           1              1
         *                          ub
         *           lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  1  1  1  1  1  1  0  0  0  0
         *
         * rangeIdManager.reserve(5, ReservationMethod::ReserveRange);
         *
         *           1              1                              1                       1
         *                          ub>.->.->|                                             ub
         *           lb                                            lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  1  1  1  1  1  1  0  0  1  0         0  0  0  1  1  1  1  1  1  1  1  1  0
         *
         *
         * Ситуация 4.
         *
         *           1              1
         *                          ub
         *           lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  5,5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .   .   .
         *  0  0  0  1  1  1  1  1  1  0  0  0   0   0
         *
         * rangeIdManager.reserve(5.5, ReservationMethod::ReserveRange);
         *
         *           1              1                                   1                       1
         *                          ub>.->.->|                                                  ub
         *           lb                                                 lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  5,5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  5,5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .   .   .   =>    .  .  .  .  .  .  @  .  .  .  .  .   .   .
         *  0  0  0  1  1  1  1  1  1  0  0  0   1   0         0  0  0  1  1  1  1  1  1  1  1  1   1   0
         *
         *
         * В данных примерах обе границы вначале включены, но те же результаты будут, если они будут
         * выключены.
         * @endcode
         *
         * И наконец ReservationMethod::Interpolate. <br>
         * Сразу отмечу что в этом случае если в **id** указать нестандартный ID, то просто произойдет
         * резервация указанного ID по всем тем правилам как если бы мы передали не
         * ReservationMethod::Interpolate, а ReservationMethod::NotSet.
         *
         * Если границы диапазона не находятся на одном и том же ID в выключенном состоянии и мы
         * резервируем ID вне диапазона, данный перечислитель говорит методу reserve(T, ReservationMethod)
         * зарезервировать указанный ID и передвинуть на него границу.
         * @code
         * Ситуация 1.
         *
         *                    1
         *                    ub
         *                    lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  0  0  0  1  0  0  0  0  0  0
         *
         * rangeIdManager.reserve(3, ReservationMethod::Interpolate);
         *
         *                    1                                             1        1
         *                    ub>.->.->|                                             ub
         *                    lb                                            lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  0  0  0  1  0  0  1  0  0  0         0  0  0  0  0  0  1  0  0  1  0  0  0
         *
         *
         * Обратите внимание, что 1 и 2 небыли зарезервированы.
         * Так же обратите внимание на то что обе границы здесь был изначально в одной точке и
         * включены. О случае когда он изначально в точке, но выключены, поговорим позже,
         * так как границы в таком случае ведут себя по-разному в динамическом и статическом
         * режиме.
         *
         *
         * Ситуация 2.
         *
         *           1              1
         *                          ub
         *           lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  1  1  1  1  1  1  0  0  0  0
         *
         * rangeIdManager.reserve(5, ReservationMethod::Interpolate);
         *
         *           1              1                              1                       1
         *                          ub>.->.->|                                             ub
         *           lb                                            lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  1  1  1  1  1  1  0  0  1  0         0  0  0  1  1  1  1  1  1  0  0  1  0
         *
         *
         * Обратите внимание, что 3 и 4 небыли зарезервированы, но были интерполированы.
         * О том что это значит позже.
         *
         *
         * Следующая ситуация возможна только при статическом режиме, так как здесь состояние
         * обеих границ может различаться друг от друга.
         *
         *            1              0
         *                          ub
         *           lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  1  1  1  1  1  0  0  0  0  0
         *
         * rangeIdManager.reserve(5, ReservationMethod::Interpolate);
         *
         *           1              0                              1                       1
         *                          ub>.->.->|                                             ub
         *           lb                                            lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  1  1  1  1  1  0  0  0  1  0         0  0  0  1  1  1  1  1  0  0  0  1  0
         *
         *
         * 2, 3 и 4 остались свободными.
         * Как можно заметить, в этом примере все работает так же как и в других примерах выше,
         * разница лишь в том что изначально BorderRange::UpperBorder быль отключен, а
         * BorderRange::LowerBorder включен. Данная ситуация невозможна в динамическом режиме.
         * @endcode
         *
         * Если указать в **id** свободный ID находящийся в пределах диапазона или на его границах,
         * данный метод просто зарезервирует данный ID и если этот ID находится  на границе диапазона,
         * включит ее.
         *
         * Теперь о ситуации когда обе границы находятся в точке в выключенном состоянии. <br>
         * Если установлен статический режим, то все будет так же как и в примерах приведенных выше.
         * @code
         *                    0
         *                    ub
         *                    lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  0  0  0  0  0  0  0  0  0  0
         *
         * rangeIdManager.reserve(3, ReservationMethod::Interpolate);
         *
         *                    0                                             0        1
         *                    ub>.->.->|                                             ub
         *                    lb                                            lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  0  0  0  0  0  0  1  0  0  0         0  0  0  0  0  0  0  0  0  1  0  0  0
         *
         *
         * 0, 1 и 2 остались свободны.
         * Граница BorderRange::LowerBorder осталась выключенной, а BorderRange::UpperBorder
         * включилась.
         * @endcode
         *
         * В динамическом режиме произойдет перепрыгивание на указанный ID.
         * @code
         *                    0
         *                    ub
         *                    lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  0  0  0  0  0  0  0  0  0  0
         *
         * rangeIdManager.reserve(3, ReservationMethod::Interpolate);
         *
         *                    0                                                      1
         *                    ub>.->.->|                                             ub
         *                    lb>.->.->|                                             lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  0  0  0  0  0  0  0  0  1  0  0  0         0  0  0  0  0  0  0  0  0  1  0  0  0
         * @endcode
         *
         * А теперь вкратце про то, что происходит под капотом. <br>
         * Данный перечислитель не просто так получил название "Interpolate". <br>
         * Под капотом данный метод находит все стандартные промежуточные ID плюс ID на котором
         * находилась граница диапазона перед началом интерполяции и делает следующее:
         * - Если ID зарезервирован, оставляет его таковым.
         * - Если ID свободен, он переходит под ответственность диапазона.
         *   Визуально это означает лишь то, что данные ID можно будет получить
         *   методом getFreeId().
         *
         * ID переданный в **id** всегда должен быть свободен.
         *
         * @param id - ID который нужно зарезервировать.
         * @param reservationMethod - метод резервации ID указанного в **id**.
         * @return Если удалось зарезервировать указанный ID, возвращает *true*, иначе *false*.
         */
        bool reserve(T id, ReservationMethod reservationMethod = ReservationMethod::NotSet);

        /**
         * @brief Освобождает указанный ID.
         * @param id - ID который нужно освободить.
         * @return Если удалось успешно освободить указанный ID, возвращает *true*, иначе *false*.
         */
        bool free(T id);

        /**
         * @brief Освобождает все зарезервированные ID.
         */
        void freeAll();

        /**
         * @brief Сообщает, зарезервировано ли ID.
         * @param id - ID который нужно найти среди зарезервированных.
         * @return Если ID зарезервирован, возвращает *true*, иначе *false*.
         */
        bool find(T id) const; // TODO: Протестировать в разных ситуациях.

        /**
         * @brief Задает Лимит для указанной границы диапазона.
         *
         * Установить новый Лимит возможно только если он находится за пределами диапазона. <br>
         * При этом если новый Лимит устанавливается между границей диапазона и
         * старым Лимитом, все ID между новым Лимитом и старым будут освобождены. <br>
         * Если после отсечения части ID не удастся установить новый Лимит по какой-либо причине,
         * RangeIdManager выкинет исключение.
         *
         * @param borderRange - граница диапазона, лимит для которой нужно установить.
         *
         * @param
         * value - Лимит который нужно установить для указанной в **borderRange**
         * границы диапазона.
         *
         * @return Если удалось успешно установить Лимит, возвращает *true*, иначе *false*.
         */
        bool setBorderLimit(BorderRange borderRange, T value);

        /**
         * @brief Возвращает Лимит указанной границы диапазона.
         * @param borderRange - граница диапазона, Лимит которой нужно получить.
         * @return Возвращает Лимит указанной границы диапазона.
         */
        T getBorderLimit(BorderRange borderRange) const;

        /**
         * @brief Включает или отключает жесткий шаг.
         *
         * При включенном жестком шаге, попытки зарезервировать нестандартный ID будут
         * блокироваться, а при отключенном резервация будет происходить успешно. <br>
         * Если отключить жесткий шаг и зарезервировать некое количество нестандартных
         * ID, а потом включить жесткий шаг, все зарезервированные нестандартные
         * ID будут освобождены.
         *
         * @param value - Состояние шага. *true* - включить жесткий шаг, а *false* - отключить.
         */
        void setHardStep(bool value);

        /**
         * @brief Сообщает, установлен ли жесткий шаг.
         *
         * О том что такое жесткий шаг: setHardStep(bool).
         *
         * @return Если жесткий шаг установлен, возвращает *true*, иначе *false*.
         */
        bool isHardStep() const;

        /**
         * @brief Меняет метод выдачи ID и режим границ.
         *
         * При смене режима границ со статического на динамический, данный метод передвигает
         * границу диапазона на зарезервированный ID в случае если она находится на свободном ID. <br>
         * Движение границ возможно только в сторону уменьшения диапазона, так как и в статическом и
         * в динамическом режиме, следующий за границей ID всегда свободен.
         * @code
         * RangeIdManager<int> rangeIdManager;
         * ...
         * rangeIdManager.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
         *
         *           1                    0
         *                                ub
         *           lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  1  0  1  0  0  1  1  1  0  0  0  1
         *
         * rangeIdManager.setIdIssuingMethod(IdIssuingMethod::Dynamic);
         *
         *           1                    0                        1              1
         *                          |<-.<-ub                                      ub
         *           lb                                            lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6        -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .  .   =>    .  .  .  .  .  .  @  .  .  .  .  .  .
         *  0  1  0  1  0  0  1  1  1  0  0  0  1         0  1  0  1  0  0  1  1  1  0  0  0  1
         * @endcode
         * В данном примере можно увидеть что несмотря на то что свободные ID были позади как у
         * BorderRange::LowerBorder так и BorderRange::UpperBorder, передвинулась только
         * BorderRange::UpperBorder. <br>
         * Это из-за того что BorderRange::UpperBorder был на свободном ID, а BorderRange::LowerBorder
         * был на зарезервированном ID.
         *
         * При смене режима границ с динамического на статический, данный метод сперва восстановит
         * диапазон если это необходимо. <br>
         * О восстановлении диапазона можно прочитать в описании RangeIdManager.
         *
         * Все это нужно для того что бы соответствовать требованиям того режима в который
         * переходят границы диапазона.
         *
         * @param
         * idIssuingMethod - метод выдачи ID и режим границ на который нужно переключить данный
         * объект класса.
         */
        void setIdIssuingMethod(IdIssuingMethod idIssuingMethod);

        /**
         * @brief Возвращает заданный метод выдачи ID.
         * @return Возвращает один из перечислителей @ref IdIssuingMethod.
         */
        IdIssuingMethod getIdIssuingMethod() const;

        /**
         * @brief Возвращает количество зарезервированных ID.
         * @return Возвращает количество зарезервированных ID.
         */
        size_t size() const;

        /**
         * @brief Проверяет, является ли указанный ID стандартным для данного объекта класса.
         *
         * Подробнее об этом методе: isStandardId(T, T, T).
         *
         * @param id - ID который нужно проверить на стандартность.
         * @return Если **id** является стандартным, вернет *true*, иначе *false*.
         */
        bool isStandardId(T id) const;

        /**
         * @brief Возвращает значение стартового ID.
         * @return Возвращает значение стартового ID.
         */
        T getStart() const;

        /**
         * @brief Возвращает размер шага и его направление.
         * @return Возвращает размер шага и его направление.
         */
        T_Step getStep() const;

        /**
         * @brief Возвращает текущее значение указанной границы диапазона.
         * @param borderRange - граница диапазона, текущее значение которой нужно получить.
         * @return Возвращает текущее значение указанной границы диапазона.
         */
        T getBorderValue(BorderRange borderRange) const;

        /**
         * @brief Возвращает состояние указанной границы диапазона.
         * @param borderRange - граница диапазона, состояние которой нужно получить.
         * @return Если граница диапазона включена, возвращает *true*, иначе *false*.
         */
        bool getBorderState(BorderRange borderRange) const;

        /**
         * @brief Возвращает ближайший к переданному ID, стандартный ID.
         *
         * Лимит не распространяется на данный метод. <br>
         * В **id** надо передать тот ID, ближайший стандартный ID к которому нужно найти,
         * а в **borderRange** надо передать ту границу от которой будет вестись отсчет. <br>
         * Т.е. искомый ID будет находиться между **id** и границей переданной в
         * **borderRange**. <br>
         * Данный метод основан на функции ONF::findNearestStdId(T, T, T). <br>
         * Параметр **target** данной функции это параметр **id** данного метода,
         * а параметр **start** это **borderRange**.
         *
         * Параметр **borderRange** необходим из-за особенности динамического режима,
         * а именно из-за того что обе границы могут оказаться по одну сторону от
         * стартового ID. <br>
         * Подробнее о данной особенности можно прочитать в описании данного класса. <br>
         * Если бы не эта особенность динамического режима, **borderRange** можно
         * было бы откинут и оставить только **id**. <br>
         * В таком случае отсчет мог бы вестись от стартового ID. <br>
         * Но из-за динамического режима это невозможно потому что возникнет такая
         * проблема:
         * @code
         * rangeIdManager.findNearestStdId(5.5);  //result: 5
         *
         *                                ub
         *                             lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  5.5  6
         *  .  .  .  .  .  .  @  .  .  .  .  .   .   .
         *
         *
         * rangeIdManager.findNearestStdId(1.5);  //result: 1
         *
         *                                     ub
         *                                  lb
         * -6 -5 -4 -3 -2 -1  0  1  1.5  2  3  4  5  6
         *  .  .  .  .  .  .  @  .   .   .  .  .  .  .
         * @endcode
         * В первом случае все хорошо, ближайший стандартный к границе диапазона
         * ID равен 5. <br>
         * А вот во втором случае ошибка. Ближайшим стандартным ID к границе
         * диапазона является 2, но метод возвратит 1. <br>
         * В целом это не ошибка, но для данного класса это все же она.
         * Потому был добавлен параметр **borderRange**. Он уточняет, от какой
         * границы ведется отсчет. <br>
         * В примере выше, в обоих случаях можно передавать в **borderRange**
         * как BorderRange::UpperBorder, так и BorderRange::LowerBorder,
         * результат будет один, и этот результат будет правильным. <br>
         * К тому же **borderRange** вносит конкретику и в случае когда ID
         * переданный в **id** находится в диапазоне:
         * @code
         * rangeIdManager.findNearestStdId(3.5, BorderRange::UpperBorder);  //result: 4
         *
         *                                        ub
         *                       lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  3.5  4  5  6
         *  .  .  .  .  .  .  @  .  .  .   .   .  .  .
         *
         *
         * rangeIdManager.findNearestStdId(3.5, BorderRange::LowerBorder);  //result: 3
         *
         *                                        ub
         *                       lb
         * -6 -5 -4 -3 -2 -1  0  1  2  3  3.5  4  5  6
         *  .  .  .  .  .  .  @  .  .  .   .   .  .  .
         * @endcode
         *
         * @param id - ID, ближайший стандартный ID к которому нужно найти.
         * @param borderRange - граница от которой будет вестись отсчет.
         *
         * @return
         * Если в **id** передан стандартный ID, возвращает его же. <br>
         * Если в **id** передан нестандартный ID, возвращает ближайший к
         * нему стандартный ID.
         */
        T findNearestStdId(T id, BorderRange borderRange) const;

        /**
         * @param other - копируемый объект класса.
         */
        RangeIdManager& operator=(const RangeIdManager<T, T_Step>& other);

        /**
         * После перемещения, **other** сохраняет все кроме хранимых ID. <br>
         * Т.е. Лимиты границ, метод выдачи ID и жесткость шага сохраняются.
         *
         * @param other - перемещаемый объект класса.
         */
        RangeIdManager& operator=(RangeIdManager<T, T_Step>&& other);

    protected:
        /**
         * @brief Возвращает количество свободных ID в пределах диапазона.
         * @return Возвращает количество свободных ID в пределах диапазона.
         */
        size_t getFreeIdsSize() const;

        /**
         * @brief Возвращает количество зарезервированных ID вне диапазона плюс нестандартные ID.
         * @return Возвращает количество зарезервированных ID вне диапазона плюс нестандартные ID.
         */
        size_t getReservedIdsSize() const;

    private:
        /**
         * Предвигает границу которую выбирает исходя из направления шага.
         * Если шаг с '-', данный метод будет работать с BorderRange::LowerBorder, а если
         * с '+', то с BorderRange::UpperBorder.
         *
         * Сперва передвигает границу, если ее удалось передвинуть вызывает метод
         * expandRangeIfPossible.
         * Важно подчеркнуть что данный метод возвращает тот ID на который передвинулась граница
         * до вызова expandRangeIfPossible.
         *
         * @return
         * Если границу удалось передвинуть возвращает ID на который переместилась граница,
         * иначе возвращает std::nullopt.
         */
        std::optional<T> getNextId();

        /**
         * Проверяет следующий за границей диапазона ID, если он зарезервирован,
         * диапазон расширяется и захватывает его.
         * Потом опять проверяет следующий ID и т.д. до тех пор пока следующий ID
         * не окажется свободнен или пока мы не упремся в Лимит.
         *
         * @param border - граница, которую нужно передвинуть вперед если это возможно.
         *
         * @return
         * Возвращает последнюю полученную структуру IdInfo.
         * Если граница диапазона упрется в Лимит то IdInfo будет
         * содержать информацию об этом.
         */
        typename IdRange<T>::IdInfo expandRangeIfPossible(BorderRange border);

        /**
         * Если границы не находятся в точке, предвигает указанную границу диапазона
         * назад на 1 ID и проверяет, если данный ID свободен, передвигает
         * границу еще на 1 ID и опять проверяет.
         * Так будет происходить до тех пор пока граница не встанет на зарезервированный
         * ID или пока не попробует пересеч другую границу.
         * Если границы находятся в точке то ничего не произойдет.
         *
         * Данный метод должен применяться только для динамического режима, так как при
         * статическом режиме границы не могут двигаться назад уменьшая диапазон.
         *
         * @param border - граница, которую нужно передвинуть назад если это возможно.
         *
         * @return
         * Возвращает последнюю полученную структуру IdInfo.
         * Если указанная граница диапазона попробует пересечь другую
         * границу диапазона то IdInfo будет содержать информацию об этом.
         */
        typename IdRange<T>::IdInfo reduceRangeIfPossible(BorderRange border);

        /**
         * Включает обе границы диапазона резервируя ID на который они указывают.
         * Данный метод подразумевает что границы находятся в точке. Потому
         * резервируется только один ID значение которого будет возращено данным методом.
         *
         * @return Возращает ID на котором распологаются границы диапазона.
         */
        T activateBothBorders();

        /**
         * То же что и activateBothBorders(), но после резервации ID, данный метод попробует
         * раздвинуть границы методом expandRangeIfPossible(BorderRange).
         *
         * Вернет он ID который был зарезервирован до вызова функции
         * expandRangeIfPossible(BorderRange).
         */
        T activateBothBordersWithExpending();

        /**
         * Перепрыгивание.
         *
         * Перемещает обе границы на указанный ID.
         * Границы диапазона должны быть в точке в выключенном состоянии, а так же в **id**
         * должен быть передан стандартный ID и этот ID не должен выходить за пределы Лимита.
         *
         * Если метод переместил первую границу, но ему не удалось по какой либо
         * причине передвинуть вторую, он попытается вернуть первую границу на место.
         * Если ему не удалось вернуть первую границу на место, метод кинет исключение.
         *
         * @param id - ID на который должны перепрыгнуть границы диапазона.
         *
         * @return
         * Если в **id** передан нестандартный ID, вернет *false*.
         * Если границы диапазона не находятся в точке, вернет *false*.
         * Если удалось передвинуть обе границы вернет *true*, либо *false*.
         */
        bool jumpOver(T id);

        /**
         * Данный метод нормализует указанную границу диапазона.
         * Это необходимо при смене режима со статического на динамический или с динамического
         * на статический.
         * Данный метод подготавливает границы диапазона к работе в новом режиме.
         * Например, если мы переводим режим с динамического на статический, данный метод
         * востановит диапазон, а если со статического на динамический, то он передвинет границы
         * на зарезервированные ID вызовом функции reduceRangeIfPossible(BorderRange).
         *
         * То в какой режим будут переводиться границы зависит от поля idIssuingMethod_ данного
         * объекта класса. Потому, прежде чем вызывать данный метод нужно обновить значение
         * данного поля.
         *
         * @param borderRange - граница диапазона которую нужно нормализовать.
         *
         * @return
         * Вернет флаг последней полученной структуры IdInfo или IDRF_SUCCESSFULLY в случае успеха
         * если normalizeBorderRange не получал структуру IdInfo.
         */
        unsigned normalizeBorderRange(BorderRange borderRange);

        /**
         * Резервирует указанный ID если он находится в пределах диапазона.
         *
         * @param id - ID который необходимо зарезервировать.
         * @return
         * Если ID переданный в **id** находится вне диапазона или на его границах,
         * вернет *false*.
         * Если удалось успешно зарезервировать ID, вернет *true*, иначе *false*.
         */
        bool reserveIdInRange(T id);

        /**
         * Включает указанную границу диапазона если она выключена, тем самым резервируя ID
         * на котором она распологается.
         *
         * @param borderRange - граница диапазона которую необходимо включить.
         * @return Если граница диапазона включена, возвращает *false*, иначе *true*.
         */
        bool reserveBorderRange(BorderRange borderRange);

        /**
         * Данный метод не имеет никаких проверок на корректность переданных данных.
         * Если **id** больше UpperBorder, данный метод вернет UpperBorder,
         * иначе вернет LowerBorder.
         * Тобишь данный метод вернет LowerBorder даже если ID находится в пределах
         * диапазона или на его границах.
         *
         * Этот метод был создан просто потому что данный кусок кода достаточно часто встречается.
         *
         * @param id - проверяемый ID.
         * @return Если **id** больше UpperBorder, вернет UpperBorder, иначе LowerBorder.
         */
        BorderRange getExpandableBorderRange(T id) const;

        /**
         * Передвигает указанную границу диапазона на следующий ID, но только в том случае
         * если следующий ID равен ID переданному в **id**.
         * После перемещения границы данный метод вызывает expandRangeIfPossible(BorderRange).
         *
         * Небольшое уточнение. Он не просто перемещает границу, а резервирует ID на который
         * переместилась граница. И происходит это все по правилам RangeIdManager и установленного
         * режима выдачи ID.
         *
         * @param borderRange - граница, которую мы хотим передвинуть.
         *
         * @param
         * id - ID с которым должен совпадать следующий, за указанной в **borderRange**
         * границей, ID.
         *
         * @return Если граница была передвинута, вернет *true*, иначе *false*.
         */
        bool moveBorderToNextId(BorderRange borderRange, T id);

        /**
         * Резервирует указанный ID и интерполирует промежуточные значения если это возможно.
         * В **id** должен быть передан только стандартный ID.
         * Если ID находится в пределах диапазона или на его границах, происходит только
         * резервация и только если это возможно.
         * Данный метод не проверяет указанный ID на факт выхода за пределы Лимита и не
         * проверяет стандартность переданного в него ID.
         *
         * @param
         * id - ID который нужно зарезервировать и если это возможно, до которого нужно
         * интерполировать.
         *
         * @return
         * Если удалось зарезервировать указанный ID и интерполировать, если это нужно,
         * вернет *true*, иначе *false*.
         *
         * @see reserve(T, ReservationMethod)
         */
        bool interpolateIds(T id);

        /**
         * Резервирует все ID от границы диапазона (включительно) до указанного в **id**
         * ID (включительно).
         * Если ID находится в пределах диапазона или на его границах, резервирует
         * только его и только если это возможно.
         * Данный метод не проверяет переданный в него ID на факт выхода за пределы Лимита.
         *
         * @param id - ID который нужно зарезервироать или ID до которого нужно резервировать.
         *
         * @return
         * Если удалось зарезервировать указанный ID и, если нужно, все промежуточные ID,
         * вернет *true*, иначе *false*.
         *
         * @see reserve(T, ReservationMethod)
         */
        bool reserveIds(T id);

    };
}

#include "IdManagement/RangeIdManager.inl"

#endif
