import os
import matplotlib.pyplot as plt

dir_path = r'/home/goesonghos/Documents/School/CSCI1205/TC3-CSCI205-Fall2023/Week_10/lab/'  # Adjust this path

colors = ["red", "blue", "green", "orange"]

fig, ax = plt.subplots()

files = sorted([f for f in os.listdir(dir_path) if f.endswith(".txt")])

for idx, file_path in enumerate(files):
    xPoints = []
    yPoints = []

    with open(os.path.join(dir_path, file_path), 'r') as file:
        lines = file.readlines()
        for line in lines:
            x, y = map(float, line.strip().split(' '))
            xPoints.append(x)
            yPoints.append(y)

    ax.plot(xPoints, yPoints, color=colors[idx % len(colors)], label=file_path.split('.')[0])

ax.set_xlabel("Vector Size")
ax.set_ylabel("Actions")
ax.set_title("Experiment 2: Swaps")
ax.legend()
plt.show()
