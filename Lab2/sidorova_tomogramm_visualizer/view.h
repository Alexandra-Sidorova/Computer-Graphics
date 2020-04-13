#ifndef _VIEW_H_
#define _VIEW_H_

#include <QtOpengl>
#include <QGLWidget>
#include <QTimer>
#include <qimage.h>
#include <algorithm>

#include "data.h"

enum VisualState { VISUALIZATION_QUADS, VISUALIZATION_QUADSTRIP, VISUALIZATION_TEXTURE };

class View : public QGLWidget
{
	Q_OBJECT

private:
	Data data;
	VisualState visualization_state = VISUALIZATION_QUADS;
	int numberLayer;

	static const int MAX_WIN_SIZE = 1000;
	static const int MIN_WIN_SIZE = 250;

	QImage textureImage;
	GLuint VBOtexture;

public:
	View(QGLWidget *parent = Q_NULLPTR);
	~View() {};

	void LoadData(QString _path);

private:
	QColor TransferFunction(short _v);

	void ChangeLayer();
	void genTextureImage();
	void Load2DTexture();

	void VisualizationQuads();
	//void VisualizationQuadStrip();
	void VisualizationTexture();

	void Up();
	void Up10();
	void Down();
	void Down10();

protected:
	void initializeGL() override;
	void resizeGL(int _w, int _h) override;
	void paintGL() override;

public slots:
	void keyPressEvent(QKeyEvent* _event) override;
};

#endif