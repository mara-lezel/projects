import random

from state import *
from pacman_init import *
from pacman_get import *
from pacman_action import *


class PacGrid(PacInit, PacGet, PacAction):
    def __init__(self, map, args):
        #Map specific
        self.map = map

        #MDP core
        self.NUM_A = 4
        self.GAMMA = 0.33

        self.EPSILON = args.get_e()
        self.min_EPSILON = 0.0001
        self.decay_rate_epsilon = 0.999
        

        self.alpha = args.get_a()
        self.min_alpha = 0.00005
        self.decay_rate = 1

        self.use_epsilon_decay = True
        self.use_alpha_decay = True
        self.use_game_states = True

        #Game
        self.consumed_pellets = 0

        self.states = []
        self.pellet_ids = []
        self.first_time_load = True
        self.game_states = []
        self.create_map()

        #Collision
        self.ghost_next_ids = None
        

            
    #Epsilon greedy
    def epsilon_greedy(self, s):
        if random.uniform(0, 1) < self.EPSILON:
            return random.randint(0, 3)
        return s.policy
    
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
            #self.consumed_pellets += 1

    #Reset physical states
    def reset(self):
        self.consumed_pellets = 0
        self.load_state_types()
        self.assign_properties()


    #Return reward based on next state
    def r_gamestate(self, next_state_id = 0, ghosts = []):
        gs = self.game_states[next_state_id]

        if sum(gs.pellets) == 0:
            return 500

        for g in ghosts:
            if gs.info[0] == g.next_state.id:
                return -500

        match self.states[gs.info[0]].type:
            case 0: #EMPTY
                return -1
            case 1: #WALL
                return -1
            case 2: #PELLET
                return 10
            case 3: #ENERGIZER
                return 50
            
    #Return reward based on next state
    def r(self, next_state_id = 0, ghosts = []):

        if self.consumed_pellets == self.map.total_pellets:
            print("a")
            return 500

        for ghost in ghosts:
            if self.states[next_state_id].id == ghost.next_state.id:
                return -500
            
        match self.states[next_state_id].type:
            case 0: #EMPTY
                return -1
            case 1: #WALL
                return -1
            case 2: #PELLET
                if self.consumed_pellets + 1 == self.map.total_pellets:
                    return 500
                return 10
            case 3: #ENERGIZER
                return 10