/* ParseResult: a simple object for holding the result of a parse.

   Author: Eric Van Wyk

   Last modified: March 5, 2012.
*/

#ifndef PARSER_RESULT_H
#define PARSER_RESULT_H

#include <string>
#include <iostream>

using namespace std;

/******
TODO:

	-Expr ::= '\' TypeBindingsList 'arrow' Expr
	-Expr ::= 'fold' '(' Expr ',' Expr ',' Expr ')'
	-Expr ::= 'read' '<' TypeExpr '>' '(' Expr ')'


	// ADD TONS OF TESTS

*******/

// Base Node class
class Node {
public:
	virtual string unparse() {
		return "";
	};
	
	virtual string cppCode() {
		return "";
	};
	

	Node* left;
	Node* right;

	Node(){
		this->left = NULL;
		this->right = NULL;
	};
};


class ParseResult {
public:
    ParseResult() ;
    string errors ;
    string pp ;
    bool ok ;
    Node* ast;
};

class ExprNode;
class DeclNode;
class DeclListNode;
class TypeExprNode;
class TypeExprListNode;
class FoldExprNode;

/*****************************************
 *	-Expression classes
 *
 ****************************************/


class ExprNode: public Node {
public:
	string unparse();
	string cppCode();
};


// Keyword Expression Type
typedef enum KwdExpEnum {
	VariableName, IntConst, FloatConst, StringConst,
	TrueKwd, FalseKwd
} KEtype ;

// Operator Expression Type
typedef enum OpExprEnum {
	Plus, Star, ForwardSlash, Minus, Percent,
	Colon, PlusPlus, DotDot
} Optype ;

// Relative Expression Types
typedef enum RelExprEnum {
	EqualEqual, LessThan, GreaterThan, LessEqual, GreaterEqual,
	NotEqual
} Reltype;

// Function Type with a single expression
typedef enum Func1TypeEnum {
	Print, Head, Tail, Null
} F1type;

// Function Type with two expressions
typedef enum Func2TypeEnum {
	Write, Map, Filter, Zip
} F2type;


// EXPR::
// list
// let

// Relative Expression Node Class
class RelExprNode: public ExprNode {
public:
	Reltype type;
	
     string unparse() {
		string retS( "" );
		retS += " (";
		// unparse left
		ExprNode* e = dynamic_cast<ExprNode*>(this->left);
		if( e ) retS += e->unparse();

		switch(type) {
			case EqualEqual: retS += " =="; break;
			case LessThan: retS += " <"; break;
			case GreaterThan: retS += " >"; break;
			case LessEqual: retS += " <="; break;
			case GreaterEqual: retS += " >="; break;
			case NotEqual: retS += " !="; break;
		}

		// unparse right
		e = dynamic_cast<ExprNode*>(this->right);
		if( e ) retS += e->unparse();
		retS += " )";
		
		return retS;
     };
     
     string cppCode() {
		string retS( "" );
		retS += " (";
		// unparse left
		ExprNode* e = dynamic_cast<ExprNode*>(this->left);
		if( e ) retS += e->unparse();

		switch(type) {
			case EqualEqual: retS += " =="; break;
			case LessThan: retS += " <"; break;
			case GreaterThan: retS += " >"; break;
			case LessEqual: retS += " <="; break;
			case GreaterEqual: retS += " >="; break;
			case NotEqual: retS += " !="; break;
		}

		// unparse right
		e = dynamic_cast<ExprNode*>(this->right);
		if( e ) retS += e->unparse();
		retS += " )";
		
		return retS;
     };
};

// If then else Expression Class
class IfExprNode: public ExprNode {
public:	
	string unparse(){
		string retS;
		ExprNode* e;

		retS += " if";
		e = dynamic_cast<ExprNode*>(this->left);
		if( e ) retS += e->unparse();
		
		retS += " then";
		e = dynamic_cast<ExprNode*>(this->right->left);
		if( e ) retS += e->unparse();
		
		retS += " else";
		e = dynamic_cast<ExprNode*>(this->right->right);
		if( e ) {
			retS += e->unparse();
		}
		
		return retS;
	} 
	
