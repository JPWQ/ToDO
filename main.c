#include "main.h"

int main(){
  Collection* collections = NULL;
  char name[100];
  int index;
  int choice = 0;
  int tIndex;
//  addCollection(NULL, &collections);
  addCollection("Daily", &collections);
  addCollection("Weekly", &collections);
  while(choice != 7){
    printf("\tOptions\n");
    printf("1. Collections.\n");
    printf("2. Create Collection.\n");
    printf("3. Delete Collection.\n");
    printf("4. View Tasks Within A Collection.\n");
    printf("5. Add Task To Collection.\n");
    printf("6. Delete Task From Collection.\n");
    printf("7. Exit Program.\n");
    printf("Enter A Choice: ");
    scanf("%d", &choice);
    getchar();
    switch(choice) {
      case 1:
        printf("\n");
        listCollections(collections);
        printf("\n");
        break;
      case 2:
        printf("Enter a name: \n");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        addCollection(name, &collections);
        break;
      case 3:
        printf("Enter An Index: ");
        scanf("%d", &index);
        deleteCollection(index-1, collections);
        break;
      case 4:
        printf("Enter An Index: ");
        scanf("%d", &index);
        listTasks(index, collections[index-1].tasks);
        break;
      case 5:
        printf("Enter An Index: ");
        scanf("%d", &index);
        getchar();
        printf("Enter A Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        addTaskToCollection(index, name, collections);
        break;
      case 6:
        printf("Enter The Index Of The Collection: ");
        scanf("%d", &index);
        getchar();
        printf("Enter The Index Of The Task: ");
        scanf("%d", &tIndex);
        getchar();
        deleteTask(tIndex - 1, collections[index-1].tasks);
        break;
      case 7:
        printf("Exiting Program...\n");
        freeCollections(collections);
        break;
      default:
        printf("Invalid Input.\n");
        break;
    }
  }
  return 0;
}
