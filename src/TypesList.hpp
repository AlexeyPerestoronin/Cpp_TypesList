#ifndef __TYPES_LIST__
#define __TYPES_LIST__

#include <stdint.h>
#include <type_traits>

#define TYPE_INFO(name_value, description_value)          \
    constexpr static const char* NameOfType = name_value; \
    constexpr static const char* DescriptionOfType = description_value;

// TL - Types Lists
namespace TL {
#pragma region Always(True | False)
    // SECTION: Always(True|False)
    // brief: returns boolean (true/false) regardless of type
    // example 1: static_assert(AlwaysFalse_R<TypesList_t>, "message that will be printing always but target compiling expression must be compiled");

    template<class ArbitraryType, uint8_t arbitrary_index>
    struct AlwaysTrue {
        constexpr static bool Result = std::is_trivial_v<ArbitraryType> || arbitrary_index || true;
    };

    template<class ArbitraryType, uint8_t arbitrary_index>
    constexpr bool AlwaysTrue_R = AlwaysTrue<ArbitraryType, arbitrary_index>::Result;

    template<class ArbitraryType>
    constexpr bool AlwaysTrue_tR = AlwaysTrue_R<ArbitraryType, 0>;

    template<class ArbitraryType>
    constexpr bool AlwaysFalse_tR = !AlwaysTrue_tR<ArbitraryType>;

    template<uint8_t arbitrary_index>
    constexpr bool AlwaysTrue_iR = AlwaysTrue_R<bool, arbitrary_index>;

    template<uint8_t arbitrary_index>
    constexpr bool AlwaysFalse_iR = !AlwaysTrue_iR<arbitrary_index>;
#pragma endregion

#pragma region TypeInfo
    // SECTION: TypeInfo
    // brief: if Type is compatibility - provides information about type; compilation error - vise versa
    // note: for convenient of applying use it via TYPE_INFO-define

    template<class Type>
    struct TypeInfo {
        constexpr static const char* name = Type::NameOfType;
        constexpr static const char* description = Type::DescriptionOfType;
    };

    // NOTE: need determine TypeInfo instance for C++ common types below

    template<>
    struct TypeInfo<float> {
        constexpr static const char* name = "float";
        constexpr static const char* description = "standart type float";
    };

    template<>
    struct TypeInfo<double> {
        constexpr static const char* name = "double";
        constexpr static const char* description = "standart type double";
    };

    template<>
    struct TypeInfo<bool> {
        constexpr static const char* name = "bool";
        constexpr static const char* description = "standart type bool";
    };

    template<>
    struct TypeInfo<uint8_t> {
        constexpr static const char* name = "uint8_t";
        constexpr static const char* description = "8-bit size unsigned integer STL-type";
    };

    template<>
    struct TypeInfo<uint16_t> {
        constexpr static const char* name = "uint16_t";
        constexpr static const char* description = "16-bit size unsigned integer STL-type";
    };

    template<>
    struct TypeInfo<uint32_t> {
        constexpr static const char* name = "uint32_t";
        constexpr static const char* description = "32-bit size unsigned integer STL-type";
    };

    template<>
    struct TypeInfo<uint64_t> {
        constexpr static const char* name = "uint64_t";
        constexpr static const char* description = "64-bit size unsigned integer STL-type";
    };

    template<>
    struct TypeInfo<int8_t> {
        constexpr static const char* name = "int8_t";
        constexpr static const char* description = "8-bit size integer STL-type";
    };

    template<>
    struct TypeInfo<int16_t> {
        constexpr static const char* name = "int16_t";
        constexpr static const char* description = "16-bit size integer STL-type";
    };

    template<>
    struct TypeInfo<int32_t> {
        constexpr static const char* name = "int32_t";
        constexpr static const char* description = "32-bit size integer STL-type";
    };

    template<>
    struct TypeInfo<int64_t> {
        constexpr static const char* name = "int64_t";
        constexpr static const char* description = "64-bit size integer STL-type";
    };

    template<>
    struct TypeInfo<char> {
        constexpr static const char* name = "char";
        constexpr static const char* description = "system-dependent-size standart one-symbol-type";
    };

    template<>
    struct TypeInfo<char16_t> {
        constexpr static const char* name = "char16_t";
        constexpr static const char* description = "16-bit size STL-one-symbol-type";
    };

    template<>
    struct TypeInfo<char32_t> {
        constexpr static const char* name = "char32_t";
        constexpr static const char* description = "16-bit size STL-one-symbol-type";
    };
#pragma endregion

#pragma region TypesList
    // SECTION: TypesList
    // WARNING: do not use it directly
    // brief: base struct of TL-logic

    struct NullType {
        TYPE_INFO("NullType", "do not use it directly: only for TypesList-struct");

        constexpr static uint8_t size = 0;
    };

    template<class H, class T>
    struct TypesList {
        TYPE_INFO("TypesList", "do not create it directly: use it via CreateTypesList");

        using Head = H;
        using Tail = T;
        using Result = TypesList<Head, Tail>;
        constexpr static uint8_t size = 1 + Tail::size;
    };

    template<class Head, class Tail>
    using TypesList_R = typename TypesList<Head, Tail>::Result;
#pragma endregion

#pragma region CreateTypesList
    // SECTION: CreateTypesList
    // brief: creates arbitrary length list of types
    // Result: list of target types
    // example 1: using UINTs_t = TL::CreateTypesList_R<uint8_t, uint16_t, uint32_t, uint64_t>; // --> [uint8_t, uint16_t, uint32_t, uint64_t]
    // example 2: using INTs_t = TL::CreateTypesList_R<int8_t, int16_t, int32_t, int64_t>; // --> [int8_t, int16_t, int32_t, int64_t]
    // example 3: using ALL_INTs_t TL::TL::CreateTypesList_R<INTs_t, UINTs_t>; // --> [int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t]

#define EXPLICIT_TYPE_INFO TYPE_INFO("CreateTypesList", "creates arbitrary length list of types");

