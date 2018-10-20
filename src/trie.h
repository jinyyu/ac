#ifndef AHO_CORASICK_PROJECT_TRIE_H
#define AHO_CORASICK_PROJECT_TRIE_H
#include <stdint.h>
#include "ahocorasick/Slice.h"

class TrieNode
{
public:
    explicit TrieNode(int level);

    ~TrieNode();

    bool is_root(bool root);
    bool is_root();

    bool is_leaf(bool leaf);
    bool is_leaf();

    bool is_accept(bool accept);
    bool is_accept();

    TrieNode* next(char c);

    TrieNode* search(const char* data, int len);

    void insert(const char* data, int len);

    std::string prefix();
public:
    char character_;
    uint32_t flag_;
    int level_;
    Slice* prefix_;
    TrieNode* nodes_[256];
    TrieNode* parent_;
    TrieNode* fail_;
};

#endif //AHO_CORASICK_PROJECT_TRIE_H
