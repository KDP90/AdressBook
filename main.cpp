#include <iostream>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct Recipient {
    int id;
    string name, surname, phoneNumber, email, adress;
};

string getName () {
    string name;
    cout << "Input name: " << endl;
    cin >> name;
    transform(name.begin(),name.end(),name.begin(),::tolower);
    return name;
}

string getSurname () {
    string surname;
    cout << "Input surname: " << endl;
    cin >> surname;
    transform(surname.begin(),surname.end(),surname.begin(),::tolower);
    return surname;
}

string getPhoneNumber () {
    string phoneNumber;
    cout << "Input phone number (has to consist of 9 digits): " << endl;
    cin >> phoneNumber;
    for (int i = 0; i < 9; i++) {
        if (phoneNumber.length()>9) {
            cout << "Invalid number. Phone number has to consist of 9 digits. Try again." << endl;
            cin >> phoneNumber;
            i = 0;
        }
        if (phoneNumber[i] >'9' || phoneNumber[i] < '0') {
            cout << "Invalid number. Please try again and input digits only." << endl;
            cin >> phoneNumber;
            i = 0;
        }

    }
    phoneNumber.insert(6, "-");
    phoneNumber.insert(3, "-");
    return phoneNumber;
}

string getEmail () {
    string email;
    cout << "Input the e-mail: " << endl;
    cin >> email;
    for (int i = 0; i < (int) email.length(); i++) {
        if (email[i] == '@') {
            break;
        } else if (i == (int) email.length()-1) {
            cout << "This e-mail is invaild. E-mail has to contain @." << endl;
            cin >> email;
            i = 0;
        } else {
            continue;
        }
    }
    return email;
}

string getAdress () {
    string adress;
    cout << "Input the adress:" << endl;
    cin.sync();
    getline(cin,adress);
    return adress;
}

void saveInTextFile (vector <Recipient> &adressBook, int numberOfExistingRecipients) {
    fstream file;

    file.open("ksiazka_adresowa.txt", ios::out);

    for (int i = 0; i < numberOfExistingRecipients; i++) {
        file << adressBook[i].id << '|' << adressBook[i].name << '|' << adressBook[i].surname << '|' << adressBook[i].phoneNumber << '|' << adressBook[i].email << '|' << adressBook[i].adress << endl;
    }
    file.close();
}

int addNewRecipientToAdressBook(vector <Recipient> &adressBook, int numberOfExistingRecipients) {
    Recipient contact;
    string name, surname, phoneNumber, email, adress;

    name = getName ();
    surname = getSurname ();
    phoneNumber = getPhoneNumber ();
    email = getEmail ();
    adress = getAdress ();

    for (int i = 0; i < numberOfExistingRecipients; i++) {
        if (adressBook[i].name == name && adressBook[i].surname == surname && adressBook[i].phoneNumber == phoneNumber && adressBook[i].email == email && adressBook[i].adress == adress) {
            cout << "That recipient is already exist in your adress book.";
            system("PAUSE");
            return numberOfExistingRecipients;
        }
    }
    if (adressBook.empty()) {
        contact.id = numberOfExistingRecipients + 1;
        contact.name = name;
        contact.surname = surname;
        contact.phoneNumber = phoneNumber;
        contact.email = email;
        contact.adress = adress;
    } else {
        auto lastRecipientId = adressBook.back();
        contact.id = lastRecipientId.id + 1;
        contact.name = name;
        contact.surname = surname;
        contact.phoneNumber = phoneNumber;
        contact.email = email;
        contact.adress = adress;
    }
    adressBook.push_back(contact);

    saveInTextFile (adressBook, numberOfExistingRecipients +1);
    cout << "Data added correctly." << endl;
    system("PAUSE");

    return numberOfExistingRecipients + 1;
}

