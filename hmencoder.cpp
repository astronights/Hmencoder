#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <deque>
#include <map>
#include <algorithm>
using namespace std;

struct Node
{
  int f;
  char c;
  Node *left;
  Node *right;
};
bool compare(Node *&a, Node *&b)
{
    return a->f < b->f;
}
bool find(deque<Node*>q, char word)
{
  deque<Node*>::iterator itr;
  for(itr = q.begin(); itr != q.end(); itr++)
  {
    if((*itr)->c == word)
    {
      return true;
    }
  }
  return false;
}
int Traverse(Node *n, string s, map<char, string> &m)
{
  if(n->left == NULL && n->right == NULL)
  {
    m[n->c] = s;
    return (s.length())*n->f;
  }
  int l = Traverse(n->left, s+"0", m);
  int l1 = Traverse(n->right, s+"1", m);
  return l + l1;
}
int main(int argc, char *argv[])
{
  ifstream fin;
  ofstream fout, fo;
  string filename = "input_file.txt";
  filename = argv[1];
  fin.open(filename);
  char c;
  deque<Node*>q;
  map<char, string> m;
  int counter = 0;
  if(fin.fail())
  {
    cout<<"Can't open the file..."<<endl;
    exit(0);
  }
  while(fin.get(c))
  {
    if(int(c) >= 32 && int(c) <= 126)
    {
      if(find(q, c))
      {
        deque<Node*>::iterator itr;
        for(itr = q.begin(); itr!= q.end(); itr++)
        {
          if((*itr)->c == c)
          {
            (*itr)->f++;
          }
        }
      }
      else
      {
        Node *lol = new Node();
        lol->f = 1;
        lol->c = c;
        lol->left = lol->right = NULL;
        q.push_back(lol);
      }
    }
  }
  fin.close();
  deque<Node*>::iterator itr;
  for(itr = q.begin(); itr != q.end(); itr++)
  {
    counter += (*itr)->f;
  }
  sort(q.begin(), q.end(), compare);
  int total = 0;
  if(q.size() == 1)
  {
    Node* temp = new Node();
    temp = q.front();
    m[temp->c] = "0";
    total = q.front()->f;
  }
  else
  {
    while(q.size()>1)
    {
      Node* at = new Node();
      at = q.front();
      q.pop_front();
      Node* bt = new Node();
      bt = q.front();
      q.pop_front();
      Node* nt = new Node();
      nt->f = at->f + bt->f;
      nt->c = '\0';
      nt->left = at;
      nt->right = bt;
      q.push_front(nt);
      sort(q.begin(), q.end(), compare);
    }
    total = Traverse(q.front(), "", m);
  }
  fout.open("code.txt");
  map<char, string>::iterator itr1;
  for(itr1 = m.begin(); itr1 != m.end(); itr1++)
  {
    if((*itr1).first == ' ')
    {
      fout<<"Space: "<<(*itr1).second<<endl;
    }
    else
    {
        fout<<(*itr1).first<<": "<<(*itr1).second<<endl;
    }
  }
  fout<<"Ave = "<<setprecision(3)<<float(total)/float(counter)<<" bits per symbol";
  fout.close();
  fin.open(filename);
  fo.open("encodemsg.txt");
  while(fin.get(c))
  {
    fo << m[c];
  }
  fin.close();
  fo.close();
  return 0;
}
