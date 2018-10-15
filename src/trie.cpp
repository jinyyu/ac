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
      prefix_(NULL)
{
    is_accept(false);
    memset(nodes_, 0, sizeof(nodes_));
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
    if (!prefix_) {
        prefix_ = new Slice(data , level_);
    }




    if (len - level_ == 1) {
        //last level
        is_leaf(true);
        is_accept(true);
        return;
    }

    char c = data[level_];
    LOG_DEBUG("%c level = %d, prefix = %s",c, level_,  prefix_->to_string().c_str());

    TrieNode* node = nodes_[c];
    if (!node) {
        node = new TrieNode(level_ + 1);
        node->parent_ = this;
        nodes_[c] = node;
    }

    node->insert(data, len);
}