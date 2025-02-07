""" from run import *

if __name__ == "__main__":
    parser = ArgParser()

    lr = ['0.001', '0.005', '0.01', '0.05', '0.1', '0.2', '0.3', '0.4', '0.5']  # Learning rates
    er = ['0.1', '0.2', '0.3', '0.4', '0.5', '0.6', '0.7', '0.8', '0.9']  # Exploration rates

    for i in range(9):
        print('-------------------------------------------------------- LR = ' + lr[i])
        parser.args.alpha = float(lr[i])
        for j in range(9):
            parser.args.epsilon = float(er[i])
            envi = Controller(parser)
            envi.run() """


import os

lr = ['0.001', '0.005', '0.01', '0.05', '0.1', '0.2', '0.3', '0.4', '0.5']  # Learning rates
er = ['0.1', '0.2', '0.3', '0.4', '0.5', '0.6', '0.7', '0.8', '0.9']  # Exploration rates

for i in range(9):
    for j in range(9):
        os.system("python3 run.py -m 1 -r 0 -n 5000" + " -e " + er[j] + " -a " + lr[i])