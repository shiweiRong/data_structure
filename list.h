//list.h
#ifndef LIST_H
#define LIST_H
#include "listNode.h"
#include <iostream>
using namespace std;

typedef int Rank ;
const int DEFAULT_CAPACITY = 5;


template <typename T> class List{
private:
	ListNodePosi header;ListNodePosi trailer;

protected:
	void init();

public:
	ListNodePosi posi;
	List(){ init(); };//д╛хо
	bool isEmpty()const;
	void insertAsLast(const T *e, Rank lo, Rank hi);
	void insertAsLast(const T e);
	void display();
	ListNodePosi last(){return trailer->pred;}
	T& getElem(Rank rank);
	int getSize();
	T& firstElem(){return header->succ->t;};
	T& removeFirst();
};

template <typename T> void List<T>::init(){
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	posi = header;
}
template <typename T> bool List<T>::isEmpty()const{
	return header->succ == trailer ? true:false;
}
template <typename T> void List<T>::insertAsLast(const T * e, Rank lo, Rank hi){
    posi = trailer->pred;
	for(int i=lo;i<hi;i++){
		posi = posi->insertAsSucc(e[i]);
	}
}
template <typename T> void List<T>::insertAsLast(const T e){
    posi = trailer->pred;
	posi = posi ->insertAsSucc(e);
}
template <typename T> void List<T>::display(){
	if(isEmpty()){
		cout<<"this list is empty"<<endl;
		return;
	}

	posi = header->succ;
	do{
		cout<<posi->t<<" ";
		posi = posi ->succ;
	}while (posi != trailer);
	cout<<endl;
	return;
}
template <typename T> T& List<T>::getElem(Rank rank){
	posi = header->succ;
	for(int i=0;i<rank;i++) posi = posi->succ;
	return posi->t;
}
template <typename T> int List<T>::getSize(){
	int size = 0;posi = header->succ;
	while(posi != trailer){
		size++;
		posi = posi->succ;
	}
	return size;
}
template <typename T> T& List<T>::removeFirst(){
	T e = header->succ->t;
	header->succ = header->succ->succ;
	header->succ->pred = header;
	return e;
}
#endif 