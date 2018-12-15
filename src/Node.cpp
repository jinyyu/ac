#include "Node.h"
#include <string.h>
#include <assert.h>
#include "DebugLog.h"

#define FLAG_ROOT   (0x01 << 0)
#define FLAG_LEAF   (0x01 << 1)
#define FLAG_FINAL  (0x01 << 2)
#define FLAG_MATCHED  (0x01 << 3)

void TrieNode::is_root(bool root)
{
    if (root) {
        flag |= FLAG_ROOT;
    }
    else {
        flag &= ~FLAG_ROOT;
    }
}

bool TrieNode::is_root()
{
    return flag & FLAG_ROOT;
}

void TrieNode::is_leaf(bool leaf)
{
    if (leaf) {
        flag |= FLAG_LEAF;
    }
    else {
        flag &= ~FLAG_LEAF;
    }
}

bool TrieNode::is_leaf()
{
    return flag & FLAG_LEAF;
}

void TrieNode::is_final(bool final)
{
    if (final) {
        flag |= FLAG_FINAL;
    }
    else {
        flag &= ~FLAG_FINAL;
    }
}

bool TrieNode::is_final()
{
    return flag & FLAG_FINAL;
}

void TrieNode::matched(bool matched)
{
    if (matched) {
        flag |= FLAG_MATCHED;
    }
    else {
        flag &= ~FLAG_MATCHED;
    }
}

bool TrieNode::matched()
{
    return flag & FLAG_MATCHED;
}

TrieNode::TrieNode(int level)
    : state(0),
      flag(FLAG_ROOT | FLAG_LEAF),
      depth(level),
      prefix(NULL),
      parent(NULL),
      failure_node(NULL)
{
    is_final(false);
    memset(all_nodes, 0, sizeof(all_nodes));
    if (level) {
        is_root(false);
    }
}

TrieNode::~TrieNode()
{
    if (prefix) {
        delete (prefix);
    }
    for (int i = 0; i < 256; ++i) {
        if (all_nodes[i]) {
            delete (all_nodes[i]);
        }
    }
}

void TrieNode::insert(const char* data, int len)
{
    int prefix_len = depth + 1;

    if (depth == len) {
        is_final(true);
        return;
    }

    char c = data[depth];
    TrieNode* node = all_nodes[(uint8_t)c];
    if (!node) {
        //new node
        this->is_leaf(false);
        node = new TrieNode(prefix_len);
        node->state = c;
        node->parent = this;
        all_nodes[(uint8_t)c] = node;
        node->prefix = new Slice(data, prefix_len);
    }

    node->insert(data, len);
}

TrieNode* TrieNode::search(const char* data, int len)
{
    if (len == 0) {
        return this;
    }

    if (is_leaf()) {
        return NULL;
    }

    char c = data[0];
    TrieNode* node = all_nodes[(uint8_t)c];
    if (!node) {
        return NULL;
    }
    return node->search(data + 1, len - 1);
}