#include "logic_parser.h"

 

bool logic_parser::evaluate(){
    // Save the original logic statement
    // Remove spaces from the statement
    const string originalStatement = clearSpaces(statement);
    string procStatement = originalStatement;


    bool escape_primed = false;
    bool exit = false;
    while (procStatement != "TRUE" && procStatement != "FALSE"){
        // Progress from left to right, stopping at each || or && Operator (must be double)
        for (auto it = procStatement.begin(); it != procStatement.end(); it++){
            auto it_2 = it + 1; // The next character

            // Check for and/or operators
            if ((*it == '&' && *(it_2) == '&') || (*it == '|' && *(it_2) == '|')){
                // We have found an and/or operator
                bool left;
                bool right;

                bool escape = false;
                auto left_it_start = it - 1;
                auto left_it_end = left_it_start;
                // First, search left. If any of [')', procStatement.begin(), '|', or '&'] are found, stop
                // the .begin()-1 is to see if we're past the beginning character
                for (left_it_end; left_it_end != procStatement.begin()-1; left_it_end--){
                    if (*left_it_end == ')'){
                        left_it_end++;  // go back to the last valid position
                        escape = true;  // We have other work to do on this left parentheses first
                        break;
                    }

                    else if (*left_it_end == '|' || *left_it_end == '&' || *left_it_end == '(') {
                        left_it_end++;  // go back to the last valid position
                        escape = false; // We've captured a valid statement
                        break;
                    }
                }

                if (escape) {continue;} // We can't yet process this && statement
                

                // If it's past the end, we need to scoot it up 1
                if (left_it_end == procStatement.begin()-1){
                    left_it_end++;
                }
                string capturedStr_left(left_it_end, left_it_start+1); // Get the string associated with the LHS. This should be a proposition
                if (capturedStr_left.size() == 0){
                    capturedStr_left = *left_it_end;
                } 
                
                cout << "Left: " << capturedStr_left << endl;

                auto prop_left = propositions.find(capturedStr_left);
                if (prop_left != propositions.end()){
                    // It's a proposition
                    left = (*prop_left).second.boolVal;
                } else if (capturedStr_left[0] == '!' && propositions.find(capturedStr_left.substr(1)) != propositions.end()) {
                    // If there's a negate symbol and the remaining string is a proposition
                    prop_left = propositions.find(capturedStr_left.substr(1));
                    left = !(*prop_left).second.boolVal;
                } else if (capturedStr_left == "TRUE") {
                    left = true;
                }   else if (capturedStr_left == "FALSE") {
                    left = false;
                } else {
                    cout << "Invalid Right Proposition: " << capturedStr_left << endl;
                    continue;   // Invalid proposition
                }
                

                // Repeat for the right side now.

                escape = false;
                auto right_it_start = it_2 + 1;
                auto right_it_end = right_it_start;
                // First, search left. If any of ['(', procStatement.begin(), '|', or '&'] are found, stop
                for (right_it_end; right_it_end != procStatement.end(); right_it_end++){
                    if (*right_it_end == '('){
                        right_it_end--;  // go back to the last valid position
                        escape = true;  // We have other work to do on this right parentheses first
                        break;
                    }

                    else if (*right_it_end == '|' || *right_it_end == '&' || *right_it_end == ')') {
                        right_it_end--;  // go back to the last valid position
                        escape = false; // We've captured a valid statement
                        break;
                    }
                }

                if (escape) {continue;} // We can't yet process this && statement

                if (right_it_end == procStatement.end()){
                    right_it_end--;
                }
                string capturedStr_right(right_it_start, right_it_end+1); // Get the string associated with the LHS. This should be a proposition
                if (capturedStr_right.size() == 0){
                    capturedStr_right = *right_it_end;
                } 
                cout << "Right: " << capturedStr_right << endl;

                auto prop_right = propositions.find(capturedStr_right);
                if (prop_right != propositions.end()){
                    // It's a proposition
                    right = (*prop_right).second.boolVal;
                } else if (capturedStr_right[0] == '!' && propositions.find(capturedStr_right.substr(1)) != propositions.end()) {
                    // If there's a negate symbol and the remaining string is a proposition
                    prop_right = propositions.find(capturedStr_right.substr(1));
                    right = !(*prop_right).second.boolVal;
                } else if (capturedStr_right == "TRUE") {
                    right = true;
                }   else if (capturedStr_right == "FALSE") {
                    right = false;
                } else {
                    cout << "Invalid Right Proposition: " << capturedStr_right << endl;
                    continue;   // Invalid proposition
                }


                // We now have two valid propositions, connected by an AND or OR operator
                string replacement;
                if (*it == '&'){
                    // It's an AND
                    if (left && right){
                        replacement = "TRUE";
                    } else {
                        replacement = "FALSE";
                    }
                } else {
                    // It's an OR
                    if (left || right){
                        replacement = "TRUE";
                    } else {
                        replacement = "FALSE";
                    }
                }

                // We've evaluated the proposition. Replace it in the statement
                if (*(left_it_end-1) == '(' && *(right_it_end+1) == ')') {
                    left_it_end--;  // We want to replace the parentheses too
                    right_it_end++;  
                }
                right_it_end++;

                // If it's past the end, we need to scoot it up 1
                if (left_it_end == procStatement.begin()-1){
                    left_it_end++;
                }
                procStatement.replace(left_it_end, right_it_end, replacement);
                cout << "Updated Statement: " << procStatement << endl;
                
                escape_primed = false;

                break;
            }


            // We didn't find any available operators to act on. Let's see if we can condense parentheses
            if (*it == '('){
                bool closed = false;
                for (auto it_p = it+1; it_p != procStatement.end(); it_p++){
                    if (*it_p == '('){
                        break;  // We found another open parentheses
                    } else if (*it_p == ')') {
                        // We found a close parentheses (!!)

                        procStatement.erase(it_p);
                        procStatement.erase(it);

                        closed = true;
                        break;
                    }
                }
                if (closed) {break;}
            }


            // If we've reached here, it means we didn't find anything on the last pass.
            if (escape_primed && it == procStatement.end()-1) {
                exit = true;
                break;
            } else {
                escape_primed = true;
            }
        }
        
        // We've closed all the parentheses and checked for and/or's. Now check if there's any stand-alone variables
        // Query the whole statement as a variable
        bool standAlone;
        auto prop = propositions.find(procStatement);
        if (prop != propositions.end()){
            // It's a proposition
            standAlone = (*prop).second.boolVal;
        } else if (procStatement[0] == '!' && propositions.find(procStatement.substr(1)) != propositions.end()) {
            // If there's a negate symbol and the remaining string is a proposition
            prop = propositions.find(procStatement.substr(1));
            standAlone = !(*prop).second.boolVal;
        } else if (procStatement == "TRUE") {
            standAlone = true;
        }   else if (procStatement == "FALSE") {
            standAlone = false;
        } else {
            cout << "Invalid Stand-Alone Proposition: " << procStatement << endl;
            continue;   // Invalid proposition
        }
    
        if (standAlone) {
            procStatement = "TRUE";
            break;
        } else {
            procStatement = "FALSE";
            break;
        }


        // If nothing was found for two passes in a row, exit
        if (exit){
            throw std::runtime_error("Invalid proposition.");
            return false;
        }
    }

    // Now return the corresponding value to the string
    if (procStatement == "TRUE"){
        return true;
    } else {
        return false;
    }
    
}


string logic_parser::clearSpaces(string input){
    input.erase(std::remove_if(input.begin(), input.end(), [](char c) { return std::isspace(static_cast<unsigned char>(c)); }), input.end());
    return input;
}

void logic_parser::setStatement(string newStatement){
    statement = newStatement;
}

void logic_parser::addProp(string var, double val, string comparisonType){
    prop newProp;
    newProp.var = var;
    newProp.val = val;
    newProp.comparisonType = comparisonType;

    propositions[var] = newProp;
}

bool logic_parser::evalProp(string var, double val){
    if (propositions.find(var) != propositions.end()){
        // This is a valid propisition
        return propositions[var].eval(val);
    }

    throw std::runtime_error("Invalid proposition.");
    return false;
}