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

    while (!nodes.empty()) {
        TrieNode* node = nodes.front();
        nodes.pop_front();
        node->fail_ = root_;

        for (int i = 0; i < 256; ++i) {
            TrieNode* n = node->nodes_[i];
            if (!n) {
                continue;
            }
            nodes.push_back(n);
        }


        if (node->level_ <= 1) {
            continue;
        }

        assert(node->prefix_->size() >1);

        for (int i = 1; i < node->prefix_->size(); ++i) {
            Slice data(node->prefix_->data() + i, node->prefix_->size() - i);

            TrieNode* failed_node = root_->search(data.data(), data.size());
            if (failed_node) {
                LOG_DEBUG("%s -> %s", node->prefix_->to_string().c_str(), data.to_string().c_str());
                node->fail_ = failed_node;
                break;
            }
        }

    }
}