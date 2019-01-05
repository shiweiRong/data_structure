// Zuma.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include "listNode.h"
#include "list.h"
#include <string>


void showZuma(const List z){
	string s1,s2;
	bool b = z.display(s1,s2);
	if (b == false)//序列为空
		cout <<"-"<<endl;
	else
		cout<<s1<<endl;
}
int main()
{
	
	//cout<<"请输入初始祖玛序列：";
	string s;
	cin>>s;
	unsigned int isize = s.size();
	List zuma;
	for(int i=0; i<isize; i++){
		zuma.insert(i,s[i]);
	}
	//cout<<"初始序列：";showZuma(zuma);

	
	//cout<<"请输入操作次数：";
	int n;
	cin>>n;

	int *k = new int[n];char *e = new char[n];
	for(int i=0; i<n; i++){
		//cout<<"请输入第"<<i+1<<"次操作数："<<endl;
		cin>>k[i]>>e[i];
		zuma.insert(k[i],e[i]);
		//cout<<"第"<<i+1<<"次操作后的序列：";
		showZuma(zuma);
	} 
		
	return 0;
}

