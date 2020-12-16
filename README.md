# TypesList
It is a library provided structs and type-constructor-struct for manipulation of types as if a list-data-structure is used
***
## Plan
* [ ] namespace: TL:
    * [x] struct: TypeInfo - if Type is compatibility - provides information about type; compilation error - vise versa
    * [x] struct: TypesList - base struct of TL-logic is one list of cpp-types
    * [x] struct: CreateTypesList - creates arbitrary length list of types
    * [x] struct: GetTypeByIndex - get Type from TypesList by index
    * [x] struct: GetIndexByType - get index inside TypesList by which target Type is placed
    * [x] struct: IsInList - check if Type is in TypesList
    * [x] struct: AppendBack - appends one type or arbitrary length types list at the end of the target TypesList
    * [x] struct: AppendFront - appends one type or arbitrary length types list at the end of the target TypesList to front
    * [x] struct: InsertByIndex - insert one type or arbitrary length types list at the target TypesList by index
    * [ ] struct: RemoveBack
    * [ ] struct: RemoveFront
    * [ ] struct: RemoveByIndex
    * [ ] struct: 
    * [ ] struct: 
    * [ ] struct: 
### Suggestions for improvement
* [ ] develop and use `sc_string`-cpp-class which provides static-compiler-strings, and use it for modernize static assertion messages as:
    - before: `static_assert(!std::is_same_v<NullType, TypesList>, "Type is not existant inside TypesList");`
    - after: `static_assert(!std::is_same_v<NullType, TypesList>, sc_string("Type") + sc_string(TypeInfo<NullType>::name) + sc_string("is not existant inside TypesList"));`
* [ ] by using of `cs_string`-type need implement extended `TypeInfo`-struct for `TypesList`-struct which will defined the `name` and `description` fields as (for example):
    - `uint8_t + uint16_t + uint32_t + uint64_t`
    - `8-bit size unsigned integer STL-type + 16-bit size unsigned integer STL-type + 32-bit size unsigned integer STL-type + 641-bit size unsigned integer STL-type`