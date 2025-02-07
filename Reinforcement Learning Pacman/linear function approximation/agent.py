
class Agent:
    def __init__(self, starting_state = None, game_start_state = None):
        #Used for debug info, to highlight features
        self.last_action = None
        
        self.action = None
        self.next_action = 0
        self.state = starting_state

class Ghost:
    def __init__(self, index, starting_state = None, AI = 1, color = (255, 1, 0)):
        self.previous_action = 0
        self.action = None

        self.state = starting_state
        self.next_state = starting_state

        self.AI = AI
        self.color = color
        self.frightened = False
        self.scared_timer = -1
        self.index = index