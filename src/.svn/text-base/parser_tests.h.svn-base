#include <cxxtest/TestSuite.h>

#include "readInput.h"
#include "scanner.h"
#include "ExtToken.h"
#include "Parser.h"
#include "ParseResult.h"

using namespace std ;

class ParserTestSuite : public CxxTest::TestSuite 
{
public:
    Scanner *s ;
    Parser *p ;
    void test_setup_code ( ) {
        s = new Scanner() ;
        p = new Parser() ;
    }

    /* This function checks that the terminal fields in the list of
       tokens matches a list of terminals.
    */
    bool sameTerminalsExt (ExtToken *tks, int numTerms, tokenType *ts) {
        ExtToken *currentToken = tks ;
        int termIndex = 0 ;
        while (currentToken != NULL && termIndex < numTerms ) {
            if (currentToken->terminal != ts[termIndex]) {
                return false ;
            }
            else {
                ++ termIndex ;
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }

    void test_scan_nums_vars ( ) {
        Token *tks = s->scan ("a :: Integer = 4 ; ") ;
        TS_ASSERT (tks != NULL) ;
        ExtToken *etks = extendTokenList (p, tks ) ;
        TS_ASSERT (etks != NULL) ;
        tokenType ts[] = { variableName, colonColon, integerKwd, equalsSign,
                            intConst, semiColon, endOfFile } ;
        TS_ASSERT ( sameTerminalsExt ( etks, 7, ts ) ) ;
    }


    void test_parse_dcl ( ) {
        ParseResult pr = p->parse ("a :: Integer = 4 + 1 * 8 - 2 % 4 ; ") ;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }

    void test_parse_BExpr_list ( ) {
        ParseResult pr = p->parse ("a :: Integer = [ <Integer> 4, 5+5, 6] ;") ;
        cout << "\n" << pr.ast->unparse() << endl;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }

    void test_parse_Expr_list ( ) {
        ParseResult pr = p->parse ("a :: Integer = (4, 5+5, 6) ;") ;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }

    void test_parse_expr_list ( ) {
        ParseResult pr = p->parse ("a :: Integer = (4, false, true, 6%5) ;") ;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }

    void test_parse_expr_list2 ( ) {
        ParseResult pr = p->parse ("a :: Integer = (4, 5, 6, 6%5) ;") ;
        //cout << "\n" << pr.ast->unparse() << "\n";
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }

    void test_parse_dcl_fail ( ) {
        ParseResult pr = p->parse ("a :: ; Integer = 4 ;") ;
        TSM_ASSERT ( pr.errors, ! pr.ok ) ;
    }

    void test_parse_dcls ( ) {
        ParseResult pr = p->parse ("a :: Integer = 4 ; b :: Integer = 5 ;") ;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }

    void test_parse_dcls_fail ( ) {
        ParseResult pr = p->parse ("arrow :: Integer = a+3 * 1 /4 -2 *5 ; ; b :: Integer = 5 ;") ;
        TSM_ASSERT ( pr.errors,  ! pr.ok ) ;
    }
    
    void test_parse_type_expr_list ( ) {
        ParseResult pr = p->parse ("a :: (Integer,Float,Boolean,String) = 3 ;") ;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    void test_parse_functions ( ) {
        ParseResult pr = p->parse ("a :: Integer = if print ( x%y ) then map( x , y ) else filter(x,y) ;") ;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    void test_parse_if ( ) {
        ParseResult pr = p->parse ("a :: Integer = if 5 == 5 then 100 else 3 ;") ;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }

    void test_parse_relative_exprs1 ( ) {
        ParseResult pr = p->parse ("a :: Integer = if 5 == 5 then (6<10) else (5 > 6) ;") ;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    void test_parse_relative_exprs2 ( ) {
        ParseResult pr = p->parse ("a :: Integer = if 5 != 5 then 6>=6 else (5<=6) ;") ;
        //cout << "\n" << pr.ast->unparse() << "\n";
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    
    void test_parse_other_functions ( ) {
        ParseResult pr = p->parse ("a :: Integer = if zip( 5+6,9) then write(3, x) else head(1) ;") ;
        //cout << "\n" << pr.ast->unparse() << "\n";
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    
    void test_parse_other_functions2 ( ) {
        ParseResult pr = p->parse ("a :: Integer = if tail( 5+6) then null( x) else head(1) ;") ;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    
    void test_parse_tuple ( ) {
        ParseResult pr = p->parse ("a :: Integer = #3 ( 1,2,3,4,5 ) ;") ;
        //cout << "\n" << pr.ast->unparse() << "\n";
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    
	void test_parse_ExprListtest ( ) {
        ParseResult pr = p->parse ("arrow :: ( m :: Integer, v :: Integer, b :: Boolean)->Float = (5+5, 6+3, false) ;") ;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    
    void test_parse_BracketsforParens ( ) {
        ParseResult pr = p->parse ("arrow :: ( m :: [Integer], v :: [Integer], b :: [Boolean]) -> Integer = (5+5, 6+3, false) ;") ;
        //cout << "\n" << pr.ast->unparse() << "\n";
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    
    void test_parse_LetKwd_simple ( ) {
        ParseResult pr = p->parse ("main :: Integer = let x :: Integer = 4;  in x*3 end ;") ;
        DeclListNode* head = (DeclListNode*) pr.ast;
		string res = head->unparse();
		//cout << "\n" << res << "\n";
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }


    void test_parse_typeBinding_simple ( ) {
        ParseResult pr = p->parse ("main :: ( args::[String] ) -> Integer = 1 + 2 ;") ;
        /*DeclListNode* head = (DeclListNode*) pr.ast;
		string res = head->unparse();
		cout << "\n" << res << "\n";*/
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
   
    void test_parse_optionalExprList_simple ( ) {
        ParseResult pr = p->parse ("matMul :: ( m::[Integer], v::[Integer] ) -> [Integer] = (3, 5);") ;
        /*DeclListNode* head = (DeclListNode*) pr.ast;
		string res = head->unparse();
		cout << "\n" << res << "\n";*/
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    
    void test_parse_LetKwd ( ) {
        ParseResult pr = p->parse ("main :: ( args::[String] ) -> Boolean = let x :: Integer = 4; in x*3 end ; ") ;
        //cout << (pr.ast)->unparse() << endl;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    
    void test_parse_string ( ) {
        ParseResult pr = p->parse ("m :: (ms::Integer)->String = \"kdjfa;\";") ;
        //cout << (pr.ast)->unparse() << endl;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    
    void test_parse_noparameterfunction ( ) {
        ParseResult pr = p->parse ("m :: Integer = adk();") ;
        //cout << (pr.ast)->unparse() << endl;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
        
    void test_parse_reading_simple ( ) {
    	//cout << "m :: [[Integer]] = read<[[Integer]]> ( \"file.dat\" ) ;" << endl;
        ParseResult pr = p->parse ("m :: [[Integer]] = read<[[Integer]]> ( \"file.dat\" ) ;") ;
        //cout << (pr.ast)->unparse() << endl;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    
    void test_parse_fold_simple ( ) {
        ParseResult pr = p->parse ("    vecSum :: ( vs::[Integer] ) -> Integer = fold ( 5, 0, 7 ) ;") ;
        //cout << (pr.ast)->unparse() << endl;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }
    
    void test_parse_lambda_simple ( ) {
        ParseResult pr = p->parse ("    vecSum :: ( vs::[Integer] ) -> Integer = \\r :: Integer -> hola( 3, r);") ;
        //cout << (pr.ast)->unparse() << endl;
        TSM_ASSERT ( pr.errors, pr.ok ) ;
    }

    
	/*	Parses files no errors.
	*
	*/
    void parseFileNoErrors ( const char* filename ) {
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        ParseResult pr = p->parse ( text ) ;
        string msg (filename) ;
        msg += "\n" + pr.errors + "\n" + pr.pp ;
        TSM_ASSERT ( msg , pr.ok );
    }

	
    void test_parse_simple_1 ( ) {
        parseFileNoErrors ("../samples/simple_1.kix") ;
    }
    void test_parse_simple_2 ( ) {
        parseFileNoErrors ("../samples/simple_2.kix") ;
    }
    void test_parse_simple_3 ( ) {
        parseFileNoErrors ("../samples/simple_3.kix") ;
    }
    void test_parse_squares ( ) {
        parseFileNoErrors ("../samples/squares.kix") ;
    }
    void test_parse_evenSquares ( ) {
        parseFileNoErrors ("../samples/evenSquares.kix") ;
    }
    void test_parse_matVecMul ( ) {
        parseFileNoErrors ("../samples/matVecMul.kix") ;
    }
    void xtest_parse_matVecMulLiterals ( ) {
        parseFileNoErrors ("../samples/matVecMulLiterals.kix") ;
    }
    


} ;
