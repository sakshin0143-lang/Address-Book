#include <stdio.h>
#include <string.h>
#include "contact.h"

// To create a contact
int create_contact(AddressBook *addressbook)
{
    char name[20];
    char mob[11];
    char mail[30];

    while (1)
    {
        int index = addressbook->contact_count;

        // Name input with validation  
        while (1)
        {
            printf("Enter the Name: ");
            scanf(" %[^\n]", name);

            if (name_validation(name))
            {
                strcpy(addressbook->contact_details[index].Name, name);
                break;
            }
        }

        // Mobile validation
        while (1)
        {
            printf("Enter the Mobile Number: ");
            scanf(" %[^\n]", mob);

            if (!number_validation(mob))
                continue;

            if (is_duplicate_mobile(addressbook, mob))
            {
                printf("This Mobile number already exists! Please enter again.\n");
                continue;
            }

            strcpy(addressbook->contact_details[index].Mobile_number, mob);
            break;
        }

        // Email validation
        while (1)
        {
            printf("Enter the Mail ID: ");
            scanf(" %[^\n]", mail);

            if (!email_validation(mail))
                continue;

            if (is_duplicate_email(addressbook, mail))
            {
                printf("This Email already exists! Please enter again.\n");
                continue;
            }

            strcpy(addressbook->contact_details[index].Mail_ID, mail);
            break;
        }

        addressbook->contact_count++;

        int cont;
        printf("Contact added successfully.\n");
        printf("Do you want to add any other contacts? YES-1 / NO-0: ");
        scanf("%d", &cont);
        getchar();

        if (cont == 0)
            break;
    }

    return 0;
}

// To list contacts
void list_contacts(AddressBook *addressbook)
{
    if (addressbook->contact_count == 0)
    {
        printf("No contacts to display.\n");
        return;
    }

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        printf("----------------------------\n");
        printf("Contact : %d\n", i + 1);
        printf("Name   : %s\n", addressbook->contact_details[i].Name);
        printf("Mobile : %s\n", addressbook->contact_details[i].Mobile_number);
        printf("Mail   : %s\n\n", addressbook->contact_details[i].Mail_ID);
        printf("----------------------------\n");
    }
}

// To search contacts
int search_contacts(AddressBook *addressbook)
{
    while (1)
    {
        int option;
        int found = 0;
        int i;

        printf("Search contact menu:\n");
        printf("1.Search by Name\n");
        printf("2.Search by Mobile\n");
        printf("3.Search by Mail\n");
        printf("4.Exit search menu\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            char name[40];
            printf("Enter Name to search : ");
            scanf(" %[^\n]", name);

            int cnt = 0;
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (!strcmp(addressbook->contact_details[i].Name, name))
                {
                    printf("%d. %s | %s | %s\n", ++cnt,
                           addressbook->contact_details[i].Name,
                           addressbook->contact_details[i].Mobile_number,
                           addressbook->contact_details[i].Mail_ID);
                }
            }

            if (cnt == 0)
                printf("No matching Name found.\n");

            break;
        }

        case 2:
        {
            char mob[40];
            printf("Enter Mobile to search : ");
            getchar();
            scanf("%[^\n]", mob);

            found = 0;
            for (i = 0; i < addressbook->contact_count; i++)
            {
                if (!strcmp(addressbook->contact_details[i].Mobile_number, mob))
                {
                    found = 1;
                    break;
                }
            }

            if (found == 1)
            {
                printf("Contact found:\n");
                printf("Name: %s | Mobile: %s | Mail: %s\n",
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);
            }
            else
            {
                printf("No matching Mobile found.\n");
            }
            break;
        }

        case 3:
        {
            char email[40];
            printf("Enter Email to search : ");
            getchar();
            scanf("%[^\n]", email);

            found = 0;
            for (i = 0; i < addressbook->contact_count; i++)
            {
                if (!strcmp(addressbook->contact_details[i].Mail_ID, email))
                {
                    found = 1;
                    break;
                }
            }

            if (found == 1)
            {
                printf("Contact found:\n");
                printf("Name: %s | Mobile: %s | Mail: %s\n",
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);
            }
            else
            {
                printf("No matching Email found.\n");
            }
            break;
        }

        case 4:
            printf("Exiting search menu.\n");
            return 0;

        default:
            printf("Invalid option.\n");
            return 0;
        }
    }

    return 0;
}