    template<class Type, class... OtherTypes>
    struct CreateTypesList {
        EXPLICIT_TYPE_INFO
        using Result = TypesList_R<Type, typename CreateTypesList<OtherTypes...>::Result>;
    };

    template<class Head, class Tail, class... OtherTypes>
    struct CreateTypesList<TypesList<Head, Tail>, OtherTypes...> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList_R<Head, typename CreateTypesList<Tail, OtherTypes...>::Result>;
    };

    template<class Head, class... OtherTypes>
    struct CreateTypesList<TypesList<Head, NullType>, OtherTypes...> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList_R<Head, typename CreateTypesList<OtherTypes...>::Result>;
    };

    template<class Head, class Tail>
    struct CreateTypesList<TypesList<Head, Tail>> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList_R<Head, Tail>;
    };

    template<class Head>
    struct CreateTypesList<TypesList<Head, NullType>> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList_R<Head, NullType>;
    };

    template<class Type>
    struct CreateTypesList<Type> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList_R<Type, NullType>;
    };

    template<>
    struct CreateTypesList<NullType> {
        EXPLICIT_TYPE_INFO
        using Result = NullType;
    };

#undef EXPLICIT_TYPE_INFO
    template<class Type, class... OtherTypes>
    using CreateTypesList_R = typename CreateTypesList<Type, OtherTypes...>::Result;
#pragma endregion

#pragma region GetTypeByIndex
    // SECTION: GetTypeByIndex
    // brief: get Type from TypesList by index
    // Result: Type by index from TypesList - if exist; compilation error - vise versa
    // example 1: GetTypeByIndex<UINTs_t, 0>::Result; // -> uint8_t
    // example 2: GetTypeByIndex<UINTs_t, 1>::Result; // -> uint16_t
    // example 3: GetTypeByIndex<UINTs_t, 2>::Result; // -> uint32_t
    // example 4: GetTypeByIndex<UINTs_t, 3>::Result; // -> uint64_t
    // example 6: GetTypeByIndex<UINTs_t, 4>::Result; // compilation error

#define EXPLICIT_TYPE_INFO TYPE_INFO("GetTypeByIndex", "get Type from TypesList by index: use only with TypesList-struct");

    template<class TypesList_t, uint8_t index>
    struct GetTypeByIndex {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use GetTypeByIndex with not TypesList-struct");
    };

    template<uint8_t index>
    struct GetTypeByIndex<NullType, index> {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_iR<index>, "index out of range");
    };

    template<class Head, class Tail, uint8_t index>
    struct GetTypeByIndex<TypesList<Head, Tail>, index> {
        EXPLICIT_TYPE_INFO
        using Result = typename GetTypeByIndex<Tail, index - 1>::Result;
    };

    template<class Head, class Tail>
    struct GetTypeByIndex<TypesList<Head, Tail>, 0> {
        EXPLICIT_TYPE_INFO
        using Result = Head;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList, uint8_t index>
    using GetTypeByIndex_R = typename GetTypeByIndex<TypesList, index>::Result;
#pragma endregion

#pragma region GetIndexByType
    // SECTION: GetIndexByType
    // brief: get index inside TypesList by which target Type is placed
    // Result: index by which the Type is placed inside the TypesList
    // example 1: TL::GetIndexByType<UINTs_t, uint8_t>::Result // -> 0
    // example 2: TL::GetIndexByType<UINTs_t, uint16_t>::Result // -> 1
    // example 3: TL::GetIndexByType<UINTs_t, uint32_t>::Result // -> 2
    // example 4: TL::GetIndexByType<UINTs_t, uint64_t>::Result // -> 3
    // example 5: TL::GetIndexByType<UINTs_t, int8_t>::Result // compilation error

#define EXPLICIT_TYPE_INFO TYPE_INFO("GetIndexByType", "get index inside TypesList by which target Type is placed: use only with TypesList-struct");

    template<class TypesList_t, class Type>
    struct GetIndexByType {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use GetIndexByType with not TypesList-struct");
    };

    template<class Type>
    struct GetIndexByType<NullType, Type> {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<Type>, "target type is not existant inside TypesList");
    };

    template<class Head, class Tail, class Type>
    struct GetIndexByType<TypesList<Head, Tail>, Type> {
        EXPLICIT_TYPE_INFO
        constexpr static uint8_t Result = 1 + GetIndexByType<Tail, Type>::Result;
    };

    template<class Head, class Tail>
    struct GetIndexByType<TypesList<Head, Tail>, Head> {
        EXPLICIT_TYPE_INFO
        constexpr static uint8_t Result = 0;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList, class Type>
    constexpr uint8_t GetIndexByType_R = GetIndexByType<TypesList, Type>::Result;
#pragma endregion

#pragma region IsInList
    // SECTION: IsInList
    // brief: check if Type is in TypesList
    // Result: true - if Type is into TypesList; false - vise versa
    // example 1: TL::IsInList<UINTs_t, uint8_t>::Result // -> true
    // example 2: TL::IsInList<UINTs_t, int8_t>::Result // -> false
    // example 3: TL::IsInList<UINTs_t, uint16_t>::Result // -> true
    // example 4: TL::IsInList<UINTs_t, int16_t>::Result // -> false
    // example 5: TL::IsInList<UINTs_t, uint32_t>::Result // -> true
    // example 6: TL::IsInList<UINTs_t, int32_t>::Result // -> false
    // example 7: TL::IsInList<UINTs_t, uint64_t>::Result // -> true
    // example 8: TL::IsInList<UINTs_t, int64_t>::Result // -> false

#define EXPLICIT_TYPE_INFO TYPE_INFO("IsInList", "check if Type is in TypesList: use only with TypesList-struct");

    template<class TypesList_t, class Type>
    struct IsInList {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use IsInList with not TypesList-struct");
    };

    template<class Type>
    struct IsInList<NullType, Type> {
        EXPLICIT_TYPE_INFO
        constexpr static bool Result = false;
    };

    template<class Head, class Tail, class Type>
    struct IsInList<TypesList<Head, Tail>, Type> {
        EXPLICIT_TYPE_INFO
        constexpr static bool Result = IsInList<Tail, Type>::Result;
    };

    template<class Head, class Tail>
    struct IsInList<TypesList<Head, Tail>, Head> {
        EXPLICIT_TYPE_INFO
        constexpr static bool Result = true;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList, class Type>
    constexpr bool IsInList_R = IsInList<TypesList, Type>::Result;
#pragma endregion

#pragma region AppendBack
    // SECTION: AppendBack
    // brief: appends one type or arbitrary length types list at the end of the target TypesList
    // Result: new list of types consisting of all types from the target TypesList and additional type(or types) from back
    // example 1: TL::AppendBack<TL::CreateTypesList<int8_t>::Result, int16_t>::Result // -> [int8_t, int16_t]
    // example 2: TL::AppendBack<INTs_t, char>::Result // -> [int8_t, int16_t, int32_t, int64_t, char]
    // example 3: TL::AppendBack<INTs_t, UINTs_t>::Result // -> [int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t]

#define EXPLICIT_TYPE_INFO \
    TYPE_INFO("AppendBack", "appends one type or arbitrary length types list at the end of the target TypesList: use only with TypesList-struct");

    template<class TypesList_t, class Type>
    struct AppendBack {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use AppendBack with not TypesList-struct");
    };

    template<class Head, class Tail, class Type>
    struct AppendBack<TypesList<Head, Tail>, Type> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Head, typename AppendBack<Tail, Type>::Result>;
    };

    template<class Head, class Type>
    struct AppendBack<TypesList<Head, NullType>, Type> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Head, TypesList<Type, NullType>>;
    };

    template<class Head1, class Head2, class Tail2>
    struct AppendBack<TypesList<Head1, NullType>, TypesList<Head2, Tail2>> {
        EXPLICIT_TYPE_INFO
        using Result = typename AppendBack<TypesList<Head1, TypesList<Head2, NullType>>, Tail2>::Result;
    };

    template<class Head1, class Head2>
    struct AppendBack<TypesList<Head1, NullType>, TypesList<Head2, NullType>> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Head1, TypesList<Head2, NullType>>;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList, class Type>
    using AppendBack_R = typename AppendBack<TypesList, Type>::Result;
