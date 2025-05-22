#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Color states for BFS
#define WHITE 0
#define GREY 1
#define BLACK 2

// Graph node structure
struct Node {
    int vertex;
    struct Node* next;
};

// Graph structure with adjacency lists
struct Graph {
    int num_of_vertices;
    struct Node** adj_Lists;
};

// Vertex properties for BFS
struct Vertex_props {
    int color;
    int distance;
    int parent;
};

// Queue node for BFS traversal
struct Queue_node {
    int vertex;
    struct Queue_node* next;
};

// Queue structure
struct Queue {
    struct Queue_node *front, *back;
};

// Creates a new node for the graph
struct Node* create_node(int v) {
    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->vertex = v;
    new_node->next = NULL;
    return new_node;
}

// Initializes a new graph with given number of vertices
struct Graph* create_graph(int no_vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->num_of_vertices = no_vertices;
    graph->adj_Lists = calloc(no_vertices, sizeof(struct Node*));
    return graph;
}

// Adds directed edge from_node -> to_node
void add_edge(struct Graph* ed_graph, int from_node, int to_node) {
    struct Node* new_node = create_node(to_node);
    if (ed_graph->adj_Lists[from_node] == NULL) {
        ed_graph->adj_Lists[from_node] = new_node;
    } else {
        struct Node* temp = ed_graph->adj_Lists[from_node];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Creates empty queue
struct Queue* create_queue() {
    struct Queue* new_queue = malloc(sizeof(struct Queue));
    new_queue->front = NULL;
    new_queue->back = NULL;
    return new_queue;
}

// Adds vertex to queue
void enqueue(struct Queue* queue, int vertex) {
    struct Queue_node* newnode = malloc(sizeof(struct Queue_node));
    newnode->vertex = vertex;
    newnode->next = NULL;

    if (queue->back == NULL) {
        queue->front = newnode;
        queue->back = newnode;
        return;
    }

    queue->back->next = newnode;
    queue->back = newnode;
}

// Removes and returns front vertex from queue
int dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return -1;
    }

    struct Queue_node* temp = queue->front;
    int vertex = temp->vertex;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->back = NULL;
    }

    free(temp);
    return vertex;
}

// Frees graph memory
void free_graph(struct Graph* graph) {
    for (int i = 0; i < graph->num_of_vertices; i++) {
        struct Node* current = graph->adj_Lists[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adj_Lists);
    free(graph);
}

// Frees queue memory
void free_queue(struct Queue* queue) {
    while (queue->front != NULL) {
        dequeue(queue);
    }
    free(queue);
}

// Finds shortest path between start and end vertices using BFS
void BFS_shortest_path(struct Graph* graph, int start, int end) {
    struct Vertex_props* vertices = malloc(graph->num_of_vertices * sizeof(struct Vertex_props));

    // Initialize vertices
    for (int i = 0; i < graph->num_of_vertices; i++) {
        vertices[i].color = WHITE;
        vertices[i].distance = INT_MAX;
        vertices[i].parent = -1;
    }

    // Start BFS from start vertex
    vertices[start].color = GREY;
    vertices[start].distance = 0;

    struct Queue* queue = create_queue();
    enqueue(queue, start);

    // BFS main loop
    while (queue->front != NULL) {
        int u = dequeue(queue);

        if (u == end) {
            break;
        }

        // Process all adjacent vertices
        struct Node* tempo = graph->adj_Lists[u];
        while (tempo) {
            int v = tempo->vertex;
            
            if (vertices[v].color == WHITE) {
                vertices[v].color = GREY;
                vertices[v].distance = vertices[u].distance + 1;
                vertices[v].parent = u;
                enqueue(queue, v);
            }
            tempo = tempo->next;
        }

        vertices[u].color = BLACK;
    }

    // Print results
    if (vertices[end].distance == INT_MAX) {
        printf("No path exists between vertices %d and %d\n", start, end);
    } else {
        printf("Shortest distance from %d to %d is: %d\n", start, end, vertices[end].distance);
        printf("Path:");
        int* path = malloc(graph->num_of_vertices * sizeof(int));
        int length = 0;
        int current = end;

        // Reconstruct path
        while (current != -1) {
            path[length++] = current;
            current = vertices[current].parent;
        }

        // Print path
        for (int i = length - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) {
                printf(" -> ");
            }
        }
        printf("\n"); 

        free(path);
    }

    free(vertices);
    free_queue(queue);
}

// Cleanup function
void free_all_resources(struct Graph* graph) {
    free_graph(graph);
}

// Counts number of vertices in input file
int count_vertices(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for counting vertices\n");
        return -1;
    }
    
    int max_vertex = -1;
    int i, j;
    
    while (fscanf(file, "%d,%d\n", &i, &j) == 2) {
        if (i > max_vertex){
            max_vertex = i;
        } 
        if (j > max_vertex){
            max_vertex = j;
        } 
    }
    
    fclose(file);
    return max_vertex + 1; 
}


int main() {
    char filename[256];
    printf("Enter the input file name: ");
    scanf("%s", filename);
    
    // Build graph from file
    int num_vertices = count_vertices(filename);
    if (num_vertices == -1) {
        return 1;
    }

    //printf("Number of vertices: %d\n", num_vertices);

    struct Graph* graph = create_graph(num_vertices);

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading edges\n");
        free_all_resources(graph);
        return 1;
    }
    
    // Read edges
    int i, j;
    while (fscanf(file, "%d,%d\n", &i, &j) == 2) {
        add_edge(graph, i, j);
    }
    
    fclose(file);

    // Get start and end vertices
    int start, end;
    printf("Enter start,end vertices(seperated with a comma) : ");
    if (scanf("%d,%d", &start, &end) != 2) {
        printf("Invalid input\n");
        free_all_resources(graph);
        return 1;
    }

    // Checks if input is valid or not
    if (start < 0 || end < 0 || start >= num_vertices || end >= num_vertices) {
        printf("Invalid start or end vertex \n");
        free_all_resources(graph);
        return 1;
    }
    
    BFS_shortest_path(graph, start, end);
    
    free_all_resources(graph);
    return 0;
}