// To edit contacts
int edit_contact(AddressBook *addressbook)
{
    while (1)
    {
        if (addressbook->contact_count == 0)
        {
            printf("No contacts to edit.\n");
            return 0;
        }

        int option, i;
        char name[40], mob[20], email[40];

        printf("\nPlease select one option from edit Menu\n");
        printf("1.Edit Name\n");
        printf("2.Edit Mobile\n");
        printf("3.Edit Mail\n");
        printf("4.Edit All\n");
        printf("5.Exit edit menu\n");
        printf("Enter the option you want to edit: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            printf("Enter existing Name: ");
            scanf(" %[^\n]", name);

            int idxList[50], n = 0;

            for (i = 0; i < addressbook->contact_count; i++)
                if (!strcmp(addressbook->contact_details[i].Name, name))
                    idxList[n++] = i;

            if (n == 0)
            {
                printf("No matching Name found to edit.\n");
                break;
            }

            if (n > 1)
            {
                printf("\nMultiple contacts found:\n");
                for (int k = 0; k < n; k++)
                    printf("%d. %s | %s | %s\n", k + 1,
                           addressbook->contact_details[idxList[k]].Name,
                           addressbook->contact_details[idxList[k]].Mobile_number,
                           addressbook->contact_details[idxList[k]].Mail_ID);

                printf("Select number to edit: ");
                int sel;
                scanf("%d", &sel);

                if (sel < 1 || sel > n)
                {
                    printf("Invalid selection.\n");
                    break;
                }
                i = idxList[sel - 1];
            }
            else
                i = idxList[0];

            printf("\nCurrent details: Name: %s | Mobile: %s | Mail: %s\n",
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);

            printf("\nEnter new Name: ");
            scanf(" %[^\n]", addressbook->contact_details[i].Name);

            while (!name_validation(addressbook->contact_details[i].Name))
            {
                printf("Enter new Name: ");
                scanf(" %[^\n]", addressbook->contact_details[i].Name);
            }

            printf("\nContact updated successfully.\n");
            printf("Name: %s | Mobile: %s | Mail: %s\n",
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);
            break;
        }


        case 2:
        {
            printf("Enter existing Mobile number: ");
            scanf(" %[^\n]", mob);

            int idxList[50], n = 0;

            for (i = 0; i < addressbook->contact_count; i++)
                if (!strcmp(addressbook->contact_details[i].Mobile_number, mob))
                    idxList[n++] = i;

            if (n == 0)
            {
                printf("No matching Mobile found.\n");
                break;
            }

            if (n > 1)
            {
                printf("\nMultiple contacts found:\n");
                for (int k = 0; k < n; k++)
                    printf("%d. %s | %s | %s\n", k + 1,
                           addressbook->contact_details[idxList[k]].Name,
                           addressbook->contact_details[idxList[k]].Mobile_number,
                           addressbook->contact_details[idxList[k]].Mail_ID);

                printf("Select number to edit: ");
                int sel;
                scanf("%d", &sel);

                if (sel < 1 || sel > n)
                {
                    printf("Invalid selection.\n");
                    break;
                }
                i = idxList[sel - 1];
            }
            else
                i = idxList[0];

            printf("\nCurrent details: Name: %s | Mobile: %s | Mail: %s\n",
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);

            char newMob[20];   // temp variable

            while (1)
            {
                printf("\nEnter new Mobile number: ");
                scanf(" %[^\n]", newMob);

                if (!number_validation(newMob))
                    continue;

                int duplicate = 0;
                for (int j = 0; j < addressbook->contact_count; j++)
                {
                    if (j == i)
                        continue;

                    if (!strcmp(addressbook->contact_details[j].Mobile_number, newMob))
                    {
                        duplicate = 1;
                        break;
                    }
                }

                if (duplicate)
                {
                    printf("This Mobile number already exists! Please enter another.\n");
                    continue;
                }

                // write into struct only after validation 
                strcpy(addressbook->contact_details[i].Mobile_number, newMob);
                break;
            }

            printf("\nUpdated Contact:\n");
            printf("Name: %s | Mobile: %s | Mail: %s\n",
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);
            break;
        }


        case 3:
        {
            printf("Enter existing Mail ID: ");
            scanf(" %[^\n]", email);

            int idxList[50], n = 0;

            for (i = 0; i < addressbook->contact_count; i++)
                if (!strcmp(addressbook->contact_details[i].Mail_ID, email))
                    idxList[n++] = i;

            if (n == 0)
            {
                printf("No matching Email found.\n");
                break;
            }

            if (n > 1)
            {
                printf("\nMultiple contacts found:\n");
                for (int k = 0; k < n; k++)
                    printf("%d. %s | %s | %s\n", k + 1,
                           addressbook->contact_details[idxList[k]].Name,
                           addressbook->contact_details[idxList[k]].Mobile_number,
                           addressbook->contact_details[idxList[k]].Mail_ID);

                printf("Select number to edit: ");
                int sel;
                scanf("%d", &sel);

                if (sel < 1 || sel > n)
                {
                    printf("Invalid selection.\n");
                    break;
                }
                i = idxList[sel - 1];
            }
            else
                i = idxList[0];

            printf("\nCurrent details: Name: %s | Mobile: %s | Mail: %s\n",
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);

            char newEmail[40]; // temp variable

            while (1)
            {
                printf("\nEnter new Mail ID: ");
                scanf(" %[^\n]", newEmail);

                if (!email_validation(newEmail))
                    continue;

                int duplicate = 0;
                for (int j = 0; j < addressbook->contact_count; j++)
                {
                    if (j == i)
                        continue;

                    if (!strcmp(addressbook->contact_details[j].Mail_ID, newEmail))
                    {
                        duplicate = 1;
                        break;
                    }
                }

                if (duplicate)
                {
                    printf("This Email already exists! Please enter another.\n");
                    continue;
                }

                strcpy(addressbook->contact_details[i].Mail_ID, newEmail);
                break;
            }

            printf("\nUpdated Contact:\n");
            printf("Name: %s | Mobile: %s | Mail: %s\n",
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);
            break;
        }

        case 4:
        {
            printf("Enter existing Name: ");
            scanf(" %[^\n]", name);

            int idxList[50], n = 0;

            for (i = 0; i < addressbook->contact_count; i++)
                if (!strcmp(addressbook->contact_details[i].Name, name))
                    idxList[n++] = i;

            if (n == 0)
            {
                printf("No matching Name found.\n");
                break;
            }

            if (n > 1)
            {
                printf("\nMultiple contacts found:\n");
                for (int k = 0; k < n; k++)
                    printf("%d. %s | %s | %s\n", k + 1,
                           addressbook->contact_details[idxList[k]].Name,
                           addressbook->contact_details[idxList[k]].Mobile_number,
                           addressbook->contact_details[idxList[k]].Mail_ID);

                printf("Select number to edit: ");
                int sel;
                scanf("%d", &sel);

                if (sel < 1 || sel > n)
                {
                    printf("Invalid selection.\n");
                    break;
                }
                i = idxList[sel - 1];
            }
            else
                i = idxList[0];

            printf("\nCurrent details: Name: %s | Mobile: %s | Mail: %s\n",
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);

            printf("\nEditing All Fields.\n");

            //New name
            do
            {
                printf("Enter new Name: ");
                scanf(" %[^\n]", addressbook->contact_details[i].Name);
            } while (!name_validation(addressbook->contact_details[i].Name));

            // New number
            char newMob2[20];
            while (1)
            {
                printf("Enter new Mobile number: ");
                scanf(" %[^\n]", newMob2);

                if (!number_validation(newMob2))
                    continue;

                int duplicate = 0;
                for (int j = 0; j < addressbook->contact_count; j++)
                {
                    if (j == i)
                        continue;

                    if (!strcmp(addressbook->contact_details[j].Mobile_number, newMob2))
                    {
                        duplicate = 1;
                        break;
                    }
                }

                if (duplicate)
                {
                    printf("This Mobile number already exists! Please enter another.\n");
                    continue;
                }

                strcpy(addressbook->contact_details[i].Mobile_number, newMob2);
                break;
            }

            // New mail
            char newEmail2[40];
            while (1)
            {
                printf("Enter new Mail ID: ");
                scanf(" %[^\n]", newEmail2);

                if (!email_validation(newEmail2))
                    continue;

                int duplicate = 0;
                for (int j = 0; j < addressbook->contact_count; j++)
                {
                    if (j == i)
                        continue;

                    if (!strcmp(addressbook->contact_details[j].Mail_ID, newEmail2))
                    {
                        duplicate = 1;
                        break;
                    }
                }

                if (duplicate)
                {
                    printf("This Email already exists! Please enter another.\n");
                    continue;
                }

                strcpy(addressbook->contact_details[i].Mail_ID, newEmail2);
                break;
            }

            printf("\nContact updated successfully.\n");
            printf("Name: %s | Mobile: %s | Mail: %s\n",
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);
            break;
        }

        case 5:
            printf("Exiting edit menu.\n");
            return 0;

        default:
            printf("Invalid option.\n");
        }
    }
    return 0;
}

