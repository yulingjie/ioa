#ifndef __VERTEX_H__
#define __VERTEX_H__
#include <climits>
#include <vector>
#include <queue>
#include <stack>
typedef enum {UNDISCOVERED, DISCOVERED, VISITED} VStatus;
template <typename Tv>
struct Vertex{
    Tv data;
    int inDegree;
    int outDegree;
    VStatus status;
    int dTime;
    int fTime;
    int parent;
    int priority;
    Vertex(Tv const& d):
        data(d),inDegree(0), outDegree(0), status(UNDISCOVERED),
        dTime(-1), fTime(-1), parent(-1), priority(INT_MAX)
    {}

};
typedef enum {UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} EType;
template <typename Te> 
struct Edge{
    Te data;
    int weight;
    EType type;
    Edge(Te const& d, int w):
        data(d), weight(w), type(UNDETERMINED){}
};
template <typename Tv, typename Te>
class Graph;
template <typename Tv, typename Te>
struct PrimPU
{

    virtual void operator()( Graph<Tv, Te>* g,int uk, int v)
    {
        if(UNDISCOVERED != g->status(v)) return;
        if(g->priority(v) > g->weight(uk, v))
        {
            g->priority(v) = g->weight(uk, v);
            g->parent(v) = uk;
        }
    }
};
template <typename Tv, typename Te>
struct DijkstraPU{
    virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
    {
        if(UNDISCOVERED != g->status(v)) return ;
        if(g->priority(v) > g->weight(uk,v) + g->priority(uk))
        {
            g->priority(v) = g->weight(uk,v) + g->priority(uk);
            g->parent(v) = uk;
        }
    }
};

template <typename Tv, typename Te>
class Graph{
    protected:
    protected:
        
        virtual int & dTime(int i) =0;
        virtual VStatus & status(int i) = 0;

        virtual int firstNbr(int i )= 0;
        virtual int nextNbr(int i, int j) = 0;
        virtual EType & type(int i, int j) = 0;
        virtual int & parent(int i ) = 0;
        virtual bool exists(int i, int j) = 0;
        virtual int & priority(int i) = 0;
        virtual int & fTime(int i)  = 0;

        virtual int vertexNum() = 0;
        virtual int edgeNum() = 0;
        virtual Tv& vertex(int v);

    private:
        void reset()
        {
            for(int i = 0; i < vertexNum(); ++i)
            {
                status(i) = UNDISCOVERED;
                dTime(i) = fTime(i) = -1;
                parent(i) = -1;
                priority(i) = INT_MAX;
                for (int j =0; j < vertexNum(); ++j)
                {
                    if(exists(i,j)) type(i,j) = UNDETERMINED;
                }
            }
        }
        void DFS(int v, int & clock)
        {
            dTime(v) = ++clock;
            status(v) = DISCOVERED;
            for(int u = firstNbr(v); -1 <u; u = nextNbr(v, u))
            {
                switch(status(u))
                {
                    case UNDISCOVERED:
                        {
                            type(v,u) = TREE;
                            parent(u) = v;
                            DFS(u,clock);
                            break;
                        }
                    case DISCOVERED:
                        {
                            type(v,u) =BACKWARD;
                            break;
                        }
                    default:
                        {
                            type(v,u) = dTime(v) < dTime(u)? FORWARD : CROSS;
                            break;
                        }
                }
            }
            status(v) = VISITED;
            fTime(v) = ++clock;
        }
 
