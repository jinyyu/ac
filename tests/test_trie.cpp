#include <trie.h>
#include <stdio.h>
#include <gtest/gtest.h>

TEST(test_trie, test_flag)
{
    TrieNode n(0);
    ASSERT_TRUE(n.is_root());
    ASSERT_TRUE(n.is_leaf());
    ASSERT_FALSE(n.is_accept());

    n.is_accept(true);
    ASSERT_TRUE(n.is_accept());

    n.is_root(false);
    ASSERT_FALSE(n.is_root());
    ASSERT_TRUE(n.is_leaf());
    ASSERT_TRUE(n.is_accept());


    n.is_leaf(false);
    ASSERT_FALSE(n.is_root());
    ASSERT_FALSE(n.is_leaf());
    ASSERT_TRUE(n.is_accept());
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

