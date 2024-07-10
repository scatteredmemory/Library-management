#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <conio.h>  // For getch()

using namespace std;

class Person {
public:
    int id;
    string name;
    string gender;
    string password;

    Person(int id, string name, string gender, string password)
        : id(id), name(name), gender(gender), password(password) {}

    virtual ~Person() {}

    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Gender: " << gender << endl;
    }
};

class Librarian : public Person {
public:
    string position;

    Librarian(int id, string name, string gender, string position, string password)
        : Person(id, name, gender, password), position(position) {}

    void display() const {
        Person::display();
        cout << "Position: " << position << endl;
    }
};

class Student : public Person {
public:
    int age;
    string category;
    string college;
    string entry_date;
    string graduation_date;

    Student(int id, string name, string gender, int age, string category, string college,
            string entry_date, string graduation_date, string password)
        : Person(id, name, gender, password), age(age), category(category),
          college(college), entry_date(entry_date), graduation_date(graduation_date) {}

    void display() const {
        Person::display();
        cout << "Age: " << age << ", Category: " << category << ", College: " << college
             << ", Entry Date: " << entry_date << ", Graduation Date: " << graduation_date << endl;
    }
};

class Teacher : public Person {
public:
    int age;
    string college;
    string entry_date;

    Teacher(int id, string name, string gender, int age, string college, string entry_date, string password)
        : Person(id, name, gender, password), age(age), college(college), entry_date(entry_date) {}

    void display() const {
        Person::display();
        cout << "Age: " << age << ", College: " << college << ", Entry Date: " << entry_date << endl;
    }
};

class Book {
public:
    int id;
    string title;
    string author;
    string subject;
    string publisher;
    string publish_date;
    string entry_date;
    int pages;
    double price;

    Book(int id, string title, string author, string subject, string publisher, string publish_date,
         string entry_date, int pages, double price)
        : id(id), title(title), author(author), subject(subject), publisher(publisher),
          publish_date(publish_date), entry_date(entry_date), pages(pages), price(price) {}

    void display() const {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author << ", Subject: " << subject
             << ", Publisher: " << publisher << ", Publish Date: " << publish_date << ", Entry Date: " << entry_date
             << ", Pages: " << pages << ", Price: " << price << endl;
    }
};

class ReaderCategory {
public:
    int id;
    string name;
    int borrow_duration_limit;
    int borrow_count_limit;
    string other_notes;

    ReaderCategory(int id, string name, int borrow_duration_limit, int borrow_count_limit, string other_notes)
        : id(id), name(name), borrow_duration_limit(borrow_duration_limit), borrow_count_limit(borrow_count_limit), other_notes(other_notes) {}

    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Borrow Duration Limit: " << borrow_duration_limit
             << ", Borrow Count Limit: " << borrow_count_limit << ", Other Notes: " << other_notes << endl;
    }
};

class BorrowRecord {
public:
    int id;
    int book_id;
    int reader_id;
    string borrow_date;
    string due_date;
    int librarian_id;
    bool is_returned;

    BorrowRecord(int id, int book_id, int reader_id, string borrow_date, string due_date, int librarian_id, bool is_returned = false)
        : id(id), book_id(book_id), reader_id(reader_id), borrow_date(borrow_date), due_date(due_date), librarian_id(librarian_id), is_returned(is_returned) {}

    void display() const {
        cout << "Borrow ID: " << id << ", Book ID: " << book_id << ", Reader ID: " << reader_id
             << ", Borrow Date: " << borrow_date << ", Due Date: " << due_date << ", Librarian ID: " << librarian_id
             << ", Returned: " << (is_returned ? "Yes" : "No") << endl;
    }
};

class LibrarySystem {
public:
    Librarian* currentLibrarian = nullptr;

private:
    vector<Book> books;
    vector<Librarian> librarians;
    vector<Student> students;
    vector<Teacher> teachers;
    vector<ReaderCategory> readerCategories;
    vector<BorrowRecord> borrowRecords;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void deleteBook(int id) {
        books.erase(remove_if(books.begin(), books.end(), [id](Book& book) { return book.id == id; }), books.end());
    }

    void editBook(int id, const Book& updatedBook) {
        for (auto& book : books) {
            if (book.id == id) {
                book = updatedBook;
                break;
            }
        }
    }

    Book* findBook(int id) {
        for (auto& book : books) {
            if (book.id == id) {
                return &book;
            }
        }
        return nullptr;
    }

