#include <iostream>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

struct CEdge;

struct CNode
{
    CNode(int x, int y,float x1, float y1)
    {
        valuex = x;
        valuey = y;
        value_x=x1;
       value_y=y1;
    }

    list<CEdge*> edges;
    int valuex;
    int valuey;
    float value_x;
    float value_y;
    bool estado = true;
};

struct CEdge
{
    CEdge(CNode* a, CNode* b, float distance)
    {
        nodes[0] = a; nodes[1] = b;
        distancia = distance;
        nodes[0]->edges.push_back(this);
        nodes[1]->edges.push_back(this);
    }

    ~CEdge() {}

    CNode* nodes[2];
    float distancia;
};

class CGraph
{
public:
    bool InsertNode()
    {   
        float x_pr = -1;
        float y_pr = 1;

        for (int i = 0; i < 20; ++i)
        {
            vector<CNode*> t1;
            for (int j = 0; j < 20; ++j)
            {

                CNode* node = new CNode(i, j,x_pr,y_pr);
                t1.push_back(node);
                x_pr = x_pr + 0.04;

            }
            x_pr = -1;
            nodes.push_back(t1);
            y_pr = y_pr-0.04;
        }
        return true;
    }

    bool InsertEdge(CNode* a, CNode* b, float dist)
    {
        new CEdge(a, b, dist);
        return true;
    }

    bool ConnectNodes()
    {
        int numRows = nodes.size();
        int numCols = nodes[0].size();

        // Loop through each node to connect with its adjacent nodes
        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; j < numCols; ++j)
            {
                // Connect with right node if it exists
                if (j + 1 < numCols)
                {
                    InsertEdge(nodes[i][j], nodes[i][j + 1], 10);
                }

                // Connect with bottom node if it exists
                if (i + 1 < numRows)
                {
                    InsertEdge(nodes[i][j], nodes[i + 1][j], 10);
                }

                // Connect with diagonal node (bottom right) if it exists
                if (i + 1 < numRows && j + 1 < numCols)
                {
                    InsertEdge(nodes[i][j], nodes[i + 1][j + 1], 10 * sqrt(2));
                }

                // Connect with diagonal node (top right) if it exists
                if (i - 1 >= 0 && j + 1 < numCols)
                {
                    InsertEdge(nodes[i][j], nodes[i - 1][j + 1], 10 * sqrt(2));
                }
            }
        }
        return true;
    }
public:
    vector<vector<CNode*>> nodes;
};


int main()
{
    CGraph graph;
    graph.InsertNode();
    graph.ConnectNodes();

    cout << "Nodes and their edges:\n";

    cout << graph.nodes[1][1]->value_x<<' '<< graph.nodes[1][1]->value_y;
}