#pragma endregion

#pragma region AppendFront
    // SECTION: AppendFront
    // brief: appends one type or arbitrary length types list at the end of the target TypesList to front
    // Result: new list of types consisting of all types from the target TypesList and additional type(or types) from front
    // example 1: TL::AppendFront<TL::CreateTypesList<int8_t>::Result, int16_t>::Result // -> [int16_t, int8_t]
    // example 2: TL::AppendFront<INTs_t, char>::Result // -> [char, int8_t, int16_t, int32_t, int64_t]
    // example 3: TL::AppendFront<INTs_t, UINTs_t>::Result // -> [uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t, int32_t, int64_t]

#define EXPLICIT_TYPE_INFO \
    TYPE_INFO(             \
        "AppendFront", "appends one type or arbitrary length types list at the beginning of the target TypesList to front: use only with TypesList-struct");

    template<class TypesList_t, class Type>
    struct AppendFront {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use AppendFront with not TypesList-struct");
    };

    template<class Head, class Tail, class Type>
    struct AppendFront<TypesList<Head, Tail>, Type> {
        EXPLICIT_TYPE_INFO
        using Result = AppendBack_R<CreateTypesList_R<Type>, TypesList<Head, Tail>>;
    };

    template<class Head1, class Tail1, class Head2, class Tail2>
    struct AppendFront<TypesList<Head1, Tail1>, TypesList<Head2, Tail2>> {
        EXPLICIT_TYPE_INFO
        using Result = AppendBack_R<TypesList<Head2, Tail2>, TypesList<Head1, Tail1>>;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList, class Type>
    using AppendFront_R = typename AppendFront<TypesList, Type>::Result;
#pragma endregion

#pragma region InsertByIndex
    // SECTION: InsertByIndex
    // brief: insert one type or arbitrary length types list at the target TypesList by index
    // Result: new list of types consisting of all types from the target TypesList and additional type(or types) inserted by index
    // example 1: TL::InsertByIndex_R<TL::CreateTypesList_R<int8_t>, int16_t, 0> // -> [int16_t, int8_t]
    // example 2: TL::InsertByIndex_R<TL::CreateTypesList_R<int8_t>, int16_t, 0> // -> [int8_t, int16_t]
    // example 3: TL::InsertByIndex_R<INTs_t, UINTs_t, 0>::Result // -> [uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t, int32_t, int64_t]
    // example 3: TL::InsertByIndex_R<INTs_t, UINTs_t, 1>::Result // -> [int8_t, uint8_t, uint16_t, uint32_t, uint64_t, int16_t, int32_t, int64_t]
    // example 3: TL::InsertByIndex_R<INTs_t, UINTs_t, 2>::Result // -> [int8_t, int16_t, uint8_t, uint16_t, uint32_t, uint64_t, int32_t, int64_t]
    // example 3: TL::InsertByIndex_R<INTs_t, UINTs_t, 3>::Result // -> [int8_t, int16_t, int32_t, uint8_t, uint16_t, uint32_t, uint64_t, int64_t]
    // example 3: TL::InsertByIndex_R<INTs_t, UINTs_t, 4>::Result // -> [int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t]

#define EXPLICIT_TYPE_INFO \
    TYPE_INFO("InsertByIndex", "insert one type or arbitrary length types list at the target TypesList by index: use only with TypesList-struct");

    template<class TypesList_t, class Type, uint8_t index>
    struct InsertByIndex {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use InsertByIndex with not TypesList-struct");
    };

    template<class Type, uint8_t index>
    struct InsertByIndex<NullType, Type, index> {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_iR<index>, "forbidden to use InsertByIndex with not TypesList-struct");
    };

    template<class Head, class Tail, class Type, uint8_t index>
    struct InsertByIndex<TypesList<Head, Tail>, Type, index> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Head, typename InsertByIndex<Tail, Type, index - 1>::Result>;
    };

    template<class Head, class Tail, class Type>
    struct InsertByIndex<TypesList<Head, Tail>, Type, 0> {
        EXPLICIT_TYPE_INFO
        using Result = AppendFront_R<TypesList<Head, Tail>, Type>;
    };

    template<class Head, class Tail>
    struct InsertByIndex<NullType, TypesList<Head, Tail>, 0> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Head, Tail>;
    };

    template<class Type>
    struct InsertByIndex<NullType, Type, 0> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Type, NullType>;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList, class Type, uint8_t index>
    using InsertByIndex_R = typename InsertByIndex<TypesList, Type, index>::Result;
