#include "iostream"
#include "random"
#include "ctime"

std::mt19937_64 rd(time(nullptr));


template<typename T>
class Tree {
private:
    struct Node{
        T data;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(T d): data(d) {}

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

public:
    Tree() = default;

    void insert(T d) {
        if (root == nullptr) {
            root = new Node(d);
        }
        else {
            Node* tmp = root;

            while (true) {
                if (d == tmp->data) break;

                if (d < tmp->data) {
                    if (tmp->left == nullptr) tmp->left = new Node(d);
                    tmp = tmp->left;
                }
                else if (d > tmp->data) {
                    if (tmp->right == nullptr) tmp->right = new Node(d);
                    tmp = tmp->right;
                }
            }
        }
    }

    bool find(T d) {
        bool flag = false;

        if (root == nullptr) {
            return flag;
        }
        else {
            Node* tmp = root;

            while (tmp != nullptr) {
                if (d == tmp->data) {
                    flag = true;
                    break;
                }

                if (d < tmp->data) {
                    tmp = tmp->left;
                }
                else{
                    tmp = tmp->right;
                }
            }
        }

        return flag;
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