#include "Stack.hpp"
#include "string"
#include <stack>
#include <vector>
void f() {
    laba::Stack<int> fs;
    for (int i = 0; i < 20; i++) {
        fs.push(i);
    }
}

int main(int argc, char** argv){
    f();
    int a = 30, b = 40, c = -50, d = -12;
    laba::Stack<int> stck;
    laba::Stack<int> stck2;
    stck.push(a);
    stck.push(b);
    stck.push(c);
    stck.clear();
    for (int i = 0; i < 12; i++) {
        stck.push(i);
    }
    stck.push(d);
    std::cout << stck << std::endl;
    laba::Stack<int> *stckd = new laba::Stack<int>[3];
    delete[] stckd;
    //stck.pop();
    //std::cout<< stck <<std::endl;
    //stck.top(d);
    //std::cout << stck << std::endl;
    //stck.swap(c);
    //std::cout << stck << std::endl;
    std::cout << "stck2=" << stck2 << std::endl;
    stck2 = std::move(stck);
    std::cout << "stck2=" << stck2 << std::endl;
    for (int i = 0; i < 5; i++) {
        stck2.push(i);
    }
    std::cout << "stck2="<< stck2 << std::endl;
  
    std::cout << "stck=" << stck << std::endl;

    laba::Stack<int> stck3(stck2);
    std::cout << "stck3=" << stck3 << std::endl;

    try{
        std::vector<int> datas = {22,31,4};
        laba::Stack<int> itStack(datas.end(), datas.begin());
        std::cout << "stack itter:\n " << itStack << std::endl;
    }catch(laba::Stack_Exception e){
        std::cout << "\nError\n";
    }
    return 0;
}