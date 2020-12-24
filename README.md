# TypesList
It is a library provided structs (and type-constructor-struct) for manipulation of types as if a list-data-structure is used
***
## Content (Plan)
* [x] namespace: TL:
    * [x] struct: Always(True|False) - returns boolean (true/false) regardless of type
    * [x] struct: TypeInfo - if Type is compatibility - provides information about type; compilation error - vise versa
    * [x] struct: TypesList - base struct of TL-logic is one list of cpp-types
    * [x] struct: CreateTypesList - creates arbitrary length list of types
    * [x] struct: GetTypeByIndex - get Type from TypesList by index
    * [x] struct: GetIndexByType - get index inside TypesList by which target Type is placed
    * [x] struct: IsInList - check if Type is in TypesList
    * [x] struct: AppendBack - appends one type or arbitrary length types list at the end of the target TypesList
    * [x] struct: AppendFront - appends one type or arbitrary length types list at the end of the target TypesList to front
    * [x] struct: InsertByIndex - insert one type or arbitrary length types list at the target TypesList by index
    * [x] struct: RemoveBack - removes last type from target TypesList
    * [x] struct: RemoveFront - removes first type from target TypesList
    * [x] struct: RemoveByIndex - removes type from target TypesList by index
    * [x] struct: RemoveFromSize - removes the types since from-index to from+size-index from target TypesList
    * [x] struct: CutFromSize - cuts out the types since from-index to from+size-index from target TypesList
    * [x] struct: Count - counts the quantity of entries of the Type (or Types) in target TypesList
    * [x] struct: Remove - removes the Type from target TypesList, leave only a given quantity of occurrences
    * [x] struct: RemoveAll - removes all occurrences of the Type (or Types) from target TypesList
    * [x] struct: RemoveAllCopy - leaves only one occurrences of the Type (or Types) in target TypesList
    * [x] struct: Refine - refine TypesList making its more beautiful: (1) only one occurrence for each types
    * [x] struct: Replace - replaces Before-type to After-type in target TypesList, leaved only a given quantity occurrences
    * [x] struct: ReplaceAll - replaces Before-type to After-type in target TypesList
    * [x] struct: Swap - swaps two types by its indexes in target TypesList
    * [x] struct: SwapTypes - swaps two types in target TypesList
### Suggestions for improvement
* [ ] develop and use `sc_string`-cpp-class which provides static-compiler-strings, and use it for modernize static assertion messages as:
    - before: `static_assert(!std::is_same_v<NullType, TypesList>, "Type is not existent inside TypesList");`
    - after: `static_assert(!std::is_same_v<NullType, TypesList>, sc_string("Type") + sc_string(TypeInfo<NullType>::name) + sc_string("is not existent inside TypesList"));`
* [ ] by using of `cs_string`-type need implement extended `TypeInfo`-struct for `TypesList`-struct which will defined the `name` and `description` fields as (for example):
    - `uint8_t + uint16_t + uint32_t + uint64_t`
    - `8-bit size unsigned integer STL-type + 16-bit size unsigned integer STL-type + 32-bit size unsigned integer STL-type + 641-bit size unsigned integer STL-type`
* [ ] make substitute (1) `#define TL_TYPE uint8_t` and (2) `#define TL_TYPE_MAX UINT8_MAX` and use them