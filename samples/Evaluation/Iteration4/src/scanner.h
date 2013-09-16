#ifndef SCANNER_H
#define SCANNER_H

#include "regex.h"
#include <string>
#include <stdio.h>
using namespace std;

class Regexx ;
class Token ;

/* This enumerated type is used to keep track of what kind of
   construct was matched. 
*/
enum tokenEnumType { 

	// Keywords
	letKwd, inKwd, endKwd, ifKwd, thenKwd, elseKwd, 
	printKwd, readKwd, writeKwd, 
	integerKwd, floatKwd, booleanKwd, stringKwd, 
	trueKwd, falseKwd, headKwd, tailKwd, nullKwd, 
	mapKwd, filterKwd, foldKwd, zipKwd,

	// Constants
	intConst, floatConst, stringConst, 

	// Names
	variableName ,

	// Punctuation
	leftParen, rightParen, 
	leftSquare, rightSquare, leftAngle, rightAngle,
	colon, colonColon, comma, semiColon, 
	equalsSign, 

	plusSign, star, dash, forwardSlash, percent, backSlash,
	arrow, equalsEquals, lessThanEquals, greaterThanEquals, 
	notEquals, plusPlus, 
		    
	dotDot, tupleOp,

	endOfFile,
	lexicalError,
	nothing
} ;

typedef enum tokenEnumType tokenType ;

// Below you need to write your class definitions for Token and Scanner.

class Token {
public:
  Token* next;
  tokenType terminal;
  string lexeme;
} ;


class Scanner {
public:
  Token* scan (const char *) ;
  regex_t ignorable;
  Scanner();
  Token* attemptMatch(const char* buffer);
  Regexx* regex;
} ;


int consumeWhiteSpaceAndComments( regex_t *ignorable, const char *text );
Token* makeToken( tokenType terminal, const char* buffer, int size );
void freeTokens( Token* tokn );

class Regexx {
public:
	// Keywords
	 
	regex_t letKwdRegE;
	regex_t inKwdRegE;
	regex_t endKwdRegE;
	regex_t ifKwdRegE;
	regex_t thenKwdRegE;
	regex_t elseKwdRegE;
	 
	regex_t printKwdRegE;
	regex_t readKwdRegE;
	regex_t writeKwdRegE;
	regex_t integerKwdRegE;
	regex_t floatKwdRegE;
	regex_t booleanKwdRegE;
	regex_t stringKwdRegE;
	regex_t trueKwdRegE;
	regex_t falseKwdRegE;
	regex_t headKwdRegE;
	regex_t tailKwdRegE;
	regex_t nullKwdRegE;

	regex_t mapKwdRegE;
	regex_t filterKwdRegE;
	regex_t foldKwdRegE;
	regex_t zipKwdRegE;

	// Constants
	regex_t intConstRegE;
	regex_t floatConstRegE;
	regex_t stringConstRegE;

	// Names
	regex_t variableNameRegE;

	
	// Punctuation
	regex_t leftParen;
	regex_t rightParen;
	regex_t leftSquare;
	regex_t rightSquare;
	regex_t leftAngle;
	regex_t rightAngle;
	regex_t colon;
	regex_t colonColon;
	regex_t comma;
	regex_t semiColon;
	regex_t equalsSign;
	
	// Math Operations
	regex_t plusSign;
	regex_t star;
	regex_t dash;
	regex_t forwardSlash;
	regex_t percent;
	regex_t backSlash;
	regex_t arrow;
	regex_t equalsEquals;
	regex_t lessThanEquals;
	regex_t greaterThanEquals;
	regex_t notEquals;
	regex_t plusPlus;
	
	// Special
	regex_t dotDot;
	regex_t tupleOp;

	// end of file and errors
	regex_t endOfFileRegE;
	regex_t lexicalErrorRegE;

	Regexx();

}; // end class Regexx


#endif /* SCANNER_H */
