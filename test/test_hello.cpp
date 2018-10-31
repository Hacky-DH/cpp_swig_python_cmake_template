#include "src/utils.h"
#include "src/hello.h"
#include <gtest/gtest.h>

class HelloTest : public testing::Test {
protected:
    static Hello hello;
    static void SetUpTestCase(){
        set_log_dir("./");
    }
    static void TearDownTestCase(){
    }
    virtual void SetUp(){
    }
    virtual void TearDown(){
    }

    void cmp_file_size(const char* tf, size_t size){
        struct stat st;
        stat(tf, &st);
        EXPECT_EQ(st.st_size, size);
    }
};

Hello HelloTest::hello;

TEST_F(HelloTest, login){
    ASSERT_TRUE(hello.login("hello","hello"));
}

TEST_F(HelloTest, hello){
    EXPECT_STREQ("hello from cpp", hello.hello().c_str());
}

TEST_F(HelloTest, add){
    std::vector<int> v{1,2,3,4,5};
    EXPECT_EQ(15, hello.add(v));
}

TEST_F(HelloTest, add1){
    std::vector<int> v;
    EXPECT_EQ(0, hello.add(v));
}

TEST_F(HelloTest, split){
    std::vector<std::string> res = hello.split("ab bc cd", " ");
    EXPECT_EQ(3, res.size());
    EXPECT_STREQ("ab", res[0].c_str());
    EXPECT_STREQ("bc", res[1].c_str());
    EXPECT_STREQ("cd", res[2].c_str());
}
