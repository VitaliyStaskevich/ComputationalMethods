import matplotlib.pyplot as plt
# Function to plot data from a file
import numpy as np

def plot_from_file(filename, func):
    with open(filename, 'r') as file:
        lines = file.readlines()

    x = []
    y = []

    # Process data
    for line in lines:
        values = line.split()
        x.append(float(values[0]))
        y.append(float(values[1]))

    # Plot
    plt.figure()  # Create a new figure

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title(filename)
    plt.grid(True)
    xFunc = np.linspace(-3, 3, 101)
    yFunc = func(xFunc)
    plt.plot(xFunc, yFunc, label=func.__name__)
    plt.plot(x, y, label='Spline')
    plt.legend()
    plt.savefig(filename.removesuffix('.txt')+'.jpg', dpi = 400)
    plt.show()

def plot_errors(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    x = []
    y = []

    # Process data
    for line in lines:
        values = line.split()
        x.append(float(values[0]))
        y.append(float(values[1]))

    # Plot
    plt.figure()  # Create a new figure

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title(filename)
    plt.grid(True)
    plt.plot(x, y, label='Error')
    plt.legend()
    plt.savefig(filename.removesuffix('.txt')+'.jpg', dpi = 400)
    plt.show()

def f1(x):
    return np.cos(2*x)*x*x

# Array of filenames
filenames1 = ['spline.txt']
filenames2 = ['errors.txt']
# Plot from each file
for filename in filenames1:
    plot_from_file(filename, f1)
for filename in filenames2:
    plot_errors(filename)
