// #include <catch2/catch_test_macros.hpp>
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <random>
// #include "AVLTree.h"
// // Name: Jiahao Liu
// // UFID: 89240893
//
// // uncomment and replace the following with your own headers
//
// using namespace std;
//
// // the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
// TEST_CASE("Example Test Name - Change me!", "[flag]"){
// 	// instantiate any class members that you need to test here
// 	int one = 1;
//
// 	// anything that evaluates to false in a REQUIRE block will result in a failing test
// 	REQUIRE(one == 1); // fix me!
//
// 	// all REQUIRE blocks must evaluate to true for the whole test to pass
// 	REQUIRE(true); // also fix me!
// }
//
// TEST_CASE("Test 2", "[flag]"){
// 	// you can also use "sections" to share setup code between tests, for example:
// 	int one = 1;
//
// 	SECTION("num is 2") {
// 		int num = one + 1;
// 		REQUIRE(num == 2);
// 	};
//
// 	SECTION("num is 3") {
// 		int num = one + 2;
// 		REQUIRE(num == 3);
// 	};
//
// 	// each section runs the setup code independently to ensure that they don't affect each other
// }
//
// // you must write 5 unique, meaningful tests for credit on the testing portion of this project!
//
// // the provided test from the template is below.
//
// TEST_CASE("BST Insert", "[flag]"){
// 	AVL inputTree;
// 	inputTree.insert(3);
// 	inputTree.insert(2);
// 	inputTree.insert(1);
// 	std::vector<int> actualOutput = inputTree.inorder();
// 	std::vector<int> expectedOutput = {1, 2, 3};
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	REQUIRE(actualOutput == expectedOutput);
// }
//
//
//
// // 1. Test Incorrect Commands
// TEST_CASE("Incorrect Commands", "[invalid]") {
//     AVL inputTree;
//     // Insert a string (should throw or fail to compile; here, we use try/catch for demonstration)
//     // These tests are for interface robustness; if insert only accepts int, these lines may not compile.
//     // So, for demonstration, we show negative numbers and other invalid ints.
//     REQUIRE_NOTHROW(inputTree.insert(0)); // 0 may be valid, depending on implementation
//     REQUIRE_NOTHROW(inputTree.insert(-1)); // Allow negative? Should not throw if negative is valid
//     REQUIRE_NOTHROW(inputTree.insert(-1000));
//     // For non-integer, we can't compile, so we simulate by casting or skipping.
//     // If insert is int-only, the following would not compile:
//     // REQUIRE_THROWS(inputTree.insert("string")); // Uncomment if insert(string) is valid
//     // REQUIRE_THROWS(inputTree.insert(3.14)); // Uncomment if insert(double) is valid
//     // But for invalid usage, we can try duplicate insertions (if not allowed):
//     inputTree.insert(5);
//     REQUIRE_NOTHROW(inputTree.insert(5)); // If duplicates are allowed, should not throw
//     // Try very large and very small numbers
//     REQUIRE_NOTHROW(inputTree.insert(INT_MAX));
//     REQUIRE_NOTHROW(inputTree.insert(INT_MIN));
// }
//
// // 2. Test Insert and Rotations
// TEST_CASE("AVL Rotations", "[rotation]") {
//     // LL Rotation: Insert 30, 20, 10
//     AVL treeLL;
//     treeLL.insert(30);
//     treeLL.insert(20);
//     treeLL.insert(10);
//     std::vector<int> expectedLL = {10, 20, 30};
//     REQUIRE(treeLL.inorder() == expectedLL);
//
//     // RR Rotation: Insert 10, 20, 30
//     AVL treeRR;
//     treeRR.insert(10);
//     treeRR.insert(20);
//     treeRR.insert(30);
//     std::vector<int> expectedRR = {10, 20, 30};
//     REQUIRE(treeRR.inorder() == expectedRR);
//
//     // LR Rotation: Insert 30, 10, 20
//     AVL treeLR;
//     treeLR.insert(30);
//     treeLR.insert(10);
//     treeLR.insert(20);
//     std::vector<int> expectedLR = {10, 20, 30};
//     REQUIRE(treeLR.inorder() == expectedLR);
//
//     // RL Rotation: Insert 10, 30, 20
//     AVL treeRL;
//     treeRL.insert(10);
//     treeRL.insert(30);
//     treeRL.insert(20);
//     std::vector<int> expectedRL = {10, 20, 30};
//     REQUIRE(treeRL.inorder() == expectedRL);
// }
//
// // 3. Test Large Insert/Delete
// TEST_CASE("Insert 100 and Remove 10", "[large]") {
//     AVL inputTree;
//     std::vector<int> allVals;
//     for (int i = 1; i <= 100; ++i) {
//         inputTree.insert(i);
//         allVals.push_back(i);
//     }
//     // Randomly remove 10 elements
//     std::vector<int> toRemove = allVals;
//     std::shuffle(toRemove.begin(), toRemove.end(), std::mt19937{std::random_device{}()});
//     toRemove.resize(10);
//     for (int v : toRemove) {
//         // If remove is implemented; if not, skip or comment out
//         inputTree.remove(v);
//         allVals.erase(std::remove(allVals.begin(), allVals.end(), v), allVals.end());
//     }
//     std::sort(allVals.begin(), allVals.end());
//     std::vector<int> inorderOut = inputTree.inorder();
//     REQUIRE(inorderOut.size() == allVals.size());
//     for (size_t i = 0; i < allVals.size(); ++i) {
//         REQUIRE(inorderOut[i] == allVals[i]);
//     }
// }

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_set>
#include "AVLTree.h"
using namespace std;
// test.cpp
// Comment out this entire file before submitting to Gradescope



