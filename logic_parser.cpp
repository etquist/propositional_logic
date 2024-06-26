#include "logic_parser.h"

   

bool logic_parser::evaluate(){
    // Save the original logic statement
    // Remove spaces from the statement
    const std::string originalStatement = clearSpaces(statement);
    std::string procStatement = originalStatement;


    bool escape_primed = false;
    bool exit = false;
    bool skip_parentheses_standAlone;
    while (procStatement != "TRUE" && procStatement != "FALSE"){
        skip_parentheses_standAlone = false;

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
                std::string capturedStr_left(left_it_end, left_it_start+1); // Get the string associated with the LHS. This should be a proposition
                if (capturedStr_left.size() == 0){
                    capturedStr_left = *left_it_end;
                } 
                
                std::cout << "Left: " << capturedStr_left << std::endl;

                bool negate = false;
                // See how many negate symbols we have
                while (capturedStr_left[0] == '!'){
                    negate = !negate;
                    capturedStr_left = capturedStr_left.substr(1);
                }

                auto prop_left = propositions.find(capturedStr_left);
                if (prop_left != propositions.end()){
                    // It's a proposition
                    left = (*prop_left).second.boolVal;
                } else if (capturedStr_left == "TRUE") {
                    left = true;
                }   else if (capturedStr_left == "FALSE") {
                    left = false;
                } else {
                    std::cout << "Invalid Right Proposition: " << capturedStr_left << std::endl;
                    continue;   // Invalid proposition
                }
                
                if (negate){
                    left = !left;
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
                std::string capturedStr_right(right_it_start, right_it_end+1); // Get the string associated with the LHS. This should be a proposition
                if (capturedStr_right.size() == 0){
                    capturedStr_right = *right_it_end;
                } 
                std::cout << "Right: " << capturedStr_right << std::endl;

                
                negate = false;
                // See how many negate symbols we have
                while (capturedStr_right[0] == '!'){
                    negate = !negate;
                    capturedStr_right = capturedStr_right.substr(1);
                }

                auto prop_right = propositions.find(capturedStr_right);
                if (prop_right != propositions.end()){
                    // It's a proposition
                    right = (*prop_right).second.boolVal;
                } else if (capturedStr_right == "TRUE") {
                    right = true;
                }   else if (capturedStr_right == "FALSE") {
                    right = false;
                } else {
                    std::cout << "Invalid Right Proposition: " << capturedStr_right << std::endl;
                    continue;   // Invalid proposition
                }

                if (negate){
                    right = !right;
                }


                // We now have two valid propositions, connected by an AND or OR operator
                std::string replacement;
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
                std::cout << "Updated Statement: " << procStatement << std::endl;
                
                escape_primed = false;

                skip_parentheses_standAlone = true;
                exit = false;

                break;
            }

            // If we've reached here, it means we didn't find anything on the last pass.
            if (escape_primed && it == procStatement.end()-1) {
                exit = true;
                break;
            } else {
                escape_primed = true;
            }
        }
        
        // If we condensed the statement already, don't do it again
        if (skip_parentheses_standAlone){
            continue;
        }

        // We didn't find any available operators to act on. Let's see if we can condense parentheses
        for (auto it = procStatement.begin(); it != procStatement.end(); it++){
            if (*it == '('){
                bool closed = false;
                for (auto it_p = it+1; it_p != procStatement.end(); it_p++){
                    if (*it_p == '('){
                        break;  // We found another open parentheses
                    } else if (*it_p == ')') {
                        // We found a close parentheses (!!)

                        procStatement.erase(it_p);
                        procStatement.erase(it);

                        std::cout << "Removed parentheses." << std::endl;

                        exit = false;
                        closed = true;
                        break;
                    }
                }
                if (closed) {break;}
            }
        }


        // We've closed all the parentheses and checked for and/or's. Now check if there's any stand-alone variables
        // Query the whole statement as a variable
        bool standAlone;
        
        bool negate = false;
        // See how many negate symbols we have
        while (procStatement[0] == '!'){
            negate = !negate;
            procStatement = procStatement.substr(1);
        }

        auto prop = propositions.find(procStatement);
        if (prop != propositions.end()){
            // It's a proposition
            standAlone = (*prop).second.boolVal;
        } else if (procStatement == "TRUE") {
            standAlone = true;
        }   else if (procStatement == "FALSE") {
            standAlone = false;
        } else {
            std::cout << "Invalid Stand-Alone Proposition: " << procStatement << std::endl;
            if (!exit){
                exit = true; // next time around, kill it
                continue;
            } 
        }

        if (negate){
            standAlone = !standAlone;
        }
    
        if (standAlone && !exit) {
            procStatement = "TRUE";
            break;
        } else if (!standAlone && !exit){
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
    } else if (procStatement == "FALSE") {
        return false;
    } else {
        throw std::runtime_error("Invalid proposition.");   // Throw an error if we couldn't fully evaluate it.
        return false;
    }
    
}


