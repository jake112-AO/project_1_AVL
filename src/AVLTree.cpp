
#include "AVLTree.h"
#include <iostream>
using namespace std;



AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    deleteTree(root);
}

int AVLTree::getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

void AVLTree::updateHeight(Node* node) {
    if (node != nullptr) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right)); // quote from the slides
    }
}

int AVLTree::getBalance(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return leftHeight - rightHeight;
}

Node* AVLTree::rightRotate(Node* node) {
    Node* child = node->left;
    Node* grandchild = child->right;
    child->right = node;
    node->left = grandchild;
    updateHeight(node);
    updateHeight(child);
    return child;
}
//qoute: from balance tree slides
Node* AVLTree::leftRotate(Node* node) {
    Node* child = node->right;
    Node* grandchild = child->left;
    child->left = node;
    node->right = grandchild;
    updateHeight(node);
    updateHeight(child);
    return child;
}

//
Node* AVLTree::insertHelper(Node* node, string name, string ufid) {
    if (node == nullptr) {
        return new Node(name, ufid, nullptr, nullptr, 1);
    }
    if (ufid < node->ufid) {
        node->left = insertHelper(node->left, name, ufid);
    } else if (ufid > node->ufid) {
        node->right = insertHelper(node->right, name, ufid);
    } else {
        return node; // duplicate
    }
    updateHeight(node);
    int balance = getBalance(node);
    if (balance > 1 && ufid < node->left->ufid) {
        return rightRotate(node);
    }
    if (balance < -1 && ufid > node->right->ufid) {
        return leftRotate(node);
    }
    if (balance > 1 && ufid > node->left->ufid) {
        node->left = leftRotate(node->left);
        return rightRotate(node); //LR
    }
    if (balance < -1 && ufid < node->right->ufid) {
        node->right = rightRotate(node->right); // quote from the slides
        return leftRotate(node); //RL
    }
    return node;
}

Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left) {
        current = current->left;
    }
    return current;
}

Node* AVLTree::removeHelper(Node* node, std::string id) {
    if (node == nullptr) {
        return nullptr;
    }

    if (id < node->ufid) {
        node->left = removeHelper(node->left, id);
    } else if (id > node->ufid) {
        node->right = removeHelper(node->right, id);
    } else {
        // Found the node to delete
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp;
            if (node->left != nullptr) {
                temp = node->left;
            }
            else {
                temp = node->right;
            }
            delete node;
            return temp;
        } else {
            // Node has two children, find inorder successor
            Node* temp = minValueNode(node->right);
            node->ufid = temp->ufid;
            node->name = temp->name;
            node->right = removeHelper(node->right, temp->ufid);
        }
    }

    // If node became null after recursive deletion, return null
    if (node == nullptr) {
        return nullptr;
    }

    updateHeight(node);
    int balance = getBalance(node);

    // Left heavy cases
    if (balance > 1) {
        if (getBalance(node->left) >= 0) {
            return rightRotate(node);
        } else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    // Right heavy cases
    if (balance < -1) {
        if (getBalance(node->right) <= 0) {
            return leftRotate(node);
        } else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}


Node* AVLTree::findNode(Node* node, const std::string& id) {
    if (!node || node->ufid == id) {
        return node;
    }
    if (id < node->ufid) {
        return findNode(node->left, id);
    }
    return findNode(node->right, id);
}

//recursive helper for searching all nodes in AVL tree that have a specific name
void AVLTree::searchNameHelper(Node* node, const string& name, vector<string>& ids) {
    if (node == nullptr) {
        return;
    }
    searchNameHelper(node->left, name, ids);
    if (node->name == name) {
        ids.push_back(node->ufid);
    }
    searchNameHelper(node->right, name, ids);
}

void AVLTree::printInorderHelper(Node* node, bool& first) {
    if (!node) {
        return;
    }
    printInorderHelper(node->left, first);
    if (!first) {
        cout << ", ";
    }
    cout << node->name;
    first = false;
    printInorderHelper(node->right, first);
}

void AVLTree::printPreorderHelper(Node* node, bool& first) {
    if (node == nullptr) {
        return;
    }
    if (!first) {
        cout << ", ";
    }
    cout << node->name;
    first = false;
    printPreorderHelper(node->left, first);
    printPreorderHelper(node->right, first);
}

void AVLTree::printPostorderHelper(Node* node, bool& first) {
    if (node == nullptr) {
        return;
    }
    printPostorderHelper(node->left, first);
    printPostorderHelper(node->right, first);
    if (!first) {
        cout << ", ";
    }
    cout << node->name;
    first = false;
}
// give all the ufid in the tree as list print out
void AVLTree::getInorder_list(Node* node, vector<string>& ids) {
    if (node == nullptr) {
        return;
    }
    getInorder_list(node->left, ids);
    ids.push_back(node->ufid);
    getInorder_list(node->right, ids);
}

// deleted entire in memory
void AVLTree::deleteTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

//insert new node with name and id into avl tree
bool AVLTree::insert(const string& name, const string& id) {
    if (!isValidID(id) || !isValidName(name)) {
        return false;
    }
    if (findNode(root, id)) {
        return false;
    }
    root = insertHelper(root, name, id);
    return true;
}

bool AVLTree::remove(const string& id) {
    if (!findNode(root, id)) {
        return false;
    }
    root = removeHelper(root, id);
    return true;
}

void AVLTree::searchID(const std::string& id) {
    Node* found = findNode(root, id);
    if (found) {
        cout << found->name << std::endl;
    }else {
        cout << "unsuccessful" << std::endl;
    }
}

void AVLTree::searchName(const string& name) {
    vector<string> ids;
    searchNameHelper(root, name, ids);
    if (ids.empty()) {
        cout << "unsuccessful" << endl;
    } else {
        for (const auto& i : ids) {
            cout << i << endl;
        }
    }
}

void AVLTree::printInorder() {
    if (root == nullptr) {
        cout << endl;
        return;
    }
    bool first = true;
    printInorderHelper(root, first);
    cout << endl;
}

void AVLTree::printPreorder() {
    if (root == nullptr) {
        cout << endl;
        return;
    }
    bool first = true;
    printPreorderHelper(root, first);
    cout << endl;
}

void AVLTree::printPostorder() {
    if (!root) {
        cout << endl;
        return;
    }
    bool first = true;
    printPostorderHelper(root, first);
    cout << endl;
}

int AVLTree::levelCount() {
    return getHeight(root);
}


bool AVLTree::removeInorder(int n) {
    vector<string> ids;
    getInorder_list(root, ids);
    if (n < 0 || n >= static_cast<int>(ids.size())) {
        return false;
    }
    bool result = remove(ids[n]);
    return result;
}


bool AVLTree::isValidID(const string& id) {
    if (id.length() != 8) {
        return false;
    }
    for (char c : id) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool AVLTree::isValidName(const string& name) {
    if (name.empty()) {
        return false;
    }
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}
