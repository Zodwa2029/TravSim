#include<iostream>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<string.h>
using namespace std;
 
int menu();
class Book
{
      private:
              int bookid;
              char title[20];
              float price;
      protected:
                int allotbookid();
                void showheader();
      public:
             void getbook();
             void showbook();
             void addbook();
             void viewbook();
             void searchbook();
             void deletebook();
             void modifybook();
};
 
int Book::allotbookid()
{
    ifstream myfile;
    Book temp;
    int id=0;
    myfile.open("C:\\Code\\TravSim\\books.txt",ios::in|ios::binary);
    if(!myfile)
            return(id+1);
    else
    {
        myfile.read((char*)&temp,sizeof(temp));
        while(!myfile.eof())
        {
         id=temp.bookid;
         myfile.read((char*)&temp,sizeof(temp));
        }
        id++;
        return(id);
    }
}
 
 
void Book::showheader()
{
     cout<<left;
     cout<<"\n"<<setw(10)<<"BOOK ID"<<setw(10)<<"Price"<<setw(10)<<"Title\n";
}
void Book::getbook()
{
     cout<<"Enter Book Title: ";
     fflush(stdin);
     gets(title);
     cout<<"Price of Book: ";
     cin>>price;
     bookid=allotbookid();
}
void Book::showbook()
{
     cout<<left;
     cout<<"\n"<<setw(10)<<bookid<<setw(10)<<price<<setw(10)<<title;
}
void Book::addbook()
{
     ofstream fout;
     fout.open("C:\\Code\\TravSim\\books.txt",ios::out|ios::app|ios::binary);
     if(!fout)
              cout<<"File can not open";
     else
              fout.write((char*)this,sizeof(*this));
     fout.close();
}
void Book::viewbook()
{
     ifstream myfile;
     myfile.open("C:\\Code\\TravSim\\books.txt",ios::in|ios::binary);
     if(!myfile)
             cout<<"File not found";
     else
     {
         showheader();
         myfile.read((char*)this,sizeof(*this));
         while(!myfile.eof())
         {
          showbook();
          myfile.read((char*)this,sizeof(*this));
         }
     }
     myfile.close();
}
void Book::searchbook()
{
     ifstream myfile;
     char str[20];
     myfile.open("C:\\Code\\TravSim\\books.txt",ios::in|ios::binary);
     cout<<"Enter the name of book to search:";
     fflush(stdin);
     gets(str);
     if(!myfile)
             cout<<"File not found";
     else
     {
         myfile.read((char*)this,sizeof(*this));
         while(!myfile.eof())
         {
 
          if(!strcmp(this->title,str))
          {
            showheader();
            showbook();
            break;
          }
          myfile.read((char*)this,sizeof(*this));
         }
         if(myfile.eof())
          cout<<"\nRecord not found";
     }
     myfile.close();
}
void Book:: modifybook()
{
     int id,r=0;
     fstream myfile;
     myfile.open("C:\\Code\\TravSim\\books.txt",ios::in|ios::out|ios::ate|ios::binary);
     cout<<"\nEnter record number to modify (bookid): ";
     cin>>id;
     myfile.seekg(0);
     if(!myfile)
             cout<<"File not found";
     else
     {
         myfile.read((char*)this,sizeof(*this));
 
         while(!myfile.eof())
         {
           r++;
           if(bookid==id)
           {
             showheader();
             showbook();
             cout<<"\nRe-enter book details:\n";
             cout<<"Enter book title:";
             fflush(stdin);
             gets(title);
             cout<<"Enter book price";
             cin>>price;
             myfile.seekp((r-1)*sizeof(Book),ios::beg);
             myfile.write((char*)this,sizeof(*this));
             break;
           }
           myfile.read((char*)this,sizeof(*this));
         }
         if(myfile.eof())
                      cout<<"Record not found";
     }
         myfile.close();
}
void Book:: deletebook()
{
     ifstream myfile;
     ofstream fout;
     int id;
     char x;
     myfile.open("C:\\Code\\TravSim\\books.txt",ios::in|ios::binary);
     fout.open("C:\\Code\\TravSim\\tempbooks.txt",ios::out|ios::app|ios::binary);
     cout<<"Enter bookid to delete record";
     cin>>id;
     if(!myfile)
             cout<<"File not found";
     else
     {
         myfile.read((char*)this,sizeof(*this));
         while(!myfile.eof())
         {
          if(this->bookid==id)
          {
            cout<<"Record you want to delete is:\n\n";
            showheader();
            showbook();
            cout<<"\nAre you sure you want to delete this record(y/n): ";
            fflush(stdin);
            cin>>x;
            if(x=='n')
                         fout.write((char*)this,sizeof(*this));
            else
                         cout<<"\nRecord is deleted";
          }
          else
              fout.write((char*)this,sizeof(*this));
          myfile.read((char*)this,sizeof(*this));
         }
         myfile.close();
         fout.close();
 
 
                      system("erase C:\\Code\\TravSim\\books.txt");
                      system("rename C:\\Code\\TravSim\\tempbooks.txt C:\\Code\\TravSim\\books.txt");
 
 
     }
}
int menu()
{
    system("cls");
    cout<<"\n1. Add new book";
    cout<<"\n2. View all books";
    cout<<"\n3. Search book";
    cout<<"\n4. modify book";
    cout<<"\n5. delete book";
    cout<<"\n6. Exit";
    cout<<"\n\nEnter your choice";
    int ch;
    cin>>ch;
    return(ch);
}
int main()
{
    Book b;
    int ch;
    while(1)
    {
           ch=menu();
           switch(ch)
           {
                     case 1:
                            b.getbook();
                            b.addbook();
                            break;
                     case 2:
                            b.viewbook();
                            break;
                     case 3:
                            b.searchbook();
                            break;
                     case 4:
                            b.modifybook();
                            break;
                     case 5:
                            b.deletebook();
                            break;
                     case 6:
                            exit(0);
                     default:
                            cout<<"Enter Valid choice";
           }
    }
 
    return 0;
}