	string cppCode(){
		string retS;
		ExprNode* e;

		retS += " ( (";
		ExprNode* re = dynamic_cast<ExprNode*>(this->left);
		if( re ) retS += re->cppCode();
		
		retS += " ) ? (";
		e = dynamic_cast<ExprNode*>(this->right->left);
		if( e ) retS += e->cppCode();
		
		retS += " ) : (";
		e = dynamic_cast<ExprNode*>(this->right->right);
		if( e ) {
			retS += e->cppCode();
		}
		
		retS += " ) )";
		
		return retS;
	} 

}; // end IfExprNode

// Operation Expression Class
class OpExprNode: public ExprNode {
public:
	Optype type;
	
     string unparse() {
		string retS( "" );
		retS += " (";
		// unparse left
		ExprNode* e = dynamic_cast<ExprNode*>(this->left);
		if( e ) retS += e->unparse();

		switch(type) {
			case Plus: retS += " +"; break;
			case Star: retS += " *"; break;
			case Minus: retS += " -"; break;
			case ForwardSlash: retS += " /"; break;
			case Percent: retS += " %"; break;
			case Colon: retS += " :"; break;
			case PlusPlus: retS += " ++"; break;
			case DotDot: retS += " .."; break;
		}

		// unparse right
		e = dynamic_cast<ExprNode*>(this->right);
		if( e ) retS += e->unparse();
		retS += " )";
		
		return retS;
     };
     
     
     /// cpp Code
     string cppCode() {
		string retS( "" );
		retS += " (";
		// unparse left
		ExprNode* e = dynamic_cast<ExprNode*>(this->left);
		if( e ) retS += e->cppCode();

		switch(type) {
			case Plus: retS += " +"; break;
			case Star: retS += " *"; break;
			case Minus: retS += " -"; break;
			case ForwardSlash: retS += " /"; break;
			case Percent: retS += " %"; break;
			case Colon: break;
			case PlusPlus: retS += " ++"; break;
			case DotDot: retS += " .."; break;
		}

		// unparse right
		e = dynamic_cast<ExprNode*>(this->right);
		if( e ) retS += e->cppCode();
		retS += " )";
		
		if (type == Colon){
			retS = " (";
			e = dynamic_cast<ExprNode*>(this->right);
			if( e ) retS += e->cppCode();		
			retS += " ).cons("; 
			ExprNode* el = dynamic_cast<ExprNode*>(this->left);
			if( el ) {
				//el->type = 1;
				retS += el->cppCode();	
			}
			retS += ")";
			return retS;
		} else {
			return retS;
		}
     }; // end cpp Code
};

// Class for functions with lexemes, i.e. varName ( Expr )  and tupleOp ( Expr )
class LexFuncNode: public ExprNode {
public:
	string lexeme;
	
	string unparse(){
		string retS( " " );

		retS += lexeme;
		retS += " (";
		ExprNode* e = dynamic_cast<ExprNode*>(this->left);
		if( e ) retS += e->unparse();
		retS += " )";

		return retS;
	}
	
	int type;
	string cppCode(){
		string retS( " " );

		retS += lexeme;
		retS += " (";
		ExprNode* e = dynamic_cast<ExprNode*>(this->left);
		if( e ) retS += e->cppCode();
		retS += " )";

		return retS;
	}
}; 

// Class for functions with one Expr after
class Func1ExprNode: public ExprNode {
public:
	F1type type;

	string unparse(){
		string retS( "" );
		ExprNode* e;
		switch( type ){
			case Print:
				retS += " print (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " )";
				break;
			case Head:
				retS += " head (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " )";
				break;
			case Tail:
				retS += " tail (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " )";
				break;
			case Null:
				retS += " null (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " )";
				break;
		}
		return retS;
	};
	
	string cppCode(){
		string retS( "" );
		ExprNode* e;
		switch( type ){
			case Print:
				retS += "({ cout << ";
				// FoldExprNode* tr = dynamic_cast<FoldExprNode*>(this->left);
				e = dynamic_cast<ExprNode*>(this->left);
				/*
				if (tr) {
					retS += tr->cppCode();
				} else */
				if( e ){
					retS += e->cppCode();
				}
				retS += " << endl; 0;})";
				break;
			case Head:
				retS += " (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->cppCode();
				retS += ".head() )";
				break;
			case Tail:
				retS += " (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->cppCode();
				retS += ".tail() )";
				break;
			case Null:
				retS += " (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->cppCode();
				retS += ".null() )";
				break;
		}
		return retS;
	};

};

