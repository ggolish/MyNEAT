from neatpy import NEAT, visualize
import numpy as np
import pygame
import sys
import random

xor_inputs = [[0, 0], [0, 1], [1, 0], [1, 1]]
xor_outputs = np.array([0, 1, 1, 0])


class XORVisualization():

    def __init__(self):
        pygame.display.init()
        self.width = 800
        self.height = 600
        self.window = pygame.display.set_mode((self.width, self.height))
        self.finished = False
        self.res = 40
        self.cols = self.width // self.res
        self.rows = self.height // self.res
        self.neat = NEAT(150, 2, 1)
        self.best = -1
        self.fitnesses = []
        self.best_found = False
        
    def mainloop(self):
        while not self.finished:
            self.process_input()
            if not self.best_found:
                self.update()
                self.draw()
                self.neat.repopulate(self.fitnesses)
        visualize.display_genome(self.neat[self.best])
        self.neat[self.best].summary()
        pygame.display.quit()

    def process_input(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.finished = True

    def update(self):
        global xor_inputs, xor_outputs
        outputs = np.array(self.neat.feed_forward_list(xor_inputs))
        self.fitnesses = np.square(4.0 - np.sum(np.abs(outputs - xor_outputs), axis=1))
        self.best = np.argmax(self.fitnesses)
        if self.fitnesses[self.best] > 15.0:
            self.res = 2
            self.cols = self.width // self.res
            self.rows = self.height // self.res
            self.best_found = True
        print(self.fitnesses[self.best])

    def draw(self):
        self.window.fill((0, 0, 0))

        for c in range(self.cols):
            for r in range(self.rows):
                x = int(self.neat.feed_forward(self.best, [c / self.cols, r / self.cols]) * 255)
                color = [x] * 3
                dims = (c * self.res, r * self.res, self.res, self.res)
                pygame.draw.rect(self.window, color, dims)

        pygame.display.flip()


if __name__ == "__main__":
    
    viz = XORVisualization()
    viz.mainloop()


