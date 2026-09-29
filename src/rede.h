#ifndef REDE_H
#define REDE_H

#include <vector>

struct No {
    int id;
    int R;
    int B;
    bool busy;
    bool inactive;
};

struct Aresta {
    int destino;
    int latencia;
};

class Rede {
public:
    std::vector<No> nos;
    std::vector<int> edgeNodes;
    std::vector<std::vector<Aresta>> adjList;
    
    Rede(
        const std::vector<int>& edgeNodes,
        const std::vector<int>& vR,
        const std::vector<int>& vB,
        const std::vector<int>& vBusy,
        const std::vector<int>& vInactive,
        const std::vector<std::vector<Aresta>>& adjList
    );

    std::vector<int> calcularDistancias(int origem) const;
};



#endif