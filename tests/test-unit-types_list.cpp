#include <gtest/gtest.h>
#include <types_list.hpp>

// test types lists
using UINTs_t = TL::CreateTypesList_R<uint8_t, uint16_t, uint32_t, uint64_t>;
using INTs_t = TL::CreateTypesList_R<int8_t, int16_t, int32_t, int64_t>;

TEST(TypesList, Size) {
    EXPECT_EQ(UINTs_t::size, 4);
    EXPECT_EQ(INTs_t::size, 4);
}

TEST(TypesList, GetTypeByIndex) {
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<UINTs_t, 0>, uint8_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<UINTs_t, 1>, uint16_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<UINTs_t, 2>, uint32_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<UINTs_t, 3>, uint64_t>));
    //EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<UINTs_t, 4>, uint64_t>)); // compilation error

    EXPECT_FALSE((std::is_same_v<TL::GetTypeByIndex_R<UINTs_t, 3>, uint8_t>));
    EXPECT_FALSE((std::is_same_v<TL::GetTypeByIndex_R<UINTs_t, 2>, uint16_t>));
    EXPECT_FALSE((std::is_same_v<TL::GetTypeByIndex_R<UINTs_t, 1>, uint32_t>));
    EXPECT_FALSE((std::is_same_v<TL::GetTypeByIndex_R<UINTs_t, 0>, uint64_t>));
    //EXPECT_FALSE((std::is_same_v<TL::GetTypeByIndex_R<UINTs_t, 11>, uint64_t>)); // compilation error

    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<INTs_t, 0>, int8_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<INTs_t, 1>, int16_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<INTs_t, 2>, int32_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<INTs_t, 3>, int64_t>));
    //EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<INTs_t, 5>, int64_t>)); // compilation error

    EXPECT_FALSE((std::is_same_v<TL::GetTypeByIndex_R<INTs_t, 3>, int8_t>));
    EXPECT_FALSE((std::is_same_v<TL::GetTypeByIndex_R<INTs_t, 2>, int16_t>));
    EXPECT_FALSE((std::is_same_v<TL::GetTypeByIndex_R<INTs_t, 1>, int32_t>));
    EXPECT_FALSE((std::is_same_v<TL::GetTypeByIndex_R<INTs_t, 0>, int64_t>));
    //EXPECT_FALSE((std::is_same_v<TL::GetTypeByIndex_R<INTs_t, 8>, int64_t>)); // compilation error
}

TEST(TypesList, GetIndexByType) {
    EXPECT_EQ((TL::GetIndexByType_R<UINTs_t, uint8_t>), 0);
    EXPECT_EQ((TL::GetIndexByType_R<UINTs_t, uint16_t>), 1);
    EXPECT_EQ((TL::GetIndexByType_R<UINTs_t, uint32_t>), 2);
    EXPECT_EQ((TL::GetIndexByType_R<UINTs_t, uint64_t>), 3);
    //EXPECT_EQ((TL::GetIndexByType_R<UINTs_t, char>), 3); // compilation error

    EXPECT_NE((TL::GetIndexByType_R<UINTs_t, uint8_t>), 3);
    EXPECT_NE((TL::GetIndexByType_R<UINTs_t, uint16_t>), 2);
    EXPECT_NE((TL::GetIndexByType_R<UINTs_t, uint32_t>), 1);
    EXPECT_NE((TL::GetIndexByType_R<UINTs_t, uint64_t>), 0);
    //EXPECT_NE((TL::GetIndexByType_R<UINTs_t, bool>), 0); // compilation error

    EXPECT_EQ((TL::GetIndexByType_R<INTs_t, int8_t>), 0);
    EXPECT_EQ((TL::GetIndexByType_R<INTs_t, int16_t>), 1);
    EXPECT_EQ((TL::GetIndexByType_R<INTs_t, int32_t>), 2);
    EXPECT_EQ((TL::GetIndexByType_R<INTs_t, int64_t>), 3);
    //EXPECT_EQ((TL::GetIndexByType_R<INTs_t, double>), 3); // compilation error

    EXPECT_NE((TL::GetIndexByType_R<INTs_t, int8_t>), 3);
    EXPECT_NE((TL::GetIndexByType_R<INTs_t, int16_t>), 2);
    EXPECT_NE((TL::GetIndexByType_R<INTs_t, int32_t>), 1);
    EXPECT_NE((TL::GetIndexByType_R<INTs_t, int64_t>), 0);
    //EXPECT_NE((TL::GetIndexByType_R<INTs_t, std::string>), 0); // compilation error
}

