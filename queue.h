//queue.h
#ifndef QUEUE_H
#define QUEUE_H
#include "listNode.h"

template <typename T> class Queue { //�б�ģ����
 private:
   int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //��ģ��ͷ�ڱ���β�ڱ�
protected:
   void init(); //�б���ʱ�ĳ�ʼ��
   int clear(); //������нڵ�
public:
// ���캯��
   Queue() { init(); } //Ĭ��
// ��������
   ~Queue(); //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
   Rank size() const { return _size; } //��ģ
   bool empty() const { return _size <= 0; } //�п�
   ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��
// ��д���ʽӿ�
   ListNodePosi(T) insertAsLast ( T const& e ); 
   T remove ( ListNodePosi(T) p ); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�

   void enqueue ( T const& e ) { insertAsLast ( e ); } 
   T dequeue() { return remove ( first() ); } 
   T& front() { return first()->data; } 
};

template <typename T> void Queue<T>::init() { //�б��ʼ�����ڴ����б����ʱͳһ����
   header = new ListNode<T>; //����ͷ�ڱ��ڵ�
   trailer = new ListNode<T>; //����β�ڱ��ڵ�
   header->succ = trailer; header->pred = NULL;
   trailer->pred = header; trailer->succ = NULL;
   _size = 0; //��¼��ģ
}
template <typename T> int Queue<T>::clear() { //����б�
   int oldSize = _size;
   while ( 0 < _size ) remove ( header->succ ); //����ɾ���׽ڵ㣬ֱ���б���
   return oldSize;
}
template <typename T> Queue<T>::~Queue() //�б�������
{ clear(); delete header; delete trailer; } //����б��ͷ�ͷ��β�ڱ��ڵ�
template <typename T> ListNodePosi(T) Queue<T>::insertAsLast ( T const& e )
{  _size++; return trailer->insertAsPred ( e );  } //e����ĩ�ڵ����
template <typename T> T Queue<T>::remove ( ListNodePosi(T) p ) { //ɾ���Ϸ��ڵ�p����������ֵ
   T e = p->data; //���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
   p->pred->succ = p->succ; p->succ->pred = p->pred; //��̡�ǰ��
   delete p; _size--; //�ͷŽڵ㣬���¹�ģ
   return e; //���ر��ݵ���ֵ
}

#endif