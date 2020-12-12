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
    
    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 3>::Result, uint8_t>));
    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 2>::Result, uint16_t>));
    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 1>::Result, uint32_t>));
    EXPECT_FALSE(bool(std::is_same_v<TL::GetTypeByIndex<UINTs_t, 0>::Result, uint64_t>));
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
