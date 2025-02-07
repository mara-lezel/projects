import random

from state import *
from pacman_init import *
from pacman_get import *
from pacman_action import *


class PacGrid(PacInit, PacGet, PacAction):
    def __init__(self, map):
        #Map specific
        self.map = map

        #MDP core
        self.NUM_A = 4
        self.GAMMA = 0.99

        self.EPSILON = 0.05
        self.min_EPSILON = 0.0001
        self.decay_rate_epsilon = 0.999
        

        self.alpha = 0.0002
        self.min_alpha = 0.00005
        self.decay_rate = 0.999

        self.use_epsilon_decay = True
        self.use_alpha_decay = True

        #Game
        self.consumed_pellets = 0
        self.consumed_energizers = 0
        self.energizer_consumed = False

        self.states = []
        self.create_map()

    #Legal actions
    def get_legal_actions(self, s):
        legal = []
        for a in range (self.NUM_A):
            next_id = self.get_next_state_id(s, a)
            if next_id != s.id:
                legal.append(a)
        return legal
        
            
    #Epsilon greedy -- if -1, then it is NOT random
    def epsilon_greedy(self, s):
        if random.uniform(0, 1) < self.EPSILON:
            legal = self.get_legal_actions(s)
            return random.choice(legal)
            return random.randint(0, 3)
        return -1
    
    #Decay learning rate (if enabled)
    def decay_a(self):
        if self.use_alpha_decay and self.alpha > self.min_alpha:
            self.alpha *= self.decay_rate

    #Decay exploeation rate (if enabled)
    def decay_epsilon(self):
        if self.use_epsilon_decay and self.EPSILON > self.min_EPSILON:
            self.EPSILON *= self.decay_rate_epsilon

    #For plotting
    def get_epsilon_alpha(self):
        return (self.EPSILON, self.min_EPSILON, self.decay_rate_epsilon), (self.alpha, self.min_alpha, self.decay_rate)

    #For shortest path
    def get_legal_neighbours(self, state_id):
        nbrs = []
        for a in range (self.NUM_A):
            next_id = self.get_next_state_id(self.states[state_id], a)
            if next_id != state_id:
                nbrs.append(next_id)
        return nbrs

    #Remove pellet from physical state
    def consume_pellet(self, state):
        if state.has_pellet():
            state.type = 0
            self.assign_property(state)
            self.consumed_pellets += 1

        if state.has_energizer():
            state.type = 0
            self.assign_property(state)
            self.consumed_energizers += 1
            self.energizer_consumed = True

    #Reset physical states
    def reset(self):
        self.consumed_pellets = 0
        self.consumed_energizers = 0
        self.load_state_types()
        self.assign_properties()

    #Return reward based on next state
    def r(self, next_state_id = 0, ghosts = []):

        for ghost in ghosts:
            if self.states[next_state_id].id == ghost.next_state.id:
                if ghost.frightened:
                    return self.normalize(200)
                return self.normalize(-500)
            
        match self.states[next_state_id].type:
            case 0: #EMPTY
                return self.normalize(-1)
            case 1: #WALL
                return self.normalize(-1)
            case 2: #PELLET
                if self.consumed_pellets + 1 == self.map.total_pellets:
                    return self.normalize(500)
                return self.normalize(10)
            case 3: #ENERGIZER
                return self.normalize(20)
            

    def normalize(self, r):
        return r
        max_r = 500
        min_r = -500
        return 2 * ((r - min_r) / (max_r - min_r)) - 1 