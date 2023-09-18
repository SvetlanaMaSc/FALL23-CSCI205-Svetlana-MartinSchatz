import matplotlib.pyplot as plt
import os

# directory/folder path
dir_path = r'/home/goesonghos/Documents/School/CSCI1205/TC3-CSCI205-Fall2023/Week_3/lab/'

# label colors
colors = ["red", "blue", "green", "orange"]
# color iterator
colorI = 0

# Create a figure and axis
fig, ax = plt.subplots()

# Iterate directory
for file_path in os.listdir(dir_path):
    # check if current file_path is a file
    if os.path.isfile(os.path.join(dir_path, file_path)):
        # add filename to list
        if file_path.find(".") != -1:
            start, last = file_path.split(".")
            if last == "txt":
                xPoints = []
                yPoints = []
                file1 = open(file_path)
                lines = file1.readlines()
                for line in lines:
                    x, y = map(float, line.strip().split())
                    xPoints.append(x)
                    yPoints.append(y)
                ax.plot(xPoints, yPoints, color=colors[colorI], label=start)
                colorI += 1
                    
ax.set_xlabel("Problem Size")
ax.set_ylabel("Comparisons")
ax.set_title("Analysis of Random Algorithms")
ax.set_xticks([0, 200, 400, 600, 800, 1000])
ax.set_yticks([0.0, 0.5, 1.0, 1.5, 2.0, 2.5])
ax.set_xticklabels(['0', '200', '400', '600', '800', '1000'])
ax.set_yticklabels(['0.0', '0.5', '1.0', '1.5', '2.0', '2.5'])
ax.legend()
plt.show()

