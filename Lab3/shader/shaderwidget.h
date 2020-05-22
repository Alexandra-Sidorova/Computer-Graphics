#pragma once
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <iostream>

class ShaderWidget : public QOpenGLWidget
{
private:
	QOpenGLShaderProgram mProgram;
	GLfloat* vertData;
	int vertDataLocation;

protected:
	void initializeGL() override;
	void resizeGL(int nWidth, int nHeight) override;
	void paintGL() override;

public:
	ShaderWidget(QWidget* parent = 0);
	~ShaderWidget();
};