import copy

class PacGet:

    '''
    Returns next game state [pacman_location, pellet setup, ghost_location]:
    - New pacman location
    - If new pacman location has a pellet, game state changes to reflect the new
      environment where that pellet no longer exists
    - New ghost location
    '''
    def get_next_gamestate(self, gs, a, ghosts):
        DIR = None
        gs_info = copy.deepcopy(gs.info)
        for i in range (len(ghosts)):
            gs_info[-(i+1)] = ghosts[-(i+1)].next_state.id

        match a:
            case 0: #UP
                DIR = UP = gs.location - 1
                if gs.j == 0 or self.states[UP].blocked:
                    return self.get_gamestate_id(gs_info)  
            case 1: #RIGHT
                DIR = RIGHT = gs.location + self.map.ROWS
                if gs.i == self.map.COLUMNS - 1 or self.states[RIGHT].blocked:
                    return self.get_gamestate_id(gs_info)  
            case 2: #DOWN
                DIR = DOWN = gs.location + 1
                if gs.j == self.map.ROWS - 1 or self.states[DOWN].blocked:
                    return self.get_gamestate_id(gs_info)  
            case 3: #LEFT
                DIR = LEFT = gs.location - self.map.ROWS
                if gs.i == 0 or self.states[LEFT].blocked:
                    return self.get_gamestate_id(gs_info) 

        #If pacman and ghost are swapping, stop pacman movement so they collide
        for i in range (len(ghosts)):
            if gs_info[0] == ghosts[i].next_state.id and ghosts[i].state.id == DIR:
                return self.get_gamestate_id(gs_info) 
            
        #If upcoming state has a pellet
        if self.states[DIR].has_pellet():
            return self.get_next_gamestate_id(gs, DIR, ghosts, True)
        return self.get_next_gamestate_id(gs, DIR, ghosts)

    #Get id of next game state based on movement direction and pellets
    def get_next_gamestate_id(self, gs, new_location, ghosts, pellet = False):

        index = None
        new_info = copy.deepcopy(gs.info)

        for i in range (len(ghosts)):
            new_info[-(i+1)] = ghosts[-(i+1)].next_state.id

        #If moving into pellet state
        if pellet:
            index = self.pellet_ids.index(new_location)
            new_info[0] = new_location
            new_info[index + 1] = 0
        else:
            new_info[0] = new_location

        return self.get_gamestate_id(new_info)

    #Get id of game state
    def get_gamestate_id(self, new_info):
        game_state_id = 0
        for gs in self.game_states:
            if gs.info == new_info:
                return game_state_id
            game_state_id += 1
        return -1
    
     #Get start state
    def get_start_gamestate(self):
        match self.map.name:
            case "small.txt":
                return self.game_states[self.get_gamestate_id([8, 1, 1, 33])]
            case "medium.txt":
                return self.game_states[self.get_gamestate_id([8, 1, 1, 1, 1, 40])]

            
    #FUNCTION APPROX AND GRID ----------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------
    def get_next_pacman_state_id(self, s, a, ghosts):
        DIR = self.get_next_state_id(s, a)

        #If pacman and ghost are swapping, stop pacman movement so they collide
        for i in range (len(ghosts)):
            if s.id == ghosts[i].next_state.id and ghosts[i].state.id == DIR:
                return s.id
        return DIR
            
    
    def get_start_state(self):
        return self.states[self.map.start_id]
            
    def get_ghost_start_state(self, ghost_index):
        return self.states[self.map.ghost_start_id[ghost_index]]
    
    #Returns next state id
    def get_next_state_id(self, s, a):
        DIR = None
        match a:
            case 0: #UP
                DIR = UP = s.id - 1
                if s.j == 0 or self.states[UP].blocked:
                    return s.id
            case 1: #RIGHT
                DIR = RIGHT = s.id + self.map.ROWS
                if s.i == self.map.COLUMNS - 1 or self.states[RIGHT].blocked:
                    return s.id
            case 2: #DOWN
                DIR = DOWN = s.id + 1
                if s.j == self.map.ROWS - 1 or self.states[DOWN].blocked:
                    return s.id
            case 3: #LEFT
                DIR = LEFT = s.id - self.map.ROWS
                if s.i == 0 or self.states[LEFT].blocked:
                    return s.id
        return DIR