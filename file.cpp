#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ios>
#include <limits>
#include <time.h>

using namespace std;

class Node
{
public:
    Node *Next;
    string Author, Book;
    int Price, Pages;
    int ISBN;
    bool Available;

    Node(string Book, string Author, int Price, int Pages, int ISBN)
    {
        this->Book = Book;
        this->Author = Author;
        this->Price = Price;
        this->Pages = Pages;
        this->ISBN = ISBN;
        Available = true;
        Next = NULL;
    }
};

class BSTNode
{
public:
    BSTNode *Right;
    BSTNode *Left;
    string Author, Book_Name;
    int ISBN;
    int Price;
    int Pages;

    BSTNode(string Author, string Book, int Price, int Pages, int ISBN)
    {
        this->Book_Name = Book;
        this->Author = Author;
        this->Price = Price;
        this->Pages = Pages;
        this->ISBN = ISBN;
        Right = NULL;
        Left = NULL;
    }
};

class QueueNode
{
public:
    QueueNode *Next;
    string Book, Author;

    QueueNode(string Book, string Author)
    {
        this->Book = Book;
        this->Author = Author;
        Next = NULL;
    }
};

class BST
{

public:
    // Binary Search Tree sorts the data acc. to Prices
    void AddNode(string Author, string Book, int Price, int Pages, int ISBN, BSTNode *&Root)
    {

        BSTNode *n = new BSTNode(Author, Book, Price, Pages, ISBN);
        if (Root == NULL)
        {
            Root = n;
            cout << "Book added" << endl;
            return;
        }

        if (Price > Root->Price)
        {
            AddNode(Author, Book, Price, Pages, ISBN, Root->Right);
        }

        if (Price < Root->Price)
        {
            AddNode(Author, Book, Price, Pages, ISBN, Root->Left);
        }
    }

    // InOrder Traversal of the Binary Search Tree
    void DisplayTree(BSTNode *Root)
    {

        if (Root == NULL)
        {
            return;
        }

        DisplayTree(Root->Left);
        cout << "Book: " << Root->Book_Name << "\nAuthor: " << Root->Author << "\nPrice: " << Root->Price << "\nPages: " << Root->Pages << "\nISBN: " << Root->ISBN << endl
             << endl;
        DisplayTree(Root->Right);
    }
};

class Library
{

public:
    bool ValidateISBN(int ISBN, Node *Head)
    {
        int Sum = 0;
        Node *Temp = Head;

        while (ISBN != 0)
        {
            Sum += ISBN % 10;
            ISBN = ISBN / 10;
        }

        while (Temp != NULL)
        {
            if (Temp->ISBN == ISBN)
            {
                return false;
            }
            Temp = Temp->Next;
        }

        if (Sum % 10 == 0)
        {
            return true;
        }

        return false;
    }

    int GenerateISBN(Node *Head)
    {

        int ISBN;
        srand(time(0));

        while (true)
        {
            ISBN = (rand() % 9999999999) + 1111111111;

            if (ValidateISBN(ISBN, Head))
            {
                break;
            }
        }

        return ISBN;
    }

    int GetISBN(string Book, string Author, Node *Head)
    {
        Node *Temp = Head;

        while (Temp != NULL)
        {
            if ((strcmp(Temp->Book.c_str(), Book.c_str()) == 0) && (strcmp(Temp->Author.c_str(), Author.c_str()) == 0))
            {
                return Temp->ISBN;
            }
            Temp = Temp->Next;
        }

        return 0;
    }

    // Sorted Via Book Names
    void Add(string Book, string Author, int Price, int Pages, Node *&Head)
    {
        int ISBN = GenerateISBN(Head);

        Node *n = new Node(Book, Author, Price, Pages, ISBN);

        if (Head == NULL)
        {
            Head = n;
            cout << "Book Added" << endl;
            return;
        }

        if (strcmp(Head->Book.c_str(), n->Book.c_str()) > 0)
        {
            n->Next = Head;
            Head = n;
            cout << "Book Added" << endl;
            return;
        }

        Node *Temp = Head;
        Node *Prev = Head;

        while (Temp->Next != NULL)
        {
            if ((strcmp(Temp->Book.c_str(), n->Book.c_str()) > 0) && (strcmp(n->Book.c_str(), Temp->Book.c_str()) < 0))
            {
                Prev->Next = n;
                n->Next = Temp;
                cout << "Book Added" << endl;
                return;
            }
            Prev = Temp;
            Temp = Temp->Next;
        }
        Temp->Next = n;
        cout << "Book Added" << endl;
        return;
    }

