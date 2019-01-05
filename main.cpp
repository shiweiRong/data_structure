#include "graphMatrix.h"
#include <iostream>
int main(){
	int n, m ;
	std::cin>>n>>m;
	GraphMatrix<int, int> towns;
	for(int i = 0; i < n; i ++)
		towns.insert(i+1);
	int a, b;
	for(int i = 0; i < m; i ++){
		std::cin>>a>>b;
		towns.insert(-1,a-1,b-1);
		towns.insert(-1,b-1,a-1);
	}
	towns.bfs(0);
	int result = towns.checkColor(0) ? 1:-1;
	std::cout<<result<<std::endl;
	return 0;
}
