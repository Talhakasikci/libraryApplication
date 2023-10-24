#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

class Books {
private:
    string name;
    string author;
    int year;
protected:
    string type;
    string isbn;
public:
    Books() {};
    Books(string name, string author, string type, int year, string isbn) {
        this->name = name;
        this->author = author;
        this->year = year;
        this->isbn = isbn;
        this->type = type;

        ofstream bookAdd;
        bookAdd.open("Books.txt", ios::app);
        bookAdd << name << setw(25) << author << setw(25) << type << setw(25) << isbn << setw(25) << year << setw(25) << endl;
        bookAdd.close();

        if (type == "horror") {
            ofstream types;
            types.open("HorrorBooks.txt", ios::app);
            types << name << setw(25) << isbn << endl;
            types.close();
        }
        else if (type == "science-fiction") {
            ofstream types;
            types.open("scienceFictionBooks.txt", ios::app);
            types << name << setw(25) << isbn << endl;
            types.close();
        }
        else if (type == "adventure") {
            ofstream types;
            types.open("AdventureBooks.txt", ios::app);
            types << name << setw(25) << isbn << endl;
            types.close();
        }
        else if (type == "fantasy") {
            ofstream types;
            types.open("FantasyBooks.txt", ios::app);
            types << name << setw(25) << isbn << endl;
            types.close();
        }
        else {
            ofstream types;
            types.open("MixBooks.txt", ios::app);
            types << name << setw(25) << isbn << endl;
            types.close();
        }

    }
    void bookDelete(string isbn) {
        ifstream old("Books.txt", ios::in);
        ofstream Bookdelete("swap.txt", ios::app);
        string line;
        int isbnControl = 0;
        int control = 0;
        while (getline(old, line)) {
            if (control == 0) {
                if (line.find(isbn) == string::npos) {

                    Bookdelete << line << endl;

                }
                else {
                    control++;
                    isbnControl++;
                }


            }
            else
                Bookdelete << line << endl;

        }
        if (isbnControl == 0) {
            cout << "There is no book which has this isbn" << endl;
        }
        else
            cout << "Book has been deleted" << endl;

        old.close();
        Bookdelete.close();
        remove("Books.txt");
        rename("swap.txt", "Books.txt");
    }





};


class Member {
private:
    string name;
    string surname;
protected:
    string id;
public:

    Member() {

    };
    Member(string name, string surname, string id) {
        this->name = name;
        this->surname = surname;
        this->id = id;


    }


    bool membershipCheck(string id) {

        ifstream membershipCheck;
        string line;

        membershipCheck.open("Members.txt", ios::in);
        while (getline(membershipCheck, line)) {
            if (line.find(id) != string::npos)
                return true;
        }
        membershipCheck.close();
        return false;
    }

    void addSubscription(string id) {

        if (!membershipCheck(id)) {

            ofstream addMember;
            addMember.open("Members.txt", ios::app);
            addMember << name << setw(25) << surname << setw(25) << id << endl;
            addMember.close();
            cout << "Student added" << endl;
        }
        else
            cout << "There is a student with this id!" << endl;

    }

    void membershipDelete(string id) {

        if (membershipCheck(id)) {
            ifstream old("Members.txt");
            ofstream memberDelete("gecici.txt");
            string line;

            ifstream oldLease("Rental.txt", ios::in);
            ofstream newLease("geciciKira.txt", ios::app);
            while (getline(oldLease, line)) {
                if (line.find(id) == string::npos) {
                    newLease << line << endl;
                }
                else
                    continue;
            }
            oldLease.close();
            newLease.close();

            remove("Rental.txt");
            rename("geciciKira.txt", "Rental.txt");

            while (getline(old, line)) {
                if (line.find(id) == string::npos) {
                    memberDelete << line << endl;
                }
            }
            old.close();
            memberDelete.close();
            remove("Members.txt");
            rename("gecici.txt", "Members.txt");
            cout << "Member has been deleted" << endl;
        }
        else
            cout << "There is no Member which has this id" << endl;


    }

};
void allbooks();
class Rent : public Member, public Books {
public:

    Rent() {

    }
    Rent(string id, string isbn) {
        this->id = id;
        this->isbn = isbn;
    }

    void consistency() {
        int mainFileControl = 0;
        int rentalFileControl = 0;

        if (membershipCheck(id)) {
            ifstream mainFile;
            mainFile.open("Books.txt", ios::in);
            ofstream forRent;
            forRent.open("Rental.txt", ios::app);
            ifstream rentalControl;
            rentalControl.open("Rental.txt", ios::in);
            string line;
            while (getline(mainFile, line)) {
                if (line.find(isbn) != string::npos)
                    mainFileControl++;
            }
            while (getline(rentalControl, line)) {
                if (line.find(isbn) != string::npos)
                    rentalFileControl++;
            }
            mainFile.close();
            rentalControl.close();

            if (mainFileControl > rentalFileControl) {
                cout << "Member can rent this book" << endl;
                forRent << id << setw(25) << isbn << endl;

            }
            else if (mainFileControl == 0) {
                cout << "No such book was found" << endl;
            }
            else
                cout << "all copies of this book are leased" << endl;



            forRent.close();
        }
        else
            cout << "No member found with this id" << endl;
    }

