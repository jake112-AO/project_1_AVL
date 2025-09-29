
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
int main() {
    int numCommands;
    cin >> numCommands;
    cin.ignore(); // Consume newline

    AVLTree tree;

    for (int i = 0; i < numCommands; ++i) {
        string line;
        getline(cin, line);
        if (line.empty()) {
            continue;
        }
        //insert name ID
        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "insert") {
            auto start = line.find('"');
            if (start == string::npos) {
                cout << "unsuccessful" << endl;
                continue;
            }
            auto end = line.find('"', start + 1);
            if (end == string::npos) {
                cout << "unsuccessful" << endl;
                continue;
            }
            string name = line.substr(start + 1, end - start - 1);
            istringstream iss_id(line.substr(end + 1));
            string id;
            iss_id >> id;
            if (tree.insert(name, id)) {
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
            // remove ID
        } else if (command == "remove") {
            string id;
            iss >> id;
            if (tree.remove(id)) {
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
            // search ID/name
        } else if (command == "search") {
            int start = line.find('"', command.length());
            if (start != string::npos) {
                int end = line.find('"', start + 1);
                if (end == string::npos) {
                    cout << "unsuccessful" << endl;
                    continue;
                }
                string name = line.substr(start + 1, end - start - 1); // extract the word between the quotes (position, how many letter been take out)
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
            //remove in order
        } else if (command == "removeInorder") {
            int n;
            iss >> n;
            if (tree.removeInorder(n)) {
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        } else {
            cout << "unsuccessful" << endl;
        }
    }
    return 0;
}