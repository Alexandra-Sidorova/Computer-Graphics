#include "ShaderWidget.h"
#include <QtOpenGL\qglfunctions.h>

ShaderWidget::ShaderWidget(QWidget* parent) {
	vertData = new GLfloat[12]{ -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f };
}

ShaderWidget::~ShaderWidget() {
	delete [] vertData;
}

void ShaderWidget::initializeGL() {
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
		qWarning("Error bind programm shader");

    mProgram.setUniformValue("camera.position", QVector3D(0.0, 0.0, -10));
    mProgram.setUniformValue("camera.view", QVector3D(0.0, 0.0, 1.0));
    mProgram.setUniformValue("camera.up", QVector3D(0.0, 1.0, 0.0));
    mProgram.setUniformValue("camera.side", QVector3D(1.0, 0.0, 0.0));
    mProgram.setUniformValue("spherein.center", QVector3D(0.0, 0.0, 0.0));
    mProgram.setUniformValue("spherein.color", QVector3D(1.0, 1.0, 0.0));
    mProgram.setUniformValue("spherein.radius", 1.0f);

    mProgram.setUniformValue("scale", QVector2D(width(), height()));

    mProgram.release();
}

void ShaderWidget::resizeGL(int nWidth, int nHeight) {
	glViewport(0, 0, nWidth, nHeight);
	if (!mProgram.bind())
		qWarning("Error bind program shader");
    mProgram.setUniformValue("scale", QVector2D(width(), height()));
    mProgram.release();
}

void ShaderWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (!mProgram.bind())
		return;

    mProgram.enableAttributeArray(vertDataLocation);
    mProgram.setAttributeArray(vertDataLocation, vertData, 3);

	glDrawArrays(GL_QUADS, 0, 4);

    mProgram.disableAttributeArray(vertDataLocation);

    mProgram.release();
}