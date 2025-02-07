import copy
import random

class RunGame:
    
    '''
    ------------------------------------------------ UPDATE LOOP ---------------------------------------------------------------
    ----------------------------------------------------------------------------------------------------------------------------
    '''
    def update(self): 

        #If Pacman eats all the pellets
        if self.game_victory():
            self.test_agent_after_training(won=True)
            self.last_won = True
            self.end_episode()

        #If Pacman gets eaten by a ghost
        elif self.pacman_gets_eaten() or self.steps_taken > 200:
            self.test_agent_after_training(won=False)
            self.last_won = False
            self.end_episode()

        else:
            #Respawn eaten ghost if needed
            self.ghost_gets_eaten()

            #Take action (user input, follow policy or epsilon-greedy)
            self.agent.action = self.get_action(self.agent.state)
            
            #Pick a state after agent moves
            if self.action_was_made():

                self.agent.last_action = self.agent.action 
                self.steps_taken += 1
                self.seen = False

                for ghost in self.ghosts:
                    ghost.action = self.mdp.get_ghost_action(ghost.state, 
                                    ghost.previous_action, self.agent.state, ghost.AI)
                    ghost.previous_action = ghost.action
                    ghost.next_state = self.mdp.states[self.mdp.get_next_state_id(ghost.state, ghost.action)]

                #Get next state id
                next_state_id = self.mdp.get_next_pacman_state_id(self.agent.state, self.agent.action, self.ghosts)

                #self.q_function.feats = self.q_function.get_features(self.agent.state, self.agent.action, self.ghosts)
                #DEBUG
                self.add_debug_info()

                #Update q function
                if self.training() or self.manual():
                    self.q_function.update(self.agent.state, self.agent.action, next_state_id, self.ghosts)
                
                #Total reward to measure agent's progress
                self.total_reward += self.mdp.r(next_state_id, self.ghosts)
                self.total_rewards_paper += self.mdp.r(next_state_id, self.ghosts)

                #print(self.episodes)
                #Set state to new state
                self.agent.state = self.mdp.states[next_state_id]
                for i in range (len(self.ghosts)):
                    if self.ghosts[i].frightened and self.ghosts[i].scared_timer % 2 == 0:
                        None
                    else:
                     self.ghosts[i].state = self.ghosts[i].next_state
                
                #Remove pellet if pacman is standing on it
                self.mdp.consume_pellet(self.agent.state)

                #Scared ghost control
                self.scared_ghost_logic()



    def experience_replay(self, next_state_id, feats, delta):
        #(s, a, s', r)
        if self.mdp.r(next_state_id, self.ghosts) > 0:
            self.pos_buffer.append((feats, delta))
        else:
            self.neg_buffer.append((feats, delta))

        buffer = None
        if self.episodes % 2 == 0 or len(self.neg_buffer) == 0:
            buffer = self.pos_buffer
        else:
            buffer = self.neg_buffer

        f, d = random.choice(buffer)
        self.q_function.update_from_buffer(f, d)

    
    '''
    Selects action to take -- epsilon greedy strategy.
     - In testing mode, always uses action from policy
     - In training mode, occasionally selects greedy (random) action 
    '''
    def get_action(self, state):
        if self.training():
            greedy = self.mdp.epsilon_greedy(state) 
            if greedy == -1:
                return self.q_function.get_policy(state, self.ghosts)
            self.greedy_was_chosen = True if greedy != -1 else False
            return greedy
        
        if self.testing():
            return self.q_function.get_policy(state, self.ghosts)
        
        return self.agent.action
    

    '''
    Calculates test game results.
    '''
    def test_agent_after_training(self, won):
        if self.args.get_m() == 2:
            self.play_ep += 1
            if won:
                self.won_ep += 1
            if self.play_ep == 500:
                print(f"Ep[{self.play_ep}] Win {(self.won_ep / self.play_ep) * 100:.2f}% Avg. score {self.total_rewards_paper / self.play_ep}")
                exit()

    
    '''
    Adds feature info for debugging later.
    '''
    def add_debug_info(self):

        self.debug_info = []
        self.debug_weights = []

        if self.q_function.feats == None:
            return
        
        
        feats = self.q_function.feats
        weights = self.q_function.weights
        i = 0
        for key in feats:
            self.debug_info.append(key + f" [{feats[key]:.3f}] [{weights[i]:.3}]")
            self.debug_weights.append(feats[key])
            i += 1

        """ #Features
        sep = 0
        num_feats = self.q_function.NUM_FEATURES
        feats = self.q_function.feats
        for f in feats:
            if sep == 0:
                self.debug_info.append(f"[{feats[f]:.3f}]")
            elif sep % num_feats == 1:
                self.debug_info.append(f"[{feats[f]:.3f}, ")
            elif sep % num_feats == 0:
                self.debug_info[-1] += f"{feats[f]:.3f}]"
            else:
                self.debug_info[-1] += f"{feats[f]:.3f}, "
            sep += 1
        
        #Weights
        sep = 0
        for w in self.q_function.weights:
            if sep == 0:
                self.debug_weights.append(f"[{w:.3f}]")
            elif sep % num_feats == 1:
                self.debug_weights.append(f"[{w:.3f}, ")
            elif sep % num_feats == 0:
                self.debug_weights[-1] += f"{w:.3f}]"
            else:
                self.debug_weights[-1] += f"{w:.3f}, "
            sep += 1
 """
    
    '''
    -------------------------------------------------------- END EPISODE -------------------------------------------------
    ----------------------------------------------------------------------------------------------------------------------
    '''
    def end_episode(self):
        #print(self.episodes)
        #Reset starting states
        self.agent.state = self.mdp.get_start_state()
        for ghost in self.ghosts:
            self.reset_ghost(ghost)

        #Append episode data for plotting
        self.add_plot_data_after_episode()

        #Increment training episodes 
        if not self.testing():
            self.episodes += 1
            self.mdp.decay_a()
            self.mdp.decay_epsilon()

        #Reset environment
        self.steps_taken = 0
        self.total_reward = 0
        self.mdp.reset()


    '''
    Appends relevant data to the plot, based on current plot scheme.
    '''
    def add_plot_data_after_episode(self):

        #Show results after every episode, no testing
        if self.plot_total_rewards():
            self.plot.x.append(self.episodes)
            self.plot.y.append(self.total_reward)

            self.plot.a.append(self.mdp.alpha)
            self.plot.e.append(self.mdp.EPSILON)
            self.plot.won.append(self.games_won)
            if self.total_reward > self.most_won:
                self.most_won = self.total_reward
                self.most_w = self.q_function.weights
            self.most_w = self.q_function.weights
              

        #Show results after a number of episodes of training, 
        #averaged over some amount of test plays
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
                    self.most_w = copy.deepcopy(self.q_function.weights)
                    self.most_ep = self.episodes
                    #self.save_game_weights()

                self.avg_reward = 0
                self.games_won = 0

            if self.testing():
                self.avg_reward += self.total_reward
                self.test_counter += 1

                if self.mdp.map.total_pellets == self.mdp.consumed_pellets:
                    self.games_won += 1
    

    '''
    -------------------------------------------------------- SHORTCUTS -------------------------------------------------
    --------------------------------------------------------------------------------------------------------------------
    '''
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

    
    '''
    -------------------------------------------------------- GAME ------------------------------------------------------
    --------------------------------------------------------------------------------------------------------------------
    '''
    def pacman_gets_eaten(self):
        for ghost in self.ghosts:
            if self.agent.state.id == ghost.state.id and not ghost.frightened:
                return True
        return False
    
    def ghost_gets_eaten(self):
        for ghost in self.ghosts:
            if self.agent.state.id == ghost.state.id and ghost.frightened:
                self.reset_ghost(ghost)
                return True
        return False
    
    def game_victory(self):
        return self.mdp.consumed_pellets == self.mdp.map.total_pellets
    
    '''
    If Pacman consumes a power pellet, ghosts become frightened:
     - AI is set to random movement
     - Color changes to white
     - They become vulnerable to Pacman, and can be eaten
     - Eaten ghosts return to their starting spot, no longer frightened
    '''
    def scared_ghost_logic(self):
        #Scared ghost behaviour
        if self.mdp.energizer_consumed:
            self.mdp.energizer_consumed = False
            for g in self.ghosts:
                g.frightened = True
                g.scared_timer = 40
                g.color = (241, 235, 237)
                g.AI = 0

        for g in self.ghosts:
            if g.scared_timer == 0:
                self.reset_ghost(g, eaten=False)
            if g.scared_timer > 0:
                g.scared_timer -= 1

    '''
    Resets the ghost to its original configuration.
    '''
    def reset_ghost(self, ghost, eaten = True):
        #Move ghost to starting spot, if he was eaten
        if eaten:
            ghost.state = self.mdp.get_ghost_start_state(ghost.index)
        ghost.previous_action = 0
        ghost.frightened = False
        ghost.scared_timer = -1
        ghost.color = self.mdp.map.ghost_color[ghost.index]
        ghost.AI = self.mdp.map.ghost_AI[ghost.index]