// LightHouse.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
#include "vector.h"
#include "light.h"
#include <iostream>
using namespace std;
typedef long TYPE;

int main()
{
	//����˼·���Ժ�������������ٶ�������鲢���򣬲����������Ե����������ι鲢����ķ������в�ͬ

	//cout<<"�����������������";
	TYPE n;
	cin>>n;

	Vector<TYPE> v;
	TYPE *x= new TYPE[n]; TYPE *y= new TYPE[n];
	for(TYPE i=0;i<n;i++)
	{
		//cout<<"����������ĺ������꣺";
		cin>>x[i]>>y[i];
		v.add(x[i],y[i]);
	}
	//cout<<endl<<"���е�����ԭʼλ�����ݣ�"<<endl;v.display();

	v.mergeSort(0,v.getSize());
	//cout<<endl<<"���պ�����鲢�����"<<endl;v.display();

	TYPE invI = v.invInside(0,v.getSize());
	//cout<<endl<<"����������鲢�����"<<endl;v.display();
    cout<<invI;

	return 0;
}
