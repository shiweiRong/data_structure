// Range.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
#include "vector.h"

int main(){//����˼·����n�����ݽ��й鲢����
	int n,m;
	cin>>n>>m;

	int *e = new int[n];;
	for(int i=0;i<n;i++) cin>>e[i];

	Vector<int> v(e,n);
	v.mergeSort(0,v.getSize());
	
	int a, b;
	int * num = new int[m];
	for(int i=0;i<m;i++){
		cin>>a>>b;
		num[i] = v.numBetw(a,b);
	}
	
	//report result
	for(int i=0;i<m;i++){
		cout<<num[i]<<endl;
	}

	return 0;
}