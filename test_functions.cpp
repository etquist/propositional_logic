#include "logic_parser.h"
#include <string>

// Expected result: true
bool test_1(){
    logic_parser testParser;
 
    testParser.addProp("A", 0, ">");
    testParser.addProp("B", 0, ">");
    testParser.addProp("C", 0, "!=");
    testParser.addProp("D", 0, "=");

    testParser.evalProp("A", -10);
    testParser.evalProp("B", -2);
    testParser.evalProp("C", 0);
    testParser.evalProp("D", 0);

    string expression = "!C";

    testParser.setStatement(expression);
    bool result = testParser.evaluate();

    return result;
}

// Expected result: false 
bool test_2(){
    logic_parser testParser;

    testParser.addProp("A", 0, ">");
    testParser.addProp("B", 0, ">");
    testParser.addProp("C", 0, "!=");
    testParser.addProp("D", 0, "=");

    testParser.evalProp("A", 10);
    testParser.evalProp("B", -2);
    testParser.evalProp("C", 0);
    testParser.evalProp("D", 0);

    string expression = "C";

    testParser.setStatement(expression);
    bool result = testParser.evaluate();
    
    return result;
}

// Expected result: false 
bool test_3(){
    logic_parser testParser;

    testParser.addProp("A", 0, ">");
    testParser.addProp("B", 0, ">");
    testParser.addProp("C", 0, "!=");
    testParser.addProp("D", 0, "=");

    testParser.evalProp("A", 10);
    testParser.evalProp("B", -2);
    testParser.evalProp("C", 0);
    testParser.evalProp("D", 0);

    string expression = "C && A && B && D";

    testParser.setStatement(expression);
    bool result = testParser.evaluate();
    
    return result;
}

// Expected result: false
bool test_4(){
    logic_parser testParser;

    testParser.addProp("A", 0, ">");
    testParser.addProp("B", 0, ">");
    testParser.addProp("C", 0, "!=");
    testParser.addProp("D", 0, "=");

    testParser.evalProp("A", 10);   // true
    testParser.evalProp("B", -2);   // false
    testParser.evalProp("C", 1);    // true
    testParser.evalProp("D", 0);    // true

    string expression = "(C && A ) || (D && B)";

    testParser.setStatement(expression);
    bool result = testParser.evaluate();
    
    return result;
}

// Expected result: false
bool test_5(){
    logic_parser testParser;

    testParser.addProp("A", 0, ">");
    testParser.addProp("B", 0, ">");
    testParser.addProp("C", 0, "!=");
    testParser.addProp("D", 0, "=");

    testParser.evalProp("A", 10);   // true
    testParser.evalProp("B", -2);   // false
    testParser.evalProp("C", 1);    // true
    testParser.evalProp("D", 0);    // true

    string expression = "C && (A  || D) && B";

    testParser.setStatement(expression);
    bool result = testParser.evaluate();
    
    return result;
}

// Expected result: true
bool test_6(){
    logic_parser testParser;

    testParser.addProp("A", 0, ">");
    testParser.addProp("B", 0, ">");
    testParser.addProp("C", 0, "!=");
    testParser.addProp("D", 0, "=");

    testParser.evalProp("A", 10);   // true
    testParser.evalProp("B", -2);   // false
    testParser.evalProp("C", 1);    // true
    testParser.evalProp("D", 0);    // true

    string expression = "C && (A  || D) && !B";

    testParser.setStatement(expression);
    bool result = testParser.evaluate();
    
    return result;
}

// Expected result: true
bool test_7(){
    logic_parser testParser;

    testParser.addProp("A", 0, ">");
    testParser.addProp("B", 0, ">");
    testParser.addProp("C", 0, "!=");
    testParser.addProp("D", 0, "=");

    testParser.evalProp("A", 10);   // true
    testParser.evalProp("B", -2);   // false
    testParser.evalProp("C", 1);    // true
    testParser.evalProp("D", 0);    // true

    string expression = "((C && (((A  || D))) &&) !B)";

    testParser.setStatement(expression);
    bool result = testParser.evaluate();
    
    return result;
}