    void Display(Node *Head)
    {
        system("CLS");
        Node *Temp = Head;

        while (Temp != NULL)
        {
            cout << "Book: " << Temp->Book << "\nAuthor: " << Temp->Author << "\nPrice: " << Temp->Price << "\nPages: " << Temp->Pages << "\nISBN: " << Temp->ISBN << endl
                 << endl;

            Temp = Temp->Next;
        }
    }

    void DisplayAuthor(string Author, Node *Head)
    {
        system("CLS");
        Node *Temp = Head;

        while (Temp != NULL)
        {

            if (strcmp(Temp->Author.c_str(), Author.c_str()) == 0)
            {
                cout << "Book: " << Temp->Book << "\nAuthor: " << Temp->Author << "\nPrice: " << Temp->Price << "\nPages: " << Temp->Pages << "\nISBN: " << Temp->ISBN << endl
                     << endl;
            }

            Temp = Temp->Next;
        }
    }

    void DisplayBook(string Book, Node *Head)
    {
        system("CLS");
        Node *Temp = Head;

        while (Temp != NULL)
        {

            if (strcmp(Temp->Book.c_str(), Book.c_str()) == 0)
            {
                cout << "Book: " << Temp->Book << "\nAuthor: " << Temp->Author << "\nPrice: " << Temp->Price << "\nPages: " << Temp->Pages << "\nISBN: " << Temp->ISBN << endl
                     << endl;
            }

            Temp = Temp->Next;
        }
    }

    void DeleteABook(string Book, string Author, Node *&Head)
    {

        Node *Temp = Head;
        Node *Prev = Head;

        if (Head == NULL)
        {
            cout << endl
                 << "Nothing to delete" << endl;
            return;
        }

        while (Temp->Next != NULL)
        {

            if ((!strcmp(Temp->Book.c_str(), Book.c_str())) && (!strcmp(Temp->Author.c_str(), Author.c_str())))
            {
                Node *ToDelete = Temp;
                if (Temp == Head)
                {
                    Head = Head->Next;
                    delete ToDelete;
                    return;
                }
                Prev->Next = Temp->Next;
                delete ToDelete;
                return;
            }

            Prev = Temp;
            Temp = Temp->Next;
        }

        if ((!strcmp(Temp->Book.c_str(), Book.c_str())) && (!strcmp(Temp->Author.c_str(), Author.c_str())))
        {
            Node *ToDelete = Temp;
            Prev->Next = Temp->Next;
            delete ToDelete;
            return;
        }

        cout << endl
             << "Nothing to delete" << endl;
    }
};

class Queue
{
public:
    QueueNode *Peak(QueueNode *Head)
    {
        return Head;
    }

    void enQueue(QueueNode *&Head, string Book, string Author)
    {
        QueueNode *n = new QueueNode(Book, Author);
        QueueNode *Temp = Head;
        if (Head == NULL)
        {
            Head = n;
            cout << "You have been added to our Queue" << endl;
            return;
        }

        while (Temp->Next != NULL)
            Temp = Temp->Next;

        Temp->Next = n;
        cout << "You have been added to our Queue" << endl;
        return;
    }

    void deQueue(QueueNode *&QHead, string Book, string Author, Node *Head)
    {
        QueueNode *ToDelete;
        Node *Temp = Head;

        if (QHead == NULL)
        {
            cout << "Nothing in Queue" << endl;
            return;
        }

        if (Head == NULL)
        {
            cout << "'" << Book << "' is not available yet" << endl;
            return;
        }

        while (Temp != NULL)
        {
            if ((Temp->Book == Peak(QHead)->Book) && (Temp->Author == Peak(QHead)->Author) && (Temp->Available))
            {
                ToDelete = Peak(QHead)->Next;
                QHead = Peak(QHead)->Next;
                Temp->Available = false;
                delete ToDelete;
                cout << "'" << Book << "' has been issued!" << endl;
                return;
            }

            if ((Temp->Book == Peak(QHead)->Book) && (Temp->Author == Peak(QHead)->Author) && (!Temp->Available))
            {
                cout << "'" << Book << "' is already borrowed by someone" << endl;
                return;
            }

            Temp = Temp->Next;
        }
        cout << "'" << Book << "' is not available yet" << endl;
    }
};

class Menu
{
protected:
    string UserName;
    string Password;
    string OfficialPass = "DSU";

private:
    Library Obj;
    BST Obj_BST;
    QueueNode *QHead = NULL;
    Queue Q;
    string Book, Author;
    int Price, Pages, Choice;
    Node *Head = NULL;
    BSTNode *Root = NULL;
    int ISBN;
    int C;

public:
    void Display()
    {
        while (true)
        {
            system("CLS");
            cout << endl
                 << endl
                 << "\t\t\t\t\t Welcome to PK-Library" << endl;
            cout << "1. Admin Portal" << endl;
            cout << "2. Member Portal" << endl;
            cout << "0. [EXIT]" << endl;
            cout << "Enter Choice: ";
            cin >> C;

            switch (C)
            {
            case 1:
                system("CLS");
                while (true)
                {
                    cout << "\t\t\t\t Login" << endl;
                    if (Verification())
                        break;

                    cout << "Wrong Credentials, try again" << endl;
                }
                Admin();
                break;
            case 2:
                Member();
                break;
            default:
                exit(0);
            }
        }
    }

