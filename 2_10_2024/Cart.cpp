#include "iostream"
#include "random"
#include "ctime"

std::mt19937_64 rd(time(nullptr));


template<typename T>
class Tree {
private:
    struct Node{
        T data;
        T sum;
        uint64_t priora = rd();
        Node* left = nullptr;
        Node* right = nullptr;

        Node(T d): data(d), sum(d){}

        ~Node() {
            delete left;
            delete right;
        }
    } *root = nullptr;

    void print(Node* node) {
        if (node == nullptr) return;

        print(node->left);
        std::cout << node->data << ' ';

        print(node->right);
    }

    std::pair<Node*, Node*> split(Node* tree, T key) {
        if (tree == nullptr) return {nullptr, nullptr};

        if (tree->data > key) {
            auto q = split(tree->left, key);
            tree->left = q.second;

            return {q.first, tree};
        }
        else {
            auto q = split(tree->left, key);
            tree->right = q.first;

            return {tree, q.second};
        }
    }

    Node* merge(Node* smaller, Node* bigger) {
        if (smaller == nullptr) return bigger;
        if (bigger == nullptr) return smaller;

        if (bigger->priora < smaller->priora) {
            smaller->right = merge(smaller->right, bigger);

            return smaller;
        }
        else {
            bigger->left = merge(smaller, bigger->left);

            return bigger;
        }

    }

public:
    Tree() = default;

    void insert(T key) {
        auto q = split(root, key);
        root = merge(merge(q.first, new Node(key)), q.second);
    }

    void print() {
        print(root);
    }

    ~Tree() {
        delete root;
    }
};


int main() {
    Tree<int> tree;

    for (size_t i = 0; i < 30; i ++) {
        tree.insert(rd() % 30);
    }

    tree.print();

    return 0;
}