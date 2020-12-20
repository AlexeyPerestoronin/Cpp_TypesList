#ifndef __TYPES_LIST__
#define __TYPES_LIST__

#include <stdint.h>
#include <type_traits>

#define TYPE_INFO(name_value, description_value)\
constexpr static const char* NameOfType = name_value;\
constexpr static const char* DescriptionOfType = description_value;

// TL - Types Lists
namespace TL {
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
    // example 1: using UINTs_t = TL::CreateTypesList<uint8_t, uint16_t, uint32_t, uint64_t>::Result;
    // example 2: using INTs_t = TL::CreateTypesList<int8_t, int16_t, int32_t, int64_t>::Result;

    template<class Type, class ... OtherTypes>
    struct CreateTypesList {
        TYPE_INFO("CreateTypesList", "creates arbitrary length list of types");

        using Result = TypesList_R<Type, typename CreateTypesList<OtherTypes ...>::Result>;
    };

    template<class Type>
    struct CreateTypesList<Type> {
        TYPE_INFO("CreateTypesList", "creates arbitrary length list of types");

        using Result = TypesList_R<Type, NullType>;
    };

    template<>
    struct CreateTypesList<NullType> {
        TYPE_INFO("CreateTypesList", "creates arbitrary length list of types");

        using Result = NullType;
    };

    template<class Type, class ... OtherTypes>
    using CreateTypesList_R = typename CreateTypesList<Type, OtherTypes ...>::Result;
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

    template<class TypesList, uint8_t index>
    struct GetTypeByIndex {
        TYPE_INFO("GetTypeByIndex", "get Type from TypesList by index: use only with TypesList-struct");

        static_assert(!std::is_same_v<NullType, TypesList>, "index of TypesList out of range");
        using Result = NullType;
    };

    template<class Head, class Tail, uint8_t index>
    struct GetTypeByIndex<TypesList<Head, Tail>, index> {
        TYPE_INFO("GetTypeByIndex", "get Type from TypesList by index: use only with TypesList-struct");

        using Result = typename GetTypeByIndex<Tail, index - 1>::Result;
    };

    template<class Head, class Tail>
    struct GetTypeByIndex<TypesList<Head, Tail>, 0> {
        TYPE_INFO("GetTypeByIndex", "get Type from TypesList by index: use only with TypesList-struct");

        using Result = Head;
    };

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

    template<class TypesList, class Type>
    struct GetIndexByType {
        TYPE_INFO("GetIndexByType", "get index inside TypesList by which target Type is placed: use only with TypesList-struct");

        static_assert(!std::is_same_v<NullType, TypesList>, "Type is not existant inside TypesList");
        constexpr static uint8_t Result = 1;
    };

    template<class Head, class Tail, class Type>
    struct GetIndexByType<TypesList<Head, Tail>, Type> {
        TYPE_INFO("GetIndexByType", "get index inside TypesList by which target Type is placed: use only with TypesList-struct");

        constexpr static uint8_t Result = 1 + GetIndexByType<Tail, Type>::Result;
    };

    template<class Head, class Tail>
    struct GetIndexByType<TypesList<Head, Tail>, Head> {
        TYPE_INFO("GetIndexByType", "get index inside TypesList by which target Type is placed: use only with TypesList-struct");

        constexpr static uint8_t Result = 0;
    };

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

    template<class TypesList, class Type>
    struct IsInList {
        TYPE_INFO("IsInList", "check if Type is in TypesList: use only with TypesList-struct");

        static_assert(std::is_same_v<NullType, TypesList>, "use IsInList only with TypesList-struct");
        constexpr static bool Result = false;
    };

    template<class Head, class Tail, class Type>
    struct IsInList<TypesList<Head, Tail>, Type> {
        TYPE_INFO("IsInList", "check if Type is in TypesList: use only with TypesList-struct");

        constexpr static bool Result = IsInList<Tail, Type>::Result;
    };

    template<class Head, class Tail>
    struct IsInList<TypesList<Head, Tail>, Head> {
        TYPE_INFO("IsInList", "check if Type is in TypesList: use only with TypesList-struct");

        constexpr static bool Result = true;
    };

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

    template<class TypesList_t, class Type>
    struct AppendBack {
        TYPE_INFO("AppendBack", "appends one type or arbitrary length types list at the end of the target TypesList: use only with TypesList-struct");

        static_assert(std::is_same_v<TypesList_t, TypesList>, "forbidden to apply AppendBack-struct to not TypesList-struct");
    };

    template<class Head, class Tail, class Type>
    struct AppendBack<TypesList<Head, Tail>, Type> {
        TYPE_INFO("AppendBack", "appends one type or arbitrary length types list at the end of the target TypesList: use only with TypesList-struct");

        using Result = TypesList<Head, typename AppendBack<Tail, Type>::Result>;
    };

    template<class Head, class Type>
    struct AppendBack<TypesList<Head, NullType>, Type> {
        TYPE_INFO("AppendBack", "appends one type or arbitrary length types list at the end of the target TypesList: use only with TypesList-struct");

        using Result = TypesList<Head, TypesList<Type, NullType>>;
    };

    template<class Head1, class Head2, class Tail2>
    struct AppendBack<TypesList<Head1, NullType>, TypesList<Head2, Tail2>> {
        TYPE_INFO("AppendBack", "appends one type or arbitrary length types list at the end of the target TypesList: use only with TypesList-struct");

