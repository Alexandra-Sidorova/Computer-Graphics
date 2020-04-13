#include "view.h"

View::View(QGLWidget* parent) : QGLWidget(parent)
{
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

QColor View::TransferFunction(short _v)
{
	int c = (_v - data.GetMin()) * 255 / (data.GetMax() - data.GetMin());
	return QColor(c, c, c);
};

void View::ChangeLayer()
{
	if (visualization_state == VISUALIZATION_TEXTURE)
	{
		genTextureImage();
		Load2DTexture();
	}
};

void View::genTextureImage()
{
	textureImage = QImage(data.GetWidth(), data.GetHeight(), QImage::Format_RGB32);

	int w = data.GetWidth();
	int h = data.GetHeight();

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			QColor c = TransferFunction(data[numberLayer * w * h + y * w + x]);
			textureImage.setPixelColor(x, y, c);
		}
};

void View::Load2DTexture()
{
	glBindTexture(GL_TEXTURE_2D, VBOtexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(),
		0, GL_BGRA, GL_UNSIGNED_BYTE, textureImage.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
};

void View::VisualizationQuads()
{
	QColor c;

	int w = data.GetWidth();
	int h = data.GetHeight();

	for (int y = 0; y < (h - 1); y++)
		for (int x = 0; x < (w - 1); x++)
		{
			glBegin(GL_QUADS);

			c = TransferFunction(data[numberLayer * w * h + y * w + x]);
			qglColor(c);
			glVertex2i(x, y);

			c = TransferFunction(data[numberLayer * w * h + (y + 1) * w + x]);
			qglColor(c);
			glVertex2i(x, (y + 1));

			c = TransferFunction(data[numberLayer * w * h + (y + 1) * w + (x + 1)]);
			qglColor(c);
			glVertex2i((x + 1), (y + 1));

			c = TransferFunction(data[numberLayer * w * h + y * w + (x + 1)]);
			qglColor(c);
			glVertex2i((x + 1), y);

			glEnd();
		}
};

void View::VisualizationQuadStrip()
{
	QColor c;

	int w = data.GetWidth();
	int h = data.GetHeight();

	for (int y = 0; y < (h - 1); y++)
		for (int x = 0; x < (w - 1); x++)
		{
			glBegin(GL_QUADS);

			c = TransferFunction(data[numberLayer * w * h + y * w + x]);
			qglColor(c);
			glVertex2i(x, y);

			c = TransferFunction(data[numberLayer * w * h + (y + 1) * w + x]);
			qglColor(c);
			glVertex2i(x, (y + 1));

			c = TransferFunction(data[numberLayer * w * h + (y + 1) * w + (x + 1)]);
			qglColor(c);
			glVertex2i((x + 1), (y + 1));

			c = TransferFunction(data[numberLayer * w * h + y * w + (x + 1)]);
			qglColor(c);
			glVertex2i((x + 1), y);

			glEnd();
		}
};

void View::VisualizationTexture()
{
	glBegin(GL_QUADS);
	qglColor(QColor(255, 255, 255));

	glTexCoord2f(0, 0);
	glVertex2i(0, 0);

	glTexCoord2f(0, 1);
	glVertex2i(0, data.GetHeight());

	glTexCoord2f(1, 1);
	glVertex2i(data.GetWidth(), data.GetHeight());

	glTexCoord2f(1, 0);
	glVertex2i(data.GetWidth(), 0);

	glEnd();
};

void View::Up()
{
	if ((numberLayer + 1 < data.GetDepth()))
		numberLayer++;

	updateGL();
};

void View::Up10()
{
	if ((numberLayer + 10 < data.GetDepth()))
		numberLayer += 10;

	updateGL();
};

void View::Down()
{
	if ((numberLayer - 1 >= 0))
		numberLayer--;

	updateGL();
};

void View::Down10()
{
	if ((numberLayer - 10 >= 0))
		numberLayer -= 10;

	updateGL();
};

void View::initializeGL()
{
	qglClearColor(Qt::white);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGenTextures(1, &VBOtexture);
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
		VisualizationTexture();
		break;
	}
};

void View::keyPressEvent(QKeyEvent* _event)
{
	if (_event->nativeVirtualKey() == Qt::Key_W)
	{
		Up();
		ChangeLayer();
	}
	else if (_event->nativeVirtualKey() == Qt::Key_S)
	{
		Down();
		ChangeLayer();
	}
	else if (_event->nativeVirtualKey() == Qt::Key_D)
	{
		visualization_state = (visualization_state + 1) % 3;
		if (visualization_state == VISUALIZATION_TEXTURE)
		{
			glEnable(GL_TEXTURE_2D);
			genTextureImage();
			Load2DTexture();
		}
		else
			glDisable(GL_TEXTURE_2D);
	}

	update();
};