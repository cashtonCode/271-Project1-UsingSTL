#include<iostream>  //
#include<list>      //BUILT IN LINKED LIST
#include<fstream>   //READS IN FILE TO BE SORTED AND PRINTED
#include<algorithm> //SORT PUTS SLIST IN ORDER
#include<cstring>   //STRCPY(usable, readin)
//#include<iterator>
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
  list<list<student> > Mlist;//The Master List of smaller GLists

  student Cashton = {"Cashton", 100.0};
  student Bobby = {"Bobby", 90.9};
  student Miles = {"Miles", 80.8};

  Slist.push_back(Cashton);
  Slist.push_back(Bobby);
  Slist.push_back(Miles);
  printList(Slist.begin(), Slist.end());
  Slist.sort(compare);
  printList(Slist.begin(), Slist.end());
////////////////////////////////////////////////////////////////////////////////
  Glist.push_front(Bobby);
  Glist.push_front(Cashton);
  printList(Glist.begin(), Glist.end());

  Mlist.push_front(Glist);
  Mlist.push_front(Slist);
  printMlist(Mlist.begin(), Mlist.end());
////////////////////////////////////////////////////////////////////////////////
  cout << "List Reset\n" << endl;
  Slist.clear();
  Glist.clear();
  Mlist.clear();
////////////////////////////////////////////////////////////////////////////////
    double in_grade;
    char in_name[21];
    student in_student;

  ifstream in_list;
//  in_list.open("master.dat", ios::in);  // open the master list
  in_list.open("/home/win.thackerw/271/peer/master.dat", ios::in);  // open the master list
    if(!in_list)//ERROR CHECK
    {
        cerr << "Unable to open file datafile.txt\n";
        exit(1);  //Call system to stop
    }
  while(in_list>>in_name && in_list>>in_grade)
  {
    strcpy(in_student.m_name, in_name);
    in_student.m_grade = in_grade;
    Slist.push_front(in_student);
  }
  Slist.sort(compare);
  printList(Slist.begin(), Slist.end());
  in_list.close();                      // close the master list
  cout << endl;
////////////////////////////////////////////////////////////////////////////////
  //in_list.open("groups.dat", ios::in);  // open the group list
  in_list.open("/home/win.thackerw/271/peer/groups.dat", ios::in);  // open the group list
    if(!in_list)//ERROR CHECK
    {
        cerr << "Unable to open file datafile.txt\n";
        exit(1);  //Call system to stop
    }

  char in_name2[21];
  int in_groupnum;
  student in_group;

/*
  while(in_list>>in_name2 && in_list>>in_groupnum)
  {
    strcpy(in_group.m_name, in_name2);
    in_group.m_grade = in_groupnum;
    Glist.push_front(in_group);
  }
  printList(Glist.begin(), Glist.end());
*/
////////////////////////////////////////////////////////////////////////////////
/*  list<student>::iterator cursor, left, right, test;

  test = Slist.begin();
  for(int i=0; i<1; i++)
  {
    test++;
  }
  student sample = *test;
  cursor = setCursor(Slist.begin(), Slist.end(), cursor, sample.m_name);
  left = --cursor;
  right = ++cursor;
  right++;
  cout << "left: "<< left->m_name << endl << "cursor: " << cursor->m_name << endl << "right: "<< right->m_name << endl;


  int Lcompare, Rcompare, count = 16;
*/
  /*Sorting Groups Math
    use student.grade
      if in middle: (iter++ - curriter)<?> (curriter - iter--)
      if at beginning: use beginning iterator++
      if at end: us ending iterator--
  */
////////////////////////////////////////////////////////////////////////////////
  //LOOP THIS FOR ALL IN GLIST
  //  SET NAME == sample
  //  SET NUMB == count
  list<student>::iterator cursor, left, right, test;


  while(in_list>>in_name2 && in_list>>in_groupnum)
  {
    strcpy(in_group.m_name, in_name2);
    in_group.m_grade = in_groupnum;

    cout << in_name2 << "  " << in_groupnum << endl;

    cursor = setCursor(Slist.begin(), Slist.end(), cursor, in_name2);
    TempList.push_back(*cursor);
    if(cursor == Slist.begin()){left = cursor;}
    else{left = --cursor;}
    if(cursor == Slist.end()){right = cursor;}
    else{
      right = ++cursor;
      right++;
    }
    double Lcompare, Rcompare;
    int count = in_groupnum-1;

    while((left != Slist.begin()) && (right != Slist.end()) && (count > 0))
    {
      Lcompare = cursor->m_grade - left->m_grade;
      Rcompare = right->m_grade - cursor->m_grade;

      if(Lcompare>=Rcompare)
      {
        TempList.push_back(*right);      //copy right into Glist
        right++;
      }
      else//Lcompare < Rcompare
      {
        TempList.push_back(*left);      //copy left into Glist
        left--;
      }
      count--;
    }
      if((left == Slist.begin()) && (right == Slist.end()) && (count != 0))
      {
        cerr << "List not large enough to make this group\n" << endl;
      }
        ////////////////////////////////////////////////////////////////////
    if(left == Slist.begin())
    {
      Rcompare = right->m_grade - cursor->m_grade;
      while((right != Slist.end()) && (count > 0))
      {
        TempList.push_back(*right);
        right++;
        count--;
      }
      if((right == Slist.end()) && (count != 0))
      {
        cerr << "List not large enough to complete this group\n" << endl;
      }
    }
        ////////////////////////////////////////////////////////////////////
    if(right == Slist.end())
    {
      while((left != Slist.begin()) && count > 0)
      {
        TempList.push_back(*left);
        left--;
        count--;
      }
      if((left == Slist.begin()) && (count != 0))
      {
        cerr << "List not large enough to complete this group\n" << endl;
      }
    }
    Mlist.push_back(TempList);
    TempList.clear();
  }
  printMlist(Mlist.begin(), Mlist.end());
////////////////////////////////////////////////////////////////////////////////
  cout << "Hello End" << endl;

  in_list.close();                      //close the group list
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
    if(strcmp(cur-> m_name, sample)==0)
    {
      return cur;
    }
    cur++;
  }
  cout << "Last name not found" << endl;
  return --cur;
}

/*******************************************************************************
Name: printList
Purpose: Prints out the values in an STL Linked List of any data type using
          iterators.
*******************************************************************************/
template<typename Iterator>
void printList(Iterator begin, Iterator end)
{
  while(begin != end)
  {
    student user = *begin;
    cout << user.m_name << "\t";
    cout << user.m_grade << "\n";
    begin++;
    //cout << endl;
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
    cout << "Group " << count << ": " << endl;
    cout << "   Size: " << copy.size() << endl;
    printList(copy.begin(), copy.end());
    cout << endl;
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
  if (first.m_grade < second.m_grade)
    return true;
  else
    return false;
}
