/*
    Custom Logic Statement Parsing Class

    Written by Ethan Almquist
    April 2024
*/  
 
#ifndef INCLUDE_LOGIC_PARSER
#define INCLUDE_LOGIC_PARSER

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <set>



using namespace std;

class logic_parser{
    public:
        struct prop{
            // Of the format... "var comparisonType val"
            string var;                 // e.g., "speed"
            double val;                 // e.g., "3"
            string comparisonType;      // ["<", "<=", ">=", ">", "=", "!=""]

            bool boolVal = false;   // default, false. the last evaluated value of the propositon

            // A simple function to evaluate the proposition based on the passed value
            bool eval(double trueVal){
                if (comparisonType == "<"){
                    boolVal = trueVal < val;
                } else if (comparisonType == "<="){
                    boolVal = trueVal <= val;
                } else if (comparisonType == ">="){
                    boolVal = trueVal >= val;
                } else if (comparisonType == ">"){
                    boolVal = trueVal > val;
                } else if (comparisonType == "="){
                    boolVal = trueVal == val;
                } else if (comparisonType == "!="){
                    boolVal = trueVal != val;
                } else {
                    throw std::runtime_error("Invalid comparison type.");
                    return false;
                }
                return boolVal;
            }

        };

        // Evaluate the logic statement
        // Invalid propositions throw an error and return false
        bool evaluate();

        // Get/Set the logic_parser's statement
        void setStatement(string newStatement);
        string getStatement();

        // Add a proposition to the known variables
        void addProp(string var, double val, string comparisonType);

        // Evaluate a proposition based on the passed value
        bool evalProp(string var, double val);

        // Deletes a proposition from the known variables
        void deleteProp(string var);

        // Updates the value and comparison type of the specified proposition if it exists, 
        //      and if not a new prop is created
        void updateProp(string var, double val, string comparisonType);

        // Returns a set of all the propositions contained in the parser object
        set<string> getPropositions();

        // Evaluate a proposition statement given the text statement and variable-value pairs
        bool evaluateStandAlone(string statement, unordered_map<string, double> vars);

    private:
        
        // A map between a unique string, and the proposition statement
        unordered_map<string, prop> propositions;
        
        // Logic statement written by the user
        string statement;

        // clear all of the spaces from the statement
        string clearSpaces(string input);

        // This takes a statement of the freehand form [e.g., sim!=1||((speed<=5)&&temp==5)], and replaces 
        // values according to the map of variables passed into the string. Expressions will then be evaluated,
        // leaving a statement of only TRUE and FALSES 
        // NOTE: Will accept comparison operators of ["<<", "<=", ">=", ">>", "==", "!="]
        string preParseStatement(string statement_str, unordered_map<string, double> vars);


};


#endif