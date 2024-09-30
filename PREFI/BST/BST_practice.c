// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int elem;
    struct node* LC;
    struct node* RC;
} *TreeNode;

typedef struct list {
    int elem;
    struct list* next;
} *List;

void initializeTree(TreeNode* main);
void insertLL(List* main, int newData);
void insertTree(TreeNode* main, List database);
bool isMember(TreeNode main, int find);
void displayLL(List main);
int deleteMin(TreeNode* main);
int deleteMax(TreeNode* main);
int deleteNode(TreeNode* main, int delete);
int predecessor(TreeNode main);
int successor(TreeNode main);

// Display
void preOrder(TreeNode main){
    if (main != NULL){
        printf("%d->", main->elem);
        preOrder(main->LC);
        preOrder(main->RC);
    }
}
void inOrder(TreeNode main){
  if (main != NULL){
    inOrder(main->LC);
    printf("%d->", main->elem);
    inOrder(main->RC);
  }
}
void postOrder(TreeNode main){
  if (main != NULL){
      postOrder(main->LC);
      postOrder(main->RC);
      printf("%d->", main->elem);
  }
}

int main() {
  List Database = NULL;
  TreeNode root = NULL;
  
  {
    insertLL(&Database, 48);
    insertLL(&Database, 45);
    insertLL(&Database, 64);
    insertLL(&Database, 52);
    insertLL(&Database, 22);
    insertLL(&Database, 27);
    insertLL(&Database, 69);
    insertLL(&Database, 52);
    insertLL(&Database, 100);
    insertLL(&Database, 124);
    insertLL(&Database, 47);
    insertLL(&Database, 48);
    insertLL(&Database, 21);
  }
  
  displayLL(Database);
  
  initializeTree(&root);
  insertTree(&root, Database);
  
  
  printf("\nisMember(%d) = %d\n", 70, isMember(root, 70));
  inOrder(root);
  deleteMin(&root);
  inOrder(root);

  printf("\npredecessor(%d) = %d", 48, predecessor(root));
  printf("\nsuccessor(%d) = %d", 48, successor(root));
  
  return 0;
}

// Tree
void initializeTree(TreeNode* main){
    *main = NULL;
}
void insertTree(TreeNode* main, List database){
  TreeNode newNode;   // Used for allocating memory for a newNode for the tree
  TreeNode* trav;     // Used to traverse the tree for insertion
  List fetcher;       // Used to traverse the List database
  
  // Loop over linked list database, each element insert into tree
  for (fetcher = database ; fetcher != NULL ; fetcher = fetcher->next){
    for (trav = main ; *trav != NULL && fetcher->elem != (*trav)->elem ; ){
      trav = (fetcher->elem < (*trav)->elem) ? &(*trav)->LC : &(*trav)->RC; 
    }

    if (*trav == NULL || fetcher->elem != (*trav)->elem){
      newNode = (TreeNode)malloc(sizeof(struct node));
      if (newNode != NULL){
        newNode->LC = NULL;
        newNode->RC = NULL;
        newNode->elem = fetcher->elem;
        *trav = newNode;
        printf("\nSuccessfully inserted %d into tree.", fetcher->elem);
      }   
    } else {
      printf("\n %d is not a valid element.", fetcher->elem);
    }
  }
}
bool isMember(TreeNode main, int find){
  TreeNode trav;
  for (trav = main ; trav != NULL && trav->elem != find ; ){
    trav = (find < trav->elem) ? trav->LC : trav->RC; 
  };
  return (trav != NULL) ? true : false;
}

// Tree - DELETE
int deleteMin(TreeNode* main){
  TreeNode* trav;
  TreeNode temp;
  int returnThis;
  
  for (trav = main ; (*trav)->LC != NULL ; trav = &(*trav)->LC){};
  if (*trav != NULL){
    temp = *trav;
    *trav = temp->RC;       // Very important.
    returnThis = temp->elem;
    free(temp);
    printf("\nSuccessfully deleted %d!", returnThis);
  }
  return returnThis;
}
int deleteMax(TreeNode* main){
  TreeNode* trav;
  TreeNode temp;
  int returnThis;
  
  for (trav = main ; (*trav)->RC != NULL ; trav = &(*trav)->RC){};
  if (*trav != NULL){
    temp = *trav;
    *trav = temp->LC;       // Very important.
    returnThis = temp->elem;
    free(temp);
    printf("\nSuccessfully deleted %d!", returnThis);
  }
  return returnThis;
}

// Linked List
void insertLL(List* main, int newData){
  List* trav;
  List newNode;
  for (trav = main ; *trav != NULL ; trav = &(*trav)->next){};
  newNode = (List)malloc(sizeof(struct list));
  if (newNode != NULL){
    newNode->elem = newData;
    newNode->next = NULL;
    *trav = newNode;
    printf("\nInserted %d into the linked list database.", newData);
  }
}
void displayLL(List main){
  List trav;
  printf("\n");
  for (trav = main ; trav != NULL ; trav = trav->next){
      printf("%d->", trav->elem);
  }
  printf("NULL");
}

int predecessor(TreeNode main){
  TreeNode trav = main;
  // There could be a predecessor
  if (trav != NULL && trav->LC != NULL){
    trav = main;
    trav = trav->LC;
    while (trav->RC != NULL){
      trav = trav->RC;
    }
  } else {
    printf("\nGetting predecessor is impossible.");
  }
  // If it reached its predecessor, then that means the predecessor's right child will be NULL since it's a leaf.
  return (trav->RC == NULL) ? trav->elem : -1;
}

int successor(TreeNode main){
  TreeNode trav = main;
  // There could be a predecessor
  if (trav != NULL && trav->RC != NULL){
    trav = trav->RC;
    while (trav->LC != NULL){
      trav = trav->LC;
    }
  } else {
    printf("\nGetting successor is impossible.");
  }
  // If it reached its predecessor, then that means the predecessor's right child will be NULL since it's a leaf.
  return (trav->LC == NULL) ? trav->elem : -1;
}

int deleteNode(TreeNode* main, int delete) {
    TreeNode* trav;
    TreeNode* succ;
    TreeNode temp;
    
    for (trav = main ; *trav != NULL && (*trav)->elem != delete ; ){
    	trav = (delete < (*trav)->elem) ? &(*trav)->LC : &(*trav)->RC;
	}
	
	if (*trav != NULL){
		if ((*trav)->LC == NULL){
			temp = *trav;
			*trav = (*trav)->RC;
			free(temp);
		} else if ((*trav)->RC == NULL){
			temp = *trav;
			*trav = (*trav)->LC;
			free(temp);
		} else {
			for (succ = &(*trav)->RC ; (*succ)->LC != NULL ; succ = &(*succ)->LC){};
			temp = *succ;
			*succ = temp->RC;
			(*trav)->elem = temp->elem;
			free(temp);
		}
	}
}

