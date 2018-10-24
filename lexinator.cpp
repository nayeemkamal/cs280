#include <map>
#include <string.h>
#include <cctype>
#include "tokens.h"

//track all tokentypes from tokens.h
static std::map<TokenType, std::string> TokenMap {
    {PRINT, "PRINT"},
    {IF, "IF"},
    {THEN, "THEN"},
    {TRUE, "TRUE"},
    {FALSE, "FALSE"},
    {IDENT, "IDENT"},
    {ICONST, "ICONST"},
    {SCONST, "SCONST"},
    {PLUS, "PLUS"},
    {MINUS, "MINUS"},
    {STAR, "STAR"},
    {SLASH, "SLASH"},
    {ASSIGN, "ASSIGN"},
    {EQ, "EQ"},
    {NEQ, "NEQ"},
    {LT, "LT"},
    {LEQ, "LEQ"},
    {GT, "GT"},
    {GEQ, "GEQ"},
    {LOGICAND, "LOGICAND"},
    {LOGICOR, "LOGICOR"},
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {SC, "SC"},
    {ERR, "ERR"},
    {DONE, "DONE"}
};
//redir istream to cout
ostream& operator<<(ostream& out, const Token &tok) {
    TokenType tt = tok.GetTokenType();
    //output whatever token you match from the map
    out << TokenMap[tt];
    //check a few tokentypes including string and int
    if(tt == IDENT || tt == SCONST || tt == ICONST || tt == ERR) {
        out << "(" << tok.GetLexeme() << ")";
    }
    return out;
}

Token getNextToken(istream *in, int *lineNum) {
    //TokenType tt = tok.GetTokenType(); //test tok
    //from slide
    enum LexState {BEGIN, INID, INSTRING, INCOMMENT, /* do more later */};
    string lexeme;
    char ch;
    LexState state = BEGIN;
   
    //deref instream, istream::peek didn't work?
    while(in->get(ch)) {
        //grab chars / close lines
        if(ch == '\n') {
            (*lineNum)++;
        }
        //lexemes for strings and declarations
        switch(state) {
            //begin case
            case BEGIN:
                if(isspace(ch)) {
                    continue; //move on to next word if you see a space
                }
                
                lexeme = ch; //save the char
                //Identifier stuff
                if(isalpha(ch)) {
                    state = INID;
                } else if(isdigit(ch)) {
                    ;//state = ININT;
                } else if( ch == '"' ) {
                    //string stuff
                    state = INSTRING;
                } else {
                    // operators
                    TokenType tt = ERR;
                    switch(ch) {
                        case '+':
                            tt = PLUS; 
                        case '*':
                            tt = STAR;
                        case '/':
                            tt = SLASH;
                        case '-':
                            tt = MINUS;
                        case '#':
                            state = INCOMMENT;
                        case '=':
                            //two char ops are strange
                            lexeme.push_back(ch);
                            ch = in->peek();
                            lexeme.push_back(ch);
                            if(ch == '=') {
                                tt = EQ;
                            } else if(' ') {
                                tt = ASSIGN;
                            } else {
                                return Token(ERR, lexeme, *lineNum);
                            }
                        case '!':
                        //two char ops are strange
                            lexeme.push_back(ch);
                            ch = in->peek();
                            lexeme.push_back(ch);
                            if(ch == '=') {
                                tt = NEQ;
                            } else {
                                //tf is that?
                                return Token(ERR, lexeme, *lineNum);
                            }
                        case '<':
                            //two char ops are strange
                            lexeme.push_back(ch);
                            ch = in->peek();
                            lexeme.push_back(ch);
                            if(ch == '=') {
                                tt = LEQ;
                            }
                            tt = LT;
                        case '>':
                            //two char ops are strange
                            lexeme.push_back(ch);
                            ch = in->peek();
                            lexeme.push_back(ch);
                            if(ch == '=') {
                                tt = GEQ;
                            }
                            tt = LT;
                        case '&':
                            //two char ops are strange
                            lexeme.push_back(ch);
                            ch = in->peek();
                            lexeme.push_back(ch);
                            if(ch == '&') {
                                tt = LOGICAND;
                            }
                            tt = LT;
                        case '|':
                            //two char ops are strange
                            lexeme.push_back(ch);
                            ch = in->peek();
                            lexeme.push_back(ch);
                            if(ch == '|') {
                                tt = LOGICOR;
                            }
                            tt = LT;
                        case '(':
                            //two char ops are strange
                                tt = LPAREN;
                        case ')':
                            //two char ops are strange
                                tt = RPAREN;
                        case ';':
                                tt = SC;                 
                    } //end opcase
                    return Token(tt, lexeme, *lineNum);
                    //cant return in case statements
                    
                } //end stringbs
                break;
                //end begin case
            //identifiers
            case INID:
                if(isalpha(ch) || isdigit(ch)) {
                    lexeme += ch;
                } else {
                    if(ch == '\n')
                        in->putback(ch);
                }
                return Token(IDENT, lexeme, *lineNum);
                //break; for later
            //finish strings
            case INSTRING:
                lexeme += ch;
                if(ch == '\n') {
                    return Token(ERR, lexeme, *lineNum);
                }
                if(ch == '"') {
                    lexeme = lexeme.substr(1, lexeme.length()-2);
                    return Token(SCONST, lexeme, *lineNum);
                }
                break; //start the case over
            case INCOMMENT:
                ;
        }
    }
    
    if( in->eof() )
        return Token(DONE, "", *lineNum);
    
    return Token(ERR, lexeme, *lineNum);
}