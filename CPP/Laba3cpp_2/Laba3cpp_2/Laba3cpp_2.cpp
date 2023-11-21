#include "Derevo.hpp"
#include <thread>
#include <string>



class TestClass {
private:
    int cur;
public:
    TestClass(int value) {
        cur = value;
    }

    int getValue() {
        return cur;
    }

    friend bool operator<(const TestClass& left, const TestClass& right) {
        return left.cur < right.cur;
    }
    friend bool operator>(const TestClass& left, const TestClass& right) {
        return left.cur > right.cur;
    }

    friend bool operator<=(const TestClass& left, const TestClass& right) {
        return left.cur <= right.cur;
    }

    friend bool operator==(const TestClass& left, const TestClass& right) {
        return left.cur == right.cur;
    }
    friend bool operator!=(const TestClass& left, const TestClass& right) {
        return left.cur != right.cur;
    }
};



template <typename T>
void thread_func_test(laba2::Tree<T>& tree, int num1, int num2) {
    std::cout << "Thread launched" << std::endl;
    laba2::Tree<int> treeoper;
    treeoper << 104 << 42 << 33 << 15 << 8 << 9 << 10 << 2 << 50 << 12;
    std::cout << "tree for operators:"<<std::endl<< treeoper << std::endl;
    for (int i = num1; i <= num2; i++) {
        tree.add(i);
    }
    
    for (int i = num1; i <= num2; i++) {
        if (i % 4 == 0) {
            tree.deleteNode(i);
        }
    }
    for (int i = num1; i <= num2; i++) {
        if (i / 7 == 1) {
            std::cout << tree.findTree(i) << std::endl;
            std::cout << "heiloy" << std::endl;
            break;
        }
    }
    for (int i = num1; i <= num2; i++) {
        if (i % 3 == 0) {
            tree.find(i);
            std::cout<<"find ["<<i<<"]:"<< tree.find(i) << std::endl;
        }
    }
    
    for (int i = num1; i <= num2; i++) {
        if (i/ 11 == 0) {
            tree << 99;
            std::cout << tree << std::endl;
        }
        break;
    }
    for (int i = num1; i <= num2; i++) {
        if (i == 0) {
            std::cout << "tree == anothertree ? : " << (tree == treeoper) << std::endl;
            std::cout << "tree != anothertree ? : " << (tree != treeoper) << std::endl;
            if (tree != treeoper) {
                tree = treeoper;
                std::cout << "tree == anothertree ?  again: " << (tree == treeoper) << std::endl;
            }
            else {
                tree.clear();
                tree << 1234;
            }
        }
    }
}

int main(int argc, char** argv) {

   
    laba2::Tree<int> tree1;
    tree1.add(5);
    tree1.add(3);
    tree1.add(7);
   
    std::cout<< "find 7 = "<< tree1.find(7)<<std::endl;
    std::cout << "find 10 = " << tree1.find(10) << std::endl;

    tree1.deleteNode(7);
    std::cout << "find 7 again = " << tree1.find(7) << std::endl;
    tree1.add(7);
    laba2::Tree<int> tree2;
    tree2.add(5);
    tree2.add(3);
    tree2.add(7);
    laba2::Tree<int> tree3;
    tree3.add(2);
    tree3.add(4);
    tree3.add(8);
    std::cout << "tree1 = " << tree1 << std::endl;
    std::cout << "tree2 = " << tree2 << std::endl;
    std::cout << "tree3 = " << tree3 << std::endl;
    std::cout << "tree1 == tree2 ? " << (tree1==tree2) << std::endl;
    std::cout << "tree1 == tree3 ? " << (tree1 == tree3) << std::endl;
    tree3 = tree1;
    std::cout << "tree1 == tree3 ? again =  " << (tree1 == tree3) << std::endl;

    laba2::Tree<int> trelpklkpklp;
    trelpklkpklp.add(5);
    trelpklkpklp.add(3);
    trelpklkpklp.add(7);
    trelpklkpklp.add(2);
    trelpklkpklp.add(4);
    std::cout << trelpklkpklp << std::endl;
    std::cout << std::endl;
    std::cout << tree1.findTree(5) << std::endl;
    tree1.clear();
    std::cout << tree1 << std::endl;
    int  i = 9;
    tree1 << tree2;
    tree1 << i << 1;
    std::cout << tree1 << std::endl;
    std::cout << "tree1 != tree2 ? " << (tree1 != tree2) << std::endl;
    
    laba2::Tree<double> treedouble1;
    laba2::Tree<double> treedouble2;
    laba2::Tree<double> treedouble3;
    treedouble1.add(5.576);
    treedouble1.add(3.345);
    treedouble1.add(7.1234);
    treedouble2.add(5.47123);
    treedouble2.add(3.43268);
    treedouble2.add(7.6457);
    treedouble3.add(2.342186);
    treedouble3.add(4.7465312);
    treedouble3.add(8.586324);
    std::cout << "treeD1 = " << treedouble1 << std::endl;
    std::cout << "treeD2 = " << treedouble2 << std::endl;
    std::cout << "treeD3 = " << treedouble3 << std::endl;

    laba2::Tree<int> tree;
    std::thread thread_1([&tree]() {thread_func_test(tree, 0, 21);});
    thread_1.join();
    //std::cout << "Tree:" << tree << std::endl;
   
}