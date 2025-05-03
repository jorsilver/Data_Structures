#include "WGraph.h"

WGraph::WGraph(){
    m_size = 0;
    m_adj = NULL;
    m_conn = NULL;
}

WGraph::WGraph(unsigned int sz){
    m_size = sz;
    //allocate sz * sz adj matrix
    m_adj = new double*[sz];
    m_conn = new double*[sz];
    for(uint i = 0; i < m_size; ++i){
        m_adj[i] = new double[sz];
        m_conn[i] = new double[sz];
    }
    //start with edges
    for(uint i = 0; i < m_size; ++i){
        for(uint j = 0; j < m_size; ++j){
            m_adj[i][j] = std::numeric_limits<double>::max(); //essentially infinity
            m_conn[i][j] = std::numeric_limits<double>::max();
        }
    }
}

WGraph::~WGraph(){
    delete [] m_adj;
    delete [] m_conn;
}

void WGraph::addEdge(VertexID i, VertexID j, double w){
    if(i < m_size && j < m_size){
        m_adj[i][j] = w;
        m_adj[j][i] = w;
    }
}

void WGraph::removeEdge(VertexID i, VertexID j){
    if(i < m_size && j < m_size){
        m_adj[i][j] = std::numeric_limits<double>::max();
        m_adj[j][i] = std::numeric_limits<double>::max();
    }
}

bool WGraph::areAdjacent(VertexID i, VertexID j){
    return (m_adj[i][j] < std::numeric_limits<double>::max());
}


void WGraph::calcFW(){ //runtime complexity O(v^3)
    for(uint i = 0; i < m_size; ++i){
        for(uint j = 0; j < m_size; ++j){
            m_conn[i][j] = m_adj[i][j]; //start with conn == adj matrix
        }
    }
    for(uint im = 0; im < m_size; ++ im){ //intermediate points --> transitive closure
        for(uint source = 0; source < m_size; ++source){ //source = starting point
            for(uint sink = 0; sink <m_size; ++sink){ //sink = ending point
                if(source == sink){
                    continue;
                }else if(m_conn[source][im] != std::numeric_limits<double>::max() &&
                         m_conn[im][sink] != std::numeric_limits<double>::max() &&
                         m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink]){
                    m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink];
                }
            }
        }
    }
}

void WGraph::computeMST()
{
    UnionFind uf(m_size * m_size);
    PriorityQueue pq(m_size * m_size);

    for(uint i=0; i<m_size; ++i) {
        for(uint j=0; j<m_size; ++j) {
            if(areAdjacent(i, j)) {
                t edge(i, j, m_adj[i][j]);
                pq.put(edge);
            }
        }
    }

    uint mst = 0;
    bool adj[m_size][m_size];
    memset(adj, 0, m_size*m_size);
    double cost = 0.0;
    while (!pq.empty() and mst<=m_size) {
        auto e = pq.get();
        int u = e.u, v = e.v;
        double w = e.w;
        if(!uf.connected(u, v)) {
            uf.connect(u, v);
            adj[u][v] = 1;
            cost += w;
            ++mst;
        }
    }

    std::cout << "MST cost: " << cost << std::endl;

    for(uint i=0; i<m_size; ++i) {
        for(uint j=0; j<m_size; ++j) {
            if(adj[i][j]) {
                std::cout << m_adj[i][j] << "\t";
            } else {
                std::cout << 0 << "\t";
            }
        }

        std::cout << std::endl;
    }
}

double WGraph::cheapestCost(VertexID i, VertexID j){
    return m_conn[i][j]; //constant
}

