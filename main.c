#include <stdio.h>
#include <string.h>
#include "contact.h"

int main()
{
    AddressBook addressbook;
    addressbook.contact_count = 0;

    load_contacts(&addressbook);

    int choice;
    char line[32];

    while (1)
    {
        printf("\n===== ADDRESS BOOK MENU =====\n");
        printf("1. Add Contact\n");
        printf("2. List Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Edit Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Save Contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (fgets(line, sizeof(line), stdin) == NULL)
            return 0;

        sscanf(line, "%d", &choice);   // ✅ NO stdlib used

        switch (choice)
        {
        case 1: create_contact(&addressbook); break;
        case 2: list_contacts(&addressbook); break;
        case 3: search_contacts(&addressbook); break;
        case 4: edit_contact(&addressbook); break;
        case 5: delete_contact(&addressbook); break;
        case 6: save_contacts(&addressbook); break;
        case 7: printf("Exiting...\n"); return 0;
        default: printf("Invalid choice!\n");
        }
    }
}
