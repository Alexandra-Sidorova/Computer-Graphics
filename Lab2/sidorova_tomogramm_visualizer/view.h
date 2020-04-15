#ifndef _VIEW_H_
#define _VIEW_H_

#include <QtOpengl>
#include <QGLWidget>
#include <QTimer>
#include <qimage.h>
#include <algorithm>

#include "data.h"

enum Visualization { VISUALIZATION_QUADS, VISUALIZATION_QUADSTRIP, VISUALIZATION_TEXTURE };

enum Axis {X, Y, Z};

class View : public QGLWidget
{
	Q_OBJECT

private:
	Data data;
	int numberLayer;

	static const int MAX_WIN_SIZE = 1000;
	static const int MIN_WIN_SIZE = 250;

	Visualization visualization_state;
	Axis axis;

	QImage textureImage;
	GLuint VBOtexture;

	short min, max;

public:
	View(QGLWidget *parent = Q_NULLPTR);
	~View() {};

	void LoadData(QString _path);

private:
	QString DialogFile();
	void DialogMinMax();

	QColor TransferFunction(short _v);

	void ChangeLayer();
	void genTextureImage();
	void Load2DTexture();

	void VisualizationQuads();
	void VisualizationQuadStrip();
	void VisualizationTexture();

	void Up();
	void Down();

protected:
	void initializeGL() override;
	void resizeGL(int _w, int _h) override;
	void paintGL() override;

public slots:
	void keyPressEvent(QKeyEvent* _event) override;
};

#endif