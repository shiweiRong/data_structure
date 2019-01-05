///listNode.h
#ifndef LISTNODE_H
#define LISTNODE_H
#define ListNodePosi ListNode* //�б�ڵ�λ��
#define NULL 0

struct ListNode{//˫������
//��Ա
	char letter; int mark; ListNodePosi pred; ListNodePosi succ;//��ĸ����ǡ�ǰ�������
//���캯��
	ListNode(){mark = 0;}//���header��trailer�Ĺ�����
	ListNode(char a,int b, ListNodePosi p = NULL, ListNodePosi s = NULL):letter(a), mark(b), pred(p), succ(s){};//Ĭ�Ϲ�����
//�����ӿ�
	ListNodePosi insertAsSucc (const char &e);//���浱ǰ�ڵ�֮������½ڵ�
};

ListNodePosi ListNode::insertAsSucc(const char &e){
	int b = (letter == e) ? mark+1:1;
	ListNodePosi x = new ListNode(e, b, this, succ);
	succ -> pred = x; succ = x;
	return x;
}

#endif 