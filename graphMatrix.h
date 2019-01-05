//graphMatrix.h
#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H
#include "vector.h"
#include "queue.h"
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //����״̬
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //���ڱ�����������������
typedef enum {BLANK, RB_BLACK, RB_RED} RB_Color; //CCCCCCCCCCCC
#define NULL 0

template <typename Tv> struct Vertex { 
    Tv data; int inDegree, outDegree; VStatus status; RB_Color color;
    int dTime, fTime; 
    int parent; 
    Vertex ( Tv const& d = ( Tv ) 0 ) : 
       data ( d ), inDegree ( 0 ), outDegree ( 0 ), status ( UNDISCOVERED ), color( color ),
       dTime ( -1 ), fTime ( -1 ), parent ( -1 ) {}
 };

template <typename Te> struct Edge {
    Te data; EType type; 
    Edge ( Te const& d) : data ( d ), type ( UNDETERMINED ) {} 
 };

template <typename Tv, typename Te> class GraphMatrix{
private:
	Vector< Vertex< Tv > > V; 
    Vector< Vector< Edge< Te > * > > E;
	void reset() { //���ж��㡢�ߵĸ�����Ϣ��λ
       for ( int i = 0; i < n; i++ ) { //���ж����
          status ( i ) = UNDISCOVERED; dTime ( i ) = fTime ( i ) = -1; //״̬��ʱ���ǩ
          parent ( i ) = -1;  color ( i ) = BLANK; //���ڱ������еģ����ڵ㣬�߶�
          for ( int j = 0; j < n; j++ ) //���бߵ�
             if ( exists ( i, j ) ) type ( i, j ) = UNDETERMINED; //����
       }
    }
    void BFS ( int v, int& clock ); //����ͨ�򣩹�����������㷨

public:
	int n; //��������
	int e; //������
	GraphMatrix() { n = e = 0; } 
    ~GraphMatrix() { 
       for ( int j = 0; j < n; j++ ) 
          for ( int k = 0; k < n; k++ )
             delete E[j][k]; 
	}
// ����Ļ�����������ѯ��i�����㣨0 <= i < n��
	Tv& vertex ( int i ) { return V[i].data; } //����
    int inDegree ( int i ) { return V[i].inDegree; } //���
    int outDegree ( int i ) { return V[i].outDegree; } //����
    int firstNbr ( int i ) { return nextNbr ( i, n ); } //�׸��ڽӶ���
    int nextNbr ( int i, int j ) //����ڶ���j����һ�ڽӶ��㣨�����ڽӱ�����Ч�ʣ�
    { while ( ( -1 < j ) && ( !exists ( i, --j ) ) ); return j; } //����������̽
    VStatus& status ( int i ) { return V[i].status; } //״̬
    int& dTime ( int i ) { return V[i].dTime; } //ʱ���ǩdTime
    int& fTime ( int i ) { return V[i].fTime; } //ʱ���ǩfTime
    int& parent ( int i ) { return V[i].parent; } //�ڱ������еĸ���
	int& height ( int i ) { return V[i].height; } //�ڱ������еĸ߶�
	RB_Color& color ( int i ) { return V[i].color; } //CCCCCCCCCCCCC
// ����Ķ�̬����
    int insert ( Tv const& vertex ) { //���붥�㣬���ر��
       for ( int j = 0; j < n; j++ ) E[j].insert ( NULL ); n++; //������Ԥ��һ��Ǳ�ڵĹ�����
       E.insert ( Vector<Edge<Te>*> ( n, n, ( Edge<Te>* ) NULL ) ); //�����¶����Ӧ�ı�����
       return V.insert ( Vertex<Tv> ( vertex ) ); //������������һ������
    }
    Tv remove ( int i ) { //ɾ����i�����㼰������ߣ�0 <= i < n��
       for ( int j = 0; j < n; j++ ) //���г���
          if ( exists ( i, j ) ) { delete E[i][j]; V[j].inDegree--; } //����ɾ��
       E.remove ( i ); n--; //ɾ����i��
       Tv vBak = vertex ( i ); V.remove ( i ); //ɾ������i
       for ( int j = 0; j < n; j++ ) //�������
          if ( Edge<Te> * e = E[j].remove ( i ) ) { delete e; V[j].outDegree--; } //����ɾ��
       return vBak; //���ر�ɾ���������Ϣ
    }
// �ߵ�ȷ�ϲ���
    bool exists ( int i, int j ) //��(i, j)�Ƿ����
    { return ( 0 <= i ) && ( i < n ) && ( 0 <= j ) && ( j < n ) && E[i][j] != NULL; }
// �ߵĻ�����������ѯ����i��j֮������ߣ�0 <= i, j < n��exists(i, j)��
    EType & type ( int i, int j ) { return E[i][j]->type; } //��(i, j)������
    Te& edge ( int i, int j ) { return E[i][j]->data; } //��(i, j)������
// �ߵĶ�̬����
    void insert ( Te const& edge, int i, int j ) { 
       if ( exists ( i, j ) ) return; //ȷ���ñ��в�����
       E[i][j] = new Edge<Te> ( edge); //�����±�
	   e++; V[i].outDegree++; V[j].inDegree++; //���±߼������������Ķ���
    }
    Te remove ( int i, int j ) { //ɾ������i��j֮������ߣ�exists(i, j)��
       Te eBak = edge ( i, j ); delete E[i][j]; E[i][j] = NULL; //���ݺ�ɾ���߼�¼
       e--; V[i].outDegree--; V[j].inDegree--; //���±߼������������Ķ���
       return eBak; //���ر�ɾ���ߵ���Ϣ
    }
	// �㷨
	void bfs ( int s ); //������������㷨
	bool checkColor( int v ); // ��鶥����ɫ�Ƿ��ͻ
};

