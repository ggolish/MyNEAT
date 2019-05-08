from neatpy import NEAT, visualize
import numpy as np
import random
import sys

xor_inputs = [[0, 0], [0, 1], [1, 0], [1, 1]]
xor_outputs = np.array([0, 1, 1, 0])

def evaluate_outputs(outputs):
    x = np.abs(outputs - xor_outputs)
    return (np.sum(x < 0.5) == 4)

def randomize_xor():
    global xor_inputs, xor_outputs
    li = list(zip(xor_inputs, xor_outputs.tolist()))
    random.shuffle(li)
    xor_inputs, xor_outputs = zip(*li)
    xor_outputs = np.array(xor_outputs)

def xor_trained_neat():
    neat = NEAT(150, 2, 1)
    best = None
    fitnesses = None
    generation = 1
    while True:
        outputs = np.array(neat.feed_forward_list(xor_inputs))
        fitnesses = np.square(4.0 - np.sum(np.abs(outputs - xor_outputs), axis=1))
        best = np.argmax(fitnesses)
        if evaluate_outputs(outputs[best]):
            break
        neat.repopulate(fitnesses)
        randomize_xor()
        generation += 1
    return neat, generation, best, fitnesses[best]

if __name__ == "__main__":

    trials = int(sys.argv[1]) if len(sys.argv) > 1 else 50
    avg_generations = 0
    trial = 1
    for i in range(trials):
        neat, generation, best, fitness = xor_trained_neat()
        visualize.genome_to_png(neat[best], "results/trial{:03d}".format(trial), caption="Trial {}, Generation {}".format(trial, generation))
        avg_generations += generation
        trial += 1

    print("Average generations over {} trials: {}".format(trials, avg_generations / trials))
         
