/*
Name:Sakshi N
Sample Input: (Name:prajwal,Mobile:9874563214,Email:prajwal@gmail.com)
Sample Output:Contact saved successfully
Adressbook is program to store contact details like name,mobile number,email.
Name should be only alphabetic characters and spaces.
Mobile number should be exactly 10 digits.
Email should follow some standard format.
*/

#include <stdio.h>
#include "contact.h"

/* Structure declaration */

int main()
{
    AddressBook addressbook;
    addressbook.contact_count = 0;

    loadContactsFromFile(&addressbook);
    int option;
   

    while (1)
    {
         // Give a prompt message for a user 
        printf("\nAddress book menu\n");
        printf("1.Add contact\n2.search contact\n3.Edit contact\n4.Delete contact\n5.Display contact\n6.Save contact\n7.Exit\n");
        printf("Enter the option : ");
        scanf("%d", &option);

        switch (option) // Based on choosed option 
        {
        case 1:
        {
            //To create a new contact
            create_contact(&addressbook);
            break;
        }

        case 2:
        {
            //To search a contact 
            search_contacts(&addressbook);
            break;
        }
        case 3:
            //To edit a contact          
            edit_contact(&addressbook);
            break;

        case 4:
        {
            //To delete a contact
            delete_contact(&addressbook);
            break;
        }
        case 5:
        {
            //To list all the contacts
            list_contacts(&addressbook);
            break;
        }

        case 6:
        {
            //To save all the contacts
            printf("Saving contacts\n");
            save_contacts(&addressbook);
            break;
        }

        case 7:
        {
            //To save and come out
            printf("INFO : Save and Exit...\n");
            return 0;
        }

        default:
            printf("Invalid option \n");
            break;
        }
    }
    return 0;
}
