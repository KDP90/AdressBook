#include <iostream>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct User {
    string login, password;
    int userID;
};

struct Recipient {
    int recipientID, userID;
    string name, surname, phone, email, adress;
};

string readLine() {
    string line;
    cin.sync();
    getline(cin, line);
    return line;
}

void saveUserIndex (vector <User> &userIndex) {
    fstream file;
    file.open("user_index.txt", ios::out);
    for (int i = 0; i < (int) userIndex.size(); i++) {
        file << userIndex[i].userID << '|';
        file << userIndex[i].login << '|';
        file << userIndex[i].password << endl;
    }
    file.close();
}

void registration (vector <User> &userIndex) {
    User newUser;
    cout << "Input login: " << endl;
    cin >> newUser.login;
    cout << "Input password: " << endl;
    cin >> newUser.password;
    newUser.userID = userIndex.size() + 1;
    userIndex.push_back(newUser);
    saveUserIndex (userIndex);
    cout << "User added." << endl;
    system ("PAUSE");
}

void loadUserIndex (vector <User> &userIndex) {
    fstream file;
    string line, buffer;
    int position = 0;
    User user;

    file.open("user_index.txt", ios::in);
    if (!file.good()) {
        cout << "file does not exist" << endl;
        return;
    }
    while(getline(file, line)) {
        for (int i = 0; i < (int) line.length(); i++) {
            position = i;
            if (line [i] == '|') {
                break;
            }
            buffer += line[i];
        }

        user.userID = atoi (buffer.c_str());
        buffer = "";

        for (int i = position + 1; i < (int) line.length(); i++) {
            position = i;
            if (line [i] == '|') {
                break;
            }
            buffer += line[i];
        }
        user.login = buffer;
        buffer = "";
        for (int i = position + 1; i < (int)line.length(); i++) {
            buffer += line[i];
        }
        user.password = buffer;
        buffer = "";
        userIndex.push_back(user);
    }
    file.close();
}

int login (vector <User> &userIndex) {
    string login, password;
    cout << "Login: ";
    login = readLine();
    cout << "Password: ";
    password = readLine();

    for (int i = 0; i < (int) userIndex.size(); i++) {
        if (userIndex[i].login == login && userIndex[i].password == password) {
            cout << "Successfuly logged in." << endl;
            system ("PAUSE");
            return userIndex[i].userID;
        }
    }
    cout << "Invalid data." << endl;
    system ("PAUSE");
    return 0;
}

int loginMenu () {
    vector <User> userIndex;
    char choice;
    int id;
    loadUserIndex(userIndex);

    while(1) {
        system("cls");
        cout << "===== ADRESS BOOK =====" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Close program" << endl;

        choice = getch();

        switch (choice) {
        case '1':
            registration (userIndex);
            break;

        case '2':
            id = login (userIndex);
            return id;
            break;

        case '3':
            exit (0);
            break;

        default:
            while (choice>'3' || choice<'1') {
                cout << "Wrong option. Please input a number from 1 to 3." << endl;
                choice = getch();
            }
            break;
        }
    }
}

void saveAdressBook(Recipient addedPerson) {
    fstream file;

    file.open("adress_book.txt", ios::out | ios::app);
    if (!file.good()) {
        cout << "File corrupted..." << endl;
        exit(0);
    }
    file << addedPerson.recipientID << '|';
    file << addedPerson.userID << '|';
    file << addedPerson.name << '|';
    file << addedPerson.surname << '|';
    file << addedPerson.phone << '|';
    file << addedPerson.email << '|';
    file << addedPerson.adress << endl;

    file.close();
}

void addRecipient (vector <Recipient> &adressBook, int userID, int &lastEntryID) {
    Recipient contact;

    contact.recipientID = lastEntryID + 1;
    contact.userID = userID;
    cout << "Input name: " << endl;
    contact.name = readLine();
    cout << "Input surname: " << endl;
    contact.surname = readLine();
    cout << "Input phone number: " << endl;
    contact.phone = readLine();
    cout << "Input email: " << endl;
    contact.email = readLine();
    cout << "Input adress: " << endl;
    contact.adress = readLine();

    adressBook.push_back(contact);
    saveAdressBook(contact);
    lastEntryID++;
}