    void saveBooksToFile(const string& filename) {
        ofstream outFile(filename.c_str());
        for (const auto& book : books) {
            outFile << book.id << ',' << book.title << ',' << book.author << ',' << book.subject << ','
                    << book.publisher << ',' << book.publish_date << ',' << book.entry_date << ','
                    << book.pages << ',' << book.price << '\n';
        }
        outFile.close();
    }

    void loadBooksFromFile(const string& filename) {
        ifstream inFile(filename.c_str());
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string item;
            vector<string> elements;
            while (getline(ss, item, ',')) {
                elements.push_back(item);
            }
            if (elements.size() == 9) {
                Book book(stoi(elements[0]), elements[1], elements[2], elements[3], elements[4], elements[5],
                          elements[6], stoi(elements[7]), stod(elements[8]));
                books.push_back(book);
            }
        }
        inFile.close();
    }

    void addLibrarian(const Librarian& librarian) {
        librarians.push_back(librarian);
    }

    void deleteLibrarian(int id) {
        librarians.erase(remove_if(librarians.begin(), librarians.end(), [id](Librarian& librarian) { return librarian.id == id; }), librarians.end());
    }

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void deleteStudent(int id) {
        students.erase(remove_if(students.begin(), students.end(), [id](Student& student) { return student.id == id; }), students.end());
    }

    void addTeacher(const Teacher& teacher) {
        teachers.push_back(teacher);
    }

    void deleteTeacher(int id) {
        teachers.erase(remove_if(teachers.begin(), teachers.end(), [id](Teacher& teacher) { return teacher.id == id; }), teachers.end());
    }

    void addReaderCategory(const ReaderCategory& category) {
        readerCategories.push_back(category);
    }

    void deleteReaderCategory(int id) {
        readerCategories.erase(remove_if(readerCategories.begin(), readerCategories.end(), [id](ReaderCategory& category) { return category.id == id; }), readerCategories.end());
    }

    void editReaderCategory(int id, const ReaderCategory& updatedCategory) {
        for (auto& category : readerCategories) {
            if (category.id == id) {
                category = updatedCategory;
                break;
            }
        }
    }

    ReaderCategory* findReaderCategory(int id) {
        for (auto& category : readerCategories) {
            if (category.id == id) {
                return &category;
            }
        }
        return nullptr;
    }

    void addBorrowRecord(const BorrowRecord& record) {
        borrowRecords.push_back(record);
    }

    void saveLibrariansToFile(const string& filename) {
        ofstream outFile(filename.c_str());
        for (const auto& librarian : librarians) {
            outFile << librarian.id << ',' << librarian.name << ',' << librarian.gender << ',' << librarian.position << ',' << librarian.password << '\n';
        }
        outFile.close();
    }

    void loadLibrariansFromFile(const string& filename) {
        ifstream inFile(filename.c_str());
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string item;
            vector<string> elements;
            while (getline(ss, item, ',')) {
                elements.push_back(item);
            }
            if (elements.size() == 5) {
                Librarian librarian(stoi(elements[0]), elements[1], elements[2], elements[3], elements[4]);
                librarians.push_back(librarian);
            }
        }
        inFile.close();
    }

    void saveStudentsToFile(const string& filename) {
        ofstream outFile(filename.c_str());
        for (const auto& student : students) {
            outFile << student.id << ',' << student.name << ',' << student.gender << ',' << student.age << ','
                    << student.category << ',' << student.college << ',' << student.entry_date << ',' << student.graduation_date << ',' << student.password << '\n';
        }
        outFile.close();
    }

    void loadStudentsFromFile(const string& filename) {
        ifstream inFile(filename.c_str());
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string item;
            vector<string> elements;
            while (getline(ss, item, ',')) {
                elements.push_back(item);
            }
            if (elements.size() == 9) {
                Student student(stoi(elements[0]), elements[1], elements[2], stoi(elements[3]), elements[4], elements[5], elements[6], elements[7], elements[8]);
                students.push_back(student);
            }
        }
        inFile.close();
    }

    void saveTeachersToFile(const string& filename) {
        ofstream outFile(filename.c_str());
        for (const auto& teacher : teachers) {
            outFile << teacher.id << ',' << teacher.name << ',' << teacher.gender << ',' << teacher.age << ','
                    << teacher.college << ',' << teacher.entry_date << ',' << teacher.password << '\n';
        }
        outFile.close();
    }

    void loadTeachersFromFile(const string& filename) {
        ifstream inFile(filename.c_str());
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string item;
            vector<string> elements;
            while (getline(ss, item, ',')) {
                elements.push_back(item);
            }
            if (elements.size() == 7) {
                Teacher teacher(stoi(elements[0]), elements[1], elements[2], stoi(elements[3]), elements[4], elements[5], elements[6]);
                teachers.push_back(teacher);
            }
        }
        inFile.close();
    }

    void saveReaderCategoriesToFile(const string& filename) {
        ofstream outFile(filename.c_str());
        for (const auto& category : readerCategories) {
            outFile << category.id << ',' << category.name << ',' << category.borrow_duration_limit << ','
                    << category.borrow_count_limit << ',' << category.other_notes << '\n';
        }
        outFile.close();
    }

    void loadReaderCategoriesFromFile(const string& filename) {
        ifstream inFile(filename.c_str());
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string item;
            vector<string> elements;
            while (getline(ss, item, ',')) {
                elements.push_back(item);
            }
            if (elements.size() == 5) {
                ReaderCategory category(stoi(elements[0]), elements[1], stoi(elements[2]), stoi(elements[3]), elements[4]);
                readerCategories.push_back(category);
            }
        }
        inFile.close();
    }

    void saveBorrowRecordsToFile(const string& filename) {
        ofstream outFile(filename.c_str());
        for (const auto& record : borrowRecords) {
            outFile << record.id << ',' << record.book_id << ',' << record.reader_id << ',' << record.borrow_date << ','
                    << record.due_date << ',' << record.librarian_id << ',' << record.is_returned << '\n';
        }
        outFile.close();
    }

    void loadBorrowRecordsFromFile(const string& filename) {
        ifstream inFile(filename.c_str());
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string item;
            vector<string> elements;
            while (getline(ss, item, ',')) {
                elements.push_back(item);
            }
            if (elements.size() == 7) {
                BorrowRecord record(stoi(elements[0]), stoi(elements[1]), stoi(elements[2]), elements[3], elements[4], stoi(elements[5]), stoi(elements[6]));
                borrowRecords.push_back(record);
            }
        }
        inFile.close();
    }

    void loadAllData() {
        loadBooksFromFile("books.txt");
        loadLibrariansFromFile("librarians.txt");
        loadStudentsFromFile("students.txt");
        loadTeachersFromFile("teachers.txt");
        loadReaderCategoriesFromFile("reader_categories.txt");
        loadBorrowRecordsFromFile("borrow_records.txt");
    }

    void saveAllData() {
        saveBooksToFile("books.txt");
        saveLibrariansToFile("librarians.txt");
        saveStudentsToFile("students.txt");
        saveTeachersToFile("teachers.txt");
        saveReaderCategoriesToFile("reader_categories.txt");
        saveBorrowRecordsToFile("borrow_records.txt");
    }

    void librarianMenu() {
        int choice;
        do {
            cout << "Librarian Menu:" << endl;
            cout << "1. Manage Books" << endl;
            cout << "2. Manage Students" << endl;
            cout << "3. Manage Teachers" << endl;
            cout << "4. Manage Reader Categories" << endl;
            cout << "5. Manage Borrow Records" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int subChoice;
                    do {
                        cout << "Manage Books:" << endl;
                        cout << "1. Add Book" << endl;
                        cout << "2. Delete Book" << endl;
                        cout << "3. Edit Book" << endl;
                        cout << "4. Find Book" << endl;
                        cout << "5. Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> subChoice;

                        switch (subChoice) {
                            case 1: {
                                int id, pages;
                                string title, author, subject, publisher, publish_date, entry_date;
                                double price;
                                cout << "Enter Book ID: ";
                                cin >> id;

                                Book* existingBook = findBook(id);
                                if (existingBook) {
                                    cout << "This ID is already taken by the following book:" << endl;
                                    existingBook->display();
                                    cout << "Do you want to overwrite it? (y/n): ";
                                    char overwrite;
                                    cin >> overwrite;
                                    if (overwrite == 'n') {
                                        break;
                                    }
                                }

                                cout << "Enter Book Title: ";
                                cin.ignore();
                                getline(cin, title);
                                cout << "Enter Author: ";
                                getline(cin, author);
                                cout << "Enter Subject: ";
                                getline(cin, subject);
                                cout << "Enter Publisher: ";
                                getline(cin, publisher);
                                cout << "Enter Publish Date: ";
                                getline(cin, publish_date);
                                cout << "Enter Entry Date: ";
                                getline(cin, entry_date);
                                cout << "Enter Pages: ";
                                cin >> pages;
                                cout << "Enter Price: ";
                                cin >> price;
                                addBook(Book(id, title, author, subject, publisher, publish_date, entry_date, pages, price));
                                cout << "Book added successfully!" << endl;
                                break;
                            }
                            case 2: {
                                int id;
                                cout << "Enter Book ID to delete: ";
                                cin >> id;
                                Book* book = findBook(id);
                                if (book) {
                                    deleteBook(id);
                                    cout << "Book deleted successfully!" << endl;
                                } else {
                                    cout << "Book not found. Deletion aborted." << endl;
                                }
                                break;
                            }
                            case 3: {
                                int id, pages;
                                string title, author, subject, publisher, publish_date, entry_date;
                                double price;
                                cout << "Enter Book ID to edit: ";
                                cin >> id;

                                Book* book = findBook(id);
                                if (!book) {
                                    cout << "Book not found. Edit aborted." << endl;
                                    break;
                                }

                                cout << "Enter new Book Title: ";
                                cin.ignore();
                                getline(cin, title);
                                cout << "Enter new Author: ";
                                getline(cin, author);
                                cout << "Enter new Subject: ";
                                getline(cin, subject);
                                cout << "Enter new Publisher: ";
                                getline(cin, publisher);
                                cout << "Enter new Publish Date: ";
                                getline(cin, publish_date);
                                cout << "Enter new Entry Date: ";
                                getline(cin, entry_date);
                                cout << "Enter new Pages: ";
                                cin >> pages;
                                cout << "Enter new Price: ";
                                cin >> price;
                                editBook(id, Book(id, title, author, subject, publisher, publish_date, entry_date, pages, price));
                                cout << "Book edited successfully!" << endl;
                                break;
                            }
                            case 4: {
                                int id;
                                cout << "Enter Book ID to find: ";
                                cin >> id;
                                Book* book = findBook(id);
                                if (book) {
                                    book->display();
                                } else {
                                    cout << "Book not found." << endl;
                                }
                                break;
                            }
                            case 5:
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }
                    } while (subChoice != 5);
                    break;
                }
                case 2: {
                    int subChoice;
                    do {
                        cout << "Manage Students:" << endl;
                        cout << "1. Add Student" << endl;
                        cout << "2. Delete Student" << endl;
                        cout << "3. Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> subChoice;

                        switch (subChoice) {
                            case 1: {
                                int id, age;
                                string name, gender, category, college, entry_date, graduation_date, password;
                                cout << "Enter Student ID: ";
                                cin >> id;
                                cout << "Enter Name: ";
                                cin.ignore();
                                getline(cin, name);
                                cout << "Enter Gender: ";
                                getline(cin, gender);
                                cout << "Enter Age: ";
                                cin >> age;
                                cout << "Enter Category: ";
                                cin.ignore();
                                getline(cin, category);
                                cout << "Enter College: ";
                                getline(cin, college);
                                cout << "Enter Entry Date: ";
                                getline(cin, entry_date);
                                cout << "Enter Graduation Date: ";
                                getline(cin, graduation_date);
                                cout << "Enter Password: ";
                                getline(cin, password);
                                addStudent(Student(id, name, gender, age, category, college, entry_date, graduation_date, password));
                                cout << "Student added successfully!" << endl;
                                break;
                            }
                            case 2: {
                                int id;
                                cout << "Enter Student ID to delete: ";
                                cin >> id;
                                Student* student = findStudent(id);
                                if (student) {
                                    deleteStudent(id);
                                    cout << "Student deleted successfully!" << endl;
                                } else {
                                    cout << "Student not found. Deletion aborted." << endl;
                                }
                                break;
                            }
                            case 3:
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }
                    } while (subChoice != 3);
                    break;
                }
                case 3: {
                    int subChoice;
                    do {
                        cout << "Manage Teachers:" << endl;
                        cout << "1. Add Teacher" << endl;
                        cout << "2. Delete Teacher" << endl;
                        cout << "3. Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> subChoice;

                        switch (subChoice) {
                            case 1: {
                                int id, age;
                                string name, gender, college, entry_date, password;
                                cout << "Enter Teacher ID: ";
                                cin >> id;
                                cout << "Enter Name: ";
                                cin.ignore();
                                getline(cin, name);
                                cout << "Enter Gender: ";
                                getline(cin, gender);
                                cout << "Enter Age: ";
                                cin >> age;
                                cout << "Enter College: ";
                                cin.ignore();
                                getline(cin, college);
                                cout << "Enter Entry Date: ";
                                getline(cin, entry_date);
                                cout << "Enter Password: ";
                                getline(cin, password);
                                addTeacher(Teacher(id, name, gender, age, college, entry_date, password));
                                cout << "Teacher added successfully!" << endl;
                                break;
                            }
                            case 2: {
                                int id;
                                cout << "Enter Teacher ID to delete: ";
                                cin >> id;
                                Teacher* teacher = findTeacher(id);
                                if (teacher) {
                                    deleteTeacher(id);
                                    cout << "Teacher deleted successfully!" << endl;
                                } else {
                                    cout << "Teacher not found. Deletion aborted." << endl;
                                }
                                break;
                            }
                            case 3:
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }
                    } while (subChoice != 3);
                    break;
                }
                case 4: {
                    int subChoice;
                    do {
                        cout << "Manage Reader Categories:" << endl;
                        cout << "1. Add Reader Category" << endl;
                        cout << "2. Edit Reader Category" << endl;
                        cout << "3. Delete Reader Category" << endl;
                        cout << "4. Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> subChoice;

                        switch (subChoice) {
                            case 1: {
                                int id, borrow_duration_limit, borrow_count_limit;
                                string name, other_notes;
                                cout << "Enter Reader Category ID: ";
                                cin >> id;
                                cout << "Enter Category Name: ";
                                cin.ignore();
                                getline(cin, name);
                                cout << "Enter Borrow Duration Limit: ";
                                cin >> borrow_duration_limit;
                                cout << "Enter Borrow Count Limit: ";
                                cin >> borrow_count_limit;
                                cout << "Enter Other Notes: ";
                                cin.ignore();
                                getline(cin, other_notes);
                                addReaderCategory(ReaderCategory(id, name, borrow_duration_limit, borrow_count_limit, other_notes));
                                cout << "Reader category added successfully!" << endl;
                                break;
                            }
                            case 2: {
                                int id, borrow_duration_limit, borrow_count_limit;
                                string name, other_notes;
                                cout << "Enter Reader Category ID to edit: ";
                                cin >> id;

                                ReaderCategory* category = findReaderCategory(id);
                                if (!category) {
                                    cout << "Reader category not found. Edit aborted." << endl;
                                    break;
                                }

                                cout << "Current details:" << endl;
                                category->display();

                                cout << "Enter new Category Name: ";
                                cin.ignore();
                                getline(cin, name);
                                cout << "Enter new Borrow Duration Limit: ";
                                cin >> borrow_duration_limit;
                                cout << "Enter new Borrow Count Limit: ";
                                cin >> borrow_count_limit;
                                cout << "Enter new Other Notes: ";
                                cin.ignore();
                                getline(cin, other_notes);
                                editReaderCategory(id, ReaderCategory(id, name, borrow_duration_limit, borrow_count_limit, other_notes));
                                cout << "Reader category edited successfully!" << endl;
                                break;
                            }
                            case 3: {
                                int id;
                                cout << "Enter Reader Category ID to delete: ";
                                cin >> id;
                                ReaderCategory* category = findReaderCategory(id);
                                if (category) {
                                    deleteReaderCategory(id);
                                    cout << "Reader category deleted successfully!" << endl;
                                } else {
                                    cout << "Reader category not found. Deletion aborted." << endl;
                                }
                                break;
                            }
                            case 4:
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }
                    } while (subChoice != 4);
                    break;
                }
                case 5: {
                    int subChoice;
                    do {
                        cout << "Manage Borrow Records:" << endl;
                        cout << "1. Borrow Book" << endl;
                        cout << "2. Return Book" << endl;
                        cout << "3. View Borrow Records" << endl;
                        cout << "4. Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> subChoice;

                        switch (subChoice) {
                            case 1: {
                                int book_id, reader_id;
                                string borrow_date, due_date;
                                cout << "Enter Book ID to borrow: ";
                                cin >> book_id;
                                Book* book = findBook(book_id);
                                if (!book) {
                                    cout << "Book not found. Borrowing aborted." << endl;
                                    break;
                                }

                                bool isBookBorrowed = false;
                                for (const auto& record : borrowRecords) {
                                    if (record.book_id == book_id && !record.is_returned) {
                                        isBookBorrowed = true;
                                        break;
                                    }
                                }

                                if (isBookBorrowed) {
                                    cout << "Book is already borrowed and not returned yet. Borrowing aborted." << endl;
                                    break;
                                }

                                cout << "Enter Reader ID: ";
                                cin >> reader_id;
                                Student* student = findStudent(reader_id);
                                Teacher* teacher = findTeacher(reader_id);
                                if (!student && !teacher) {
                                    cout << "Reader not found. Borrowing aborted." << endl;
                                    break;
                                }

                                int currentBorrowCount = 0;
                                for (const auto& record : borrowRecords) {
                                    if (record.reader_id == reader_id && !record.is_returned) {
                                        currentBorrowCount++;
                                    }
                                }

                                int borrowLimit = 0;
                                if (student) {
                                    for (const auto& category : readerCategories) {
                                        if (category.name == "student") {
                                            borrowLimit = category.borrow_count_limit;
                                            break;
                                        }
                                    }
                                } else if (teacher) {
                                    for (const auto& category : readerCategories) {
                                        if (category.name == "teacher") {
                                            borrowLimit = category.borrow_count_limit;
                                            break;
                                        }
                                    }
                                }

                                if (currentBorrowCount >= borrowLimit) {
                                    cout << "Reader has reached the borrow limit. Borrowing aborted." << endl;
                                    break;
                                }

                                time_t now = time(0);
                                tm* ltm = localtime(&now);
                                stringstream ss;
                                ss << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday;
                                borrow_date = ss.str();

                                int borrow_duration = 30; // default duration
                                if (student) {
                                    for (const auto& category : readerCategories) {
                                        if (category.name == "student") {
                                            borrow_duration = category.borrow_duration_limit;
                                            break;
                                        }
                                    }
                                } else if (teacher) {
                                    for (const auto& category : readerCategories) {
                                        if (category.name == "teacher") {
                                            borrow_duration = category.borrow_duration_limit;
                                            break;
                                        }
                                    }
                                }

                                ltm->tm_mday += borrow_duration;
                                mktime(ltm);
                                ss.str("");
                                ss << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday;
                                due_date = ss.str();

                                int borrow_id = borrowRecords.size() + 1;
                                addBorrowRecord(BorrowRecord(borrow_id, book_id, reader_id, borrow_date, due_date, currentLibrarian->id));
                                cout << "Book borrowed successfully!" << endl;
                                break;
                            }
                            case 2: {
                                int borrow_id;
                                cout << "Enter Borrow ID to return: ";
                                cin >> borrow_id;
                                for (auto& record : borrowRecords) {
                                    if (record.id == borrow_id && !record.is_returned) {
                                        record.is_returned = true;
                                        cout << "Book returned successfully!" << endl;
                                        break;
                                    }
                                }
                                break;
                            }
                            case 3: {
                                int viewChoice;
                                cout << "View Borrow Records:" << endl;
                                cout << "1. View All Records" << endl;
                                cout << "2. View Unreturned Records" << endl;
                                cout << "Enter your choice: ";
                                cin >> viewChoice;

                                if (viewChoice == 1) {
                                    for (const auto& record : borrowRecords) {
                                        record.display();
                                    }
                                } else if (viewChoice == 2) {
                                    for (const auto& record : borrowRecords) {
                                        if (!record.is_returned) {
                                            record.display();
                                        }
                                    }
                                } else {
                                    cout << "Invalid choice." << endl;
                                }
                                break;
                            }
                            case 4:
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }
                    } while (subChoice != 4);
                    break;
                }
                case 6:
                    saveAllData();
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 6);
    }

    void rootMenu() {
        int choice;
        do {
            cout << "Root Menu:" << endl;
            cout << "1. Add Librarian" << endl;
            cout << "2. Delete Librarian" << endl;
            cout << "3. Display All Librarians" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int id;
                    string name, gender, position, password;
                    cout << "Enter Librarian ID: ";
                    cin >> id;

                    Librarian* existingLibrarian = findLibrarian(id);
                    if (existingLibrarian) {
                        cout << "This ID is already taken by the following librarian:" << endl;
                        existingLibrarian->display();
                        cout << "Do you want to overwrite it? (y/n): ";
                        char overwrite;
                        cin >> overwrite;
                        if (overwrite == 'n') {
                            break;
                        }
                    }

                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Gender: ";
                    getline(cin, gender);
                    cout << "Enter Position: ";
                    getline(cin, position);
                    cout << "Enter Password: ";
                    getline(cin, password);
                    addLibrarian(Librarian(id, name, gender, position, password));
                    cout << "Librarian added successfully!" << endl;
                    break;
                }
                case 2: {
                    int id;
                    cout << "Enter Librarian ID to delete: ";
                    cin >> id;
                    Librarian* librarian = findLibrarian(id);
                    if (librarian) {
                        deleteLibrarian(id);
                        cout << "Librarian deleted successfully!" << endl;
                    } else {
                        cout << "Librarian not found. Deletion aborted." << endl;
                    }
                    break;
                }
                case 3: {
                    for (const auto& librarian : librarians) {
                        librarian.display();
                    }
                    break;
                }
                case 4:
                    saveAllData();
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 4);
    }

    void readerMenu(int reader_id) {
        int choice;
        do {
            cout << "Reader Menu:" << endl;
            cout << "1. Find Book" << endl;
            cout << "2. View Borrow Records" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int id;
                    cout << "Enter Book ID to find: ";
                    cin >> id;
                    Book* book = findBook(id);
                    if (book) {
                        book->display();
                    } else {
                        cout << "Book not found." << endl;
                    }
                    break;
                }
                case 2: {
                    bool found = false;
                    for (const auto& record : borrowRecords) {
                        if (record.reader_id == reader_id) {
                            record.display();
                            found = true;
                        }
                    }
                    if (!found) {
                        cout << "No borrow records found." << endl;
                    }
                    break;
                }
                case 3:
                    saveAllData();
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 3);
    }

    Librarian* findLibrarian(int id) {
        for (auto& librarian : librarians) {
            if (librarian.id == id) {
                return &librarian;
            }
        }
        return nullptr;
    }

    Student* findStudent(int id) {
        for (auto& student : students) {
            if (student.id == id) {
                return &student;
            }
        }
        return nullptr;
    }

    Teacher* findTeacher(int id) {
        for (auto& teacher : teachers) {
            if (teacher.id == id) {
                return &teacher;
            }
        }
        return nullptr;
    }
};