TEST(TypesList, CreateTypesList) {
    {
        using ALL_INTs_t = TL::CreateTypesList_R<INTs_t>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 3);
    }
    {
        using ALL_INTs_t = TL::CreateTypesList_R<INTs_t, double>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, double>), 4);
    }
    {
        using ALL_INTs_t = TL::CreateTypesList_R<double, INTs_t>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, double>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 4);
    }
    {
        using ALL_INTs_t = TL::CreateTypesList_R<INTs_t, UINTs_t>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint8_t>), 4);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint16_t>), 5);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint32_t>), 6);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint64_t>), 7);
    }
    using CHARs_t = TL::CreateTypesList_R<char, char16_t, char32_t>;
    {
        using ALL_INTs_t = TL::CreateTypesList_R<INTs_t, UINTs_t, CHARs_t>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size + CHARs_t::size);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint8_t>), 4);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint16_t>), 5);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint32_t>), 6);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint64_t>), 7);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, char>), 8);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, char16_t>), 9);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, char32_t>), 10);
    }
    {
        using ALL_INTs_t = TL::CreateTypesList_R<double, INTs_t, UINTs_t, CHARs_t, float>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size + CHARs_t::size + 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, double>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 4);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint8_t>), 5);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint16_t>), 6);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint32_t>), 7);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint64_t>), 8);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, char>), 9);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, char16_t>), 10);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, char32_t>), 11);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, float>), 12);
    }
    {
        using ALL_INTs_t = TL::CreateTypesList_R<double, INTs_t, UINTs_t, float, CHARs_t>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size + CHARs_t::size + 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, double>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 4);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint8_t>), 5);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint16_t>), 6);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint32_t>), 7);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint64_t>), 8);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, float>), 9);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, char>), 10);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, char16_t>), 11);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, char32_t>), 12);
    }
}

using ALL_INTs_t = TL::CreateTypesList_R<UINTs_t, INTs_t>;

TEST(TypesList, IsInList) {
    EXPECT_TRUE((TL::IsInList_R<UINTs_t, uint8_t>));
    EXPECT_TRUE((TL::IsInList_R<UINTs_t, uint16_t>));
    EXPECT_TRUE((TL::IsInList_R<UINTs_t, uint32_t>));
    EXPECT_TRUE((TL::IsInList_R<UINTs_t, uint64_t>));

    EXPECT_FALSE((TL::IsInList_R<UINTs_t, int8_t>));
    EXPECT_FALSE((TL::IsInList_R<UINTs_t, int16_t>));
    EXPECT_FALSE((TL::IsInList_R<UINTs_t, int32_t>));
    EXPECT_FALSE((TL::IsInList_R<UINTs_t, int64_t>));
}

TEST(TypesList, AppendBack) {
    // using INT8_t_and_INT16_t = TL::AppendBack_R<int8_t, int16_t>; // compilation error

    using INT8_t_and_INT16_t = TL::AppendBack_R<TL::CreateTypesList<int8_t>::Result, int16_t>;
    EXPECT_EQ(INT8_t_and_INT16_t::size, 2);
    EXPECT_TRUE((TL::IsInList_R<INT8_t_and_INT16_t, int8_t>));
    EXPECT_TRUE((TL::IsInList_R<INT8_t_and_INT16_t, int16_t>));
    EXPECT_EQ((TL::GetIndexByType_R<INT8_t_and_INT16_t, int8_t>), 0);
    EXPECT_EQ((TL::GetIndexByType_R<INT8_t_and_INT16_t, int16_t>), 1);
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<INT8_t_and_INT16_t, 0>, int8_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<INT8_t_and_INT16_t, 1>, int16_t>));

    using INTs_with_char_t = TL::AppendBack_R<INTs_t, char>;
    EXPECT_TRUE((TL::IsInList_R<INTs_with_char_t, char>));
    EXPECT_EQ(INTs_with_char_t::size, INTs_t::size + 1);
    EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, char>), INTs_with_char_t::size - 1);
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<INTs_with_char_t, INTs_with_char_t::size - 1>, char>));

    using ALL_INTs_t = TL::AppendBack_R<INTs_t, UINTs_t>;
    EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 0);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 1);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 2);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 3);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint8_t>), 4);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint16_t>), 5);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint32_t>), 6);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint64_t>), 7);
    //EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, char>), 8); // compilation error
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 0>, int8_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 1>, int16_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 2>, int32_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 3>, int64_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 4>, uint8_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 5>, uint16_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 6>, uint32_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 7>, uint64_t>));
    //EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 8>, char>)); // compilation error
}

