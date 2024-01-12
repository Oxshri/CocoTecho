#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Book {
public:
    string name;
    string checkoutDate;
    string returnDate;
};

class Member {
public:
    string name;
    vector<Book> books;
};

string generateRandomDate() {
    string date(10, ' ');

    time_t now = time(0);
    tm* ltm = localtime(&now);

    int year = 2023;
    int month = 1 + rand() % 12;
    int day = 1 + rand() % 28;

    ltm->tm_year = year - 1900;
    ltm->tm_mon = month - 1;
    ltm->tm_mday = day;

    strftime(&date[0], sizeof(date), "%Y-%m-%d", ltm);

    return date;
}

int calculateDaysDifference(const string& returnDate, const string& checkoutDate) {
    struct tm tmReturn, tmCheckout;

    strptime(returnDate.c_str(), "%Y-%m-%d", &tmReturn);
    strptime(checkoutDate.c_str(), "%Y-%m-%d", &tmCheckout);

    time_t timeReturn = mktime(&tmReturn);
    time_t timeCheckout = mktime(&tmCheckout);

    int difference = static_cast<int>(difftime(timeReturn, timeCheckout) / (60 * 60 * 24));

    return difference;
}

int main() {
    const int numberOfMembers = 10;

    // Create an array of Member objects
    Member members[numberOfMembers];

    for (int i = 0; i < numberOfMembers; ++i) {
        members[i].name = "Member" + to_string(i + 1);

        int numberOfBooks = 10 + rand() % 21;
        cout << "Member: " << members[i].name << endl;

        for (int j = 0; j < numberOfBooks; ++j) {
            Book book;
            book.name = "Book" + to_string(j + 1);
            book.checkoutDate = generateRandomDate();
            book.returnDate = generateRandomDate();

            cout << "  Book: " << book.name << ", Checkout Date: " << book.checkoutDate
                 << ", Return Date: " << book.returnDate << endl;

            members[i].books.push_back(book);
        }

        cout << endl;
    }

    int totalDays = 0;
    int totalBooks = 0;

    for (int i = 0; i < numberOfMembers; ++i) {
        for (const auto& book : members[i].books) {
            int days = calculateDaysDifference(book.returnDate, book.checkoutDate);
            totalDays += days;
            totalBooks++;
        }
    }

    double averageDays = static_cast<double>(totalDays) / totalBooks;

    cout << "Average number of days each member keeps the book: " << averageDays << endl;

    return 0;
}