int loadAdressBook (vector <Recipient> &adressBook, int loggedUserID) {
    fstream file;
    string line, buffer;
    int position = 0;
    int lastEntryID = 0;
    Recipient contact;

    file.open("adress_book.txt", ios::in);
    if (!file.good()) {
        cout << "file does not exist" << endl;
        return 0;
    }
    while(getline(file, line)) {

        for (int i = 0; i < (int) line.length(); i++) {
            position = i;
            if (line [i] == '|') {
                break;
            }
            buffer += line[i];
        }

        lastEntryID = atoi (buffer.c_str());
        buffer = "";

        for (int i = position + 1; i < (int) line.length(); i++) {
            position = i;
            if (line [i] == '|') {
                break;
            }
            buffer += line[i];
        }

        if (loggedUserID == atoi (buffer.c_str())) {
            contact.recipientID = lastEntryID;
            contact.userID = atoi (buffer.c_str());
            buffer = "";

            for (int i = position + 1; i < (int) line.length(); i++) {
                position = i;
                if (line [i] == '|') {
                    break;
                }
                buffer += line[i];
            }
            contact.name = buffer;
            buffer = "";

            for (int i = position + 1; i < (int) line.length(); i++) {
                position = i;
                if (line [i] == '|') {
                    break;
                }
                buffer += line[i];
            }
            contact.surname = buffer;
            buffer = "";

            for (int i = position + 1; i < (int) line.length(); i++) {
                position = i;
                if (line [i] == '|') {
                    break;
                }
                buffer += line[i];
            }
            contact.phone = buffer;
            buffer = "";

            for (int i = position + 1; i < (int) line.length(); i++) {
                position = i;
                if (line [i] == '|') {
                    break;
                }
                buffer += line[i];
            }
            contact.email = buffer;
            buffer = "";

            for (int i = position + 1; i < (int) line.length(); i++) {
                buffer += line[i];
            }
            contact.adress = buffer;
            buffer = "";
            adressBook.push_back(contact);
        }
        buffer = "";
    }
    file.close();
    return lastEntryID;
}

void displayAdressBook (vector <Recipient> &adressBook, int loggedUserID) {
    if (adressBook.empty()) {
        cout << "Your adress book is empty" << endl;
        system("PAUSE");
    } else {
        cout << endl << "===Your adress book===" << endl << endl;
        for (int i = 0; i < (int) adressBook.size(); i++) {
            if (loggedUserID == adressBook[i].userID) {
                cout << "Contact ID: " << adressBook[i].recipientID << endl;
                cout << "Name: " << adressBook[i].name << endl;
                cout << "Surname: " << adressBook[i].surname << endl;
                cout << "Phone number: " << adressBook[i].phone << endl;
                cout << "E-mail: " << adressBook[i].email << endl;
                cout << "Adress: " << adressBook[i].adress << endl << endl;
            }
        }
        system("PAUSE");
    }
}

void saveAfterDeleting (int removedRecipientID) {
    fstream file, tempFile;
    string line, buffer;

    file.open("adress_book.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    while (getline(file, line)) {
        for (int i = 0; i < (int) line.length(); i++) {
            if (line [i] == '|') {
                break;
            }
            buffer += line[i];
        }
        if (atoi (buffer.c_str()) != removedRecipientID) {
            tempFile << line << endl;
        }
        buffer = "";
    }
    file.close();
    tempFile.close();

    remove("adress_book.txt");
    rename("temp.txt", "adress_book.txt");
}

