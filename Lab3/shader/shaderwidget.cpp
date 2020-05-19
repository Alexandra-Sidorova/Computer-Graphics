#include "shaderwidget.h"

#include <qmessagebox.h>

ShaderWidget::ShaderWidget(QGLWidget* parent) : QGLWidget(parent)
{
	vertData = new GLfloat[12];

	vertData[0] = -1.0; vertData[1] = -1.0; vertData[2] = 0.0;
	vertData[3] = 1.0;  vertData[4] = -1.0; vertData[5] = 0.0;
	vertData[6] = 1.0;  vertData[7] = 1.0;  vertData[8] = 0.0;
	vertData[9] = -1.0; vertData[10] = 1.0;  vertData[11] = 0.0;
};

ShaderWidget::~ShaderWidget()
{
	delete[] vertData;
};
//---------------------------------------------------------

void ShaderWidget::initializeGL()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	QOpenGLShader vShader(QOpenGLShader::Vertex);
	vShader.compileSourceFile("raytracing.vert");

	QOpenGLShader fShader(QOpenGLShader::Fragment);
	fShader.compileSourceFile("raytracing.frag");

	mProgram.addShader(&vShader);
	mProgram.addShader(&fShader);

	if (!mProgram.link())
	{
		QMessageBox::warning(this, "Warning", "Error link programm shader!");
		return;
	}
	
	vertDataLocation = mProgram.attributeLocation("vertex");

	if (!mProgram.bind())
		return;

	mProgram.setUniformValue("camera.position", QVector3D(0.0, 0.0, -10));
	mProgram.setUniformValue("camera.view", QVector3D(0.0, 0.0, 1.0));
	mProgram.setUniformValue("camera.up", QVector3D(0.0, 1.0, 0.0));
	mProgram.setUniformValue("camera.side", QVector3D(1.0, 0.0, 0.0));
	mProgram.setUniformValue("camera.scale", QVector2D(width(), height()));
	
	mProgram.release();
};

void ShaderWidget::resizeGL(int nWidth, int nHeight)
{
	glViewport(0, 0, nWidth, nHeight);
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