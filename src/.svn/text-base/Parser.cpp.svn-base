/* A recursive descent parser with operator precedence.

   Author: Eric Van Wyk

   This algorithms is based on the work of Douglas Crockford in "Top
   Down Operator Precedence", a chapter in the book "Beautiful Code".
   Mr. Crockford describes in his chapter how his work comes from that
   of Based on algorithms described Vaughan Pratt in "Top Down Operator
   Precedence", presented at the ACM Symposium on Principles of
   Programming Languages.

   Douglas Crockford's chapter is available at 
    http://javascript.crockford.com/tdop/tdop.html

   Vaughan Pratt's paper is available at 
    http://portal.acm.org/citation.cfm?id=512931

   These are both quite interesting works and worth reading if you
   find the problem of parsing to be an interesting one.

   Last modified: March 5, 2012.
*/

//#include "Parser.h"
#include "scanner.h"
#include "ExtToken.h"
#include <assert.h>
#include <stdlib.h>

using namespace std ;

Parser::Parser ( ) { } 

ParseResult Parser::parse (const char *text) {
    assert (text != NULL) ;

    ParseResult pr ;
    try {
        Scanner *s = new Scanner() ;
        tokens = extendTokenList ( this, s->scan (text) ) ;

        assert (tokens != NULL) ;

        currToken = tokens ;

        pr = parseProgram( ) ;
        pr.ok = true ;
        pr.errors = "" ;
    }
    catch (string errMsg) {
        pr.ok = false ;
        pr.errors = errMsg ;
    }
    return pr ;
}

/* 
 * parse methods for non-terminal symbols
 * --------------------------------------
 */

// Program
ParseResult Parser::parseProgram () {
    ParseResult pr ;
    // Program ::= DeclList
    pr = parseDeclList() ;
	if( !pr.ok ){ 
		fprintf( stderr, "Error parsing file.\n" );
		return pr;
	}
    match(endOfFile) ;
    return pr ;
}

/******************************************************************************
 *	-Decl and DeclList
 *
 *****************************************************************************/
// DeclList
ParseResult Parser::parseDeclList () {
	ParseResult pr ;
	ParseResult tpr;
	Node* tmp = new DeclListNode();
	pr.ast = tmp;

	// DeclList ::= Decl
	if( (tpr = parseDecl()).ok ){
		DeclNode* l = dynamic_cast<DeclNode*>(tpr.ast);
		if( l ){
			tmp->left = l;
		}
	}
	
	// TODO ADD ERROR CHECKS

	// DeclList ::= Decl DeclList
	if ( nextIs(variableName) ) {
		if( (tpr = parseDeclList()).ok ){
			DeclListNode* r = dynamic_cast<DeclListNode*>(tpr.ast);
			if( r ){
				tmp->right = r;
			}
		}
    }
    
    return pr ;
}

// Decl
ParseResult Parser::parseDecl () {
	ParseResult pr ;
	ParseResult tpr;
	Node* tmp = new DeclNode();

	// Decl ::= variableName '::' TypeExpr '=' Expr ';'
	// Decl ::= parseVariableName parseDeclRNode
	tpr = parseVarName();
	VarNameNode* vn = dynamic_cast<VarNameNode*>(tpr.ast);
	if( vn ){
		
		tmp->left = vn;
	} else {
		throw ((string) "Decl could not be parsed correctly for the the variable name!");
	}
	
	match(colonColon);
	
	// TypeExpr '=' Expr ';'
	DeclRNode* DeclR = new DeclRNode();
	if( (tpr = parseTypeExpr()).ok ){
		
		// adds the type expression
		TypeExprNode* d = dynamic_cast<TypeExprNode*>(tpr.ast) ;
		if( d ){
			DeclR->left = d;
		}

	} else {
		throw ((string) "Decl could not be parsed correctly for the type and expr!");
	}

	match(equalsSign);

	if( (tpr = parseExpr(0)).ok ){
		ExprNode *edecl = dynamic_cast<ExprNode*>(tpr.ast) ;
		if( edecl ){
			DeclR->right = edecl; 
		}
	} else {
		//Error
	}

	match(semiColon) ;

	tmp->right = DeclR;
	pr.ast = tmp;
	return pr ;
}

/******************************************************************************
 *	-TypeExpr and TypeExprList
 *
 *****************************************************************************/
 
