import matplotlib.pyplot as plt
import datetime

class Plotting:
    def __init__(self, epsilon_alpha):
        self.x = []
        self.y = []

        self.a = []
        self.e = []
        self.won = []

        self.epsilon, self.alpha = epsilon_alpha

    def write_paper(self, file_path, weights):
        f = open(file_path, "w")
        for w in weights:
            f.write(f"{w}")
            f.write("\n")
        f.close()

    def get_ema(self, rewards, smoothing_factor=0.99):
        smoothed_rewards = []
        for reward in rewards:
            if smoothed_rewards == []:
                smoothed_rewards = [reward]
            else:
                smoothed_rewards += [
                    smoothed_rewards[-1] * smoothing_factor
                    + reward * (1 - smoothing_factor)
                ]
        return smoothed_rewards

    def plot(self, setting, r, grid, counter, play_count = 1, show = False):
        
        fig, host = plt.subplots(figsize=(8,5), layout='constrained') # (width, height) in inches

        #self.y = self.won
        self.won = self.get_ema(self.y)

        file1 = "/Users/mara/Desktop/KP kodas/linear function approximation/data/atlygis" + str(grid) + ".txt"
        file2 = "/Users/mara/Desktop/KP kodas/linear function approximation/data/noise" + str(grid) + ".txt"

        self.write_paper(file1, self.won)
        self.write_paper(file2, self.y)

        title = None
        ylabel = None
        match setting:
            case "CML":
                ylabel = "Total reward"
                title = f"Total Reward per Episode   [{grid}]"
            case "AVG":
                ylabel = "Average reward"
                title = f"Average Reward after {play_count} test runs   [{grid}]"
        title += f"\nepsilon={self.epsilon}  alpha={self.alpha}"

        plt.title(title)
            
        ax2 = host.twinx()
        ax3 = host.twinx()
        ax4 = host.twinx()
            
        host.set_xlabel("Episodes")
        host.set_ylabel(ylabel)
        ax4.set_ylabel("Win %")
        #ax4.set_ylim(-600, 525) #-0.05, 1.05

        if show:
            ax2.set_ylabel("Learning Rate")
            ax3.set_ylabel("Exploration Rate")

        if not show:
            ax2.set_zorder(-1)
            ax3.set_zorder(-1)

        color1, color2, color3, color4 = plt.cm.viridis([0.3, .6, .9, .99])

        p1 = host.plot(self.x, self.y, color = color1, label = "Reward", alpha=0.2)
        p4 = ax4.plot(self.x, self.won, color = color1, label = "Win %")

        if show:
            p2 = ax2.plot(self.x, self.a, color = color2, label = "Alpha")
            p3 = ax3.plot(self.x, self.e, color = color3, label = "Epsilon")

        if show:
            ax4.legend(handles=p1+p3+p4, loc='center', bbox_to_anchor=[0.9, 0.2])

            ax3.spines['right'].set_position(('outward', 70))
            ax4.spines['right'].set_position(('outward', 130))

            host.yaxis.label.set_color(p1[0].get_color())
            ax2.yaxis.label.set_color(p2[0].get_color())
            ax3.yaxis.label.set_color(p3[0].get_color())
            ax4.yaxis.label.set_color(p4[0].get_color())
        else:
            ax4.legend(handles=p1+p4, loc='center', bbox_to_anchor=[0.9, 0.2])

            ax4.spines['right'].set_position(('outward', 70))

            host.yaxis.label.set_color(p1[0].get_color())
            ax4.yaxis.label.set_color(p4[0].get_color())


        now = datetime.datetime.now().time()
        file_name = f"{counter} - {setting}[{play_count}] E{self.x[-1]} X{self.x[0]}            " + now.__str__()

        plt.savefig(f"plots/{file_name}.png", dpi=300, bbox_inches='tight')