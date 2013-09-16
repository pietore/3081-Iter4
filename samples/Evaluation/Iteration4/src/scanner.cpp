/*
*
* Title: Scanner
* Authors: Group 2 (Bill Graham, Eric Ung)
* Description: Functions to be used in the scanner class
*
*/

#include "regex.h"
#include "scanner.h"
#include <stdlib.h>
#include <string.h>


// function to ignore whitespace and comments from the input file
// by returning how many characters to ignore
int consumeWhiteSpaceAndComments (regex_t *ignorable, const char *text) {
	int numMatchedChars = 0;
	int totalMatchedChars = 0;

	// try to find whitespace or comments
	numMatchedChars = matchRegex(ignorable, text);
	totalMatchedChars = numMatchedChars;
	// check for more whitespace or comments
	// regex will match one or the other, not both
	while( numMatchedChars > 0 ){
		numMatchedChars = matchRegex(ignorable, text+totalMatchedChars);
		totalMatchedChars += numMatchedChars;
	} // end while

	return totalMatchedChars;
} // end consumeWhiteSpaceAndComments


// scanner constructor function
Scanner::Scanner(){
	// regular expression to match whitespace or comments, universal, so far left and right Curly
	ignorable = *(makeRegex ("(^[\n\t\r ]+)|(^/\\*([^\\*]|\\*+[^\\*/])*\\*+/)"));
	// make the regular expressions so they are only made once
	regex = new Regexx();
} // end Scanner::Scanner()


Token* Scanner::scan (const char *buffer){

	// check to see if buffer is nothing, if yes, quit
	if( buffer == NULL ){
		return NULL;
	} // end if buffer == NULL
	
	// declare variables
	Token* origTokn;
	Token* curTokn;
	Token* tmpTokn;
	int numIgnore = 0;
  
	// set up the first token in the list
	numIgnore = consumeWhiteSpaceAndComments( &ignorable, buffer );
	buffer += numIgnore;
	origTokn = attemptMatch( buffer );
	curTokn = origTokn;
	buffer += (origTokn->lexeme).length();

	// iterate through while the buffer is not at the end of the file
	// update the buffer while reading and manipulate accordingly
	while( (curTokn->terminal) != endOfFile){
		// skip white spaces and comments in buffer
		numIgnore = consumeWhiteSpaceAndComments(&ignorable, buffer);
		buffer += numIgnore;
		
		// attempt a match and add it to the list if found
		// otherwise skip over unmatched character
		tmpTokn = attemptMatch(buffer);
		if( tmpTokn != NULL ){
			curTokn->next = tmpTokn;
			curTokn = tmpTokn;
		
			buffer += (tmpTokn->lexeme).length();
		} else {
			buffer++;
		} // end if
  	} // end while 

  return origTokn;
} // end Token* Scanner::scan