// Expected result: true
bool test_8(){
    logic_parser testParser;

    testParser.addProp("A", 0, "<=");
    testParser.addProp("B", 0, ">=");
    testParser.addProp("C", 0, "<");
    testParser.addProp("D", 0, "=");

    testParser.evalProp("A", 10);   // false
    testParser.evalProp("B", -2);   // false
    testParser.evalProp("C", 1);    // false
    testParser.evalProp("D", 0);    // true

    string expression = "D && !(A && B && C)";

    testParser.setStatement(expression);
    bool result = testParser.evaluate();
    
    return result;
}

// Expected result: false
bool test_9(){
    logic_parser testParser;

    testParser.addProp("toad", 0, "<=");
    testParser.addProp("the", 0, ">=");
    testParser.addProp("wet", 0, "<");
    testParser.addProp("sprocket", 0, "=");

    testParser.evalProp("toad", 10);   // false
    testParser.evalProp("the", -2);   // false
    testParser.evalProp("wet", 1);    // false
    testParser.evalProp("sprocket", 0);    // true

    string expression = "toad && the && wet && sprocket";

    testParser.setStatement(expression);
    bool result = testParser.evaluate();
    
    return result;
}

// Expected result: true
bool test_10(){
    logic_parser testParser;

    testParser.addProp("alex", 0, "<=");
    testParser.addProp("ovechkin", 0, ">=");
    testParser.addProp("gr8", 0, "<");
    testParser.addProp("8", 0, "=");

    testParser.evalProp("alex", 10);   // false
    testParser.evalProp("ovechkin", -2);   // false
    testParser.evalProp("gr8", 1);    // false
    testParser.evalProp("8", 0);    // true

    string expression = "(alex && ovechkin ) || (!gr8 && 8)";

    testParser.setStatement(expression);
    bool result = testParser.evaluate();
    
    return result;
}

// Expected result: false
bool test_11(){
    logic_parser testParser;

    testParser.addProp("speed", 0, "<=");

    testParser.evalProp("speed", 10);   // false


    string expression = "(!(!(speed)))";

    testParser.setStatement(expression);
    bool result = testParser.evaluate();
    
    return result;
}

// Expected result: true
bool test_12(){
    logic_parser testParser;

    testParser.addProp("speed", 0, "<=");

    testParser.evalProp("speed", 10);   // false


    string expression = "(!(!(speed)))";
    testParser.setStatement(expression);

    bool result = testParser.evaluate();

    testParser.evalProp("speed", -10);   // true
    result = testParser.evaluate();
    
    return result;
}

// Expected result: true
bool test_13(){
    unordered_map<string, double> vars;
    vars["speed"] = 5;
    vars["temp"] = 5;
    vars["waveHeight"] = 5;
    
    string statement = "waveHeight>=3||(speed >> 1 && temp == 5)";

    logic_parser testParser;
    bool result = testParser.evaluateStandAlone(statement, vars);
    
    return result;
}

// Expected result: false
bool test_14(){
    unordered_map<string, double> vars;
    vars["speed"] = 5;
    vars["temp"] = 5;
    vars["waveHeight"] = 5;
    
    string statement = "(!waveHeight>=3)||!(speed >> 1 && temp == 5)";

    logic_parser testParser;
    bool result = testParser.evaluateStandAlone(statement, vars);
    
    return result;
}

// Expected result: true
bool test_15(){
    unordered_map<string, double> vars;
    vars["speed"] = 53225;
    vars["temp"] = -22465.235;
    vars["waveHeight"] = 5.2356;
    
    string statement = "(!waveHeight>=3)||!(speed >> 1 && temp == 5)";

    logic_parser testParser;
    bool result = testParser.evaluateStandAlone(statement, vars);
    
    return result;
}