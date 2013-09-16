#include "../samples/common_header.h"
using namespace std;

int main (int argc, char **argv ) { 
	// make args as list of string 
	return({ MyList<  int >  someNumbers =  ({  MyList< int > temp;   temp.push_back( 1);
 temp.push_back( 2);
 temp.push_back( 3);
  temp;  }) ;
 MyList<  int >  moreNumbers =  ({ MyList< int > temp( 4,  10); temp;  }) ;
 MyList<  int >  allNumbers =  ( someNumbers + moreNumbers );

	({ cout <<  allNumbers << endl; 0;});
	})  ;
}
;

