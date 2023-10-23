import os
import matplotlib.pyplot as plt

dir_path = r'/home/goesonghos/Documents/School/CSCI1205/TC3-CSCI205-Fall2023/Week_8/lab/'  # Adjust this path

colors = ["red", "blue", "green", "orange"]
colorI = 0

fig, ax = plt.subplots()

for file_path in os.listdir(dir_path):
    if file_path.endswith(".txt"):
        xPoints = []
        yPoints = []

        with open(os.path.join(dir_path, file_path), 'r') as file:
            lines = file.readlines()
            for line in lines:
                x, y = map(float, line.strip().split())
                xPoints.append(x)
                yPoints.append(y)

        ax.plot(xPoints, yPoints, color=colors[colorI], label=file_path.split('.')[0])
        colorI += 1

ax.set_xlabel("Problem Size")
ax.set_ylabel("Average Comparisons")
ax.set_title("Analysis of ClosedHashTable Comparisons")
# ... (other settings for the plot)
ax.legend()
plt.show()
