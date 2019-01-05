//stack.h
#ifndef STACK_H
#define STACK_H
#include "list.h"
//const int DEFAULT_CAPACITY = 2;
#define DEFAULT_CAPACITY  2

template <typename T> class Stack: public List<T>{
private:
	List<T> l;
	int size; int capacity;
public:
	Stack(int c = DEFAULT_CAPACITY):l(),capacity(c){size = 0;}
	void display() {l.display();};
	void push(const T e){ l.insertAsLast(e);size++;}
	T& pop();
	T& top(){return l.last()->t;}
	bool isFull();
	bool isEmpty(){return size==0?true:false;}
};

template<typename T> T& Stack<T>::pop(){
	T result = l.last()->t;
	l.posi = l.last();
	l.posi->pred->succ = l.posi->succ; l.posi->succ->pred = l.posi->pred; 
	size--;
	return result;
}
template<typename T> bool Stack<T>::isFull(){
	return size >= capacity ? true:false;
}

#endif