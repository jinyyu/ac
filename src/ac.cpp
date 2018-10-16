#include "ac/ac.h"
#include "trie.h"


ACMatcher::ACMatcher(const std::vector<std::string>& strings)
    : strings_(strings),
      root_(NULL)
{
    build_trie();

}

ACMatcher::~ACMatcher()
{
    if (root_) {
        delete(root_);
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