void searchByName (vector <Recipient> &adressBook, int numberOfExistingRecipients) {
    string name;
    bool recipientIsFound;

    recipientIsFound = false;
    cout << "Input the name: ";
    cin >> name;
    transform(name.begin(),name.end(),name.begin(),::tolower);

    for (int i = 0; i < numberOfExistingRecipients; i++) {
        if (adressBook[i].name == name) {
            cout << "Name: " << adressBook[i].name << endl;
            cout << "Surname: " << adressBook[i].surname << endl;
            cout << "Phone number: " << adressBook[i].phoneNumber << endl;
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

void searchBySurname (vector <Recipient> &adressBook, int numberOfExistingRecipients) {
    string surname;
    bool recipientIsFound;

    recipientIsFound = false;
    cout << "Input the surname: ";
    cin >> surname;
    transform(surname.begin(),surname.end(),surname.begin(),::tolower);

    for (int i = 0; i < numberOfExistingRecipients; i++) {
        if (adressBook[i].surname == surname) {
            cout << "Name: " << adressBook[i].name << endl;
            cout << "Surname: " << adressBook[i].surname << endl;
            cout << "Phone number :" << adressBook[i].phoneNumber << endl;
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

void displayAllRecipients (vector <Recipient> &adressBook, int numberOfExistingRecipients) {
    cout << endl << "===Your adress book===" << endl << endl;
    for (int i = 0; i < numberOfExistingRecipients; i++) {
        cout << "Contact ID: " << adressBook[i].id << endl;
        cout << "Name: " << adressBook[i].name << endl;
        cout << "Surname: " << adressBook[i].surname << endl;
        cout << "Phone number: " << adressBook[i].phoneNumber << endl;
        cout << "E-mail: " << adressBook[i].email << endl;
        cout << "Adress: " << adressBook[i].adress << endl << endl;
    }
    system("PAUSE");
}

int readFromTextFile (vector <Recipient> &adressBook) {
    fstream file;
    Recipient contact;
    int lineNumber = 0;
    string lineOfText;
    string buffer = "";
    char separator = '|';
    size_t separatorIndex;
    int recipientElement = 0;
    int firstLetterIndex = 0;

    file.open("ksiazka_adresowa.txt", ios::in);

    if(!file.good()) {
        return 0;
    }

    while(getline(file, lineOfText)) {
        separatorIndex = lineOfText.find(separator);
        for (int i = 0; i < (int)separatorIndex; i++) {
            buffer += lineOfText[i];
        }
        contact.id = atoi(buffer.c_str());

        buffer = "";

        do {
            recipientElement++;
            firstLetterIndex = (int)separatorIndex + 1;
            separatorIndex = lineOfText.find (separator, firstLetterIndex);

            switch(recipientElement) {
            case 1:
                for (int i = firstLetterIndex; i < (int)separatorIndex; i++) {
                    buffer += lineOfText[i];
                }
                contact.name = buffer;
                break;

            case 2:
                for (int i = firstLetterIndex; i < (int)separatorIndex; i++) {
                    buffer += lineOfText[i];
                }
                contact.surname = buffer;
                break;

            case 3:
                for (int i = firstLetterIndex; i < (int)separatorIndex; i++) {
                    buffer += lineOfText[i];
                }
                contact.phoneNumber = buffer;
                break;

            case 4:
                for (int i = firstLetterIndex; i < (int)separatorIndex; i++) {
                    buffer += lineOfText[i];
                }
                contact.email = buffer;
                break;

            case 5:
                for (int i = firstLetterIndex; i < (int)lineOfText.length(); i++) {
                    buffer += lineOfText[i];
                }
                contact.adress = buffer;
                break;
            }
            buffer = "";


        } while (separatorIndex != string::npos);
        adressBook.push_back(contact);
        recipientElement = 0;
        lineNumber++;
    }
    file.close();
    return lineNumber;
}

int deleteRecipient (vector <Recipient> &adressBook, int numberOfExistingRecipients) {
    int id = 0;
    char userChoice;
    bool found = false;

    if(adressBook.size() == 0){
        cout << "Your adress book is empty!" << endl;
        system("PAUSE");
        return numberOfExistingRecipients;
    }

    cout << "Input ID number of recipient that you would like to delete:" << endl;
    cin >> id;

    for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
        if (itr->id == id) {
            found = true;
            cout << "Please press 't' to confirm:" << endl;
            userChoice = getch();
            if (userChoice == 't') {
                adressBook.erase(itr);
                cout << "Recipient was deleted." << endl;
                system("PAUSE");
                saveInTextFile (adressBook, numberOfExistingRecipients - 1);
                return numberOfExistingRecipients - 1;
            } else {
                cout << "Recipient was not deleted." << endl;
                system("PAUSE");
                return numberOfExistingRecipients;
            }
        }
    }
    if(!found) {
        cout << "There is no user with that ID." << endl;
        system("PAUSE");
    }
    return numberOfExistingRecipients;
}

void editRecipient (vector <Recipient> &adressBook, int numberOfExistingRecipients) {
    char userChoice;
    int id = 0;
    bool found = false;
    string newData;

    if(adressBook.size() == 0){
        cout << "Your adress book is empty!" << endl;
        system("PAUSE");
        return;
    }

    cout << "Input Recipent ID to start editing: " << endl;
    cin >> id;

    for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
        if (itr->id == id) {
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

        userChoice = getch();

        switch (userChoice) {
        case '1':
            for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
                if (itr->id == id) {
                    newData = getName ();
                    itr->name = newData;
                    saveInTextFile (adressBook, numberOfExistingRecipients);
                    cout << "Data changed correctly." << endl;
                    system("PAUSE");
                }
            }
            break;

        case '2':
            for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
                if (itr->id == id) {
                    newData = getSurname ();
                    itr->surname = newData;
                    saveInTextFile (adressBook, numberOfExistingRecipients);
                    cout << "Data changed correctly." << endl;
                    system("PAUSE");
                }
            }
            break;

        case '3':
            for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
                if (itr->id == id) {
                    newData = getPhoneNumber ();
                    itr->phoneNumber = newData;
                    saveInTextFile (adressBook, numberOfExistingRecipients);
                    cout << "Data changed correctly." << endl;
                    system("PAUSE");
                }
            }
            break;

        case '4':
            for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
                if (itr->id == id) {
                    newData = getEmail ();
                    itr->email = newData;
                    saveInTextFile (adressBook, numberOfExistingRecipients);
                    cout << "Data changed correctly." << endl;
                    system("PAUSE");
                }
            }
            break;

        case '5':
            for (auto itr = adressBook.begin(); itr <= adressBook.end(); itr++) {
                if (itr->id == id) {
                    newData = getAdress ();
                    itr->adress = newData;
                    saveInTextFile (adressBook, numberOfExistingRecipients);
                    cout << "Data changed correctly." << endl;
                    system("PAUSE");
                }
            }
            break;

        case '6':
            return;
            break;

        default:
            while (userChoice>'6' || userChoice<'1') {
                cout << "Wrong option. Please input a number from 1 to 6." << endl;
                userChoice = getch();
            }
            break;
        }
    }
}

int main() {
    vector <Recipient> adressBook;
    int numberOfExistingRecipients = readFromTextFile (adressBook);
    char userChoice;

    while (1) {
        system("cls");
        cout << "===== ADRESS BOOK =====" << endl;
        cout << "1. Add new Recipient" << endl;
        cout << "2. Search by name" << endl;
        cout << "3. Search by surname" << endl;
        cout << "4. Display all recipients" << endl;
        cout << "5. Delete recipient" << endl;
        cout << "6. Edit recipient" << endl;
        cout << "7. Close" << endl;

        userChoice = getch();

        switch (userChoice) {
        case '1':
            numberOfExistingRecipients = addNewRecipientToAdressBook (adressBook, numberOfExistingRecipients);
            break;

        case '2':
            searchByName(adressBook, numberOfExistingRecipients);
            break;

        case '3':
            searchBySurname(adressBook, numberOfExistingRecipients);
            break;

        case '4':
            displayAllRecipients(adressBook, numberOfExistingRecipients);
            break;

        case '5':
            numberOfExistingRecipients = deleteRecipient(adressBook, numberOfExistingRecipients);
            break;

        case '6':
            editRecipient(adressBook, numberOfExistingRecipients);
            break;

        case '7':
            return 0;

        default:
            while (userChoice>'7' || userChoice<'1') {
                cout << "Wrong option. Please input a number from 1 to 7." << endl;
                userChoice = getch();
            }
            break;
        }
    }

    return 0;
}


