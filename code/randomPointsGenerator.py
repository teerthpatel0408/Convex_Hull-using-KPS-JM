"""
This file is responsible for generation of the random points. 
"""
import csv
import random
import sys

"""
Generates num_points number of points with coordinates within the range specified in the input.
"""
def generate_random_points(num_points, min_x, max_x, min_y, max_y):
    points = []
    for _ in range(num_points):
        x = random.randint(min_x, max_x)
        y = random.randint(min_y, max_y)
        points.append((x, y))
    return points

"""
Takes the generated points and stores them in a csv file.
"""
def write_points_to_csv(points, filename):
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        # writer.writerow(['X', 'Y'])
        for point in points:
            writer.writerow(point)

num_points = int(sys.argv[1])
min_x, max_x = 10, 1150
min_y, max_y = 10, 790
points = generate_random_points(num_points, min_x, max_x, min_y, max_y)
write_points_to_csv(points, 'points.csv')
