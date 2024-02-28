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
    plt.plot(x, y, label='Interpolation')
    plt.legend()
    plt.savefig(filename.removesuffix('.txt')+'.jpg', dpi = 400)
    plt.show()


def xxcos2x(x):
    return np.cos(2*x)*x*x

def f2(x):
    return 1/(1+5*x*x)
# Array of filenames
filenames1 = ['equid1-3.txt', 'equid1-10.txt', 'equid1-20.txt',
             'cheb1-3.txt', 'cheb1-10.txt', 'cheb1-20.txt']
filenames2 = ['equid2-3.txt', 'equid2-10.txt', 'equid2-20.txt',
             'cheb2-3.txt', 'cheb2-10.txt', 'cheb2-20.txt']  # Add more filenames as needed
# Plot from each file
for filename in filenames1:
    plot_from_file(filename, xxcos2x)
for filename in filenames2:
    plot_from_file(filename, f2)