//vector.h
#ifndef VECTOR_H
#define VECTOR_H

typedef int Rank;
const int DEFAULT_CAPACITY = 20;

template <typename T> class Vector {
private:
	Rank size; int capacity; T *elem;
protected:
	void expand();
public:
	Vector();//默认构造函数
	Vector(const Rank s);
	Vector(T* const list, int s);
	Rank getSize(){return size;}
	void push(const T &e);
	T getElem(Rank r)const{return elem[r];};
	Rank find(T &e, Rank r)const;//寻找元素
};

template <typename T> void Vector<T>::expand(){
	if(size < capacity ) return;
	T *oldElem = elem;
	elem = new T[capacity<<=1];
	for(int i=0;i<size;i++)
		elem[i]=oldElem[i];
	delete [] oldElem;
}
template <typename T> Vector<T>::Vector(){
	elem = new T[capacity = DEFAULT_CAPACITY];
	for (int i = 0; i < capacity; elem[i++] = 0 ); 
	size = 0;
}
template <typename T> Vector<T>::Vector(const Rank s){
	elem = new T[capacity = s];
	for (int i = 0; i < capacity; elem[i++] = 0 ); 
	size = 0;
}
template <typename T> Vector<T>::Vector(T* const list, int s){
	capacity = s;
	elem = new T[capacity];
	for (int i = 0; i < capacity; i++ )
		elem[i] = list[i];
	size = s;
}
template <typename T> void Vector<T>::push(const T &e){
	expand();
	elem[size++]=e;
}
template <typename T> Rank Vector<T>::find(T &e, Rank r)const{
	for(int i = r;i>-1;--i){
		if(e == elem[i]) return i;
	}
	return -1;
}

#endif