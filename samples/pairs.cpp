#include "../samples/common_header.h"
using namespace std;

int main (int argc, char **argv ) { 
	// make args as list of string 
	return({ MyList<  int >  xs =  ({ MyList< int > temp( 1,  10); temp;  }) ;
 MyList<  int >  ys =  ({ MyList< int > temp( 11,  20); temp;  }) ;
 MyList<  pair<  int , int >  >  ps =  ys.zip ( xs );

	({ cout <<  ps << endl; 0;});
	})  ;
}
;

