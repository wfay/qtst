#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
//#include "noisynode.h"
//#include "gridnode.h"
#include "linenode.h"
using namespace std;
string line;
Graph::Graph()
    : m_samplesChanged(false)
    , m_geometryChanged(false)
{
    setFlag(ItemHasContents, true);
    datafile.open("data.txt");
}


void Graph::appendSample(QString id)
{
    static int idx=0;
    string name,ti,interval,ask,bid;
    stringstream linestream;
 //   while(getline(datafile,line))
    {
        getline(datafile,line);
        if(!getline(datafile,line)){return;}
    linestream.str(line);
    getline(linestream,name,',');
    if(name!="IF1509"){return;}
    getline(linestream,ti,',');
    getline(linestream,interval,',');
    getline(linestream,ask,',');
//    linestream>>interval>>ask>>bid;
 //   cout<<idx++<<"->"<<name<<" "<<ti<<" "<<atof(ask.c_str())<<endl;
    m_samples << atof(ask.c_str())/10000;
    m_samplesChanged = true;
    update();
    }
}


void Graph::removeFirstSample()
{
    m_samples.removeFirst();
    m_samplesChanged = true;
    update();
}

void Graph::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    m_geometryChanged = true;
    update();
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}


class GraphNode : public QSGNode
{
public:
//    NoisyNode *background;
 //   GridNode *grid;
    LineNode *line;
//    LineNode *shadow;
};


QSGNode *Graph::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    GraphNode *n= static_cast<GraphNode *>(oldNode);

    QRectF rect = boundingRect();

    if (rect.isEmpty()) {
        delete n;
        return 0;
    }

    if (!n) {
        n = new GraphNode();

 //       n->background = new NoisyNode(window());
 //       n->grid = new GridNode();
        n->line = new LineNode(10, 0.5, QColor("steelblue"));
 //       n->shadow = new LineNode(20, 0.2, QColor::fromRgbF(0.2, 0.2, 0.2, 0.4));

 //       n->appendChildNode(n->background);
 //       n->appendChildNode(n->grid);
 //       n->appendChildNode(n->shadow);
        n->appendChildNode(n->line);
    }
/*
    if (m_geometryChanged) {
        n->background->setRect(rect);
        n->grid->setRect(rect);
    }
*/
    if (m_geometryChanged || m_samplesChanged) {
        n->line->updateGeometry(rect, m_samples);
        // We don't need to calculate the geometry twice, so just steal it from the other one...
  //      n->shadow->setGeometry(n->line->geometry());
    }

    m_geometryChanged = false;
    m_samplesChanged = false;

    return n;
}
