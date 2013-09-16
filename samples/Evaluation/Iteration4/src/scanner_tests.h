#include <cxxtest/TestSuite.h>
#include "readInput.h"
#include "scanner.h"

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
    }


    // Tests for components and functions used by "scan"
    // --------------------------------------------------

    /* You will need to write several tests to adequately test the
       functions that are called from "scan".  Once you are confident
       that the components used by "scan" work properly, then you can
       run tests on the "scan" method itself.
    */

    // Here you should place tests for these other functions.

	void test_consume_comment(){
	int numMatchedChars;

	char string[26] = "/*comment */";
		numMatchedChars = consumeWhiteSpaceAndComments(&(s->ignorable), &string[0]);
		TS_ASSERT( numMatchedChars == 12 );
	}


    void test_consume_whitespace(){
	int numMatchedChars;

	char string[26] = "      ";
	numMatchedChars = consumeWhiteSpaceAndComments(&(s->ignorable), &string[0]);
	TS_ASSERT( numMatchedChars == 6 );
    }


    void test_consume_whitespace_and_comments(){
	int numMatchedChars;

	char string[26] = " /*comment */   /**/ ";
	numMatchedChars = consumeWhiteSpaceAndComments(&(s->ignorable), &string[0]);
	TS_ASSERT( numMatchedChars == 21 );
    }

    void test_consume_whitespace_and_comments_and_text(){
	int numMatchedChars;

	char string[33] = " /*comment */   /**/ garbage";
	numMatchedChars = consumeWhiteSpaceAndComments(&(s->ignorable), &string[0]);
	TS_ASSERT( numMatchedChars == 21 );
    }

    void test_consume_whitespace_and_comments_and_text_with_word(){
	int numMatchedChars;

	char string[35] = "wordup /*comment */   /**/ garbage";
	numMatchedChars = consumeWhiteSpaceAndComments(&(s->ignorable), &string[0]);
	TS_ASSERT( numMatchedChars == 0 );
    }

    void test_attemptMatch_main(){
	Token* ptr = s->attemptMatch("main");
	TS_ASSERT( ptr->lexeme == "main" ); 
	TS_ASSERT( ptr->terminal == variableName );
    }
    
    /* Simple punctuation tests for each expression using scan*/
    void test_mainisVariableSymbol(){
	    Token *tks = s->scan ("main") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "main");
        TS_ASSERT_EQUALS (tks->terminal, variableName);
        tks = tks->next ;
    }
    
    
    void test_letKwdSymbol(){
	    Token *tks = s->scan ("let") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "let");
        TS_ASSERT_EQUALS (tks->terminal, letKwd);
        tks = tks->next ;
    }
    
    void test_inKwdSymbol(){
	    Token *tks = s->scan ("in") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "in");
        TS_ASSERT_EQUALS (tks->terminal, inKwd);
        tks = tks->next ;
    }
    
    void test_endKwdSymbol(){
	    Token *tks = s->scan ("end") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "end");
        TS_ASSERT_EQUALS (tks->terminal, endKwd);
        tks = tks->next ;
    }
    
    
    void test_ifKwdSymbol(){
	    Token *tks = s->scan ("if") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "if");
        TS_ASSERT_EQUALS (tks->terminal, ifKwd);
        tks = tks->next ;
    }
    
    void test_thenKwdSymbol(){
	    Token *tks = s->scan ("then") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "then");
        TS_ASSERT_EQUALS (tks->terminal, thenKwd);
        tks = tks->next ;
    }
    
    
    void test_elseKwdSymbol(){
	    Token *tks = s->scan ("else") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "else");
        TS_ASSERT_EQUALS (tks->terminal, elseKwd);
        tks = tks->next ;
    }
    
    void test_printKwdSymbol(){
	    Token *tks = s->scan ("print") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "print");
        TS_ASSERT_EQUALS (tks->terminal, printKwd);
        tks = tks->next ;
    }
    
    void test_readKwdSymbol(){
	    Token *tks = s->scan ("read") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "read");
        TS_ASSERT_EQUALS (tks->terminal, readKwd);
        tks = tks->next ;
    }
    
    void test_writeKwdSymbol(){
	    Token *tks = s->scan ("write") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "write");
        TS_ASSERT_EQUALS (tks->terminal, writeKwd);
        tks = tks->next ;
    }
    
    void test_integerKwdSymbol(){
	    Token *tks = s->scan ("Integer") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "Integer");
        TS_ASSERT_EQUALS (tks->terminal, integerKwd);
        tks = tks->next ;
    }
    
    
    void test_floatKwdSymbol(){
	    Token *tks = s->scan ("Float") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "Float");
        TS_ASSERT_EQUALS (tks->terminal, floatKwd);
        tks = tks->next ;
    }
    
    void test_booleanKwdSymbol(){
	    Token *tks = s->scan ("Boolean") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "Boolean");
        TS_ASSERT_EQUALS (tks->terminal, booleanKwd);
        tks = tks->next ;
    }
    
    void test_stringKwdSymbol(){
	    Token *tks = s->scan ("String") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "String");
        TS_ASSERT_EQUALS (tks->terminal, stringKwd);
        tks = tks->next ;
    }
    
    void test_trueKwdSymbol(){
	    Token *tks = s->scan ("true") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "true");
        TS_ASSERT_EQUALS (tks->terminal, trueKwd);
        tks = tks->next ;
    }
    
    void test_falseKwdSymbol(){
	    Token *tks = s->scan ("false") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "false");
        TS_ASSERT_EQUALS (tks->terminal, falseKwd);
        tks = tks->next ;
    }
    
    void test_headKwdSymbol(){
	    Token *tks = s->scan ("head") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "head");
        TS_ASSERT_EQUALS (tks->terminal, headKwd);
        tks = tks->next ;
    }
    
    void test_tailKwdSymbol(){
	    Token *tks = s->scan ("tail") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "tail");
        TS_ASSERT_EQUALS (tks->terminal, tailKwd);
        tks = tks->next ;
    }
    
    void test_nullKwdSymbol(){
	    Token *tks = s->scan ("null") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "null");
        TS_ASSERT_EQUALS (tks->terminal, nullKwd);
        tks = tks->next ;
    }
    
    void test_zipKwdSymbol(){
	    Token *tks = s->scan ("zip") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "zip");
        TS_ASSERT_EQUALS (tks->terminal, zipKwd);
        tks = tks->next ;
    }
    
    void test_mapKwdSymbol(){
	    Token *tks = s->scan ("map") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "map");
        TS_ASSERT_EQUALS (tks->terminal, mapKwd);
        tks = tks->next ;
    }
    
    void test_filterKwdSymbol(){
	    Token *tks = s->scan ("filter") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "filter");
        TS_ASSERT_EQUALS (tks->terminal, filterKwd);
        tks = tks->next ;
    }
    
    void test_foldKwdSymbol(){
	    Token *tks = s->scan ("fold") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "fold");
        TS_ASSERT_EQUALS (tks->terminal, foldKwd);
        tks = tks->next ;
    }
    
    void test_intConstSymbol(){
	    Token *tks = s->scan ("234") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "234");
        TS_ASSERT_EQUALS (tks->terminal, intConst);
        tks = tks->next ;
    }
    
	void test_floatConstSymbol(){
	    Token *tks = s->scan ("2.34") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "2.34");
        TS_ASSERT_EQUALS (tks->terminal, floatConst);
        tks = tks->next ;
    }
    
    void test_stringConstKwdSymbol(){
	    Token *tks = s->scan ("\"askdjf\"") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "\"askdjf\"");
        TS_ASSERT_EQUALS (tks->terminal, stringConst);
        tks = tks->next ;
    }
    
    void test_variableKwdSymbol(){
	    Token *tks = s->scan ("gooey") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "gooey");
        TS_ASSERT_EQUALS (tks->terminal, variableName);
        tks = tks->next ;
    }
	
	/* Simple punctuation tests for each expression */
    void test_leftParenSymbol(){
	    Token *tks = s->scan ("(") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "(");
        TS_ASSERT_EQUALS (tks->terminal, leftParen) ;
        tks = tks->next ;
    }
    
    void test_rightParenSymbol(){
	    Token *tks = s->scan (")") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, ")");
        TS_ASSERT_EQUALS (tks->terminal, rightParen) ;
        tks = tks->next ;
    }
    
    void test_leftSquareSymbol(){
	    Token *tks = s->scan ("[") ;
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "[");
        TS_ASSERT_EQUALS (tks->terminal, leftSquare) ;
        tks = tks->next ;
    }
    
    void test_rightSquareSymbol(){
	    Token *tks = s->scan ("]");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "]");
        TS_ASSERT_EQUALS (tks->terminal, rightSquare) ;
        tks = tks->next ;
    }

    void test_leftAngleSymbol(){
	    Token *tks = s->scan ("<");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "<");
        TS_ASSERT_EQUALS (tks->terminal, leftAngle) ;
        tks = tks->next ;
    }
    
    void test_rightAngleSymbol(){
	    Token *tks = s->scan (">");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, ">");
        TS_ASSERT_EQUALS (tks->terminal, rightAngle) ;
        tks = tks->next ;
    }

    void test_colonSymbol(){
	    Token *tks = s->scan (":");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, ":");
        TS_ASSERT_EQUALS (tks->terminal, colon) ;
        tks = tks->next ;
    }
    
	void test_colonColonSymbol(){
	    Token *tks = s->scan ("::");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "::");
        TS_ASSERT_EQUALS (tks->terminal, colonColon) ;
        tks = tks->next ;
    }
    
	void test_commaSymbol(){
	    Token *tks = s->scan (",");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, ",");
        TS_ASSERT_EQUALS (tks->terminal, comma) ;
        tks = tks->next ;
    }
    
	void test_semiColonSymbol(){
	    Token *tks = s->scan (";");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, ";");
        TS_ASSERT_EQUALS (tks->terminal, semiColon) ;
        tks = tks->next ;
    }
    
	void test_equalsSignSymbol(){
	    Token *tks = s->scan ("=");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "=");
        TS_ASSERT_EQUALS (tks->terminal, equalsSign) ;
        tks = tks->next ;
    }
    
    /* Simple tests for mathematical operation regular expressions */
    void test_plusSignSymbol(){
	    Token *tks = s->scan ("+");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "+");
        TS_ASSERT_EQUALS (tks->terminal, plusSign) ;
        tks = tks->next ;
    }
    
    void test_starSymbol(){
	    Token *tks = s->scan ("*");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "*");
        TS_ASSERT_EQUALS (tks->terminal, star) ;
        tks = tks->next ;
    }
    
    void test_dashSymbol(){
	    Token *tks = s->scan ("-");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "-");
        TS_ASSERT_EQUALS (tks->terminal, dash) ;
        tks = tks->next ;
    }
    
    void test_forwardSlashSymbol(){
	    Token *tks = s->scan ("/");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "/");
        TS_ASSERT_EQUALS (tks->terminal, forwardSlash) ;
        tks = tks->next ;
    }
    
    void test_percentSymbol(){
	    Token *tks = s->scan ("%");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "%");
        TS_ASSERT_EQUALS (tks->terminal, percent) ;
        tks = tks->next;
    }
    
   void test_backSlashSymbol(){
	    Token *tks = s->scan ("\\");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "\\");
        TS_ASSERT_EQUALS (tks->terminal, backSlash) ;
        tks = tks->next ;
    }
    
    void test_arrowSymbol(){
	    Token *tks = s->scan ("->");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "->");
        TS_ASSERT_EQUALS (tks->terminal, arrow) ;
        tks = tks->next ;
    }
    
    void test_equalsEqualsSymbol(){
	    Token *tks = s->scan ("==");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "==");
        TS_ASSERT_EQUALS (tks->terminal, equalsEquals) ;
        tks = tks->next ;
    }
    
    void test_lessThanEqualsSymbol(){
	    Token *tks = s->scan ("<=");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "<=");
        TS_ASSERT_EQUALS (tks->terminal, lessThanEquals) ;
        tks = tks->next ;
    }
    
    void test_greaterThanEqualsSymbol(){
	    Token *tks = s->scan (">=");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, ">=");
        TS_ASSERT_EQUALS (tks->terminal, greaterThanEquals) ;
        tks = tks->next ;
    }
    
    void test_notEqualsSymbol(){
	    Token *tks = s->scan ("!=");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "!=");
        TS_ASSERT_EQUALS (tks->terminal, notEquals) ;
        tks = tks->next ;
    }
    
    void test_plusPlusSymbol(){
	    Token *tks = s->scan ("++");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "++");
        TS_ASSERT_EQUALS (tks->terminal, plusPlus) ;
        tks = tks->next ;
    }
    
    // dotDot and tupleOp
    void test_dotDotSymbol(){
	    Token *tks = s->scan ("..");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "..");
        TS_ASSERT_EQUALS (tks->terminal, dotDot) ;
        tks = tks->next ;
    }
    
    void test_tupleOp1digitsSymbol(){
	    Token *tks = s->scan ("#2");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "#2");
        TS_ASSERT_EQUALS (tks->terminal, tupleOp) ;
        tks = tks->next ;
    }    

    void test_tupleOp2digitsSymbol(){
	    Token *tks = s->scan ("#29");
        TS_ASSERT (tks != NULL);
        TS_ASSERT_EQUALS (tks->lexeme, "#29");
        TS_ASSERT_EQUALS (tks->terminal, tupleOp) ;
        tks = tks->next ;
    }    
    
    /* Below is one of my tests for these components.  It uses a
       helper function function called "tokenMaker_tests", which you
       have not been given.  You are expected to design your own
       components for "scan" and your own mechanisms for easily
       testing them.

        void xtest_TokenMaker_leftCurly ( ) {
            tokenMaker_tester ("{ ", "^\\{", leftCurly, "{" ) ;
        }

        Note that this test is here named "xtest_Token..." The leading
        "x" is so that cxxTest doesn't scan the line above and think
        it is an actual test that isn't commented out.  cxxTest is
        very simple and doesn't even process block comments.
    */


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

    /* A quick, but inaccurate, test for scanning files.  It only
       checks that no lexical errors occurred, not that the right
       tokens were returned. 
    */
    void scanFileNoLexicalErrors ( const char* filename ) {
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT (noLexicalErrors(tks));
    }


    /* This function checks that the terminal fields in the list of
       tokens matches a list of terminals.
    */
    bool sameTerminals (Token *tks, int numTerms, tokenType *ts) {
        Token *currentToken = tks ;
        int termIndex = 0 ;
        while (currentToken != NULL && termIndex < numTerms ) {
            if (currentToken->terminal != ts[termIndex]) {
		printf("\n%d", currentToken->terminal);    
        	printf("\n%d\n",termIndex);
                return false ;
            }
            else {
                ++ termIndex ;
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }

    void test_scan_func(){
	Token* tks = s->scan("  /*  */end of buff");
	TS_ASSERT( tks != NULL );

    }

    // The "endOfFile" token is always the last one in the list of tokens.
    void test_scan_empty ( ) {
        Token *tks = s->scan ("  ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }

    void test_scan_empty_comment ( ) {
        Token *tks = s->scan (" /* a comment */ ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }

    // When a lexical error occurs, the scanner creates a token with a 
    // single-character lexeme and lexicalError as the terminal.
    void test_scan_lexicalErrors ( ) {
        Token *tks = s->scan ("$&1  ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "$");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "&");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, intConst) ;
        TS_ASSERT_EQUALS (tks->lexeme, "1");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }


    // A test for scanning numbers and a variable.
    void test_scan_nums_vars ( ) {
        Token *tks = s->scan (" 123 x 12.34 ") ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { intConst, variableName, floatConst, endOfFile } ;
        TS_ASSERT ( sameTerminals ( tks, 4, ts ) ) ;
    }

    /* This test checks that the scanner returns a list of tokens with
       the correct terminal fields.  It doesn't check that the lexeme
       are correct.
     */
    void test_scan_bad_syntax_good_tokens ( ) {
        const char *filename = "../samples/bad_syntax_good_tokens.kix" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
            intConst, intConst, intConst, intConst, 

            stringConst, stringConst,

            leftSquare, floatConst, comma, floatConst, comma,
            floatConst, rightSquare,

            semiColon, comma, leftParen, leftSquare,
            rightParen, rightSquare ,

            equalsSign, plusSign, star, dash, forwardSlash, percent,
            rightAngle, leftAngle, colon, backSlash,

            colonColon, arrow, equalsEquals, lessThanEquals, 
            greaterThanEquals, notEquals, plusPlus, dotDot,

            variableName, variableName, variableName, variableName, 
            variableName, variableName, variableName,

            variableName, 
            letKwd, inKwd, endKwd, ifKwd, thenKwd, elseKwd, 
            printKwd, readKwd, writeKwd, 
            integerKwd, floatKwd, booleanKwd, stringKwd, 
            trueKwd, falseKwd, headKwd, tailKwd, nullKwd, 
            mapKwd, filterKwd, foldKwd,
            
            /* added tupleOp */
            // tupleOp, tupleOp, tupleOp, tupleOp, tupleOp,

            endOfFile
        } ;
        int count = 66;
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }
    
    /* This test checks that the scanner returns a list of tokens with
       the correct terminal fields.  It doesn't check that the lexeme
       are correct.
     */
    void test_scan_bad_syntax_good_tokens_tuples ( ) {
        const char *filename = "../samples/bad_syntax_good_tokens.kix" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
            intConst, intConst, intConst, intConst, 

            stringConst, stringConst,

            leftSquare, floatConst, comma, floatConst, comma,
            floatConst, rightSquare,

            semiColon, comma, leftParen, leftSquare,
            rightParen, rightSquare ,

            equalsSign, plusSign, star, dash, forwardSlash, percent,
            rightAngle, leftAngle, colon, backSlash,

            colonColon, arrow, equalsEquals, lessThanEquals, 
            greaterThanEquals, notEquals, plusPlus, dotDot,

            variableName, variableName, variableName, variableName, 
            variableName, variableName, variableName,

            variableName, 
            letKwd, inKwd, endKwd, ifKwd, thenKwd, elseKwd, 
            printKwd, readKwd, writeKwd, 
            integerKwd, floatKwd, booleanKwd, stringKwd, 
            trueKwd, falseKwd, headKwd, tailKwd, nullKwd, 
            mapKwd, filterKwd, foldKwd,
            
            /* added tupleOp */
            tupleOp, tupleOp, tupleOp, tupleOp, tupleOp,

            endOfFile
        } ;
        int count = 71;
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }


    void test_scan_simple_1 ( ) {
        scanFileNoLexicalErrors ("../samples/simple_1.kix") ;
    }
    
    void test_scan_simple_1_furthur( ) {
        const char *filename = "../samples/simple_1.kix" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
	        variableName, colonColon, leftParen, 
        	variableName, colonColon, leftSquare,
        	stringKwd, rightSquare, rightParen,
        	arrow, integerKwd, equalsSign,
		intConst, plusSign, intConst,
		semiColon,
        	
			
            endOfFile
        } ;
        int count = 16;
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }
    
    void test_scan_simple_2 ( ) {
        scanFileNoLexicalErrors ("../samples/simple_2.kix") ;
    }
    
    void test_scan_simple_2_furthur( ) {
        const char *filename = "../samples/simple_2.kix" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
	        variableName,colonColon,leftParen,variableName,//4
	        colonColon,leftSquare,stringKwd,rightSquare,//8
	        rightParen,arrow,integerKwd,equalsSign,//12
	        letKwd,variableName,colonColon,integerKwd,//16
		   equalsSign,intConst,
	        semiColon,variableName,colonColon,integerKwd,//20
		   equalsSign,intConst,
	        semiColon, inKwd,variableName,star,//24
	        variableName,endKwd,semiColon,//27
			
            endOfFile
        } ;
        int count = 31;
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }
    
    void test_scan_simple_3 ( ) {
        scanFileNoLexicalErrors ("../samples/simple_3.kix") ;
    }
    
    void test_scan_simple_3_furthur( ) {
        const char *filename = "../samples/simple_3.kix" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
        	variableName,colonColon,leftParen,variableName,//4
        	colonColon,integerKwd,comma,variableName,//8
        	colonColon,integerKwd,rightParen,arrow,//12
        	integerKwd,equalsSign,variableName,plusSign,//16
        	variableName,semiColon,//18
        
	        variableName,colonColon,leftParen,variableName,//4 22
	        colonColon,leftSquare,stringKwd,rightSquare,//8 26
	        rightParen,arrow,integerKwd,equalsSign,//12 30
	        letKwd,variableName,colonColon,integerKwd,
		   equalsSign,intConst,//16 34
	        semiColon,variableName,colonColon,integerKwd,
		   equalsSign,intConst,//20 38
	        semiColon, inKwd,variableName,leftParen,//24 42
	        variableName,comma,variableName,rightParen,//28 46
	        endKwd, semiColon,//48
			
            endOfFile
        } ;
        int count = 51;
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }
    
    void test_scan_squares ( ) {
        scanFileNoLexicalErrors ("../samples/squares.kix") ;
    }
    
    void test_scan_squares_furthur( ) {
        const char *filename = "../samples/squares.kix" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
	       	variableName,colonColon,leftParen,variableName,
	       	colonColon,integerKwd,rightParen,arrow,
	       	integerKwd,equalsSign,variableName,star,
	       	variableName,semiColon,
/*	       	
			variableName,colonColon,leftParen,variableName,
			colonColon,leftParen,variableName,arrow,variableName,
			comma,variableName,colonColon,leftSquare,
			variableName,rightSquare,rightParen,arrow,
			leftSquare,variableName,rightSquare,equalsSign,
			ifKwd,variableName,equalsEquals,leftSquare,
			rightSquare,thenKwd,leftSquare,rightSquare,
			elseKwd,variableName,leftParen,leftParen,
			headKwd,leftParen,variableName,rightParen,
			rightParen,colon,mapKwd,leftParen,variableName,
			tailKwd,leftParen,variableName,rightParen,
			rightParen,rightParen,semiColon,
*/
	       	variableName,colonColon,leftParen,variableName,
	       	colonColon,leftSquare,stringKwd,rightSquare,
	       	rightParen,arrow,integerKwd,equalsSign,
	       	letKwd,variableName,colonColon,leftSquare,
	       	integerKwd,rightSquare,equalsSign,leftSquare,
	       	intConst,dotDot,intConst,rightSquare,
	       	semiColon,variableName,colonColon,leftSquare,
	       	integerKwd,rightSquare,equalsSign,mapKwd,
	       	leftParen,variableName,comma,variableName,
	       	rightParen,semiColon,inKwd,printKwd,
	       	leftParen,variableName,rightParen,endKwd,
	       	semiColon,
			
            endOfFile
        } ;
        int count = 62;
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }
    
    void test_scan_evenSquares ( ) {
        scanFileNoLexicalErrors ("../samples/evenSquares.kix") ;
    }
    
    void test_scan_evenSquares_furthur( ) {
        const char *filename = "../samples/evenSquares.kix" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
	       	variableName,colonColon,leftParen,variableName,
	       	colonColon,	integerKwd,rightParen,arrow,
	       	integerKwd,equalsSign,variableName,star,
	       	variableName,semiColon,//14
	       	
	       	variableName, colonColon,leftParen,variableName,//18
	       	colonColon,integerKwd,rightParen,arrow,//22
	       	booleanKwd,equalsSign,variableName,forwardSlash,//26
	       	intConst,equalsEquals,intConst,semiColon, //30
	       	
	       	variableName,colonColon,leftParen,variableName,
	       	colonColon,leftSquare,stringKwd,rightSquare,
	       	rightParen,arrow,integerKwd,equalsSign,
	       	letKwd,variableName,colonColon,leftSquare,
	       	integerKwd,rightSquare,equalsSign,leftSquare,
	       	intConst,dotDot,intConst,rightSquare,
	       	semiColon,variableName,colonColon,leftSquare,
	       	integerKwd,rightSquare,equalsSign,mapKwd,
	       	leftParen,variableName,comma,variableName,
	       	rightParen,semiColon,variableName,colonColon,
	       	leftSquare,integerKwd,rightSquare,equalsSign,
	       	filterKwd,leftParen,variableName,comma,
	       	variableName,rightParen,semiColon,
	       	inKwd,printKwd,leftParen,variableName,
	       	rightParen,endKwd,semiColon,//59
			
            endOfFile
        } ;
        int count = 59;
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }
    
    
    void test_scan_matVecMulLiterals ( ) {
        scanFileNoLexicalErrors ("../samples/matVecMulLiterals.kix") ;
    }

    void test_scan_matVecMulLiterals_furthur( ) {
        const char *filename = "../samples/matVecMulLiterals.kix" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
			variableName, colonColon, leftParen, variableName, // 4
			colonColon, leftSquare, integerKwd, rightSquare, // 8
			rightParen, arrow, integerKwd, equalsSign, // 12
			foldKwd, leftParen, backSlash, variableName, // 16
			colonColon, integerKwd, comma, variableName, // 20
			colonColon, integerKwd,arrow, variableName, // 24
			plusSign,variableName,comma,intConst, // 28
			comma, variableName, rightParen, semiColon, // 32

			variableName, colonColon, leftParen, variableName, // 4 36 
			colonColon, leftSquare,integerKwd, rightSquare, // 8 40
			comma, variableName,colonColon,leftSquare, // 12 44
			integerKwd,rightSquare,rightParen,arrow, //16 48
			integerKwd,equalsSign,variableName,leftParen, //20 52
			mapKwd,leftParen,backSlash,variableName, //24 56
			colonColon,leftParen,integerKwd,comma, // 28 60
			integerKwd,rightParen,arrow,tupleOp, // 32 64
			leftParen,variableName,rightParen, star, // 36
			tupleOp,leftParen,variableName,rightParen, // 40
			comma,zipKwd,leftParen,variableName, //44 
			comma,variableName,rightParen,rightParen, //48 
			rightParen,semiColon, // 50 82

			variableName, colonColon, leftParen, variableName, // 4 
			colonColon, leftSquare,leftSquare,integerKwd, // 8 
			rightSquare,rightSquare,comma,variableName, // 12 
			colonColon,leftSquare,integerKwd,rightSquare, // 16 
			rightParen,arrow,leftSquare,integerKwd, // 20 
			rightSquare,equalsSign,mapKwd,leftParen, // 24 
			backSlash,variableName,colonColon,leftSquare, // 28 
			integerKwd,rightSquare,arrow,variableName, //32 
			leftParen,variableName,comma,variableName, // 36
			rightParen,comma,variableName,rightParen, // 40
			semiColon, // 41 123

			variableName, colonColon,leftParen,variableName, // 4 127
			colonColon,leftSquare,stringKwd,rightSquare, // 8
			rightParen,arrow,integerKwd,equalsSign, // 12
			letKwd,variableName,colonColon,leftSquare, // 16
			leftSquare,integerKwd,rightSquare,rightSquare, // 20
			equalsSign, leftSquare,leftSquare,intConst, // 24 147
			comma,intConst,rightSquare,comma, // 28
			leftSquare,intConst,comma,intConst, // 32
			rightSquare,rightSquare,semiColon,variableName, // 36
			colonColon,leftSquare,integerKwd,rightSquare, // 40
			equalsSign,leftSquare,intConst,comma, // 44 167
			intConst,rightSquare,semiColon,inKwd, // 48
			printKwd,leftParen,variableName,leftParen, // 52
			variableName,comma,variableName,rightParen, // 56
			rightParen, endKwd, // 58
		       
			
            endOfFile
        } ;
        int count = 181;
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }

    void test_scan_matVecMul ( ) {
        scanFileNoLexicalErrors ("../samples/matVecMul.kix") ;
    }
    
    void test_scan_matVecMul_furthur( ) {
        const char *filename = "../samples/matVecMul.kix" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
			variableName, colonColon, leftParen, variableName, // 4
			colonColon, leftSquare, integerKwd, rightSquare, // 8
			rightParen, arrow, integerKwd, equalsSign, // 12
			foldKwd, leftParen, backSlash, variableName, // 16
			colonColon, integerKwd, comma, variableName, // 20
			colonColon, integerKwd,arrow, variableName, // 24
			plusSign,variableName,comma,intConst, // 28
			comma, variableName, rightParen, semiColon, // 32

			variableName, colonColon, leftParen, variableName, // 4 36 
			colonColon, leftSquare,integerKwd, rightSquare, // 8 40
			comma, variableName,colonColon,leftSquare, // 12 44
			integerKwd,rightSquare,rightParen,arrow, //16 48
			integerKwd,equalsSign,variableName,leftParen, //20 52
			mapKwd,leftParen,backSlash,variableName, //24 56
			colonColon,leftParen,integerKwd,comma, // 28 60
			integerKwd,rightParen,arrow,tupleOp, // 32 64
			leftParen,variableName,rightParen, star, // 36
			tupleOp,leftParen,variableName,rightParen, // 40
			comma,zipKwd,leftParen,variableName, //44 
			comma,variableName,rightParen,rightParen, //48 
			rightParen,semiColon, // 50 82

			variableName, colonColon, leftParen, variableName, // 4 
			colonColon, leftSquare,leftSquare,integerKwd, // 8 
			rightSquare,rightSquare,comma,variableName, // 12 
			colonColon,leftSquare,integerKwd,rightSquare, // 16 
			rightParen,arrow,leftSquare,integerKwd, // 20 
			rightSquare,equalsSign,mapKwd,leftParen, // 24 
			backSlash,variableName,colonColon,leftSquare, // 28 
			integerKwd,rightSquare,arrow,variableName, //32 
			leftParen,variableName,comma,variableName, // 36
			rightParen,comma,variableName,rightParen, // 40
			semiColon, // 41 123

			variableName, colonColon,leftParen,variableName, // 4
			colonColon,leftSquare,stringKwd,rightSquare, // 8
			rightParen,arrow,integerKwd,equalsSign, // 12
			letKwd,variableName,colonColon,leftSquare, // 16
			leftSquare,integerKwd,rightSquare,rightSquare, // 20
			equalsSign,readKwd,leftAngle,leftSquare, // 24
			leftSquare,integerKwd,rightSquare,rightSquare,//28
			rightAngle,leftParen,stringConst,rightParen,//32
			semiColon,variableName,colonColon,leftSquare,//36
			integerKwd,rightSquare,equalsSign,readKwd,//40
			leftAngle,leftSquare,integerKwd,rightSquare,//44
			rightAngle,leftParen,stringConst,rightParen,//48
			semiColon,inKwd,printKwd,leftParen, // 52
			variableName,leftParen,variableName,comma, // 56
			variableName,rightParen,rightParen,endKwd, // 60
			semiColon,//61 183
			
            endOfFile
        } ;
        int count = 184;
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }

} ;





