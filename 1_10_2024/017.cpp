#include<iostream>
#include<random>
#include<ctime>

std::mt19937_64 rd(time(0));

template<typename T>
class Tree {
private:
    struct Node {
        T value;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;
        Node(T value) : value(value) {}
        ~Node() {
            delete left;
            delete right;
        }
    } *root = nullptr;

    void print(Node* node) {
        if (node == nullptr) return;
        print(node->left);
        std::cout << node->value << ' ';
        print(node->right);
    }

    Node* max(Node* node) {
        if (node == nullptr)
            return nullptr;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    Node* min(Node* node) {
        if (node == nullptr)
            return nullptr;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void remove(Node* node) {
        if (node == nullptr) return;
        if (node->left == nullptr && node->right == nullptr) {
            Node* tmp = node->parent;
            if (tmp->left == node) {
                tmp->left = nullptr;
            } else {
                tmp->right = nullptr;
            }
            delete node;
        } else if (node->left == nullptr || node->right == nullptr) {
            Node* tmp = node->parent;
            Node* child = node->left == nullptr ? node->right : node->left;
            if (tmp->left == node) {
                tmp->left = child;
            } else {
                tmp->right = child;
            }
            child->parent = tmp;
            delete node;
        } else {
            Node* tmp = max(node->left);
            node->value = tmp->value;
            remove(tmp);
        }
    }

public:
    Tree() = default;

    void insert(T value) {
        if (root == nullptr) {
            root = new Node(value);
        } else {
            Node *tmp = root;
            while(tmp->value != value) {
                if (tmp->value > value) {
                    if (tmp->left == nullptr) {
                        tmp->left = new Node(value);
                        tmp->left->parent = tmp;
                    }
                    tmp = tmp->left;
                } else {
                    if (tmp->right == nullptr) {
                        tmp->right = new Node(value);
                        tmp->right->parent = tmp;
                    }
                    tmp = tmp->right;
                }
            }
        }
    }

    bool find(T value) {
        Node *tmp = root;
        bool isValue = false;
        while(tmp != nullptr) {
            if (tmp->value == value) {
                isValue = true;
                break;
            }
            if (tmp->value > value) {
                tmp = tmp->left;
            } else {
                tmp = tmp->right;
            }
        }
        return isValue;
    }

    void print() {
        print(root);
    }

    void remove(T value) {
        Node *tmp = root;
        while(tmp != nullptr) {
            if (tmp->value == value) {
                break;
            }
            if (tmp->value > value) {
                tmp = tmp->left;
            } else {
                tmp = tmp->right;
            }
        }
        remove(tmp);
    }

    ~Tree() {
        delete root;
    }
};

int main() {
    Tree<double> tree;
    for (size_t i = 0; i < 20; ++i) {
        tree.insert(rd() % 30);
    }
    tree.print();

    return 0;
}