class Func2ExprNode: public ExprNode {
public:
	F2type type;

	string unparse(){
		string retS;
		ExprNode* e;

		switch( type ){
			case Write:
				retS += " write (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " ,";
				e = dynamic_cast<ExprNode*>(this->right);
				if( e ) retS += e->unparse();
				retS += " )";
				break;
			case Map:
				retS += " map (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " ,";
				e = dynamic_cast<ExprNode*>(this->right);
				if( e ) retS += e->unparse();
				retS += " )";
				break;
			case Filter:
				retS += " filter (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " ,";
				e = dynamic_cast<ExprNode*>(this->right);
				if( e ) retS += e->unparse();
				retS += " )";
				break;
			case Zip:
				retS += " zip (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " ,";
				e = dynamic_cast<ExprNode*>(this->right);
				if( e ) retS += e->unparse();
				retS += " )";
				break;
		}

		return retS;
	} // end unparse()
	
	// ================ start cppCode
	string cppCode(){
		string retS;
		ExprNode* e;

		switch( type ){
			case Write:
				retS += " write (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " ,";
				e = dynamic_cast<ExprNode*>(this->right);
				if( e ) retS += e->unparse();
				retS += " )";
				break;
			case Map:
				retS += " ( ";
				e = dynamic_cast<ExprNode*>(this->right);
				if( e ) retS += e->unparse();
				retS += ".map (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " ) ) ";
				break;
			case Filter:
				// variable name
				e = dynamic_cast<ExprNode*>(this->right);
				if( e ) retS += e->unparse();
				retS += ".filter (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " )";
				break;
			case Zip:
				e = dynamic_cast<ExprNode*>(this->right);
				if( e ) retS += e->unparse();
				retS += ".zip (";
				e = dynamic_cast<ExprNode*>(this->left);
				if( e ) retS += e->unparse();
				retS += " )";
				break;
		}

		return retS;
	} // end cppCode()
		
};

class KwdExprNode: public ExprNode {
public:
	KEtype type;
	string lexeme;
    string unparse() {
		string retS;
		retS += " " + lexeme;
          return retS;
    };
    
    string cppCode() {
		string retS;
		retS += " " + lexeme;
        return retS;
    };    
};

class ExprListNode: public ExprNode{
public:
	string unparse(){
		string retS;

		ExprNode* t = dynamic_cast<ExprNode*>(this->left);
		if( t ) retS += t->unparse();

		ExprListNode* te = dynamic_cast<ExprListNode*>(this->right);
		if( te ) {
			retS += " ,";
			retS += te->unparse();
		}

		return retS;
	};
	
	int type;
	
	string cppCode(){
		string retS;

		ExprNode* t = dynamic_cast<ExprNode*>(this->left);
		if( t ) {
			if (type == 0){
				retS += t->cppCode();
			} else {
				retS += " temp.push_back(";
				retS += t->cppCode();
				retS += ");\n";
			}
		}

		ExprListNode* te = dynamic_cast<ExprListNode*>(this->right);
		if( te ) {
			if (te-> type == 0){
				retS += ", ";
			}
			
			te->type = type;
			retS += te->cppCode();
		}

		return retS;
	};
};

class OptionalExprListNode: public ExprNode{
public:
	string unparse(){
		string retS = "";

		ExprListNode* te = dynamic_cast<ExprListNode*>(this->left);
		if( te ) {
			retS += te->unparse();
		}

		return retS;
	};
	
	int type;
	// type 0, regular
	// type 1, temp.push_back
	
	string cppCode(){
		
		string retS = " ";

		ExprListNode* te = dynamic_cast<ExprListNode*>(this->left);
		if( te ) {
			te->type = type;
			retS += te->cppCode();
		}
		
		retS += " ";

		return retS;
	};
};

     
/******************************************
 *	-Type Expression classes
 *
 *****************************************/

