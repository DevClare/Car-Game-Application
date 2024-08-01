LinkedList* createLinkedList();
player* playerNode(player*);
car* carNode(car*);
void insertLast(LinkedList*, void*);
void* removeLast(LinkedList*);
void freeLinkedList (LinkedList* list, listFunc funcPtr);
void freeStruct (void* data);
/*void freeCar (void* data);*/