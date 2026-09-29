#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

#include "instancia.h"
#include "busca_exaustiva.h"

int main()
{

    std::cout << std::fixed << std::setprecision(0);

    // leitura do arquivo json para criacao da rede e dos jobs

    Instancia instancia = carregarInstancia("dados/input_6nds_2jobs.json");

    std::cout << "Instancia carregada!\n";
    std::cout << "Jobs: " << instancia.jobs.size() << "\n";
    std::cout << "Nos: " << instancia.rede.nos.size() << "\n\n";

    for (const Job& job : instancia.jobs)
    {
        std::cout << "Job " << job.id
                << " - distancias: "
                << job.distancias.size()
                << "\n";
    }

    // inicia medicao do tempo

    auto inicio = std::chrono::high_resolution_clock::now();

    // solucao de cada Job

    std::vector<Solucao> melhoresSolucoes;

    for (Job& job : instancia.jobs){
        std::cout << "====================================\n";
        std::cout << "Job " << job.id << "\n";
        std::cout << "====================================\n";

        // busca todas as solucoes validas
        std::vector<Solucao> solucoesValidas =
            buscarSolucoesValidas(
                job,
                instancia.rede
            );

        std::cout << "Solucoes validas: "
                  << solucoesValidas.size()
                  << "\n";


        // verifica se existe alguma solucao

        if (solucoesValidas.empty()){
            std::cout << "Nenhuma solucao valida encontrada.\n\n";
            continue;
        }


        // encontra a menor OF

        Solucao melhor = solucoesValidas[0];

        for (const Solucao& solucao : solucoesValidas){
            if (solucao.OF < melhor.OF){
                melhor = solucao;
            }
        }


        // guarda a melhor solucao
        melhoresSolucoes.push_back(melhor);


        // reserva os nos utilizados pelo Job

        for (int no : melhor.nos){
            instancia.rede.nos[no].busy = 1;
        }


        // imprime resultado

        std::cout << "Melhor solucao:\n";

        std::cout << "Nos: ";

        for (int no : melhor.nos){
            std::cout << no << " ";
        }

        std::cout << "\n";

        std::cout << "OF: "
                  << melhor.OF
                  << "\n\n";
    }


    // finaliza medicao do tempo
    auto fim = std::chrono::high_resolution_clock::now();

    auto tempo =
        std::chrono::duration_cast<
            std::chrono::microseconds
        >(fim - inicio);


    // resultado final

    std::cout << "====================================\n";
    std::cout << "RESULTADO FINAL\n";
    std::cout << "====================================\n";

    for (const Solucao& solucao : melhoresSolucoes){
        std::cout << "Job "
                  << solucao.jobAtendido
                  << ": ";

        std::cout << "Nos = ";

        for (int no : solucao.nos){
            std::cout << no << " ";
        }

        std::cout << "| OF = "
                  << solucao.OF
                  << "\n";
    }

    std::cout << "\nTempo de execucao: "
              << tempo.count()
              << " us\n";

    std::cout << "Tempo de execucao: "
              << tempo.count() / 1000.0
              << " ms\n";

    return 0;
}