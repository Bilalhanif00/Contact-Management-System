#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cstring>
#include <conio.h> // For getch()

using namespace std;

struct Contact
{
    long phone;
    char name[20], address[20], email[30];
};

Contact list;
char query[20], name[20];
fstream fp, ft;
int choice, found;

void addContact();
void listContacts();
void searchContact();
void editContact();
void deleteContact();

int main()
{
    do
    {
        system("cls");
        cout << "\n\t**** Welcome to Contact Management System ****\n\n";
        cout << "\tMAIN MENU\n";
        cout << "\t=====================\n";
        cout << "\t[1] Add a New Contact\n";
        cout << "\t[2] List All Contacts\n";
        cout << "\t[3] Search for a Contact\n";
        cout << "\t[4] Edit a Contact\n";
        cout << "\t[5] Delete a Contact\n";
        cout << "\t[0] Exit\n";
        cout << "\t=====================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addContact();
            break;
        case 2:
            listContacts();
            break;
        case 3:
            searchContact();
            break;
        case 4:
            editContact();
            break;
        case 5:
            deleteContact();
            break;
        case 0:
            cout << "\nExiting... Thank you!\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";
            getch();
        }
    } while (choice != 0);

    return 0;
}

void addContact()
{
    system("cls");
    fp.open("contact.dat", ios::out | ios::app);
    if (!fp)
    {
        cout << "\nError in opening file!\n";
        return;
    }
    cout << "Enter Contact Details (leave name blank to exit):\n";
    while (true)
    {
        cin.ignore();
        cout << "Name: ";
        cin.getline(list.name, 20);
        if (strlen(list.name) == 0)
            break;

        cout << "Phone: ";
        cin >> list.phone;
        cin.ignore();
        cout << "Address: ";
        cin.getline(list.address, 20);
        cout << "Email: ";
        cin.getline(list.email, 30);

        fp.write(reinterpret_cast<char *>(&list), sizeof(list));
    }
    fp.close();
}

void listContacts()
{
    system("cls");
    cout << "\n\t\tLIST OF CONTACTS\n";
    cout << "=============================================\n";
    cout << setw(20) << "Name" << setw(15) << "Phone" << setw(20) << "Address" << setw(30) << "Email" << endl;
    cout << "=============================================\n";
    fp.open("contact.dat", ios::in);
    if (!fp)
    {
        cout << "\nError in opening file!\n";
        return;
    }
    while (fp.read(reinterpret_cast<char *>(&list), sizeof(list)))
    {
        cout << setw(20) << list.name << setw(15) << list.phone << setw(20) << list.address << setw(30) << list.email << endl;
    }
    fp.close();
    getch();
}

void searchContact()
{
    system("cls");
    cin.ignore();
    cout << "\nEnter name to search: ";
    cin.getline(query, 20);
    fp.open("contact.dat", ios::in);
    if (!fp)
    {
        cout << "\nError in opening file!\n";
        return;
    }
    found = 0;
    while (fp.read(reinterpret_cast<char *>(&list), sizeof(list)))
    {
        if (strcmp(list.name, query) == 0)
        {
            cout << "\nName: " << list.name;
            cout << "\nPhone: " << list.phone;
            cout << "\nAddress: " << list.address;
            cout << "\nEmail: " << list.email << endl;
            found = 1;
        }
    }
    if (!found)
    {
        cout << "\nNo contact found with this name!";
    }
    fp.close();
    getch();
}

void editContact()
{
    system("cls");
    cin.ignore();
    cout << "\nEnter name to edit: ";
    cin.getline(name, 20);
    fp.open("contact.dat", ios::in);
    ft.open("temp.dat", ios::out);
    if (!fp || !ft)
    {
        cout << "\nError in opening file!\n";
        return;
    }
    found = 0;
    while (fp.read(reinterpret_cast<char *>(&list), sizeof(list)))
    {
        if (strcmp(list.name, name) == 0)
        {
            found = 1;
            cout << "Enter new details:\n";
            cout << "Name: ";
            cin.getline(list.name, 20);
            cout << "Phone: ";
            cin >> list.phone;
            cin.ignore();
            cout << "Address: ";
            cin.getline(list.address, 20);
            cout << "Email: ";
            cin.getline(list.email, 30);
        }
        ft.write(reinterpret_cast<char *>(&list), sizeof(list));
    }
    fp.close();
    ft.close();
    remove("contact.dat");
    rename("temp.dat", "contact.dat");
    if (found)
        cout << "\nContact updated successfully!";
    else
        cout << "\nNo contact found with this name!";
    getch();
}

void deleteContact()
{
    system("cls");
    cin.ignore();
    cout << "\nEnter name to delete: ";
    cin.getline(name, 20);
    fp.open("contact.dat", ios::in);
    ft.open("temp.dat", ios::out);
    if (!fp || !ft)
    {
        cout << "\nError in opening file!\n";
        return;
    }
    found = 0;
    while (fp.read(reinterpret_cast<char *>(&list), sizeof(list)))
    {
        if (strcmp(list.name, name) != 0)
        {
            ft.write(reinterpret_cast<char *>(&list), sizeof(list));
        }
        else
        {
            found = 1;
        }
    }
    fp.close();
    ft.close();
    remove("contact.dat");
    rename("temp.dat", "contact.dat");
    if (found)
        cout << "\nContact deleted successfully!";
    else
        cout << "\nNo contact found with this name!";
    getch();
}