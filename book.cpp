#include "book.h"
#include <iostream>
#include <sstream>

using namespace std;

// Les deux constructeurs de l'objet Book.
// Le premier sans paramètre et le deuxième avec des paramètres
Book::Book() : title(""), author(""), isbn(""), isAvailable(true), borrowerName("")
{
}

Book::Book(const string &title, const string &author, const string &isbn)
    : title(title), author(author), isbn(isbn), isAvailable(true), borrowerName("")
{
}

// Getters pour les 5 variables de l'objet Book.
string Book::getTitle() const
{
    return title;
}

string Book::getAuthor() const
{
    return author;
}

string Book::getISBN() const
{
    return isbn;
}

bool Book::getAvailability() const
{
    return isAvailable;
}

string Book::getBorrowerName() const
{
    return borrowerName;
}

// Setters des cinq variable de l'objet Book.
void Book::setTitle(const string &title)
{
    this->title = title;
}

void Book::setAuthor(const string &author)
{
    this->author = author;
}

void Book::setISBN(const string &isbn)
{
    this->isbn = isbn;
}

void Book::setAvailability(bool isAvailable)
{
    this->isAvailable = isAvailable;
}

void Book::setBorrowerName(const string &borrowerName)
{
    this->borrowerName = borrowerName;
}

// Méthode checkOut.
// Met la disponibilitée à false et met le nom de l'emprunt passé en paramètre.
void Book::checkOut(const string &borrowerName)
{
    this->isAvailable = false;
    this->borrowerName = borrowerName;
}

// Méthode returnBook.
// Met la disponibilitée à true et met le nom de l'emprunt à ""
void Book::returnBook()
{
    this->isAvailable = true;
    this->borrowerName = "";
}

// Méthode toString.
string Book::toString() const
{
    return title + " écrit par " + author;
}

// Méthode toFileFormat.
string Book::toFileFormat() const
{
    string result = title + "|" + author + "|" + isbn + "|";
    if (isAvailable)
    {
        result += "1|";
    }
    else
    {
        result += "0|" + borrowerName;
    }
    return result;
}

// Méthode fromFileFormat.
void Book::fromFileFormat(const string &line)
{
    stringstream ss(line);
    string token;

    getline(ss, title, '|');
    getline(ss, author, '|');
    getline(ss, isbn, '|');

    string available;
    getline(ss, available, '|');

    if (stoi(available) == 0)
    {
        isAvailable = false;
        getline(ss, borrowerName, '|');
    }
    else
    {
        isAvailable = true;
    }
}