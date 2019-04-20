%module neat_backend

%{
#include "include/Genome.h"
#include "include/NEAT.h"
%}

%include "std_vector.i"

namespace std {
    %template(GenomeVector) vector<Genome *>;
    %template(NodeVector) vector<Node *>;
    %template(ConnectionVector) vector<Connection *>;
    %template(DoubleVector) vector<double>;
    %template(DoubleDoubleVector) vector<vector<double>>;
}

%include "include/Genome.h"
%include "include/NEAT.h"

