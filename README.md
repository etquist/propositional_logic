# Propositional Logic Parser
A simple class for evaluating custom propositional logic statements encoded in text.

This has two primary components:
  - A map of propositions defined by the user, of which describe the valid statements that can be used.
  - A statement parser, which can interpret AND (&&), OR (||), and negate (!) symbols, and use order of operations as defined with parentheses to properly interpret a propositional logic statement.
  - A statement pre-parset, which can process a single statement with an associated map of variables and values.

A sample statement could be: (A && !B) || C || !(D && B),
  which, after defining the values of A, B, C, and D, can be reduced to a single true or false boolean.

By using the preparser, this statement could be (speed << 5 && !temp >> 67) || waveHeight <= 3 || !(status == 1 && temp >> 67),
  which could be solved when passed with a map of {speed : 4, temp : 65, waveHeight : 7, status : 1}.


# Installation Instructions
This code is written in C++, and is contained in a single class: "Logic_Parser". Include "logic_parser.cpp" and "logic_parser.h" in your build to access them in your code.


# Testing Suite
Running the main.cpp file will test the parser over 15 different cases, including some edge cases dealing with order of operations, double negates, and stacked parentheses.
