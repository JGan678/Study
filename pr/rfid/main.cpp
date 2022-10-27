#include <ctime>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

unordered_set<string> pass;

bool isTeacher = false;

struct student
{
  string name;
  int num;
  int clas;
  student(string a, int b, int c) : name(a), num(b), clas(c) {}
};

unordered_map<string, struct student> card;

struct course
{
  string name;
  int clas;
  time_t bg;
  time_t ed;
  course() : name(""), clas(0), bg(0), ed(0) {}
} cu;

typedef vector<bool> vb;
unordered_map<string, vb> join;
unordered_map<string, vb> leave;

void auth()
{
  isTeacher = false;
  string ps;
  cout << "Input pass:" << endl;
  cin >> ps;
  if (pass.contains(ps))
    isTeacher = true;
}

void passwd()
{
  string ps;
  cout << "Input pass:" << endl;
  cin >> ps;
  if (pass.contains(ps))
  {
    char tmp;
    cout << "[A]dd or [D]elete:" << endl;
    cin >> tmp;
    if (tmp == 'A')
    {
      cout << "New pass" << endl;
      cin >> ps;
      pass.emplace(ps);
    }
    if (tmp == 'D')
    {
      cout << "Del which" << endl;
      cin >> ps;
      pass.erase(ps);
    }
  }
}

string cardGen()
{
  string cd = "0000000000";
  for (int i = 0; i < 10; ++i)
  {
    int t = rand() % 16;
    if (t < 10)
      cd[i] = '0' + t;
    else
      cd[i] = 'a' + t - 10;
  }
  return cd;
}

void regStudent()
{
  string name;
  int num;
  int clas;
  string cd = cardGen();
  cout << "Name:" << endl;
  cin >> name;
  cout << "Number:" << endl;
  cin >> num;
  cout << "Class:" << endl;
  cin >> clas;
  card.emplace(cd, student(name, num, clas));
  cout << "Your Code: " << cd << endl;
}

void regCourse()
{
  if (!isTeacher)
  {
    cout << "You aren't Teacher" << endl;
    return;
  }
  string name;
  int clas;
  struct tm bg, ed;
  cout << "Name:" << endl;
  cin >> name;
  cout << "Class:" << endl;
  cin >> clas;
  cout << "Begin: Y M D H M S" << endl;
  cin >> bg.tm_year >> bg.tm_mon >> bg.tm_mday >> bg.tm_hour >> bg.tm_min >> bg.tm_sec;
  cout << "End: Y M D H M S" << endl;
  cin >> ed.tm_year >> ed.tm_mon >> ed.tm_mday >> ed.tm_hour >> ed.tm_min >> ed.tm_sec;

  cu.name = name;
  cu.clas = clas;
  cu.bg = mktime(&bg);
  cu.ed = mktime(&ed);
}

void checkin()
{
  string cd;
  char jn;
  time_t ct;
  time(&ct);
  cout << "I'm [J]oining or [L]eaving class:" << endl;
  cin >> jn;
  if (jn != 'J' && jn != 'L')
  {
    cout << "???" << endl;
    return;
  }
  cout << "Your Card:" << endl;
  cin >> cd;
  if (!card.contains(cd))
  {
    cout << "No Such Card" << endl;
    return;
  }
  if (jn == 'J')
  {
    if (join.contains(cd))
      join[cd].emplace_back(ct <= cu.bg);
    else
      join.emplace(cd, vb().emplace_back(ct <= cu.bg));
  }
  if (jn == 'L')
  {
    if (leave.contains(cd))
      leave[cd].emplace_back(ct >= cu.ed);
    else
      leave.emplace(cd, vb().emplace_back(ct >= cu.ed));
  }
}

void queryStudent()
{
  string cd;
  int m = 0, n = 0;
  cout << "Your Card:" << endl;
  cin >> cd;
  if (join.contains(cd))
  {
    for (bool b : join[cd])
    {
      if (b)
        ++m;
      else
        ++n;
    }
    cout << "You arrive in time for " << m << " times, and is late for " << n << " times." << endl;
  }
  else
    cout << "No arrive record" << endl;
  m = 0, n = 0;
  if (leave.contains(cd))
  {
    for (bool b : leave[cd])
    {
      if (b)
        ++m;
      else
        ++n;
    }
    cout << "You leave in time for " << m << " times, and is early for " << n << " times." << endl;
  }
  else
    cout << "No leave record" << endl;
}

