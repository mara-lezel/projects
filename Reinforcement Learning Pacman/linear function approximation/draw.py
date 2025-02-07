import pygame

Color = pygame.Color

class Draw:
    def __init__(self, SCREEN_SIZE, BOX_SIZE, BORDER, FONT):
        self.screen = pygame.display.set_mode(SCREEN_SIZE)
        self.box_size = BOX_SIZE
        self.border_width = BORDER
        self.font = pygame.font.SysFont('Sans', FONT)
        self.big_font = pygame.font.SysFont('Sans', 10)
        self.surface = None
        self.rect = None

        pygame.display.set_caption("Approximate Q Learning")

    def clear(self, color = Color(255,255,255)):
        self.screen.fill(color)

    def draw_agent(self, agent, color = Color(0, 0, 0)):
        self.draw_fill(agent.state.x + self.box_size * 0.36, agent.state.y + self.box_size * 0.4, 
                       agent.state.len * 0.25, color)
        
    def draw_state(self, state, use_policy, show_directional_values, hide, approx = None):
        if state.blocked: #BLOCKED STATE 
            self.draw_fill(state.x, state.y, state.len, state.color)
        elif state.terminal: #TERMINAL STATE
            self.draw_fill(state.x, state.y, state.len, state.color)
            self.draw_text(f"{state.v:.2f}", state.center_x, state.center_y, (0, 0, 0), state.color)
        else:
            if state.type == 2 or state.type == 3: #PELLET
                self.draw_fill_tiny(state.x, state.y, state.len, state.color)

            #If game, render values only for that game state in its physical location
            if approx != None:
                if use_policy and approx == state.id:
                    self.draw_policy(state)
                elif approx == state.id:
                    self.draw_values(state, show_directional_values)
            elif use_policy:
                self.draw_policy(state)                       
            else:
                if not hide:
                    self.draw_values(state, show_directional_values)              
        self.draw_rect(state.x, state.y, state.len)


    def draw_policy(self, state):
        match state.policy:
            case 0:
                self.draw_text("  ↑", state.center_x, state.center_y)                           
            case 1:
                self.draw_text("  →", state.center_x, state.center_y)                           
            case 2:
                self.draw_text("  ↓", state.center_x, state.center_y)                           
            case 3:
                self.draw_text("  ←", state.center_x, state.center_y)

    def draw_values(self, state, show_directional_values):
        SHFT_X = self.box_size * 0.3
        SHFT_Y = self.box_size / 3             
        if show_directional_values:
            self.draw_text(f"{state.direction[0]:.2f}", state.center_x, state.center_y - SHFT_Y)
            self.draw_text(f"{state.direction[1]:.2f}", state.center_x + SHFT_X, state.center_y)
            self.draw_text(f"{state.direction[2]:.2f}", state.center_x, state.center_y + SHFT_Y)
            self.draw_text(f"{state.direction[3]:.2f}", state.center_x - SHFT_X, state.center_y)
            #self.draw_text(f"{state.id}", state.center_x - SHFT_X, state.center_y)
            pygame.draw.line(self.screen, Color(0,0,0), (state.x, state.y), (state.x + state.len, state.y + state.len))
            pygame.draw.line(self.screen, Color(0,0,0), (state.x + state.len, state.y), (state.x, state.y + state.len))
        else:
            self.draw_text(f"{state.v:.2f}", state.center_x, state.center_y)
    
    def draw_text(self, text, x, y, fg_color = (0, 0, 0), bg_color = (255, 255, 255)):
        self.surface = self.font.render(text, 1, fg_color, bg_color)
        self.screen.blit(self.surface, (x, y))

    def draw_text_big(self, text, x, y, fg_color = (0, 0, 0), bg_color = (255, 255, 255)):
        self.surface = self.big_font.render(text, 1, fg_color, bg_color)
        self.screen.blit(self.surface, (x, y))

    def draw_fill(self, x, y, len, color):
        self.rect = pygame.Rect(x, y, len, len)
        self.screen.fill(color, self.rect)

    def draw_fill_tiny(self, x, y, len, color):
        len /= 5
        x += 29
        y += 32
        self.rect = pygame.Rect(x, y, len, len)
        self.screen.fill(color, self.rect)

    def draw_rect(self, x, y, len, color = Color(0, 0, 0)):
        self.rect = pygame.Rect(x, y, len, len)
        pygame.draw.rect(self.screen, color, self.rect, self.border_width)