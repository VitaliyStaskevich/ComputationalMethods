import matplotlib.pyplot as plt

# Function to plot data from a file
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

    # Plot
    plt.figure()  # Create a new figure
    plt.plot(x, y)
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title(filename)
    plt.grid(True)
    plt.show()

# Array of filenames
filenames = ['equid1-3.txt', 'equid1-10.txt', 'equid1-20.txt',
             'cheb1-3.txt', 'cheb1-10.txt', 'cheb1-20.txt',
             'equid2-3.txt', 'equid2-10.txt', 'equid2-20.txt',
             'cheb2-3.txt', 'cheb2-10.txt', 'cheb2-20.txt']  # Add more filenames as needed

# Plot from each file
for filename in filenames:
    plot_from_file(filename)
