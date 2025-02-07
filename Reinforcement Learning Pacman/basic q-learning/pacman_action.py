import random

class PacAction:

    def get_ghost_action(self, s, prev_a, p_s, AI):
        match AI:
            case 0:
                return self.get_ghost_action_normal(s, prev_a)
            case 1:
                return self.get_ghost_action_aggressive(s, prev_a, p_s)
            case 2:
                return self.get_ghost_action_mixed(s, prev_a, p_s)
    
    def get_ghost_action_normal(self, s, prev_a):
        actions = [0, 1, 2, 3]
        random.shuffle(actions)

        for a in actions:
            #Do not reverse direction
            if abs(a - prev_a) == 2:
                continue

            #Do not move into a wall
            if self.get_next_state_id(s, a) == s.id:
                continue

            return a
        
        return (prev_a - 2) % (self.NUM_A)
    
    def get_ghost_action_aggressive(self, s, prev_a, pacman_state):

        dists = []
        for a in range(self.NUM_A):
            #Do not reverse direction
            if abs(a - prev_a) == 2:
                dists.append(99999)
                continue

            #Do not move into a wall
            if self.get_next_state_id(s, a) == s.id:
                dists.append(99999)
                continue

            dists.append(self.closest_to_ghost(s, a, pacman_state))

        if len(dists) == 0:
            return (prev_a - 2) % (self.NUM_A)
        
        return dists.index(min(dists))
    
    def get_ghost_action_mixed(self, s, prev_a, pacman_state):

        aggro = random.uniform(0, 1) < 0.8

        dists = []
        for a in range(self.NUM_A):
            #Do not reverse direction
            if abs(a - prev_a) == 2:
                dists.append(99999)
                continue

            #Do not move into a wall
            if self.get_next_state_id(s, a) == s.id:
                dists.append(99999)
                continue

            #dists.append(self.closest_to_ghost(s, a, pacman_state))
            dists.append(self.manhattan(pacman_state, self.states[self.get_next_state_id(s, a)]))


        if len(dists) == 0:
            return (prev_a - 2) % (self.NUM_A)
        
        if aggro:
            return dists.index(min(dists))
        
        for i in range(self.NUM_A):
            if dists[i] == 99999:
                dists[i] = -1
                
        return dists.index(max(dists))

    def manhattan(self, pac, ghost):
        "Returns the Manhattan distance between points xy1 and xy2"
        return abs(pac.i - ghost.i) + abs(pac.j - ghost.j)


    
    def closest_to_ghost(self, s, a, pacman_state):
        new_id = self.get_next_state_id(s, a)

        possible = [(new_id, 1)]
        explored = set()
        
        #While there are possible tiles
        while possible:
            s_id, dist = possible.pop(0)
            if s_id in explored:
                continue
            explored.add(s_id)

            if self.states[s_id].id == pacman_state.id:
                return dist
            
            nbrs = self.get_legal_neighbours(s_id)
            for nbr_id in nbrs:
                if nbr_id not in explored:
                    possible.append((nbr_id, dist + 1))

        return None