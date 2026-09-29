#include "rede.h"
#include <queue>
#include <limits>
using namespace std;

// construtor de rede
Rede::Rede(
    const vector<int>& edgeNodes,
    const vector<int>& vR,
    const vector<int>& vB,
    const vector<int>& vBusy,
    const vector<int>& vInactive,
    const vector<vector<Aresta>>& adjList
)
    : edgeNodes(edgeNodes),
      adjList(adjList)
{
    int quantidadeNos = vR.size();

    nos.reserve(quantidadeNos);

    for (int i = 0; i < quantidadeNos; i++) {
        No no;

        no.id = i;
        no.R = vR[i];
        no.B = vB[i];
        no.busy = (vBusy[i] != 0);
        no.inactive = (vInactive[i] != 0);

        nos.push_back(no);
    }
}

// calcula distancias entre uma origem qualquer (atualmente um Job) e um nó utilizando Dijkstra
vector<int> Rede::calcularDistancias(int origem) const
{
    const int INF = numeric_limits<int>::max();

    vector<int> dist(nos.size(), INF);

    using Par = pair<int, int>;
    priority_queue<
        Par,
        vector<Par>,
        greater<Par>
    > fila;

    dist[origem] = 0;
    fila.push({0, origem});

    while (!fila.empty()) {

        int distanciaAtual = fila.top().first;
        int noAtual = fila.top().second;

        fila.pop();

        if (distanciaAtual > dist[noAtual])
            continue;

        for (const Aresta& aresta : adjList[noAtual]) {

            int vizinho = aresta.destino;
            int novaDistancia =
                distanciaAtual + aresta.latencia;

            if (novaDistancia < dist[vizinho]) {

                dist[vizinho] = novaDistancia;

                fila.push({
                    novaDistancia,
                    vizinho
                });
            }
        }
    }

    return dist;
}