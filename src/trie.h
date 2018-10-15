#ifndef AHO_CORASICK_PROJECT_TRIE_H
#define AHO_CORASICK_PROJECT_TRIE_H
#include <stdint.h>
#include "Slice.h"

class TrieNode
{
public:
    explicit TrieNode(int level);

    bool is_root(bool root);
    bool is_root();

    bool is_leaf(bool leaf);
    bool is_leaf();

    bool is_accept(bool accept);
    bool is_accept();

    void insert(const char* data, int len);

    int level() { return level_; }

private:
    uint32_t flag_;
    int level_;
    Slice* prefix_;
    TrieNode* nodes_[256];
    TrieNode* parent_;
};

#endif //AHO_CORASICK_PROJECT_TRIE_H