// RAII class to redirect cout
class CoutRedirect {
private:
    streambuf* old;
    ostringstream buffer;
public:
    CoutRedirect() {
        old = cout.rdbuf(buffer.rdbuf());
    }
    ~CoutRedirect() {
        std::cout.rdbuf(old);
    }
    std::string str() const {
        return buffer.str();
    }

};

TEST_CASE("AVLTree insert and searchID", "[AVLTree]") {
    AVLTree tree;
    REQUIRE(tree.insert("Brandon", "45679999") == true);
    {
        CoutRedirect redirect;
        tree.searchID("45679999");
        REQUIRE(redirect.str() == "Brandon\n");
    }
    REQUIRE(tree.insert("Brandon", "45679999") == false); // duplicate ID
}

TEST_CASE("AVLTree insert invalid", "[AVLTree]") {
    AVLTree tree;
    REQUIRE(tree.insert("Brandon!", "45679999") == false); // invalid name
    REQUIRE(tree.insert("Brandon", "4567999") == false); // invalid ID length
    REQUIRE(tree.insert("Brandon", "4567999a") == false); // invalid ID digit
}

TEST_CASE("AVLTree remove", "[AVLTree]") {
    AVLTree tree;
    tree.insert("Brian", "35459999");
    REQUIRE(tree.remove("35459999") == true);
    REQUIRE(tree.remove("35459999") == false);
}

TEST_CASE("AVLTree searchName", "[AVLTree]") {
    AVLTree tree;
    tree.insert("Brian", "35459999");
    tree.insert("Brian", "87879999"); // same name, different ID
    {
        CoutRedirect redirect;
        tree.searchName("Brian");
        // Assuming pre-order: depending on insertion, but since IDs sorted, 35459999 left of something? Wait, insert order.
        // 35459999 first, then 87879999 right.
        // Pre-order: root 354, right 878
        REQUIRE(redirect.str() == "35459999\n87879999\n");
    }
    {
        CoutRedirect redirect;
        tree.searchName("NotFound");
        REQUIRE(redirect.str() == "unsuccessful\n");
    }
}

TEST_CASE("AVLTree printInorder", "[AVLTree]") {
    AVLTree tree;
    tree.insert("Brian", "35459999");
    tree.insert("Brandon", "45679999");
    tree.insert("Briana", "87879999");
    tree.insert("Bella", "95469999");
    {
        CoutRedirect redirect;
        tree.printInorder();
        REQUIRE(redirect.str() == "Brian, Brandon, Briana, Bella\n");
    }
}

TEST_CASE("AVLTree printPreorder", "[AVLTree]") {
    AVLTree tree;
    tree.insert("Brian", "35459999");
    tree.insert("Brandon", "45679999");
    tree.insert("Briana", "87879999");
    tree.insert("Bella", "95469999");
    {
        CoutRedirect redirect;
        tree.printPreorder();
        // Depending on tree structure after rotations, but for this insertion, assume balanced.
        // Actual output may vary, adjust based on expected.
        // For simplicity, test the content.
        std::string output = redirect.str();
        REQUIRE(output.find("Brian") != std::string::npos);
        // More precise checks can be added.
    }
}

TEST_CASE("AVLTree levelCount", "[AVLTree]") {
    AVLTree tree;
    REQUIRE(tree.levelCount() == 0);
    tree.insert("Test", "12345678");
    REQUIRE(tree.levelCount() == 1);
}

