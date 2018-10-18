#include "trie.h"
#include <string.h>
#include <assert.h>
#include "DebugLog.h"

#define FLAG_ROOT   (0x1 << 0)
#define FLAG_LEAF   (0x1 << 1)
#define FLAG_ACCEPT (0x1 << 2)

TrieNode::TrieNode(int level)
    : flag_(FLAG_ROOT | FLAG_LEAF),
      level_(level),
      parent_(NULL),
      prefix_(NULL),
      fail_(NULL)
{
    is_accept(false);
    memset(nodes_, 0, sizeof(nodes_));
    if (level) {
        is_root(false);
    }
}

TrieNode::~TrieNode()
{
    if (prefix_) {
        delete (prefix_);
    }
}

bool TrieNode::is_root()
{
    return flag_ & FLAG_ROOT;
}

bool TrieNode::is_root(bool root)
{
    if (root) {
        flag_ |= FLAG_ROOT;
    }
    else {
        flag_ &= ~FLAG_ROOT;
    }
}

bool TrieNode::is_leaf(bool leaf)
{
    if (leaf) {
        flag_ |= FLAG_LEAF;
    }
    else {
        flag_ &= ~FLAG_LEAF;
    }
}

bool TrieNode::is_leaf()
{
    return flag_ & FLAG_LEAF;
}

bool TrieNode::is_accept(bool accept)
{
    if (accept) {
        flag_ |= FLAG_ACCEPT;
    }
    else {
        flag_ &= ~FLAG_ACCEPT;
    }
}

bool TrieNode::is_accept()
{
    return flag_ & FLAG_ACCEPT;
}

void TrieNode::insert(const char* data, int len)
{
    int prefix_len = level_ + 1;

    if (level_ == len) {
        is_accept(true);
        return;
    }

    char c = data[level_];
    TrieNode* node = nodes_[c];
    if (!node) {
        //new node
        this->is_leaf(false);
        node = new TrieNode(prefix_len);
        node->parent_ = this;
        nodes_[c] = node;
        node->prefix_ = new Slice(data, prefix_len);
        LOG_DEBUG("level = %d, prefix = %s", level_ + 1, node->prefix_->to_string().c_str());
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
    TrieNode* node = nodes_[c];
    if (!node) {
        return NULL;
    }
    return node->search(data + 1, len - 1);
}