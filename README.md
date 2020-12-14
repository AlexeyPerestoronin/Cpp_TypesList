# TypesList
If is a library provided structs and type-constructor-struct for manipulation of types as if a list-data-structure is used
***
## suggestions for improvement
1. develop and use `sc_string`-cpp-class which provides static-compiler-strings, and use it for modernize static assertion messages as:
    - before: `static_assert(!std::is_same_v<NullType, TypesList>, "Type is not existant inside TypesList");`
    - after: `static_assert(!std::is_same_v<NullType, TypesList>, sc_string("Type") + sc_string(TypeInfo<NullType>::name) + sc_string("is not existant inside TypesList"));`
2. by using of `cs_string`-type need implement extended `TypeInfo`-struct for `TypesList`-struct which will defined the `name` and `description` fields as (for example):
    - `uint8_t + uint16_t + uint32_t + uint64_t`
    - `8-bit size unsigned integer STL-type + 16-bit size unsigned integer STL-type + 32-bit size unsigned integer STL-type + 641-bit size unsigned integer STL-type`