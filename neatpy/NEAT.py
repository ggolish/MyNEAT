from . import neat_backend

class NEAT():

    def __init__(self, population_size, ninputs, noutputs):
        self.population_size = population_size
        self.ninputs = ninputs
        self.noutputs = noutputs
        self.neat = neat_backend.NEAT(population_size, ninputs, noutputs)

    def feed_forward(self, index, inputs):
        inputs_vector = neat_backend.DoubleVector(len(inputs))
        for i in range(len(inputs)):
            inputs_vector[i] = inputs[i]
        output = self.neat.feed_forward(index, inputs_vector)
        return output[0] if self.noutputs == 1 else output

    def feed_forward_all(self, inputs):
        inputs_vector = neat_backend.DoubleVector(len(inputs))
        for i in range(len(inputs)):
            inputs_vector[i] = inputs[i]
        outputs = self.neat.feed_forward_all(inputs_vector)
        if self.noutputs == 1:
            return tuple(output[0] for output in outputs)
        else:
            return outputs

    def feed_forward_list(self, inputs_list, index=-1):
        if index == -1:
            outputs_list = [self.feed_forward_all(inputs) for inputs in inputs_list]
            return tuple(zip(*outputs_list))
        else:
            return tuple(self.feed_forward(int(index), inputs) for inputs in inputs_list)

    def repopulate(self, fitnesses):
        fitnesses_vector = neat_backend.DoubleVector(len(fitnesses))
        for i in range(len(fitnesses)):
            fitnesses_vector[i] = fitnesses[i]
        self.neat.repopulate(fitnesses_vector)