// check for a token match
Token* Scanner::attemptMatch (const char* buffer){

	if( buffer == NULL ){
		return NULL;
	}

	// initialize some variables
	int numMatchedChars = 0;
	int maxMatchedChars = 0;
	tokenType terminal = lexicalError;
	Token* toknptr = NULL;

  	// match let keyword
	numMatchedChars = matchRegex( &(this->regex->letKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = letKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if

  	// match in keyword
	numMatchedChars = matchRegex( &(this->regex->inKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = inKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match end keyword
	numMatchedChars = matchRegex( &(this->regex->endKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = endKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match if keyword
	numMatchedChars = matchRegex( &(this->regex->ifKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = ifKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match then keyword
	numMatchedChars = matchRegex( &(this->regex->thenKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = thenKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match else keyword
	numMatchedChars = matchRegex( &(this->regex->elseKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = elseKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match print keyword
	numMatchedChars = matchRegex( &(this->regex->printKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = printKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match read keyword
	numMatchedChars = matchRegex( &(this->regex->readKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = readKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if

	// match writeKwd
	numMatchedChars = matchRegex( &(this->regex->writeKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = writeKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match integer keyword
	numMatchedChars = matchRegex( &(this->regex->integerKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = integerKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match float keyword
	numMatchedChars = matchRegex( &(this->regex->floatKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = floatKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match boolean keyword
	numMatchedChars = matchRegex( &(this->regex->zipKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = zipKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if

  	// match boolean keyword
	numMatchedChars = matchRegex( &(this->regex->booleanKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = booleanKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match true keyword
	numMatchedChars = matchRegex( &(this->regex->trueKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = trueKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match false keyword
	numMatchedChars = matchRegex( &(this->regex->falseKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = falseKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match head keyword
	numMatchedChars = matchRegex( &(this->regex->headKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = headKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match tail keyword
	numMatchedChars = matchRegex( &(this->regex->tailKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = tailKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if

	// match null keyword
	numMatchedChars = matchRegex( &(this->regex->nullKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = nullKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match map keyword
	numMatchedChars = matchRegex( &(this->regex->mapKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = mapKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match filter keyword
	numMatchedChars = matchRegex( &(this->regex->filterKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = filterKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match fold keyword
	numMatchedChars = matchRegex( &(this->regex->foldKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = foldKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if

	// try to match intConst
  	numMatchedChars = matchRegex( &(this->regex->intConstRegE), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = intConst;
		maxMatchedChars = numMatchedChars;
  	}	
  	
  	// match float keyword
	numMatchedChars = matchRegex( &(this->regex->floatConstRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = floatConst;
		maxMatchedChars = numMatchedChars;
  	} // end if

  	// match string keyword
	numMatchedChars = matchRegex( &(this->regex->stringKwdRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = stringKwd;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
  	// match variableName keyword
	numMatchedChars = matchRegex( &(this->regex->variableNameRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = variableName;
		maxMatchedChars = numMatchedChars;
  	} // end if

  	// match string constant
	numMatchedChars = matchRegex( &(this->regex->stringConstRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = stringConst;
		maxMatchedChars = numMatchedChars;
  	} // end if
  	
	// try to match leftParen
	numMatchedChars = matchRegex( &(this->regex->leftParen), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = leftParen;
		maxMatchedChars = numMatchedChars;
  	}
  	
  	// try to match rightParen
	numMatchedChars = matchRegex( &(this->regex->rightParen), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = rightParen;
		maxMatchedChars = numMatchedChars;
  	}
 
	// try to match leftSquare
	numMatchedChars = matchRegex( &(this->regex->leftSquare), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = leftSquare;
		maxMatchedChars = numMatchedChars;
  	}
  	
	// try to match rightSquare
	numMatchedChars = matchRegex( &(this->regex->rightSquare), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = rightSquare;
		maxMatchedChars = numMatchedChars;
  	}
  	
  	// try to match leftAngle
	numMatchedChars = matchRegex( &(this->regex->leftAngle), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = leftAngle;
		maxMatchedChars = numMatchedChars;
  	}
  	
	// try to match rightAngle
	numMatchedChars = matchRegex( &(this->regex->rightAngle), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = rightAngle;
		maxMatchedChars = numMatchedChars;
  	}
  	

	// try to match colon
	numMatchedChars = matchRegex( &(this->regex->colon), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = colon;
		maxMatchedChars = numMatchedChars;
  	}
  	
	// try to match colonColon
	numMatchedChars = matchRegex( &(this->regex->colonColon), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = colonColon;
		maxMatchedChars = numMatchedChars;
  	}

	// try to match comma
	numMatchedChars = matchRegex( &(this->regex->comma), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = comma;
		maxMatchedChars = numMatchedChars;
  	}
  		
	// try to match semiColon
	numMatchedChars = matchRegex( &(this->regex->semiColon), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = semiColon;
		maxMatchedChars = numMatchedChars;
  	}
  	
	// try to match equalsSign
	numMatchedChars = matchRegex( &(this->regex->equalsSign), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = equalsSign;
		maxMatchedChars = numMatchedChars;
  	}
  	
  	
	// try to match plusSign
	numMatchedChars = matchRegex( &(this->regex->plusSign), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = plusSign;
		maxMatchedChars = numMatchedChars;
  	}
  	
  	
  	// try to match star
	numMatchedChars = matchRegex( &(this->regex->star), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = star;
		maxMatchedChars = numMatchedChars;
  	}
  	
  	
  	// try to match dash
	numMatchedChars = matchRegex( &(this->regex->dash), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = dash;
		maxMatchedChars = numMatchedChars;
  	}
	
  	// try to match forwardSlash
	numMatchedChars = matchRegex( &(this->regex->forwardSlash), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = forwardSlash;
		maxMatchedChars = numMatchedChars;
  	}
  	
  	// try to match percent
	numMatchedChars = matchRegex( &(this->regex->percent), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = percent;
		maxMatchedChars = numMatchedChars;
  	}
  	
  	
  	// try to match backSlash
	numMatchedChars = matchRegex( &(this->regex->backSlash), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = backSlash;
		maxMatchedChars = numMatchedChars;
  	} 
  
  	
  	
  	// try to match arrow
	numMatchedChars = matchRegex( &(this->regex->arrow), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = arrow;
		maxMatchedChars = numMatchedChars;
  	}  	
	
	
	// try to match equalsEquals
	numMatchedChars = matchRegex( &(this->regex->equalsEquals), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = equalsEquals;
		maxMatchedChars = numMatchedChars;
  	}
  	
  	// try to match lessThanEquals
	numMatchedChars = matchRegex( &(this->regex->lessThanEquals), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = lessThanEquals;
		maxMatchedChars = numMatchedChars;
  	}
  	
  
  	// try to match greaterThanEquals
	numMatchedChars = matchRegex( &(this->regex->greaterThanEquals), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = greaterThanEquals;
		maxMatchedChars = numMatchedChars;
  	}
  	
  	// try to match notEquals
	numMatchedChars = matchRegex( &(this->regex->notEquals), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = notEquals;
		maxMatchedChars = numMatchedChars;
  	}
  	
  	// try to match plusPlus
	numMatchedChars = matchRegex( &(this->regex->plusPlus), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = plusPlus;
		maxMatchedChars = numMatchedChars;
  	}
  	
  	// try to match dotDot
	numMatchedChars = matchRegex( &(this->regex->dotDot), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = dotDot;
		maxMatchedChars = numMatchedChars;
  	}

  	// try to match tupleOp
	numMatchedChars = matchRegex( &(this->regex->tupleOp), buffer);
  	if( numMatchedChars > maxMatchedChars ){
		terminal = tupleOp;
		maxMatchedChars = numMatchedChars;
  	}

	// check for lexical errors
	numMatchedChars = matchRegex( &(this->regex->lexicalErrorRegE), buffer);
	if( numMatchedChars > maxMatchedChars ){
		terminal = lexicalError;
		maxMatchedChars = numMatchedChars;
  	}
	
	// check for end of file
  	if( *(buffer) == '\0' ){
		terminal = endOfFile;
		maxMatchedChars = 1;
  	}
	

	if( maxMatchedChars == 0 ){
		maxMatchedChars = 1;
	}
	toknptr = makeToken( terminal, buffer, maxMatchedChars );
	
	return toknptr;

} // end Scanner::attemptMatch


// function to free the memory for all the tokens
void freeTokens ( Token* tokn ){
	
	if( tokn == NULL ){
		return;
	}

	Token* tmptokn;

	while( tokn != NULL ) {
		tmptokn = tokn->next;
		free( tokn );
		tokn = tmptokn;
	}

	return;
}


// Constructor for making regular expressions
Regexx::Regexx(){

	// Keywords
	letKwdRegE = *(makeRegex("^let"));
	inKwdRegE = *(makeRegex("^in"));
	endKwdRegE = *(makeRegex("^end"));
	ifKwdRegE = *(makeRegex("^if"));
	thenKwdRegE = *(makeRegex("^then"));
	elseKwdRegE = *(makeRegex("^else"));
	printKwdRegE = *(makeRegex("^print"));
	readKwdRegE = *(makeRegex("^read"));
	writeKwdRegE = *(makeRegex("^write"));
	integerKwdRegE = *(makeRegex("^Integer"));
	floatKwdRegE = *(makeRegex("^Float"));
	booleanKwdRegE = *(makeRegex("^Boolean"));
	stringKwdRegE = *(makeRegex("^String"));
	trueKwdRegE = *(makeRegex("^true"));
	falseKwdRegE = *(makeRegex("^false"));
	headKwdRegE = *(makeRegex("^head"));
	tailKwdRegE = *(makeRegex("^tail"));
	nullKwdRegE = *(makeRegex("^null"));
	mapKwdRegE = *(makeRegex("^map"));
	filterKwdRegE = *(makeRegex("^filter"));
	foldKwdRegE = *(makeRegex("^fold"));
	zipKwdRegE = *(makeRegex("^zip"));

	// Constants
	intConstRegE = *(makeRegex("^[0-9]+"));
	floatConstRegE = *(makeRegex("^[0-9]+\\.[0-9]+"));
	stringConstRegE = *(makeRegex("^\"([^\"\\]|\\.)*\""));

	// Names
	variableNameRegE = *(makeRegex("^[a-z][a-z0-9A-Z_]*"));
	
	// Punctuation
	leftParen = *(makeRegex("^\\("));
	rightParen = *(makeRegex("^\\)"));
	leftSquare = *(makeRegex("^\\["));
	rightSquare = *(makeRegex("^\\]"));
	leftAngle = *(makeRegex("^<"));		// not a lit.
	rightAngle = *(makeRegex("^>"));	// not a lit.
	colon = *(makeRegex("^\\:"));
	colonColon = *(makeRegex("^(\\:\\:)"));
	comma = *(makeRegex("^,"));
	semiColon = *(makeRegex("^\\;"));
	equalsSign = *(makeRegex("^\\="));
	
	// Mathematical operations
	plusSign = *(makeRegex("^\\+"));
	star = *(makeRegex("^\\*"));
	dash = *(makeRegex("^\\-"));
	forwardSlash = *(makeRegex("^/"));
	percent = *(makeRegex("^%"));
	backSlash = *(makeRegex("^[\\]"));
	arrow = *(makeRegex("^\\->"));
	equalsEquals = *(makeRegex("^\\=\\="));
	lessThanEquals = *(makeRegex("^<\\="));
	greaterThanEquals = *(makeRegex("^>\\="));
	notEquals = *(makeRegex("^\\!\\="));
	plusPlus = *(makeRegex("^\\+\\+"));
	
	// dots and dots
	dotDot = *(makeRegex("^\\.\\."));
	tupleOp = *(makeRegex("^\\#[1-9][0-9]*"));
	
	// End of file and lexical errors
	endOfFileRegE = *(makeRegex("^[\\]0"));
	lexicalErrorRegE = *(makeRegex("^[$&]"));
} // end Regexx


Token* makeToken(tokenType terminal, const char* buffer, int size){

	if( (buffer == NULL) ){
		return NULL;
	}

	Token* toknptr = new Token();
	char* string = (char*) calloc( (size + 1) , sizeof(char) );
	memcpy(string, buffer, size);
	memcpy(string+size, "\0", 1);
	//	string += size;
	//	string = '\0';
	toknptr->lexeme = string;
	toknptr->next = NULL;
	toknptr->terminal = terminal;
	free(string);
	return toknptr;
} // end makeToken
