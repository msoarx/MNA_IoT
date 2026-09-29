#ifndef INSTANCIA_H
#define INSTANCIA_H

#include "rede.h"
#include "job.h"
#include <vector>
#include <string>

struct Instancia {
    Rede rede;
    std::vector<Job> jobs;
};

Instancia carregarInstancia(const std::string& caminho);

#endif