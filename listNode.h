///listNode.h
#ifndef LISTNODE_H
#define LISTNODE_H
#define ListNodePosi ListNode* //列表节点位置
#define NULL 0

struct ListNode{//双向链表
//成员
	char letter; int mark; ListNodePosi pred; ListNodePosi succ;//字母、标记、前驱、后继
//构造函数
	ListNode(){mark = 0;}//针对header和trailer的构造器
	ListNode(char a,int b, ListNodePosi p = NULL, ListNodePosi s = NULL):letter(a), mark(b), pred(p), succ(s){};//默认构造器
//操作接口
	ListNodePosi insertAsSucc (const char &e);//紧随当前节点之后插入新节点
};

ListNodePosi ListNode::insertAsSucc(const char &e){
	int b = (letter == e) ? mark+1:1;
	ListNodePosi x = new ListNode(e, b, this, succ);
	succ -> pred = x; succ = x;
	return x;
}

#endif 