import numpy as np
import matplotlib.pyplot as plt
import os
import sys




def main():
    if len(sys.argv) != 3:
        sys.exit("python plot_test_case.py <test_case.in> <plot_indices?: 0 or 1>")

    test_case    = sys.argv[1]
    plot_indices = bool(int(sys.argv[2]))

    f = open(test_case, "r")

    line = f.readline().split("\n")[0].split(" ")
    n_train = int(line[0])
    n_test  = int(line[1])

    Xtrain = [[], []] # [0] = reprovados, [1] = aprovados
    Xtest  = []

    # read the training set
    for i in range(n_train):
        line = f.readline().split("\n")[0].split(" ")

        nota_media   = float(line[0])
        horas_estudo = float(line[1])
        label        = int(line[2])

        Xtrain[label].append((nota_media, horas_estudo))


    # read the testing set
    for i in range(n_test):
        line = f.readline().split("\n")[0].split(" ")

        nota_media   = float(line[0])
        horas_estudo = float(line[1])

        Xtest.append((nota_media, horas_estudo))
    f.close()
    

    plt.axis([0, 10.0, 0, 10])
    plt.xticks(np.arange(0.0, 11.0, 1))
    plt.yticks(np.arange(0.0, 11.0, 1))
    plt.grid(True, linestyle='--')
    plt.xlabel('nota media')
    plt.ylabel('horas de estudos semanais')

    x0, y0 = zip(*Xtrain[0]) # return two lists, one with the x-coords and another with y-coords
    x1, y1 = zip(*Xtrain[1])
    x2, y2 = zip(*Xtest)

    rep  = plt.scatter(x0, y0, c='r', clip_on=False) # clip_on=False allows the points over the lines
    apr  = plt.scatter(x1, y1, c='g', clip_on=False)
    test = plt.scatter(x2, y2, marker="x", c='b', clip_on=False)

    # plot the indices from the train samples
    if (plot_indices):
        for i in range(len(Xtrain[0])):
            plt.annotate(i, Xtrain[0][i])
        for i in range(len(Xtrain[1])):
            plt.annotate(i+len(Xtrain[0]), Xtrain[1][i])
        for i in range(len(Xtest)):
            plt.annotate(i, Xtest[i])


    plt.legend((rep, apr, test), ("Reprovado", "Aprovado", "Testes"), loc='upper left')
    plt.show()




if __name__ == "__main__":
    main()






