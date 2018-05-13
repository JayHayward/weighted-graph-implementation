#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Graph.cpp"
using namespace std;

Graph gp;

void readFile(string filename)
{
  fstream file;
  file.open(filename);

  if(file)
  {
    string ele, line, name;
    getline(file,line,'\n'); //removes first line
    stringstream ss(line);
    getline(ss, line, ',');

    while(getline(ss,line, ','))
    {
      gp.addVertex(line);
      // cout<<line<<'\n';
      names.push_back(line);

      // cout<<ele<<endl;
    }
    while(getline(file, ele))
    {
      // cout<<ele<<'\n';
      string c1, c2, w;
      stringstream zz(ele);
      getline(zz, c1, ',');
      // cout<<c1<<'\n';
      int i=0;
      while(getline(zz, c2, ','))
      {
        if(stoi(c2) > 0)
          gp.addEdge(c1, names[i], stoi(c2));
        // cout<<c1<<" "<<c2<<"\n";
        i++;
      }
    }
  }
  else
    cout<<"error reading file\n";
}

int printMenu()
{
  cout<<"======Main Menu======\n";
  cout<<"1. Print vertices\n";
  cout<<"2. Find districts\n";
  cout<<"3. Find shortest path\n";
  cout<<"4. Find shortest weighted path\n";
  cout<<"5. Quit\n";

  string selection;
  // cin>>selection;
  getline(cin,selection);

  // int iSel;
  // try{
  //   iSel = stoi(selection);
  //   return iSel;
  // }
  // catch(...){
  //   cout<<"Invalid\n";
  //   printMenu();
  // }

  return stoi(selection);
}

int main(int argc, char *argv[])
{
  readFile(argv[1]);
  // readFile("zombieCities.txt");

  int sel = printMenu();
  if((sel < 1) || (sel > 5))
  {
    cout<<"invalid\n";
    sel = printMenu();
  }

  while(true)
  {
    if(sel == 1)
    {
      // cout<<sel<<'\n';
      gp.displayEdges();
      sel = printMenu();
    }
    if(sel == 2)
    {
      // cout<<sel<<'\n';
      gp.assignDistricts();
      sel = printMenu();
    }
    if(sel == 3)
    {
      // cout<<sel<<'\n';
      string in1, in2;
      cout<<"Enter a starting city:\n";
      getline(cin, in1);
      cout<<"Enter an ending city:\n";
      getline(cin, in2);
      gp.shortestPath(in1, in2);

      // cout<<in1<<" "<<in2<<'\n';
      // gp.shortestPath("Atlanta", "Boston"); //no path
      // gp.shortestPath("Portland", "Yakima");
      sel = printMenu();
    }
    if(sel == 4)
    {
      cout<<sel<<'\n';
      sel = printMenu();
    }
    if(sel == 5)
    {
      cout<<"Goodbye!"<<'\n';
      return 0;
    }
  }
}
