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

        // Set the logic_parser's statement
        void setStatement(string newStatement);

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

    private:
        
        // A map between a unique string, and the proposition statement
        unordered_map<string, prop> propositions;
        
        // Logic statement written by the user
        string statement;

        // clear all of the spaces from the statement
        string clearSpaces(string input);

        // Check validity of a statement. Returns true if valid logic statement
        bool validate(string input);
};


#endif