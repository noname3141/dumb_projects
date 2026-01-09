#include <stdio.h>
#include <string.h>

#define MAX_CONSIZE 100

typedef struct Contact {
	char name[50];
	char num[15];
	char email[50];
} contact;

void print_contact(contact con){
	printf("Name: %s\n", con.name);
	printf("Mobile no.: %s\n", con.num);
	printf("Email: %s\n", con.email);
}

int main(void){
	contact contacts[MAX_CONSIZE];
	int numContacts=0,choice;
	char name[50];

	while(1){
    printf("Currntly saved: %d\n", numContacts);
	printf("1:save new contact\n");
	printf("2:show contacts\n");
	printf("3:Exit\n");
	printf("4:Update contacts\n");
	printf("Enter Choice:");
	scanf("%d", &choice);

	switch(choice){
		case 0:
			printf("give the name of contact to delete");
			scanf("%s", name);
			printf("Underwork!");
            break;
		case 1:
			if (numContacts < MAX_CONSIZE){
				contact newcon;
				printf("Name:");
				scanf("%s", newcon.name);
				printf("Mobile no:");
				scanf("%s", newcon.num);
				printf("Email:");
				scanf("%s", newcon.email);
				int j = 0,dce = 1;
				for(j=0;j<numContacts;j++){
					if(contacts[j].name == newcon.name){
						printf("contact already exists");
						dce = 0;
					}
				}
				if(dce == 1){
					contacts[numContacts] = newcon;
					numContacts++;
					printf("added\n");
				}
			}
			else{
				printf("Contact limit reached");
			}
            break;
		case 2:
			int i = 0;
			for(i=0;i<numContacts;i++){
				printf("Name: %s\n", contacts[i].name);
				printf("Mobile no: +91 %s\n", contacts[i].num);
				printf("Email: %s\n", contacts[i].email);
				printf("\n");
			}
            break;
		case 3:
			printf("Exiting\n");
			return 0;
		case 4:
			printf("Name of contact:");
			scanf("%s", name);
			i = 0;
			for(i=0;i<numContacts;i++){
				if(strcmp(contacts[i].name, name) == 0){
					int update;
					printf("Enter 1 for changing name");
					printf("Enter 2 for changing Mob no.");
					printf("Enter 3 for changing email");
					scanf("%d",&update);
					switch(update){
						case 1:
							printf("Enter new name:");
							scanf("%s", contacts[i].name);
                            break;
						case 2:
							printf("Enter new Mob no.:");
							scanf("%s", contacts[i].num);
                            break;
						case 3:
							printf("Enter new email:");
							scanf("%s", contacts[i].email);
                            break;
						default:
							printf("Enter valid field");
                            break;
					}
				}
			}
            break;
		default:
			printf("Invalid choice");
            break;
		}
	}
	return -1;
}
