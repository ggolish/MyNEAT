%module neat_backend

%{
#include "include/Node.h"
#include "include/Connection.h"
#include "include/Genome.h"
#include "include/NEAT.h"
%}

%include "std_string.i"
%include "std_vector.i"

namespace std {
    %template(GenomeVector) vector<Genome *>;
    %template(NodeVector) vector<Node *>;
    %template(ConnectionVector) vector<Connection *>;
    %template(DoubleVector) vector<double>;
    %template(DoubleDoubleVector) vector<vector<double>>;
}

%include "include/Node.h"
%include "include/Connection.h"
%include "include/Genome.h"
%include "include/NEAT.h"