// TypeExpr
ParseResult Parser::parseTypeExpr () {
    ParseResult pr ;
	ParseResult tpr;
	Node* tmp;

    if ( nextIs(integerKwd) ) { 
        // TypeExpr ::= 'Integer'
		tmp = new TypeExprNode();
		((TypeExprNode*)tmp)->type = Integer;
		pr.ast = tmp;
		nextToken();
    }

    else if ( nextIs(floatKwd) ) {
        // TypeExpr ::= 'Float'
		tmp = new TypeExprNode();
		((TypeExprNode*)tmp)->type = Float;
		pr.ast = tmp;
		nextToken();			
    }

    else if ( nextIs(stringKwd) ) {
        // TypeExpr ::= 'String'
		tmp = new TypeExprNode();
		((TypeExprNode*)tmp)->type = String;
		pr.ast = tmp;				
		nextToken();			
    }

    else if ( nextIs(booleanKwd) ) {
        // TypeExpr ::= 'Boolean'
		tmp = new TypeExprNode();
		((TypeExprNode*)tmp)->type = Boolean;
		pr.ast = tmp;				
		nextToken();			
    }

    else if ( attemptMatch(leftSquare) ) {
		// TypeExpr ::= '[' TypeExpr ']'
		TypeExprNode* teb = new TypeExprNode();
		teb->type = Bexpr;
		tpr = parseTypeExpr() ;
		match(rightSquare) ;
		pr.ast = teb;
		teb = dynamic_cast<TypeExprNode*>(tpr.ast);
		if( teb ) (pr.ast)->left = tpr.ast;
    }

    else if ( attemptMatch(leftParen) ) {
    	
        if ( nextIs(variableName) ) {
            // TypeExpr ::= '(' TypeBindingList ')' '->' TypeExpr
			TypeExprNode* ten = new TypeExprNode();
			ten->type = Aexpr;

            if ( (tpr = parseTypeBindingList()).ok ){
            	TypeBindingListNode* bind = dynamic_cast<TypeBindingListNode*>(tpr.ast);
            	if (bind) ten->left = tpr.ast;
            }
            else {
            	return pr;
            }
            match(rightParen) ;
            match(arrow) ;
            
			tpr = parseTypeExpr();
			if ( tpr.ok ){
				TypeExprNode* tel = dynamic_cast<TypeExprNode*>(tpr.ast);
				if( tel && tpr.ok ) ten->right = tpr.ast;
			}
			else{
				return pr;
			}
			
			pr.ast = ten;
			
        } else {
            // TypeExpr ::= '(' TypeExprList ')'
			TypeExprNode* te = new TypeExprNode();
			te->type = TElist;
			tpr = parseTypeExprList();
			TypeExprListNode* tel = dynamic_cast<TypeExprListNode*>(tpr.ast);
			if( tel && tpr.ok ) te->left = tpr.ast;
			match(rightParen) ;
			pr.ast = te;
        }
        
        
        
    } // else if attemptMatch(leftParen
    else {
        throw ( makeErrorMsg ( currToken->terminal ) ) ;
    }
	
	//cout << "\n" << pr.ast->unparse() << "\n" ;
    return pr ;
}

// TypeExprList
ParseResult Parser::parseTypeExprList () {
	ParseResult pr ;
	ParseResult tpr;
	Node* te = new TypeExprListNode();

	// TypeExprList ::= TypeExpr
 	if( (tpr = parseTypeExpr()).ok ){
		te->left = tpr.ast;
	} else {
		pr.ok = false;
	}

	// Check for more entries and add if necessary
	if ( attemptMatch(comma) ) {
        // TypeExprList ::= TypeExpr ',' TypeExprList
		if( (tpr = parseTypeExprList()).ok ){
			te->right = tpr.ast;
		} else {
			pr.ok = false;
		}
	}

	pr.ast = te;
	return pr;
}

/******************************************************************************
 *	-TypeBindingList and TypeBinding
 *
 *****************************************************************************/
 
// TypeBindingList
ParseResult Parser::parseTypeBindingList () {
    ParseResult pr ;
    ParseResult tpr;
    Node *tmp = new TypeBindingListNode();
    // TypeBindingList ::= TypeBinding
    
    
	if ( (tpr = parseTypeBinding ()).ok ){
		tmp->left = tpr.ast;
	} // end if
    
    if ( attemptMatch(comma) ) {
        // TypeBindingList ::= TypeBinding ',' TypeBindingList
        if ( (tpr = parseTypeBindingList ()).ok ){
			tmp->right = tpr.ast;
		} // end if
    }
    
    pr.ast = tmp;
    return pr ;
}

