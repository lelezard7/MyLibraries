#include "UniversalDefinitions.h"


template <size_t TV_PairCount, class T_Key, class T_Value>
ONF::TypePairs<TV_PairCount, T_Key, T_Value>::
TypePairs(Key key, Value value)
    : key_  (key)
    , value_(value)
{ static_assert(TV_PairCount == 1, "TV_PairCount does not match the actual number of pairs!"); }

template <size_t TV_PairCount, class T_Key, class T_Value>
void
ONF::TypePairs<TV_PairCount, T_Key, T_Value>::
setValue(Value value)
{ value_ = value; }

template <size_t TV_PairCount, class T_Key, class T_Value>
typename ONF::TypePairs<TV_PairCount, T_Key, T_Value>::Value
ONF::TypePairs<TV_PairCount, T_Key, T_Value>::
getValue() const
{ return value_; }

template <size_t TV_PairCount, class T_Key, class T_Value>
void
ONF::TypePairs<TV_PairCount, T_Key, T_Value>::
setKeyValue(Key value)
{ key_ = value; }

template <size_t TV_PairCount, class T_Key, class T_Value>
typename ONF::TypePairs<TV_PairCount, T_Key, T_Value>::Key
ONF::TypePairs<TV_PairCount, T_Key, T_Value>::
getKeyValue() const
{ return key_; }

template <size_t TV_PairCount, class T_Key, class T_Value>
template<class T, class... T_Args>
auto
ONF::TypePairs<TV_PairCount, T_Key, T_Value>::
getPairValueType(T_Args... args) const
{
    if constexpr (std::is_same_v<T, T_Key>)
        return Value(args...);
    else
        return void();
}

template <size_t TV_PairCount, class T_Key, class T_Value>
template<class T>
auto
ONF::TypePairs<TV_PairCount, T_Key, T_Value>::
getPair() const
{
    if constexpr (std::is_same_v<T, T_Key>)
        return this;
    else
        return void();
}

template <size_t TV_PairCount, class T_Key, class T_Value>
template<size_t TV_Index>
auto
ONF::TypePairs<TV_PairCount, T_Key, T_Value>::
getPairByIndex() const
{
    if constexpr (TV_Index == 0)
        return this;
    else
        return void();
}

template <size_t TV_PairCount, class T_Key, class T_Value>
void*
ONF::TypePairs<TV_PairCount, T_Key, T_Value>::
getNextPair() const
{ return nullptr; }

template <size_t TV_PairCount, class T_Key, class T_Value>
size_t
ONF::TypePairs<TV_PairCount, T_Key, T_Value>::
getPairCount() const
{ return TV_PairCount; }



template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::
TypePairs(Key key, Value value, T_OtherPairs... otherPairs)
    : nextPair_(new NextPair(otherPairs...))
    , key_     (key)
    , value_   (value) {}

template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::
~TypePairs()
{ delete nextPair_; }

template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
void
ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::
setValue(Value value)
{ value_ = value; }

template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
typename ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::Value
ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::
getValue() const
{ return value_; }

template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
void
ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::
setKeyValue(Key value)
{ key_ = value; }

template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
typename ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::Key
ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::
getKeyValue() const
{ return key_; }

template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
template<class T, class... T_Args>
auto
ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::
getPairValueType(T_Args... args) const
{
    if constexpr (std::is_same_v<T, T_Key>)
        return Value(args...);
    else
        return nextPair_->template getPairValueType<T>(args...);
}

template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
template<class T>
auto
ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::
getPair() const
{
    if constexpr (std::is_same_v<T, T_Key>)
        return this;
    else
        return nextPair_->template getPair<T>();
}

template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
template<size_t TV_Index>
auto
ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::
getPairByIndex() const
{
    if constexpr (TV_Index == 0)
        return this;
    else
        return nextPair_->template getPairByIndex<TV_Index - 1>();
}

template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
typename ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::NextPair*
ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::
getNextPair() const
{ return nextPair_; }

template <size_t TV_PairCount, class T_Key, class T_Value, class... T_OtherPairs>
size_t
ONF::TypePairs<TV_PairCount, T_Key, T_Value, T_OtherPairs...>::
getPairCount() const
{ return TV_PairCount; }



template <class... T_Pairs>
auto
ONF::makeTypePairs(T_Pairs... pairs)
{ return ONF::TypePairs<sizeof...(pairs) / 2, T_Pairs...>(std::forward<T_Pairs>(pairs)...); }
