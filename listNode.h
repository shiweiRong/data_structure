///listNode.h
#ifndef LISTNODE_H
#define LISTNODE_H
#define ListNodePosi ListNode<T>*
#define NULL 0

template <typename T> struct ListNode{
//成员
	T t; ListNodePosi pred; ListNodePosi succ;
//构造函数
	ListNode(){t = NULL; pred = NULL; succ = NULL; }//针对header和trailer的构造器
	ListNode(T t, ListNodePosi pred = NULL, ListNodePosi succ = NULL):t(t), pred(pred), succ(succ){};
//操作接口
	ListNodePosi insertAsSucc (const T &e);//紧随当前节点之后插入新节点
};

template <typename T> ListNodePosi ListNode<T>::insertAsSucc(const T &e){
	ListNodePosi x = new ListNode<T>(e, this, succ);
	succ -> pred = x; succ = x;
	return x;
}

#endif 