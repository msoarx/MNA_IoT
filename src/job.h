#ifndef JOB_H
#define JOB_H

#include <vector>

class Job {
public:
    int id;
    int origem;
    int jr;
    int jb;
    int jl;
    std::vector<int> distancias;

    Job(int id, int origem, int jr, int jb, int jl);
};

#endif