TEST(TypesList, AppendFront) {
    //using INT8_t_and_INT16_t = TL::AppendFront_R<int8_t, int16_t>; // compilation error

    using INT16_t_and_INT8_t = TL::AppendFront_R<TL::CreateTypesList_R<int8_t>, int16_t>;
    EXPECT_EQ(INT16_t_and_INT8_t::size, 2);
    EXPECT_TRUE((TL::IsInList_R<INT16_t_and_INT8_t, int16_t>));
    EXPECT_TRUE((TL::IsInList_R<INT16_t_and_INT8_t, int8_t>));
    EXPECT_EQ((TL::GetIndexByType_R<INT16_t_and_INT8_t, int16_t>), 0);
    EXPECT_EQ((TL::GetIndexByType_R<INT16_t_and_INT8_t, int8_t>), 1);
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<INT16_t_and_INT8_t, 0>, int16_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<INT16_t_and_INT8_t, 1>, int8_t>));

    using char_with_INTs_t = TL::AppendFront_R<INTs_t, char>;
    EXPECT_EQ(char_with_INTs_t::size, INTs_t::size + 1);
    EXPECT_EQ((TL::GetIndexByType_R<char_with_INTs_t, char>), 0);
    EXPECT_EQ((TL::GetIndexByType_R<char_with_INTs_t, int8_t>), 1);
    EXPECT_EQ((TL::GetIndexByType_R<char_with_INTs_t, int16_t>), 2);
    EXPECT_EQ((TL::GetIndexByType_R<char_with_INTs_t, int32_t>), 3);
    EXPECT_EQ((TL::GetIndexByType_R<char_with_INTs_t, int64_t>), 4);
    //EXPECT_EQ((TL::GetIndexByType_R<char_with_INTs_t, int>), 0); // compilation error
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<char_with_INTs_t, 0>, char>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<char_with_INTs_t, 1>, int8_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<char_with_INTs_t, 2>, int16_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<char_with_INTs_t, 3>, int32_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<char_with_INTs_t, 4>, int64_t>));
    //EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<char_with_INTs_t, 5>, int>)); // compilation error

    using ALL_INTs_t = TL::AppendFront_R<INTs_t, UINTs_t>;
    EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint8_t>), 0);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint16_t>), 1);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint32_t>), 2);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint64_t>), 3);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 4);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 5);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 6);
    EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 7);
    //EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int>), 8); // compilation error
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 0>, uint8_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 1>, uint16_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 2>, uint32_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 3>, uint64_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 4>, int8_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 5>, int16_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 6>, int32_t>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 7>, int64_t>));
    //EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<ALL_INTs_t, 8>, int>)); // compilation error
}

TEST(TypesList, InsertByIndex) {
    //using int_char_t = TL::InsertByIndex_R<int, char, 1>;  // compilation error
    {
        using INT_16_8_t = TL::InsertByIndex_R<TL::CreateTypesList_R<int8_t>, int16_t, 0>;
        EXPECT_EQ((TL::GetIndexByType_R<INT_16_8_t, int16_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<INT_16_8_t, int8_t>), 1);
        using INT_8_16_t = TL::InsertByIndex_R<TL::CreateTypesList_R<int8_t>, int16_t, 1>;
        EXPECT_EQ((TL::GetIndexByType_R<INT_8_16_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<INT_8_16_t, int16_t>), 1);
    }
    {
        using INTs_with_char_t = TL::InsertByIndex_R<INTs_t, char, 0>;
        EXPECT_EQ(INTs_with_char_t::size, INTs_t::size + 1);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, char>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int8_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int16_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int32_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int64_t>), 4);
    }
    {
        using INTs_with_char_t = TL::InsertByIndex_R<INTs_t, char, 1>;
        EXPECT_EQ(INTs_with_char_t::size, INTs_t::size + 1);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, char>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int16_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int32_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int64_t>), 4);
    }
    {
        using INTs_with_char_t = TL::InsertByIndex_R<INTs_t, char, 2>;
        EXPECT_EQ(INTs_with_char_t::size, INTs_t::size + 1);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int16_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, char>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int32_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int64_t>), 4);
    }
    {
        using INTs_with_char_t = TL::InsertByIndex_R<INTs_t, char, 3>;
        EXPECT_EQ(INTs_with_char_t::size, INTs_t::size + 1);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int16_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int32_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, char>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int64_t>), 4);
    }
    {
        using INTs_with_char_t = TL::InsertByIndex_R<INTs_t, char, 4>;
        //using INTs_with_char_t = TL::InsertByIndex_R<INTs_t, char, 5>; // compilation error
        EXPECT_EQ(INTs_with_char_t::size, INTs_t::size + 1);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int16_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int32_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, int64_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<INTs_with_char_t, char>), 4);
    }
    {
        using ALL_INTs_t = TL::InsertByIndex_R<INTs_t, UINTs_t, 0>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint16_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint32_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint64_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 4);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 5);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 6);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 7);
    }
    {
        using ALL_INTs_t = TL::InsertByIndex_R<INTs_t, UINTs_t, 1>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint8_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint16_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint32_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint64_t>), 4);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 5);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 6);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 7);
    }
    {
        using ALL_INTs_t = TL::InsertByIndex_R<INTs_t, UINTs_t, 2>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint8_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint16_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint32_t>), 4);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint64_t>), 5);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 6);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 7);
    }
    {
        using ALL_INTs_t = TL::InsertByIndex_R<INTs_t, UINTs_t, 3>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint8_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint16_t>), 4);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint32_t>), 5);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint64_t>), 6);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 7);
    }
    {
        using ALL_INTs_t = TL::InsertByIndex_R<INTs_t, UINTs_t, 4>;
        EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int8_t>), 0);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int16_t>), 1);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int32_t>), 2);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, int64_t>), 3);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint8_t>), 4);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint16_t>), 5);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint32_t>), 6);
        EXPECT_EQ((TL::GetIndexByType_R<ALL_INTs_t, uint64_t>), 7);
    }
    // using ALL_INTs_t = TL::InsertByIndex_R<INTs_t, UINTs_t, 5>; // compilation error
}

