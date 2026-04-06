#include <stdio.h>
#include <string.h>
#include "contact.h"

/* REQUIRED GLOBAL VARIABLE */
int editing_index = -1;

/*  VALIDATION FUNCTIONS */

int name_validation(char *name)//validate the name 
{
    if (name[0] == ' ')
    {
        printf("Name cannot start with a space ! Please try again.\n");
        return 0;
    }

    if (strlen(name) == 0)//if the length of name is zero
    {
        printf("Invalid name!\n");
        return 0;
    }

    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||
              (name[i] >= 'a' && name[i] <= 'z') ||
              name[i] == ' '))
        {
            printf("Name must contain only alphabets and spaces! Please try again.\n");
            return 0;
        }
    }

    return 1;
}

int mobile_validation(char *mob)
{
    if (strlen(mob) != 10)//if the length of mobile is not 10
    {
        printf("Mobile number must be exactly 10 digits!Try again.\n");
        return 0;
    }

    if (!(mob[0] == '9' || mob[0] == '8' || mob[0] == '7' || mob[0] == '6'))
    {
        printf("Mobile number must start with 6,7,8 or 9!Please try again.\n");
        return 0;
    }

    for (int i = 0; i < 10; i++)
    {
        if (mob[i] < '0' || mob[i] > '9')
        {
            printf("Mobile number must contain only digits!Please try again.\n");
            return 0;
        }
    }

    return 1;
}

int email_validation(char *email)//validate the email
{
    int at_found = 0, dot_found = 0;
    int at_pos = -1, dot_pos = -1;   // ✅ For domain check only

    if ((email[0] >= '0' && email[0] <= '9'))
    {
        printf("Email must not start with a number!\n");
        return 0;
    }

    if (email[0] == '@' || email[0] == '.')
    {
        printf("Email cannot start with @ or .\n");
        return 0;
    }

    for (int i = 0; email[i] != '\0'; i++)
    {
        /* ✅ ✅ ✅ NEW RULE: NO CAPITAL LETTERS */
        if (email[i] >= 'A' && email[i] <= 'Z')
        {
            printf("Email must not contain capital letters!\n");
            return 0;
        }

        if (email[i] == ' ')
        {
            printf("Email must not contain spaces! Please try again.\n");
            return 0;
        }

        if (!((email[i] >= 'a' && email[i] <= 'z') ||
              (email[i] >= '0' && email[i] <= '9') ||
              email[i] == '@' ||
              email[i] == '.'))
        {
            printf("Invalid email characters!\n");
            return 0;
        }

        if (email[i] == '@')
        {
            if (at_found)
            {
                printf("Email cannot contain more than one '@'! Please try again.\n");
                return 0;
            }
            at_found = 1;
            at_pos = i;   // ✅ store @ position
        }

        if (email[i] == '.' && at_found && dot_found == 0)
        {
            dot_found = 1;
            dot_pos = i;   // ✅ store first dot after @
        }
    }

    if (!at_found)
    {
        printf("Email must contain @!\n");
        return 0;
    }

    if (!dot_found)
    {
        printf("Email must contain '.' after @!\n");
        return 0;
    }

    /* ✅ ✅ ✅ DOMAIN MUST EXIST BETWEEN @ AND . */
    if (dot_pos == at_pos + 1)
    {
        printf("Email must contain a domain between @ and .\n");
        return 0;
    }

    return 1;
}




/*  DUPLICATE CHECK FUNCTIONS  */

int duplicate_mobile(AddressBook *addressbook, char *mob)
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (i == editing_index)
            continue;

        if (strcmp(addressbook->contact_details[i].Mobile_number, mob) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int duplicate_email(AddressBook *addressbook, char *email)
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (i == editing_index)   // Skip same contact while editing
            continue;

        if (strcmp(addressbook->contact_details[i].Mail_ID, email) == 0)
        {
            return 1;  // duplicate found
        }
    }
    return 0;
}


