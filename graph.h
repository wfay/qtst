#ifndef GRAPH_H
#define GRAPH_H

#include <QQuickItem>
#include <iostream>
#include <fstream>
using namespace std;
class Graph : public QQuickItem
{
    Q_OBJECT
public:
    Graph();
    ifstream datafile;
protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

public slots:
    void appendSample(QString id);
    void removeFirstSample();

private:
    QList<qreal> m_samples;

    bool m_samplesChanged;
    bool m_geometryChanged;
};
#endif // GRAPH_H

