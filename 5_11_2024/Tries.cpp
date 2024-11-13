#include "iostream"
#include "map"
#include "string"


class Trie {
private:
    struct Node {
        std::map<char, Node> next;
        int isTerminal = false;
    } root;

    void dfs(Node& v, std::string& ans) {
        if (v.isTerminal) std::cout << ans << '\n';
        for (auto& el : v.next) {
            ans.push_back(el.first);
            dfs(el.second, ans);
            ans.pop_back();
        }
    }

public:
    void add(const std::string& s) {
        Node* v = &root;
        for (auto ch : s) v = &v->next[ch];
        v->isTerminal = true;
    }

    void print() {
        std::string s;
        dfs(root, s);
    }
};

int main() {
    Trie trie;
    trie.add("abba");
    trie.add("bab");
    trie.add("aba");
    trie.add("baab");
    trie.add("ababab");
    trie.add("bababa");

    trie.print();

    return 0;
}