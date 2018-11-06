#ifndef AHO_CORASICK_PROJECT_AC_H
#define AHO_CORASICK_PROJECT_AC_H
#include <vector>
#include <string>
#include <ahocorasick/Slice.h>


typedef bool (*match_callback)(void* ctx, Slice* slice);

class TrieNode;
class AcAutomata
{
public:
    explicit AcAutomata(const std::vector<std::string>& patterns);

    ~AcAutomata();

    void search(const char* data, int len, match_callback callback, void* ctx);

    void search_all(const char* data, int len, std::vector<Slice>& patterns);

private:
    void build_trie();

    void build_fail();

    std::vector<std::string> patterns_;
    TrieNode* root_;
};


#endif //AHO_CORASICK_PROJECT_AC_H
