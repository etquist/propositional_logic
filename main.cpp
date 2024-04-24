#include <cstdio>
#include <string>
#include <iostream>
#include "logic_parser.h"

 

int main(int argc, char** argv) {
    logic_parser testParser;

    testParser.addProp("speed", 0, ">");
    testParser.addProp("B", 0, ">");
    testParser.addProp("C", 0, "!=");
    testParser.addProp("D", 0, "=");

    cout << testParser.evalProp("speed", 10) << endl;
    cout << testParser.evalProp("B", -2) << endl;
    cout << testParser.evalProp("C", 0) << endl;
    cout << testParser.evalProp("D", 0) << endl;


    string expression = "(speed) || FALSE";


    testParser.setStatement(expression);
    bool result = testParser.evaluate();
    
    if (result){
        cout << "Result: True" << endl;
    } else {
        cout << "Result: False" << endl;
    }
    

    return 0;
}


