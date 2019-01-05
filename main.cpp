//main.h
#include "graphMatrix.h"
#include <iostream>
using namespace std;

int main(){
	int n, m;
	cin>>n>>m;

    GraphMatrix<int, int> g;
	int villige;
	for( int i = 0; i < n; i ++){
		villige = g.insert( i + 1 );
	}

	int a;
	int b;
	for( int i = 0; i < m; i ++){
		cin>>a>>b;
		g.insert(1, a - 1, b - 1);
		g.insert(1, b - 1, a - 1);
	}

	int maxOut = 0;
	for(int i = 0; i < g.n; i ++){
		if (g.outDegree( maxOut ) < g.outDegree( i ))
			maxOut = i;
	}
    g.bfs( maxOut );

	int first =  g.firstNbr ( maxOut );
	int second = g.nextNbr ( maxOut, first );
	if (g.height( first ) < g.height( second )){
		int t = first;
		first = second;
		second = t;
	}
	for ( int u = g.firstNbr ( maxOut ); -1 < u; u = g.nextNbr ( maxOut, u ) ){
		if( g.height( first ) < g.height( u ) ){
			first = u;
		}
	}
	for ( int u = g.firstNbr ( maxOut ); -1 < u; u = g.nextNbr ( maxOut, u ) ){
		if( g.height( second ) < g.height( u ) && u != first){
			second = u;
		}
	}
	int result = g.height( first ) + g.height( second ) + 5;
	cout<<result;

	return 0;
}