TEST(TypesList, RemoveBack) {
    using NOT_ALL_INTs_3_t = TL::RemoveBack_R<INTs_t>;
    EXPECT_EQ(NOT_ALL_INTs_3_t::size, INTs_t::size - 1);
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_3_t, 0>, TL::GetTypeByIndex_R<INTs_t, 0>>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_3_t, 1>, TL::GetTypeByIndex_R<INTs_t, 1>>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_3_t, 2>, TL::GetTypeByIndex_R<INTs_t, 2>>));
    //EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_3_t, 3>, TL::GetTypeByIndex_R<INTs_t, 3>>)); // compilation error

    using NOT_ALL_INTs_2_t = TL::RemoveBack_R<NOT_ALL_INTs_3_t>;
    EXPECT_EQ(NOT_ALL_INTs_2_t::size, NOT_ALL_INTs_3_t::size - 1);
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_2_t, 0>, TL::GetTypeByIndex_R<INTs_t, 0>>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_2_t, 1>, TL::GetTypeByIndex_R<INTs_t, 1>>));
    //EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_2_t, 2>, TL::GetTypeByIndex_R<INTs_t, 2>>)); // compilation error

    using NOT_ALL_INTs_1_t = TL::RemoveBack_R<NOT_ALL_INTs_2_t>;
    EXPECT_EQ(NOT_ALL_INTs_1_t::size, NOT_ALL_INTs_2_t::size - 1);
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_1_t, 0>, TL::GetTypeByIndex_R<INTs_t, 0>>));
    //EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_1_t, 1>, TL::GetTypeByIndex_R<INTs_t, 1>>)); // compilation error

    EXPECT_TRUE((std::is_same_v<TL::RemoveBack_R<NOT_ALL_INTs_1_t>, TL::NullType>));

    //using ERROR_1_t = TL::RemoveBack_R<TL::NullType>; // compilation error
    //using ERROR_2_t = TL::RemoveBack_R<int>; // compilation error
}

TEST(TypesList, RemoveFront) {
    using NOT_ALL_INTs_3_t = TL::RemoveFront_R<INTs_t>;
    EXPECT_EQ(NOT_ALL_INTs_3_t::size, INTs_t::size - 1);
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_3_t, 0>, TL::GetTypeByIndex_R<INTs_t, 1>>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_3_t, 1>, TL::GetTypeByIndex_R<INTs_t, 2>>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_3_t, 2>, TL::GetTypeByIndex_R<INTs_t, 3>>));
    //EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_3_t, 3>, TL::GetTypeByIndex_R<INTs_t, 3>>)); // compilation error

    using NOT_ALL_INTs_2_t = TL::RemoveFront_R<NOT_ALL_INTs_3_t>;
    EXPECT_EQ(NOT_ALL_INTs_2_t::size, NOT_ALL_INTs_3_t::size - 1);
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_2_t, 0>, TL::GetTypeByIndex_R<INTs_t, 2>>));
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_2_t, 1>, TL::GetTypeByIndex_R<INTs_t, 3>>));
    //EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_2_t, 2>, TL::GetTypeByIndex_R<INTs_t, 2>>)); // compilation error

    using NOT_ALL_INTs_1_t = TL::RemoveFront_R<NOT_ALL_INTs_2_t>;
    EXPECT_EQ(NOT_ALL_INTs_1_t::size, NOT_ALL_INTs_2_t::size - 1);
    EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_1_t, 0>, TL::GetTypeByIndex_R<INTs_t, 3>>));
    //EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_1_t, 1>, TL::GetTypeByIndex_R<INTs_t, 1>>)); // compilation error

    EXPECT_TRUE((std::is_same_v<TL::RemoveFront_R<NOT_ALL_INTs_1_t>, TL::NullType>));

    //using ERROR_1_t = TL::RemoveFront_R<TL::NullType>; // compilation error
    //using ERROR_2_t = TL::RemoveFront_R<int>; // compilation error
}

TEST(TypesList, RemoveByIndex) {
    {
        using NOT_ALL_INTs_t = TL::RemoveByIndex_R<INTs_t, 0>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, INTs_t::size - 1);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<INTs_t, 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<INTs_t, 3>>));
    }
    {
        using NOT_ALL_INTs_t = TL::RemoveByIndex_R<INTs_t, 1>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, INTs_t::size - 1);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<INTs_t, 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<INTs_t, 3>>));
    }
    {
        using NOT_ALL_INTs_t = TL::RemoveByIndex_R<INTs_t, 2>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, INTs_t::size - 1);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<INTs_t, 3>>));
    }
    {
        using NOT_ALL_INTs_t = TL::RemoveByIndex_R<INTs_t, 3>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, INTs_t::size - 1);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<INTs_t, 2>>));
    }
    {
        //using NOT_ALL_INTs_t = TL::RemoveByIndex_R<INTs_t, 4>; // compilation error
        //using NOT_ALL_INTs_t = TL::RemoveByIndex_R<INTs_t, 5>; // compilation error
    }
}