// Type Expression Type
typedef enum TEtypeEnum {
	Integer, Float, String, Boolean,
	TElist,  		//'(' TypeExprList ')'
	Bexpr,		// '[' TypeExpr ']'
	Aexpr // '(' TypeBindingList ')' '->' TypeExpr
} TEtype;

class TypeExprNode: public Node {
public:
	TEtype type;

     string unparse() {
		string retS;
		switch( type ){
			case Integer:
				retS += " Integer";
				break;
			case Float:
				retS += " Float";
				break;
			case String:
				retS += " String";
				break;
			case Boolean:
				retS += " Boolean";
				break;
			case TElist:
				retS += " (";
				if( this->left ) retS += this->left->unparse();
				retS += " )";
				break;
			case Bexpr:
				retS += " [";
				if( this->left ) retS += this->left->unparse();
				retS += " ]";
				break;
			case Aexpr:
				retS += " (";
				if( this->left ) retS += this->left->unparse();
				retS += " ) ->";
				if( this->right ) retS += this->right->unparse();
				break;
		}

		return retS;
	};
	
	string cppCode(){
		string code ( "" );
		switch( type ){
			case Integer:
				code += " int";
				break;
			case Float:
				code += " float";
				break;
			case String:
				code += " string";
				break;
			case Boolean:
				code += " bool";
				break;
			case TElist:
				code += " pair< ";
				if( this->left ) code += this->left->cppCode();
				code += " > ";
				break;
			case Bexpr:
				code += " MyList< ";
				if( this->left ) code += this->left->cppCode();
				code += " > ";
				break;
			case Aexpr:
				/*
				code += " (";
				if( this->left ) code += this->left->cppCode();
				code += " ) ->";
				*/
				if( this->right ) code += this->right->cppCode();
				break;
		} // end switch
		
		return code;
	};
};

class TypeExprListNode: public Node{
public:
	string unparse(){
		string retS;

		TypeExprNode* t = dynamic_cast<TypeExprNode*>(this->left);
		if( t ) retS += t->unparse();

		TypeExprListNode* te = dynamic_cast<TypeExprListNode*>(this->right);
		if( te ) {
			retS += " ,";
			retS += te->unparse();
		}
		
		return retS;
	};
	
	string cppCode(){
		string retS;

		TypeExprNode* t = dynamic_cast<TypeExprNode*>(this->left);
		if( t ) retS += t->cppCode();

		TypeExprListNode* te = dynamic_cast<TypeExprListNode*>(this->right);
		if( te ) {
			retS += " ,";
			retS += te->cppCode();
		}
		
		return retS;
	};
};


/******************************************************************************
 *	- Declaration List Classes
 *
 *****************************************************************************/

class VarNameNode: public Node{
public:
	string lexeme;	

	string unparse(){
		return "" + lexeme;
	};
	
	string cppCode(){
		return "" + lexeme;
	};
};

// variableName '::' TypeExpr = Expr
class DeclRNode: public Node {
public:
     string unparse() {
		string retS;
		
		/* Might cause an error? TypeExpr already is TypeExpr, TypeExprList */
		TypeExprNode* l = dynamic_cast<TypeExprNode*>(this->left);
		//TypeExprListNode* te = dynamic_cast<TypeExprListNode*>(this->left);
		if( l ){
			retS += l->unparse();
		}
		/*
		if( te ){
			retS += " (";
			retS += te->unparse();
			retS += " )";
		}
		*/
		retS += " =";
		ExprNode* r = dynamic_cast<ExprNode*>(this->right);
		if( r ){
			retS += r->unparse();
		}

		return retS;
	};
	
	string cppCode() {
		string code ("");
		
		/*
		TypeExprNode* l = dynamic_cast<TypeExprNode*>(this->left);
		if (l) {
			code += l->cppCode();
		}
		*/
		
		return code;
	};
};

class DeclNode: public Node {
public:
     string unparse() {
		string retS;

		VarNameNode* l = dynamic_cast<VarNameNode*>(this->left);
		if( l ){
			retS += l->unparse();
		}
		retS += " ::";
		DeclRNode* r = dynamic_cast<DeclRNode*>(this->right);
		if( r ){
			retS += r->unparse();
		}

		return retS;
	};
	
