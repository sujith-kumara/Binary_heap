# Number of vertices in the graph
V = 4

# Define infinity as a large value for unconnected vertices
INF = float("inf")

def floyd_warshall(graph):
    # Initialize the distance matrix with the same values as the input graph
    dist = [row[:] for row in graph]

    # Iterate through all vertices as intermediate nodes
    for k in range(V):
        for i in range(V):
            for j in range(V):
                # If vertex k is on the shortest path from i to j, update the distance
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    print_solution(dist)

def print_solution(dist):
    print("Shortest distances between every pair of vertices:")
    for i in range(V):
        for j in range(V):
            if dist[i][j] == INF:
                print("{:7s}".format("INF"), end=" ")
            else:
                print("{:7d}".format(dist[i][j]), end=" ")
            if j == V - 1:
                print()

# Driver's code
if __name__ == "__main__":
    graph = [[0, 5, INF, 10],
             [INF, 0, 3, INF],
             [INF, INF, 0, 1],
             [INF, INF, INF, 0]
            ]
    floyd_warshall(graph)
