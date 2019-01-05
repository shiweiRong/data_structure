// LightHouse.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include "vector.h"
#include "light.h"
#include <iostream>
using namespace std;
typedef long TYPE;

int main()
{
	//本题思路：对横坐标进行排序；再对纵坐标归并排序，并计算非逆序对的数量；两次归并排序的方法略有不同

	//cout<<"请输入灯塔的总数：";
	TYPE n;
	cin>>n;

	Vector<TYPE> v;
	TYPE *x= new TYPE[n]; TYPE *y= new TYPE[n];
	for(TYPE i=0;i<n;i++)
	{
		//cout<<"请输入灯塔的横纵坐标：";
		cin>>x[i]>>y[i];
		v.add(x[i],y[i]);
	}
	//cout<<endl<<"所有灯塔的原始位置数据："<<endl;v.display();

	v.mergeSort(0,v.getSize());
	//cout<<endl<<"按照横坐标归并排序后："<<endl;v.display();

	TYPE invI = v.invInside(0,v.getSize());
	//cout<<endl<<"按照纵坐标归并排序后："<<endl;v.display();
    cout<<invI;

	return 0;
}
