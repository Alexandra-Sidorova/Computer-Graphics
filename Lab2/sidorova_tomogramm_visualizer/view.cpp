#include "view.h"

View::View(QGLWidget* parent) : QGLWidget(parent)
{
	visualization_state = VISUALIZATION_QUADS;
	numberLayer = 0;
	resizeGL(MIN_WIN_SIZE, MIN_WIN_SIZE);
	setFocus();
};
//------------------------------------

int Clamp(int _v, int _min, int _max)
{
	if (_v > _max)
		return _max;
	else if (_v < _min)
		return _min;
	return _v;
};
//-----------------------------------

void View::LoadData(QString _path)
{
	data.ReadBIN(_path);
	resize(Clamp(data.GetWidth(), MIN_WIN_SIZE, MAX_WIN_SIZE),
		Clamp(data.GetHeight(), MIN_WIN_SIZE, MAX_WIN_SIZE));
};
//-----------------------------------

//void View::ChangeLayer()
//{
//	if (visualization_state == VISUALIZATION_TEXTURE)
//	{
//		genTextureImage();
//		Load2DTexture();
//	}
//};

QColor View::TransferFunction(short _v)
{
	int c = (_v - data.GetMin()) * 255 / (data.GetMax() - data.GetMin());
	return QColor(c, c, c);
};

//void View::textureImage()
//{
//
//};

//void View::Load2DTexture()
//{
//
//};

void View::VisualizationQuads()
{
	QColor c;

	for (int y = 0; y < (data.GetHeight() - 1); y++)
		for (int x = 0; x < (data.GetWidth() - 1); x++)
		{
			glBegin(GL_QUADS);

			c = TransferFunction(data.GetData(x, y, numberLayer));
			qglColor(c);
			glVertex2i(x, y);

			c = TransferFunction(data.GetData(x, y + 1, numberLayer));
			qglColor(c);
			glVertex2i(x, y + 1);

			c = TransferFunction(data.GetData(x + 1, y + 1, numberLayer));
			qglColor(c);
			glVertex2i(x + 1, y + 1);

			c = TransferFunction(data.GetData(x + 1, y, numberLayer));
			qglColor(c);
			glVertex2i(x + 1, y);

			glEnd();
		}
};

//void View::VisualizationQuadStrip()
//{
//
//};

//void View::VisualizationTexture()
//{
//
//};

void View::Up()
{
	if ((numberLayer + 1 < data.GetDepth()))
		numberLayer++;

	qDebug() << numberLayer + 1;
	updateGL();
};

void View::Up10()
{
	if ((numberLayer + 10 < data.GetDepth()))
		numberLayer += 10;

	qDebug() << numberLayer + 10;
	updateGL();
};

void View::Down()
{
	if ((numberLayer - 1 >= 0))
		numberLayer--;

	qDebug() << numberLayer - 1;
	updateGL();
};

void View::Down10()
{
	if ((numberLayer - 10 >= 0))
		numberLayer -= 10;

	qDebug() << numberLayer - 10;
	updateGL();
};

void View::initializeGL()
{
	qglClearColor(Qt::white);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glGenTextures(1, &VBOtexture);
};

void View::resizeGL(int _w, int _h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, data.GetWidth() - 1, 0.0f, data.GetHeight() - 1, -1.0f, 1.0f);
	glViewport(0, 0, _w, _h);
	update();
};

void View::paintGL()
{
	qDebug() << "repaint" << visualization_state;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (visualization_state)
	{
	case VISUALIZATION_QUADS:
		VisualizationQuads();
		break;
	case VISUALIZATION_QUADSTRIP:
		//VisualizationQuadStrip();
		break;
	case VISUALIZATION_TEXTURE:
		//VizualizationTexture();
		break;
	}
};

void View::keyPressEvent(QKeyEvent* _event)
{
	if (_event->nativeVirtualKey() == Qt::Key_U)
	{
		Up();
		//changeLayer();
	}
	else if (_event->nativeVirtualKey() == Qt::Key_D)
	{
		Down();
		//changeLayer();
	}
	else if (_event->nativeVirtualKey() == Qt::Key_N)
	{
		// Переключиться на следующий тип рендеринга
	}
	// Подняться на слой выше
	update();
};
//---------------------------------------------------------------