template <typename Tv, typename Te> //�����������BFS�㷨��ȫͼ��
void GraphMatrix<Tv, Te>::bfs ( int s ) { //assert: 0 <= s < n
   int clock = 0; int v = s; //��ʼ��
   BFS ( v, clock ); //���Ӹö����������һ��BFS
}

template <typename Tv, typename Te> //�����������BFS�㷨��������ͨ��
void GraphMatrix<Tv, Te>::BFS ( int v, int& clock ) { //assert: 0 <= v < n
   Queue<int> Q; //���븨������
   status ( v ) = DISCOVERED; 
   color (v) = RB_BLACK; //CCCCCCCCCCCCC
   Q.enqueue ( v ); //��ʼ�����
   while ( !Q.empty() ) { //��Q���֮ǰ������
      int v = Q.dequeue();  //ȡ�����׶���v
      for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //ö��v�������ھ�u
         if ( UNDISCOVERED == status ( u ) ) { //��u��δ�����֣���
            status ( u ) = DISCOVERED; 
			Q.enqueue ( u ); //���ָö���
            type ( v, u ) = TREE; 
			parent ( u ) = v; //����������չ֧����
			color ( u ) = ( color( v ) == RB_BLACK ) ? RB_RED : RB_BLACK; //CCCCCCCCCCCCCCCCCC
         } else { //��u�ѱ����֣����������ѷ�����ϣ���
            type ( v, u ) = CROSS; //��(v, u)�����ڿ��
         }
      status ( v ) = VISITED; //���ˣ���ǰ����������
   }
}

template <typename Tv, typename Te>
bool GraphMatrix<Tv, Te>::checkColor ( int v ){//����v�޶�Ϊ��������root
	Queue<int> Q;
	Q.enqueue(v);
	while ( !Q.empty() ) {
		int v = Q.dequeue();
		for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ){
			if ( CROSS == type ( u, v )  && color ( v ) == color( u ))
				return false;
			if ( v ==  parent( u ))  
				Q.enqueue(u);
		}	
	}
	return true;
}
#endif