	string cppCode() {
		string code ("");
		
		VarNameNode* l = dynamic_cast<VarNameNode*>(this->left);
		string var_name = l->cppCode();
		
		TypeExprNode* func = dynamic_cast<TypeExprNode*>((this->right)->left);
		string ft = func->cppCode();
		
		ExprNode* r = dynamic_cast<ExprNode*>((this->right)->right);
		string exp = r->cppCode();
		
		if (func->type == Aexpr){
			string args = (func->left)->cppCode();
			if (var_name == "main"){
				code += "int main (int argc, char **argv ) { \n";
				code +=	"	// make args as list of string \n";
				code += "	return";
				code += exp;
				code += "  ;\n}\n" ;
			} 
			// end if
			else {
				// this is a regular function
				// code += "int ";
				code += ft + " ";
				code += var_name;
				code += "(";
				code += args;
				code += ") {\n\treturn ";
				code += exp;
				code += " ;\n}\n";
			} // end else
		} // end func->type
		else {
				//code += "int ";
				code += ft + " ";
				//code += (func->left)->unparse();
				//code += var_name;
				code += var_name;
				code += " = ";
				code += exp;
		}
		
		
		// cout << code << endl;
		
		return code;
	}; // end cpp Code
};

class DeclListNode: public Node {
public:
	string unparse() {
		string retS;

		DeclNode* l = dynamic_cast<DeclNode*>(this->left);
		if( l ){
			retS += l->unparse();
		}
		retS += ";\n";	
		DeclListNode* r = dynamic_cast<DeclListNode*>(this->right);
		if( r ){
			retS += r->unparse();
		}
		return retS;
	};
	
	
	// initial call
	string cppCode(){
		
		string code ( "#include \"../samples/common_header.h\"\n");
		code += "using namespace std;\n\n";
		
		
		DeclNode* l = dynamic_cast<DeclNode*>(this->left);
		if( l ){
			code += l->cppCode();
		}
		code += ";\n";	
		
		DeclListNode* r = dynamic_cast<DeclListNode*>(this->right);
		if( r ){
			code += r->cppSubCode();
		}
		
		return code;
	};
	
	// subprocedure for declList used if not the very first call
	string cppSubCode(){
		string code ("");
		DeclNode* l = dynamic_cast<DeclNode*>(this->left);
		if( l ){
			code += l->cppCode();
		}
		code += ";\n";	
		
		DeclListNode* r = dynamic_cast<DeclListNode*>(this->right);
		if( r ){
			code += r->cppSubCode();
		}
		
		return code;
	
	}
};

/******************************************************************************
 *	- typebinding and list classes
 *
 *****************************************************************************/

class TypeBindingNode: public Node{
public:
	string unparse(){
		string retS;
		// variableName
		VarNameNode* vn = dynamic_cast<VarNameNode*>(this->left);
		if( vn ) retS += vn->unparse();	
		
		retS += " ::";

		// TypeExpr and TypeExprList as well
		TypeExprNode* r = dynamic_cast<TypeExprNode*>(this->right);
		if( r ) retS += r->unparse();
	
		return retS;
	};
	
	string cppCode(){
		string retS ("" );
		
		// TypeExpr and TypeExprList as well
		TypeExprNode* r = dynamic_cast<TypeExprNode*>(this->right);
		if( r ) retS += r->cppCode();
		
		retS += " ";
		
		// variableName
		VarNameNode* vn = dynamic_cast<VarNameNode*>(this->left);
		if( vn ) retS += vn->cppCode();	
	
		return retS;
	};
};
 
class TypeBindingListNode: public Node{
public:
	string unparse(){
		string retS;

		TypeBindingNode* t = dynamic_cast<TypeBindingNode*>(this->left);
		if( t ) retS += t->unparse();
	
		
		TypeBindingListNode* te = dynamic_cast<TypeBindingListNode*>(this->right);
		if( te ) {
			retS += " ,";
			retS += te->unparse();
		}

		return retS;
	};
	
