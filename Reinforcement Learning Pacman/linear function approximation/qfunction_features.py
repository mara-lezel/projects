DIST = 1

''' IDENTITY FEATURES (SAME AS TABULAR) '''
class IdentityExtractor:
    def get_number_of_feats(self):
        return len(self.mdp.states)
    
    def add_features(self, feats, state, action, ghosts):
        for s in self.mdp.states:
            if s.id == state.id:
                feats.append(1.0)
            else:
                feats.append(0.0)


''' BASIC REFLEX FEATURES '''
class BasicReflexExtractor:

    def get_number_of_feats(self):
        return 6

    def add_features(self, feats, state, action, ghosts):    
        #Get new state
        state_after_action = self.mdp.get_next_pacman_state_id(state, action, ghosts)

        #feats.append(self.cornered(state_after_action))
        feats.append(self.closest_food(state_after_action, ghosts))
        feats.append(self.can_eat_food(state_after_action, ghosts))
        feats.append(self.ghost_one_step(state_after_action, ghosts))
        feats.append(self.closest_ghost(state_after_action, ghosts))
        feats.append(self.will_collide(state_after_action, ghosts))
        feats.append(feats[-2] * feats[-3])

        """ if feats[-1] > 0.0:
            for i in range (len(feats) - 2):
                feats[i] = 0.0 """

        for i in range(len(feats)):
            feats[i] /= 10.0
    
    def cornered(self, state_id):
        nbrs = self.mdp.get_legal_neighbours(state_id)
        if len(nbrs) == 1:
            return 1.0
        return 0.0


    def closest_food(self, state_id, ghosts):
        dist = self.closest_food_dist(state_id)
        if dist is not None and dist != 0:
            return (1/dist) 
            return float(dist) / (self.mdp.map.ROWS * self.mdp.map.COLUMNS)
        return 0.0
    
    def closest_ghost(self, state_id, ghosts):
        #dist = self.closest_ghost_dist(state_id, ghosts)
        dist = self.ghost_avg_dist(state_id, ghosts)
        if dist is not None and dist != 0:
            return 1/dist
            return float(dist) / (self.mdp.map.ROWS * self.mdp.map.COLUMNS)
        return 0.0
    
    def closest_food_dist(self, state_id):

        possible = [(state_id, DIST)]
        explored = set()
        
        #While there are possible tiles
        while possible:
            possible_id, dist = possible.pop(0)
            if possible_id in explored:
                continue
            explored.add(possible_id)

            if self.mdp.states[possible_id].has_pellet():
                return dist 
            
            nbrs = self.mdp.get_legal_neighbours(possible_id)
            for nbr_id in nbrs:
                possible.append((nbr_id, dist + 1))

        return None


    def closest_ghost_dist(self, state_id, ghosts):

        possible = [(state_id, DIST)]
        explored = set()
        
        #While there are possible tiles
        while possible:
            s_id, dist = possible.pop(0)
            if s_id in explored:
                continue
            explored.add(s_id)

            for g in ghosts:
                if s_id == g.state.id:
                    return dist
            
            nbrs = self.mdp.get_legal_neighbours(s_id)
            for nbr_id in nbrs:
                possible.append((nbr_id, dist + 1))

        return None
    
    def ghost_avg_dist(self, state_id, ghosts):
        sum = 0.0
        for g in ghosts:
            possible = [(state_id, DIST)]
            explored = set()
            
            #While there are possible tiles
            while possible:
                s_id, dist = possible.pop(0)
                if s_id in explored:
                    continue
                explored.add(s_id)

                if s_id == g.state.id:
                    sum += dist
                    break
                
                nbrs = self.mdp.get_legal_neighbours(s_id)
                for nbr_id in nbrs:
                    possible.append((nbr_id, dist + 1))

        return sum

    def can_eat_food(self, state_id, ghosts):
        one_step = self.ghost_one_step(state_id, ghosts)
        if one_step == 0.0 and self.mdp.states[state_id].has_pellet():
            return 1.0
        return 0.0

    def ghost_one_step(self, state_id, ghosts):
        num = 0.0
        for g in ghosts:
            if state_id in self.mdp.get_legal_neighbours(g.state.id) or state_id == g.state.id:
                num += 1.0
        return num
    
    def will_collide(self, state_id, ghosts):
        for g in ghosts:
            if state_id == g.next_state.id:
                return 1.0
        return 0.0
    


