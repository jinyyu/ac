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

    const char* str = "shr";

    bool ok = root_->search(str, strlen(str));

    LOG_DEBUG("OK = %d", ok);
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

        for (int i = 0; i < 256; ++i) {
            TrieNode* n = node->nodes_[i];
            if (!n) {
                continue;
            }

            if (n->level_ <= 1) {
                n->fail_ = root_;
            }
            else {
                assert(n->prefix_->size() > 1);
                n->fail_ = root_;

                for (int i = 1; i < n->prefix_->size(); ++i) {
                    Slice data(n->prefix_->data()+1, n->prefix_->size() - 1);

                    TrieNode* failed_node = root_->search(data.data(), data.size());
                    if (failed_node) {
                        LOG_DEBUG("prefix = %s, found %s", n->prefix_->to_string().c_str(), data.to_string().c_str());
                        n->fail_ = failed_node;
                        break;
                    }
                }
            }
            nodes.push_back(n);
        }
    }
}