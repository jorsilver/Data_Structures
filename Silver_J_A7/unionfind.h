#ifndef UNIONFIND_H
#define UNIONFIND_H

class UnionFind {
    int *id, *sz;
    int cnt;

    int find(int p) {
        int root = p;

        while (root != id[root])
            root = id[root];

        while (p != root) {
            int newp = id[p];
            id[p] = root;
            p = newp;
        }

        return root;
    }


public:
    UnionFind(int N) {
        cnt = N;
        id = new int[N];
        sz = new int[N];
        for (int i = 0; i<N; i++)
            id[i] = i, sz[i] = 1;
    }

    ~UnionFind() { delete[] id; delete[] sz; }

    void connect(int x, int y) {
        int i = find(x), j = find(y);
        if (i == j) return;

        // make smaller root, point to larger one
        if (sz[i] < sz[j]) {
            id[i] = j, sz[j] += sz[i];
        } else {
            id[j] = i, sz[i] += sz[j];
        } cnt--;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
};

#endif // UNIONFIND_H
