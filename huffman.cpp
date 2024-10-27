#include <cstdlib>
#include <iostream>
using namespace std;

// Nodos para cada dato
struct Node
{
    char data;
    unsigned freq;
    struct Node *left, *right;
};

// Coleccion de nodos
struct MinHeap
{
    unsigned size;
    unsigned capacity;
    struct Node** array;
};

//Inicialización del nodo
struct Node* newNode(char data, unsigned freq)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));

    temp->left = NULL;
    temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct Node**)malloc(minHeap->capacity * sizeof(struct Node*));
    return minHeap;
}

// Cambiar los nodos por uno de menor tamaño
void swapMinNode(struct Node** a, struct Node** b)
{
    struct Node* aux = *a;
    *a = *b;
    *b = aux;
}

// Funcion estandar para moverse con matematica de apuntadores.
void min_Heapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swapMinNode(&minHeap->array[smallest], &minHeap->array[idx]);
        min_Heapify(minHeap, smallest);
    }
}

int is_Size_One(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}

// Extraer el valor minimo
struct Node* extract_Min(struct MinHeap* minHeap)
{
    struct Node* aux = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    min_Heapify(minHeap, 0);
    return aux;
}

// Insertar nuevo arbol
void insert_MinHeap(struct MinHeap* minHeap, struct Node* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Funcion de creacion de arbol
void build_MinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        min_Heapify(minHeap, i);
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        cout << arr[i];

    cout << "\n";
}

// Verificar si el nodo es una hoja final
int isLeaf(struct Node* root)
{
    return !(root->left) && !(root->right);
}

// Creacion de la primera estructura
struct MinHeap* create_n_Build_MinHeap(char data[], int freq[], int size)
{
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    build_MinHeap(minHeap);

    return minHeap;
}

struct Node* buildHuffmanTree(char data[], int freq[], int size)
{
    struct Node *left, *right, *top;
    struct MinHeap* minHeap = create_n_Build_MinHeap(data, freq, size);

    while (!is_Size_One(minHeap))
    {
        left = extract_Min(minHeap);
        right = extract_Min(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insert_MinHeap(minHeap, top);
    }

    return extract_Min(minHeap);
}

void print_Codes(struct Node* root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        print_Codes(root->left, arr, top + 1);
    }
    if (root->right)
    {
        arr[top] = 1;
        print_Codes(root->right, arr, top + 1);
    }
    if (isLeaf(root))
    {
        cout << root->data << ": ";
        printArr(arr, top);
    }
}

void HuffmanCodes(char data[], int freq[], int size)
{
    struct Node* root = buildHuffmanTree(data, freq, size);
    // Impresion se utiliza 100 esperando que no se haga un tamaño más grande
    int arr[100], top = 0;

    print_Codes(root, arr, top);
}

int main()
{
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
    int freq[] = { 5, 12, 35, 3, 8, 14, 21, 1, 39 };

    int size = sizeof(arr) / sizeof(arr[0]);
    HuffmanCodes(arr, freq, size);
    return 0;
}
