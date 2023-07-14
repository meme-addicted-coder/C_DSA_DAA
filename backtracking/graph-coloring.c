
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int** adjMatrix;
    int numNodes;
    int* colors;
} Graph;

// Function to check if it is safe to color the vertex with a given color
bool isSafe(Graph* graph, int node, int color) {
    for (int i = 0; i < graph->numNodes; i++) {
        if (graph->adjMatrix[node][i] && graph->colors[i] == color) {
            return false;
        }
    }
    return true;
}

// Function to color the graph using the Greedy algorithm
void graph_coloring(Graph* graph) {
    int numColors = 1; // Initialize the number of colors used to 1

    for (int node = 0; node < graph->numNodes; node++) {
        // Find the lowest available color for the current node
        for (int color = 1;; color++) {
            if (isSafe(graph, node, color)) {
                graph->colors[node] = color;

                if (color > numColors) {
                    numColors = color; // Update the number of colors used
                }

                break;
            }
        }
    }

    printf("Graph can be colored using at most %d colors:\n", numColors);
    for (int i = 0; i < graph->numNodes; i++) {
        printf("Node %d: Color %d\n", i, graph->colors[i]);
    }
}

// Function to create a graph with the specified number of nodes
Graph* createGraph(int numNodes) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = numNodes;
    graph->adjMatrix = (int**)malloc(numNodes * sizeof(int*));
    graph->colors = (int*)malloc(numNodes * sizeof(int));

    for (int i = 0; i < numNodes; i++) {
        graph->adjMatrix[i] = (int*)malloc(numNodes * sizeof(int));
        graph->colors[i] = 0; // Initialize all colors to 0 (not colored)
    }

    return graph;
}

// Function to free the memory allocated for the graph
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numNodes; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph->colors);
    free(graph);
}

int main() {
    int numNodes;

    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &numNodes);

    Graph* graph = createGraph(numNodes);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            scanf("%d", &graph->adjMatrix[i][j]);
        }
    }

    graph_coloring(graph);

    freeGraph(graph);

    return 0;
}
