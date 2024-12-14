import re
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider

def find_quad(position, map_height, map_width):
    x, y = position
    mid_x = (map_width - 1) / 2
    mid_y = (map_height - 1) / 2
    if x == mid_x or y == mid_y:
        return None
    if x < mid_x and y < mid_y:
        return 0
    if x < mid_x and y > mid_y:
        return 3
    if x > mid_x and y < mid_y:
        return 1
    if x > mid_x and y > mid_y:
        return 2

def update_plot(val):
    """Update the scatter plot based on the slider value."""
    global robots, map_width, map_height, scatter

    i = int(slider.val)
    i = val# Get the slider value as an integer
    new_robots = []
    for robot in robots:
        position, velocity = robot
        part_2 = position[:]
        part_2[0] += i * velocity[0]
        part_2[1] += i * velocity[1]
        part_2[0] %= map_width
        part_2[1] %= map_height
        new_robots.append(part_2)

    # Update the scatter plot data
    scatter.set_offsets(new_robots)
    fig.canvas.draw_idle()

# Load the data
with open("../inputs/day14.txt") as file:
    robots = [[[int(a) for a in z.split(',')] for z in y.split(" ")] for y in
              [re.sub('[^0-9,\s-]', '', x.replace('\n', '')) for x in file.readlines()]]

map_height = 103
map_width = 101
quad_counts = [0, 0, 0, 0]

for robot in robots:
    position, velocity = robot
    part_1 = position[:]
    part_1[0] += 100 * velocity[0]
    part_1[1] += 100 * velocity[1]
    part_1[0] %= map_width
    part_1[1] %= map_height
    quad = find_quad(part_1, map_height, map_width)
    if quad is not None:
        quad_counts[quad] += 1

print("Part 1: ", quad_counts[0] * quad_counts[1] * quad_counts[2] * quad_counts[3])

# Create the plot
fig, ax = plt.subplots()
plt.subplots_adjust(bottom=0.2)  # Make room for the slider

# Initial data for the scatter plot
initial_robots = []
for robot in robots:
    position, velocity = robot
    part_2 = position[:]
    part_2[0] += 0 * velocity[0]  # i = 0 initially
    part_2[1] += 0 * velocity[1]
    part_2[0] %= map_width
    part_2[1] %= map_height
    initial_robots.append(part_2)

scatter = ax.scatter([pos[0] for pos in initial_robots],
                     [pos[1] for pos in initial_robots],
                     color='blue', label='Data Points')

ax.set_title('Robots Innit')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.legend()
ax.grid(True, linestyle='--', alpha=0.7)

# Slider setup
ax_slider = plt.axes([0.2, 0.05, 0.65, 0.03], facecolor='lightgoldenrodyellow')
slider = Slider(ax_slider, 'i', 7857, 7859, valinit=0, valstep=1)
slider.on_changed(update_plot)

# plt.show()


# for i in range(0, 10000):
#     if update_plot(i):
#         print(i)

# 1266
# 2350
# 5077
# 5131
# 7858
# 8942