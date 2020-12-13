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


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