TEST(TypesList, CutFromSize) {
    {
        constexpr uint8_t size = 0;
        //using NOT_ALL_INTs_1_t = TL::CutFromSize_R<ALL_INTs_t, 0, size>; // compilation error
        //using NOT_ALL_INTs_2_t = TL::CutFromSize_R<ALL_INTs_t, 1, size>; // compilation error
        //using NOT_ALL_INTs3__t = TL::CutFromSize_R<ALL_INTs_t, 2, size>; // compilation error
    }
    {
        constexpr uint8_t from = 7, size = 2;
        //using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 6, size = 3;
        //using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 5, size = 4;
        //using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 4, size = 5;
        //using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 3, size = 6;
        //using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 2, size = 7;
        //using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 1, size = 8;
        //using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 0, size = 9;
        //using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 0, size = 8;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, 4>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 5>, TL::GetTypeByIndex_R<ALL_INTs_t, 5>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 6>, TL::GetTypeByIndex_R<ALL_INTs_t, 6>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 7>, TL::GetTypeByIndex_R<ALL_INTs_t, 7>>));
    }
    {
        constexpr uint8_t from = 0, size = 1;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
    }
    {
        constexpr uint8_t from = 1, size = 1;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
    }
    {
        constexpr uint8_t from = 2, size = 1;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
    }
    {
        constexpr uint8_t from = 3, size = 1;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
    }
    {
        constexpr uint8_t from = 4, size = 1;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
    }
    {
        constexpr uint8_t from = 5, size = 1;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
    }
    {
        constexpr uint8_t from = 6, size = 1;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
    }
    {
        constexpr uint8_t from = 7, size = 1;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
    }
    {
        constexpr uint8_t from = 0, size = 3;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 2>>));
    }
    {
        constexpr uint8_t from = 1, size = 3;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 2>>));
    }
    {
        constexpr uint8_t from = 2, size = 3;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 2>>));
    }
    {
        constexpr uint8_t from = 3, size = 3;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 2>>));
    }
    {
        constexpr uint8_t from = 0, size = 4;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 3>>));
    }
    {
        constexpr uint8_t from = 1, size = 4;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 3>>));
    }
    {
        constexpr uint8_t from = 2, size = 4;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 3>>));
    }
    {
        constexpr uint8_t from = 3, size = 4;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 3>>));
    }
    {
        constexpr uint8_t from = 4, size = 4;
        using NOT_ALL_INTs_t = TL::CutFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, from + 3>>));
    }
}

TEST(TypesList, RemoveFromSize) {
    {
        constexpr uint8_t from = 4, size = 0;
        //using ERROR_t = TL::RemoveFromSize_R<char, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 4, size = 0;
        //using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 8, size = 3;
        //using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 4, size = 8;
        //using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>; // compilation error
    }
    {
        constexpr uint8_t from = 0, size = 1;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, size>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 4>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 5>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 5>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 6>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 6>>));
    }
    {
        constexpr uint8_t from = 1, size = 1;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 4>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 5>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 5>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 6>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 6>>));
    }
    {
        constexpr uint8_t from = 2, size = 1;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 4>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 5>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 5>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 6>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 6>>));
    }
    {
        constexpr uint8_t from = 3, size = 1;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 4>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 5>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 5>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 6>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 6>>));
    }
    {
        constexpr uint8_t from = 4, size = 1;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 4>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 5>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 5>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 6>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 6>>));
    }
    {
        constexpr uint8_t from = 5, size = 1;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, 4>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 5>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 5>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 6>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 6>>));
    }
    {
        constexpr uint8_t from = 6, size = 1;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, 4>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 5>, TL::GetTypeByIndex_R<ALL_INTs_t, 5>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 6>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 6>>));
    }
    {
        constexpr uint8_t from = 7, size = 1;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, 4>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 5>, TL::GetTypeByIndex_R<ALL_INTs_t, 5>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 6>, TL::GetTypeByIndex_R<ALL_INTs_t, 6>>));
    }
    {
        constexpr uint8_t from = 0, size = 3;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, size>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 4>>));
    }
    {
        constexpr uint8_t from = 1, size = 3;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 4>>));
    }
    {
        constexpr uint8_t from = 2, size = 3;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 4>>));
    }
    {
        constexpr uint8_t from = 3, size = 3;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 4>>));
    }
    {
        constexpr uint8_t from = 4, size = 3;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 4>>));
    }
    {
        constexpr uint8_t from = 5, size = 3;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, 0>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, 3>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 4>, TL::GetTypeByIndex_R<ALL_INTs_t, 4>>));
    }
    {
        constexpr uint8_t from = 0, size = 4;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, size>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 2>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 3>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 3>>));
    }
    {
        constexpr uint8_t from = 0, size = 5;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, size>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 1>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 2>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 2>>));
    }
    {
        constexpr uint8_t from = 0, size = 6;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, size>>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 1>, TL::GetTypeByIndex_R<ALL_INTs_t, size + 1>>));
    }
    {
        constexpr uint8_t from = 0, size = 7;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<NOT_ALL_INTs_t, 0>, TL::GetTypeByIndex_R<ALL_INTs_t, size>>));
    }
    {
        constexpr uint8_t from = 0, size = 8;
        using NOT_ALL_INTs_t = TL::RemoveFromSize_R<ALL_INTs_t, from, size>;
        EXPECT_EQ(NOT_ALL_INTs_t::size, ALL_INTs_t::size - size);
        EXPECT_TRUE((std::is_same_v<NOT_ALL_INTs_t, TL::NullType>));
    }
}