// TypeBinding
ParseResult Parser::parseTypeBinding () {
    ParseResult pr ;
    ParseResult tpr;
    TypeBindingNode* tmp = new TypeBindingNode();
    
    // TypeBinding ::= variableName '::' TypeExpr
	tpr = parseVarName();
	VarNameNode* vn = dynamic_cast<VarNameNode*>(tpr.ast);
	if( vn ){
		tmp->left = vn;
	} else {
		throw ((string) "Decl could not be parsed correctly for the the variable name!");
	}    

    // '::'
    match(colonColon) ;
    
    
    // TypeExpr;'
	if( (tpr = parseTypeExpr()).ok ){
		
		// addes the type expression
		TypeExprNode* d = dynamic_cast<TypeExprNode*>(tpr.ast) ;
		if( d ){
			tmp->right = d;
		}
		
	} else {
		throw ((string) "Decl could not be parsed correctly for the type and expr!");
	}
	pr.ast = tmp;
    
    return pr ;
}

/******************************************************************************
 *	-Expression functions
 *
 *****************************************************************************/

// OptionalExprList
ParseResult Parser::parseOptionalExprList () {
    ParseResult pr ;
    ParseResult tpr;
    Node* tmp = new OptionalExprListNode();
    if ( nextIs(rightSquare) || nextIs(rightParen) ) {
        // OptionalExprList ::= <<empty>>
    } else {
        // OptionalExprList ::= ExprList
        if ( (tpr = parseExprList()).ok ){
        	ExprListNode* l = dynamic_cast<ExprListNode*>(tpr.ast);
        	if (l)
        		tmp->left = l;
		}
        else {
        	return pr;
        }
    }
    
    pr.ast = tmp;
    return pr ;
}

// ExprList
ParseResult Parser::parseExprList () {
    ParseResult pr ;
    ParseResult tpr;
    ExprListNode* tmp = new ExprListNode();
    
    // ExprList ::= Expr
	if ( (tpr = parseExpr(0)).ok){
		ExprNode* l = dynamic_cast<ExprNode*>(tpr.ast);
		if (l){ 
			tmp->left = tpr.ast;
		} else {
			pr.ok = false;
		}
	}

	if ( nextIs(comma) ) {
		match(comma);
        // ExprList ::= Expr ',' ExprList
		if ( (tpr = parseExprList()).ok ){
			ExprListNode* r = dynamic_cast<ExprListNode*>(tpr.ast);
			if (r){
				tmp->right = tpr.ast;
			} else {
				pr.ok = false;
			}
		}
	}
	
	pr.ast = tmp;
	
	return pr ;
}


ParseResult Parser::parseExpr (int rbp) {
    /* Examine current token, without consuming it, to call its
       associated parse methods.  The ExtToken objects have 'nud' and
       'led' methods that are dispatchers that call the appropriate
       parse methods.*/
	ParseResult left = currToken->nud() ;
	
	while (rbp < currToken->lbp() ) {
		left = currToken->led(left) ;
	}

	return left ;
}


/*
 * parse methods for productions
 * -----------------------------
 */

// variableName (main)
ParseResult Parser::parseVarName ( ) {
    ParseResult pr ;
    
    if (nextIs(variableName)){
		VarNameNode* tmp = new VarNameNode();
    		tmp->lexeme = currToken->lexeme;
 	   	pr.ast = tmp;
		nextToken();
    }
    else {
		pr.ok = false;
    }
    return pr ;
}

// Expr ::= variableName
ParseResult Parser::parseVariableName ( ) {
    ParseResult pr ;
    
    if (nextIs(variableName)){
		KwdExprNode* tmp = new KwdExprNode();
    		tmp->type = VariableName;
    		tmp->lexeme = currToken->lexeme;
 	   	pr.ast = tmp;
		nextToken();
    }
    else {
    	pr.ok = false;
    }
    return pr ;
}

// Expr ::= intConst
ParseResult Parser::parseIntConst ( ) {
	ParseResult pr ;

	if (nextIs(intConst)){
		KwdExprNode* tmp = new KwdExprNode();
		tmp->type = IntConst;
		tmp->lexeme = currToken->lexeme;
		pr.ast = tmp;
		nextToken();
	} else {
		pr.ok = false;
	}

	return pr ;
}

// Expr ::= floatConst
ParseResult Parser::parseFloatConst ( ) {
    ParseResult pr ;
    
    if (nextIs(floatConst)){
		KwdExprNode* tmp = new KwdExprNode();
    	tmp->type = FloatConst;
    	tmp->lexeme = currToken->lexeme;
    	pr.ast = tmp;
    }
    else {
    	pr.ok = false;
    }
    return pr ;
}

