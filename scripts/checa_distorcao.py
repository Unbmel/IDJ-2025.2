from matplotlib import pyplot as plt
with open("data") as i_f:
    y = list(map(int,i_f.read().split(',')[:-1]))
    plt.plot(range(len(y)), y)
    plt.show()
