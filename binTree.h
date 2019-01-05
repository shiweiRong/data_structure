//binTree.h
#ifndef BINTREE_H
#define BINTREE_H

#include "binNode.h"
#include "vector.h" 

template <typename T> class BinTree {
protected:
	int _size; BinNodePosi(T) _root;
public:
	BinTree() : _size ( 0 ), _root ( NULL ) { }
	int size() const { return _size; }
	bool empty() const { return !_root; }
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot ( T const& e ); 
	BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e ); 
	BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e ); 	
	BinNodePosi(T) properRebuild(Vector<T> preLL, Vector<T> postLL);//真二叉树重构
	void travIn() const;
};

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot ( T const& e )
{ _size = 1; return _root = new BinNode<T> ( e ); } //将e当作根节点插入空的二叉树
template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC ( BinNodePosi(T) x, T const& e )
{ _size++; x->insertAsLC ( e ); return x->lc; } //e插入为x的左孩子
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC ( BinNodePosi(T) x, T const& e )
{ _size++; x->insertAsRC ( e ); return x->rc; } //e插入为x的右孩子
template <typename T> BinNodePosi(T) BinTree<T>::properRebuild(Vector<T> preLL, Vector<T> postLL){
	Rank pre_lo = 0; Rank pre_hi = preLL.getSize(); Rank post_hi = pre_hi;
	T root_data = preLL.getElem(pre_lo);
	insertAsRoot(root_data);
	_root->rebuildLRC(preLL, pre_lo, pre_hi, postLL, post_hi);
	_size = post_hi;
	return _root;
}
template <typename T> void BinTree<T>::travIn()const{
	if(!_root){cout<<"empty!"<<endl;return;}
	_root->travIn();
}
#endif