#pragma endregion

#pragma region RemoveBack
    // SECTION: RemoveBack
    // brief: removes last type from target TypesList
    // example 1: RemoveBack_R<INTs_t> // --> [int8_t, int16_t, int32_t]
    // example 2: RemoveBack_R<RemoveBack_R<INTs_t>> // --> [int8_t, int16_t]
    // example 3: RemoveBack_R<RemoveBack_R<RemoveBack_R<INTs_t>>> // --> [int8_t]
    // example 4: RemoveBack_R<RemoveBack_R<RemoveBack_R<RemoveBack_R<INTs_t>>>> // --> []
    // example 5: RemoveBack_R<RemoveBack_R<RemoveBack_R<RemoveBack_R<RemoveBack_R<INTs_t>>>>> // --> compilation error

#define EXPLICIT_TYPE_INFO TYPE_INFO("RemoveBack", "removes last type from target TypesList: use only with TypesList-struct");

    template<class TypesList_t>
    struct RemoveBack {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use RemoveBack with not TypesList-struct");
    };

    template<class Head, class Tail>
    struct RemoveBack<TypesList<Head, Tail>> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Head, typename RemoveBack<Tail>::Result>;
    };

    template<class Head>
    struct RemoveBack<TypesList<Head, NullType>> {
        EXPLICIT_TYPE_INFO
        using Result = NullType;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t>
    using RemoveBack_R = typename RemoveBack<TypesList_t>::Result;
#pragma endregion

#pragma region RemoveFront
    // SECTION: RemoveFront
    // brief: removes first type from target TypesList
    // example 1: RemoveFront_R<INTs_t> // --> [int16_t, int32_t, int64_t]
    // example 2: RemoveFront_R<RemoveFront_R<INTs_t>> // --> [int32_t, int64_t]
    // example 3: RemoveFront_R<RemoveFront_R<RemoveFront_R<INTs_t>>> // --> [int64_t]
    // example 4: RemoveFront_R<RemoveFront_R<RemoveFront_R<RemoveFront_R<INTs_t>>>> // --> []
    // example 5: RemoveFront_R<RemoveFront_R<RemoveFront_R<RemoveFront_R<RemoveFront_R<INTs_t>>>>> // --> compilation error

#define EXPLICIT_TYPE_INFO TYPE_INFO("RemoveFront", "removes first type from target TypesList: use only with TypesList-struct");

    template<class TypesList_t>
    struct RemoveFront {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use RemoveFront with not TypesList-struct");
    };

    template<class Head, class Tail>
    struct RemoveFront<TypesList<Head, Tail>> {
        EXPLICIT_TYPE_INFO
        using Result = Tail;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t>
    using RemoveFront_R = typename RemoveFront<TypesList_t>::Result;
#pragma endregion

#pragma region RemoveByIndex
    // SECTION: RemoveByIndex
    // brief: removes type from target TypesList by index
    // example 1: RemoveByIndex<INTs_t, 0> // --> [int16_t, int32_t, int64_t]
    // example 2: RemoveByIndex<INTs_t, 1> // --> [int8_t, int32_t, int64_t]
    // example 3: RemoveByIndex<INTs_t, 2> // --> [int8_t, int16_t, int64_t]
    // example 4: RemoveByIndex<INTs_t, 3> // --> [int8_t, int16_t, int32_t]

#define EXPLICIT_TYPE_INFO TYPE_INFO("RemoveByIndex", "removes type from target TypesList by index: use only with TypesList-struct");

    template<class TypesList_t, uint8_t index>
    struct RemoveByIndex {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use RemoveByIndex with not TypesList-struct");
    };

    template<uint8_t index>
    struct RemoveByIndex<NullType, index> {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_iR<index>, "index of TypesList out of range");
    };

    template<class Head, class Tail, uint8_t index>
    struct RemoveByIndex<TypesList<Head, Tail>, index> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Head, typename RemoveByIndex<Tail, index - 1>::Result>;
    };

    template<class Head, class Tail>
    struct RemoveByIndex<TypesList<Head, Tail>, 0> {
        EXPLICIT_TYPE_INFO
        using Result = Tail;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t, uint8_t index>
    using RemoveByIndex_R = typename RemoveByIndex<TypesList_t, index>::Result;
#pragma endregion

#pragma region RemoveFromSize
    // SECTION: RemoveFromSize
    // brief: removes the types since from-index to from+size-index from target TypesList
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 0, 1> // --> [uint16_t, uint32_t, uint64_t, int8_t, int16_t, int32_t, int64_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 1, 1> // --> [uint8_t, uint32_t, uint64_t, int8_t, int16_t, int32_t, int64_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 2, 1> // --> [uint8_t, uint16_t, uint64_t, int8_t, int16_t, int32_t, int64_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 3, 1> // --> [uint8_t, uint16_t, uint32_t, int8_t, int16_t, int32_t, int64_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 4, 1> // --> [uint8_t, uint16_t, uint32_t, uint64_t, int16_t, int32_t, int64_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 5, 1> // --> [uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int32_t, int64_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 6, 1> // --> [uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t, int64_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 7, 1> // --> [uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t, int32_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 0, 4> // --> [int8_t, int16_t, int32_t, int64_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 1, 4> // --> [uint8_t, int16_t, int32_t, int64_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 2, 4> // --> [uint8_t, uint16_t, int32_t, int64_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 3, 4> // --> [uint8_t, uint16_t, uint32_t, int64_t]
    // example 1: TL::RemoveFromSize_R<ALL_INTs_t, 4, 4> // --> [uint8_t, uint16_t, uint32_t, uint64_t]

    template<class TypesList_t, uint8_t from, uint8_t size>
    struct RemoveFromSize {
        TYPE_INFO("RemoveFromSize", "removes the types since from-index to from+size-index from target TypesList: use only with TypesList-struct");

        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use RemoveFromSize with not TypesList-struct");
    };

    template<uint8_t from, uint8_t size>
    struct RemoveFromSize<NullType, from, size> {
        TYPE_INFO("RemoveFromSize", "removes the types since from-index to from+size-index from target TypesList: use only with TypesList-struct");

        static_assert(from == 0, "from-index of TypesList out of range");
        static_assert(size == 0, "size-value is more than available size of target TypesList");
    };

    template<class Head, class Tail, uint8_t from, uint8_t size>
    struct RemoveFromSize<TypesList<Head, Tail>, from, size> {
        TYPE_INFO("RemoveFromSize", "removes the types since from-index to from+size-index from target TypesList: use only with TypesList-struct");

        static_assert(size > 0, "size-value must be greater 0");
        using Result = TypesList<Head, typename RemoveFromSize<Tail, from - 1, size>::Result>;
    };

    template<class Head, class Tail, uint8_t size>
    struct RemoveFromSize<TypesList<Head, Tail>, 0, size> {
        TYPE_INFO("RemoveFromSize", "removes the types since from-index to from+size-index from target TypesList: use only with TypesList-struct");

        using Result = typename RemoveFromSize<Tail, 0, size - 1>::Result;
    };

    template<class Head, class Tail>
    struct RemoveFromSize<TypesList<Head, Tail>, 0, 0> {
        TYPE_INFO("RemoveFromSize", "removes the types since from-index to from+size-index from target TypesList: use only with TypesList-struct");

        using Result = TypesList<Head, typename RemoveFromSize<Tail, 0, 0>::Result>;
    };

    template<>
    struct RemoveFromSize<NullType, 0, 0> {
        TYPE_INFO("RemoveFromSize", "removes the types since from-index to from+size-index from target TypesList: use only with TypesList-struct");

        using Result = NullType;
    };

    template<class TypesList_t, uint8_t from, uint8_t size>
    using RemoveFromSize_R = typename RemoveFromSize<TypesList_t, from, size>::Result;
#pragma endregion

#pragma region CutFromSize
    // SECTION: CutFromSize
    // brief: cuts out the types since from-index to from+size-index from target TypesList
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 0, 1> // --> [uint8_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 1, 1> // --> [uint16_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 2, 1> // --> [uint32_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 3, 1> // --> [uint64_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 4, 1> // --> [int8_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 5, 1> // --> [int16_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 6, 1> // --> [int32_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 7, 1> // --> [int64_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 0, 4> // --> [uint8_t, uint16_t, uint32_t, uint64_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 1, 4> // --> [uint16_t, uint32_t, uint64_t, int8_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 2, 4> // --> [uint32_t, uint64_t, int8_t, int16_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 3, 4> // --> [uint64_t, int8_t, int16_t, int32_t]
    // example 1: TL::CutFromSize_R<ALL_INTs_t, 4, 4> // --> [int8_t, int16_t, int32_t, int64_t]

#define EXPLICIT_TYPE_INFO \
    TYPE_INFO("CutFromSize", "cuts out the types since from-index to from+size-index from target TypesList: use only with TypesList-struct");

    template<class TypesList_t, uint8_t from, uint8_t size>
    struct CutFromSize {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use CutFromSize with not TypesList-struct");
    };

    template<uint8_t from, uint8_t size>
    struct CutFromSize<NullType, from, size> {
        EXPLICIT_TYPE_INFO
        static_assert(from == 0, "from-index of TypesList out of range");
        static_assert(size == 0, "size-value is more than available size of target TypesList");
    };

    template<class Head, class Tail, uint8_t from, uint8_t size>
    struct CutFromSize<TypesList<Head, Tail>, from, size> {
        EXPLICIT_TYPE_INFO
        static_assert(size > 0, "size-value must be greater 0");
        using Result = typename CutFromSize<Tail, from - 1, size>::Result;
    };

    template<class Head, class Tail, uint8_t size>
    struct CutFromSize<TypesList<Head, Tail>, 0, size> {
        EXPLICIT_TYPE_INFO
        static_assert(size > 0, "size-value must be greater 0");
        using Result = TypesList<Head, typename CutFromSize<Tail, 0, size - 1>::Result>;
    };

    template<class Head, class Tail>
    struct CutFromSize<TypesList<Head, Tail>, 0, 1> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Head, NullType>;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t, uint8_t from, uint8_t size>
    using CutFromSize_R = typename CutFromSize<TypesList_t, from, size>::Result;
#pragma endregion

#pragma region Count
    // SECTION Count
    // brief: counts the quantity of entries of the Type (or Types) in target TypesList
    // note 1: using RANDOM_TYPE1s_t = TL::CreateTypesList_R<int, int, int, int>;
    // note 2: using RANDOM_TYPE2s_t = TL::CreateTypesList_R<int, int, bool, bool, char, char, float, float>;
    // note 3: using RANDOM_TYPE3s_t = TL::CreateTypesList_R<int, bool, char, float, int, bool, char, float>;
    // note 4: using RANDOM_TYPE4s_t = TL::CreateTypesList_R<int, int, int, char, char, bool, bool, int, float, bool>;
    // example 1: TL::Count_R<RANDOM_TYPE1s_t, int>; // --> 4
    // example 2: TL::Count_R<RANDOM_TYPE2s_t, int>; // --> 2
    // example 3: TL::Count_R<RANDOM_TYPE3s_t, int>; // --> 2
    // example 4: TL::Count_R<RANDOM_TYPE4s_t, int>; // --> 4
    // example 5: TL::Count_R<RANDOM_TYPE1s_t, int, bool, char, float>; // --> RANDOM_TYPE1s_t::size;
    // example 6: TL::Count_R<RANDOM_TYPE2s_t, int, bool, char, float>; // --> RANDOM_TYPE2s_t::size;
    // example 7: TL::Count_R<RANDOM_TYPE3s_t, int, bool, char, float>; // --> RANDOM_TYPE3s_t::size;
    // example 8: TL::Count_R<RANDOM_TYPE4s_t, int, bool, char, float>; // --> RANDOM_TYPE4s_t::size;

#define EXPLICIT_TYPE_INFO TYPE_INFO("Count", "counts the quantity of entries of the Type in target TypesList");

    template<class TypesList_t, class Type, class... OtherTypes>
    struct Count {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use Count with not TypesList-struct");
    };

    template<class Head, class Tail, class Type, class... OtherTypes>
    struct Count<TypesList<Head, Tail>, Type, OtherTypes...> {
        EXPLICIT_TYPE_INFO
        constexpr static uint8_t Result = Count<TypesList<Head, Tail>, Type>::Result + Count<TypesList<Head, Tail>, OtherTypes...>::Result;
    };

    template<class Head, class Tail, class Type>
    struct Count<TypesList<Head, Tail>, Type> {
        EXPLICIT_TYPE_INFO
        constexpr static uint8_t Result = Count<Tail, Type>::Result;
    };

    template<class Head, class Tail>
    struct Count<TypesList<Head, Tail>, Head> {
        EXPLICIT_TYPE_INFO
        constexpr static uint8_t Result = 1 + Count<Tail, Head>::Result;
    };

    template<class Head, class Type>
    struct Count<TypesList<Head, NullType>, Type> {
        EXPLICIT_TYPE_INFO
        constexpr static uint8_t Result = 0;
    };

    template<class Head>
    struct Count<TypesList<Head, NullType>, Head> {
        EXPLICIT_TYPE_INFO
        constexpr static uint8_t Result = 1;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t, class Type, class... OtherTypes>
    constexpr uint8_t Count_R = Count<TypesList_t, Type, OtherTypes...>::Result;
#pragma endregion

#pragma region Remove
    // SECTION: Remove
    // brief: removes the Type from target TypesList, leave only a given quantity of occurrences
    // note 4: using RANDOM_TYPE1s_t = TL::CreateTypesList_R<char, int, int, char, char, bool, bool, int, float, bool>;
    // example 1: Remove_R<RANDOM_TYPE1s_t, int, 0>; // --> [char, char, char, bool, bool, float, bool]
    // example 1: Remove_R<RANDOM_TYPE1s_t, int, 1>; // --> [char, int, char, char, bool, bool, float, bool]
    // example 1: Remove_R<RANDOM_TYPE1s_t, int, 2>; // --> [char, int, int, char, char, bool, bool, float, bool]
    // example 1: Remove_R<RANDOM_TYPE1s_t, int, 3>; // --> [char, int, int, char, char, bool, bool, int, float, bool]

#define EXPLICIT_TYPE_INFO TYPE_INFO("Remove", "removes the Type from target TypesList, leave only a given quantity of occurrences");

    template<class TypesList_t, class Type, uint8_t quantity>
    struct Remove {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use Remove with not TypesList-struct");
    };

    template<class Head, class Tail, class Type, uint8_t quantity>
    struct Remove<TypesList<Head, Tail>, Type, quantity> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Head, typename Remove<Tail, Type, quantity>::Result>;
    };

    template<class Head, class Tail, uint8_t quantity>
    struct Remove<TypesList<Head, Tail>, Head, quantity> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Head, typename Remove<Tail, Head, quantity - 1>::Result>;
    };

    template<class Head, class Tail>
    struct Remove<TypesList<Head, Tail>, Head, 0> {
        EXPLICIT_TYPE_INFO
        using Result = typename Remove<Tail, Head, 0>::Result;
    };

    template<class Type, uint8_t quantity>
    struct Remove<NullType, Type, quantity> {
        EXPLICIT_TYPE_INFO
        using Result = NullType;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t, class Type, uint8_t quantity>
    using Remove_R = typename Remove<TypesList_t, Type, quantity>::Result;
#pragma endregion

#pragma region RemoveAll
    // SECTION: RemoveAll
    // brief: removes all occurrences of the Type (or Types) from target TypesList
    // note 1: using RANDOM_TYPE1s_t = TL::CreateTypesList_R<char, int, int, char, char, bool, bool, int, float, bool>;
    // example 1: TL::RemoveAll_R<RANDOM_TYPE1s_t, int>; // --> [char, char, char, bool, bool, float, bool]
    // example 2: TL::RemoveAll_R<RANDOM_TYPE1s_t, int, char>; // --> [bool, bool, float, bool]
    // example 2: TL::RemoveAll_R<RANDOM_TYPE1s_t, int, char, bool>; // --> [float]
    // example 2: TL::RemoveAll_R<RANDOM_TYPE1s_t, int, char, bool, float>; // --> NullType

#define EXPLICIT_TYPE_INFO TYPE_INFO("RemoveAll", "removes all occurrences of the Type (or Types) from target TypesList");

    template<class TypesList_t, class Type, class... OtherTypes>
    struct RemoveAll {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use RemoveAll with not TypesList-struct");
    };

    template<class Head, class Tail, class Type, class... OtherTypes>
    struct RemoveAll<TypesList<Head, Tail>, Type, OtherTypes...> {
        EXPLICIT_TYPE_INFO
        using Result = typename RemoveAll<Remove_R<TypesList<Head, Tail>, Type, 0>, OtherTypes...>::Result;
    };

    template<class Head, class Tail, class Type>
    struct RemoveAll<TypesList<Head, Tail>, Type> {
        EXPLICIT_TYPE_INFO
        using Result = Remove_R<TypesList<Head, Tail>, Type, 0>;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t, class Type, class... OtherTypes>
    using RemoveAll_R = typename RemoveAll<TypesList_t, Type, OtherTypes...>::Result;
#pragma endregion

#pragma region RemoveAllCopy
    // SECTION: RemoveAllCopy
    // brief: leaves only one occurrences of the Type (or Types) in target TypesList
    // note 1: using RANDOM_TYPE1s_t = TL::CreateTypesList_R<char, int, int, char, char, bool, bool, int, float, bool>;
    // example 1: TL::RemoveAllCopy_R<RANDOM_TYPE1s_t, int>; // --> [char, int, char, char, bool, bool, float, bool]
    // example 2: TL::RemoveAllCopy_R<RANDOM_TYPE1s_t, int, char>; // --> [char, int, bool, bool, float, bool]
    // example 2: TL::RemoveAllCopy_R<RANDOM_TYPE1s_t, int, char, bool>; // --> [char, int, bool, float]
    // example 2: TL::RemoveAllCopy_R<RANDOM_TYPE1s_t, int, char, bool, float>; // --> [char, int, bool, float]

#define EXPLICIT_TYPE_INFO TYPE_INFO("RemoveAllCopy", "leaves only one occurrences of the Type (or Types) in target TypesList");

    template<class TypesList_t, class Type, class... OtherTypes>
    struct RemoveAllCopy {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use RemoveAllCopy with not TypesList-struct");
    };

    template<class Head, class Tail, class Type, class... OtherTypes>
    struct RemoveAllCopy<TypesList<Head, Tail>, Type, OtherTypes...> {
        EXPLICIT_TYPE_INFO
        using Result = typename RemoveAllCopy<Remove_R<TypesList<Head, Tail>, Type, 1>, OtherTypes...>::Result;
    };

    template<class Head, class Tail, class Type>
    struct RemoveAllCopy<TypesList<Head, Tail>, Type> {
        EXPLICIT_TYPE_INFO
        using Result = Remove_R<TypesList<Head, Tail>, Type, 1>;
    };

    template<class Head1, class Tail1, class Head2, class Tail2>
    struct RemoveAllCopy<TypesList<Head1, Tail1>, TypesList<Head2, Tail2>> {
        EXPLICIT_TYPE_INFO
        using Result = typename RemoveAllCopy<Remove_R<TypesList<Head1, Tail1>, Head2, 1>, Tail2>::Result;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t, class Type, class... OtherTypes>
    using RemoveAllCopy_R = typename RemoveAllCopy<TypesList_t, Type, OtherTypes...>::Result;
#pragma endregion

#pragma region Refine
    // SECTION: Refine
    // brief: refine TypesList making its more beautiful: (1) only one occurrence for each types
    // note 1: using RANDOM_TYPE1s_t = TL::CreateTypesList_R<int, int, int, int>;
    // note 2: using RANDOM_TYPE2s_t = TL::CreateTypesList_R<int, int, bool, bool, char, char, float, float>;
    // note 3: using RANDOM_TYPE3s_t = TL::CreateTypesList_R<int, bool, char, float, int, bool, char, float>;
    // note 4: using RANDOM_TYPE4s_t = TL::CreateTypesList_R<char, int, int, char, char, bool, bool, int, float, bool>;
    // example 1: TL::Refine_R<RANDOM_TYPE1s_t>; // --> [int]
    // example 2: TL::Refine_R<RANDOM_TYPE2s_t>; // --> [int, bool, char, float]
    // example 2: TL::Refine_R<RANDOM_TYPE3s_t>; // --> [int, bool, char, float]
    // example 4: TL::Refine_R<RANDOM_TYPE4s_t>; // --> [char, int, bool, float]

#define EXPLICIT_TYPE_INFO TYPE_INFO("Refine", "refine TypesList making its more beautiful: (1) only one occurrence for each types");

    template<class TypesList_t>
    struct Refine {
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use Refine with not TypesList-struct");
    };

    template<class Head, class Tail>
    struct Refine<TypesList<Head, Tail>> {
        using Result = RemoveAllCopy_R<TypesList<Head, Tail>, TypesList<Head, Tail>>;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t>
    using Refine_R = typename Refine<TypesList_t>::Result;
#pragma endregion

#pragma region Replace
    // SECTION: Replace
    // brief: replaces Before-type to After-type in target TypesList, leaved only a given quantity occurrences
    // note 1: using RANDOM_TYPE1s_t = TL::CreateTypesList_R<int, int, int, int>;
    // note 2: using RANDOM_TYPE4s_t = TL::CreateTypesList_R<char, int, int, char, char, bool, bool, int, float, bool>;
    // example 1: TL::Replace_R<RANDOM_TYPE1s_t, int, double, 0>; // --> [double, double, double, double]
    // example 1: TL::Replace_R<RANDOM_TYPE1s_t, int, double, 1>; // --> [int, double, double, double]
    // example 1: TL::Replace_R<RANDOM_TYPE1s_t, int, double, 2>; // --> [int, int, double, double]
    // example 1: TL::Replace_R<RANDOM_TYPE1s_t, int, double, 3>; // --> [int, int, int, double]
    // example 1: TL::Replace_R<RANDOM_TYPE1s_t, int, double, 4>; // --> [int, int, int, int]
    // example 1: TL::Replace_R<RANDOM_TYPE1s_t, int, double, UINT8_MAX>; // --> [int, int, int, int]
    // example 1: TL::Replace_R<RANDOM_TYPE2s_t, int, double, 0>; // --> [char, double, double, char, char, bool, bool, double, float, bool]

#define EXPLICIT_TYPE_INFO TYPE_INFO("Replace", "replaces Before-type to After-type in target TypesList, leaved only a given quantity occurrences");

    template<class TypesList_t, class Before, class After, uint8_t quantity>
    struct Replace {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use Replace with not TypesList-struct");
    };

    template<class Head, class Tail, class Before, class After, uint8_t quantity>
    struct Replace<TypesList<Head, Tail>, Before, After, quantity> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Head, typename Replace<Tail, Before, After, quantity>::Result>;
    };

    template<class Tail, class Before, class After, uint8_t quantity>
    struct Replace<TypesList<Before, Tail>, Before, After, quantity> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<Before, typename Replace<Tail, Before, After, quantity - 1>::Result>;
    };

    template<class Tail, class Before, class After>
    struct Replace<TypesList<Before, Tail>, Before, After, 0> {
        EXPLICIT_TYPE_INFO
        using Result = TypesList<After, typename Replace<Tail, Before, After, 0>::Result>;
    };

    template<class Before, class After, uint8_t quantity>
    struct Replace<NullType, Before, After, quantity> {
        EXPLICIT_TYPE_INFO
        using Result = NullType;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t, class Before, class After, uint8_t quantity>
    using Replace_R = typename Replace<TypesList_t, Before, After, quantity>::Result;

    template<class TypesList_t, class Before, class After>
    using ReplaceAll_R = Replace_R<TypesList_t, Before, After, 0>;
#pragma endregion

#pragma region Swap
    // SECTION: Swap
    // brief: swaps two types by its indexes in target TypesList
    // note 1: using TEST_TYPEs_t = TL::CreateTypesList_R<char, int, bool, double, float>;
    // example 1: TL::Swap_R<TEST_TYPEs_t, 0, 1>; // --> [int, char, bool, double, float]
    // example 1: TL::Swap_R<TEST_TYPEs_t, 1, 3>; // --> [char, double, bool, int, float]
    // example 1: TL::Swap_R<TEST_TYPEs_t, 0, 4>; // --> [float, int, bool, double, char]

#define EXPLICIT_TYPE_INFO TYPE_INFO("Swap", "swaps two types by its indexes in target TypesList");

    template<class TypesList_t, uint8_t index1, uint8_t index2>
    struct Swap {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use Swap with not TypesList-struct");
    };

    template<class Head, class Tail, uint8_t index1, uint8_t index2>
    struct Swap<TypesList<Head, Tail>, index1, index2> {
        EXPLICIT_TYPE_INFO
        private:
        using TypesList_t = TypesList<Head, Tail>;
        using Type1 = GetTypeByIndex_R<TypesList_t, index1>;
        using Type2 = GetTypeByIndex_R<TypesList_t, index2>;

        public:
        using Result = InsertByIndex_R<RemoveByIndex_R<InsertByIndex_R<RemoveByIndex_R<TypesList_t, index2>, Type1, index2>, index1>, Type2, index1>;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t, uint8_t index1, uint8_t index2>
    using Swap_R = typename Swap<TypesList_t, index1, index2>::Result;
#pragma endregion

#pragma region SwapTypes
    // SECTION: SwapTypes
    // brief: swaps two types in target TypesList
    // note 1: using TEST_TYPEs_t = TL::CreateTypesList_R<int, char, bool, bool, double, float>;
    // example 1: TL::SwapTypes_R<TEST_TYPEs_t, int, char>; // --> [char, int, bool, bool, double, float]
    // example 1: TL::SwapTypes_R<TEST_TYPEs_t, char, int>; // --> [char, int, bool, bool, double, float]
    // example 1: TL::SwapTypes_R<TEST_TYPEs_t, int, double>; // --> [double, char, bool, bool, int, float]
    // example 1: TL::SwapTypes_R<TEST_TYPEs_t, int, bool>; // compilation error

#define EXPLICIT_TYPE_INFO TYPE_INFO("SwapTypes", "swaps two types in target TypesList");

    template<class TypesList_t, class Type1, class Type2>
    struct SwapTypes {
        EXPLICIT_TYPE_INFO
        static_assert(AlwaysFalse_tR<TypesList_t>, "forbidden to use SwapTypes with not TypesList-struct");
    };

    template<class Head, class Tail, class Type1, class Type2>
    struct SwapTypes<TypesList<Head, Tail>, Type1, Type2> {
        EXPLICIT_TYPE_INFO
        private:
        static_assert(!std::is_same_v<Type1, Type2>, "swapping types cannot be same");
        using TypesList_t = TypesList<Head, Tail>;
        static_assert((Count_R<TypesList_t, Type1> == 1), "first type to swap must have only one occurrence inside target TypesList");
        static_assert((Count_R<TypesList_t, Type2> == 1), "second type to swap must have only one occurrence inside target TypesList");

        public:
        using Result = Swap_R<TypesList_t, GetIndexByType_R<TypesList_t, Type1>, GetIndexByType_R<TypesList_t, Type2>>;
    };

#undef EXPLICIT_TYPE_INFO

    template<class TypesList_t, class Type1, class Type2>
    using SwapTypes_R = typename SwapTypes<TypesList_t, Type1, Type2>::Result;
#pragma endregion
} // namespace TL

#endif // __TYPES_LIST__
