#ifndef BUSCA_EXAUSTIVA_H
#define BUSCA_EXAUSTIVA_H

#include <vector>

#include "job.h"
#include "rede.h"

struct Solucao
{
    std::vector<int> nos;
    int jobAtendido;
    double OF;
};

std::vector<Solucao> buscarSolucoesValidas(
    const Job& job,
    const Rede& rede
);

#endif