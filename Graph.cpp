#include "Graph.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <cmath>

using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}

vector<int> nums;
vector<string> names;

void Graph::addEdge(string v1, string v2, int weight)
{
  // cout<<v1<<" "<<v2<<" "<<weight<<'\n';
  for(int i = 0; i < vertices.size(); i++){
      if(vertices[i].name == v1){
          for(int j = 0; j < vertices.size(); j++){
              if(vertices[j].name == v2 && i != j){
                  adjVertex av;
                  av.v = &vertices[j];
                  av.weight = weight;
                  vertices[i].adj.push_back(av);
                  //another vertex for edge in other direction
                  // adjVertex av2;
                  // av2.v = &vertices[i];
                  // av2.weight = weight;
                  // vertices[j].adj.push_back(av2);
              }
          }
      }
  }
}
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.districtID=-1;
        vertices.push_back(v);

    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].districtID<<":";
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            if(j != vertices[i].adj.size()-1)
            {
              cout<<"***";
            }
        }
        cout<<'\n';
    }
}

void Graph::DFSLabel(string source, int ID)
{
  vertex *start;
  for (int i = 0; i < (int)vertices.size(); i++)
  {
    vertices[i].visited = false;
    if (vertices[i].name == source)
    {
      start = &vertices[i];
    }
  }

  // cout<<"DFS\n";
  stack<vertex*> S;
  start->districtID = ID;
  S.push(start);
  start->visited = true;
  while(!S.empty())
  // cout<<"While\n";
  {
    vertex *node = S.top();
    S.pop();
    // cout<<"Pop\n";
    for(int n=0; n < (int)node->adj.size(); n++)
    {
      // cout<<"For\n";
      if(!node->adj[n].v->visited)
      {
        // cout<<"If\n";
        node->adj[n].v->visited = true;
        S.push(node->adj[n].v);
        node->adj[n].v->districtID = ID;
      }
    }
  }
}

void Graph::assignDistricts()
{
  int c=1;
  for(int x=0; x < (int)vertices.size(); x++)
  {
    //check to see if you already hit node
    if (vertices[x].districtID == -1)
    {
      DFSLabel(vertices[x].name, c);
      c++;
    }
  }
}


void Graph::shortestPath(string source, string destination)
{
  //first chack if cities exist
  bool flagA = false;
  bool flagB = false;
  for(int a=0; a < (int)vertices.size(); a++)
  {
    if(vertices[a].name == source)
    {
      flagA = true;
      break;
    }
  }
  for(int b=0; b < (int)vertices.size(); b++)
  {
    if(vertices[b].name == destination)
    {
      flagB = true;
      break;
    }
  }
  if((flagA == false)||(flagB == false))
  {
    cout<<"One or more cities doesn't exist\n";
    return;
  }

  vertex *src;
  vertex *dst;
  for (int i = 0; i < (int)vertices.size(); i++)
  {
    vertices[i].visited = false;
    if (vertices[i].name == source)
    {
      src = &vertices[i];
    }
    if(vertices[i].name == destination)
    {
      dst = &vertices[i];
    }
  }

  //check if districts are set
  if((src->ID == -1)||(dst->ID == -1))
  {
    cout<<"Please identify the districts before checking distances\n";
    return;
  }

  if(src->districtID != dst->districtID)
  {
    cout<<"No safe path between cities\n";
  }
  else
  {
    queue<vertex*> Q;
    Q.push(src);
    src->visited = true;
    stack<vertex*> stored;
    // cout<<"source: "<<src->name<<'\n';
    while(!Q.empty())
    {
      vertex *node = Q.front();
      Q.pop();
      for(int i=0; i < (int)node->adj.size(); i++)
      {
        if(!node->adj[i].v->visited)
        {
          node->adj[i].v->parent = node;
          node->adj[i].v->visited = true;
          Q.push(node->adj[i].v);
          if(node->adj[i].v->name == destination)
          {
            vertex *w = node->adj[i].v;
            while(w->name != source)
            {
              stored.push(w);
              w = w->parent;
            }
          }
        }
      }
    }
    cout<<stored.size()<<", "<<src->name<<", ";
    for(int x = 0; x < (int)stored.size(); x++)
    {
      cout<<stored.top()->name<<", ";
      stored.pop();
    }
    cout<<dst->name<<'\n';
  }
}
