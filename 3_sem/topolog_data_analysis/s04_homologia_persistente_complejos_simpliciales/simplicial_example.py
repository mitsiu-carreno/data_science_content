import scipy.spatial
import numpy as np
import matplotlib.pyplot as plt

def get_simplices(self, vertex):
    "Find all simplices this `vertex` belongs to"
    visited = set()
    queue = [self.vertex_to_simplex[vertex]]
    while queue:
        simplex = queue.pop()
        for i, s in enumerate(self.neighbors[simplex]):
            if self.simplices[simplex][i] != vertex and s != -1 and s not in visited:
                queue.append(s)
        visited.add(simplex)
    return np.array(list(visited))

np.random.seed(0)
points = np.random.rand(10, 2)
print("points",points)
tri = scipy.spatial.Delaunay(points)
vertex = 2
simplices = get_simplices(tri, vertex)
print("simplices",simplices)
# 0, 2, 5, 9, 11
neighbors = np.unique(tri.simplices[simplices].reshape(-1))
# 0, 1, 2, 3, 7, 8

plt.triplot(points[:,0], points[:,1], tri.simplices)
plt.plot(points[neighbors,0], points[neighbors,1], 'or')
plt.plot(points[vertex,0], points[vertex,1], 'ob')
plt.show()