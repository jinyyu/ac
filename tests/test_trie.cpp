#include <trie.h>
#include <stdio.h>
#include <gtest/gtest.h>

TEST(test_flag, test_flag)
{
    TrieNode n;
    ASSERT_TRUE(n.is_root());
    ASSERT_TRUE(n.is_leaf());

    n.is_root(false);
    ASSERT_FALSE(n.is_root());
    ASSERT_TRUE(n.is_leaf());


    n.is_leaf(false);
    ASSERT_FALSE(n.is_root());
    ASSERT_FALSE(n.is_leaf());

}


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