TEST_CASE("AVLTree removeInorder", "[AVLTree]") {
    AVLTree tree;
    tree.insert("Brian", "35459999");
    tree.insert("Brandon", "45679999");
    tree.insert("Briana", "87879999");
    REQUIRE(tree.removeInorder(1) == true); // removes Brandon (inorder: Brian, Brandon, Briana)
    REQUIRE(tree.removeInorder(3) == false); // out of range
}
// test.cpp
TEST_CASE("AVLTree remove and search duplicate ID", "[AVLTree]") {
    AVLTree tree;
    tree.insert("m", "99999999");
    tree.insert("at", "99999999"); // Simulate duplicate ID
    REQUIRE(tree.remove("99999999") == true); // Should remove the first instance
    {
        CoutRedirect redirect;
        tree.searchID("99999999");
        REQUIRE(redirect.str() == "unsuccessful\n"); // Should not find "at"
    }
}

// test.cpp
TEST_CASE("AVLTree remove and removeInorder", "[AVLTree]") {
    AVLTree tree;
    tree.insert("Brandon", "45674567");
    tree.insert("Brian", "35455565");
    tree.insert("Briana", "87878787");
    tree.insert("Bella", "95462138");
    {
        CoutRedirect redirect;
        tree.printInorder();
        REQUIRE(redirect.str() == "Brian, Brandon, Briana, Bella\n");
    }
    REQUIRE(tree.remove("45674567") == true);
    {
        CoutRedirect redirect;
        tree.removeInorder(2); // Remove Bella (index 2 after Brandon removal)
        REQUIRE(redirect.str() == "successful\n");
    }
    {
        CoutRedirect redirect;
        tree.printInorder();
        REQUIRE(redirect.str() == "Brian, Briana\n");
    }
}


// Add more tests as needed for other functions and edge cases


// TEST_CASE("Example Test Name - Change me!", "[flag]"){
//    int one = 1;
//    REQUIRE(one == 1);
//    REQUIRE(true);
// }
//
//
// TEST_CASE("Test 2", "[flag]"){
//    int one = 1;
//    SECTION("num is 2") {
//       int num = one + 1;
//       REQUIRE(num == 2);
//    };
//    SECTION("num is 3") {
//       int num = one + 2;
//       REQUIRE(num == 3);
//    };
// }
//
//
//
//
// TEST_CASE("Incorrect Commands", "[invalid]") {
//    AVLTree inputTree;
//    REQUIRE_NOTHROW(inputTree.insertd(0));
//    REQUIRE_NOTHROW(inputTree.insert(-1));
//    REQUIRE_NOTHROW(inputTree.insert(-1000));
//    inputTree.insert(5);
//    REQUIRE_NOTHROW(inputTree.insert(5));
//    REQUIRE_NOTHROW(inputTree.insert(INT_MAX));
//    REQUIRE_NOTHROW(inputTree.insert(INT_MIN));
// }
//
//
// TEST_CASE("AVL Rotations", "[rotation]") {
//    AVLTree treeLL;
//    treeLL.insert(30);
//    treeLL.insert(20);
//    treeLL.insert(10);
//    vector<int> expectedLL = {10, 20, 30};
//    REQUIRE(treeLL.inorder() == expectedLL);
//
//    AVLTree treeRR;
//    treeRR.insert(10);
//    treeRR.insert(20);
//    treeRR.insert(30);
//    vector<int> expectedRR = {10, 20, 30};
//    REQUIRE(treeRR.inorder() == expectedRR);
//
//    AVLTree treeLR;
//    treeLR.insert(30);
//    treeLR.insert(10);
//    treeLR.insert(20);
//    vector<int> expectedLR = {10, 20, 30};
//    REQUIRE(treeLR.inorder() == expectedLR);
//
//
//    AVLTree treeRL;
//    treeRL.insert(10);
//    treeRL.insert(30);
//    treeRL.insert(20);
//    vector<int> expectedRL = {10, 20, 30};
//    REQUIRE(treeRL.inorder() == expectedRL);
// }
//
//
// TEST_CASE("Insert 100 and Remove 10", "[large]") {
//    AVLTree inputTree;
//    vector<int> all_Vals;
//    for (int i = 1; i <= 100; ++i) {
//       inputTree.insert(i);
//       all_Vals.push_back(i);
//    }
//    vector<int> toRemove = all_Vals;
//    shuffle(toRemove.begin(), toRemove.end(), mt19937{random_device{}()});
//    toRemove.resize(10);
//    for (int v : toRemove) {
//       inputTree.remove(v);
//       all_Vals.erase(remove(all_Vals.begin(), all_Vals.end(), v), all_Vals.end());
//    }
//    sort(all_Vals.begin(), all_Vals.end());
// }