// To delete contact
int delete_contact(AddressBook *addressbook)
{
    while (1)
    {
        if (addressbook->contact_count == 0)
        {
            printf("No contacts to delete.\n");
            return 0;
        }

        int choice, i, j, found = 0;

        printf("\nDelete Menu\n");
        printf("1.Delete by Name\n");
        printf("2.Delete by Mobile\n");
        printf("3.Delete by Mail\n");
        printf("4.Exit delete menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
        {
            char name[40];
            printf("Enter the Name to delete : ");
            scanf(" %[^\n]", name);

            int idxList[50], n = 0;

            for (i = 0; i < addressbook->contact_count; i++)
                if (!strcmp(addressbook->contact_details[i].Name, name))
                    idxList[n++] = i;

            if (n == 0)
            {
                printf("No matching Name found to delete.\n");
                break;
            }

            if (n > 1)
            {
                printf("\nMultiple contacts found:\n");
                for (int k = 0; k < n; k++)
                    printf("%d. %s | %s | %s\n", k + 1,
                           addressbook->contact_details[idxList[k]].Name,
                           addressbook->contact_details[idxList[k]].Mobile_number,
                           addressbook->contact_details[idxList[k]].Mail_ID);

                printf("Select number to delete: ");
                int sel;
                scanf("%d", &sel);

                if (sel < 1 || sel > n)
                {
                    printf("Invalid selection.\n");
                    break;
                }
                i = idxList[sel - 1];
            }
            else
            {
                i = idxList[0];
            }

            for (j = i; j < addressbook->contact_count - 1; j++)
                addressbook->contact_details[j] =
                    addressbook->contact_details[j + 1];

            addressbook->contact_count--;
            printf("Contact deleted successfully.\n");
            break;
        }

        case 2:
        {
            char mob[20];
            printf("Enter the Mobile Number to delete : ");
            scanf("%[^\n]", mob);
            getchar();

            found = 0;
            for (i = 0; i < addressbook->contact_count; i++)
            {
                if (!strcmp(addressbook->contact_details[i].Mobile_number, mob))
                {
                    found = 1;

                    for (j = i; j < addressbook->contact_count - 1; j++)
                        addressbook->contact_details[j] =
                            addressbook->contact_details[j + 1];

                    addressbook->contact_count--;
                    printf("Contact deleted successfully.\n");
                    break;
                }
            }

            if (!found)
                printf("No matching Mobile Number found to delete.\n");

            break;
        }

        case 3:
        {
            char email[40];
            printf("Enter the Mail ID to delete : ");
            scanf("%[^\n]", email);
            getchar();

            found = 0;
            for (i = 0; i < addressbook->contact_count; i++)
            {
                if (!strcmp(addressbook->contact_details[i].Mail_ID, email))
                {
                    found = 1;

                    for (j = i; j < addressbook->contact_count - 1; j++)
                        addressbook->contact_details[j] =
                            addressbook->contact_details[j + 1];

                    addressbook->contact_count--;
                    printf("Contact deleted successfully.\n");
                    break;
                }
            }

            if (!found)
                printf("No matching Mail ID found to delete.\n");

            break;
        }

        case 4:
            printf("Exiting delete menu.\n");
            return 0;

        default:
            printf("Invalid option in delete menu.\n");
            return 0;
        }
    }

    printf("\nSaving after deletion successfully.....\n");
    return 0;
}

// To save contacts
void save_contacts(AddressBook *addressbook)
{
    FILE *file = fopen("contacts.txt", "w");

    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "#%d\n", addressbook->contact_count);

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        fprintf(file, "%s,%s,%s\n",
                addressbook->contact_details[i].Name,
                addressbook->contact_details[i].Mobile_number,
                addressbook->contact_details[i].Mail_ID);
    }

    fclose(file);
}
