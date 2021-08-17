#ifndef ID_MANAGEMENT_H_
#define ID_MANAGEMENT_H_

#include "ONF.h"

#include <optional>
#include <list>
#include <set>


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
        Dynamic,            ///<ID выдаются в порядке их добавления. <br>
                            /// В классе RangeIdManager границы имеют плавающий характер.
        Static_Ascending,   ///<ID выдаются в порядке возрастания. <br>
                            /// В классе RangeIdManager границы имеют фиксированный характер.
        Static_Descending   ///<ID выдаются в порядке убывания. <br>
                            /// В классе RangeIdManager границы имеют фиксированный характер.
    };


    /**
     * @brief Контейнер с настраиваемым способом выдачи ID.
     *
     * По сути IdContainer это объединение [std::list](https://en.cppreference.com/w/cpp/container/list)
     * и [std::set](https://en.cppreference.com/w/cpp/container/set). <br>
     * IdContainer хранит все записанные в него уникальные ID и выдает их в порядке возрастания,
     * убывания или добавления. <br>
     * Если метод выдачи ID равен IdIssuingMethod::Static_Ascending, то
     * ID выдаются в порядке возрастания. <br>
     * Если метод выдачи ID равен IdIssuingMethod::Static_Descending, то
     * ID выдаются в порядке убывания. <br>
     * Если метод выдачи ID равен IdIssuingMethod::Dynamic, то
     * ID выдаются в порядке их добавления в контейнер. <br>
     * По умолчанию метод выдачи ID равен IdIssuingMethod::Dynamic. <br>
     * Мы можем задать способ выдачи ID в конструкторе при создании и менять через метод
     * setIdIssuingMethod(IdIssuingMethod).
     *
     * Когда метод выдачи ID равен IdIssuingMethod::Dynamic, все ID хранятся в **unorderedIds_**,
     * а при IdIssuingMethod::Static_Ascending и IdIssuingMethod::Static_Descending в
     * **orderedIds_**:
     *
     * @code
     * std::list<T> unorderedIds_;
     * std::set<T> orderedIds_;
     * @endcode
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
         * @param id - проверяемое ID.
         * @return Если ID найдено, возвращает *true*, иначе *false*.
         */
        bool find(T id) const;

        /**
         * @brief Возвращает ID по указанному индексу.
         * @param index - индекс по которому нужно найти ID.
         *
         * @return
         * Если ID по указанному индексу найден, возвращает ID,
         * иначе [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt).
         */
        std::optional<T> findByIndex(size_t index) const;

        /**
         * @brief Задает метод выдачи ID для IdContainer.
         *
         * @bug
         * На момент версии 0.0.0 вызов этого метода может быть очень затратным по времени. <br>
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

/// @defgroup IdRange_Flag
/// @brief Флаги структуры @ref ONF::IdRange::IdInfo.
///@{
#define IDRF_NOT_SET            0x0000   ///<Флаг не задан.
#define IDRF_SUCCESSFULLY       0x0001   ///<Задача успешно выполнена.
#define IDRF_ID_OUT_OF_LIMIT    0x0002   ///<Граница попыталась выйты за пределы своего Лимита.
#define IDRF_RANGE_ARE_BENT     0x0004   ///<Одна граница попыталась пересечь другую границу.
///@}

/// @defgroup IdRange_Position
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
        UpperBorder,   ///<Верхняя граница диапазона.
        LowerBorder    ///<Нижняя граница диапазона.
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
     * Если в результате вычислений, \f$ n \f$ окажется целым числом, то проверяемый
     * ID (\f$ a_n \f$) можно считать стандартным.
     * Если \f$ n \f$ окажется дробным, то проверяемый ID будет нестандартным.
     *
     * @param target - ID которое нужно проверить.
     * @param start - начальный ID.
     * @param step - размер шага.
     * @return Если **target** окажется стандартным ID, вернется *ture*, иначе *false*.
     */
    template<class T>
    bool isStandardId(T target, T start, T step) {
        ldouble n = static_cast<ldouble>(target) - static_cast<ldouble>(start);
        n = std::abs((n / static_cast<ldouble>(step)) + 1.0);

        return (n - static_cast<udlong>(n) == 0.0);
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
     * При создании IdRange обе границы находятся в одной точке, она задается при создании
     * и называется "Стартовая ID" или просто "Старт" ( @ ). <br>
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
     * Несмотря на то что границы могут идти навстречу друг другу и могут даже встретиться в одной точке,
     * они никогда не могут пересечь друг друга. <br>
     * Граница, которая попытается пересечь другую границу, остановится там где, находится другая граница:
     * @code
     *              |<x.<x.<-.<-.<-.<-ub                                ub
     *                    lb                                            lb
     * -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6   =>   -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
     *  .  .  .  .  .  .  @  .  .  .  .  .  .         .  .  .  .  .  .  @  .  .  .  .  .  .
     * @endcode
     *
     * Так же для каждой границы можно установить Лимит ( :: ). <br>
     * Лимит можно установить как вне диапазона, так и на границе диапазона, но не
     * внутри диапазона. <br>
     * Граница диапазона не может пересечь установленный для нее Лимит. <br>
     * В случае если граница диапазона попробует это сделать и Лимит установлен на стандартном ID,
     * граница диапазона остановится там где установлен Лимит. <br>
     * Если граница диапазона попробует пересечь Лимит который установлен на нестандартном ID,
     * она остановится на ближайшем к Лимиту стандартном ID. <br>
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
     * По сути moveBorder(BorderRange, dlong) и getIdInfo(BorderRange, dlong) const это
     * почти одна и та же функция. <br>
     * Разница в том что в самом конце moveBorder(BorderRange, dlong) все же передвигает границу,
     * тогда как getIdInfo(BorderRange, dlong) const этого не делает. <br>
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
     * При тех же условиях, в первом случае мы получим информацию об ID равном 16,
     * во втором случае так же о 16, в третьем, четвертом и т.д. тоже о 16. <br>
     * Это из-за того что граница не передвигается и нам придется увеличивать второй параметр
     * getIdInfo(BorderRange, dlong) const что бы получить информацию о более больших ID
     * или все же двигать границу. <br>
     *
     * Если продолжить эту логическую цепочку, можно прийти к выводу о том
     * что если мы не хотим двигать границу, а хотим только получать информацию об ID, то максимальное ID,
     * информацию о котором мы можем получить, ограниченно типом данных второго параметра,
     * если опустить все прочее. <br>
     * Для решения этой проблемы была добавлена перегрузка для
     * @ref getIdInfo - getIdInfo(BorderRange, T, dlong) const. <br>
     * Она работает так же как и обычная getIdInfo(BorderRange, dlong) const, но здесь во втором
     * параметре мы указываем временное значение границы указанной в первом параметре. <br>
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
         * Шаг не может быть равен 0. Если вы передадите в **step** 0,
         * он автоматически станет равен 1. <br>
         * Знак числа шага, передаваемого в **step**, не имеет значения,
         * минус автоматически отбрасывается.
         *
         * @param start - стартовый ID.
         * @param step - размер шага.
         */
        IdRange(T start = 0, T step = 1);

        /**
         * @param other - копируемый объект класса.
         */
        IdRange(const IdRange& other) = default;

        virtual ~IdRange();

        /**
         * @brief Передвигает указанную границу диапазона.
         *
         * **n** показывает на какое количество шагов нужно переместить границу диапазона указанную в
         * **borderRange**, а знак числа указывает направление движения. <br>
         * Если **n** имеет знак "+", граница будет идти в сторону расширения диапазона. <br>
         * Если **n** имеет знак "-", граница будет идти в сторону уменьшения диапазона.
         *
         * Более подробно о работе этого метода: <br>
         * Описание IdRange <br>
         * IdInfo
         *
         * @param borderRange - граница диапазона, которую нужно передвинуть.
         *
         * @param
         * n - количество шагов, на которое нужно передвинуть указанную границу диапазона,
         * и направление движения.
         *
         * @return
         * Возвращает структуру IdInfo с информацией о последнем ID на который смогла успешно
         * переместиться граница диапазона.
         */
        IdInfo moveBorder(BorderRange borderRange, dlong n);

        /**
         * @brief Возвращает информацию об ID.
         *
         * Данный метод работает так же как и moveBorder(BorderRange, dlong), но
         * в конце своей работы не передвигает границу.
         *
         * @param borderRange - граница диапазона, от которой будет вестись отсчет шагов.
         *
         * @param
         * n - количество шагов, которое нужно сделать от границы диапазона указанной в **borderRange**
         * что бы найти ID, информацию о котором нужно получить.
         *
         * @return
         * Возвращает структуру IdInfo с информацией о последнем ID на который ***может***
         * переместиться граница диапазона.
         *
         * @see Описание IdRange
         */
        IdInfo getIdInfo(BorderRange borderRange, dlong n) const;

        /**
         * @brief Возвращает информацию об ID.
         *
         * Данный метод работает так же как getIdInfo(BorderRange, dlong) const, но здесь добавляется
         * параметр **id**. <br>
         * В getIdInfo(BorderRange, dlong) const параметр **id** скрыт от взгляда. Он равен
         * текущему значению границы диапазона преданному в первый аргумент. <br>
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
         * [std::nullopt](https://en.cppreference.com/w/cpp/utility/optional/nullopt),
         * иначе структуру IdInfo.
         */
        std::optional<IdInfo> getIdInfo(BorderRange borderRange, T id, dlong n) const;

        /**
         * @brief Сбрасывает значение и состояние границ диапазона.
         *
         * **reset** сбрасывает только значение и состояние границ диапазона, но лимит
         * установленный для границ диапазона не сбрасывается.
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
         * @return Если граница диапазона включена возвращает *true*, иначе *false*.
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
     * @brief Структура для предоставления информации об ID, возвращаемая IdRange.
     *
     * @pre Прежде стоит ознакомиться с IdRange.
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

        unsigned    flags;      ///<@brief Флаги. <br>
                                /// Значение по умолчанию @ref IDRF_NOT_SET.
                                ///
                                /// **flags** может хранить достаточно разные флаги. <br>
                                /// На данный момент доступны следующие флаги: @ref IdRange_Flag.
                                ///
                                /// По умолчанию **flags** имеет значение @ref IDRF_NOT_SET
                                /// (не путать с @ref IDRP_NOT_SET). <br>
                                /// Флаги @ref IDRF_SUCCESSFULLY, @ref IDRF_ID_OUT_OF_LIMIT,
                                /// @ref IDRF_RANGE_ARE_BENT показывают, успешно ли выполнена
                                /// задача перемещения или получения информации об ID классом IdRange. <br>
                                /// Если в процессе выполнения одна из границ диапазона попытается выйти
                                /// за пределы своего Лимита, в **flags** будет записан
                                /// @ref IDRF_ID_OUT_OF_LIMIT. <br>
                                /// Если в процессе выполнения одна из границ диапазона попытается
                                /// пересечь другую границу диапазона, в **flags** будет записан
                                /// @ref IDRF_RANGE_ARE_BENT. <br>
                                /// Если задача была выполнена успешно и граница не пытались пересечь
                                /// ни Лимит ни другую границу в **flags** будет записан
                                /// @ref IDRF_SUCCESSFULLY. <br>
                                /// Подробнее о пересечении Лимита или противоположной границы: IdRange.
                                ///
                                /// @see
                                /// IdRange::moveBorder <br>
                                /// IdRange::getIdInfo <br>
                                /// value

        unsigned    position;   ///<@brief Позиция ID относительно границ диапазона. <br>
                                /// Значение по умолчанию @ref IDRP_NOT_SET.
                                ///
                                /// **position** хранит информацию о том где располагается полученный ID
                                /// относительно указанной границы диапазона.
                                /// Полученный ID хранится в **value**. <br>
                                /// На данный момент доступны следующие флаги: @ref IdRange_Position.
                                ///
                                /// По умолчанию **position** имеет значение @ref IDRP_NOT_SET
                                /// (не путать с @ref IDRF_NOT_SET). <br>
                                /// Если полученный ID находится на границе диапазона, в **position** будет
                                /// записан @ref IDRP_AT_BORDER. <br>
                                /// Если полученный ID находится вне границ диапазона, в **position** будет
                                /// записан @ref IDRP_OUT_OF_RANGE. <br>
                                /// Если полученный ID находится в границах диапазона, в **position** будет
                                /// записан @ref IDRP_WITHIN_RANGE. <br>
                                /// Если полученный ID совпадает со Стартовым ID, в **position** будет
                                /// записан @ref IDRP_AT_START. <br>
                                /// @ref IDRP_AT_START может быть записан вместе с @ref IDRP_AT_BORDER
                                /// и @ref IDRP_WITHIN_RANGE. <br>
                                /// Подробнее о Стартовом ID: IdRange.
                                ///
                                /// @see
                                /// IdRange::moveBorder <br>
                                /// IdRange::getIdInfo <br>
                                /// value

        BorderRange border;     ///<@brief Граница диапазона, на территории которой находится
                                /// полученный ID. <br>
                                /// Значение по умолчанию BorderRange::UpperBorder.
                                ///
                                /// Полученный ID хранится в **value**.
                                ///
                                /// **border** хранит информацию о том на чьей территории
                                /// располагается полученный ID. Полученный ID хранится в **value**. <br>
                                /// Все ID больше Стартового ID находятся на территории
                                /// BorderRange::UpperBorder, он и будет записан в **border**. <br>
                                /// Все ID меньше Стартового ID находятся на территории
                                /// BorderRange::LowerBorder, он и будет записан в **border**. <br>
                                /// Стартовый ID является нейтральным. Если полученный ID совпадает
                                /// со Стартовым ID, в **border** записывается то значение @ref BorderRange
                                /// которое мы указали в IdRange::moveBorder(BorderRange, dlong) или
                                /// IdRange::getIdInfo(BorderRange, dlong) const в первом параметре.
                                ///
                                /// Например:
                                /// @code
                                /// IdRange<int> idRange;
                                /// ...
                                /// auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, -4); //idInfo.border == BorderRange::UpperBorder
                                ///
                                ///                    |<-.<-.<-.<-ub
                                ///        lb
                                /// -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
                                ///  .  .  .  .  .  .  @  .  .  .  .  .  .
                                ///
                                ///
                                /// auto idInfo = idRange.getIdInfo(BorderRange::LowerBorder, -4); //idInfo.border == BorderRange::LowerBorder
                                ///
                                ///                                ub
                                ///        lb>.->.->.->|
                                /// -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
                                ///  .  .  .  .  .  .  @  .  .  .  .  .  .
                                /// @endcode
                                ///
                                /// @ref getIdInfo вернет @ref IdInfo где в первом варианте **border**
                                /// равен BorderRange::UpperBorder, а во втором BorderRange::LowerBorder и это несмотря на то что мы
                                /// запросили один и тот же ID. <br>
                                ///
                                /// А вот в остальных случаях **border** будет корректно указывать на то
                                /// к какой территории принадлежит ID:
                                /// @code
                                /// IdRange<int> idRange;
                                /// ...
                                /// auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, -3); //idInfo.border == BorderRange::UpperBorder
                                ///
                                ///                       |<-.<-.<-ub
                                ///        lb
                                /// -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
                                ///  .  .  .  .  .  .  @  .  .  .  .  .  .
                                ///
                                ///
                                /// auto idInfo = idRange.getIdInfo(BorderRange::LowerBorder, -5); //idInfo.border == BorderRange::UpperBorder
                                ///
                                ///                                ub
                                ///        lb>.->.->.->.->|
                                /// -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
                                ///  .  .  .  .  .  .  @  .  .  .  .  .  .
                                /// @endcode
                                ///
                                /// @see
                                /// state <br>
                                /// IdRange::moveBorder <br>
                                /// IdRange::getIdInfo <br>
                                /// IdRange <br>
                                /// value

        bool        state;      ///<@brief Состояние границы, на территории которой находится полученный ID. <br>
                                /// Значение по умолчанию *false*.
                                ///
                                /// Полученный ID хранится в **value**.
                                ///
                                /// **state** хранит состояние границы диапазона указанной в **border**. <br>
                                /// Если граница выключена, в **state** записывается *false*. <br>
                                /// Если граница включена, в **state** записывается *true*.
                                ///
                                /// @see
                                /// border <br>
                                /// value

        T           value;      ///<@brief Последняя ID на которую успешно смогла переместиться граница. <br>
                                /// Значение по умолчанию 0.
                                ///
                                /// Если граница диапазона ***может*** успешно переместиться
                                /// и ей ничего не помешает, то **value** примет ожидаемое значение. <br>
                                /// Если граница диапазона не ***может*** успешно переместиться,
                                /// в **value** будет записан не ожидаемый ID, а ближайший возможный.
                                ///
                                /// Я подчеркнул слово "может" из-за того что @ref getIdInfo
                                /// не двигает границу, но работает почти так же как и @ref moveBorder
                                /// который в свою очередь уже двигает границу. <br>
                                /// Подробнее о правилах перемещения границы: IdRange.
                                ///
                                /// Пример:
                                /// @code
                                /// IdRange<int> idRange;
                                /// ...
                                /// auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, 4); //idInfo.value == 3
                                ///
                                ///                       ub>.->.xxxxxx>.x>|
                                ///        lb
                                /// -6 -5 -4 -3 -2 -1  0  1  2  3  3,5  4  5  6
                                ///  .  .  .  .  .  .  @  .  .  .  ::   .  .  .
                                ///
                                ///
                                /// auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, 4); //idInfo.value == 5
                                ///
                                ///                       ub>.->.->.->|
                                ///        lb
                                /// -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
                                ///  .  .  .  .  .  .  @  .  .  .  .  .  .
                                /// @endcode
                                ///
                                /// В первом примере Лимит установленный для BorderRange::UpperBorder на 3,5
                                /// мешает границе получить информацию о 5. <br>
                                /// Ближайшее ID к 5, информацию о котором мы можем получить это 3. Значит в **value**
                                /// будет записана 3. <br>
                                /// Во втором случае нам ничего не мешает получить информацию о 5. Значит в **value**
                                /// будет записана 5.
                                ///
                                /// @see
                                /// stepCount <br>
                                /// IdRange::moveBorder <br>
                                /// IdRange::getIdInfo

        dlong    stepCount;     ///<@brief Количество успешно сделанных шагов. <br>
                                /// Значение по умолчанию 0.
                                ///
                                /// **stepCount** повязан с **value**. **stepCount** указывает, какое
                                /// количество шагов нужно сделать границе до ID записанного в **value**. <br>
                                /// Если вернуться к примеру из описания **value**:
                                /// @code
                                /// IdRange<int> idRange;
                                /// ...
                                /// auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, 4); //idInfo.value == 3, idInfo.stepCount == 2
                                ///
                                ///                       ub>.->.xxxxxx>.x>|
                                ///        lb
                                /// -6 -5 -4 -3 -2 -1  0  1  2  3  3,5  4  5  6
                                ///  .  .  .  .  .  .  @  .  .  .  ::   .  .  .
                                ///
                                ///
                                /// auto idInfo = idRange.getIdInfo(BorderRange::UpperBorder, 4); //idInfo.value == 5, idInfo.stepCount == 4
                                ///
                                ///                       ub>.->.->.->|
                                ///        lb
                                /// -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6
                                ///  .  .  .  .  .  .  @  .  .  .  .  .  .
                                /// @endcode
                                ///
                                /// В первом случае **stepCount** будет равен 2, так как между 1 и 3 всего
                                /// 2 шага. <br>
                                /// Во втором случае **stepCount** будет равен 4, как и ожидалось
                                /// (во втором аргументе мы просим получить информацию об ID на
                                /// расстоянии 4 шагов). Между 1 и 5, всего 4 шага, потому **stepCount**
                                /// равен 4.
                                ///
                                /// @see
                                /// value <br>
                                /// IdRange::moveBorder <br>
                                /// IdRange::getIdInfo

        /**
         * @param other - копируемый объект класса.
         */
        IdInfo& operator=(const IdInfo& other) = default;
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
