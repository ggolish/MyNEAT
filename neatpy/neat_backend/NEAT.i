%module NEAT

%{
#include "include/NEAT.h"
%}

%include "std_vector.i"

namespace std {
    %template(GenomeVector) vector<Genome *>;
    %template(DoubleVector) vector<double>;
    %template(DoubleDoubleVector) vector<vector<double>>;
}

%include "include/NEAT.h"
