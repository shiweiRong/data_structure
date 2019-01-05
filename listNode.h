///listNode.h
#ifndef LISTNODE_H
#define LISTNODE_H
#define ListNodePosi ListNode<T>*
#define NULL 0

template <typename T> struct ListNode{
//��Ա
	T t; ListNodePosi pred; ListNodePosi succ;
//���캯��
	ListNode(){t = NULL; pred = NULL; succ = NULL; }//���header��trailer�Ĺ�����
	ListNode(T t, ListNodePosi pred = NULL, ListNodePosi succ = NULL):t(t), pred(pred), succ(succ){};
//�����ӿ�
	ListNodePosi insertAsSucc (const T &e);//���浱ǰ�ڵ�֮������½ڵ�
};

template <typename T> ListNodePosi ListNode<T>::insertAsSucc(const T &e){
	ListNodePosi x = new ListNode<T>(e, this, succ);
	succ -> pred = x; succ = x;
	return x;
}

#endif 