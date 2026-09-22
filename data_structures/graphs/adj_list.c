#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 4

typedef struct node {
    int vertex;
    struct node *next;
} Node, *NodePtr;

typedef struct {
    NodePtr *adjList;   // Dynamic array of linked list heads
    int num_vertices;
    int capacity;
} Graph;

// Core API
void initGraph(Graph *G, int vertices);
void freeGraph(Graph *G);
void addVertex(Graph *G);
void removeVertex(Graph *G, int vertex);
void addEdge(Graph *G, int src, int dest);
void removeEdge(Graph *G, int src, int dest);

// Utility
void displayGraph(const Graph *G);
bool hasEdge(const Graph *G, int src, int dest);

// Internal Helper
static NodePtr createNode(int vertex);
static void resizeGraph(Graph *G, int new_capacity);

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
    printf("\nDeleting Vertex B (Triggers Dynamic Expansion)...\n");
    removeVertex(&G, 1);

    printf("\n--- Updated Matrix (4 Vertices) ---\n");
    displayGraph(&G);

    freeGraph(&G);
    return 0;
}

void initGraph(Graph *G, int initial_capacity) {
    G->num_vertices = 0;
    G->capacity = initial_capacity;

    // Allocate array of pointers (heads of linked lists)
    G->adjList = malloc(sizeof(NodePtr) * G->capacity);
    if (G->adjList == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    // Initialize all heads to NULL
    for (int i = 0; i < G->capacity; i++) {
        G->adjList[i] = NULL;
    }
}

void freeGraph(Graph *G) {
    // Traverse every list and free nodes
    for (int i = 0; i < G->capacity; i++) {
        NodePtr trav = G->adjList[i];
        while (trav != NULL) {
            NodePtr del = trav;
            trav = trav->next;
            free(del);
        }
    }

    // Free the array of heads
    free(G->adjList);
    G->num_vertices = 0;
    G->capacity = 0;
}

void addVertex(Graph *G) {
    // Dynamically expand the array of pointers if full
    if (G->num_vertices == G->capacity) {
        resizeGraph(G, G->capacity * 2);
    }
    G->num_vertices++;
}

void removeVertex(Graph *G, int vertex) {
    if (vertex < 0 || vertex >= G->num_vertices) {
        printf("ERROR: Invalid vertex index %d.\n", vertex);
        return;
    }

    // 1. Free the removed vertex's own linked list
    NodePtr trav = G->adjList[vertex];
    while (trav != NULL) {
        NodePtr del = trav;
        trav = trav->next;
        free(del);
    }
    G->adjList[vertex] = NULL;

    // 2. Remove all inbound edges pointing to this vertex from other lists
    for (int i = 0; i < G->num_vertices; i++) {
        if (i != vertex) {
            removeEdge(G, i, vertex);
        }
    }

    // 3. Shift the array of list heads to close the gap
    for (int i = vertex; i < G->num_vertices - 1; i++) {
        G->adjList[i] = G->adjList[i + 1];
    }
    G->adjList[G->num_vertices - 1] = NULL; // Clear the duplicated tail

    // 4. Update vertex IDs in all remaining nodes
    // Because vertex 'k' is now vertex 'k-1', we must decrement IDs > removed vertex
    for (int i = 0; i < G->num_vertices - 1; i++) {
        NodePtr curr = G->adjList[i];
        while (curr != NULL) {
            if (curr->vertex > vertex) {
                curr->vertex--;
            }
            curr = curr->next;
        }
    }

    // 5. Decrement the active vertex count
    G->num_vertices--;

    // 6. Dynamic Shrink: Halve capacity if 25% or less full
    if (G->capacity > INITIAL_CAPACITY && G->num_vertices <= G->capacity / 4) {
        resizeGraph(G, G->capacity / 2);
    }
}

void addEdge(Graph *G, int src, int dest) {
    if (src >= G->num_vertices || dest >= G->num_vertices || src < 0 || dest < 0) {
        printf("ERROR: Invalid vertex index (%d, %d).\n", src, dest);
        return;
    }

    // Add edge from src to dest (Insert at Head for O(1) time)
    NodePtr newNode = createNode(dest);
    newNode->next = G->adjList[src];
    G->adjList[src] = newNode;

    // Uncomment the folloring block for undirected graph
    // NodePtr newNode2 = createNode(src);
    // newNode2->next = G->adjList[dest];
    // G->adjList[dest] = newNode2;
}

void removeEdge(Graph *G, int src, int dest) {
    if (src >= G->num_vertices || dest >= G->num_vertices || src < 0 || dest < 0) {
        printf("ERROR: Invalid vertex index (%d, %d).\n", src, dest);
        return;
    }

    NodePtr *trav = &(G->adjList[src]);
    while (*trav != NULL && (*trav)->vertex != dest) {
        trav = &(*trav)->next;
    }
    if (*trav != NULL) {
        NodePtr del = *trav;
        *trav = del->next;
        free(del);
    }

    // Uncomment the folloring block for undirected graph
    // trav = &(G->adjList[dest]);
    // while (*trav != NULL && (*trav)->vertex != src) {
    //     trav = &(*trav)->next;
    // }
    // if (*trav != NULL) {
    //     NodePtr del = *trav;
    //     *trav = del->next;
    //     free(del);
    // }
}

void displayGraph(const Graph *G) {
    for (int i = 0; i < G->num_vertices; i++) {
        printf("Vertex %d:", i);
        NodePtr trav = G->adjList[i];
        while (trav != NULL) {
            printf(" -> [%d]", trav->vertex);
            trav = trav->next;
        }
        printf(" -> NULL\n");
    }
}

bool hasEdge(const Graph *G, int src, int dest) {
    if (src >= G->num_vertices || dest >= G->num_vertices || src < 0 || dest < 0) {
        printf("ERROR: Invalid vertex pair (%d, %d).\n", src, dest);
        return false;
    }
    NodePtr trav = G->adjList[src];
    while (trav != NULL) {
        if (trav->vertex == dest) {
            return true;
        }
        trav = trav->next;
    }
    return false;
}

static NodePtr createNode(int vertex) {
    NodePtr newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

static void resizeGraph(Graph *G, int new_capacity) {
    NodePtr *temp = realloc(G->adjList, sizeof(NodePtr) * new_capacity);
    if (temp == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    G->adjList = temp;

    if (new_capacity > G->capacity) {
        for (int i = G->capacity; i < new_capacity; i++) {
            G->adjList[i] = NULL;
        }
    }
    G->capacity = new_capacity;
}