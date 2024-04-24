#include <cstdio>
#include <string>
#include <iostream>
#include <cassert>
#include "logic_parser.h"
#include "test_functions.cpp"
  
 // This main.cpp script serves as a testing bed and demonstration of the parser

int main(int argc, char** argv) {
    
    cout << "\n\nTest 1: \n" << endl;
    assert(test_1() == true);
    
    cout << "\n\nTest 2: \n" << endl;
    assert(test_2() == false);

    cout << "\n\nTest 3: \n" << endl;
    assert(test_3() == false);

    cout << "\n\nTest 4: \n" << endl;
    assert(test_4() == true);

    cout << "\n\nTest 5: \n" << endl;
    assert(test_5() == false);

    cout << "\n\nTest 6: \n" << endl;
    assert(test_6() == true);

    cout << "\n\nTest 7: \n" << endl;
    assert(test_7() == true);

    cout << "\n\nTest 8: \n" << endl;
    assert(test_8() == true);

    cout << "\n\nTest 9: \n" << endl;
    assert(test_9() == false);

    cout << "\n\nTest 10: \n" << endl;
    assert(test_10() == true);

    cout << "\n\nTest 11: \n" << endl;
    assert(test_11() == false);

    cout << "\n\nTest 12 \n" << endl;
    assert(test_12() == true);
    

    return 0;
}


