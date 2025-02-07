

class FeaturesOld:

    def get_number_of_feats(self):
        return 4

    def add_features(self, features_of_state, state, ghosts):

        #FEATURE 1
        features_of_state.append(self.get_distance_to_closest_food(state))
        #FEATURE 2
        features_of_state.append(self.get_number_of_active_ghosts_one_step_away(state, ghosts))
        #FEATURE 3
        features_of_state.append(self.get_distance_to_closest_active_ghost(state, ghosts))
        #FEATURE 4
        #features_of_state.append(self.get_inverse_of_distance_to_closest_ghost(state, ghosts))
        #FEATURE 5
        #features_of_state.append(self.get_distance_to_closest_scared_ghost(state, ghosts))
        #FEATURE 6
        #features_of_state.append(self.get_number_of_scared_ghosts_nearby(state, ghosts))
        #FEATURE 7
        #features_of_state.append(self.get_min_distance_to_capsule(state))
        #FEATURE 8
        #features_of_state.append(self.get_min_distance_to_scared_ghost(state, ghosts))
        #FEATURE 9
        #features_of_state.append(self.get_number_of_capsules_when_ghost_nearby(state, ghosts))
        #FEATURE 10
        features_of_state.append(self.get_ghost_not_nearby_food_is_nearby(state, ghosts))
        #print(features_of_state)


    


    #FEATURE 1
    def get_distance_to_closest_food(self, pacman_state):
        closest_to_food = 99999
        for food_state in self.mdp.states:
            if food_state.type == 2:
                dist_to_food = self.mdp.manhattan_distance(pacman_state.id, food_state.id)
                if dist_to_food < closest_to_food:
                    closest_to_food = dist_to_food

        #Normalize
        return self.normalize_distance(closest_to_food)
    
    #FEATURE 2
    def get_number_of_active_ghosts_one_step_away(self, pacman_state, ghosts):
        number = 0
        for ghost in ghosts:
            if self.mdp.manhattan_distance(pacman_state.id, ghost.state.id) == 1:
                number += 1

        #Normalize
        return self.normalize_ghosts(number)
    
    #FEATURE 3
    def get_distance_to_closest_active_ghost(self, pacman_state, ghosts):
        closest_to_ghost = 99999
        for ghost in ghosts:
            dist_to_ghost = self.mdp.manhattan_distance(pacman_state.id, ghost.state.id)
            if dist_to_ghost < closest_to_ghost:
                closest_to_ghost = dist_to_ghost

        #Normalize        
        return self.normalize_distance(closest_to_ghost)
    
    #FEATURE 4
    def get_inverse_of_distance_to_closest_ghost(self, pacman, ghosts):
        dist = self.get_distance_to_closest_active_ghost(pacman, ghosts)
        if dist == 0:
            return 0
        return 1/(dist + 1)

    
    #FEATURE 5
    def get_distance_to_closest_scared_ghost(self, pacman_state, ghosts):
        closest_to_scared = 99999
        for ghost in ghosts:
            if ghost.frightened:
                dist_to_ghost = self.mdp.manhattan_distance(pacman_state.id, ghost.state.id)
                if dist_to_ghost < closest_to_scared:
                    closest_to_scared = dist_to_ghost

        if closest_to_scared == 99999:
            closest_to_scared = 0

        #Normalize
        return self.normalize_distance(closest_to_scared)
    
    #FEATURE 6
    def get_number_of_scared_ghosts_nearby(self, pacman_state, ghosts):
        number = 0
        for ghost in ghosts:
            if ghost.frightened:
                dist_to_ghost = self.mdp.manhattan_distance(pacman_state.id, ghost.state.id)
                if dist_to_ghost == 1 or dist_to_ghost == 2:
                    number += 1

        #Normalize
        return self.normalize_ghosts(number)
    
    #FEATURE 7
    def get_min_distance_to_capsule(self, pacman_state):
        closest_to_capsule = 99999
        for capsule in self.mdp.states:
            if capsule.type == 3:
                dist_to_capsule = self.mdp.manhattan_distance(pacman_state.id, capsule.id)
                if dist_to_capsule < closest_to_capsule:
                    closest_to_capsule = dist_to_capsule
        
        if closest_to_capsule == 99999:
            closest_to_capsule = 0

        #Normalize
        return self.normalize_distance(closest_to_capsule)
    
    #FEATURE 8
    def get_min_distance_to_scared_ghost(self, pacman_state, ghosts):
        min_closest = 99999
        for ghost in ghosts:
            if ghost.frightened:
                dist_to_ghost = self.mdp.manhattan_distance(pacman_state.id, ghost.state.id)
                if dist_to_ghost < min_closest:
                    min_closest = dist_to_ghost
        
        if min_closest == 99999:
            min_closest = 0

        #Normalize
        return self.normalize_distance(min_closest)
    
    #FEATURE 9
    def get_number_of_capsules_when_ghost_nearby(self, pacman_state, ghosts):
        number = 0
        if self.get_number_of_active_ghosts_nearby(pacman_state, ghosts) > 0:
            for capsule in self.mdp.states:
                if capsule.type == 3:
                    number += 1

        #Normalize
        return self.normalize_capsules(number)
    
    def get_number_of_active_ghosts_nearby(self, pacman_state, ghosts):
        number = 0
        for ghost in ghosts:
            dist_to_ghost = self.mdp.manhattan_distance(pacman_state.id, ghost.state.id)
            if dist_to_ghost == 1 or dist_to_ghost == 2:
                number += 1
        return number
    
    #FEATURE 10
    def get_ghost_not_nearby_food_is_nearby(self, pacman_state, ghosts):
        no_ghost = self.get_number_of_active_ghosts_nearby(pacman_state, ghosts) == 0
        is_food = self.get_distance_to_closest_food(pacman_state) <= 2
        return float(no_ghost and is_food)

    #Value normalization
    def normalize_distance(self, dist):
        return dist / self.max_distance
    
    def normalize_ghosts(self, num):
        return num / self.mdp.map.num_of_ghosts
    
    def normalize_capsules(self, num):
        if self.mdp.map.total_energizers == 0:
            return 0
        return num / self.mdp.map.total_energizers
    
    def max_manhattan_distance(self):
        play_rows = self.mdp.map.ROWS - 2
        play_cols = self.mdp.map.COLUMNS - 2
        return play_rows + play_cols - 2
    

    def closest_food(self, state):

        possible = [(state.id, 0)]
        explored = set()
        
        #While there are possible tiles
        while possible:
            s_id, dist = possible.pop(0)
            if s_id in explored:
                continue
            explored.add(s_id)

            if self.mdp.states[s_id].has_pellet():
                return dist
            
            nbrs = self.mdp.get_legal_neighbours(s_id)
            for nbr_id in nbrs:
                possible.append(nbr_id, dist + 1)

        return None
    

#Normalization
#max_distance = FeaturesOld.max_manhattan_distance()