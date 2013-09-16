#include <cxxtest/TestSuite.h>
#include "readInput.h"
#include "scanner.h"
#include <string.h>
#include <iostream>

using namespace std ;

class ScannerTestSuite : public CxxTest::TestSuite 
{
public:
    /* A Scanner object is created in the test_setup_code method.
       This is a test, beginning with "test_", so that it is executed
       by the testing framework.  The scanner is used in some tests of
       the method "scan".
     */
    Scanner *s ;
    void test_setup_code ( ) {
        s = new Scanner() ;
	TS_ASSERT( s != NULL );
    }

    // Tests for "scan"
    // --------------------------------------------------

    /* Below are some helper functions and sample tests for testing the 
       "scan" method on Scanner.
    */

    // Test that a list of tokens has no lexicalError tokens.
    bool noLexicalErrors (Token *tks) {
        Token *currentToken = tks ;
        while (currentToken != NULL) {
            if (currentToken->terminal == lexicalError) {
                return false ;
            }
            else {
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }


    /* This function checks that the terminal fields in the list of
       tokens matches a list of terminals.
    */
    bool sameTerminals (Token *tks, int numTerms, tokenType *ts) {
        Token *currentToken = tks ;
        int termIndex = 0 ;
        while( currentToken != NULL && termIndex < numTerms ) {
            if( currentToken->terminal != ts[termIndex] ) {
                return false ;
            }
            else {
                ++ termIndex ;
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }

   
  
    // When a lexical error occurs, the scanner creates a token with a 
    // single-character lexeme and lexicalError as the terminal.
    void test_scan_lexicalError_Advanced ( ) {
        Token *tks = s->scan ("~ !@ .../*32.a!#k32*/") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "~");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "!");
        tks = tks->next ;
		TS_ASSERT (tks != NULL) ;
		TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
		TS_ASSERT_EQUALS (tks->lexeme, "@");
		tks = tks->next ;
		
		TS_ASSERT (tks != NULL) ;
		TS_ASSERT_EQUALS (tks->terminal, dotDot) ;
        TS_ASSERT_EQUALS (tks->lexeme, "..");
        tks = tks->next ;
        
		TS_ASSERT (tks != NULL) ;
		TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, ".");
        tks = tks->next ;
		TS_ASSERT (tks != NULL) ;
		TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
		TS_ASSERT (tks->next == NULL) ;
    }



} ;