void deleteRecipient (vector <Recipient> &adressBook) {
    int id = 0;
    char choice;
    bool found = false;

    if(adressBook.size() == 0) {
        cout << "Your adress book is empty!" << endl;
        system("PAUSE");
        return;
    }

    cout << "Input ID number of recipient that you would like to delete:" << endl;
    id = atoi (readLine().c_str());

    for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
        if (itr->recipientID == id) {
            found = true;
            cout << "Please press 't' to confirm:" << endl;
            choice = getch();
            if (choice == 't') {
                adressBook.erase(itr);
                saveAfterDeleting(id);
                cout << "Recipient was deleted." << endl;
                system("PAUSE");
            } else {
                cout << "Recipient was not deleted." << endl;
                system("PAUSE");
                return;
            }
        }
    }
    if(!found) {
        cout << "There is no user with that ID." << endl;
        system("PAUSE");
    }
}

void saveAfterEditing (vector <Recipient> &adressBook, int editedRecipientID) {
    fstream file, tempFile;
    string line, buffer;

    file.open("adress_book.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    while (getline(file, line)) {
        for (int i = 0; i < (int) line.length(); i++) {
            if (line [i] == '|') {
                break;
            }
            buffer += line[i];
        }
        if (atoi (buffer.c_str()) != editedRecipientID) {
            tempFile << line << endl;
        } else {
            for(int i = 0; i < (int) adressBook.size(); i++) {
                if (editedRecipientID == adressBook[i].recipientID) {
                    tempFile << adressBook[i].recipientID << '|';
                    tempFile << adressBook[i].userID << '|';
                    tempFile << adressBook[i].name << '|';
                    tempFile << adressBook[i].surname << '|';
                    tempFile << adressBook[i].phone << '|';
                    tempFile << adressBook[i].email << '|';
                    tempFile << adressBook[i].adress << endl;
                }
            }
        }
        buffer = "";
    }
    file.close();
    tempFile.close();

    remove("adress_book.txt");
    rename("temp.txt", "adress_book.txt");
}

void editRecipient (vector <Recipient> &adressBook) {
    char choice;
    int id = 0;
    bool found = false;
    string newData;

    if(adressBook.size() == 0) {
        cout << "Your adress book is empty!" << endl;
        system("PAUSE");
        return;
    }

    cout << "Input Recipent ID to start editing: " << endl;
    id = atoi (readLine().c_str());

    for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
        if (itr->recipientID == id) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "There is no user with that ID." << endl;
        system ("PAUSE");
        return;
    }

    while (1) {
        system("cls");
        cout << "===== EDITION MENU =====" << endl;
        cout << "1. Edit name" << endl;
        cout << "2. Edit surname" << endl;
        cout << "3. Edit phone number" << endl;
        cout << "4. Edit e-mail" << endl;
        cout << "5. Edit adress" << endl;
        cout << "6. Return to previous menu" << endl;

        choice = getch();

        switch (choice) {
        case '1':
            for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
                if (itr->recipientID == id) {
                    cout << "Input new name: " << endl;
                    newData = readLine();
                    itr->name = newData;
                    saveAfterEditing (adressBook, id);
                    cout << "Data changed correctly." << endl;
                    system("PAUSE");
                }
            }
            break;

        case '2':
            for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
                if (itr->recipientID == id) {
                    cout << "Input new surname: " << endl;
                    newData = readLine();
                    itr->surname = newData;
                    saveAfterEditing (adressBook, id);
                    cout << "Data changed correctly." << endl;
                    system("PAUSE");
                }
            }
            break;

        case '3':
            for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
                if (itr->recipientID == id) {
                    cout << "Input new phone number: " << endl;
                    newData = readLine();
                    itr->phone = newData;
                    saveAfterEditing (adressBook, id);
                    cout << "Data changed correctly." << endl;
                    system("PAUSE");
                }
            }
            break;

        case '4':
            for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
                if (itr->recipientID == id) {
                    cout << "Input new email: " << endl;
                    newData = readLine();
                    itr->email = newData;
                    saveAfterEditing (adressBook, id);
                    cout << "Data changed correctly." << endl;
                    system("PAUSE");
                }
            }
            break;

        case '5':
            for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
                if (itr->recipientID == id) {
                    cout << "Input new adress: " << endl;
                    newData = readLine();
                    itr->adress = newData;
                    saveAfterEditing (adressBook, id);
                    cout << "Data changed correctly." << endl;
                    system("PAUSE");
                }
            }
            break;

        case '6':
            return;
            break;

        default:
            while (choice>'6' || choice<'1') {
                cout << "Wrong option. Please input a number from 1 to 6." << endl;
                choice = getch();
            }
            break;
        }
    }
}

