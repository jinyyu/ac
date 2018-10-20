#include "ac/ac.h"
#include "trie.h"
#include "DebugLog.h"
#include <deque>

ACMatcher::ACMatcher(const std::vector<std::string>& strings)
    : strings_(strings),
      root_(NULL)
{
    build_trie();
    build_fail();

}

ACMatcher::~ACMatcher()
{
    if (root_) {
        delete (root_);
    }
}

void ACMatcher::build_trie()
{
    for (int i = 0; i < strings_.size(); ++i) {
        if (strings_[i].empty()) {
            continue;
        }

        if (!root_) {
            root_ = new TrieNode(0);
        }
        root_->insert(strings_[i].c_str(), strings_[i].size());
    }
}

void ACMatcher::build_fail()
{

    std::deque<TrieNode*> nodes;
    nodes.push_back(root_);

    //先处理第一层
    while (true) {
        TrieNode* node = nodes.front();
        if (node->level_ > 0) {
            //LOG_DEBUG("level = %d, prefix = %s, %c", node->level_, node->prefix_->to_string().c_str(), node->node_);
        }
        if (node->level_ > 1) {
            break;
        }
        nodes.pop_front();

        node->fail_ = root_;

        for (int i = 0; i < 256; ++i) {
            TrieNode* child = node->nodes_[i];
            if (!child) {
                continue;
            }
            nodes.push_back(child);
        }
    }

    while (!nodes.empty()) {
        TrieNode* node = nodes.front();
        nodes.pop_front();
        assert(node->level_ > 1);


        TrieNode* fail = node->parent_->fail_;
        do {
            char c = node->character_;
            TrieNode* child = fail->nodes_[c];
            if (child && child->character_ == c) {
                fail = child;
                LOG_DEBUG("%s -> %s", node->prefix_->to_string().c_str(), fail->prefix_->to_string().c_str());
                break;
            }
            else {
                fail = fail->fail_;
            }
        }
        while (!fail->is_root());
        node->fail_ = fail;

        for (int i = 0; i < 256; ++i) {
            TrieNode* n = node->nodes_[i];
            if (!n) {
                continue;
            }
            nodes.push_back(n);
        }
        LOG_DEBUG("level = %d, prefix = %s, %c", node->level_, node->prefix_->to_string().c_str(), node->character_);
    }
}

Slice* ACMatcher::match_any(const char* data, int len)
{
    int position;
    TrieNode* curr;
    TrieNode* next;

    position = 0;
    curr = root_;

    /* This is the main search loop.
     * it must be keep as lightweight as possible. */
    while (position < len) {
        if (!(next = curr->next(data[position]))) {
            if (curr->fail_)
                curr = curr->fail_;
            else {
                position++;
            }
        }
        else {
            curr = next;
            position++;
        }

        if (curr->is_accept()) {
            return curr->prefix_;
        }
    }
    return NULL;
}