# include <iostream>
# include <map>
# include <vector>
# include <queue>

#define MAX_NODES 10000
using namespace std;

struct edge{
    int ID;
    int old_weight;
    int new_weight;
};
typedef struct edge edge;
class node{
    public:
        int ID;
        int parent;
        int distance;
        int distance_certained;
        vector <edge> neighbor;
        map <int,int> route_table; // destination, next node
        map <int,int> route_table_new;
};
vector <int> destination;

void dijkstra(int);
void dijkstra_new(int);
void fill_table(int);
void fill_table_new(int);
node nodes[MAX_NODES];
int NODEs,DSTs,LINKs;
int main(){
    //input
    cin>>NODEs>>DSTs>>LINKs;
    int input[100];
    for(int i=0;i<DSTs;i++){
        cin>>input[0];
        destination.push_back(input[0]);
    }
    for(int i=0;i<LINKs;i++){
        cin>>input[0]>>input[1]>>input[2]>>input[3]>>input[4];  // xx, node1, node2, oldweight, newweight
        edge tmp = {input[2],input[3],input[4]};
        nodes[ input[1] ].neighbor.push_back( tmp );

        tmp.ID = input[1];
        nodes[ input[2] ].neighbor.push_back( tmp );
    }
    for(int i=0;i<NODEs;i++)
        nodes[i].ID=i;
    //input


    for(int i=0;i<NODEs;i++){
        dijkstra(i);  // Do dijkstra algo and build the treee so that fill_table() can run
        fill_table(i); // backtracing the destination node to the node next to root
        cout<<i<<endl;
        for(int j=0;j<DSTs;j++){
            if( destination[j]==i )
                continue;
            cout<<destination[j]<<" "<<nodes[i].route_table[ destination[j] ]<<endl;
        }
    }

    for(int i=0;i<NODEs;i++){
        dijkstra_new(i); // Do the same things as above
        fill_table_new(i);
        int is_i_printed=0;
        for(int j=0;j<DSTs;j++){ // comparing old routing table, if differ, print
            if( destination[j]==i )
                continue;
            if( nodes[i].route_table[ destination[j] ] == nodes[i].route_table_new[ destination[j] ] )
                continue;
            if(!(is_i_printed)){
                is_i_printed=1;
                cout<<i<<endl;
            }

            cout<<destination[j]<<" "<<nodes[i].route_table_new[ destination[j] ]<<endl;
        }
    }








    return 0;
}

void dijkstra(int src){
    for(int i=0;i<NODEs;i++){
        nodes[i].distance=-1;
        nodes[i].parent=-1;
        nodes[i].distance_certained=0;
    }
    nodes[src].distance=0;
    nodes[src].distance_certained=1;
    queue <int> QQQ;
    QQQ.push(src);
    #define u nodes[QQQ.front()]
    while(!QQQ.empty()){
        for(int i=0;i<(int)u.neighbor.size();i++){
            int alt=u.distance + u.neighbor[i].old_weight;
            if(alt < nodes[u.neighbor[i].ID].distance || nodes[u.neighbor[i].ID].distance==-1){
                nodes[u.neighbor[i].ID].distance = alt;
                nodes[u.neighbor[i].ID].parent = u.ID;
                QQQ.push(u.neighbor[i].ID);
            }
            else if(alt == nodes[u.neighbor[i].ID].distance){
                // find out 2 nxt node
                int src_nxt,src_nxt_u;
                if( nodes[u.neighbor[i].ID].parent == src )
                    src_nxt = nodes[u.neighbor[i].ID].ID;
                else{
                    src_nxt = nodes[u.neighbor[i].ID].parent;
                    while( nodes[src_nxt].parent!=src ){
                        src_nxt = nodes[src_nxt].parent;
                    }
                }

                if( u.parent == src )
                    src_nxt_u = u.ID;
                else{
                    src_nxt_u = u.parent;
                    while( nodes[src_nxt_u].parent!=src ){
                        src_nxt_u = nodes[src_nxt_u].parent;
                    }
                }
                    if( src_nxt>src_nxt_u ){
                    nodes[u.neighbor[i].ID].distance = alt;
                    nodes[u.neighbor[i].ID].parent = u.ID;
                    QQQ.push(u.neighbor[i].ID);
                }

            }
        }
        QQQ.pop();
    }
}

void dijkstra_new(int src){
    for(int i=0;i<NODEs;i++){
        nodes[i].distance=-1;
        nodes[i].parent=-1;
        nodes[i].distance_certained=0;
    }
    nodes[src].distance=0;
    nodes[src].distance_certained=1;
    queue <int> QQQ;
    QQQ.push(src);
    #define u nodes[QQQ.front()]
    while(!QQQ.empty()){
        for(int i=0;i<(int)u.neighbor.size();i++){
            int alt=u.distance + u.neighbor[i].new_weight;
            if(alt < nodes[u.neighbor[i].ID].distance || nodes[u.neighbor[i].ID].distance==-1){
                nodes[u.neighbor[i].ID].distance = alt;
                nodes[u.neighbor[i].ID].parent = u.ID;
                QQQ.push(u.neighbor[i].ID);
            }
            else if(alt == nodes[u.neighbor[i].ID].distance){
                // find out 2 nxt node
                int src_nxt,src_nxt_u;
                if( nodes[u.neighbor[i].ID].parent == src )
                    src_nxt = nodes[u.neighbor[i].ID].ID;
                else{
                    src_nxt = nodes[u.neighbor[i].ID].parent;
                    while( nodes[src_nxt].parent!=src ){
                        src_nxt = nodes[src_nxt].parent;
                    }
                }

                if( u.parent == src )
                    src_nxt_u = u.ID;
                else{
                    src_nxt_u = u.parent;
                    while( nodes[src_nxt_u].parent!=src ){
                        src_nxt_u = nodes[src_nxt_u].parent;
                    }
                }
                    if( src_nxt>src_nxt_u ){
                    nodes[u.neighbor[i].ID].distance = alt;
                    nodes[u.neighbor[i].ID].parent = u.ID;
                    QQQ.push(u.neighbor[i].ID);
                }

            }
        }
        QQQ.pop();
    }
}


void fill_table(int nod){
    for(int i=0;i<DSTs;i++){
        int src_nxt;
        if( nodes[destination[i]].parent == nod )
            src_nxt = nodes[destination[i]].ID;
        else{
            src_nxt = nodes[destination[i]].parent;
            while( nodes[src_nxt].parent!=nod ){
                src_nxt = nodes[src_nxt].parent;
            }
        }
        nodes[nod].route_table.insert( pair<int,int>(destination[i],src_nxt) );
    }
}

void fill_table_new(int nod){
    for(int i=0;i<DSTs;i++){
        int src_nxt;
        if( nodes[destination[i]].parent == nod )
            src_nxt = nodes[destination[i]].ID;
        else{
            src_nxt = nodes[destination[i]].parent;
            while( nodes[src_nxt].parent!=nod ){
                src_nxt = nodes[src_nxt].parent;
            }
        }
        nodes[nod].route_table_new.insert( pair<int,int>(destination[i],src_nxt) );
    }
}


