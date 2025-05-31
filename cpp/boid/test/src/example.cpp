#include <gtest/gtest.h>

using namespace std;

class ExampleTest : public ::testing::Test {
    virtual void SetUp() override {

    }

    virtual void TearDown() override {

    }
protected:
    int x = 5;
    static int echoInt(int num) {
        return num;
    }

};

TEST_F(ExampleTest, MathTest) {
    EXPECT_EQ(5*5, 25);
    EXPECT_EQ(0*5, 0);
    EXPECT_EQ(1*5, 5);
}

TEST_F(ExampleTest, EchoTest) {
    EXPECT_EQ(5, x);
    EXPECT_EQ(33, echoInt(33));
    EXPECT_EQ(5*5, 25);
    EXPECT_EQ(0*5, 0);
    EXPECT_EQ(1*5, 5);
}