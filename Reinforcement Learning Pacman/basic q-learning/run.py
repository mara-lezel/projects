

from saveload import *
from agent import *

from plotting import *
from draw import *

from argparser import *

from qfunction import *

from pacman_mdp import *
from run_game import *
from run_events import *
from map import *

class Controller(SaveLoad, RunEvents, RunGame):
    def __init__(self, args):
        pygame.init()

        self.clock = pygame.time.Clock()
        self.args = args

        self.counter = self.read_counter()
        self.file_nr = args.get_l()

        self.mdp = PacGrid(self.set_map(), self.args)
        self.draw = Draw(self.mdp.map.SCREEN_SIZE, self.mdp.map.BOX_SIZE, self.mdp.map.BORDER, self.mdp.map.FONT)
        self.agent = Agent(self.mdp.get_start_state(), self.mdp.get_start_gamestate())
        self.ghosts = self.create_ghosts()

        self.q_function = TabularQ(self.mdp)
        self.mode = self.set_mode(args.get_m())

        self.plot = Plotting(self.mdp.get_epsilon_alpha())
        self.episodes = 0
        self.total_reward = 0

        #Flags
        self.running = True
        self.paused = False
        self.use_policy = False
        self.show_directional_values = True
        self.hide_all = False
        
        #Setup args
        self.render_graphics = args.get_r()
        self.max_ep = args.get_n()

        #Plots
        self.avg_reward = 0
        self.games_won = 0
        self.test_counter = 0

        self.plot_option = args.get_p()
        self.testing_episodes = 50
        self.training_episodes = args.get_x()

        self.play_ep = 0
        self.won_ep = 0
        self.most_won = 0
        self.steps_taken = 0
        self.sum_rewards = 0

        #DEBUG
        self.debug_info = []
        self.total_reward_paper = 0

    # ----------------------------------- INITIALIZE ------------------------------------------------
    # -----------------------------------------------------------------------------------------------
            
    def set_map(self):
        match self.args.get_map():
            case 0:
                return SmallMap()
            case 1:
                return MediumMap()
            case 2:
                return SmallClassicMap()
            case 3:
                return MediumClassicMap()
            case 4:
                return OpenMap()
            case 5:
                return CapsuleMap()
            case 6:
                return OriginalMap()
            
    def set_mode(self, mode):
        self.mode = mode
        if self.testing():
            self.load()
        return self.mode
            
    def create_ghosts(self):        
        ghosts = []
        for i in range (self.mdp.map.num_of_ghosts):
            ghosts.append(Ghost(i, self.mdp.get_ghost_start_state(i), self.mdp.map.ghost_AI[i], 
                                self.mdp.map.ghost_color[i]))
        return ghosts
    

    def limit_episodes(self):
        if self.episodes == self.max_ep and self.max_ep != 0:
            self.running = False
            self.save()

    

    #Plot results based on option
    def plot_results(self):
        """ if self.plot_option_is_total():     
            self.plot.plot("CML", self.mdp.r(), self.args.get_map(), self.counter)

        if self.plot_option_is_average():
            self.plot.plot("AVG", self.mdp.r(), self.args.get_map(), self.counter, self.testing_episodes) """

        print(self.sum_rewards / self.episodes)
        f = open('/Users/mara/Desktop/KP kodas/basic q-learning/data/test.txt', "a+")
        f.write(f"{self.sum_rewards / self.episodes}")
        f.write("\n")
        f.close()

    # ----------------------------------- EVENT LOOP ------------------------------------------------
    # -----------------------------------------------------------------------------------------------
    def run(self):
        while self.running:
            self.checkEvents()

            if not self.paused:
                self.update()

            if self.render_graphics:
                self.render()

            self.limit_episodes()
            self.wait()
        self.plot_results()


    #Slow down visual effects to see how agent works
    def wait(self):
        if self.testing() and self.plot_option == 0 and self.render_graphics == 1:
            pygame.time.wait(200)

    # ----------------------------------- RENDER ----------------------------------------------------
    # -----------------------------------------------------------------------------------------------
    def render(self):
        self.draw.clear()
        self.render_states()

        self.draw.draw_text_big("Tabular Q Learning", 100, 50)
        self.draw.draw_text_big(f"Episode = {self.episodes}", 100, 100)
        self.draw.draw_text_big(f"Score = {self.total_reward:.2f}", 300, 100)
        self.draw.draw_text_big(f"y = {self.mdp.GAMMA}", 500, 100)
        self.draw.draw_text_big(f"alpha = {self.mdp.alpha:.3f}", 600, 100)
        self.draw.draw_text_big(f"epsilon = {self.mdp.EPSILON:.3f}", 750, 100)
        
        self.draw.draw_agent(self.agent)

        for ghost in self.ghosts:
            self.draw.draw_agent(ghost, Color(ghost.color))
                
        pygame.display.flip()  # Refresh on-screen display
        self.clock.tick(60) # 60 fps   

    def render_states(self):
        for state in self.mdp.states:
            self.draw.draw_state(state, self.use_policy, self.show_directional_values, 
                                gs=self.agent.game_state)
     
        
# ----------------------------------------------------------------------------------------------------------
if __name__ == "__main__":
    parser = ArgParser()

    envi = Controller(parser)
    envi.run()