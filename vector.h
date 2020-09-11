//vector.h
#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
using namespace std;

typedef int Rank;
const int DEFAULT_CAPACITY = 20;

template <typename T> class Vector{
private:
	Rank size; int capacity; T *elem;

protected:
	void expand();
	void swap(Rank i, Rank j){T e = elem[i]; elem[i] = elem[j]; elem[j] =e;}
	Rank binSearchA(T a, Rank lo, Rank hi)const;//对于a，查找大于等于a的最小秩元素
	Rank binSearchB(T b, Rank lo, Rank hi)const;//对于b，查找小于等于b的最大秩元素

public:
	Vector();//默认构造函数
	Vector(int c);//构造函数
	Vector(const T *e, const int s);

	void add(T e);//增加元素
	//void display()const;
	int getSize()const{return size;}

	//bool bubble(Rank lo, Rank hi); //扫描交换
    //void bubbleSort(Rank lo, Rank hi); //起泡排序

	void merge(Rank lo, Rank mi, Rank hi);//归并
	void mergeSort(Rank lo, Rank hi);//归并排序

	int numBetw(const int a, const int b);//落在[a,b]的元素个数
};

template <typename T> Vector<T>::Vector(){
	elem = new T[capacity = DEFAULT_CAPACITY];
	for (int i = 0; i < capacity; elem[i++] = 0 ); 
	size = 0;
}
template <typename T> Vector<T>::Vector(int c){
	elem = new T[capacity = c];
	for (int i = 0; i < capacity; elem[i++] = 0 ); 
	size = 0;
}
template <typename T> Vector<T>::Vector(const T *e, const int s){
	elem = new T[capacity = s];
	for (int i = 0; i < capacity; i++) elem[i] = e[i];
	size = s;
}

template <typename T> void Vector<T>::expand(){
	if(size < capacity ) return;
	T *oldElem = elem;
	elem = new T[capacity<<=1];
	for(int i=0;i<size;i++)
		elem[i]=oldElem[i];
	delete [] oldElem;
}
template <typename T> void Vector<T>::add(T e){
	expand();
	elem[size++]=e;
}

//template <typename T> void Vector<T>::display()const{
//	if(size==0){
//		cout<<"This list is empty."<<endl;
//		return;
//	}
//	for(int i=0;i<size;i++){
//		cout<<elem[i]<<" ";
//	}
//	cout<<endl;
//}

//template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi){
//	bool sorted = true;
//	while(++lo<hi){
//		if(elem[lo-1] > elem[lo]){
//			sorted = false;
//		    swap(lo-1,lo);
//		}	
//	}
//	return sorted;
//}
//template <typename T> void Vector<T>::bubbleSort(Rank lo, Rank hi){
//	while(!bubble(lo,hi--));
//}

template <typename T> void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if ( hi - lo < 2 ) return; 
    int mi = ( lo + hi ) / 2; 
    mergeSort(lo,mi);mergeSort(mi,hi);
	merge(lo,mi,hi);
}
template <typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T *A = elem + lo;
	int lb = mi - lo; T *B = new T [lb];
	for(Rank i=0;i<lb;i++) B[i] = A[i];//前子向量B
	int lc = hi - mi; T *C = elem + mi;//后子向量C
	for(Rank i=0,j=0,k=0;j<lb;)
	{
		if((lc <= k) || (B[j] <= C[k]))
			A[i++] = B[j++];
		if((k < lc) && (C[k] < B[j]))
			A[i++] = C[k++];
	}
	delete []B;
}

template <typename T> int Vector<T>::numBetw(const int a, const int b){
	int num = 0;
	Rank ra, rb;

	if(elem[size-1] < a || b < elem[0])
		return 0;

	if(elem[0] <= a && elem[size-1] < b){
		ra = binSearchA(a,0,size);
		num = size - ra;
		return num;
	}

	if(a < elem[0] && b <= elem[size-1]){
		rb = binSearchB(b,0,size);
		num = rb + 1;
		return num; 
	}

	ra = binSearchA(a,0,size);
	rb = binSearchB(b,ra,size);
	num = rb - ra +1;
	return num;	
}

template <typename T> Rank Vector<T>::binSearchA(T a, Rank lo, Rank hi)const{
	Rank mi;
	while ( lo < hi ) { 
		/*if(elem[lo] == elem[hi])
			return lo;
		else{
			mi = lo + ( hi - lo )*( a - elem[lo])/( elem[hi] - elem[lo] );
			( elem[mi] < a ) ? lo = mi + 1 : hi = mi; 
		}*/
		mi = ( lo + hi ) >> 1;
		( elem[mi] < a ) ? lo = mi + 1 : hi = mi;
	} 
	return lo;
}
template <typename T> Rank Vector<T>::binSearchB(T b, Rank lo, Rank hi)const{
	Rank mi;
	while ( lo < hi ) { 
		/*if(elem[lo] == elem[hi])
			return hi;
		else{
			mi = lo + ( hi - lo )*( b - elem[lo])/( elem[hi] - elem[lo] );
			( b < elem[mi] ) ? hi = mi : lo = mi + 1; 
		} */
		mi = ( lo + hi ) >> 1;
		( b < elem[mi] ) ? hi = mi : lo = mi + 1;
	}
	return --lo;
}

#endif