std::string logic_parser::clearSpaces(std::string input){
    input.erase(std::remove_if(input.begin(), input.end(), [](char c) { return std::isspace(static_cast<unsigned char>(c)); }), input.end());
    return input;
}

void logic_parser::setStatement(std::string newStatement){
    statement = newStatement;
}

void logic_parser::addProp(std::string var, double val, std::string comparisonType){
    prop newProp;
    newProp.var = var;
    newProp.val = val;
    newProp.comparisonType = comparisonType;

    propositions[var] = newProp;
}

void logic_parser::deleteProp(std::string var){
    if (propositions.find(var) != propositions.end()){
        // This is a valid propisition
        propositions.erase(var);
    } 
    throw std::runtime_error("Invalid proposition.");
}

void logic_parser::updateProp(std::string var, double val, std::string comparisonType){
    if (propositions.find(var) != propositions.end()){
        // This is a valid propisition
        propositions[var].val = val;
        propositions[var].comparisonType = comparisonType;
    } else{
        addProp(var, val, comparisonType);
    }
}

bool logic_parser::evalProp(std::string var, double val){
    if (propositions.find(var) != propositions.end()){
        // This is a valid propisition
        return propositions[var].eval(val);
    }

    throw std::runtime_error("Invalid proposition.");
    return false;
}

std::set<std::string> logic_parser::getPropositions(){
    std::set<std::string> props;
    for (auto prop : propositions){
        props.insert(prop.first);
    }
    return props;
}


