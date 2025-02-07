import random

from state import *


#Shared stochastic environment details ------------------------------------------------------------------
class MDP:
    def __init__(self, alpha, epsilon, decay, gamma = 0.9, step_reward = -0.3):
        self.NUM_A = 4
        self.PROB_1 = 0.8
        self.PROB_2 = 0.1

        #GAMMA = 1 means a reward in the future is as important as immediate reward
        self.GAMMA = gamma
        self.R = step_reward

        self.EPSILON = epsilon
        self.min_EPSILON = 0.1
        self.decay_rate_epsilon = 0.98
        
        self.alpha = alpha
        self.min_alpha = 0.01
        self.decay_rate = 0.96

        self.use_epsilon_decay = decay
        self.use_alpha_decay = decay

    #Create empty states
    def create_initial_states(self):
        OFFSET = 150
        for i in range (self.COLUMNS):
            for j in range (self.ROWS):
                if i == 0 and j == 0:
                    self.states.append(State(i, j, OFFSET , OFFSET, self.BOX_SIZE))
                else:
                    self.states.append(State(i, j, OFFSET + i * self.BOX_SIZE - self.BORDER * i, 
                                            OFFSET + j * self.BOX_SIZE  - self.BORDER * j, self.BOX_SIZE ))

    #Mark state as blocked
    def block_state(self, state):
        state.blocked = True
        state.fill = True
        state.color = (211, 211, 211)

    #Mark state as a goal
    def goal_state(self, state, reward):
        state.terminal = True
        state.fill = True
        state.color = (144,238,144)
        state.direction = [0, 0, 0, 0]
        state.v = reward
        state.reward = reward

    #Mark state as negative terminal state
    def negative_state(self, state, reward):
        state.terminal = True
        state.fill = True
        state.color = (219,112,147)
        state.direction = [0, 0, 0, 0]
        state.v = reward
        state.reward = reward

    #Display grid coordinates and info
    def print_info(self):
        for state in self.states:
            print(state)

        for i in range(self.ROWS):
            for j in range(self.COLUMNS):
                print("(%s,%s) " % (j, i), end='')
            print()

    #Not stochastic
    def next_state(self, s, a):
        match a:
            case 0: #UP
                if s.j == 0 or self.states[s.id - 1].blocked:
                    return s.id
                return s.id - 1
            case 1: #RIGHT
                if s.i == self.COLUMNS - 1 or self.states[s.id + self.ROWS].blocked:
                    return s.id
                return s.id + self.ROWS
            case 2: #DOWN
                if s.j == self.ROWS - 1 or self.states[s.id + 1].blocked:
                    return s.id
                return s.id + 1
            case 3: #LEFT
                if s.i == 0 or self.states[s.id - self.ROWS].blocked:
                    return s.id
                return s.id - self.ROWS
            
    #Stochastic next state        
    def get_next_state(self, s, a):
        next_state_id = None

        #If going to wall, no chance to end up in a different state
        if s.id == self.next_state(s, a):
            return s.id
        
        random_num = random.uniform(0, 1)
        if random_num < 0.8:
            next_state_id = self.next_state(s, a)
        elif random_num < 0.9:
            new_action = self.counter_clockwise(a)
            next_state_id = self.next_state(s, new_action)
        else:
            new_action = self.clockwise(a)
            next_state_id = self.next_state(s, new_action)
        

        return next_state_id
    
    #Epsilon greedy
    def epsilon_greedy(self, s):
        if random.uniform(0, 1) < self.EPSILON:
            return random.randint(0, 3)
        return s.policy
            
    #Get action on the right
    def clockwise(self, a):
        return (a + 1) % self.NUM_A
    
    #Get action on the left
    def counter_clockwise(self, a):
        return (a - 1) % self.NUM_A
    
    #Decay learning rate (if enabled)
    def decay_a(self):
        if self.use_alpha_decay and self.alpha > self.min_alpha:
            self.alpha *= self.decay_rate

    #Decay exploeation rate (if enabled)
    def decay_epsilon(self):
        if self.use_epsilon_decay and self.EPSILON > self.min_EPSILON:
            self.EPSILON *= self.decay_rate_epsilon

    #Get start state
    def get_start_state(self):
        return self.start
    
    #Get positive reward state
    def get_goal_state(self):
        return self.goal
    
    #Return reward based on location
    def r(self, next_state_id = 0):
        return self.R + self.states[next_state_id].reward
    
    #For plotting
    def get_epsilon_alpha(self):
        return (self.EPSILON, self.min_EPSILON, self.decay_rate_epsilon), (self.alpha, self.min_alpha, self.decay_rate)

    #For shortest path
    def get_legal_neighbours(self, state_id):
        nbrs = []
        for a in range (self.NUM_A):
            next_id = self.next_state(self.states[state_id], a)
            if next_id != state_id:
                nbrs.append(next_id)
        return nbrs