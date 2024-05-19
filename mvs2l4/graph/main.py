import matplotlib.pyplot as plt
# Function to plot data from a file
import numpy as np


def plot_from_file(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    x = []
    y = []

    # Process data
    for line in lines:
        values = line.split()
        x.append(float(values[0]))
        y.append(float(values[1]))

    with open('exact.txt', 'r') as file:
        lines2 = file.readlines()

    x_exact = []
    y_exact = []

    for line in lines2:
        values = line.split()
        x_exact.append(float(values[0]))
        y_exact.append(float(values[1]))

    # Plot
    plt.figure()  # Create a new figure

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title(filename.removesuffix('.txt'))
    plt.grid(True)
    plt.plot(x, y, label = filename.removesuffix('.txt'))
    plt.plot(x_exact, y_exact, label='Exact solution')
    plt.legend()
    plt.savefig(filename.removesuffix('.txt')+'.jpg', dpi = 400)
    plt.show()


# Array of filenames
filenames1 = ['ABM.txt','ITM.txt','MPM.txt']  # Add more filenames as needed
# Plot from each file
for filename in filenames1:
    plot_from_file(filename)