    void rentalReturn() {

        bool rentalFound = false;

        ifstream old;
        old.open("Rental.txt", ios::in);
        ofstream forRent;
        forRent.open("gecici.txt", ios::app);
        string line;
        while (getline(old, line)) {
            string info1, info2;
            stringstream ss(line);

            ss >> info1 >> setw(25) >> info2;
            if (!rentalFound) {
                if (!(info1 == id && info2 == isbn)) {
                    forRent << line << endl;
                }
                else {
                    rentalFound = true;
                    continue;
                }
            }
            else
                forRent << line << endl;
        }



        old.close();
        forRent.close();

        remove("Rental.txt");
        rename("gecici.txt", "Rental.txt");

        if (rentalFound) {
            cout << "the book was returned" << endl;
        }
        else if (!rentalFound)
            cout << "No such rental was found." << endl;
    }

};


string bookName;
string authorName;
string isbn;
int year;
string types;
string memberName;
string memberSurname;
string memberId;

void BookAdd() {
    cin.ignore();
    cout << "Book Title: ";
    getline(cin, bookName);

    cout << "Author Name: ";
    getline(cin, authorName);

    cout << "type: ";
    getline(cin, types);

    cout << "year: ";
    cin >> year;
    cin.ignore();
    cout << "Isbn: ";
    getline(cin, isbn);

    cout << endl;
    Books newBook(bookName, authorName, types, year, isbn);
    cout << "Book added" << endl;
    cout << endl;
}

void BooksDelete() {
    cout << "Enter the isbn number of the book you want to delete: ";
    cin.ignore();
    getline(cin, isbn);
    cout << endl;
    Books deleteBook;
    deleteBook.bookDelete(isbn);
    cout << endl;
}

void memberadd() {
    cout << "Add member system:" << endl;
    cin.ignore();
    cout << "New Member Name: ";
    getline(cin, memberName);

    cout << "New Member Surname: ";
    getline(cin, memberSurname);

    cout << "New Member ID: ";
    getline(cin, memberId);

    Member newMember(memberName, memberSurname, memberId);
    newMember.addSubscription(memberId);
    cout << endl;
}

void memberDelete() {
    cout << "Please enter the id of the member you want to delete: ";
    cin.ignore();
    getline(cin, memberId);
    Member memberDelete("", "", "");
    memberDelete.membershipDelete(memberId);
    cout << endl;
}


void rent() {
    cout << "Please enter your student number: ";
    cin.ignore();
    getline(cin, memberId);
    cout << "Please enter book isbn: ";
    getline(cin, isbn);

    Rent rent(memberId, isbn);
    rent.consistency();
    cout << endl;
}

void borrow() {


    cout << "Book Return: " << endl;
    cout << "Please enter the number of the returning student: ";
    cin.ignore();
    getline(cin, memberId);
    cout << "Enter Book Isbn: ";
    getline(cin, isbn);

    Rent rebate(memberId, isbn);
    rebate.rentalReturn();
    cout << endl;
}


void allbooks()
{
    cout << "HorrorBooks           [1]" << endl;
    cout << "science-FictionBooks  [2]" << endl;
    cout << "Adventure Books       [3]" << endl;
    cout << "Fantasy Books         [4]" << endl;
    int choice;
    int i = 1;
    string line;
    cin >> choice;
    ifstream read;
    if (choice == 1)
    {
        read.open("HorrorBooks.txt", ios::in);
    }
    else if (choice == 2) {
        read.open("scienceFictionBooks.txt", ios::in);
    }
    else if (choice == 3) {
        read.open("AdventureBooks.txt", ios::in);
    }
    else if (choice == 4) {
        read.open("FantasyBooks.txt", ios::in);
    }
    else {
        cout << "You Entered Wrong Number" << endl;
        i = 0;
    }
    if (i != 0) {
        while (getline(read, line)) {
            {
                cout << line << endl;
            }
        }
    }
    read.close();
    cout << endl;
}

void advice() {
    ifstream allBooks;
    allBooks.open("Books.txt", ios::in);
    string line;

    while (getline(allBooks, line)) {
        {
            cout << line << endl;
        }
    }
    allBooks.close();
    cout << endl;
}

int main()
{


    int numeral;
    while (true) {
        cout << "**************************************************" << endl;
        cout << "**** please select the action you want to do! ****" << endl;
        cout << "**************************************************" << endl;
        cout << "Adding Books        [1]" << endl;
        cout << "Deleting a Book     [2]" << endl;
        cout << "New User            [3]" << endl;
        cout << "User Deletion       [4]" << endl;
        cout << "Book Rentals        [5]" << endl;
        cout << "Book Returns        [6]" << endl;
        cout << "Books Types         [7]" << endl;
        cout << "book Recommendation [8]" << endl;
        cout << "Exit                [9]" << endl;
        cout << endl;


        cin >> numeral;
        if (numeral == 1) {
            BookAdd();
        }
        else if (numeral == 2) {
            BooksDelete();
        }
        else if (numeral == 3) {
            memberadd();
        }
        else if (numeral == 4) {
            memberDelete();
        }
        else if (numeral == 5) {
            rent();
        }
        else if (numeral == 6) {
            borrow();
        }
        else if (numeral == 7)
        {
            allbooks();
        }
        else if (numeral == 8) {
            advice();
        }
        else if (numeral == 9)
            break;
        else
            cout << "please enter a number between 1-9" << endl;
    }
}