string getHiddenInput() {
    string input;
    char ch;
    while ((ch = _getch()) != '\r') {  // '\r' is Enter key
        if (ch == '\b') {  // '\b' is Backspace key
            if (!input.empty()) {
                cout << "\b \b";
                input.pop_back();
            }
        } else {
            input.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return input;
}

int main() {
    LibrarySystem librarySystem;
    librarySystem.loadAllData(); // 加载所有数据

    int userType, userID;
    string password;

    cout << "Welcome to the Library Management System" << endl;
    cout << "1. Librarian" << endl;
    cout << "2. Reader" << endl;
    cout << "3. Root" << endl;
    cout << "Enter user type: ";
    cin >> userType;

    if (userType == 3) {
        cout << "Enter password: ";
        password = getHiddenInput();
        if (password != "123") {
            cout << "Invalid password. Exiting..." << endl;
            return 0;
        }
        librarySystem.rootMenu();
    } else {
        cout << "Enter your ID: ";
        cin >> userID;

        Librarian* librarian = librarySystem.findLibrarian(userID);
        Student* student = librarySystem.findStudent(userID);
        Teacher* teacher = librarySystem.findTeacher(userID);

        if (userType == 1 && !librarian) {
            cout << "ID not found for Librarian. Please try again." << endl;
            main();
            return 0;
        } else if (userType == 2 && !student && !teacher) {
            cout << "ID not found for Reader. Please try again." << endl;
            main();
            return 0;
        }

        cout << "Enter password: ";
        password = getHiddenInput();

        if (userType == 1 && librarian && password != librarian->password) {
            cout << "Invalid password. Exiting..." << endl;
            return 0;
        } else if (userType == 2) {
            if (student && password != student->password) {
                cout << "Invalid password. Exiting..." << endl;
                return 0;
            } else if (teacher && password != teacher->password) {
                cout << "Invalid password. Exiting..." << endl;
                return 0;
            }
        }

        if (userType == 1) {
            librarySystem.currentLibrarian = librarian;
            librarySystem.librarianMenu();
        } else if (userType == 2) {
            librarySystem.readerMenu(userID);
        } else {
            cout << "Invalid user type. Exiting..." << endl;
        }
    }

    return 0;
}
