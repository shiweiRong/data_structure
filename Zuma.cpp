// Zuma.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
#include "listNode.h"
#include "list.h"
#include <string>


void showZuma(const List z){
	string s1,s2;
	bool b = z.display(s1,s2);
	if (b == false)//����Ϊ��
		cout <<"-"<<endl;
	else
		cout<<s1<<endl;
}
int main()
{
	
	//cout<<"�������ʼ�������У�";
	string s;
	cin>>s;
	unsigned int isize = s.size();
	List zuma;
	for(int i=0; i<isize; i++){
		zuma.insert(i,s[i]);
	}
	//cout<<"��ʼ���У�";showZuma(zuma);

	
	//cout<<"���������������";
	int n;
	cin>>n;

	int *k = new int[n];char *e = new char[n];
	for(int i=0; i<n; i++){
		//cout<<"�������"<<i+1<<"�β�������"<<endl;
		cin>>k[i]>>e[i];
		zuma.insert(k[i],e[i]);
		//cout<<"��"<<i+1<<"�β���������У�";
		showZuma(zuma);
	} 
		
	return 0;
}

