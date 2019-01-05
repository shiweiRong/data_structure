//main.h
#include "binTree.h"
#include "vector.h"

int main(){
	int n;
	cin>>n;
	
	int *pre = new int[n]; 
	for(int i=0;i<n;i++){
		cin>>pre[i];
	}
    int *post = new int[n];
	for(int i=0;i<n;i++){
		cin>>post[i];
	}
	Vector<int> preLL(pre,n); Vector<int> postLL(post,n);
	BinTree<int> tree;
	tree.properRebuild(preLL, postLL);//rebuild
	tree.travIn();//travel in order
	return 0;
}