using RANDOM_TYPE1s_t = TL::CreateTypesList_R<int, int, int, int>;
using RANDOM_TYPE2s_t = TL::CreateTypesList_R<int, int, bool, bool, char, char, float, float>;
using RANDOM_TYPE3s_t = TL::CreateTypesList_R<int, bool, char, float, int, bool, char, float>;
using RANDOM_TYPE4s_t = TL::CreateTypesList_R<char, int, int, char, char, bool, bool, int, float, bool>;

TEST(TypesList, Count) {
    //constexpr uint8_t count_2 = TL::Count_R<int, int>; // compilation error
    //constexpr uint8_t count_2 = TL::Count_R<TL::NullType, int>; // compilation error
    //constexpr uint8_t count_2 = TL::Count_R<TL::NullType, TL::NullType>; // compilation error

    EXPECT_EQ((TL::Count_R<RANDOM_TYPE1s_t, int>), 4);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE2s_t, int>), 2);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE3s_t, int>), 2);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE4s_t, int>), 3);

    EXPECT_EQ((TL::Count_R<RANDOM_TYPE1s_t, bool>), 0);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE2s_t, bool>), 2);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE3s_t, bool>), 2);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE4s_t, bool>), 3);

    EXPECT_EQ((TL::Count_R<RANDOM_TYPE1s_t, char>), 0);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE2s_t, char>), 2);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE3s_t, char>), 2);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE4s_t, char>), 3);

    EXPECT_EQ((TL::Count_R<RANDOM_TYPE1s_t, float>), 0);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE2s_t, float>), 2);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE3s_t, float>), 2);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE4s_t, float>), 1);

    EXPECT_EQ((TL::Count_R<RANDOM_TYPE1s_t, int, bool, char, float>), RANDOM_TYPE1s_t::size);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE2s_t, int, bool, char, float>), RANDOM_TYPE2s_t::size);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE3s_t, int, bool, char, float>), RANDOM_TYPE3s_t::size);
    EXPECT_EQ((TL::Count_R<RANDOM_TYPE4s_t, int, bool, char, float>), RANDOM_TYPE4s_t::size);
}

TEST(TypesList, Remove) {
    {
        using type_t = int;
        constexpr uint8_t quantity = 0;
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<removes_t, TL::NullType>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 1;
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 2;
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 3;
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, int>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 4;
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, int>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 0;
        using R_TYPEs_t = RANDOM_TYPE2s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, float>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 1;
        using R_TYPEs_t = RANDOM_TYPE2s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, float>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 2;
        using R_TYPEs_t = RANDOM_TYPE2s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, RANDOM_TYPE2s_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 7>, float>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 0;
        using R_TYPEs_t = RANDOM_TYPE3s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, float>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 1;
        using R_TYPEs_t = RANDOM_TYPE3s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, float>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 2;
        using R_TYPEs_t = RANDOM_TYPE3s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 7>, float>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 33;
        using R_TYPEs_t = RANDOM_TYPE3s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 7>, float>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 0;
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, bool>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 1;
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 7>, bool>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 2;
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, type_t> + quantity));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 7>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 8>, bool>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 3;
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, RANDOM_TYPE4s_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 7>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 8>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 9>, bool>));
    }
    {
        using type_t = int;
        constexpr uint8_t quantity = 33;
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::Remove_R<R_TYPEs_t, type_t, quantity>;
        EXPECT_EQ(removes_t::size, RANDOM_TYPE4s_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 7>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 8>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 9>, bool>));
    }
}

TEST(TypesList, RemoveAll) {
    {
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::RemoveAll_R<R_TYPEs_t, int>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, bool>));
    }
    {
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::RemoveAll_R<R_TYPEs_t, int, char>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, int, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, bool>));
    }
    {
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::RemoveAll_R<R_TYPEs_t, int, char, bool>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, int, char, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, float>));
    }
    {
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::RemoveAll_R<R_TYPEs_t, int, char, bool, float>;
        EXPECT_EQ(removes_t::size, 0);
        EXPECT_TRUE((std::is_same_v<removes_t, TL::NullType>));
    }
}

TEST(TypesList, RemoveAllCopy) {
    {
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::RemoveAllCopy_R<R_TYPEs_t, int>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, int> + 1));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 6>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 7>, bool>));
    }
    {
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::RemoveAllCopy_R<R_TYPEs_t, int, char>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, int, char> + 2));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 4>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 5>, bool>));
    }
    {
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::RemoveAllCopy_R<R_TYPEs_t, int, char, bool>;
        EXPECT_EQ(removes_t::size, (R_TYPEs_t::size - TL::Count_R<R_TYPEs_t, int, char, bool> + 3));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, float>));
    }
    {
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::RemoveAllCopy_R<R_TYPEs_t, int, char, bool, float>;
        EXPECT_EQ(removes_t::size, 4);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, float>));
    }
}

