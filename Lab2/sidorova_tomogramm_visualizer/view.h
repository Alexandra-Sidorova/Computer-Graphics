#ifndef _VIEW_H_
#define _VIEW_H_

#include <QtOpengl>
#include <QGLWidget>
#include <QTimer>
#include <qimage.h>
#include <algorithm>

#include "data.h"

class View : public QGLWidget
{
	Q_OBJECT

private:
	Data data;
	int numberLayer;

	static const int MAX_WIN_SIZE = 1000;
	static const int MIN_WIN_SIZE = 250;

	int visualization_state = 0;
	static const int VISUALIZATION_QUADS = 0;
	static const int VISUALIZATION_QUADSTRIP = 1;
	static const int VISUALIZATION_TEXTURE = 2;

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
	void VisualizationQuadStrip();
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