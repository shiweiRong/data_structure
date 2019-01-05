//queue.h
#ifndef QUEUE_H
#define QUEUE_H
#include "listNode.h"

template <typename T> class Queue { //列表模板类
 private:
   int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //规模、头哨兵、尾哨兵
protected:
   void init(); //列表创建时的初始化
   int clear(); //清除所有节点
public:
// 构造函数
   Queue() { init(); } //默认
// 析构函数
   ~Queue(); //释放（包含头、尾哨兵在内的）所有节点
   Rank size() const { return _size; } //规模
   bool empty() const { return _size <= 0; } //判空
   ListNodePosi(T) first() const { return header->succ; } //首节点位置
// 可写访问接口
   ListNodePosi(T) insertAsLast ( T const& e ); 
   T remove ( ListNodePosi(T) p ); //删除合法位置p处的节点,返回被删除节点

   void enqueue ( T const& e ) { insertAsLast ( e ); } 
   T dequeue() { return remove ( first() ); } 
   T& front() { return first()->data; } 
};

template <typename T> void Queue<T>::init() { //列表初始化，在创建列表对象时统一调用
   header = new ListNode<T>; //创建头哨兵节点
   trailer = new ListNode<T>; //创建尾哨兵节点
   header->succ = trailer; header->pred = NULL;
   trailer->pred = header; trailer->succ = NULL;
   _size = 0; //记录规模
}
template <typename T> int Queue<T>::clear() { //清空列表
   int oldSize = _size;
   while ( 0 < _size ) remove ( header->succ ); //反复删除首节点，直至列表变空
   return oldSize;
}
template <typename T> Queue<T>::~Queue() //列表析构器
{ clear(); delete header; delete trailer; } //清空列表，释放头、尾哨兵节点
template <typename T> ListNodePosi(T) Queue<T>::insertAsLast ( T const& e )
{  _size++; return trailer->insertAsPred ( e );  } //e当作末节点插入
template <typename T> T Queue<T>::remove ( ListNodePosi(T) p ) { //删除合法节点p，返回其数值
   T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
   p->pred->succ = p->succ; p->succ->pred = p->pred; //后继、前驱
   delete p; _size--; //释放节点，更新规模
   return e; //返回备份的数值
}

#endif