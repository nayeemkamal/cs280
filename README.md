# cs280
CS280 is 'Programming Language Concepts' in this class we learn the common grammars of all programming languages enabling us to quickly learn languages.

Our coursework involves the fundamentals needed to build a complete build system for a made up programming language.

### Program 2

Program2 consists of the lexer, which interprets the required grammar in a language and returns a series of `lexemes` which are the little bits and pieces that make up programming statements. Some examples of lexemes are:
 * string
 * integer
 * comment
 * mathematical operators
 * assignment operators
 * bitwise operators
 
The primary goal of the lexer is to preprocess raw code and feed it into the compiler which will complete the next step of the compilation process.

Compile with `g++ --std=c++11 -Wall -Werror -Wno-sign-compare -g *.cpp -o prog2`

### Program 3

