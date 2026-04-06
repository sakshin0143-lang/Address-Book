#ifndef CONTACT_H
#define CONTACT_H

typedef struct Contact_data
{
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];
} Contacts;

typedef struct AddressBook_Data
{
    Contacts contact_details[100];
    int contact_count;
} AddressBook;

/* Function declarations */
// void init_intitalization(AddressBook *);
int create_contact(AddressBook *);
void list_contacts(AddressBook *);
int search_contacts(AddressBook *);
int edit_contact(AddressBook *);
int delete_contact(AddressBook *);
void save_contacts(AddressBook *);

// validation//

int name_validation(char* name);
int number_validation(char* number);
int email_validation(char* mail);

// duplicates
int is_duplicate_mobile(AddressBook *addressbook, char *mobile);
int is_duplicate_email(AddressBook *addressbook, char *email);

//load contact
void loadContactsFromFile(AddressBook *addressBook);

#endif
