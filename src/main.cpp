
#include "AVLTree.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// string line;
// while (getline(cin, line)) {
//     if (line.empty()) {
//         continue;
//     }
//     istringstream iss(line);
//     string command;
//     iss >> command;
//
//     // your command handling code here
// }
// main.cpp
int main() {
    int numCommands;
    cin >> numCommands;
    cin.ignore(); // ignore newline

    AVLTree tree;

    for (int i = 0; i < numCommands; ++i) {
        string line;
        if (!getline(cin, line)) { // cin is store sentence, line is where you type,
            break; // Exit if no more input
        }
        if (line.empty()) continue;

        istringstream iss(line); // insert "alice" 1334
        string command;
        iss >> command; // first word of the line insert

        if (command == "insert") {
            size_t start = line.find('"');
            if (start == string::npos) { // npos mean not found
                cout << "unsuccessful" << endl;
                continue;
            }
            size_t end = line.find('"', start + 1); // find other quotes after start + 1
            if (end == string::npos) {
                cout << "unsuccessful" << endl;
                continue;
            }
            string name = line.substr(start + 1, end - start - 1); // take the word between quotes
            istringstream iss_id(line.substr(end + 1)); // get the id with usually after the qutotes
            string id;
            iss_id >> id;
            if (tree.insert(name, id)) {
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        } else if (command == "remove") {
            string id;
            iss >> id;
            if (tree.remove(id)) {
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        } else if (command == "search") { // search by name
            size_t start = line.find('"', command.length()); // find first quotation after the search command
            if (start != string::npos) {
                size_t end = line.find('"', start + 1); // find the second quotation at the end
                if (end == string::npos) {
                    cout << "unsuccessful" << endl;
                    continue;
                }
                string name = line.substr(start + 1, end - start - 1); // take out the name
                tree.searchName(name);
            } else {
                string id;
                iss >> id;
                tree.searchID(id);
            }
        } else if (command == "printInorder") {
            tree.printInorder();
        } else if (command == "printPreorder") {
            tree.printPreorder();
        } else if (command == "printPostorder") {
            tree.printPostorder();
        } else if (command == "printLevelCount") {
            cout << tree.levelCount() << endl;
        } else if (command == "removeInorder") {
            int n;
            if (iss >> n) {
                if (tree.removeInorder(n)) {
                    cout << "successful" << endl;
                } else {
                    cout << "unsuccessful" << endl;
                }
            } else {
                cout << "unsuccessful" << endl;
            }
        } else {
            cout << "unsuccessful" << endl;
        }
    }
    return 0;
}