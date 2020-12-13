#include <gtest/gtest.h>
#include <TypesList.hpp>

using UINTs_t = TL::CreateTypesList<uint8_t, uint16_t, uint32_t, uint64_t>::Result;
using INTs_t = TL::CreateTypesList<int8_t, int16_t, int32_t, int64_t>::Result;


TEST(TypesList, Size) {
    EXPECT_EQ(UINTs_t::size, 4);
    EXPECT_EQ(INTs_t::size, 4);
}


TEST(TypesList, GetTypeByIndex) {
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 0>::Result, uint8_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 1>::Result, uint16_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 2>::Result, uint32_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 3>::Result, uint64_t>));
    //EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 4>::Result, uint64_t>)); // compilation error

    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 3>::Result, uint8_t>));
    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 2>::Result, uint16_t>));
    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 1>::Result, uint32_t>));
    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 0>::Result, uint64_t>));
    //EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 11>::Result, uint64_t>)); // compilation error

    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<INTs_t, 0>::Result, int8_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<INTs_t, 1>::Result, int16_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<INTs_t, 2>::Result, int32_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<INTs_t, 3>::Result, int64_t>));
    //EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<INTs_t, 5>::Result, int64_t>)); // compilation error

    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<INTs_t, 3>::Result, int8_t>));
    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<INTs_t, 2>::Result, int16_t>));
    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<INTs_t, 1>::Result, int32_t>));
    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<INTs_t, 0>::Result, int64_t>));
    //EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<INTs_t, 8>::Result, int64_t>)); // compilation error
}


TEST(TypesList, GetIndexByType) {
    EXPECT_EQ(uint8_t(TL::GetIndexByType<UINTs_t, uint8_t>::Result), 0);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<UINTs_t, uint16_t>::Result), 1);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<UINTs_t, uint32_t>::Result), 2);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<UINTs_t, uint64_t>::Result), 3);
    //EXPECT_EQ(uint8_t(TL::GetIndexByType<UINTs_t, char>::Result), 3); // compilation error

    EXPECT_NE(uint8_t(TL::GetIndexByType<UINTs_t, uint8_t>::Result), 3);
    EXPECT_NE(uint8_t(TL::GetIndexByType<UINTs_t, uint16_t>::Result), 2);
    EXPECT_NE(uint8_t(TL::GetIndexByType<UINTs_t, uint32_t>::Result), 1);
    EXPECT_NE(uint8_t(TL::GetIndexByType<UINTs_t, uint64_t>::Result), 0);
    //EXPECT_NE(uint8_t(TL::GetIndexByType<UINTs_t, bool>::Result), 0); // compilation error

    EXPECT_EQ(uint8_t(TL::GetIndexByType<INTs_t, int8_t>::Result), 0);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<INTs_t, int16_t>::Result), 1);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<INTs_t, int32_t>::Result), 2);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<INTs_t, int64_t>::Result), 3);
    //EXPECT_EQ(uint8_t(TL::GetIndexByType<INTs_t, double>::Result), 3); // compilation error

    EXPECT_NE(uint8_t(TL::GetIndexByType<INTs_t, int8_t>::Result), 3);
    EXPECT_NE(uint8_t(TL::GetIndexByType<INTs_t, int16_t>::Result), 2);
    EXPECT_NE(uint8_t(TL::GetIndexByType<INTs_t, int32_t>::Result), 1);
    EXPECT_NE(uint8_t(TL::GetIndexByType<INTs_t, int64_t>::Result), 0);
    //EXPECT_NE(uint8_t(TL::GetIndexByType<INTs_t, std::string>::Result), 0); // compilation error
}


TEST(TypesList, IsInList) {
    EXPECT_TRUE(bool(TL::IsInList<UINTs_t, uint8_t>::Result));
    EXPECT_TRUE(bool(TL::IsInList<UINTs_t, uint16_t>::Result));
    EXPECT_TRUE(bool(TL::IsInList<UINTs_t, uint32_t>::Result));
    EXPECT_TRUE(bool(TL::IsInList<UINTs_t, uint64_t>::Result));

    EXPECT_FALSE(bool(TL::IsInList<UINTs_t, int8_t>::Result));
    EXPECT_FALSE(bool(TL::IsInList<UINTs_t, int16_t>::Result));
    EXPECT_FALSE(bool(TL::IsInList<UINTs_t, int32_t>::Result));
    EXPECT_FALSE(bool(TL::IsInList<UINTs_t, int64_t>::Result));
}


TEST(TypesList, AppendBack) {
    // using INT8_t_and_INT16_t = TL::AppendBack<int8_t, int16_t>::Result; // compilation error
    
    using INT8_t_and_INT16_t = TL::AppendBack<TL::CreateTypesList<int8_t>::Result, int16_t>::Result;
    EXPECT_EQ(INT8_t_and_INT16_t::size, 2);
    EXPECT_TRUE(bool(TL::IsInList<INT8_t_and_INT16_t, int8_t>::Result));
    EXPECT_TRUE(bool(TL::IsInList<INT8_t_and_INT16_t, int16_t>::Result));
    EXPECT_EQ(uint8_t(TL::GetIndexByType<INT8_t_and_INT16_t, int8_t>::Result), 0);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<INT8_t_and_INT16_t, int16_t>::Result), 1);
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<INT8_t_and_INT16_t, 0>::Result, int8_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<INT8_t_and_INT16_t, 1>::Result, int16_t>));

    using INTs_with_char_t = TL::AppendBack<INTs_t, char>::Result;
    EXPECT_TRUE(bool(TL::IsInList<INTs_with_char_t, char>::Result));
    EXPECT_EQ(INTs_with_char_t::size, INTs_t::size + 1);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<INTs_with_char_t, char>::Result), INTs_with_char_t::size - 1);
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<INTs_with_char_t, INTs_with_char_t::size - 1>::Result, char>));

    using ALL_INTs_t = TL::AppendBack<INTs_t, UINTs_t>::Result;
    EXPECT_EQ(ALL_INTs_t::size, INTs_t::size + UINTs_t::size);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<ALL_INTs_t, int8_t>::Result), 0);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<ALL_INTs_t, int16_t>::Result), 1);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<ALL_INTs_t, int32_t>::Result), 2);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<ALL_INTs_t, int64_t>::Result), 3);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<ALL_INTs_t, uint8_t>::Result), 4);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<ALL_INTs_t, uint16_t>::Result), 5);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<ALL_INTs_t, uint32_t>::Result), 6);
    EXPECT_EQ(uint8_t(TL::GetIndexByType<ALL_INTs_t, uint64_t>::Result), 7);
    //EXPECT_EQ(uint8_t(TL::GetIndexByType<ALL_INTs_t, char>::Result), 8); // compilation error
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<ALL_INTs_t, 0>::Result, int8_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<ALL_INTs_t, 1>::Result, int16_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<ALL_INTs_t, 2>::Result, int32_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<ALL_INTs_t, 3>::Result, int64_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<ALL_INTs_t, 4>::Result, uint8_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<ALL_INTs_t, 5>::Result, uint16_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<ALL_INTs_t, 6>::Result, uint32_t>));
    EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<ALL_INTs_t, 7>::Result, uint64_t>));
    //EXPECT_TRUE(bool(std::is_same_v<TL::GetTypeByIndex<ALL_INTs_t, 8>::Result, char>)); // compilation error
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
