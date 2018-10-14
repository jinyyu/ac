#ifndef AHO_CORASICK_PROJECT_TRIE_H
#define AHO_CORASICK_PROJECT_TRIE_H
#include <stdint.h>

struct TrieNode
{
    explicit TrieNode();

    uint32_t flag;


    bool is_root(bool root);
    bool is_root();

    bool is_leaf(bool leaf);
    bool is_leaf();


};

#endif //AHO_CORASICK_PROJECT_TRIE_H
