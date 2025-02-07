import pygame
import copy
from itertools import product

from state import *

Color = pygame.Color


class PacInit:

    def create_map(self, print_info = False):
        self.create_physical_states()
        self.load_state_types()
        self.assign_properties()

        if print_info:
            self.print_info()


    #Create empty initial states
    def create_physical_states(self):
        OFFSET_X = self.map.OFFSET_X
        OFFSET_Y = self.map.OFFSET_Y
        BOX_SIZE = self.map.BOX_SIZE
        BORDER = self.map.BORDER
        for i in range (self.map.COLUMNS):
            for j in range (self.map.ROWS):
                if i == 0 and j == 0:
                    self.states.append(State(i, j, OFFSET_X, OFFSET_Y, BOX_SIZE))
                else:
                    self.states.append(State(i, j, OFFSET_X + i * BOX_SIZE - BORDER * i, 
                                            OFFSET_Y + j * BOX_SIZE  - BORDER * j, BOX_SIZE))
        
    #Load physical information
    def load_state_types(self):
        file_name = "maps/" + self.map.name
        f = open(file_name, "r")
        lines = f.readlines()

        i = 0
        for line in lines:
            numbers = [int(e) for e in line.split()]
            for j in range (self.map.COLUMNS):
                self.states[i + j * self.map.ROWS].type = numbers[j]
            i += 1
        f.close()
                
    #Assign physical state properties for all states
    def assign_properties(self):
        for state in self.states:
            self.assign_property(state)

    #Assign physical state properties based on type
    def assign_property(self, state):
        match state.type:
            case 0: #EMPTY
                state.fill = False
                state.color = Color(0, 0, 0)
            case 1: #WALL
                state.blocked = True
                state.fill = True
                state.color = Color(211, 211, 211)
            case 2: #PELLET
                state.fill = True
                state.color = Color(253, 184, 155)
            case 3: #ENERGIZER
                state.fill = True
                state.color = Color(255, 132, 102)

    #Display grid coordinates and info
    def print_info(self):
        for state in self.states:
            print(state)

        for i in range(self.map.ROWS):
            for j in range(self.map.COLUMNS):
                print("(%s,%s) " % (j, i), end='')
            print()