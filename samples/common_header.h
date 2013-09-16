#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>

using namespace std;


template < typename T >
class MyList{
public:
	list<T> listList;
	
	MyList();
	MyList(list<T> l);
	MyList(MyList<T>& ml);
	MyList(const MyList<T>& ml);
	MyList(T elem1, T elem2);
	
	void push_back(const T &elem){
		listList.push_back(elem);
	};
	
	void operator=(const MyList<T> &ll){
		this.listList = ll.listList;
	};
	
	void operator=(const list<T> &ll){
		this.listList = listList;
	};
	
	T head(){
		T i = listList.front();
		//listList.pop_back();
		return i;
	}
	
	MyList<T>& tail(){
		//listList.pop_back();
		//return (MyList)this;
		listList.pop_front();
		return (*this);
	}
	
	const bool null(){
		return listList.empty();
	}
	
	T fold(T (*f)(T n, T n1), T inc){
		typename list<T>::iterator i;
		int s_ize = listList.size();
		
		int sum;
		
		if (s_ize > 0){
			// inital step
			i = listList.begin();
			sum = (*f)(*i, inc);
			i++;
			
			// for each i < k;
			for (i = i; i != listList.end(); i++){
				sum += (*f)(*i, inc);
			} // end for
		} // end if
		
		return sum;
	} // end fold
	
	MyList<T> filter(bool (*f)(T n)){
		typename list<T>::iterator i;
		int s_ize = listList.size();
		MyList<T>* retL = new MyList<T>();
		
		if (s_ize > 0){
			// for each i < k
			for (i = listList.begin(); i != listList.end(); i++){
				if ((*f)(*i)){
					retL->push_back(*i);
				}
			} // end for
		} // end if
		
		return *retL;
	}
	
	
	MyList<T>& operator+(MyList<T>& rr){
		typename list<T>::iterator i;
		int s_ize = rr.listList.size();	
		
		
		if (s_ize > 0){
			// inital step;
			i = (rr.listList).begin();
			listList.push_back(*i);
			i++;
			
			// for each i < k;
			for (i = i; i != (rr.listList).end(); i++){
				listList.push_back(*i);
			} // end for

		} // end if
		return (*this);
		
	}; // end operator+
	
	MyList<T>& cons(T ll){
		listList.push_front(ll);
		return (*this);
	}
	
	MyList<T>& map(T (*f)(T n) ){
		typename list<T>::iterator i;
		int s_ize = listList.size();	
		
		
		if (s_ize > 0){
			// initial step
			i = (listList).begin();
			*i = (*f)(*i);
			i++;
			
			// for each i < k
			for (i = i; i != (listList).end(); i++){
				*i = (*f)(*i);
			} // end for

		} // end if
		return (*this);
	}
	
		
	// works only with pair types
	MyList< pair<T,T> >& zip(MyList<T>& rr){
		typename list<T>::iterator i;
		typename list<T>::iterator j;
		int s_ize = listList.size();
		MyList< pair<T,T> >* retL = new MyList< pair<T,T> >();
		pair<T,T> insertTmp;
		if (s_ize != rr.listList.size()){
			return (*retL);
		}
		
		i = listList.begin();
		j = rr.listList.begin();
		if (s_ize > 0){
			// for each i < k
			for (i = i; i != listList.end(); i++){
				insertTmp.first = *j;
				insertTmp.second = *i;
				retL->push_back(insertTmp);
				j++;
			} // end for
		} // end if
		
		return (*retL);
	} // end zip
	
}; 

template<typename T>
MyList<T>::MyList(){
}


template<typename T>
MyList<T>::MyList(list<T> l){
	typename list<T>::iterator t;
	int s_ize_ = l.size();	
	
	if (s_ize_ > 0){
		// initial step
		t = (l).begin();
		listList.push_back(*t);
		t++;
		
		// for each i < k
		for (t = t; t != l.end(); t++){
			listList.push_back(*t);
		} // end for

	} //end if 

}

template<typename T>
MyList<T>::MyList(MyList<T>& ml){
	listList = ml.listList;
}

template<typename T>
MyList<T>::MyList(const MyList<T>& ml){
	listList = ml.listList;
}

template<typename T>
MyList<T>::MyList(T elem1, T elem2){
	
	for (int i = elem1; i <= elem2; i++){
		listList.push_back(i);
	}
	
}
	
template <class T>
inline ostream& operator<<(ostream &out, MyList<T> &ll){
	
	typename list<T>::iterator i;
	int s_ize = ll.listList.size();
	
	out << "[ ";
	
	if (s_ize > 0){
		// initial step
		i = (ll.listList).begin();
		out << *i;
		i++;
		
		// for each k
		for (i = i; i != (ll.listList).end(); i++){
			out << ", " << *i;
		} // end for
		
	}
	
	out << " ]";

	return out;
};

template <class T1, class T2>
inline ostream& operator<<(ostream &out, pair<T1, T2> &ll){

	out << "( " << ll.first << ", " << ll.second << " )";
	return out;
};


template <class T>
inline ifstream& operator>>(ifstream &in, MyList<T> &ll){
	
	string temp("");
	string newtemp("");
	string::iterator iter;
	int b;
	
	while (!in.eof() && temp != "]"){
		// grab some number
		in >> temp;
		
		// filter out commas
		for ( iter = temp.begin(); (iter != temp.end()); iter++){
			
			if (((*iter) != ',') && ((*iter) != '[') && ((*iter) != ']')){
				newtemp += (*iter);
			}
			
		} // end for 
		
		// filter out brackets
		if (temp != "[" && temp != "]"){
		
			// convert newtemp into int
			istringstream( newtemp ) >> b;
			
			// push into ll
			ll.push_back(b);
			
			// reset newtemp
			newtemp = "";
			
		} // end if
		
	} // end while
	
	return in;
}; // end operator>>