void queryCourse()
{
  if (!isTeacher)
  {
    cout << "You aren't Teacher" << endl;
    return;
  }
  for (unordered_map<string, struct student>::const_iterator p = card.cbegin(); p != card.cend(); ++p)
  {
    string cd = p->first;
    int m = 0, n = 0;
    cout << p->second.name << "(" << p->second.num << "):" << endl;
    if (join.contains(cd))
    {
      for (bool b : join[cd])
      {
        if (b)
          ++m;
        else
          ++n;
      }
      cout << "join in time: " << m << ", be late:" << n << endl;
    }
    else
      cout << "No join record" << endl;
    m = 0, n = 0;
    if (leave.contains(cd))
    {
      for (bool b : leave[cd])
      {
        if (b)
          ++m;
        else
          ++n;
      }
      cout << "leave in time: " << m << ", be early: " << n << endl;
    }
    else
      cout << "No leave record" << endl;
  }
  char tmp;
  cout << "Save? Y/N" << endl;
  cin >> tmp;
  if (tmp == 'Y')
  {
    ofstream outs("attend.csv");
    outs << "Student Name, Student Number, Join In Time, Join Late, Leave In Time, Leave Late" << endl;
    for (unordered_map<string, struct student>::const_iterator p = card.cbegin(); p != card.cend(); ++p)
    {
      string cd = p->first;
      outs << p->second.name << ", " << p->second.num;
      int m = 0, n = 0;
      if (join.contains(cd))
      {
        for (bool b : join[cd])
        {
          if (b)
            ++m;
          else
            ++n;
        }
        outs << ", " << m << ", " << n;
      }
      else
        outs << ", 0, 0";
      m = 0, n = 0;
      if (leave.contains(cd))
      {
        for (bool b : leave[cd])
        {
          if (b)
            ++m;
          else
            ++n;
        }
        outs << ", " << m << ", " << n << endl;
      }
      else
        outs << ", 0, 0" << endl;
    }
  }
}

void manage()
{
  if (!isTeacher)
  {
    cout << "You aren't Teacher" << endl;
    return;
  }
  char tmp;
  string st;
  cout << "[A]dd Checkin, [R]emove Checkin, Remove [S]tudent" << endl;
  cin >> tmp;
  if (tmp == 'A')
  {
    cout << "Card" << endl;
    cin >> st;
    if (card.contains(st))
    {
      if (join.contains(st))
        join[st].emplace_back(true);
      else
        join.emplace(st, vb().emplace_back(true));
      if (leave.contains(st))
        leave[st].emplace_back(true);
      else
        leave.emplace(st, vb().emplace_back(true));
    }
    else
      cout << "No such card" << endl;
  }
  if (tmp == 'R')
  {
    cout << "Card" << endl;
    cin >> st;
    if (join.contains(st))
      join[st].clear();
    if (leave.contains(st))
      leave[st].clear();
  }
  if (tmp == 'S')
  {
    cout << "Card" << endl;
    cin >> st;
    if (card.contains(st))
      card.erase(st);
    else
      cout << "No such card" << endl;
  }
}

int main()
{
  pass.emplace("666");
  int mode = 1;
  while (mode)
  {
    cout << "choose mode: (0 to quit)" << endl;
    cout << "1 register student" << endl;
    if (isTeacher)
      cout << "2 register course" << endl;
    cout << "3 checkin" << endl;
    cout << "4 query student" << endl;
    if (isTeacher)
      cout << "5 query course" << endl;
    if (isTeacher)
      cout << "6 manage" << endl;
    cin >> mode;
    switch (mode)
    {
    case 1:
      regStudent();
      break;
    case 2:
      regCourse();
      break;
    case 3:
      checkin();
      break;
    case 4:
      queryStudent();
      break;
    case 5:
      queryCourse();
      break;
    case 6:
      manage();
      break;
    case 8:
      auth();
      break;
    case 9:
      passwd();
      break;
    default:
      mode = 0;
    }
  }
}