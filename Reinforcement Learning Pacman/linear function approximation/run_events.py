import pygame

class RunEvents:
    # ----------------------------------- USER INPUT ------------------------------------------------
    # -----------------------------------------------------------------------------------------------
    def checkEvents(self):
        
        self.agent.action = None
        # Proccess user input
        for event in pygame.event.get():

            #Window actions
            if event.type == pygame.QUIT:
                exit()

            #Keyboard actions
            if event.type == pygame.KEYDOWN:

                #Working with data options
                if event.key == pygame.K_SPACE:
                    self.paused = not self.paused
                if event.key == pygame.K_RIGHT:
                    self.one_movement = True
                if event.key == pygame.K_ESCAPE:
                    exit()
                if event.key == pygame.K_s:
                    self.save()
                if event.key == pygame.K_l:
                    self.load()
                if event.key == pygame.K_p:
                    self.plot_results()
                if event.key == pygame.K_m:
                    self.slow = not self.slow

                #Value display options
                if event.key == pygame.K_3:
                    self.use_policy = True
                if event.key == pygame.K_1:
                    self.show_directional_values = False
                    self.use_policy = False
                if event.key == pygame.K_2:
                    self.show_directional_values = True
                    self.use_policy = False
                if event.key == pygame.K_0:
                    self.hide_all = True

                #Manual player movement
                if event.key == pygame.K_UP:
                    self.agent.action = 0
                if event.key == pygame.K_RIGHT:
                    self.agent.action = 1
                if event.key == pygame.K_DOWN:
                    self.agent.action = 2
                if event.key == pygame.K_LEFT:
                    self.agent.action = 3