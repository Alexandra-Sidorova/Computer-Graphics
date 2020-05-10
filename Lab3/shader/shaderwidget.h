#pragma once

#include <QtWidgets/QWidget>
#include <QtOpengl>
#include <QGLWidget>

class ShaderWidget : public QGLWidget
{
	Q_OBJECT

private:
	QOpenGLShaderProgram mProgram;

	GLfloat* vertData;
	int vertDataLocation;

public:
	ShaderWidget(QGLWidget *parent = Q_NULLPTR);
	~ShaderWidget();

protected:
	void initializeGL() override;
	void resizeGL(int nWidth, int nHeight) override;
	void paintGL() override;
};
