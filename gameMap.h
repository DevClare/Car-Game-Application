#define PLAYER_SIZE 5
#define CAR_SIZE 3

/* declare struct for player */
typedef struct{
        int pRow;
        int pCol;
        int curRow;
        int curCol;
        int road;
}player;

/* declare struct for car */
typedef struct{
        int row;
        int column;
        char direction;
}car;

/* declare struct for linked list node */
typedef struct LinkedListNode{
        void* data;
        struct LinkedListNode* next;
}LinkedListNode;

/* declare struct for linked list */
typedef struct LinkedList{
        LinkedListNode* head;
        int count;
}LinkedList;

typedef void (*listFunc)(void* data);

void map(char**, int, int);
void game(char**, int, int, player*, car*);
int moveUp(char**, int, player*, car*, LinkedList*, LinkedList*);
int moveDown(char**, int, player*, car*, LinkedList*, LinkedList*);
int moveRight(char**, int, player*, car*, LinkedList*, LinkedList*);
int moveLeft(char**, int, player*, car*, LinkedList*, LinkedList*);
void undo(char**, int, int, player*, car*, LinkedList*, LinkedList*);
void finalPrint(char**, int, int, int);
