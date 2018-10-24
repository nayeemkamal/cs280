#include <iostream>
#include <fstream>
#include <string.h>
#include "tokens.h"

using namespace std;

/*
return Token(token type, lexeme, line#)
return Token(Done, "", lineNum)

-v every token is printed
-sum if present, summary information is printed
-allids a list of the lexemes for all identifiers printed in
    alphabetical order
filename read from the filename; otherwise read from standard in

getNextToken(istream * ...)
istream *in;
in = & cin;
    or
in = & some ifstream;

*/

istream *in = &cin;

Token tok;
TokenType tt = tok.GetTokenType();


int main(int argc, char* argv[]) {
    //args
    //int numfiles;
    bool isfile;
    bool v;
    //bool sum;
    //bool allids;

    int lineNum;
    //int stringCt;
    //int identCt;
    //int tokenCount;

    string arg1;
    string source;

    for(int i=1; i < argc; i++) {
        //numfiles = 0;
        arg1 = argv[i];
        //Done: arg tester
        if(in) {
            ;
        }
        if(arg1[0] == '-') {
            if(arg1 == "-v") {
                //do -v
                v = true;
            } else if(arg1 == "-sum") {
                //do sum
                ;
            } else if(arg1 == "-allids") {
                //do allids
                ;
            } else {
                cout << "INVALID FLAG " << arg1 << endl;
                return 2;
            }
        } else {
            //arg must be a filename test it
            isfile = true;
            source = argv[i];   
        }
        //handle files if you have them2
        ifstream iFile;
        if(isfile) {
            iFile.open(source);
            if(i < argc - 1) {
                cout << "TOO MANY FILE NAMES" << endl;
                return 3;
            } else if(!iFile.is_open()) {
                cerr << "UNABLE TO OPEN " << source << endl;
            } else {
            in = &iFile;
                while((tok = getNextToken(&iFile, &lineNum)) != ERR && tok != DONE) {
                // handle verbose mode
                    if(v) {
                        if(tok.GetTokenType() == ERR) {
                            cout << "Error on line " << &lineNum;
                        }
                        cout << tok << endl;
                    }
            //TODO: keep statistics for other flags
                }
            }
        }

        //SLIDE: getNextToken shit
        /*
        lineNum = 0;
        while((tok = getNextToken(in, &lineNum)) != ERR && tok != DONE) {
            // handle verbose mode
            if(v) {
                cout << tok << endl;
            }
            //TODO: keep statistics for other flags
        }*/

    }
}