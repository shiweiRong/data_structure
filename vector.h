//vector.h
#ifndef VECTOR_H
#define VECTOR_H

typedef int Rank;
#define DEFAULT_CAPACITY  3 
 
template <typename T> class Vector { 
protected:
   Rank _size; int _capacity;  T* _elem; 
   void copyFrom ( T const* A, Rank lo, Rank hi ); //������������A[lo, hi)
   void expand(); 
   void shrink(); //װ�����ӹ�Сʱѹ��

public:
// ���캯��
   Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) 
   { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } 
// ��������
   ~Vector() { delete [] _elem; } 
// ֻ�����ʽӿ�
   Rank size() const { return _size; }
// ��д���ʽӿ�
   T& operator[] ( Rank r ); //�����±������������������������ʽ���ø�Ԫ��
   const T& operator[] ( Rank r ) const; //����������ֵ�����ذ汾
   Vector<T> & operator= ( Vector<T> const& ); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
   T remove ( Rank r ); //ɾ����Ϊr��Ԫ��
   int remove ( Rank lo, Rank hi ); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
   Rank insert ( Rank r, T const& e ); 
   Rank insert ( T const& e ) { return insert ( _size, e ); } //Ĭ����ΪĩԪ�ز���
 
};

template <typename T> void Vector<T>::copyFrom ( T const* A, Rank lo, Rank hi ) { //����������A[lo, hi)Ϊ������������
   _elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //����ռ䣬��ģ����
   while ( lo < hi ) //A[lo, hi)�ڵ�Ԫ����һ
      _elem[_size++] = A[lo++]; //������_elem[0, hi - lo)
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

template <typename T> T& Vector<T>::operator[] ( Rank r ) //�����±������
{ return _elem[r]; } // assert: 0 <= r < _size 
template <typename T> const T& Vector<T>::operator[] ( Rank r ) const //����������ֵ
{ return _elem[r]; } // assert: 0 <= r < _size
template <typename T> Vector<T>& Vector<T>::operator= ( Vector<T> const& V ) { //���
   if ( _elem ) delete [] _elem; //�ͷ�ԭ������
   copyFrom ( V._elem, 0, V.size() ); //���帴��
   return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}

template <typename T> T Vector<T>::remove ( Rank r ) { //ɾ����������Ϊr��Ԫ�أ�0 <= r < size
   T e = _elem[r]; //���ݱ�ɾ��Ԫ��
   remove ( r, r + 1 ); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
   return e; //���ر�ɾ��Ԫ��
}
template <typename T> int Vector<T>::remove ( Rank lo, Rank hi ) { //ɾ������[lo, hi)
   if ( lo == hi ) return 0; //����Ч�ʿ��ǣ����������˻����������remove(0, 0)
   while ( hi < _size ) _elem[lo++] = _elem[hi++]; //[hi, _size)˳��ǰ��hi - lo����Ԫ
   _size = lo; //���¹�ģ��ֱ�Ӷ���β��[lo, _size = hi)����
   shrink(); //���б�Ҫ��������
   return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ
}
template <typename T> Rank Vector<T>::insert ( Rank r, T const& e ) { //assert: 0 <= r <= size
   expand(); //���б�Ҫ������
   for ( int i = _size; i > r; i-- ) _elem[i] = _elem[i-1]; //�Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
   _elem[r] = e; _size++; //������Ԫ�ز���������
   return r; //������
}

#endif