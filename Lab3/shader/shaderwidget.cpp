#include "ShaderWidget.h"

#include <QtOpenGL\qglfunctions.h>
#include <qmessagebox.h>

ShaderWidget::ShaderWidget(QWidget* parent)
{
    vertData = new GLfloat[12]{ -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f };
};

ShaderWidget::~ShaderWidget()
{
    delete[] vertData;
};

void ShaderWidget::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    QOpenGLShader vShader(QOpenGLShader::Vertex);
    vShader.compileSourceFile("raytracing.vert");

    QOpenGLShader fShader(QOpenGLShader::Fragment);
    fShader.compileSourceFile("raytracing.frag");

    mProgram.addShader(&vShader);
    mProgram.addShader(&fShader);

    if (!mProgram.link()) {
        qWarning("Error link programm shader");
        return;
    }

    vertDataLocation = mProgram.attributeLocation("vertex");

    qDebug() << QString("Log programm");
    qDebug() << mProgram.log();

    if (!mProgram.bind())
    {
        QMessageBox::warning(this, "Warning", "Error link programm shader!");
        return;
    }

    mProgram.setUniformValue("camera.position", QVector3D(0.0, 0.0, -10));
    mProgram.setUniformValue("camera.view", QVector3D(0.0, 0.0, 1.0));
    mProgram.setUniformValue("camera.up", QVector3D(0.0, 1.0, 0.0));
    mProgram.setUniformValue("camera.side", QVector3D(1.0, 0.0, 0.0));

    mProgram.setUniformValue("spherein[0].center", QVector3D(0.0, 0.0, 0.0));
    mProgram.setUniformValue("spherein[0].color", QVector3D(1.0, 0.0, 1.0));
    mProgram.setUniformValue("spherein[0].radius", 1.0f);
    mProgram.setUniformValue("spherein[1].center", QVector3D(3.0, 3.0, 0.0));
    mProgram.setUniformValue("spherein[1].color", QVector3D(0.0, 0.0, 1.0));
    mProgram.setUniformValue("spherein[1].radius", 2.0f);

    // left
    mProgram.setUniformValue("trianglein[0].v1", QVector3D(-5.0, -5.0, -5.0));
    mProgram.setUniformValue("trianglein[0].v2", QVector3D(-5.0, 5.0, 5.0));
    mProgram.setUniformValue("trianglein[0].v3", QVector3D(-5.0, 5.0, -5.0));
    mProgram.setUniformValue("trianglein[0].color", QVector3D(1.0, 1.0, 0.0));
    mProgram.setUniformValue("trianglein[1].v1", QVector3D(-5.0, -5.0, -5.0));
    mProgram.setUniformValue("trianglein[1].v2", QVector3D(-5.0, 5.0, 5.0));
    mProgram.setUniformValue("trianglein[1].v3", QVector3D(-5.0, -5.0, 5.0));
    mProgram.setUniformValue("trianglein[1].color", QVector3D(1.0, 1.0, 0.0));

    // right
    mProgram.setUniformValue("trianglein[2].v1", QVector3D(5.0, -5.0, -5.0));
    mProgram.setUniformValue("trianglein[2].v2", QVector3D(5.0, 5.0, 5.0));
    mProgram.setUniformValue("trianglein[2].v3", QVector3D(5.0, 5.0, -5.0));
    mProgram.setUniformValue("trianglein[2].color", QVector3D(1.0, 1.0, 0.0));
    mProgram.setUniformValue("trianglein[3].v1", QVector3D(5.0, -5.0, -5.0));
    mProgram.setUniformValue("trianglein[3].v2", QVector3D(5.0, 5.0, 5.0));
    mProgram.setUniformValue("trianglein[3].v3", QVector3D(5.0, -5.0, 5.0));
    mProgram.setUniformValue("trianglein[3].color", QVector3D(1.0, 1.0, 0.0));

    // front
    mProgram.setUniformValue("trianglein[4].v1", QVector3D(-5.0, -5.0, 5.0));
    mProgram.setUniformValue("trianglein[4].v2", QVector3D(5.0, -5.0, 5.0));
    mProgram.setUniformValue("trianglein[4].v3", QVector3D(-5.0, 5.0, 5.0));
    mProgram.setUniformValue("trianglein[4].color", QVector3D(1.0, 1.0, 0.0));
    mProgram.setUniformValue("trianglein[5].v1", QVector3D(5.0, 5.0, 5.0));
    mProgram.setUniformValue("trianglein[5].v2", QVector3D(-5.0, 5.0, 5.0));
    mProgram.setUniformValue("trianglein[5].v3", QVector3D(5.0, -5.0, 5.0));
    mProgram.setUniformValue("trianglein[5].color", QVector3D(1.0, 1.0, 0.0));

    // up
    mProgram.setUniformValue("trianglein[6].v1", QVector3D(-5.0, 5.0, -5.0));
    mProgram.setUniformValue("trianglein[6].v2", QVector3D(-5.0, 5.0, 5.0));
    mProgram.setUniformValue("trianglein[6].v3", QVector3D(5.0, 5.0, -5.0));
    mProgram.setUniformValue("trianglein[6].color", QVector3D(0.0, 1.0, 0.0));
    mProgram.setUniformValue("trianglein[7].v1", QVector3D(5.0, 5.0, 5.0));
    mProgram.setUniformValue("trianglein[7].v2", QVector3D(-5.0, 5.0, 5.0));
    mProgram.setUniformValue("trianglein[7].v3", QVector3D(5.0, 5.0, -5.0));
    mProgram.setUniformValue("trianglein[7].color", QVector3D(0.0, 1.0, 0.0));

    // down
    mProgram.setUniformValue("trianglein[8].v1", QVector3D(-5.0, -5.0, -5.0));
    mProgram.setUniformValue("trianglein[8].v2", QVector3D(-5.0, -5.0, 5.0));
    mProgram.setUniformValue("trianglein[8].v3", QVector3D(5.0, -5.0, -5.0));
    mProgram.setUniformValue("trianglein[8].color", QVector3D(0.0, 1.0, 0.0));
    mProgram.setUniformValue("trianglein[9].v1", QVector3D(5.0, -5.0, 5.0));
    mProgram.setUniformValue("trianglein[9].v2", QVector3D(-5.0, -5.0, 5.0));
    mProgram.setUniformValue("trianglein[9].v3", QVector3D(5.0, -5.0, -5.0));
    mProgram.setUniformValue("trianglein[9].color", QVector3D(0.0, 1.0, 0.0));

    mProgram.setUniformValue("scale", QVector2D(width(), height()));

    mProgram.release();
};

void ShaderWidget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
    if (!mProgram.bind())
        qWarning("Error bind program shader");
    mProgram.setUniformValue("scale", QVector2D(width(), height()));
    mProgram.release();
};

void ShaderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (!mProgram.bind())
        return;

    mProgram.enableAttributeArray(vertDataLocation);
    mProgram.setAttributeArray(vertDataLocation, vertData, 3);

    glDrawArrays(GL_QUADS, 0, 4);

    mProgram.disableAttributeArray(vertDataLocation);

    mProgram.release();
};