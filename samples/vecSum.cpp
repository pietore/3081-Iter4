#include "../samples/common_header.h"
using namespace std;

 int add( int n , int m) {
	return  ( n + m ) ;
}
;
 int vecSum( MyList<  int >  vs) {
	return  vs.fold ( add , 0 ) ;
}
;
int main (int argc, char **argv ) { 
	// make args as list of string 
	return({ MyList<  int >  ns =  ({ MyList< int > temp( 1,  10); temp;  }) ;

	({ cout <<  vecSum (  ns  ) << endl; 0;});
	})  ;
}
;

