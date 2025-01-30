#include "gtest/gtest.h"
#include "../src/sorted_list.h"

template <typename T>
class SL_Test : public ::testing::Test{ protected: T list; };
using SL_Types = ::testing::Types<SortedArrayList, SortedLinkedList>;

// 'this->list' for SAL/SLL
TYPED_TEST_SUITE(SL_Test, SL_Types);
TYPED_TEST(SL_Test, empty_list) {
    EXPECT_TRUE(this->list.is_empty());
    EXPECT_FALSE(this->list.is_full()); }
TYPED_TEST(SL_Test, insert){
    this->list.insert("hello");
    EXPECT_FALSE(this->list.is_empty());
    EXPECT_TRUE(this->list.find("hello")); }
TYPED_TEST(SL_Test, find){
    this->list.insert("test");
    this->list.insert("zeta");
    EXPECT_TRUE(this->list.find("test"));
    EXPECT_TRUE(this->list.find("zeta"));
    EXPECT_FALSE(this->list.find("beta")); }
TYPED_TEST(SL_Test, remove){
    this->list.insert("peanut");
    this->list.insert("butter");
    this->list.remove("butter");
    EXPECT_FALSE(this->list.find("butter"));
    EXPECT_TRUE(this->list.find("peanut"));
    this->list.remove("peanut");
    EXPECT_TRUE(this->list.is_empty()); }
TYPED_TEST(SL_Test, print) {
    this->list.insert("foo");
    this->list.insert("bar");
    testing::internal::CaptureStdout();
    std::cout << this->list; 
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "bar foo "); }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); }
