/*
Author: Cashton Christensen
        Project 1
Purpose:  Read in a file of student's names with grades. Sort list based on grades.
          Read in a file of student's names and sizes of student groups.
            Sort these students into groups based on whose grades are closest
            to initial student's grade.
          Print out the groups.
*/
#include<iostream>
#include<list>      //BUILT IN LINKED LIST
#include<fstream>   //READS IN FILE TO BE SORTED AND PRINTED
#include<algorithm> //SORT PUTS SLIST IN ORDER
#include<cstring>   //STRCPY(usable, readin)
using namespace std;

struct student
{
  char m_name[21];
  double m_grade;
};
template<typename Iterator>
void printList(Iterator begin, Iterator end);//Prints off values in a LList
bool compare(student first, student second);//Compares Items in list for std::sort()
template<typename Iterator>
void printMlist(Iterator begin, Iterator end);//Prints off the values of the indv lists in Mlist
template<typename Iterator>
Iterator setCursor(Iterator begin, Iterator end, Iterator cur, char [21]);//Sets curosr iterator == found name or returns error

int main()
{
  list<student> Slist;//The Sorted List of all student structs
  list<student> Glist;//The student Group list of varied sizes
  list<student> TempList;//The temporary groups that get copied into Mlist and cleared()
  list<list<student> > Mlist;//The Master List of smaller TempLists

  ifstream in_list;

  in_list.open("/home/win.thackerw/271/peer/master.dat", ios::in);// open the master list
  if(!in_list)//ERROR CHECK
  {
      cerr << "Unable to open file datafile.txt\n";
      exit(1);  //Call system to stop
  }

  double in_grade;
  char in_name[21];
  student in_student;

  while(in_list>>in_name && in_list>>in_grade)//While file has data in correct format
  {
    strcpy(in_student.m_name, in_name);
    in_student.m_grade = in_grade;
    Slist.push_front(in_student);
  }
  Slist.sort(compare);

  in_list.close();// close the master list
  cout << endl;
////////////////////////////////////////////////////////////////////////////////
  in_list.open("/home/win.thackerw/271/peer/groups.dat", ios::in);// open the group list
  if(!in_list)//ERROR CHECK
  {
      cerr << "Unable to open file datafile.txt\n";
      exit(1);//Call system to stop
  }

  char in_name2[21];
  int in_groupnum;
  student in_group;
  list<student>::iterator cursor, left, right;

  while(in_list>>in_name2 && in_list>>in_groupnum)//While file has data in correct format
  {
    strcpy(in_group.m_name, in_name2);
    in_group.m_grade = in_groupnum;

    //Set cursor, left-of-cursor, and right-of-cursor
    cursor = setCursor(Slist.begin(), Slist.end(), cursor, in_name2);//Set Cursor
    TempList.push_back(*cursor);//Send the name of interest into the list
    if(cursor == Slist.begin()){left = cursor;}//If cursor is first in list
    else{left = --cursor;}
    if(cursor == Slist.end()){right = cursor;}//If cursor is last in list
    else{
      right = ++cursor;
      right++;
    }

    double Lcompare, Rcompare;
    int count = in_groupnum-1;

    ////////////////////////////////////////////////////////////////////
    // Math Sort: Middle of the sorted linked list
    ////////////////////////////////////////////////////////////////////

    while((left != Slist.begin()) && (right != Slist.end()) && (count > 0))
    {
      Lcompare = cursor->m_grade - left->m_grade;
      Rcompare = right->m_grade - cursor->m_grade;

      if(Lcompare>=Rcompare)//If left_value is <= right_value
      {
        TempList.push_back(*right);//copy right into Glist
        right++;//Shifting up list
      }
      else //If left_value is > right_value
      {
        TempList.push_back(*left);//copy left into Glist
        left--;//Shifting down list
      }
      count--;
    }
      //If all names to the left AND right of the cursor are used, send error message
      if((left == Slist.begin()) && (right == Slist.end()) && (count != 0))
      {
        cerr << "List not large enough to make this group" << endl << "\t";
      }
        ////////////////////////////////////////////////////////////////////
        // Math Sort: Beginning of the sorted linked list
        ////////////////////////////////////////////////////////////////////

    if(left == Slist.begin())//If all name to left of cursor have been added, use right
    {
      //Checking if all names to right of cursor have been added
      while((right != Slist.end()) && (count > 0))
      {
        TempList.push_back(*right);
        right++;
        count--;
      }
      //If all names to right of cursor have been added, send error message
      if((right == Slist.end()) && (count != 0))
      {
        cerr << "List not large enough to complete this group" << endl << "\t";
      }
    }
        ////////////////////////////////////////////////////////////////////
        // Math Sort: End of the sorted linked list
        ////////////////////////////////////////////////////////////////////

    if(right == Slist.end())//If all name to right of cursor have been added, use left
    {
      //Checking if all names to left of cursor have been added
      while((left != Slist.begin()) && count > 0)
      {
        TempList.push_back(*left);
        left--;
        count--;
      }
      //If all names to right of cursor have been added, send error message
      if((left == Slist.begin()) && (count != 0))
      {
        cerr << "List not large enough to complete this group" << endl << "\t";
      }
    }
    cout << "List Compiled" << endl;
    Mlist.push_back(TempList);
    TempList.clear();
  }

  printMlist(Mlist.begin(), Mlist.end());//Prints off all groups in MList

  in_list.close();//close the group list
////////////////////////////////////////////////////////////////////////////////
  return 0;
}
/*******************************************************************************
Name: setCursor
Purpose: Sets the cursor iterator = the name || returns an error "not found"
*******************************************************************************/
template<typename Iterator>
Iterator setCursor(Iterator begin, Iterator end, Iterator cur, char sample[21])
{
  cur = begin;

  while(cur != end)
  {
    if(strcmp(cur-> m_name, sample)==0)//Comparing the char arrays
    {
      return cur;//placing the cursor on the relevant last name
    }
    cur++;
  }
  cout << "Last name not found" << endl;
  return --cur;//Keeping the cur within the scope of the list to prevent seg fault
}

/*******************************************************************************
Name: printList
Purpose: Prints out the values in an STL Linked List of any data type using
          iterators.
*******************************************************************************/
template<typename Iterator>
void printList(Iterator begin, Iterator end)
{
  int count = 1;
  while(begin != end)
  {
    student user = *begin;
    cout << count << ") " << user.m_name << "   \t";
    cout << user.m_grade << "\n";
    count++;
    begin++;
  }
  cout << endl;
}
/*******************************************************************************
Name: PrintMlist()
Purpose: Print the master print list
*******************************************************************************/
template<typename Iterator>
void printMlist(Iterator begin, Iterator end)
{
  int count = 1;
  while(begin != end)
  {
    list<student> copy = *begin;
    cout << "Group " << count << ": ";
    cout << "Size: " << copy.size() << endl << endl;
    printList(copy.begin(), copy.end());
    cout << "--------------------\n";
    count++;
    begin++;
  }
}
/*******************************************************************************
Name: compare
Purpose: Takes the grade from each student struct compares it for std::sort()
*******************************************************************************/
bool compare(student first, student second)
{
  if (first.m_grade < second.m_grade)//comparing the double values of the structs
    return true;
  else
    return false;
}
