#include "linenode.h"

#include <QtGui/QColor>

#include <QtQuick/QSGSimpleMaterial>

struct LineMaterial
{
    QColor color;
    float spread;
    float size;
};

class LineShader : public QSGSimpleMaterialShader<LineMaterial>
{
    QSG_DECLARE_SIMPLE_SHADER(LineShader, LineMaterial)

public:
    LineShader() {
        setShaderSourceFile(QOpenGLShader::Vertex, "/root/Desktop/stock/content/shaders/line.vsh");
        setShaderSourceFile(QOpenGLShader::Fragment, "/root/Desktop/stock/content/shaders/line.fsh");
    }

    QList<QByteArray> attributes() const {  return QList<QByteArray>() << "pos" << "t"; }

    void updateState(const LineMaterial *m, const LineMaterial *) {
        program()->setUniformValue(id_color, m->color);
        program()->setUniformValue(id_spread, m->spread);
        program()->setUniformValue(id_size, m->size);
    }

    void resolveUniforms() {
        id_spread = program()->uniformLocation("spread");
        id_size = program()->uniformLocation("size");
        id_color = program()->uniformLocation("color");
    }

private:
    int id_color;
    int id_spread;
    int id_size;
};

struct LineVertex {
    float x;
    float y;
    float t;
    inline void set(float xx, float yy, float tt) { x = xx; y = yy; t = tt; }
};

static const QSGGeometry::AttributeSet &attributes()
{
    static QSGGeometry::Attribute attr[] = {
        QSGGeometry::Attribute::create(0, 2, GL_FLOAT, true),
        QSGGeometry::Attribute::create(1, 1, GL_FLOAT)
    };
    static QSGGeometry::AttributeSet set = { 2, 3 * sizeof(float), attr };
    return set;
}

LineNode::LineNode(float size, float spread, const QColor &color)
    : m_geometry(attributes(), 0)
{
    setGeometry(&m_geometry);
    m_geometry.setDrawingMode(GL_TRIANGLE_STRIP);

    QSGSimpleMaterial<LineMaterial> *m = LineShader::createMaterial();
    m->state()->color = color;
    m->state()->size = size;
    m->state()->spread = spread;
    m->setFlag(QSGMaterial::Blending);
    setMaterial(m);
    setFlag(OwnsMaterial);
}

/*
 * Assumes that samples have values in the range of 0 to 1 and scales them to
 * the height of bounds. The samples are stretched out horizontally along the
 * width of the bounds.
 *
 * The position of each pair of points is identical, but we use the third value
 * "t" to shift the point up or down and to add antialiasing.
 */
void LineNode::updateGeometry(const QRectF &bounds, const QList<qreal> &samples)
{
    m_geometry.allocate(samples.size() * 2);

    float x = bounds.x();
    float y = bounds.y();
    float w = bounds.width();
    float h = bounds.height();

    float dx = w / (samples.size() - 1);

    LineVertex *v = (LineVertex *) m_geometry.vertexData();
    for (int i=0; i<samples.size(); ++i) {
        v[i*2+0].set(x + dx * i, y + samples.at(i) * h, 0);
        v[i*2+1].set(x + dx * i, y + samples.at(i) * h, 1);
    }

    markDirty(QSGNode::DirtyGeometry);
}

