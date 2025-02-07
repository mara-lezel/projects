import copy

class PacGet:

    '''
    Returns next Pacman state id. 
    Identical to get_next_state_id(), except it will not let Pacman move if
    one of the ghosts is moving to current Pacman position and Pacman is moving
    to the ghosts position -- prevents swapping places without colliding.
    '''
    def get_next_pacman_state_id(self, current_pacman_state, a, ghosts):
        #For accurate display of current features
        if a == None:
            return current_pacman_state.id
        
        #Where Pacman goes next
        NEXT_STATE_ID = self.get_next_state_id(current_pacman_state, a)

        #If pacman and ghost are swapping, stop pacman movement so they collide
        for i in range (len(ghosts)):
            if current_pacman_state.id == ghosts[i].next_state.id and ghosts[i].state.id == NEXT_STATE_ID:
                return current_pacman_state.id
        return NEXT_STATE_ID
            
    
    '''
    Returns the starting state of Pacman, based on the map.
    '''
    def get_start_state(self):
        return self.states[self.map.start_id]
    
    '''
    Returns the starting state for ghosts, based on map and ghost index.
    Ghost's identity depends on the index it has.
    '''        
    def get_ghost_start_state(self, ghost_index):
        return self.states[self.map.ghost_start_id[ghost_index]]
    
    '''
    Returns next state id (for ghosts or Pacman).
    When moving into a wall, the current state id is returned.
    '''
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