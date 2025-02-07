

class RunGame:
    
    # ----------------------------------- GAME LOOP -------------------------------------------------
    # -----------------------------------------------------------------------------------------------
    def update(self): 

        #Remove pellet if pacman is standing on it
        self.mdp.consume_pellet(self.agent.state)

        if self.game_victory():
            self.test_agent_after_training(True)
            self.end_episode()

        elif self.pacman_gets_eaten() or self.steps_taken > 200:
            self.test_agent_after_training(False)
            self.end_episode()

        else:

            #Take action (user input, follow policy or epsilon-greedy)
            self.agent.action = self.get_action(self.agent.game_state)
            
            #Pick a state after agent moves
            if self.action_was_made():

                self.steps_taken += 1

                for ghost in self.ghosts:
                    ghost.action = self.mdp.get_ghost_action(ghost.state, 
                                    ghost.previous_action, self.agent.state, ghost.AI)
                    ghost.previous_action = ghost.action
                    ghost.next_state = self.mdp.states[self.mdp.get_next_state_id(ghost.state, ghost.action)]

                next_state_id = self.get_next_state_id(self.ghosts) 

                #Q(s, a) = Q(s, a) + alpha * (R(s, a, s') + y * max a' Q(s', a') - Q(s, a))
                if self.training() or self.manual():

                    #R(s, a, s') + y * max a' Q(s', a') - Q(s, a)
                    delta = self.bellman_update(self.agent.game_state, self.agent.action, next_state_id)

                    #Update q function
                    self.q_function.update(self.agent.game_state, self.agent.action, delta, self.ghosts)
        
                    #Update policy
                    self.update_policy(self.agent.game_state)

                #Total reward to measure agent's progress
                self.total_reward += self.mdp.r_gamestate(next_state_id, self.ghosts)
                self.total_reward_paper += self.mdp.r_gamestate(next_state_id, self.ghosts)

                #Set state to new state
                self.update_states(next_state_id, self.ghosts)

    def test_agent_after_training(self, won):
        if self.testing() and self.plot_option == 0:
            self.play_ep += 1
            if won:
                self.won_ep += 1
            if self.play_ep == 500:
                print(f"Ep[{self.play_ep}] Win {self.won_ep / self.play_ep * 100:.2f}% Avg. score {self.total_reward_paper / self.play_ep}")
                exit()

    #R(s, a, s') + y * max a' Q(s', a') - Q(s, a)
    def bellman_update(self, game_state, action, next_state_id):
        return self.mdp.r_gamestate(next_state_id, self.ghosts) + self.mdp.GAMMA * \
                max(self.mdp.game_states[next_state_id].direction) - game_state.direction[action]
    

    def pacman_gets_eaten(self):
        for ghost in self.ghosts:
            if self.agent.state.id == ghost.state.id:
                return True
        return False
    
    def game_victory(self):
        return self.mdp.consumed_pellets == self.mdp.map.total_pellets
    

    #-------------------------------------------------------------------------------------------------------------------
    #-------------------------------------------------------------------------------------------------------------------
    #-------------------------------------------------------------------------------------------------------------------
    
    def get_action(self, state):
        if self.training():
            return self.mdp.epsilon_greedy(state)
        if self.testing():
            return state.policy 
        return self.agent.action
    
    def get_next_state_id(self, ghosts):
        return self.mdp.get_next_gamestate(self.agent.game_state, self.agent.action, ghosts) 
    
    # UPDATE -----------------------------------------------------------------------------------

    def update_policy(self, state):
        state.v = max(state.direction)
        state.policy = state.direction.index(state.v)

    def update_states(self, next_state_id, ghosts = None):
        self.agent.game_state = self.mdp.game_states[next_state_id]
        self.agent.state = self.mdp.states[self.agent.game_state.info[0]]
        for i in range (len(self.ghosts)):
            self.ghosts[i].state = self.ghosts[i].next_state


    # ----------------------------------- SHORTCUTS -------------------------------------------------
    # -----------------------------------------------------------------------------------------------
    def manual(self):
        return self.mode == 0
    
    def training(self):
        return self.mode == 1
    
    def testing(self):
        return self.mode == 2
    
    def action_was_made(self):
        return self.agent.action is not None
    
    def training_batch_done(self):
        return self.episodes % self.training_episodes == 0
    
    def testing_batch_done(self):
        return self.test_counter == self.testing_episodes
    
    def plot_total_rewards(self):
        return self.plot_option_is_total() and self.training_batch_done()
    
    def plot_option_is_average(self):
        return self.plot_option == 1
    
    def plot_option_is_total(self):
        return self.plot_option == 0
    
    def switch_to_testing(self):
        self.mode = 2

    def switch_to_training(self):
        self.mode = 1

    
    #-------------------------------------------------------------------------------------------------------------------
    #-------------------------------------------------------------------------------------------------------------------
    #-------------------------------------------------------------------------------------------------------------------
    
    #Reset environment
    def end_episode(self):
        #Reset starting state
        self.agent.state = self.mdp.get_start_state()
        self.agent.game_state = self.mdp.get_start_gamestate()

        for ghost in self.ghosts:
            ghost.state = self.mdp.get_ghost_start_state(ghost.index)
            ghost.previous_action = 0

        #Plot every episode
        if self.plot_total_rewards():
            self.plot.x.append(self.episodes)
            self.plot.y.append(self.total_reward)

            self.sum_rewards += self.total_reward

            self.plot.a.append(self.mdp.alpha)
            self.plot.e.append(self.mdp.EPSILON)
            self.plot.won.append(self.games_won)
        #Plot every x episodes
        else:
            if self.training() and self.training_batch_done():
                self.switch_to_testing()
                self.test_counter = -1
                self.total_reward = self.mdp.consumed_pellets = 0
        
            if self.testing() and self.testing_batch_done():
                self.switch_to_training()
                self.test_counter = 0
                
                self.plot.x.append(self.episodes)
                self.plot.y.append(self.avg_reward / self.testing_episodes)
                self.plot.a.append(self.mdp.alpha)
                self.plot.e.append(self.mdp.EPSILON)
                self.plot.won.append(self.games_won / self.testing_episodes)

                if (self.games_won / self.testing_episodes) > self.most_won:
                    self.most_won = (self.games_won / self.testing_episodes)
                    print(self.episodes)

                self.avg_reward = 0
                self.games_won = 0

            if self.testing():
                self.avg_reward += self.total_reward
                self.test_counter += 1

                if self.mdp.map.total_pellets == self.mdp.consumed_pellets:
                    self.games_won += 1

        if not self.testing():
            self.episodes += 1
            self.mdp.decay_a()
            self.mdp.decay_epsilon()
        self.total_reward = 0

        self.mdp.reset()
        self.steps_taken = 0