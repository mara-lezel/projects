

class TabularQ:
    
    def __init__(self, mdp):
        self.bulk_update = False
        self.mdp = mdp

    #Q(s, a) = Q(s, a) + alpha * (R(s, a, s') + y * max a' Q(s', a') - Q(s, a))
    def update(self, state, action, delta, unused_ghosts):
        state.direction[action] += self.mdp.alpha * delta