    bool Verification()
    {
        cout << endl
             << endl
             << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Username: ";
        cin >> UserName;
        cout << "Enter Password: ";
        cin >> Password;

        if ((UserName == "DSU" && Password == OfficialPass))
            return true;

        return false;
    }

    void Admin()
    {
        system("CLS");
        cout << endl
             << "\t\t\t\t\t\t****************" << endl;
        cout << "\t\t\t\t\t\t   Welcome " << UserName << " to the Library Portal";
        cout << endl
             << "\t\t\t\t\t\t****************" << endl
             << endl;
        while (true)
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t PK-Library" << endl;
            cout << "1. Add a Book" << endl;
            cout << "2. Display List" << endl;
            cout << "3. Display Books from a Specific Author" << endl;
            cout << "4. Display Specific Books" << endl;
            cout << "5. Display via Prices (History & Current)" << endl;
            cout << "6. Delete a Book" << endl;
            cout << "7. Lend a Book" << endl;
            cout << "0. [EXIT]" << endl;
            cout << "Enter Choice: ";
            cin >> Choice;

            switch (Choice)
            {
            case 1:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl
                     << endl;
                cout << "Enter Book Name: ";
                getline(cin, Book);

                cout << "Enter Author Name: ";
                getline(cin, Author);

                cout << "Enter Pages: ";
                cin >> Pages;

                cout << "Enter Price: ";
                cin >> Price;

                Obj.Add(Book, Author, Price, Pages, Head);               // LL
                ISBN = Obj.GetISBN(Book, Author, Head);                  // Getting ISBN from LL
                Obj_BST.AddNode(Author, Book, Price, Pages, ISBN, Root); // Addition to BST
                system("CLS");
                break;
            case 2:
                cout << endl
                     << endl;
                Obj.Display(Head);
                break;
            case 3:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n"
                     << endl;
                cout << "Enter Author Name: ";
                getline(cin, Author);
                cout << endl
                     << endl;
                Obj.DisplayAuthor(Author, Head);
                break;
            case 4:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n"
                     << endl;
                cout << "Enter Book Name: ";
                getline(cin, Book);
                cout << endl
                     << endl;
                Obj.DisplayBook(Book, Head);
                break;
            case 5:
                cout << "Books (Current and History): " << endl;
                Obj_BST.DisplayTree(Root);
                cout << endl
                     << endl
                     << "Do you want to check Books' availability? (Y/N): ";
                char ChoiceChar;
                cin >> ChoiceChar;
                if (ChoiceChar == 'Y' || ChoiceChar == 'y')
                {
                    system("CLS");
                    Obj.Display(Head);
                }
                break;
            case 6:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n"
                     << endl;
                cout << "Enter Book Name: ";
                getline(cin, Book);
                cout << "Enter Author Name: ";
                getline(cin, Author);
                Obj.DeleteABook(Book, Author, Head);
                break;
            case 7:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n"
                     << endl;
                cout << "Enter Book Name: ";
                getline(cin, Book);
                cout << "Enter Author Name: ";
                getline(cin, Author);
                Q.deQueue(QHead, Book, Author, Head);
                break;
            default:
                Display();
            }
        }
    }

    void Member()
    {
        system("CLS");
        while (true)
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t PK-Library" << endl;
            cout << "1. Issue a Book" << endl;
            cout << "2. Check Status of Queue" << endl;
            cout << "0. [EXIT]" << endl;
            cout << "Enter Choice: ";
            cin >> Choice;

            switch (Choice)
            {
            case 1:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n"
                     << endl;
                cout << "Enter Book Name: ";
                getline(cin, Book);
                cout << "Enter Author Name: ";
                getline(cin, Author);
                Q.enQueue(QHead, Book, Author);
                cout << "You will be served shortly" << endl;
                break;
            case 2:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n"
                     << endl;
                cout << "Enter Book Name: ";
                getline(cin, Book);
                cout << "Enter Author Name: ";
                getline(cin, Author);
                Q.deQueue(QHead, Book, Author, Head);
                break;
            default:
                Display();
            }
        }
    }
};

int main()
{
    // Password: DSU
    // Usernames: DSU
    Menu Obj;
    Obj.Display();
}