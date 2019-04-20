from . import neat_backend

class Genome():

    def __init__(self, genome=None, ninputs=0, noutputs=0):
        if genome == None:
            self.genome = neat_backend.Genome(ninputs, noutputs)
        else:
            self.genome = genome

    def summary(self):
        self.genome.summary()
