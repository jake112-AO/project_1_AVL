//
// Created by jiahao Liu on 9/19/25.
//

#ifndef AVL_H
#define AVL_H

#include <vector>
#include <string>

using namespace std;

struct Node {
    string name;
    string ufid;
    Node* left;
    Node* right;
    int height;
    Node(string name, string ufid, Node* left, Node* right, int height) {
        this->name = name;
        this->ufid = ufid;
        this->left = nullptr;
        this->right = nullptr;
        this->height = height;
    };
};

class AVLTree {
private:
  	Node* root;

    int getHeight(Node* node);
    void updateHeight(Node* node);
    int getBalance(Node* node);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insertHelper(Node* node, string name, string id);
    Node* minValueNode(Node* node);
    Node* removeHelper(Node* node, string id);
    Node* findNode(Node* node, const string& id);
    void searchNameHelper(Node* node, const string& name, vector<string>& ids);
    void printInorderHelper(Node* node, bool& first);
    void printPreorderHelper(Node* node, bool& first);
    void printPostorderHelper(Node* node, bool& first);
    void getInorder_list(Node* node, vector<string>& ids);
    void deleteTree(Node* node);

public:
    AVLTree();
    ~AVLTree();

    bool insert(const string& name, const string& id);
    bool remove(const string& id);
    void searchID(const string& id);
    void searchName(const string& name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    int levelCount();
    bool removeInorder(int n);
    bool isValidID(const string& id);
    bool isValidName(const string& name);
};


#endif //AVL_H
