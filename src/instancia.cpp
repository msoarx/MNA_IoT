#include "instancia.h"

#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

Instancia carregarInstancia(const std::string& caminho)
{
    std::ifstream arquivo(caminho);

    if (!arquivo.is_open()) {
        throw std::runtime_error(
            "Não foi possível abrir o arquivo: " + caminho
        );
    }

    json dados;
    arquivo >> dados;


    // ler dos jobs

    std::vector<Job> jobs;

    const auto& jr = dados["jr"];
    const auto& jb = dados["jb"];
    const auto& jl = dados["jl"];
    const auto& jo = dados["jo"];

    int quantidadeJobs = jr.size();

    for (int i = 0; i < quantidadeJobs; i++) {

        jobs.emplace_back(
            i,
            jo[i],
            jr[i],
            jb[i],
            jl[i]
        );
    }


    // ler dos nós

    std::vector<int> edgeNodes =
        dados["edge_nodes"].get<std::vector<int>>();

    std::vector<int> vR =
        dados["V_R"].get<std::vector<int>>();

    std::vector<int> vB =
        dados["V_B"].get<std::vector<int>>();

    std::vector<int> vBusy =
        dados["V_Busy"].get<std::vector<int>>();

    std::vector<int> vInactive =
        dados["V_Inactive"].get<std::vector<int>>();

    
    // ler a lista de adj

    std::vector<std::vector<Aresta>> adjList;

    for (const auto& vizinhos : dados["adjList"]) {

        std::vector<Aresta> lista;

        for (const auto& aresta : vizinhos) {

            Aresta a;

            a.destino = aresta[0];
            a.latencia = aresta[1];

            lista.push_back(a);
        }

        adjList.push_back(lista);
    }

    
    // criar a rede

    Rede rede(
        edgeNodes,
        vR,
        vB,
        vBusy,
        vInactive,
        adjList
    );

    for (Job& job : jobs){
        job.distancias = rede.calcularDistancias(job.origem);
    }

    return Instancia{rede, jobs};
}