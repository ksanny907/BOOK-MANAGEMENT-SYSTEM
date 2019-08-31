#include<fstream>
#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

class Book
{
  private:
      int bookid;
      char title[20];
      float price;
  public:
    Book()
    {
        bookid=0;
        strcpy(title,"no title");
        price=0;
    }
        void getBookData()
        {
            cout<<"Enter bookid, title and price of the Book\n";
            cin>>bookid;
            cin.ignore();
            cin.getline(title,19);
            cin>>price;
        }
        void showBookData()
        {
            cout<<"\n"<<bookid<<" "<<title<<" "<<price;
        }
        int storeBook();
        void viewAllBooks();
        void searchBook(char *);
        void deleteBook(char*);
        void updateBook(char*);
};
  void Book::updateBook(char *t)
  {
      fstream file;
      file.open("file1.dat",ios::in|ios::out|ios::ate|ios::binary);
      file.seekg(0);
      file.read((char*)this,sizeof(*this));
      while(!file.eof()){
          if(!strcmp(t,title)){
            getBookData();
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this,sizeof(*this));
          }
            file.read((char*)this,sizeof(*this));
          }
            file.close();
}
  void Book:: deleteBook(char *t)
  {
      ifstream fin;
      ofstream fout;
      fin.open("file1.dat",ios::in|ios::binary);
      if(!fin)
          cout<<"\nFile not found";
      else{
           getch();
           fout.open("tempfile.dat",ios::out|ios::binary);
           fin.read((char*)this,sizeof(*this));
           while(!fin.eof()){
            if(strcmp(title,t))
                fout.write((char*)this,sizeof(*this));
                fin.read((char*)this,sizeof(*this));
           }
        fin.close();
        fout.close();
        //getch();
        remove("file1.dat");

        rename("tempfile.dat","file1.dat");
        //getch();
      }
}
  void Book::searchBook(char *t)
{

    int counter=0;
    ifstream fin;
    fin.open("file1.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\nFile not found";
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            if(!strcmp(t,title)){
                showBookData();
                counter++;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if(counter==0)
            cout<<"\nRecord not found ";
        fin.close();
    }
}
  void Book::viewAllBooks()
{
   ifstream fin;
    fin.open("file1.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\nFile not found";
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
                showBookData();
                fin.read((char*)this,sizeof(*this));
        }
        fin.close();
     }
}
  int Book::storeBook()
{
    if(bookid==0&&price==0)
    {
        cout<<"Book data not initialized ";
        return(0);
    }
    else{

        ofstream fout;
        fout.open("file1.dat",ios::app|ios::binary);
        fout.write((char*)this,sizeof(*this));
        fout.close();
        return(1);
    }
}
  int menu()
  {
      int choice;
      cout<<"\nBook Management";
      cout<<"\n1.  Insert book record";
      cout<<"\n2.  View all book records";
      cout<<"\n3.  Search book record";
      cout<<"\n4.  Delete book record";
      cout<<"\n5.  Update book record";
      cout<<"\n6.  Exit";
      cout<<"\n\nEnter your choice ";
      cin>>choice;
      return(choice);
  }
  int main()
{
    Book b1;
    char title[20];
    while(1){
        system("cls");
        switch(menu())
        {
            case 1:
                 b1.getBookData();
                 b1.storeBook();
                 cout<<"\nRecord inserted ";
                 break;
            case 2:
                 b1.viewAllBooks();
                 break;
            case 3:
                 cout<<"\nEnter title of book to search ";
                 cin.ignore();
                 cin.getline(title,19);
                 b1.searchBook(title);
                 break;
            case 4:
                 cout<<"\nEnter book title to delete record ";
                 cin.ignore();
                 cin.getline(title,19);
                 b1.deleteBook(title);
                 break;
            case 5:
                 cout<<"\nEnter book title to update record ";
                 cin.ignore();
                 cin.getline(title,19);
                 b1.updateBook(title);
                 break;
            case 6:
                 cout<<"\nThank you for using this application ";
                 cout<<"\nPress any key to exit";
                 getch();
                 exit(0);
            default:
                cout<<"\nInvalid choice ";
        }
        getch();
    }
}