TEST(TypesList, Refine) {
    {
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using removes_t = TL::Refine_R<R_TYPEs_t>;
        EXPECT_EQ(removes_t::size, 1);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
    }
    {
        using R_TYPEs_t = RANDOM_TYPE2s_t;
        using removes_t = TL::Refine_R<R_TYPEs_t>;
        EXPECT_EQ(removes_t::size, 4);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, float>));
    }
    {
        using R_TYPEs_t = RANDOM_TYPE3s_t;
        using removes_t = TL::Refine_R<R_TYPEs_t>;
        EXPECT_EQ(removes_t::size, 4);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, float>));
    }
    {
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using removes_t = TL::Refine_R<R_TYPEs_t>;
        EXPECT_EQ(removes_t::size, 4);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<removes_t, 3>, float>));
    }
}

TEST(TypesList, Replace) {
    {
        using before_t = int;
        using after_t = double;
        constexpr uint8_t quantity = 0;
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using replaced = TL::Replace_R<R_TYPEs_t, before_t, after_t, quantity>;
        EXPECT_EQ(replaced::size, R_TYPEs_t::size);
        EXPECT_EQ((TL::Count_R<replaced, before_t>), quantity);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 0>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 1>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 2>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 3>, after_t>));
    }
    {
        using before_t = int;
        using after_t = double;
        constexpr uint8_t quantity = 1;
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using replaced = TL::Replace_R<R_TYPEs_t, before_t, after_t, quantity>;
        EXPECT_EQ(replaced::size, R_TYPEs_t::size);
        EXPECT_EQ((TL::Count_R<replaced, before_t>), quantity);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 0>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 1>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 2>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 3>, after_t>));
    }
    {
        using before_t = int;
        using after_t = double;
        constexpr uint8_t quantity = 2;
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using replaced = TL::Replace_R<R_TYPEs_t, before_t, after_t, quantity>;
        EXPECT_EQ(replaced::size, R_TYPEs_t::size);
        EXPECT_EQ((TL::Count_R<replaced, before_t>), quantity);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 0>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 1>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 2>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 3>, after_t>));
    }
    {
        using before_t = int;
        using after_t = double;
        constexpr uint8_t quantity = 3;
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using replaced = TL::Replace_R<R_TYPEs_t, before_t, after_t, quantity>;
        EXPECT_EQ(replaced::size, R_TYPEs_t::size);
        EXPECT_EQ((TL::Count_R<replaced, before_t>), quantity);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 0>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 1>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 2>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 3>, after_t>));
    }
    {
        using before_t = int;
        using after_t = double;
        constexpr uint8_t quantity = 4;
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using replaced = TL::Replace_R<R_TYPEs_t, before_t, after_t, quantity>;
        EXPECT_EQ(replaced::size, R_TYPEs_t::size);
        EXPECT_EQ((TL::Count_R<replaced, before_t>), quantity);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 0>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 1>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 2>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 3>, before_t>));
    }
    {
        using before_t = int;
        using after_t = double;
        constexpr uint8_t quantity = UINT8_MAX;
        using R_TYPEs_t = RANDOM_TYPE1s_t;
        using replaced = TL::Replace_R<R_TYPEs_t, before_t, after_t, quantity>;
        EXPECT_EQ(replaced::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 0>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 1>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 2>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 3>, before_t>));
    }
    {
        using before_t = int;
        using after_t = double;
        constexpr uint8_t quantity = 0;
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using replaced = TL::Replace_R<R_TYPEs_t, before_t, after_t, quantity>;
        EXPECT_EQ(replaced::size, R_TYPEs_t::size);
        EXPECT_EQ((TL::Count_R<replaced, before_t>), quantity);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 1>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 2>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 6>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 7>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 8>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 9>, bool>));
    }
    {
        using before_t = int;
        using after_t = double;
        constexpr uint8_t quantity = 1;
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using replaced = TL::Replace_R<R_TYPEs_t, before_t, after_t, quantity>;
        EXPECT_EQ(replaced::size, R_TYPEs_t::size);
        EXPECT_EQ((TL::Count_R<replaced, before_t>), quantity);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 1>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 2>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 6>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 7>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 8>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 9>, bool>));
    }
    {
        using before_t = int;
        using after_t = double;
        constexpr uint8_t quantity = 2;
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using replaced = TL::Replace_R<R_TYPEs_t, before_t, after_t, quantity>;
        EXPECT_EQ(replaced::size, R_TYPEs_t::size);
        EXPECT_EQ((TL::Count_R<replaced, before_t>), quantity);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 1>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 2>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 6>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 7>, after_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 8>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 9>, bool>));
    }
    {
        using before_t = int;
        using after_t = double;
        constexpr uint8_t quantity = 3;
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using replaced = TL::Replace_R<R_TYPEs_t, before_t, after_t, quantity>;
        EXPECT_EQ(replaced::size, R_TYPEs_t::size);
        EXPECT_EQ((TL::Count_R<replaced, before_t>), quantity);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 1>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 2>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 6>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 7>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 8>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 9>, bool>));
    }
    {
        using before_t = int;
        using after_t = double;
        constexpr uint8_t quantity = INT8_MAX;
        using R_TYPEs_t = RANDOM_TYPE4s_t;
        using replaced = TL::Replace_R<R_TYPEs_t, before_t, after_t, quantity>;
        EXPECT_EQ(replaced::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 1>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 2>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 5>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 6>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 7>, before_t>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 8>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<replaced, 9>, bool>));
    }
}

