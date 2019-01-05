//binNode.h
#ifndef BINNODE_H
#define BINNODE_H

#include "vector.h"
#include <iostream>
using namespace std;

#define BinNodePosi(T) BinNode<T>* 
#define stature(p) ((p) ? (p)->height : -1)
//#define NULL 0

template <typename T> struct BinNode {
	T data; //数值
    BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; //父节点及左、右孩子
//构造函数
	BinNode():parent(NULL),lc(NULL),rc(NULL){};
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL):
	data ( e ), parent ( p ), lc ( lc ), rc ( rc ){ }// 操作接口
//操作接口
	int size(); //统计当前节点后代总数，亦即以其为根的子树的规模
    BinNodePosi(T) insertAsLC ( T const& ); //作为当前节点的左孩子插入新节点
    BinNodePosi(T) insertAsRC ( T const& ); //作为当前节点的右孩子插入新节点 
	void rebuildLRC(Vector<T>  &preVector, Rank pre_lo, Rank pre_hi, Vector<T>  &postVector, Rank post_hi);//单节点左右孩子重构
    void travIn() const; //子树中序遍历
};

template <typename T> int BinNode<T>::size(){
	int s = 1; //计入本身
    if ( lc ) s += lc->size(); //递归计入左子树规模
    if ( rc ) s += rc->size(); //递归计入右子树规模
    return s;
}
template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC ( T const& e )
 { return lc = new BinNode ( e, this ); } 
template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC ( T const& e )
 { return rc = new BinNode ( e, this ); } 
template <typename T> void BinNode<T>::rebuildLRC(Vector<T>  &preVector, Rank pre_lo, Rank pre_hi, Vector<T>  &postVector, Rank post_hi){
	Rank len = pre_hi - pre_lo;
	if(len < 2) return;

	Rank lc_pre_lo, lc_pre_hi, lc_post_hi; Rank len_lc; T lc_data;
	Rank rc_pre_lo, rc_pre_hi, rc_post_hi; Rank len_rc; T rc_data;
	
	
	lc_pre_lo = pre_lo + 1;//
	lc_data = preVector.getElem(lc_pre_lo);
	
	rc_post_hi = post_hi - 1;
    rc_data = postVector.getElem(rc_post_hi - 1);

	lc_post_hi = postVector.find(lc_data, post_hi - 3) + 1;
	
	len_rc = rc_post_hi - lc_post_hi;
	len_lc = len -1 - len_rc;
	lc_pre_hi = lc_pre_lo + len_lc;

	
	rc_pre_lo = lc_pre_hi;
	rc_pre_hi = pre_hi;
	rc_post_hi = post_hi - 1;
    
	insertAsLC(lc_data);insertAsRC(rc_data);

	lc->rebuildLRC(preVector, lc_pre_lo, lc_pre_hi, postVector, lc_post_hi);
	rc->rebuildLRC(preVector, rc_pre_lo, rc_pre_hi, postVector, rc_post_hi);

	return;
}
template <typename T> void BinNode<T>::travIn()const {
	if(lc)
		lc->travIn();
	cout<<data<<" ";
	if(rc)
		rc->travIn();
}


#endif