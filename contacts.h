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

/* GLOBAL — required for duplicate checks while editing */
extern int editing_index;

/* VALIDATION */
int name_validation(char *name);
int mobile_validation(char *mob);
int email_validation(char *email);

/* DUPLICATES */
int duplicate_mobile(AddressBook *, char *);
int duplicate_email(AddressBook *, char *);

/* CRUD OPERATIONS */
int create_contact(AddressBook *);
void list_contacts(AddressBook *);
int search_contacts(AddressBook *);
int edit_contact(AddressBook *);
int delete_contact(AddressBook *);

/* FILE OPERATIONS */
int save_contacts(AddressBook *);
int load_contacts(AddressBook *);

#endif
