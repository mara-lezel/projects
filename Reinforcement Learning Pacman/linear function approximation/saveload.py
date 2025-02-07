import glob
import os
import datetime

from state import *

#Parent class for Controller
class SaveLoad:

    #Save game weight information
    def save_game_weights(self, file_name = None):
        file_name = self.get_generated_file_name(file_name)
        file_path = os.path.join("/Users/mara/Desktop/KP kodas/linear function approximation/game_weights", file_name)
        #self.write_weights_to_file(file_path, self.q_function.weights)
        self.write_weights_to_file(file_path, self.most_w)
       

    #Generate file name or return already given
    def get_generated_file_name(self, file_name):
        now = datetime.datetime.now().time()
        t = "AVG" if self.plot_option_is_average() else "CML"

        if file_name == None:
            file_name = f"{self.counter} - {t}[{self.testing_episodes}] E{self.episodes-1} "
            file_name += f"X{self.training_episodes}            " + now.__str__() + ".txt"

        return file_name

     #Open file and write state information
    def write_weights_to_file(self, file_path, weights):
        f = open(file_path, "w")
        for w in weights:
            f.write(f"{w}")
            f.write("\n")
        f.write(f"{self.most_ep}")
        f.close()

    # -----------------------------------------------------------------------------------------------
    #Loads game weights from file
    def load_game_weights(self, file_name = None):       
        file_name = self.get_recent_file_name(file_name)
        self.load_weights_from_file(file_name, self.q_function.weights)

    #Returns most recent file
    def get_recent_file_name(self, file_name):
        folder = "game_weights/"
        folder_files = "game_weights/*.txt"

        #Get most recent file or specified file
        if file_name == None or file_name == 0:
            list_of_files = glob.glob(folder_files)
            latest_file = max(list_of_files, key = os.path.getctime)
            file_name = latest_file
        elif isinstance(file_name, int):
            list_of_files = glob.glob(folder_files)
            for file in list_of_files:
                if file.startswith(folder + str(file_name)):
                    file_name = file
                    break
        else:
            file_name = folder + file_name

        return file_name

    #Open file and read weights
    def load_weights_from_file(self, file_name, weights):
        f = open(file_name, "r")
        lines = f.readlines()

        i = 0
        for line in lines:
            if i < len(weights):
                numbers = [float(e) for e in line.split()]
                weights[i] = numbers[0]
                i += 1
            else:
                numbers = [float(e) for e in line.split()]
                self.episodes = int(numbers[0])
        f.close()

    # -----------------------------------------------------------------------------------------------
    def read_counter(self):
        f = open("data/counter", "r")
        counter = int(f.read())
        f.close()
        return counter
    
    def save_counter(self):
        f = open("data/counter", "w")
        f.write(f"{self.counter+1}")
        f.close()

    # ----------------------------------- SHORTCUTS -------------------------------------------------
    # -----------------------------------------------------------------------------------------------
    def save(self):
        self.save_game_weights()
        self.save_counter()

    def load(self):
        self.load_game_weights(self.file_nr)