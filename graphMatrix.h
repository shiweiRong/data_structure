//graphMatrix.h
#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H
#include "vector.h"
#include "queue.h"
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //边在遍历树中所属的类型
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
	void reset() { //所有顶点、边的辅助信息复位
       for ( int i = 0; i < n; i++ ) { //所有顶点的
          status ( i ) = UNDISCOVERED; dTime ( i ) = fTime ( i ) = -1; //状态，时间标签
          parent ( i ) = -1;  color ( i ) = BLANK; //（在遍历树中的）父节点，高度
          for ( int j = 0; j < n; j++ ) //所有边的
             if ( exists ( i, j ) ) type ( i, j ) = UNDETERMINED; //类型
       }
    }
    void BFS ( int v, int& clock ); //（连通域）广度优先搜索算法

public:
	int n; //顶点总数
	int e; //边总数
	GraphMatrix() { n = e = 0; } 
    ~GraphMatrix() { 
       for ( int j = 0; j < n; j++ ) 
          for ( int k = 0; k < n; k++ )
             delete E[j][k]; 
	}
// 顶点的基本操作：查询第i个顶点（0 <= i < n）
	Tv& vertex ( int i ) { return V[i].data; } //数据
    int inDegree ( int i ) { return V[i].inDegree; } //入度
    int outDegree ( int i ) { return V[i].outDegree; } //出度
    int firstNbr ( int i ) { return nextNbr ( i, n ); } //首个邻接顶点
    int nextNbr ( int i, int j ) //相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
    { while ( ( -1 < j ) && ( !exists ( i, --j ) ) ); return j; } //逆向线性试探
    VStatus& status ( int i ) { return V[i].status; } //状态
    int& dTime ( int i ) { return V[i].dTime; } //时间标签dTime
    int& fTime ( int i ) { return V[i].fTime; } //时间标签fTime
    int& parent ( int i ) { return V[i].parent; } //在遍历树中的父亲
	int& height ( int i ) { return V[i].height; } //在遍历树中的高度
	RB_Color& color ( int i ) { return V[i].color; } //CCCCCCCCCCCCC
// 顶点的动态操作
    int insert ( Tv const& vertex ) { //插入顶点，返回编号
       for ( int j = 0; j < n; j++ ) E[j].insert ( NULL ); n++; //各顶点预留一条潜在的关联边
       E.insert ( Vector<Edge<Te>*> ( n, n, ( Edge<Te>* ) NULL ) ); //创建新顶点对应的边向量
       return V.insert ( Vertex<Tv> ( vertex ) ); //顶点向量增加一个顶点
    }
    Tv remove ( int i ) { //删除第i个顶点及其关联边（0 <= i < n）
       for ( int j = 0; j < n; j++ ) //所有出边
          if ( exists ( i, j ) ) { delete E[i][j]; V[j].inDegree--; } //逐条删除
       E.remove ( i ); n--; //删除第i行
       Tv vBak = vertex ( i ); V.remove ( i ); //删除顶点i
       for ( int j = 0; j < n; j++ ) //所有入边
          if ( Edge<Te> * e = E[j].remove ( i ) ) { delete e; V[j].outDegree--; } //逐条删除
       return vBak; //返回被删除顶点的信息
    }
// 边的确认操作
    bool exists ( int i, int j ) //边(i, j)是否存在
    { return ( 0 <= i ) && ( i < n ) && ( 0 <= j ) && ( j < n ) && E[i][j] != NULL; }
// 边的基本操作：查询顶点i与j之间的联边（0 <= i, j < n且exists(i, j)）
    EType & type ( int i, int j ) { return E[i][j]->type; } //边(i, j)的类型
    Te& edge ( int i, int j ) { return E[i][j]->data; } //边(i, j)的数据
// 边的动态操作
    void insert ( Te const& edge, int i, int j ) { 
       if ( exists ( i, j ) ) return; //确保该边尚不存在
       E[i][j] = new Edge<Te> ( edge); //创建新边
	   e++; V[i].outDegree++; V[j].inDegree++; //更新边计数与关联顶点的度数
    }
    Te remove ( int i, int j ) { //删除顶点i和j之间的联边（exists(i, j)）
       Te eBak = edge ( i, j ); delete E[i][j]; E[i][j] = NULL; //备份后删除边记录
       e--; V[i].outDegree--; V[j].inDegree--; //更新边计数与关联顶点的度数
       return eBak; //返回被删除边的信息
    }
	// 算法
	void bfs ( int s ); //广度优先搜索算法
	bool checkColor( int v ); // 检查顶点颜色是否冲突
};

template <typename Tv, typename Te> //广度优先搜索BFS算法（全图）
void GraphMatrix<Tv, Te>::bfs ( int s ) { //assert: 0 <= s < n
   int clock = 0; int v = s; //初始化
   BFS ( v, clock ); //即从该顶点出发启动一次BFS
}

template <typename Tv, typename Te> //广度优先搜索BFS算法（单个连通域）
void GraphMatrix<Tv, Te>::BFS ( int v, int& clock ) { //assert: 0 <= v < n
   Queue<int> Q; //引入辅助队列
   status ( v ) = DISCOVERED; 
   color (v) = RB_BLACK; //CCCCCCCCCCCCC
   Q.enqueue ( v ); //初始化起点
   while ( !Q.empty() ) { //在Q变空之前，不断
      int v = Q.dequeue();  //取出队首顶点v
      for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //枚举v的所有邻居u
         if ( UNDISCOVERED == status ( u ) ) { //若u尚未被发现，则
            status ( u ) = DISCOVERED; 
			Q.enqueue ( u ); //发现该顶点
            type ( v, u ) = TREE; 
			parent ( u ) = v; //引入树边拓展支撑树
			color ( u ) = ( color( v ) == RB_BLACK ) ? RB_RED : RB_BLACK; //CCCCCCCCCCCCCCCCCC
         } else { //若u已被发现，或者甚至已访问完毕，则
            type ( v, u ) = CROSS; //将(v, u)归类于跨边
         }
      status ( v ) = VISITED; //至此，当前顶点访问完毕
   }
}

template <typename Tv, typename Te>
bool GraphMatrix<Tv, Te>::checkColor ( int v ){//顶点v限定为搜索树的root
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