	string cppCode(){
		string retS;

		TypeBindingNode* t = dynamic_cast<TypeBindingNode*>(this->left);
		if( t ) retS += t->cppCode();
	
		
		TypeBindingListNode* te = dynamic_cast<TypeBindingListNode*>(this->right);
		if( te ) {
			retS += " ,";
			retS += te->cppCode();
		}

		return retS;
	};
};

/***************************************************************************************
 *	-Classes that need other classes to be declared
 *
 **************************************************************************************/

 //	-Let In End : LetExprNode
class LetExprNode: public ExprNode{
public:
     string unparse() {
		string retS( "" );
		retS += "\nlet\n";
		
		// unparse left
		DeclListNode* e = dynamic_cast<DeclListNode*>(this->left);
		if( e ) retS += e->unparse();

		retS += "\nin\n";
		// unparse right
		
		ExprNode* m = dynamic_cast<ExprNode*>(this->right);
		if( m ) retS += m->unparse();
		
		retS += "\nend";
		
		return retS;
     };
     
     string cppCode() {
		string retS( "({" );
		
		// unparse left: let x in
		DeclListNode* e = dynamic_cast<DeclListNode*>(this->left);
		if( e ) retS += e->cppSubCode();

		// unparse right: in x end
		retS += "\n\t";
		ExprNode* m = dynamic_cast<ExprNode*>(this->right);
		if( m ) retS += m->cppCode();
		
		retS += ";\n\t})";
		
		return retS;
     };
};


class ReadExprNode: public ExprNode{
public: 
	string unparse(){
		string retS( "read < " );
		
		TypeExprNode* l = dynamic_cast<TypeExprNode*>(this->left);
		if (l) retS += l->unparse();
		
		retS += " > ( ";
		
		ExprNode* r = dynamic_cast<ExprNode*>(this->right);
		if (r) retS += r->unparse();
		
		retS += " ) ";
		
		return retS;
	}; // end unparse()
		
	string cppCode(){
		string retS( " ({ " );
		
		TypeExprNode* l = dynamic_cast<TypeExprNode*>(this->left);
		if (l) retS += l->cppCode();
		
		retS += " temp; ifstream inStream(";
		
		ExprNode* r = dynamic_cast<ExprNode*>(this->right);
		if (r) retS += r->unparse();
		
		retS += " ) ; inStream >> temp; temp; }) ";
		
		return retS;
	}; // end unparse()		
};

class FoldExprNode: public ExprNode{
public:	
	string unparse(){
		string retS;
		ExprNode* e;

		retS += " fold (";
		e = dynamic_cast<ExprNode*>(this->left);
		if( e ) retS += e->unparse();
		
		retS += " ,";
		e = dynamic_cast<ExprNode*>(this->right->left);
		if( e ) retS += e->unparse();
		
		retS += " ,";
		e = dynamic_cast<ExprNode*>(this->right->right);
		if( e ) {
			retS += e->unparse();
		}
		
		retS += " )";
		
		return retS;
	}
	
	string cppCode(){
		string retS;
		ExprNode* e;
		// var name
		e = dynamic_cast<ExprNode*>(this->right->right);
		if( e ) {
			retS += e->unparse();
		}
		retS += ".fold (";
		e = dynamic_cast<ExprNode*>(this->left);
		if( e ) retS += e->unparse();
		
		retS += " ,";
		e = dynamic_cast<ExprNode*>(this->right->left);
		if( e ) retS += e->unparse();
		retS += " )";
		
		return retS;
	} 
};

class LambdaExprNode: public ExprNode{
public:
	string unparse(){
		string retS;
		
		retS = "\\";
		
		TypeBindingListNode* l = dynamic_cast<TypeBindingListNode*>(this->left);
		if (l) retS += l->unparse();
		
		retS += " -> ";
		
		ExprNode* r = dynamic_cast<ExprNode*>(this->right);
		if (r) retS += r->unparse();
		
		
		return retS;
	} ;		
};