/* LOADING CONTACTS FROM CSV FILE */
int load_contacts(AddressBook *addressbook)
{
    FILE *fp = fopen("contacts.csv", "r");
    if (!fp)
    {
        printf("No saved contacts found. Starting fresh.\n");
        return 0;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), fp))
    {
        if (count >= 100)
        {
            printf("Maximum contact limit reached!\n");
            break;
        }

        char *name = strtok(line, ",");
        char *mob  = strtok(NULL, ",");
        char *mail = strtok(NULL, "\n");

        if (name && mob && mail)
        {
            strcpy(addressbook->contact_details[count].Name, name);
            strcpy(addressbook->contact_details[count].Mobile_number, mob);
            strcpy(addressbook->contact_details[count].Mail_ID, mail);
            count++;
        }
    }

    fclose(fp);
    addressbook->contact_count = count;

    printf("%d contacts loaded successfully (CSV).\n", count);
    return count;
}

/* CREATE CONTACT */

int create_contact(AddressBook *addressbook)
{
    char name[32], mob[11], email[35], choice;

    while (1)
    {
        while (1)
        {
            printf("Enter Name: ");
            scanf("%[^\n]", name);
            getchar();

            if (name_validation(name))
                break;

            printf("Please re-enter a valid name.\n");
        }

        while (1)
        {
            printf("Enter Mobile Number: ");
            scanf("%[^\n]", mob);
            getchar();

            if (!mobile_validation(mob))
            {
                printf("Please re-enter a valid mobile number.\n");
                continue;
            }

            if (duplicate_mobile(addressbook, mob))
            {
                printf("Mobile number already exists! Enter a different number.\n");
                continue;
            }

            break;
        }

        while (1)
        {
            printf("Enter Email ID: ");
            scanf("%[^\n]", email);
            getchar();

            if (!email_validation(email))
            {
                printf("Please re-enter a valid email.\n");
                continue;
            }

            if (duplicate_email(addressbook, email))
            {
                printf("Email already exists! Enter a different email.\n");
                continue;
            }

            break;
        }

        strcpy(addressbook->contact_details[addressbook->contact_count].Name, name);
        strcpy(addressbook->contact_details[addressbook->contact_count].Mobile_number, mob);
        strcpy(addressbook->contact_details[addressbook->contact_count].Mail_ID, email);

        addressbook->contact_count++;

        printf("Add another contact? (Y/N): ");
        scanf("%c", &choice);
        getchar();

        if (choice == 'N' || choice == 'n')
            break;
    }

    return 0;
}

/*  LIST CONTACTS  */