TEST(TypesList, Swap) {
    using TEST_TYPEs_t = TL::CreateTypesList_R<char, int, bool, double, float>;
    {
        constexpr uint8_t index1 = 0;
        constexpr uint8_t index2 = 1;
        using R_TYPEs_t = TEST_TYPEs_t;
        using swapped = TL::Swap_R<R_TYPEs_t, index1, index2>;
        EXPECT_EQ(swapped::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 1>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 3>, double>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 4>, float>));
    }
    {
        constexpr uint8_t index1 = 0;
        constexpr uint8_t index2 = 2;
        using R_TYPEs_t = TEST_TYPEs_t;
        using swapped = TL::Swap_R<R_TYPEs_t, index1, index2>;
        EXPECT_EQ(swapped::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 0>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 2>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 3>, double>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 4>, float>));
    }
    {
        constexpr uint8_t index1 = 0;
        constexpr uint8_t index2 = 3;
        using R_TYPEs_t = TEST_TYPEs_t;
        using swapped = TL::Swap_R<R_TYPEs_t, index1, index2>;
        EXPECT_EQ(swapped::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 0>, double>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 3>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 4>, float>));
    }
    {
        constexpr uint8_t index1 = 0;
        constexpr uint8_t index2 = 4;
        using R_TYPEs_t = TEST_TYPEs_t;
        using swapped = TL::Swap_R<R_TYPEs_t, index1, index2>;
        EXPECT_EQ(swapped::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 0>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 3>, double>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 4>, char>));
    }
    {
        constexpr uint8_t index1 = 0;
        constexpr uint8_t index2 = 5;
        using R_TYPEs_t = TEST_TYPEs_t;
        //using swapped = TL::Swap_R<R_TYPEs_t, index1, index2>; // compilation error
    }
    {
        constexpr uint8_t index1 = 3;
        constexpr uint8_t index2 = 2;
        using R_TYPEs_t = TEST_TYPEs_t;
        //using swapped = TL::Swap_R<R_TYPEs_t, index1, index2>; // compilation error
    }
    {
        constexpr uint8_t index1 = 1;
        constexpr uint8_t index2 = 2;
        using R_TYPEs_t = TEST_TYPEs_t;
        using swapped = TL::Swap_R<R_TYPEs_t, index1, index2>;
        EXPECT_EQ(swapped::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 1>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 2>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 3>, double>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 4>, float>));
    }
    {
        constexpr uint8_t index1 = 3;
        constexpr uint8_t index2 = 4;
        using R_TYPEs_t = TEST_TYPEs_t;
        using swapped = TL::Swap_R<R_TYPEs_t, index1, index2>;
        EXPECT_EQ(swapped::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 3>, float>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 4>, double>));
    }
    {
        constexpr uint8_t index1 = 0;
        constexpr uint8_t index2 = 1;
        using R_TYPEs_t = TL::CreateTypesList_R<int, char>;
        using swapped = TL::Swap_R<R_TYPEs_t, index1, index2>;
        EXPECT_EQ(swapped::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 1>, int>));
    }
}

TEST(TypesList, SwapTypes) {
    using TEST_TYPEs_t = TL::CreateTypesList_R<int, char, bool, bool, double, float>;
    //using swapped = TL::SwapTypes_R<TEST_TYPEs_t, int, bool>; // compilation error
    //using swapped = TL::SwapTypes_R<TEST_TYPEs_t, bool, int>; // compilation error
    {
        using Type1 = int;
        using Type2 = char;
        using R_TYPEs_t = TEST_TYPEs_t;
        using swapped = TL::SwapTypes_R<R_TYPEs_t, Type1, Type2>;
        EXPECT_EQ(swapped::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 3>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 4>, double>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 5>, float>));
    }
    {
        using Type1 = char;
        using Type2 = int;
        using R_TYPEs_t = TEST_TYPEs_t;
        using swapped = TL::SwapTypes_R<R_TYPEs_t, Type1, Type2>;
        EXPECT_EQ(swapped::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 0>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 1>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 3>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 4>, double>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 5>, float>));
    }
    {
        using Type1 = char;
        using Type2 = double;
        using R_TYPEs_t = TEST_TYPEs_t;
        using swapped = TL::SwapTypes_R<R_TYPEs_t, Type1, Type2>;
        EXPECT_EQ(swapped::size, R_TYPEs_t::size);
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 0>, int>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 1>, double>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 2>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 3>, bool>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 4>, char>));
        EXPECT_TRUE((std::is_same_v<TL::GetTypeByIndex_R<swapped, 5>, float>));
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
