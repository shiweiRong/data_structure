//list.h
#ifndef LIST_H
#define LIST_H
#include "listNode.h"
#include <iostream>
#include <sstream>
using namespace std;

const int LIMIT = 3;

class List {
private:
	int size;
	ListNodePosi header;ListNodePosi trailer;

protected:
	void init();//�б���ʱ�ĳ�ʼ��
	bool renewMark(ListNodePosi p);//����mark
	ListNodePosi insertAsLast (const char &e); //��e����ĩ�ڵ����
	ListNodePosi insertAfter (ListNodePosi p, char const& e ); //��e����p�ĺ�̲��루After��
	void remove(ListNodePosi p, int k);//ɾ��p֮ǰ��k���ڵ�

public:
//���캯��
	List(){ init(); };//Ĭ��
//����ӿ�
	int getSize() const{return size;}//�õ����еĴ�С
	bool display(string &s1, string &s2) const;//�������
	ListNodePosi getTrailer(){return trailer;}
//�����ӿ�
	void insert(const int & k,const char &e);//��c�����k��Ԫ�صĺ���
};

void List::init(){
	size = 0;
	header = new ListNode;
	trailer = new ListNode;
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
}
bool List::renewMark(ListNodePosi p){
	if (p->mark == 0 )//header��trailer��mark����Ҫ����
		return false;
	if(p->pred->letter == p->letter){
		p->mark = p->pred->mark + 1;
	}	
	else{
		if(p->mark == 1)
			return false;
		else
			p->mark = 1;
	}
	return true;
}
bool List::display(string &s1, string &s2)const{
	s1.clear();s2.clear();
	if (size == 0){
		return false;
	}

	ListNodePosi p = header->succ;
	ostringstream ss1,ss2;
	for(int i =0;i<size;i++){
		ss1 << p->letter;ss2 << p->mark;
		p = p->succ;
	}
	s1 = ss1.str();s2 = ss2.str();
	return true;
}
ListNodePosi List::insertAsLast (const char &e){
	size++;
	return trailer->pred->insertAsSucc(e);
}
ListNodePosi List::insertAfter( ListNodePosi p, char const& e ){
	size++;
	return p->insertAsSucc(e);
}
void List::remove(ListNodePosi p, int k){
	ListNodePosi x = p->pred;
	for(int i=0;i<k;i++ )
		x = x->pred;
	x->succ = p; p->pred = x;
	size = size -k;
}
void List::insert(const int & k,const char &e){
	int kk = k >size ? size:k;

	ListNodePosi p = header;
	for(int i=0;i<kk;i++){
		p = p->succ;
	}
	p = insertAfter(p,e);

	p = p->succ;
	int num;
	while(1){
		if(p->mark == 0){//pָ��trailer
			num = p->pred->mark;
			if(num >= LIMIT)
			remove(p,num);//����ɾ������
			return;
		}

		num = p->pred->mark;
		if(p->mark == 1 && num >= LIMIT)
			remove(p,num);//����ɾ������

		if (renewMark(p) == false)
			return;
		p = p->succ;
	};
}

#endif 