        using Result = typename AppendBack<TypesList<Head1, TypesList<Head2, NullType>>, Tail2>::Result;
    };

    template<class Head1, class Head2>
    struct AppendBack<TypesList<Head1, NullType>, TypesList<Head2, NullType>> {
        TYPE_INFO("AppendBack", "appends one type or arbitrary length types list at the end of the target TypesList: use only with TypesList-struct");

        using Result = TypesList<Head1, TypesList<Head2, NullType>>;
    };

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

    template<class TypesList_t, class Type>
    struct AppendFront {
        TYPE_INFO("AppendFront", "appends one type or arbitrary length types list at the beginning of the target TypesList to front: use only with TypesList-struct");

        static_assert(std::is_same_v<TypesList_t, TypesList>, "forbidden to apply AppendFront-struct to not TypesList-struct");
    };

    template<class Head, class Tail, class Type>
    struct AppendFront<TypesList<Head, Tail>, Type> {
        TYPE_INFO("AppendFront", "appends one type or arbitrary length types list at the beginning of the target TypesList to front: use only with TypesList-struct");

        using Result = AppendBack_R<CreateTypesList_R<Type>, TypesList<Head, Tail>>;
    };

    template<class Head1, class Tail1, class Head2, class Tail2>
    struct AppendFront<TypesList<Head1, Tail1>, TypesList<Head2, Tail2>> {
        TYPE_INFO("AppendFront", "appends one type or arbitrary length types list at the beginning of the target TypesList to front: use only with TypesList-struct");

        using Result = AppendBack_R<TypesList<Head2, Tail2>, TypesList<Head1, Tail1>>;
    };

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

    template<class TypesList_t, class Type, uint8_t index>
    struct InsertByIndex {
        TYPE_INFO("InsertByIndex", "insert one type or arbitrary length types list at the target TypesList by index: use only with TypesList-struct");
    };

    template<class Type, uint8_t index>
    struct InsertByIndex<NullType, Type, index> {
        TYPE_INFO("InsertByIndex", "insert one type or arbitrary length types list at the target TypesList by index: use only with TypesList-struct");

        static_assert(index == 0, "index out of range for target TypesList");
    };

    template<class Head, class Tail, class Type, uint8_t index>
    struct InsertByIndex<TypesList<Head, Tail>, Type, index> {
        TYPE_INFO("InsertByIndex", "insert one type or arbitrary length types list at the target TypesList by index: use only with TypesList-struct");

        using Result = TypesList<Head, typename InsertByIndex<Tail, Type, index - 1>::Result>;
    };

    template<class Head, class Tail, class Type>
    struct InsertByIndex<TypesList<Head, Tail>, Type, 0> {
        TYPE_INFO("InsertByIndex", "insert one type or arbitrary length types list at the target TypesList by index: use only with TypesList-struct");

        using Result = AppendFront_R<TypesList<Head, Tail>, Type>;
    };

    template<class Head, class Tail>
    struct InsertByIndex<NullType, TypesList<Head, Tail>, 0> {
        TYPE_INFO("InsertByIndex", "insert one type or arbitrary length types list at the target TypesList by index: use only with TypesList-struct");

        using Result = TypesList<Head, Tail>;
    };

    template<class Type>
    struct InsertByIndex<NullType, Type, 0> {
        TYPE_INFO("InsertByIndex", "insert one type or arbitrary length types list at the target TypesList by index: use only with TypesList-struct");

        using Result = TypesList<Type, NullType>;
    };

    template<class TypesList, class Type, uint8_t index>
    using InsertByIndex_R = typename InsertByIndex<TypesList, Type, index>::Result;
#pragma endregion


#pragma region RemoveBack
    // SECTION: RemoveBack
    // brief: remove last type from target TypesList
    // example 1: RemoveBack_R<INTs_t> // --> [int8_t, int16_t, int32_t]
    // example 2: RemoveBack_R<RemoveBack_R<INTs_t>> // --> [int8_t, int16_t]
    // example 3: RemoveBack_R<RemoveBack_R<RemoveBack_R<INTs_t>>> // --> [int8_t]
    // example 4: RemoveBack_R<RemoveBack_R<RemoveBack_R<RemoveBack_R<INTs_t>>>> // --> []
    // example 5: RemoveBack_R<RemoveBack_R<RemoveBack_R<RemoveBack_R<RemoveBack_R<INTs_t>>>>> // --> compilation error

    template<class TypesList_t>
    struct RemoveBack {
        TYPE_INFO("RemoveBack", "remove last type from target TypesList: use only with TypesList-struct");

        static_assert(!std::is_same_v<TypesList_t, NullType>, "forbidden to apply RemoveBack-struct to NullType-struct");
    };

    template<class Head, class Tail>
    struct RemoveBack<TypesList<Head, Tail>> {
        TYPE_INFO("RemoveBack", "remove last type from target TypesList: use only with TypesList-struct");

        using Result = TypesList<Head, typename RemoveBack<Tail>::Result>;
    };

    template<class Head>
    struct RemoveBack<TypesList<Head, NullType>> {
        TYPE_INFO("RemoveBack", "remove last type from target TypesList: use only with TypesList-struct");

        using Result = NullType;
    };

    template<class TypesList_t>
    using RemoveBack_R = typename RemoveBack<TypesList_t>::Result;
#pragma endregion
}

#endif // __TYPES_LIST__
