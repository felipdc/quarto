import pandas as pd
import matplotlib.pyplot as plt

def plot_time_depht():

    data = pd.read_csv("time-depht.csv", decimal='.')
    plt.scatter(data["depht"], data["time"], color = 'black')
    plt.loglog(data["depht"], data["time"], basex= 2)
    plt.xlabel("Depht")
    plt.ylabel("Processing time")
    plt.title("Depht x Processing time")
    plt.show()
    
plot_time_depht()