''' FEATURES FROM PAPER'''
class PaperExtractor:

    def get_number_of_feats(self):
        return 11

    def get_features(self, state, action, ghosts):   
        
        #Get new state
        state_after_action = self.mdp.get_next_state_id(state, action)

        feats = dict()
        feats['bias'] = 1.0
        feats['safe-to-eat'] = self.can_eat_food(state_after_action, ghosts)#[CRUCIAL] 
        feats['closest-food'] = self.closest_food(state_after_action, ghosts)
        feats['#-of-ghosts-1-step-away'] = self.active_one_step_away(state_after_action, ghosts)#[CRUCIAL]
        feats['#-of-ghosts-2-steps-away'] = self.active_two_steps_away(state_after_action, ghosts)
        feats['closest-active-ghost1'] = self.closest_part_ghost(state_after_action, ghosts[0], inverted=True)
        #feats['closest-active-ghost2'] = self.closest_part_ghost(state_after_action, ghosts[1], inverted=True)

        #feats['closest-active-ghost-inv'] = self.closest_ghost(state_after_action, ghosts, active = True, inverted = True)
        feats['closest-scared-ghost'] = self.closest_ghost(state_after_action, ghosts, active = False, inverted = False)
        feats['#-of-scared-1-step-away'] = self.scared_one_step_away(state_after_action, ghosts)
        feats['#-of-scared-2-steps-away'] = self.scared_two_steps_away(state_after_action, ghosts)
        feats['closest-capsule'] = self.closest_capsule(state_after_action, ghosts)
        feats['#-of-capsules'] = self.capsules_when_ghost_nearby(state_after_action, ghosts)

        
        if feats['#-of-ghosts-1-step-away'] > 0:
            feats['safe-to-eat'] = 0
            feats['closest-food'] = 0


        for key in feats:
            feats[key] /= 10.0

        return feats

        
    #0 -----------------------------------------------------------------------------------------------------------------------
    def can_eat_food(self, state_id, ghosts):
        dist = self.closest_food_dist(state_id)
        if dist == DIST:
            return 1.0
        return 0.0

    #1 -----------------------------------------------------------------------------------------------------------------------
    def closest_food(self, state_id, ghosts):
        dist = self.closest_food_dist(state_id)
        if dist is not None:
            return (1/dist) 
            #return float(dist) / (self.mdp.map.ROWS * self.mdp.map.COLUMNS)
        return 0.0
    
    def closest_food_dist(self, state_id):

        possible = [(state_id, DIST)]
        explored = set()
        
        #While there are possible tiles
        while possible:
            possible_id, dist = possible.pop(0)
            if possible_id in explored:
                continue
            explored.add(possible_id)

            if self.mdp.states[possible_id].has_pellet():
                return dist 
            
            nbrs = self.mdp.get_legal_neighbours(possible_id)
            for nbr_id in nbrs:
                possible.append((nbr_id, dist + 1))

        return None
    
    #2 -----------------------------------------------------------------------------------------------------------------------
    def active_one_step_away(self, state_id, ghosts):    
        num = 0.0
        for g in ghosts:
            if (state_id in self.mdp.get_legal_neighbours(g.state.id) or state_id == g.state.id) and not g.frightened:
                num += 1.0
            """ if self.closest_to_that_particular_ghost(state_id, g) == 1 and not g.frightened:
                num += 1.0 """
        return num / self.mdp.map.num_of_ghosts
    
    #3 -----------------------------------------------------------------------------------------------------------------------
    def active_two_steps_away(self, state_id, ghosts):
        num = 0
        pac_nbrs = self.mdp.get_legal_neighbours(state_id)
        for g in ghosts:
            """ if self.closest_to_that_particular_ghost(state_id, g) == 2 and not g.frightened:
                num += 1.0 """
            for pac_nbr_id in pac_nbrs:
                if pac_nbr_id in self.mdp.get_legal_neighbours(g.state.id) and not g.frightened:
                    num += 1.0
                    break
        #print("Two steps away - ", num)
        return num / self.mdp.map.num_of_ghosts
    
    #4,5,6 -------------------------------------------------------------------------------------------------------------------
    def closest_ghost(self, state_id, ghosts, active, inverted):
        
        dist = None
        if active:
            dist = self.closest_active_ghost_dist(state_id, ghosts)
        else:
            dist = self.closest_scared_ghost_dist(state_id, ghosts)

        if dist is not None:
            if inverted:
                return 1 / dist
            else:
                return float(dist) / (self.mdp.map.ROWS * self.mdp.map.COLUMNS)
        return 0.0
    
    def closest_part_ghost(self, state_id, ghost, inverted):
        
        dist = self.closest_to_that_particular_ghost(state_id, ghost)

        if dist is not None:
            if inverted:
                return 1 / dist
            else:
                return float(dist) / (self.mdp.map.ROWS * self.mdp.map.COLUMNS)
        return 0.0
    
    def closest_active_ghost_dist(self, state_id, ghosts):

        possible = [(state_id, DIST)]
        explored = set()
        
        #While there are possible tiles
        while possible:
            s_id, dist = possible.pop(0)
            if s_id in explored:
                continue
            explored.add(s_id)

            for g in ghosts:
                if s_id == g.state.id and not g.frightened:
                    return dist
            
            nbrs = self.mdp.get_legal_neighbours(s_id)
            for nbr_id in nbrs:
                possible.append((nbr_id, dist + 1))

        return None
    
    def ghost_avg_dist(self, state_id, ghosts):
        sum = 0.0
        for g in ghosts:
            possible = [(state_id, DIST)]
            explored = set()
            
            #While there are possible tiles
            while possible:
                s_id, dist = possible.pop(0)
                if s_id in explored:
                    continue
                explored.add(s_id)

                if s_id == g.state.id and not g.frightened:
                    sum += dist
                    break
                
                nbrs = self.mdp.get_legal_neighbours(s_id)
                for nbr_id in nbrs:
                    possible.append((nbr_id, dist + 1))

        return sum
    
    def closest_scared_ghost_dist(self, state_id, ghosts):

        possible = [(state_id, DIST)]
        explored = set()
        
        #While there are possible tiles
        while possible:
            s_id, dist = possible.pop(0)
            if s_id in explored:
                continue
            explored.add(s_id)

            for g in ghosts:
                if s_id == g.state.id and g.frightened:
                    return dist
            
            nbrs = self.mdp.get_legal_neighbours(s_id)
            for nbr_id in nbrs:
                possible.append((nbr_id, dist + 1))

        return None
    
    #7,8 ---------------------------------------------------------------------------------------------------------------------
    def scared_one_step_away(self, state_id, ghosts):
        num = 0.0
        for g in ghosts:
            if state_id in self.mdp.get_legal_neighbours(g.state.id) and g.frightened:
                num += 1.0
            """ if self.closest_to_that_particular_ghost(state_id, g) == 1 and g.frightened:
                num += 1.0 """
        return num / self.mdp.map.num_of_ghosts
    
    def scared_two_steps_away(self, state_id, ghosts):
        num = 0
        pac_nbrs = self.mdp.get_legal_neighbours(state_id)
        for g in ghosts:
            """ if self.closest_to_that_particular_ghost(state_id, g) == 1 and g.frightened:
                num += 1.0 """
            for pac_nbr_id in pac_nbrs:
                if pac_nbr_id in self.mdp.get_legal_neighbours(g.state.id) and g.frightened:
                    num += 1.0
                    break
        return num / self.mdp.map.num_of_ghosts
    
    #9 -----------------------------------------------------------------------------------------------------------------------
    def closest_capsule(self, state_id, ghosts):
        dist = self.closest_capsule_dist(state_id)
        if dist is not None:
            return (1/dist) 
            #return float(dist) / (self.mdp.map.ROWS * self.mdp.map.COLUMNS)
        return 0.0
    
    def closest_capsule_dist(self, state_id):

        possible = [(state_id, DIST)]
        explored = set()
        
        #While there are possible tiles
        while possible:
            possible_id, dist = possible.pop(0)
            if possible_id in explored:
                continue
            explored.add(possible_id)

            if self.mdp.states[possible_id].has_energizer():
                return dist 
            
            nbrs = self.mdp.get_legal_neighbours(possible_id)
            for nbr_id in nbrs:
                possible.append((nbr_id, dist + 1))

        return None
    
    #10 ----------------------------------------------------------------------------------------------------------------------
    def capsules_when_ghost_nearby(self, state_id, ghosts):
        if self.mdp.map.total_energizers == 0:
            return 0
        return (self.mdp.map.total_energizers - self.mdp.consumed_energizers) / self.mdp.map.total_energizers
    

    def closest_to_that_particular_ghost(self, state_id, ghost):

        possible = [(state_id, DIST)]
        explored = set()
        
        #While there are possible tiles
        while possible:
            s_id, dist = possible.pop(0)
            if s_id in explored:
                continue
            explored.add(s_id)

            if s_id == ghost.state.id:
                return dist
            
            nbrs = self.mdp.get_legal_neighbours(s_id)
            for nbr_id in nbrs:
                possible.append((nbr_id, dist + 1))

        return None

    
    
        

