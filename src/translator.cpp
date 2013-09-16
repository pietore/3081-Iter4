/* Climate data mining DSL translator.

   Authors: Eric Ung, Billy Graham.

   This file contains the main function that controls the execution of
   the translator.

   It first reads the input program into a character buffer.

   If no errors occur, it calls the scanner.

 */

#include <iostream>
#include "regex.h"
#include "scanner.h"
#include "readInput.h"
#include "Parser.h"

using namespace std ;

//no arguments currently
int main(int argc, char **argv) {

	char* fileBuffer = readInput(argc, argv);
	if( fileBuffer == NULL ){
		return -1;
	}

	Parser* parser;
	parser = new Parser();
	DeclListNode* head = NULL;
	ParseResult pr;
	pr = parser->parse( fileBuffer );

	string res;

	head = (DeclListNode*)pr.ast;
	if( pr.ok ) {
		res = head->cppCode();
		res += "\n\n============\n\n";
		res += head->unparse();
		cout << res;
	} else {
		cout << pr.errors << "\n";
	}
	


//	freeTokens(headTokn);
	// cout << "Thanks for using the translator app." << endl ;

}
