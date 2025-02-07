
RED = (255, 1, 0)
BLUE = (0, 255, 223)
ORANGE = (255, 183, 73)
PINK = (255, 185, 227)


AI_NORMAL = 0
AI_AGGRESSIVE = 1
AI_MIXED = 2


class SmallMap:
    def __init__(self):
        #Visual elements
        self.SCREEN_SIZE = (900, 720)
        self.OFFSET_X = 150
        self.OFFSET_Y = 150
        self.BORDER = 2
        self.BOX_SIZE = 75
        self.FONT = 10

        #Data elements
        self.name = "small.txt"
        self.ROWS = 7
        self.COLUMNS = 7

        #Strictly game elements
        self.total_pellets = 2
        self.total_energizers = 0
        self.start_id = 8
        self.num_of_ghosts = 1
        self.ghost_start_id = [33]
        self.ghost_AI = [AI_MIXED]
        self.ghost_color = [RED]


class MediumMap:
    def __init__(self):
        #Visual elements
        self.SCREEN_SIZE = (900, 720)
        self.OFFSET_X = 150
        self.OFFSET_Y = 150
        self.BORDER = 2
        self.BOX_SIZE = 75
        self.FONT = 10

        #Data elements
        self.name = "medium.txt"
        self.ROWS = 7
        self.COLUMNS = 8

        #Strictly game elements
        self.total_pellets = 4
        self.total_energizers = 0
        self.start_id = 8
        self.num_of_ghosts = 1
        self.ghost_start_id = [47]
        self.ghost_AI = [AI_MIXED]
        self.ghost_color = [RED]

    
class SmallClassicMap:
    def __init__(self):
        #Visual elements
        self.SCREEN_SIZE = (1250, 720)
        self.OFFSET_X = 50
        self.OFFSET_Y = 150
        self.BORDER = 2
        self.BOX_SIZE = 60
        self.FONT = 10

        #Data elements
        self.name = "smallClassic.txt"
        self.ROWS = 7
        self.COLUMNS = 20

        #Strictly game elements
        self.total_pellets = 55
        self.total_energizers = 2
        self.start_id = 68
        self.num_of_ghosts = 2
        self.ghost_start_id = [57, 78]
        self.ghost_AI = [AI_MIXED, AI_MIXED]
        self.ghost_color = [BLUE, RED]


class MediumClassicMap:
    def __init__(self):
        #Visual elements
        self.SCREEN_SIZE = (1050, 720)
        self.OFFSET_X = 50
        self.OFFSET_Y = 150
        self.BORDER = 2
        self.BOX_SIZE = 50
        self.FONT = 10

        #Data elements
        self.name = "mediumClassic.txt"
        self.ROWS = 11
        self.COLUMNS = 20

        #Strictly game elements
        self.total_pellets = 97
        self.total_energizers = 2
        self.start_id = 108
        self.num_of_ghosts = 2
        self.ghost_start_id = [93, 126]
        self.ghost_AI = [AI_NORMAL, AI_AGGRESSIVE]
        self.ghost_color = [BLUE, RED]


class CapsuleMap:
    def __init__(self):
        #Visual elements
        self.SCREEN_SIZE = (1200, 720)
        self.OFFSET_X = 50
        self.OFFSET_Y = 150
        self.BORDER = 2
        self.BOX_SIZE = 60
        self.FONT = 10

        #Data elements
        self.name = "capsule.txt"
        self.ROWS = 7
        self.COLUMNS = 19

        #Strictly game elements
        self.total_pellets = 23
        self.total_energizers = 3
        self.start_id = 61
        self.num_of_ghosts = 3
        self.ghost_start_id = [8, 71, 124]
        self.ghost_AI = [AI_NORMAL, AI_AGGRESSIVE, AI_AGGRESSIVE]
        self.ghost_color = [BLUE, RED, ORANGE]


class OpenMap:
    def __init__(self):
        #Visual elements
        self.SCREEN_SIZE = (1300, 720)
        self.OFFSET_X = 50
        self.OFFSET_Y = 150
        self.BORDER = 2
        self.BOX_SIZE = 50
        self.FONT = 10

        #Data elements
        self.name = "open.txt"
        self.ROWS = 9
        self.COLUMNS = 25

        #Strictly game elements
        self.total_pellets = 86
        self.total_energizers = 1
        self.start_id = 37
        self.num_of_ghosts = 1
        self.ghost_start_id = [202]
        self.ghost_AI = [AI_AGGRESSIVE]
        self.ghost_color = [RED]


class OriginalMap:
    def __init__(self):
        #Visual elements
        self.SCREEN_SIZE = (900, 800)
        self.OFFSET_X = 100
        self.OFFSET_Y = 150
        self.BORDER = 2
        self.BOX_SIZE = 25
        self.FONT = 10

        #Data elements
        self.name = "original.txt"
        self.ROWS = 27
        self.COLUMNS = 28

        #Strictly game elements
        self.total_pellets = 229
        self.total_energizers = 4
        self.start_id = 403
        self.num_of_ghosts = 0
        self.ghost_start_id = [283, 364, 391, 472]
        self.ghost_AI = [AI_AGGRESSIVE, AI_NORMAL, AI_AGGRESSIVE, AI_NORMAL]
        self.ghost_color = [RED, BLUE, PINK, ORANGE]