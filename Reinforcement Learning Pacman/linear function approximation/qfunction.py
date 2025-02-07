from qfunction_features import *
#from qfunction_oldfeatures import *

import random
import math

''' TABULAR Q LEARNING '''
class TabularQ:
    
    def __init__(self, mdp):
        self.bulk_update = False
        self.mdp = mdp

    #Q(s, a) = Q(s, a) + alpha * (R(s, a, s') + y * max a' Q(s', a') - Q(s, a))
    def update(self, state, action, next_state_id, unused_ghosts):
        #R(s, a, s') + y * max a' Q(s', a') - Q(s, a) 
        delta = self.bellman_update(state, action, next_state_id)

        #Q(s, a) = Q(s, a) + learning_rate * difference
        state.direction[action] += self.mdp.alpha * delta

        #Policy update
        state.v = max(state.direction)
        state.policy = state.direction.index(state.v)

    #R(s, a, s') + y * max a' Q(s', a') - Q(s, a)  
    def bellman_update(self, s, a, next_state_id, ghosts):
        return self.mdp.r(next_state_id, ghosts) + self.mdp.GAMMA * self.maxQ(next_state_id) - self.Q(s, a)
    
    #Returns Q value of (s, a) pair
    def Q(self, s, a):
        return s.direction[a]
    
    #Returns max Q value of next state
    def maxQ(self, s_id):
        return max(self.mdp.states[s_id].direction)
    
    #Returns state policy
    def get_policy(self, s, unused_ghosts):
        return s.policy
    

''' APPROXIMATE Q LEARNING (LINEAR FUNCTION APPROXIMATION) '''
class ApproximateQ(PaperExtractor):
    
    def __init__(self, mdp):
        self.bulk_update = True
        self.mdp = mdp
        self.NUM_FEATURES = self.get_number_of_feats()
        self.weights = [0.0 for _ in range(self.NUM_FEATURES)]
        self.feats = None
    
    def update_from_buffer(self, feats, delta):
        i = 0
        for key in feats:
            self.weights[i] += self.mdp.alpha * delta * feats[key]
            i += 1

    def update(self, state, action, next_state_id, ghosts):
     
        delta = self.bellman_update(state, action, next_state_id, ghosts)
        #print(delta)
        
        self.feats = self.get_features(state, action, ghosts)

        i = 0
        for key in self.feats:
            self.weights[i] += self.mdp.alpha * delta * self.feats[key]
            i += 1
            
        #Debug == show all actions after weight change
        for a in range(self.mdp.NUM_A):
            state.direction[a] = self.Q(state, a, ghosts)
       


    ''' R(s, a, s') + y * max a' Q(s', a') - Q(s, a) '''
    def bellman_update(self, s, a, next_state_id, ghosts):
        return  self.mdp.r(next_state_id, ghosts) + self.mdp.GAMMA * self.maxQ(next_state_id, ghosts) - self.Q(s, a, ghosts)


    ''' Returns Q value of (s, a) pair, based on features. '''
    def Q(self, s, a, ghosts):
        #Get features, given action a
        feats = self.get_features(s, a, ghosts)

        #Calculate approximate Q(s, a) = Σ [fi(s, a) * wi]
        q = 0.0
        i = 0
        for key in feats:
            q += feats[key] * self.weights[i]
            i += 1

        #q = 1/(1+math.e**(-q))   
        return q
    

    ''' Returns max Q value of next state, based on features '''
    def maxQ(self, s_id, ghosts):
        """ s = self.mdp.states[s_id]
        q = []
        for a in range(self.mdp.NUM_A):
            q.append(self.Q(s, a, ghosts))
        return max(q) """
        #Possible action vector
        s = self.mdp.states[s_id]
        legal = self.mdp.get_legal_actions(s)

        #Calculate Q(s, a) for legal actions
        q = []
        for a in legal: 
            q.append(self.Q(s, a, ghosts)) 

        return max(q)
        
    

    ''' Returns policy of a state, based on current features'''
    def get_policy(self, s, ghosts):
        #Possible action vector
        legal = self.mdp.get_legal_actions(s)

        #Calculate Q(s, a) for legal actions
        q = []
        for a in legal: 
            q.append(self.Q(s, a, ghosts)) 

        return legal[q.index(max(q))]