// Expr ::= stringConst
ParseResult Parser::parseStringConst ( ) {
    ParseResult pr ;
    
    /*	Is there a string const? */
    if (nextIs(stringConst)){
		KwdExprNode* tmp = new KwdExprNode();
    	tmp->type = StringConst;
    	tmp->lexeme = currToken->lexeme;
    	pr.ast = tmp;
    }
    else {
    	pr.ok = false;
    }
    
    // update and move to next token
    match(stringConst);
    return pr ;
}

// Expr ::= trueKwd
ParseResult Parser::parseTrueKwd ( ) {
    ParseResult pr ;
    
    if (nextIs(trueKwd)){
		KwdExprNode* tmp = new KwdExprNode();
    	tmp->type = TrueKwd;
    	tmp->lexeme = currToken->lexeme;
    	pr.ast = tmp;
		nextToken();
    }
    else {
    	pr.ok = false;
    }
    return pr ;
}

// Expr ::= falseKwd
ParseResult Parser::parseFalseKwd ( ) {
    ParseResult pr ;
    
    if (nextIs(falseKwd)){
		KwdExprNode* tmp = new KwdExprNode();
    	tmp->type = FalseKwd;
    	tmp->lexeme = currToken->lexeme;
    	pr.ast = tmp;
		nextToken();
    }
    else {
    	pr.ok = false;
    }
    return pr ;
}

// Expr ::= '(' Expr ')'
// Expr ::= '(' Expr ',' ExprList ')'
ParseResult Parser::parseNestedOrTupleExpr ( ) {
	ParseResult pr;
	ParseResult tpr;
	ExprListNode* tel = new ExprListNode();

	match ( leftParen ) ;
	
	if( (tpr = parseExpr(0)).ok ){
		ExprNode* e = dynamic_cast<ExprNode*>(tpr.ast);
		if( e ){
			 tel->left = tpr.ast;
		} else { pr.ok = false; }
	} else {
		pr.ok = false;
		return pr;
	}

	if ( attemptMatch(comma) ) {
		tpr = parseExprList();
		ExprListNode* tmp = dynamic_cast<ExprListNode*>(tpr.ast);
		if( tmp ) tel->right = tmp;
	}

	match(rightParen);
	
	pr.ast = tel;
	
	return pr;
}

// Expr ::= '[' ExprList ']'
ParseResult Parser::parseBraketListExpr ( ) {
	ParseResult pr ;
	ParseResult tpr ;

	BraceExprNode* b = new BraceExprNode();

	match ( leftSquare ) ;
	
	if (nextIs ( leftAngle ) ){
		b->type = 1;
		match (leftAngle);
		
		tpr = parseTypeExpr();
		TypeExprNode* te = dynamic_cast<TypeExprNode*>(tpr.ast);
		if ( te ) {b->left = te;}
		else { pr.ok = false; }
		
		match (rightAngle);
	
		tpr = parseOptionalExprList();
		OptionalExprListNode* oe = dynamic_cast<OptionalExprListNode*>(tpr.ast);	
		if( oe) { b->right = oe;}
		else { pr.ok = false; }
		
	}
	else {
		b->type = 2;
		tpr = parseExpr(0);
		ExprNode* re1 = dynamic_cast<ExprNode*>(tpr.ast);
		
		if ( re1 ) { b->left = re1; }
		else {pr.ok = false;}
		
		match (dotDot);
		
		tpr = parseExpr(0) ; 
		ExprNode* re2 = dynamic_cast<ExprNode*>(tpr.ast);
		
		if (re2 && b->type == 2) { b->right = re2; }
		else { pr.ok = false; }
	}

	match(rightSquare) ;
	
	pr.ast = b;

	return pr ;
}