class BraceExprNode: public ExprNode {
public:
	int type;
	string unparse() {
		string retS ( "[" );
		
		if (type == 1 ){
			retS += " < ";
			TypeExprNode* t = dynamic_cast<TypeExprNode*>(this->left);
			if ( t ) { retS += t->unparse(); }
			retS += " > ";
			
			OptionalExprListNode* oe = dynamic_cast<OptionalExprListNode*>(this->right);
			if ( oe ) { retS += oe->unparse(); }
		}
		else if (type == 2){
			ExprNode* e1 = dynamic_cast<ExprNode*>(this->left);
			if ( e1 ) { retS += e1->unparse(); }
			
			retS += " .. ";
			
			ExprNode* e2 = dynamic_cast<ExprNode*>(this->right);
			if ( e2 ) { retS += e2->unparse(); }
			
		}
		
		retS += "]";
		return retS;
	} // end unparse()
	
	string cppCode() {
		string retS ( " ({ " );
		
		// [ < > option_list ]
		if (type == 1 ){
			retS += " MyList<";
			TypeExprNode* t = dynamic_cast<TypeExprNode*>(this->left);
			
			if ( t ) { retS += t->cppCode(); }
			retS += " > temp; ";
			
			OptionalExprListNode* oe = dynamic_cast<OptionalExprListNode*>(this->right);
			if ( oe ) { 
				oe->type = 1;
				retS += oe->cppCode(); 
			}
			
			retS += " temp; ";
		}
		// [ .. ]
		else if (type == 2){
			retS += "MyList< int > temp(";
			
			ExprNode* e1 = dynamic_cast<ExprNode*>(this->left);
			if ( e1 ) { retS += e1->cppCode(); }
			
			retS += ", ";
			
			ExprNode* e2 = dynamic_cast<ExprNode*>(this->right);
			if ( e2 ) { retS += e2->cppCode(); }
			
			retS += "); ";
			
			retS += "temp; ";
		}
		
		retS += " }) ";
		return retS;
	} // end cppCode()
};

 //	-ExprNode 
inline string ExprNode::unparse() {
		KwdExprNode* k = dynamic_cast<KwdExprNode*>(this);
		OpExprNode* o = dynamic_cast<OpExprNode*>(this);
		IfExprNode* i = dynamic_cast<IfExprNode*>(this);
		ReadExprNode* r = dynamic_cast<ReadExprNode*>(this);
		LetExprNode* l = dynamic_cast<LetExprNode*>(this);
		FoldExprNode* f = dynamic_cast<FoldExprNode*>(this);
		LambdaExprNode* la = dynamic_cast<LambdaExprNode*>(this);
		BraceExprNode* b = dynamic_cast<BraceExprNode*>(this);
		if( k ) { k->unparse();
		} else
		if( o ) { o->unparse();
		} else 
		if ( i ) { i->unparse();
		} else
		if ( l ) { l->unparse();
		} else
		if ( r ) { r->unparse();
		} else
		if ( f ) { f->unparse();
		} else
		if ( la ) { la->unparse();
		} else
		if ( b ) { b->unparse() ;
		}

		return "";
};

inline string ExprNode::cppCode() {
		KwdExprNode* k = dynamic_cast<KwdExprNode*>(this);
		OpExprNode* o = dynamic_cast<OpExprNode*>(this);
		IfExprNode* i = dynamic_cast<IfExprNode*>(this);
		ReadExprNode* r = dynamic_cast<ReadExprNode*>(this);
		LetExprNode* l = dynamic_cast<LetExprNode*>(this);
		FoldExprNode* f = dynamic_cast<FoldExprNode*>(this);
		LambdaExprNode* la = dynamic_cast<LambdaExprNode*>(this);
		BraceExprNode* b = dynamic_cast<BraceExprNode*>(this);		
		RelExprNode* rel = dynamic_cast<RelExprNode*>(this);
		if( k ) { k->cppCode();
		} else
		if( o ) { o->cppCode();
		} else 
		if ( i ) { i->cppCode();
		} else
		if ( l ) { l->cppCode();
		} else
		if ( r ) { r->unparse();
		} else
		if ( f ) { f->cppCode();
		} else
		if ( la ) { la->unparse();
		} else
		if ( b ) { b->cppCode() ;
		} else
		if ( rel ) { rel->cppCode();
		}
		

		return "";
};



#endif /* PARSER_RESULT_H */
