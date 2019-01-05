//vector.h
#ifndef VECTOR_H
#define VECTOR_H

typedef int Rank;
#define DEFAULT_CAPACITY  3 
 
template <typename T> class Vector { 
protected:
   Rank _size; int _capacity;  T* _elem; 
   void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi)
   void expand(); 
   void shrink(); //装填因子过小时压缩

public:
// 构造函数
   Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) 
   { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } 
// 析构函数
   ~Vector() { delete [] _elem; } 
// 只读访问接口
   Rank size() const { return _size; }
// 可写访问接口
   T& operator[] ( Rank r ); //重载下标操作符，可以类似于数组形式引用各元素
   const T& operator[] ( Rank r ) const; //仅限于做右值的重载版本
   Vector<T> & operator= ( Vector<T> const& ); //重载赋值操作符，以便直接克隆向量
   T remove ( Rank r ); //删除秩为r的元素
   int remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素
   Rank insert ( Rank r, T const& e ); 
   Rank insert ( T const& e ) { return insert ( _size, e ); } //默认作为末元素插入
 
};

template <typename T> void Vector<T>::copyFrom ( T const* A, Rank lo, Rank hi ) { //以数组区间A[lo, hi)为蓝本复制向量
   _elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //分配空间，规模清零
   while ( lo < hi ) //A[lo, hi)内的元素逐一
      _elem[_size++] = A[lo++]; //复制至_elem[0, hi - lo)
}
template <typename T> void Vector<T>::expand() { 
    if ( _size < _capacity ) return; 
    if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; 
    T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; 
    for ( int i = 0; i < _size; i++ )
       _elem[i] = oldElem[i]; 
    delete [] oldElem; 
}
template <typename T> void Vector<T>::shrink() { 
   if ( _capacity < DEFAULT_CAPACITY << 1 ) return; 
   if ( _size << 2 > _capacity ) return; 
   T* oldElem = _elem;  _elem = new T[_capacity >>= 1]; 
   for ( int i = 0; i < _size; i++ ) _elem[i] = oldElem[i]; 
   delete [] oldElem; 
}

template <typename T> T& Vector<T>::operator[] ( Rank r ) //重载下标操作符
{ return _elem[r]; } // assert: 0 <= r < _size 
template <typename T> const T& Vector<T>::operator[] ( Rank r ) const //仅限于做右值
{ return _elem[r]; } // assert: 0 <= r < _size
template <typename T> Vector<T>& Vector<T>::operator= ( Vector<T> const& V ) { //深复制
   if ( _elem ) delete [] _elem; //释放原有内容
   copyFrom ( V._elem, 0, V.size() ); //整体复制
   return *this; //返回当前对象的引用，以便链式赋值
}

template <typename T> T Vector<T>::remove ( Rank r ) { //删除向量中秩为r的元素，0 <= r < size
   T e = _elem[r]; //备份被删除元素
   remove ( r, r + 1 ); //调用区间删除算法，等效于对区间[r, r + 1)的删除
   return e; //返回被删除元素
}
template <typename T> int Vector<T>::remove ( Rank lo, Rank hi ) { //删除区间[lo, hi)
   if ( lo == hi ) return 0; //出于效率考虑，单独处理退化情况，比如remove(0, 0)
   while ( hi < _size ) _elem[lo++] = _elem[hi++]; //[hi, _size)顺次前移hi - lo个单元
   _size = lo; //更新规模，直接丢弃尾部[lo, _size = hi)区间
   shrink(); //若有必要，则缩容
   return hi - lo; //返回被删除元素的数目
}
template <typename T> Rank Vector<T>::insert ( Rank r, T const& e ) { //assert: 0 <= r <= size
   expand(); //若有必要，扩容
   for ( int i = _size; i > r; i-- ) _elem[i] = _elem[i-1]; //自后向前，后继元素顺次后移一个单元
   _elem[r] = e; _size++; //置入新元素并更新容量
   return r; //返回秩
}

#endif