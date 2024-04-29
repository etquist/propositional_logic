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



class logic_parser{
    public:
        struct prop{
            // Of the format... "var comparisonType val"
            std::string var;                 // e.g., "speed"
            double val;                 // e.g., "3"
            std::string comparisonType;      // ["<", "<=", ">=", ">", "=", "!=""]

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
        void setStatement(std::string newStatement);
        std::string getStatement();

        // Add a proposition to the known variables
        void addProp(std::string var, double val, std::string comparisonType);

        // Evaluate a proposition based on the passed value
        bool evalProp(std::string var, double val);

        // Deletes a proposition from the known variables
        void deleteProp(std::string var);

        // Updates the value and comparison type of the specified proposition if it exists, 
        //      and if not a new prop is created
        void updateProp(std::string var, double val, std::string comparisonType);

        // Returns a set of all the propositions contained in the parser object
        std::set<std::string> getPropositions();

        // Evaluate a proposition statement given the text statement and variable-value pairs
        bool evaluateStandAlone(std::string statement, std::unordered_map<std::string, double> vars);

    private:
        
        // A map between a unique string, and the proposition statement
        std::unordered_map<std::string, prop> propositions;
        
        // Logic statement written by the user
        std::string statement;

        // clear all of the spaces from the statement
        std::string clearSpaces(std::string input);

        // This takes a statement of the freehand form [e.g., sim!=1||((speed<=5)&&temp==5)], and replaces 
        // values according to the map of variables passed into the string. Expressions will then be evaluated,
        // leaving a statement of only TRUE and FALSES 
        // NOTE: Will accept comparison operators of ["<<", "<=", ">=", ">>", "==", "!="]
        std::string preParseStatement(std::string statement_str, std::unordered_map<std::string, double> vars);


};


#endif
