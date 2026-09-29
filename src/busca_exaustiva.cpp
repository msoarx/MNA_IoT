#include "busca_exaustiva.h"

// busca solucoes validas dado um job e uma rede
std::vector<Solucao> buscarSolucoesValidas(
    const Job& job,
    const Rede& rede
)
{
    std::vector<Solucao> solucoesValidas;

    const int quantidadeNos = rede.nos.size();
    const int quantidadeCombinacoes = 1 << quantidadeNos; // total de combinacoes: 2^n

    // tecnica bitmask para representar subconjuntos
    for (long long mascara = 1; mascara < (1LL << quantidadeNos); mascara++){
        std::vector<int> nos;

        int somaR = 0;
        int somaB = 0;
        int somaL = 0;

        bool valida = true;

        // monta a combinacao de nos
        for (int i = 0; i < quantidadeNos; i++){
            // verifica se i faz parte do subconjunto atual
            if (mascara & (1LL << i)){
                nos.push_back(i);

                somaR += rede.nos[i].R;
                somaB += rede.nos[i].B;
                somaL += job.distancias[i];

                if (rede.nos[i].busy != 0 ||
                    rede.nos[i].inactive != 0)
                {
                    valida = false;
                    break;
                }
            }
        }

        // descarta combinacoes invalidas
        if (!valida){
            continue;
        }

        // componentes da funcao objetivo OF
        const int FR = somaR - job.jr;
        const int FB = somaB - job.jb;

        const int tc = 1;

        const int FL = job.jl - tc - somaL;

        // restricoes de viabilidade
        if (FR < 0 ||
            FB < 0 ||
            FL < 0)
        {
            continue;
        }

        // funcao objetivo
        const double OF = FR * FR + FB * FB - FL;

        // armazena somente solucoes validas
        solucoesValidas.push_back({
            nos,
            job.id,
            OF
        });
    }

    return solucoesValidas;
}