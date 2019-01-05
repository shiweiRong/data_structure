//main.cpp
#include "list.h"
#include "stack.h"
#include <iostream>
using namespace std;

int main()
{
	int n,m;
	cin>>n>>m;

	int *b = new int[n];
	for(int i=0;i<n;i++) cin>>b[i];


	Stack<int> S(m);
    
	List<bool> R;//PUSH = true = 1, POP = false = 0;

	//cout<<"GAME BEGIN "<<endl;
	int a = 1;
	int j = 0;
	while(j<n){
		if(!S.isEmpty() && b[j] == S.top()){
			S.pop(); j++;R.insertAsLast(false);//POP = false = 0
		}
		else{
			if(a <= n+1 && !S.isFull()){
				S.push(a++);R.insertAsLast(true);//PUSH = true = 1
			}
			else{
				cout<<"No"<<endl; 
				return 0;
			}
		}	
	}
	
	int size = R.getSize();bool result;
	for(int i=0;i<size;i++){
		result = R.getElem(i);
		if(result) cout<<"push"<<endl;
		else cout<<"pop"<<endl;
	}
	return 0;
}