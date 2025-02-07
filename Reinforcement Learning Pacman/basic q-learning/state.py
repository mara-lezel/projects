
class State:
    id = 0

    def __init__(self, i, j, x, y, len, terminal = False, blocked = False, color = (0,0,0), fill = False):

        #Drawing purposes
        self.x = x
        self.y = y
        self.center_x = x + len / 2.8
        self.center_y = y + len / 2.4

        self.len = len
        self.color = color
        self.fill = fill

        #State parameters
        self.i = i
        self.j = j
        self.v = 0
        self.reward = 0
        self.policy = 0
        self.type = 0
        self.direction = [0.0, 0.0, 0.0, 0.0]

        self.terminal = terminal
        self.blocked = blocked
        
        self.id = State.id
        State.id += 1

    def has_pellet(self):
        return self.type == 2
    
    def has_energizer(self):
        return self.type == 3
    
    def is_wall(self):
        return self.type == 1
    
    def is_empty(self):
        return self.type == 0



    def __str__(self):
        return f"State {self.id} pos=({self.i},{self.j}) coord=({self.x};{self.y}) size={self.len} \
        color={self.color} fill={self.fill} terminal={self.terminal} blocked={self.blocked}"
    


class GameState:
    id = 0

    def __init__(self, i, j, info, terminal = False, blocked = False, color = (0,0,0), fill = False):

        #State parameters
        self.i = i
        self.j = j
        self.v = 0
        self.reward = 0
        self.policy = 0
        self.direction = [0.0, 0.0, 0.0, 0.0]

        self.terminal = terminal
        self.blocked = blocked
        
        self.location = info[0]
        self.pellets = info[1:-1]
        self.info = info

        self.mean = 0
        self.variance = 0


    def __str__(self):
        return f"Location {self.location} pos=({self.i},{self.j}) info={self.info}"