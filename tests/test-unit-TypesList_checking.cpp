#include <gtest/gtest.h>
#include <TypesList.hpp>

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


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}