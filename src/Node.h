#ifndef AHO_CORASICK_PROJECT_NODE_H
#define AHO_CORASICK_PROJECT_NODE_H
#include <stdint.h>
#include "ahocorasick/Slice.h"

class TrieNode
{
public:
    explicit TrieNode(int level);

    ~TrieNode();

    void is_root(bool root);
    bool is_root();

    void is_leaf(bool leaf);
    bool is_leaf();


    void is_final(bool final);
    bool is_final();

    void matched(bool matched);
    bool matched();

    TrieNode* next(char state)
    {
        return all_nodes[(uint8_t)state];
    }

    TrieNode* search(const char* data, int len);

    void insert(const char* data, int len);
public:
    char state;
    uint32_t flag;
    int depth;
    Slice* prefix;
    TrieNode* all_nodes[256];
    TrieNode* parent;
    TrieNode* failure_node;
};

#endif //AHO_CORASICK_PROJECT_TRIE_H
