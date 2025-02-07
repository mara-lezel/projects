
from mdp import *

'''
Consider decaying exploration rate from 1 to 0.1 for example.
'''

class Grid_1(MDP):
    def __init__(self, alpha, epsilon, decay):
        MDP.__init__(self, alpha, epsilon, decay)
        self.SCREEN_SIZE = (900, 720)
        self.BORDER = 2
        self.BOX_SIZE = 150
        self.FONT = 20

        self.ROWS = 3
        self.COLUMNS = 4

        self.states = []
        self.create_states(True)

        self.start = self.states[2]
        self.goal = self.states[9]


    def create_states(self, print_info = False):
        self.create_initial_states()

        self.block_state(self.states[4])
        self.goal_state(self.states[9], 1)
        self.negative_state(self.states[10], -1)

        if print_info:
            self.print_info()

#--------------------------------------------------------------------------------------------------------
class Grid_2(MDP):
    def __init__(self, alpha, epsilon, decay, discount_rate = 0.9, step_reward = -0.3):
        MDP.__init__(self, alpha, epsilon, decay)
        self.SCREEN_SIZE = (1000, 800)
        self.BORDER = 2
        self.BOX_SIZE = 150
        self.FONT = 20

        self.ROWS = 4
        self.COLUMNS = 5

        self.states = []
        self.create_states(True)

        self.start = self.states[3]
        self.goal = self.states[12]

    def create_states(self, print_info = False):
        self.create_initial_states()

        self.block_state(self.states[5])
        self.block_state(self.states[9])
        self.block_state(self.states[13])
        self.negative_state(self.states[8], -1)
        self.negative_state(self.states[11], -1)
        self.goal_state(self.states[12], 5)

        if print_info:
            self.print_info()

#--------------------------------------------------------------------------------------------------------
class Grid_3(MDP):
    def __init__(self, alpha, epsilon, decay, discount_rate = 0.9, step_reward = -0.3):
        MDP.__init__(self, alpha, epsilon, decay)
        self.SCREEN_SIZE = (1000, 800)
        self.BORDER = 2
        self.BOX_SIZE = 60
        self.FONT = 10

        self.ROWS = 10
        self.COLUMNS = 10

        self.states = []
        self.create_states(True)

        self.start = self.states[0]
        self.goal = self.states[99]

    def create_states(self, print_info = False):
        self.create_initial_states()

        self.goal_state(self.states[99], 20)

        self.negative_state(self.states[98], -2)
        self.negative_state(self.states[88], -2)
        self.negative_state(self.states[35], -5)
        self.negative_state(self.states[36], -5)
        self.negative_state(self.states[37], -5)

        self.block_state(self.states[81])
        self.block_state(self.states[83])
        self.block_state(self.states[85])
        self.block_state(self.states[87])
        self.block_state(self.states[77])
        self.block_state(self.states[67])
        self.block_state(self.states[57])

        self.block_state(self.states[2])
        self.block_state(self.states[12])
        self.block_state(self.states[22])
        self.block_state(self.states[32])

        self.block_state(self.states[14])
        self.block_state(self.states[24])
        self.block_state(self.states[34])

        self.block_state(self.states[6])
        self.block_state(self.states[7])
        self.block_state(self.states[8])


        if print_info:
            self.print_info()