#include "ahocorasick/ahocorasick.h"
#include "Node.h"
#include "DebugLog.h"
#include <deque>

AcAutomata::AcAutomata(const std::vector<std::string>& patterns)
    : patterns_(patterns),
      root_(NULL)
{
    build_trie();
    build_fail();

}

AcAutomata::~AcAutomata()
{
    if (root_) {
        delete (root_);
    }
}

void AcAutomata::build_trie()
{
    for (size_t i = 0; i < patterns_.size(); ++i) {
        if (patterns_[i].empty()) {
            continue;
        }

        if (!root_) {
            root_ = new TrieNode(0);
        }
        root_->insert(patterns_[i].c_str(), patterns_[i].size());
    }
}

void AcAutomata::build_fail()
{

    std::deque<TrieNode*> nodes;
    nodes.push_back(root_);

    //先处理第一层
    while (true) {
        TrieNode* node = nodes.front();
        if (node->depth > 0) {
            //LOG_DEBUG("level = %d, prefix = %s, %c", node->depth, node->prefix_->to_string().c_str(), node->node_);
        }
        if (node->depth > 1) {
            break;
        }
        nodes.pop_front();

        node->failure_node = root_;

        for (int i = 0; i < 256; ++i) {
            TrieNode* child = node->all_nodes[i];
            if (!child) {
                continue;
            }
            nodes.push_back(child);
        }
    }

    while (!nodes.empty()) {
        TrieNode* node = nodes.front();
        nodes.pop_front();
        assert(node->depth > 1);


        TrieNode* fail = node->parent->failure_node;
        do {
            char state = node->state;
            TrieNode* child = fail->next(state);
            if (child && child->state == state) {
                fail = child;
                break;
            }
            else {
                fail = fail->failure_node;
            }
        }
        while (!fail->is_root());

        node->failure_node = fail;

        for (int i = 0; i < 256; ++i) {
            TrieNode* n = node->all_nodes[i];
            if (!n) {
                continue;
            }
            nodes.push_back(n);
        }
    }
}

void AcAutomata::search(const char* data, int len, match_callback callback, void* ctx)
{
    TrieNode* curr = root_;

    for (int position = 0; position < len;) {
        char state = data[position];
        TrieNode* next = curr->next(state);
        if (!next) {
            if (!curr->is_root())
                curr = curr->failure_node;
            else {
                position++;
            }
        }
        else {
            curr = next;
            position++;
        }

        if (curr->is_final()) {
            bool is_continue = callback(ctx, curr->prefix);
            if (is_continue) {
                continue;
            }
            else {
                break;
            }
        }
    }
}

void AcAutomata::search_all(const char* data, int len, std::vector<Slice>& patterns)
{
    TrieNode* curr = root_;

    for (int position = 0; position < len;) {
        char state = data[position];
        TrieNode* next = curr->next(state);
        if (!next) {
            if (!curr->is_root())
                curr = curr->failure_node;
            else {
                position++;
            }
        }
        else {
            curr = next;
            position++;
        }

        if (curr->is_final()) {
            curr->matched(true);
        }
    }

    std::deque<TrieNode*> nodes;
    nodes.push_back(root_);
    while (!nodes.empty()) {
        TrieNode* node = nodes.front();
        if (node->matched()) {
            patterns.push_back(*node->prefix);
            node->matched(false);
        }
        nodes.pop_front();

        for (int i = 0; i < 256; ++i) {
            TrieNode* n = node->all_nodes[i];
            if (!n) {
                continue;
            }
            nodes.push_back(n);
        }
    }
}