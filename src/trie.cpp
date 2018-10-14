#include "trie.h"


#define FLAG_ROOT (0x1 << 0)
#define FLAG_LEAF (0x1 << 1)


TrieNode::TrieNode() :flag(FLAG_ROOT | FLAG_LEAF){

}

bool TrieNode::is_root()
{
    return flag & FLAG_ROOT;
}

bool TrieNode::is_root(bool root)
{
    if (root) {
        flag |= FLAG_ROOT;
    } else {
        flag &= ~FLAG_ROOT;
    }
}

bool TrieNode::is_leaf(bool leaf)
{
    if (leaf) {
        flag |= FLAG_LEAF;
    } else {
        flag &= ~FLAG_LEAF;
    }
}

bool TrieNode::is_leaf()
{
    return flag & FLAG_LEAF;
}