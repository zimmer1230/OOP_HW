#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <queue>
using namespace std;

class node{
    public:
        class edge{
            public:
                node* target;
                unsigned int old_weight;
                unsigned int new_weight;
        };

    unsigned int ID;
    node* parent;
    vector < edge > neighbor; // node,Old weight, New weight
    map <unsigned int, int> table; //dstnation , distance
    void fill_in_table(int version);
};
node nodes [1000];
vector <int> destinations;

int NODES,DSTS,LINKS;

int main(){
    cin>>NODES>>DSTS>>LINKS;
    for(int i=0;i<NODES;i++)
        nodes[i].ID=i;
    for (int i=0;i<DSTS;i++){
        int tmp;
        cin>>tmp;
        destinations.push_back(tmp);
    }
    for (int i=0;i<LINKS;i++){
        unsigned int a,b,c,d,e; //LinkID Node1 Node2 oldW newW
        cin>>a>>b>>c>>d>>e;
        node::edge edges;
        edges.target=&nodes[c];
        edges.old_weight=d;
        edges.new_weight=e;
        nodes[b].neighbor.push_back(edges);
        edges.target=&nodes[b];
        nodes[c].neighbor.push_back(edges);
    }
    for(int i=0;i<NODES;i++){
        nodes[i].initialize_the_node();
        nodes[i].fill_in_table(0);
        cout<<"Now it's "<<i<<"'s view"<<endl;
        for(int j=0;j<NODES;j++){
            if( nodes[j].parent!=NULL ){
                cout<<nodes[j].parent->ID<<" "<<endl;
            }
            else
                cout<<"This node has no parent"<<endl;
        }
    }

//    for(int i=0;i<NODES;i++){
//        nodes[i].initialize_the_node();
//        nodes[i].fill_in_table(0);
//        cout<<nodes[i].ID<<endl;
//        for( int j=0;j<destinations.size();j++ ){
//            if(destinations[j]==nodes[i].ID)
//                continue;
//            node* finding_root=&nodes[destinations[j]];
//            while( finding_root->parent->parent!=NULL  ){
//                finding_root=finding_root->parent;
//            }
//            cout<<destinations[j]<<" "<<finding_root->ID<<endl;
//        }
//    }

    return 0;
}

# define nigger nodes[QQQ.front()].neighbor[i]
void node::fill_in_table(int version){ // version==0, old_weight; version==1, new_weight
    queue  <unsigned int> QQQ;
    QQQ.push(ID);
    while (!QQQ.empty()){
      for(int i=0;i<nodes[QQQ.front()].neighbor.size();i++){
          int alt = table[QQQ.front()] + nigger.old_weight;
          if (alt < table[nigger.target->ID]){
              cout<<" alt < table qweqeqw"<<endl;
              QQQ.push(nigger.target->ID);
              table[ nigger.target->ID ] = alt;
              nodes[ nigger.target->ID ].parent = &nodes[QQQ.front()];
          }
      }
      QQQ.pop();
    }
};
void initialize_nodes(){
    for(int i=0;i<NODES;i++)
        nodes[i].parent=NULL;
    table.clear();
    for(int i=0;i<NODES;i++){
        table.insert( pair<unsigned int,int> (i,4294967295) );
    }
    table[ID]=0;
}