void list_contacts(AddressBook *addressbook)
{
    if (addressbook->contact_count == 0)
    {
        printf("No contacts to display.\n");
        return;
    }

    Contacts temp[100];

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        temp[i] = addressbook->contact_details[i];
    }

    for (int i = 0; i < addressbook->contact_count - 1; i++)
    {
        for (int j = 0; j < addressbook->contact_count - i - 1; j++)
        {
            if (strcmp(temp[j].Name, temp[j + 1].Name) > 0)
            {
                Contacts swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    /* ✅ ✅ ✅ THIS PART WAS MISSING */
    printf("\n------ CONTACT LIST ------\n");
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        printf("Name   : %s\n", temp[i].Name);
        printf("Mobile : %s\n", temp[i].Mobile_number);
        printf("Email  : %s\n\n", temp[i].Mail_ID);
    }
}


    


/* SEARCH CONTACT */

int search_contacts(AddressBook *addressbook)
{
    int option;
    char key[40];

    while (1)
    {
        printf("Search by:\n");
        printf("1. Name\n");
        printf("2. Mobile Number\n");
        printf("3. Email ID\n");
        printf("4. Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);
        getchar();

        if (option == 4)
        {
            return -1;
        }

        if (option < 1 || option > 3)
        {
            printf("Invalid choice! Try again.\n\n");
            continue;
        }

        printf("Enter search value: ");
        scanf("%[^\n]", key);
        getchar();

        int found = 0;

        for (int i = 0; i < addressbook->contact_count; i++)
        {
            if ((option == 1 && strcmp(addressbook->contact_details[i].Name, key) == 0) ||
                (option == 2 && strcmp(addressbook->contact_details[i].Mobile_number, key) == 0) ||
                (option == 3 && strcmp(addressbook->contact_details[i].Mail_ID, key) == 0))
            {
                printf("\nContact Found:\n");
                printf("Name   : %s\n", addressbook->contact_details[i].Name);
                printf("Mobile : %s\n", addressbook->contact_details[i].Mobile_number);
                printf("Email  : %s\n\n", addressbook->contact_details[i].Mail_ID);

                found = 1;
                return i;   // FIX → return index (needed for edit/delete)
            }
        }

        if (!found)
        {
            printf("Contact not found.\n\n");
        }
    }
}

/*  EDIT CONTACT  */

int edit_contact(AddressBook *addressbook)
{
    int option;

    while (1)
    {
        printf("\n===== EDIT MENU =====\n");
        printf("1. Search & Edit Contact\n");
        printf("2. Exit to Main Menu\n");
        printf("Enter option: ");
        scanf("%d", &option);
        getchar();

        if (option == 2)
        {
            return 0;
        }

        if (option != 1)
        {
            printf("Invalid option! Try again.\n");
            continue;
        }

        int index = search_contacts(addressbook);
        if (index == -1)
            continue;

        editing_index = index;

        int choice;
        char name[32], mob[11], email[35];

        while (1)
        {
            printf("\n--- EDIT OPTIONS ---\n");
            printf("1. Edit Name\n");
            printf("2. Edit Mobile Number\n");
            printf("3. Edit Email ID\n");
            printf("4. Exit Edit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();

            if (choice == 4)
                break;

            switch (choice)
            {
            case 1:   // ✅ EDIT NAME
                printf("Enter new Name: ");
                scanf(" %31[^\n]", name);
                getchar();

                while (!name_validation(name))
                {
                    printf("Invalid name! Re-enter: ");
                    scanf(" %31[^\n]", name);
                    getchar();
                }

                strcpy(addressbook->contact_details[index].Name, name);
                printf("Name updated successfully!\n");
                break;

            case 2:   // ✅ EDIT MOBILE
                while (1)
                {
                    printf("Enter new Mobile Number: ");
                    scanf(" %10[^\n]", mob);
                    getchar();

                    if (!mobile_validation(mob))
                    {
                        printf("Invalid mobile! Re-enter.\n");
                        continue;
                    }

                    if (duplicate_mobile(addressbook, mob))
                    {
                        printf("Mobile number already exists!\n");
                        continue;
                    }

                    break;
                }

                strcpy(addressbook->contact_details[index].Mobile_number, mob);
                printf("Mobile number updated successfully!\n");
                break;

            case 3:   // ✅ EDIT EMAIL
                while (1)
                {
                    printf("Enter new Email ID: ");
                    scanf(" %34[^\n]", email);
                    getchar();

                    if (!email_validation(email))
                    {
                        printf("Invalid email! Re-enter.\n");
                        continue;
                    }

                    if (duplicate_email(addressbook, email))
                    {
                        printf("Email already exists!\n");
                        continue;
                    }

                    break;
                }

                strcpy(addressbook->contact_details[index].Mail_ID, email);
                printf("Email updated successfully!\n");
                break;

            default:
                printf("Invalid edit choice!\n");
            }
        }

        editing_index = -1;
        printf("Contact editing finished.\n");
    }
}

/*  DELETE CONTACT  */

int delete_contact(AddressBook *addressbook)
{
    int option;

    while (1)
    {
        printf("\n===== DELETE MENU =====\n");
        printf("1. Search & Delete Contact\n");
        printf("2. Exit to Main Menu\n");
        printf("Enter option: ");
        scanf("%d", &option);
        getchar();

        if (option == 2)
        {
            return 0;
        }

        if (option != 1)
        {
            printf("Invalid option! Try again.\n");
            continue;
        }

        int index = search_contacts(addressbook);

        if (index == -1)
            continue;

        for (int i = index; i < addressbook->contact_count - 1; i++)
        {
            addressbook->contact_details[i] = addressbook->contact_details[i + 1];
        }

        addressbook->contact_count--;
        printf("Contact deleted successfully.\n");
    }
}

/* SAVE CONTACTS TO CSV  */

int save_contacts(AddressBook *addressbook)
{
    FILE *fp = fopen("contacts.csv", "w");
    if (!fp)
    {
        printf("Cannot open CSV file.\n");
        return -1;
    }

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressbook->contact_details[i].Name,
                addressbook->contact_details[i].Mobile_number,
                addressbook->contact_details[i].Mail_ID);
    }

    fclose(fp);
    printf("Contacts saved successfully to CSV.\n");
    

    return 0;
}
