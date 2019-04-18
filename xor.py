import numpy as np
from neatpy import NEAT

xor_inputs = [[0, 0], [0, 1], [1, 0], [1, 1]]
xor_outputs = np.array([0, 1, 1, 0])

def evaluate_solution(index, neat):
    outputs = neat.feed_forward_list(xor_inputs, index=index)
    if outputs[0] < 0.5 and outputs[1] > 0.5 and outputs[2] > 0.5 and outputs[3] < 0.5:
        return True
    else:
        return False

def main():
    global xor_inputs, xor_outputs

    neat = NEAT(150, 2, 1)
    best = -1
    while True:
        outputs = np.array(neat.feed_forward_list(xor_inputs))
        fitnesses = np.square(4.0 - np.sum(np.abs(outputs - xor_outputs), axis=1))
        best = np.argmax(fitnesses)
        print(fitnesses[best])
        if evaluate_solution(best, neat) == True:
            break
        neat.repopulate(fitnesses)

if __name__ == "__main__":
    main()