        void BFS(int v, int & clock)
        {
            std::queue<int> Q;
            status(v) = DISCOVERED;
            Q.push(v);
            while(! Q.empty()){
                int v =Q.front();
                Q.pop();
                dTime(v) = ++clock; 
                for(int u = firstNbr(v); -1 < u; u = nextNbr(v,u))
                {
                    if(UNDISCOVERED == status(u))
                    {
                        status(u) = DISCOVERED;
                        Q.push(u);
                        type(v,u) = TREE;
                       parent(u) = v; 
                    }
                    else
                    {
                        type(v,u) = CROSS;
                    }
                }
                status(v) = VISITED;
            }
        }
    public:
        void bfs(int s) // s 为起始顶点
        {
            reset();
            int clock = 0;
            int v = s;
            do{
                if (UNDISCOVERED == status(v))
                {
                    BFS(v,clock);
                }
            }
            while(s != (v = (++v% vertexNum())));
        }
        void dfs(int s)
        {
            reset();
            int clock = 0;
            int v= s;
            do
            {
                if (UNDISCOVERED == status(v)) 
                {
                    DFS(v,clock);
                }
            }
            while(s != (v= (++v%vertexNum())));
        }
        bool TSort(int v,int & clock, std::stack<Tv>* S){
            dTime(v) = ++clock;
            status(v)  = DISCOVERED;
            for (int u = firstNbr(v); -1 <u; u = nextNbr(v,u))
            {
                switch (status(u)){
                    case UNDISCOVERED:
                        {
                            parent(u) =v;
                            type(v,u) = TREE;
                            if(!TSort(u, clock, S)) return false;
                            break;
                        }
                    case DISCOVERED:
                        {
                            type(v,u) = BACKWARD;
                            return false;
                        }
                    default:
                        type(v,u) = dTime(v) < dTime(u) ? FORWARD :CROSS; break;
                }
            }
            status(v) = VISITED;
            S->push(vertex(v));

        }
        template <typename PU>
        void pfs(int s, PU prioUpdater)
        {
            priority(s) = 0;
            status(s) = VISITED;
            parent(s) = -1;
            while(1)
            {
                for(int w = firstNbr(s); -1 <w;w = nextNbr(s, w))
                {
                    prioUpdater(this, s, w);
                }
                for (int shortest  = INT_MAX, w= 0; w < vertexNum(); ++w)
                {
                    if(UNDISCOVERED == status(w))
                    {
                        if(shortest > priority(w))
                        {
                            shortest = priority(w);
                            s = w;
                        }
                    }
                }
                if(VISITED == status(s)) break;
                status(s)  = VISITED ;
                type(parent(s),s)  = TREE;

            }// while
        }
        void Prim()
        {
            pfs(0, PrimPU<Tv, Te>());
        }
        void Dijkstra()
        {
            pfs(0, DijkstraPU<Tv,Te>());
        }

};

template <typename Tv, typename Te>
class GraphMatrix: public Graph<Tv, Te>
{
    private:
        std::vector<Vertex<Tv> > V;
        std::vector<std::vector< Edge<Te>* > > E;
        int n; // 定点数
        int e; // 边数

    protected:
        int vertexNum(){return n;}
        int edgeNum(){return e;}

    public:
        GraphMatrix()
            :n(0),
            e(0)
    {
    }
        ~GraphMatrix(){
            for(int j = 0; j < n; ++j)
            {
                for(int k =0; k < n; ++k)
                {
                    delete E[j][k];
                }
            }
        }
        Tv& vertex(int i) {return V[i].data;}
        int inDegree(int i) {return V[i].inDegree;}
        int outDegree(int i) {return V[i].outDegree;}
        VStatus & status(int i) { return V[i].status;}
        int & dTime(int i) { return V[i].dTime;}
        int & fTime(int i) { return V[i].fTime;}
        int & parent(int i ){return V[i].parent;}
        int & priority(int i) {return V[i].priority;}

        bool exists(int i, int j){
            return (0 <= i) && (i < n) && (0 <= j) && (j < n)
                && E[i][j] != NULL;
        }
        int nextNbr(int i, int j){
            while( (-1 < j) && ! exists(i, --j));
            return j;
        }
        int firstNbr(int i )
        {
            return nextNbr(i, n);
        }

        Te & edge (int i, int j)
        {
            return E[i][j]->data;
        }
        EType & type(int i, int j)
        {
            return E[i][j]->type;
        }
        int & weight(int i, int j)
        {
            return E[i][j]->weight;
        }

        void insert(Te const & edge, int w, int i, int j)
        {
            if( exists(i,j)) return;
            E[i][j] = new Edge<Te>(edge, w);
            e ++;
            V[i].outDegree ++;
            V[j].inDegree ++;
        }
        Te remove(int i, int j)
        {
            Te eBak = edge(i,j);
            delete E[i][j];
            E[i][j] = NULL;
            e--;
            V[i].outDegree --;
            V[j].inDegree --;
            return eBak;
        }
        int insert(Tv const & vertex)
        {
            for (int j =0;j < n;++j)
            {
                E[j].push_back(NULL);
            }
            n ++;
            E.push_back(std::vector<Edge<Te>* >(n,NULL));
            return V.insert(Vertex<Tv> (vertex));
        }
        Tv remove(int i)
        {
            for (int j = 0; j < n; ++j)
            {
                if(exists(i,j)) 
                {
                    delete E[i][j];
                    V[j].inDegree --;
                }
            }
            E.erase(E.cbegin() + i);
            Tv vBak = vertex(i);
            V.erase(V.cbegin() + i);
            for (int j = 0; j < n; ++j)
            {
                Edge<Te> *e = E[j][i];
                if(e != NULL)
                {
                    E[j].erase(E[j].cbegin() + i);
                    delete e;
                    V[j].outDegree --;
                }
            }
        }


};
#endif