// Expr ::= variableName '(' Expr ')'
ParseResult Parser::parseFunctionCall ( ParseResult left ) {
	ParseResult pr;
	ParseResult tpr;
	std::string lex;

	lex = prevToken->lexeme;
	match(leftParen);
	
	LexFuncNode* f = new LexFuncNode();
	f->lexeme = lex;
	tpr = parseOptionalExprList();
	
	OptionalExprListNode* oe = dynamic_cast<OptionalExprListNode*>(tpr.ast);

	if( tpr.ok && oe ){
		f->left = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(rightParen);
	pr.ast = f;

	return pr;
}


// Expr ::= Expr '+' Expr
ParseResult Parser::parseAddition ( ParseResult left ) {
	// parser has already matched left expression 
	ParseResult pr ;
	ParseResult tpr;
	match ( plusSign ) ;

	Node* op = new OpExprNode();
	((OpExprNode*)op)->type = Plus;
	op->left = left.ast;
	tpr = parseExpr( prevToken->lbp() );
	if( tpr.ok ) op->right = tpr.ast;
	pr.ast = op;  

	return pr ;
}
// Expr ::= Expr '*' Expr
ParseResult Parser::parseMultiplication ( ParseResult left ) {
	// parser has already matched left expression 
	ParseResult pr ;
	ParseResult tpr;
	match ( star ) ;

	Node* op = new OpExprNode();
	((OpExprNode*)op)->type = Star;
	op->left = left.ast;
	tpr = parseExpr( prevToken->lbp() );
	if( tpr.ok ) op->right = tpr.ast;
	pr.ast = op;  

	return pr ;
}
// Expr ::= Expr '-' Expr
ParseResult Parser::parseSubtraction ( ParseResult left ) {
	// parser has already matched left expression 
	ParseResult pr ;
	ParseResult tpr;
	match ( dash ) ;

	Node* op = new OpExprNode();
	((OpExprNode*)op)->type = Minus;
	op->left = left.ast;
	tpr = parseExpr( prevToken->lbp() );
	if( tpr.ok ) op->right = tpr.ast;
	pr.ast = op;  

	return pr ;
}
// Expr ::= Expr '/' Expr
ParseResult Parser::parseDivision ( ParseResult left ) {
	// parser has already matched left expression 
	ParseResult pr ;
	ParseResult tpr;
	match ( forwardSlash ) ;

	Node* op = new OpExprNode();
	((OpExprNode*)op)->type = ForwardSlash;
	op->left = left.ast;
	tpr = parseExpr( prevToken->lbp() );
	if( tpr.ok ) op->right = tpr.ast;
	pr.ast = op;  

	return pr ;
}
// Expr ::= Expr '%' Expr
ParseResult Parser::parseModulus ( ParseResult left ) {
	// parser has already matched left expression 
	ParseResult pr ;
	ParseResult tpr;
	match ( percent ) ;

	Node* op = new OpExprNode();
	((OpExprNode*)op)->type = Percent;
	op->left = left.ast;
	tpr = parseExpr( prevToken->lbp() );
	if( tpr.ok ) op->right = tpr.ast;
	pr.ast = op;  

	return pr ;
}

// Expr ::= Expr '==' Expr
// Expr ::= Expr '<' Expr
// Expr ::= Expr '>' Expr
// Expr ::= Expr '>=' Expr
// Expr ::= Expr '<=' Expr
// Expr ::= Expr '!=' Expr
/* Notice that for relational operators we use just one parse
   function.  This shows another possible means for implementing
   expressions, as opposed to the method used for arithmetic
   expressions in which each operation has its own parse method.  It
   will depend on what we do in iteration 3 in building an abstract
   syntax tree to decide which method is better.
 */
ParseResult Parser::parseRelationalExpr ( ParseResult left ) {
	// parser has already matched left expression 
	ParseResult pr;
	ParseResult tpr;
	terminal_t re;
	Node* rel = new RelExprNode();
	re = currToken->terminal;

	switch( re ){
		case leftAngle: ((RelExprNode*)rel)->type = LessThan; break;
		case rightAngle: ((RelExprNode*)rel)->type = GreaterThan; break;
		case equalsEquals: ((RelExprNode*)rel)->type = EqualEqual; break;
		case lessThanEquals: ((RelExprNode*)rel)->type = LessEqual; break;
		case greaterThanEquals: ((RelExprNode*)rel)->type = GreaterEqual; break;
		case notEquals: ((RelExprNode*)rel)->type = NotEqual; break;
		default: pr.ok = false; /*makeerror()*/ break;
	}

	// just advance token, since examining it in parseExpr led 
	// to this method being called.
	nextToken( ) ;

	tpr = parseExpr( prevToken->lbp() );
	ExprNode* e = dynamic_cast<ExprNode*>(tpr.ast);

	if( e && tpr.ok ){
		rel->left = left.ast;
		rel->right = tpr.ast;
	} else {
		pr.ok = false;
	}

	pr.ast = rel;
	return pr ;
}

// Expr ::= Expr ':' Expr
ParseResult Parser::parseConsExpr ( ParseResult left ) {
	// parser has already matched left expression 
	ParseResult pr ;
	ParseResult tpr;

	OpExprNode* op = new OpExprNode();
	
	match(colon);
	((OpExprNode*)op)->type = Colon;
	op->left = left.ast;

	tpr = parseExpr( prevToken->lbp() );
	if( tpr.ok ) op->right = tpr.ast;
	pr.ast = op;

	return pr ;
}

// Expr ::= Expr '++' Expr
ParseResult Parser::parseAppendExpr ( ParseResult left ) {
	// parser has already matched left expression 
	ParseResult pr ;
	ParseResult tpr;
	match ( plusPlus ) ;

	OpExprNode* op = new OpExprNode();
	((OpExprNode*)op)->type = PlusPlus;
	op->left = left.ast;

	tpr = parseExpr( prevToken->lbp() );
	if( tpr.ok ) op->right = tpr.ast;
	pr.ast = op;  

	return pr ;
}

// Expr ::= 'let' DeclList 'in' Expr 'end'
ParseResult Parser::parseLetExpr ( ) {
	ParseResult pr;
	ParseResult tpr;
	Node* leti = new LetExprNode();
	
	match(letKwd);
    
	if ( (tpr = parseDeclList()).ok ){
		DeclListNode* l = dynamic_cast<DeclListNode*>(tpr.ast);
		if (l){
			leti->left = tpr.ast;
		} else {
			pr.ok = false;
			return pr;
		}
	}
    
	match(inKwd);

	if ( (tpr = parseExpr(0) ).ok ){
		ExprNode* r = dynamic_cast<ExprNode*>(tpr.ast);
    		if (r){
			leti->right = tpr.ast;
		} else {
			pr.ok = false;
			return pr;
		}
	}
    
	match(endKwd); 
	
    	pr.ast = leti;
	return pr;
} // parseLetExpr

// Expr ::= 'if' Expr 'then' Expr 'else' Expr
ParseResult Parser::parseIfThenElse ( ) {
	ParseResult pr ;
	ParseResult tpr;
    
	// if Expr
	match(ifKwd) ;
	Node* tmp = new IfExprNode();
	if( (tpr = parseExpr(0)).ok ){
		ExprNode* l = dynamic_cast<ExprNode*>(tpr.ast);
		if( l && tpr.ok ){
			tmp->left = tpr.ast;
		} else {
               pr.ok = false;
               return pr;
          }
	}

	// then Expr
	match(thenKwd) ;

	Node* ier = new Node();
	tmp->right = ier;
	
	if( (tpr = parseExpr(0)).ok ){
		ExprNode* re = dynamic_cast<ExprNode*>(tpr.ast);
		if( re && tpr.ok ){
			ier->left = tpr.ast;
		} else {
			pr.ok = false;
			return pr;
		}
	}
	    
	// else Expr
	match(elseKwd);

	if( (tpr = parseExpr(0)).ok ){
		ExprNode* inner = dynamic_cast<ExprNode*>(tpr.ast);
		if( inner && tpr.ok ){
			ier->right = tpr.ast;
		} else {
               pr.ok = false;
               return pr;
          }
	}
	
	pr.ast = tmp;
	
	return pr ;
}

// Expr ::= 'print' '(' Expr ')'
ParseResult Parser::parsePrintExpr ( ) {
	ParseResult pr;
	ParseResult tpr;
	match(printKwd);
	match(leftParen);
	
	Func1ExprNode* f = new Func1ExprNode();
	f->type = Print;
	tpr = parseExpr(0);
	ExprNode* e = dynamic_cast<ExprNode*>(tpr.ast);

	if( tpr.ok && e ){
		f->left = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(rightParen);
	pr.ast = f;

	return pr;
}

// Expr ::= 'write' '(' Expr, Expr ')'
ParseResult Parser::parseWriteExpr ( ) {
	ParseResult pr;
	ParseResult tpr;
	Func2ExprNode* f = new Func2ExprNode();
	ExprNode* e;

	match(writeKwd);
	match(leftParen);
	f->type = Write;
	
	tpr = parseExpr(0);
	e = dynamic_cast<ExprNode*>(tpr.ast);
	if( e && tpr.ok ){
		f->left = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(comma);

	tpr = parseExpr(0);
	e = dynamic_cast<ExprNode*>(tpr.ast);
	if( e && tpr.ok ){
		f->right = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(rightParen);
	pr.ast = f;

	return pr;
}

// Expr ::= 'read' '<' TypeExpr '>' '(' Expr ')'
ParseResult Parser::parseReadExpr ( ) {
    ParseResult pr ;
    ParseResult tpr;
    ReadExprNode* tmp = new ReadExprNode();
    
    match(readKwd) ;
    match(leftAngle) ;
    
    if ( (tpr = parseTypeExpr()).ok ){ 
		TypeExprNode* l = dynamic_cast<TypeExprNode*>(tpr.ast);
		if (l) tmp->left = l ;
	} // end if
    
    match(rightAngle) ;
    match(leftParen) ;
    
    if ( (tpr = parseExpr(0)).ok ){
		ExprNode* r = dynamic_cast<ExprNode*>(tpr.ast);
		if (r){
			tmp->right = r;
		}
	} // end if	
    
    match(rightParen) ;
	
	pr.ast = tmp;
	//cout << tmp->unparse() << endl;
    return pr ;
}

// Expr ::= 'head' '(' Expr ')'
ParseResult Parser::parseHeadExpr ( ) {
	ParseResult pr;
	ParseResult tpr;
	match(headKwd);
	match(leftParen);
	
	Func1ExprNode* f = new Func1ExprNode();
	f->type = Head;
	tpr = parseExpr(0);
	ExprNode* e = dynamic_cast<ExprNode*>(tpr.ast);

	if( tpr.ok && e ){
		f->left = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(rightParen);
	pr.ast = f;

	return pr;
}

// Expr ::= 'tail' '(' Expr ')'
ParseResult Parser::parseTailExpr ( ) {
	ParseResult pr;
	ParseResult tpr;
	match(tailKwd);
	match(leftParen);
	
	Func1ExprNode* f = new Func1ExprNode();
	f->type = Tail;
	tpr = parseExpr(0);
	ExprNode* e = dynamic_cast<ExprNode*>(tpr.ast);

	if( tpr.ok && e ){
		f->left = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(rightParen);
	pr.ast = f;

	return pr;
}

// Expr ::= 'null' '(' Expr ')'
ParseResult Parser::parseNullExpr ( ) {
	ParseResult pr;
	ParseResult tpr;
	match(nullKwd);
	match(leftParen);
	
	Func1ExprNode* f = new Func1ExprNode();
	f->type = Null;
	tpr = parseExpr(0);
	ExprNode* e = dynamic_cast<ExprNode*>(tpr.ast);

	if( tpr.ok && e ){
		f->left = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(rightParen);
	pr.ast = f;

	return pr;
}

// Expr ::= 'map' '(' Expr ',' Expr ')'
ParseResult Parser::parseMapExpr ( ) {
	ParseResult pr;
	ParseResult tpr;
	Func2ExprNode* f = new Func2ExprNode();
	ExprNode* e;

	match(mapKwd);
	match(leftParen);
	f->type = Map;
	
	tpr = parseExpr(0);
	e = dynamic_cast<ExprNode*>(tpr.ast);
	if( e && tpr.ok ){
		f->left = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(comma);

	tpr = parseExpr(0);
	e = dynamic_cast<ExprNode*>(tpr.ast);
	if( e && tpr.ok ){
		f->right = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(rightParen);
	pr.ast = f;

	return pr;
}

// Expr ::= 'filter' '(' Expr ',' Expr ')'
ParseResult Parser::parseFilterExpr ( ) {
	ParseResult pr;
	ParseResult tpr;
	Func2ExprNode* f = new Func2ExprNode();
	ExprNode* e;

	match(filterKwd);
	match(leftParen);
	f->type = Filter;
	
	tpr = parseExpr(0);
	e = dynamic_cast<ExprNode*>(tpr.ast);
	if( e && tpr.ok ){
		f->left = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(comma);

	tpr = parseExpr(0);
	e = dynamic_cast<ExprNode*>(tpr.ast);
	if( e && tpr.ok ){
		f->right = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(rightParen);
	pr.ast = f;

	return pr;
}

// Expr ::= 'fold' '(' Expr ',' Expr ',' Expr ')'
ParseResult Parser::parseFoldExpr ( ) {
    ParseResult pr ;
	ParseResult tpr;
    
	match(foldKwd) ;
	match(leftParen);
	
	FoldExprNode* tmp = new FoldExprNode();
	if( (tpr = parseExpr(0)).ok ){
		ExprNode* l = dynamic_cast<ExprNode*>(tpr.ast);
		if( l && tpr.ok ){
			tmp->left = tpr.ast;
		} else {
               pr.ok = false;
               return pr;
          }
	}

	Node* ier = new Node();
	tmp->right = ier;
	
	match(comma);
	
	if( (tpr = parseExpr(0)).ok ){
		ExprNode* re = dynamic_cast<ExprNode*>(tpr.ast);
		if( re && tpr.ok ){
			ier->left = tpr.ast;
		} else {
			pr.ok = false;
			return pr;
		}
	}
	
	match(comma);

	if( (tpr = parseExpr(0)).ok ){
		ExprNode* inner = dynamic_cast<ExprNode*>(tpr.ast);
		if( inner && tpr.ok ){
			ier->right = tpr.ast;
		} else {
               pr.ok = false;
               return pr;
          }
	}
	
	match(rightParen);
	
	pr.ast = tmp;
	
	// cout << pr.ast->unparse() << endl;
	return pr ;
   
}

// Expr ::= 'zip' '(' Expr ',' Expr ')'
ParseResult Parser::parseZipExpr ( ) {
	ParseResult pr;
	ParseResult tpr;
	Func2ExprNode* f = new Func2ExprNode();
	ExprNode* e;

	match(zipKwd);
	match(leftParen);
	f->type = Zip;
	
	tpr = parseExpr(0);
	e = dynamic_cast<ExprNode*>(tpr.ast);
	if( e && tpr.ok ){
		f->left = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(comma);

	tpr = parseExpr(0);
	e = dynamic_cast<ExprNode*>(tpr.ast);
	if( e && tpr.ok ){
		f->right = tpr.ast;
	} else {
		pr.ok = false;
	}

	match(rightParen);
	pr.ast = f;

	return pr;
}

// Expr ::= '\' TypeBindingsList 'arrow' Expr
ParseResult Parser::parseLambdaExpr ( ) {
    ParseResult pr ;
    ParseResult tpr;
    
    match (backSlash);
    
    LambdaExprNode* tmp = new LambdaExprNode();
    
    if ( (tpr = parseTypeBindingList()).ok ){ 
		TypeBindingListNode* l = dynamic_cast<TypeBindingListNode*>(tpr.ast);
		if (l) tmp->left = l ;
	} // end if
	
	match(arrow) ;
    
    if ( (tpr = parseExpr(0)).ok ){
		ExprNode* r = dynamic_cast<ExprNode*>(tpr.ast);
		if (r){
			tmp->right = r;
		}
	} // end if	
	
	pr.ast = tmp;
	//cout << tmp->unparse() << endl;
    return pr ;
}

// Expr ::= tupleOp '(' Expr ')'
ParseResult Parser::parseProjectionExpr () {
// This probably needs its' own class with variableName ( Expr )
// to allow a lexeme

	ParseResult pr;
	ParseResult tpr;
	LexFuncNode* f = new LexFuncNode();
	
	if (nextIs(tupleOp)){
		std::string lex = currToken->lexeme;
		match(tupleOp);
	
		f->lexeme = lex;
	} // end if
	
	
	tpr = parseNestedOrTupleExpr();
	ExprListNode* e = dynamic_cast<ExprListNode*>(tpr.ast);

	if( tpr.ok && e ){
		f->left = tpr.ast;
	} else {
		pr.ok = false;
	}
	
	pr.ast = f;

	return pr;
}


// Helper function used by the parser.

void Parser::match (terminal_t tt) {
    if (! attemptMatch(tt)) {
        throw ( makeErrorMsgExpected ( tt ) ) ;
    }
}

bool Parser::attemptMatch (terminal_t tt) {
    if (currToken->terminal == tt) { 
        nextToken() ;
        return true ;
    }
    return false ;
}

bool Parser::nextIs (terminal_t tt) {
    return currToken->terminal == tt ;
}

void Parser::nextToken () {
    if (currToken->terminal == endOfFile && currToken->next == NULL) {
        prevToken = currToken ;
    } else if (currToken->terminal != endOfFile && currToken->next == NULL) {
        throw ( makeErrorMsg ( "Error: tokens end with endOfFile" ) ) ;
    } else {
        prevToken = currToken ;
        currToken = currToken->next ;
    }
}

string Parser::terminalDescription ( terminal_t terminal ) {
    Token *dummyToken = makeToken (terminal, "", 0) ;
    ExtToken *dummyExtToken = extendToken (this, dummyToken) ;
    string s = dummyExtToken->description() ;
    delete dummyToken ;
    delete dummyExtToken ;
    return s ;
}

string Parser::makeErrorMsgExpected ( terminal_t terminal ) {
    string s = (string) "Expected " + terminalDescription (terminal) +
        " but found " + currToken->description() ;
    return s ;
}

string Parser::makeErrorMsg ( terminal_t terminal ) {
    string s = "Unexpected symbol " + terminalDescription (terminal) ;
    return s ;
}

string Parser::makeErrorMsg ( const char *msg ) {
    return msg ;
}