std::string logic_parser::preParseStatement(std::string statement_str, std::unordered_map<std::string, double> vars){
    std::set<std::string> validOps = {"<<", "<=", ">=", ">>", "==", "!="};

    // Remove whitespace
    statement_str.erase(std::remove_if(statement_str.begin(), statement_str.end(), [](char c) { return std::isspace(static_cast<unsigned char>(c)); }), statement_str.end());

    // Freehand form: e.g., sim!=1||((speed<=5)&&temp==5)
    // First, take all of the global variables (vars) and replace them with their corresponding value
    for (auto var : vars){
        std::string query = var.first;
        std::string replacement = std::to_string(var.second);   // Prep the number to be swapped in

        size_t start_pos = 0;
        while((start_pos = statement_str.find(query, start_pos)) != std::string::npos) {
            statement_str.replace(start_pos, query.length(), replacement);
            start_pos += replacement.length(); // Handles case where 'to' is a shorter than 'from'
        }
    }

    // Next, search for all of the valid operators and evaluate the expressions they encompass
    // E.g.: found: "!=" -> evaluate: sim_Val != 1, where sim_Val was replaced in the last step by the true value
    // Evaluated expressions are replaced with TRUE or FALSE
    for (auto op : validOps){
        size_t start_pos = 0;
        while((start_pos = statement_str.find(op, start_pos)) != std::string::npos){
            std::cout << statement_str << std::endl;
            // While we can find more of this operator
            // the first operator is at the position "start_pos"

            std::string::iterator it = statement_str.begin() + start_pos; //Set the iterator at the left character of the operator pair

            bool escape = false;
            auto left_it_start = it - 1;
            auto left_it_end = left_it_start;
            // First, search left. If any of [')', procStatement.begin(), '|', or '&'] are found, stop
            // the .begin()-1 is to see if we're past the beginning character
            for (left_it_end; left_it_end != statement_str.begin()-1; left_it_end--){
                if (*left_it_end == ')'){
                    left_it_end++;  // go back to the last valid position
                    escape = true;  // We have other work to do on this left parentheses first

                    std::string errorMsg = "Error: Invalid Statement; " + statement_str;
                    throw std::runtime_error(errorMsg);

                    return "Invalid String";
                }

                else if (*left_it_end == '|' || *left_it_end == '&' || *left_it_end == '(' || *left_it_end == '!') {
                    left_it_end++;  // go back to the last valid position
                    escape = false; // We've captured a valid statement
                    break;
                }
            }

            // If it's past the end, we need to scoot it up 1
            if (left_it_end == statement_str.begin()-1){
                left_it_end++;
            }
            std::string capturedStr_left(left_it_end, left_it_start+1); // Get the string associated with the LHS. This should be a proposition
            if (capturedStr_left.size() == 0){
                capturedStr_left = *left_it_end;
            }
            std::cout << "Left: " << capturedStr_left << std::endl;
            double lhs = std::stod(capturedStr_left);
            

            escape = false;
            auto right_it_start = it + 2; // Start 1 to the right of the operator pair
            auto right_it_end = right_it_start;
            // First, search left. If any of ['(', procStatement.begin(), '|', or '&'] are found, stop
            for (right_it_end; right_it_end != statement_str.end(); right_it_end++){
                if (*right_it_end == '('){
                    right_it_end--;  // go back to the last valid position
                    escape = true;  // We have other work to do on this right parentheses first
                    
                    std::string errorMsg = "Error: Invalid Statement; " + statement_str;
                    throw std::runtime_error(errorMsg);

                    return "Invalid String";
                }

                else if (*right_it_end == '|' || *right_it_end == '&' || *right_it_end == ')' || *right_it_end == '!') {
                    right_it_end--;  // go back to the last valid position
                    escape = false; // We've captured a valid statement
                    break;
                }
            }


            if (right_it_end == statement_str.end()){
                right_it_end--;
            }
            std::string capturedStr_right(right_it_start, right_it_end+1); // Get the string associated with the LHS. This should be a proposition
            if (capturedStr_right.size() == 0){
                capturedStr_right = *right_it_end;
            } 
            std::cout << "Right: " << capturedStr_right << std::endl;
            double rhs = std::stod(capturedStr_right);
            
            // Evaluate:
            bool replacement;
            if (op == "<<"){
                replacement = lhs < rhs;
            } else if (op == "<="){
                replacement = lhs <= rhs;
            } else if (op == ">="){
                replacement = lhs >= rhs;
            } else if (op == ">>"){
                replacement = lhs > rhs;
            } else if (op == "!="){
                replacement = lhs != rhs;
            } else if (op == "=="){
                replacement = lhs == rhs;
            }

            std::string replacementStr;
            if (replacement){
                replacementStr = "TRUE";
            } else {
                replacementStr = "FALSE";
            }

            // We've evaluated the proposition. Replace it in the statement
            if (*(left_it_end-1) == '(' && *(right_it_end+1) == ')') {
                left_it_end--;  // We want to replace the parentheses too
                right_it_end++;  
            }
            right_it_end++;

            // If it's past the end, we need to scoot it up 1
            if (left_it_end == statement_str.begin()-1){
                left_it_end++;
            }
            statement_str.replace(left_it_end, right_it_end, replacementStr);
            std::cout << "Updated Statement: " << statement_str << std::endl;
        }
    }
    return statement_str;
}


bool logic_parser::evaluateStandAlone(std::string statement, std::unordered_map<std::string, double> vars){
    std::string formattedStatement = preParseStatement(statement, vars);
    setStatement(formattedStatement);
    return evaluate();
}

std::string logic_parser::getStatement(){
    return statement;
}
