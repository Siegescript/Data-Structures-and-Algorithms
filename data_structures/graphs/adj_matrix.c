#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 4

typedef struct {
    bool **matrix;      // 2D dynamic array for edges (bool for unweighted)
    int num_vertices;   // Current number of active vertices
    int capacity;       // Current allocated matrix dimensions
} Graph;

// Core API
void initGraph(Graph *G, int initial_capacity);
void freeGraph(Graph *G);
void addVertex(Graph *G);
void removeVertex(Graph *G, int vertex);
void addEdge(Graph *G, int src, int dest);
void removeEdge(Graph *G, int src, int dest);

// Internal Helper
static void resizeGraph(Graph *G, int new_capacity);

// Utility
bool hasEdge(const Graph *G, int src, int dest);
void displayGraph(const Graph *G);

int main(void) {
    Graph G;
    initGraph(&G, INITIAL_CAPACITY);

    // Add 4 vertices (A, B, C, D)
    for (int i = 0; i < 4; i++) {
        addVertex(&G);
    }

    // Connect edges (Directed Graph)
    addEdge(&G, 0, 1);
    addEdge(&G, 1, 2);
    addEdge(&G, 1, 3);
    addEdge(&G, 2, 3);
    addEdge(&G, 3, 0);
    addEdge(&G, 3, 2);

    printf("--- Adjacency Matrix (4 Vertices) ---\n");
    displayGraph(&G);

    printf("\nHas edge (0 -> 1)? %s\n", hasEdge(&G, 0, 1) ? "YES" : "NO");
    printf("Has edge (0 -> 3)? %s\n", hasEdge(&G, 0, 3) ? "YES" : "NO");

    // Add a 5th vertex to trigger dynamic expansion
    printf("\nAdding Vertex 4 (Triggers Dynamic Expansion)...\n");
    addVertex(&G);
    addEdge(&G, 2, 4);
    addEdge(&G, 4, 1);

    printf("\n--- Updated Matrix (5 Vertices) ---\n");
    displayGraph(&G);

    // Delete a vertex
    printf("\nDeleting Vertex B...\n");
    removeVertex(&G, 1);

    printf("\n--- Updated Matrix (4 Vertices) ---\n");
    displayGraph(&G);

    freeGraph(&G);
    return 0;
}

void initGraph(Graph *G, int initial_capacity) {
    G->num_vertices = 0;
    G->capacity = initial_capacity;
    
    // 1. Allocate array of row pointers
    G->matrix = malloc(sizeof(bool*) * G->capacity);
    if (G->matrix == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // 2. Allocate each row array
    for (int i = 0; i < G->capacity; i++) {
        G->matrix[i] = calloc(G->capacity, sizeof(bool)); // calloc sets elements to false
        if (G->matrix[i] == NULL) {
            printf("CRITICAL ERROR: Memory allocation failed for row %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }
}

void freeGraph(Graph *G) {
    // Free rows first
    for (int i = 0; i < G->capacity; i++) {
        free(G->matrix[i]);
    }
    // Free pointer table
    free(G->matrix);
    G->matrix = NULL;
    G->num_vertices = 0;
    G->capacity = 0;
}

void addVertex(Graph *G) {
    if (G->num_vertices == G->capacity) {
        resizeGraph(G, G->capacity * 2);
    }
    G->num_vertices++;
}

void removeVertex(Graph *G, int vertex) {
    if (vertex < 0 || vertex >= G->num_vertices) {
        printf("ERROR: Vertex %d out of bounds.\n", vertex);
        return;
    }
    
    // 1. Shift rows UP (overwriting the target row)
    // Save pointer to the last row so we can free it later
    bool *delRow = G->matrix[vertex];

    for (int i = vertex; i < G->num_vertices - 1; i++) {
        G->matrix[i] = G->matrix[i + 1];
    }

    // Place the row to be deleted at the end of the pointer array
    G->matrix[G->num_vertices - 1] = delRow;

    // 2. Shift columns LEFT across ALL rows
    for (int i = 0; i < G->num_vertices - 1; i++) {
        for (int j = vertex; j < G->num_vertices - 1; j++) {
            G->matrix[i][j] = G->matrix[i][j + 1];
        }
    }

    // 3. Clear edges in the newly shifted column tail
    for (int i = 0; i < G->num_vertices; i++) {
        G->matrix[i][G->num_vertices - 1] = false;
    }

    // 4. Decrement active vertex count
    G->num_vertices--;

    // 5. Optionally shrink capacity if matrix is severely underutilized (e.g. 25% full)
    if (G->capacity > INITIAL_CAPACITY && G->num_vertices <= G->capacity / 4) {
        resizeGraph(G, G->capacity / 2);
    }
}

void addEdge(Graph *G, int src, int dest) {
    if (src >= G->num_vertices || dest >= G->num_vertices || src < 0 || dest < 0) {
        printf("ERROR: Invalid vertex pair (%d, %d).\n", src, dest);
        return; 
    }
    G->matrix[src][dest] = true;
}

void removeEdge(Graph *G, int src, int dest) {
    if (src >= G->num_vertices || dest >= G->num_vertices || src < 0 || dest < 0) {
        printf("ERROR: Invalid vertex pair (%d, %d).\n", src, dest);
        return;
    }
    G->matrix[src][dest] = false;
}

bool hasEdge(const Graph *G, int src, int dest) {
    if (src >= G->num_vertices || dest >= G->num_vertices || src < 0 || dest < 0) {
        printf("ERROR: Invalid vertex pair (%d, %d).\n", src, dest);
        return false;
    }
    return G->matrix[src][dest];
}

static void resizeGraph(Graph *G, int new_capacity) {
    // If downsizing, free excess rows first
    if (new_capacity < G->capacity) {
        for (int i = new_capacity; i < G->capacity; i++) {
            free(G->matrix[i]);
        }
    }

    // Reallocate outer pointer array
    G->matrix = realloc(G->matrix, sizeof(bool*) * new_capacity);

    // Resize existing active rows
    for (int i = 0; i < (new_capacity < G->capacity ? new_capacity : G->capacity); i++) {
        G->matrix[i] = realloc(G->matrix[i], sizeof(bool) * new_capacity);
    }

    // If expanding, allocate fresh rows and zero them out
    if (new_capacity > G->capacity) {
        for (int i = G->capacity; i < new_capacity; i++) {
            G->matrix[i] = calloc(new_capacity, sizeof(bool));
        }
    }

    G->capacity = new_capacity;
}

void displayGraph(const Graph *G) {
    printf("   ");
    for (int i = 0; i < G->num_vertices; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < G->num_vertices; i++) {
        printf("%d: ", i);
        for (int j = 0; j < G->num_vertices; j++) {
            printf("%d ", G->matrix[i][j] ? 1 : 0);
        }
        printf("\n");
    }
}