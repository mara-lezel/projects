import argparse

""" 
HELP
-m MODE = [0 - manual; 1 - training; 2 - acting]
-r RENDER = [0 - no graphics; 1 - show graphics]
-n NUM_OF_EPISODES = [0 - no limit; >0 - episode limit]
-q Q_FUNCTION = [0 - Value Iteration; 1 - Tabular Q Learning; 2 - Approximate Q Learning]
-p PLOT = [0 - reward every episode; 1 - reward after x episodes of training]
-x TRAIN_EP = number or training episodes before measuring performance 
-g GRID = [0 - default grid; 1 - large grid; 2 - huge grid]
-e EPSILON = exploration rate
-a ALPHA = learning rate
-d DECAY = [0 - disabled; 1 - enabled]
-l LOAD_FILE = [0 - most recent; >0 - file number]
-map PACMAN_MAP = [0 - small; 1 - medium]
"""

"""
DEFAULT SETTINGS:
-m MODE -> 0
-r RENDER -> 1
-n NUM_OF_EPISODES -> 0
-q Q_FUNCTION -> 1
-p PLOT -> 0
-x TRAIN_EP -> 1
-g GRID -> 0
-e EPSILON -> 0.8
-a ALPHA -> 0.8
-d DECAY -> 1
-l LOAD_FILE -> 0
-map PACMAN_MAP -> 0
"""

class ArgParser:
    def __init__(self):
        self.parser = argparse.ArgumentParser()
        self.parser.add_argument("-m", "--mode", help = "[0 - manual; 1 - training; 2 - acting]")
        self.parser.add_argument("-r", "--render", help = "[0 - no graphics; 1 - show graphics]")
        self.parser.add_argument("-n", "--num_of_episodes", help = "[0 - no limit; >0 - episode limit]")
        self.parser.add_argument("-q", "--q_function", help = "[0 - Value Iteration; 1 - Tabular Q Learning; 2 - Approximate Q Learning]")
        self.parser.add_argument("-p", "--plot", help = "[0 - reward every episode, 1 - reward after x episodes of training]")
        self.parser.add_argument("-x", "--x", help = "number or training episodes before measuring performance")
        self.parser.add_argument("-g", "--grid", help = "[0 - default grid; 1 - large grid; 2 - huge grid]")
        self.parser.add_argument("-e", "--epsilon", help = "exploration rate")
        self.parser.add_argument("-a", "--alpha", help = "learning rate")
        self.parser.add_argument("-d", "--decay", help = "[0 - disabled; 1 - enabled]")
        self.parser.add_argument("-l", "--load_file", help = "[0 - most recent; >0 - file number]")
        self.parser.add_argument("-map", "--pacman_map", help = "[0 - small; 1 - medium]")
        self.args = self.parser.parse_args()
    
    def get_m(self):
        if self.args.mode == None:
            return 0
        return int(self.args.mode)
        
    def get_r(self):
        if self.args.render == None:
            return True
        return bool(int(self.args.render))
    
    def get_n(self):
        if self.args.num_of_episodes == None:
            return 0
        return int(self.args.num_of_episodes)
    
    def get_q(self):
        if self.args.q_function == None:
            return 2
        return int(self.args.q_function) 
    
    def get_p(self):
        if self.args.plot == None:
            return 0
        return int(self.args.plot)
    
    def get_x(self):
        if self.args.x == None:
            return 1
        return int(self.args.x)
    
    def get_g(self):
        if self.args.grid == None:
            return 3
        return int(self.args.grid)
    
    def get_e(self):
        if self.args.epsilon == None:
            return 0.8
        return float(self.args.epsilon)
    
    def get_a(self):
        if self.args.alpha == None:
            return 0.8
        return float(self.args.alpha)
    
    def get_d(self):
        if self.args.decay == None:
            return True
        return bool(int(self.args.decay))
    
    def get_l(self):
        if self.args.load_file == None:
            return 0
        return int(self.args.load_file)
    
    def get_map(self):
        if self.args.pacman_map == None:
            return 2
        return int(self.args.pacman_map)