void searchByName (vector <Recipient> adressBook) {
    string name;
    bool recipientIsFound;

    recipientIsFound = false;
    cout << "Input the name: ";
    name = readLine();

    for (int i = 0; i < (int) adressBook.size(); i++) {
        if (adressBook[i].name == name) {
            cout << "Name: " << adressBook[i].name << endl;
            cout << "Surname: " << adressBook[i].surname << endl;
            cout << "Phone number: " << adressBook[i].phone << endl;
            cout << "E-mail: " << adressBook[i].email << endl;
            cout << "Adress: " << adressBook[i].adress << endl << endl;
            recipientIsFound = true;
        }
    }

    if(recipientIsFound) {
        system("PAUSE");
    } else {
        cout << "There is no people with that name in your adress book." << endl;
        system("PAUSE");
    }

}

void searchBySurname (vector <Recipient> adressBook) {
    string surname;
    bool recipientIsFound;

    recipientIsFound = false;
    cout << "Input the surname: ";
    surname = readLine();

    for (int i = 0; i < (int) adressBook.size(); i++) {
        if (adressBook[i].surname == surname) {
            cout << "Name: " << adressBook[i].name << endl;
            cout << "Surname: " << adressBook[i].surname << endl;
            cout << "Phone number :" << adressBook[i].phone << endl;
            cout << "E-mail: " << adressBook[i].email << endl;
            cout << "Adress: " << adressBook[i].adress << endl << endl;
            recipientIsFound = true;
        }
    }
    if(recipientIsFound) {
        system("PAUSE");
    }

    else {
        cout << "There is no people with that surname in your adress book." << endl;
        system("PAUSE");
    }
}

void passwordChange (int loggedUserID) {
    vector <User> userIndex;
    loadUserIndex(userIndex);
    cout << "New password: ";
    string newPassword = readLine();

    for (int i = 0; i < (int) userIndex.size(); i++) {
        if (userIndex[i].userID == loggedUserID) {
            userIndex[i].password = newPassword;
            saveUserIndex (userIndex);
            cout << "Password changed." << endl;
            system ("PAUSE");
        }
    }
}

void bookMenu(int userID) {
    vector <Recipient> adressBook;
    char choice;
    int lastEntryID = loadAdressBook(adressBook, userID);

    while (1) {
        system("cls");
        cout << "===== ADRESS BOOK =====" << endl;
        cout << "1. Add new Recipient" << endl;
        cout << "2. Search by name" << endl;
        cout << "3. Search by surname" << endl;
        cout << "4. Display all recipients" << endl;
        cout << "5. Delete recipient" << endl;
        cout << "6. Edit recipient" << endl;
        cout << "-----------------" << endl;
        cout << "7. Password change" << endl;
        cout << "8. Sign out" << endl;

        choice = getch();

        switch (choice) {
        case '1':
            addRecipient (adressBook, userID, lastEntryID);
            break;

        case '2':
            searchByName(adressBook);
            break;

        case '3':
            searchBySurname(adressBook);
            break;

        case '4':
            displayAdressBook(adressBook, userID);
            break;

        case '5':
            deleteRecipient(adressBook);
            break;

        case '6':
            editRecipient(adressBook);
            break;

        case '7':
            passwordChange(userID);;
            break;

        case '8':
            adressBook.clear();
            return;
            break;

        default:
            while (choice>'8' || choice<'1') {
                cout << "Wrong option. Please input a number from 1 to 9." << endl;
                choice = getch();
            }
            break;
        }
    }
}

int main() {
    int userID = 0;

    while(1) {
        userID = loginMenu();
        if (userID !=0) {
            bookMenu(userID);
        }
    }

    return 0;
}
