# IC_IoT

Implementação de algoritmos para alocação de jobs em redes IoT.

## Estrutura

- `src/` - código-fonte
- `dados/` - instâncias utilizadas nos testes
- `resultados/` - resultados dos experimentos

## Algoritmos

Atualmente implementado:

- Busca Exaustiva

Posteriormente:

- DI-MNA

## Compilação

O projeto utiliza C++17.

```bash
g++ -std=c++17 src/main.cpp src/instancia.cpp src/rede.cpp src/job.cpp src/busca_exaustiva.cpp src/utils.cpp -o programa.exe