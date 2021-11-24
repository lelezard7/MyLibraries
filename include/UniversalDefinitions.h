#ifndef UNIVERSALDEFINITIONS_H_
#define UNIVERSALDEFINITIONS_H_

#include <utility>


namespace ONF
{
    /**
     * @brief Проверяет, корректный ли тип вернул тот или иной метод класса ONF::TypePairs.
     *
     * Под корректными типами подразумеваются все типы данных кроме *void*.
     *
     * @see ONF::TypePairs
     */
    #define IsCorrectType(Obj)   (!std::is_void_v<decltype(Obj)>)


    template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
    class TypePairs;

    ///@private
    template <size_t TV_PairCount, class T_Key, class T_Value>
    class TypePairs<TV_PairCount, T_Key, T_Value>
    {
    public:
        using Key = T_Key;
        using Value = T_Value;

    private:
        Key key_;
        Value value_;

    public:
        TypePairs(Key key, Value value);
        TypePairs(const TypePairs& other) = delete;
        TypePairs(TypePairs&& other) = delete;
        virtual ~TypePairs() = default;

        void setValue(Value value);
        Value getValue() const;

        void setKeyValue(Key value);
        Key getKeyValue() const;

        template<class T, class... T_Args>
        auto getPairValueType(T_Args... args) const;

        template<class T>
        auto getPair() const;

        template<size_t TV_Index>
        auto getPairByIndex() const;

        void* getNextPair() const;
        size_t getPairCount() const;

        TypePairs& operator=(const TypePairs& other) = delete;
        TypePairs& operator=(TypePairs&& other) = delete;

    };

    /**
     * @brief Данный класс предназначен для храниния типов в формате ключ-значение.
     *
     * Создавая объект данного класса мы указываем типы данных которые он будет хранить и если
     * нужно значения по умолчанию для хранимых типов данных. <br>
     * Данный класс хранит значения в виде цепочки таких же классов, но с другими параметрами
     * шаблона. <br>
     * Т.е. если мы создадим объект класса TypePairs который должен хранить 3 пары типов данных,
     * тот объект который мы создали будет хранить первую пару ключ-значение, а так же указатель
     * на следующий объект класса TypePairs. <br>
     * Следующий объект класс будет содержать следующую пару ключ-значение и указатель на
     * следующий TypePairs. <br>
     * Эта цепочка будет строится до тех пор пока все указанные типы данных не найдут для
     * себя TypePairs. <br>
     * Для того что бы создать объект данного класса, в первый параметр шаблона нужно передать
     * количество пар которые вы планируете создать, а затем поочередно указывать пары типов
     * данных, где первый тип данных любой пары это ключ, а второй - значение. <br>
     * Затем в параметры функции необходимо передать значения по умолчанию для указанных типов. <br>
     * Указывать их нужно в том же порядке в котором были указаны хранимые тыпы данных.
     * @code
     * TypePairs<3, int, bool, float, std::string, unsigned, wchar_t> typePairs(int(), bool(true), float(), std::string("hello"), unsigned(), wchar_t(33));
     * @endcode
     * Как видно из вышепреведенного примера, получилась очень длинная запись. <br>
     * Ее можно сократить используя функцию makeTypePairs. В ее параметры можно сразу передавать
     * значения по умолчанию.
     * @code
     * auto typePairs = makeTypePairs(int(), bool(true), float(), std::string("hello"), unsigned(), wchar_t(33));
     * @endcode
     * Настало время получить его значения. <br>
     * Как было сказано выше, при создании объекта этого класса создается ряд связанных в цепочку
     * пар ключ-значение. <br>
     * Чтобы получть следующую пару надо вызвать getNextPair. У нее так же можно вызвать данный
     * метод для получения следующей пары. <br>
     * Метод getNextPair возвращает указатель на следующий объект класса TypePairs всегда, кроме
     * случая, когда он вызывается из последней пары цепочки. <br>
     * В последней паре, метод getNextPair имеет тип возращаемого значения *void\** и всегда
     * возвращает *nullptr*.
     * @code
     * auto typePairs = makeTypePairs(int(), bool(true), float(), std::string("hello"), unsigned(), wchar_t(33));
     *
     * //1 пара     2 пара         3 пара         void*
     * typePairs.getNextPair()->getNextPair()->getNextPair();
     * @endcode
     * Но иногда итерироваться таким образом может быть очень неудобно. В таком случае можно
     * использовать getPair или getPairByIndex. <br>
     * Метод getPair ищет пару с ключем указанного типа. Значение ключа никак не влияет на
     * результаты поиска, только его тип данных. <br>
     * Метод getPairByIndex возвращает пару находящуюся под указанным индексом.
     * @code
     * auto typePairs = makeTypePairs(int(), bool(true), float(), std::string("hello"), unsigned(), wchar_t(33));
     *
     * //2 пара
     * typePairs.getPair<float>();
     *
     * //3 пара
     * typePairs.getPairByIndex<2>();
     * @endcode
     */
    template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
    class TypePairs
    {
    public:
        using Key = T_Key;
        using Value = T_Value;
        using NextPair = TypePairs<TV_PairCount - 1, T_OtherPairs...>;

    private:
        NextPair* const nextPair_;
        Key key_;
        Value value_;

    public:
        TypePairs(Key key, Value value, T_OtherPairs... otherPairs);
        TypePairs(const TypePairs& other) = delete;
        TypePairs(TypePairs&& other) = delete;
        virtual ~TypePairs();

        void setValue(Value value);
        Value getValue() const;

        void setKeyValue(Key value);
        Key getKeyValue() const;

        template<class T, class... T_Args>
        auto getPairValueType(T_Args... args) const;

        template<class T>
        auto getPair() const;

        template<size_t TV_Index>
        auto getPairByIndex() const;

        NextPair* getNextPair() const;
        size_t getPairCount() const;

        TypePairs& operator=(const TypePairs& other) = delete;
        TypePairs& operator=(TypePairs&& other) = delete;

    };


    template <class... T_Pairs>
    auto makeTypePairs(T_Pairs... pairs);


    #define MakeUStringFromChar()   \
        ONF::makeTypePairs(char(), std::string(), wchar_t(), std::wstring())
    #define UStringFromChar(Key, Args...)   \
        MakeUStringFromChar().getPairValueType<Key>(Args)

    #define MakeURegexFromString()   \
        ONF::makeTypePairs(std::string(), std::regex(), std::wstring(), std::wregex())
    #define URegexFromString(Key, Args...)   \
        MakeURegexFromString().getPairValueType<Key>(Args)
}

#include "TypePairs.inl"

#endif
