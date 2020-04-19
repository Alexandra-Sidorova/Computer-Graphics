#include "view.h"
#include "dialogminmax.h"

#include <qfiledialog>

View::View(QGLWidget* parent) : QGLWidget(parent)
{
	numberLayer = 0;
	visualization_state = VISUALIZATION_QUADS;
	axis = Z;
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

	width = data.GetWidth();
	height = data.GetHeight();
	depth = data.GetDepth();
	min = data.GetMin();
	max = data.GetMax();

	resize(Clamp(width, MIN_WIN_SIZE, MAX_WIN_SIZE),
		Clamp(height, MIN_WIN_SIZE, MAX_WIN_SIZE));

	update();
};
//-----------------------------------

QString View::DialogFile()
{
	QString path = QFileDialog::getOpenFileName(this, "Choose binary file", "", "*.bin");
	return path;
};

QColor View::TransferFunction(short _v)
{
	int c = (_v - min) * 255 / (max - min);
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
	switch (axis)
	{
	case Z:
		textureImage = QImage(width, height, QImage::Format_RGB32);

		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
			{
				QColor c = TransferFunction(data[numberLayer * width * height + y * width + x]);
				textureImage.setPixelColor(x, y, c);
			}
		break;
	case Y:
		textureImage = QImage(width, depth, QImage::Format_RGB32);

		for (int z = 0; z < depth; z++)
			for (int x = 0; x < width; x++)
			{
				QColor c = TransferFunction(data[z * width * height + numberLayer * width + x]);
				textureImage.setPixelColor(x, z, c);
			}
		break;
	case X:
		textureImage = QImage(height, depth, QImage::Format_RGB32);

		for (int z = 0; z < depth; z++)
			for (int y = 0; y < height; y++)
			{
				QColor c = TransferFunction(data[z * width * height + y * width + numberLayer]);
				textureImage.setPixelColor(y, z, c);
			}
		break;
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

	for (int y = 0; y < (height - 1); y++)
		for (int x = 0; x < (width - 1); x++)
		{
			glBegin(GL_QUADS);

			c = TransferFunction(data[numberLayer * width * height + y * width + x]);
			qglColor(c);
			glVertex2i(x, y);

			c = TransferFunction(data[numberLayer * width * height + (y + 1) * width + x]);
			qglColor(c);
			glVertex2i(x, (y + 1));

			c = TransferFunction(data[numberLayer * width * height + (y + 1) * width + (x + 1)]);
			qglColor(c);
			glVertex2i((x + 1), (y + 1));

			c = TransferFunction(data[numberLayer * width * height + y * width + (x + 1)]);
			qglColor(c);
			glVertex2i((x + 1), y);

			glEnd();
		}
};

void View::VisualizationQuadStrip()
{
	QColor c;

	for (int y = 0; y < (height - 1); y++)
	{
		glBegin(GL_QUAD_STRIP);

		for (int x = 0; x < width; x++)
		{
			c = TransferFunction(data[numberLayer * width * height + y * width + x]);
			qglColor(c);
			glVertex2i(x, y);

			c = TransferFunction(data[numberLayer * width * height + (y + 1) * width + x]);
			qglColor(c);
			glVertex2i(x, (y + 1));
		}

		glEnd();
	}
};

void View::VisualizationTexture()
{
	glBegin(GL_QUADS);
	qglColor(QColor(255, 255, 255));

	glTexCoord2f(0, 0);
	glVertex2i(0, 0);

	switch (axis)
	{
	case Z:
		glTexCoord2f(0, 1);
		glVertex2i(0, height);

		glTexCoord2f(1, 1);
		glVertex2i(width, height);

		glTexCoord2f(1, 0);
		glVertex2i(width, 0);
		break;
	case Y:
		glTexCoord2f(0, 1);
		glVertex2i(0, depth);

		glTexCoord2f(1, 1);
		glVertex2i(width, depth);

		glTexCoord2f(1, 0);
		glVertex2i(width, 0);
		break;
	case X:
		glTexCoord2f(0, 1);
		glVertex2i(0, depth);

		glTexCoord2f(1, 1);
		glVertex2i(height, depth);

		glTexCoord2f(1, 0);
		glVertex2i(height, 0);
		break;
	}

	glEnd();
};

void View::Up()
{
	switch (axis)
	{
	case Z:
		if ((numberLayer + 1 < depth))
			numberLayer++;
		break;
	case Y:
		if ((numberLayer + 1 < height))
			numberLayer++;
		break;
	case X:
		if ((numberLayer + 1 < width))
			numberLayer++;
		break;
	}

	updateGL();
};

void View::Down()
{
	if ((numberLayer - 1 >= 0))
		numberLayer--;

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

	switch (axis)
	{
	case Z:
		glOrtho(0.0f, width - 1, 0.0f, height - 1, -1.0f, 1.0f);
		break;
	case Y:
		glOrtho(0.0f, width - 1, 0.0f, depth - 1, -1.0f, 1.0f);
		break;
	case X:
		glOrtho(0.0f, height - 1, 0.0f, depth - 1, -1.0f, 1.0f);
		break;
	}

	glViewport(0, 0, _w, _h);
	update();
};

void View::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (visualization_state)
	{
	case VISUALIZATION_QUADS:
		this->setWindowTitle("Visualization Quads");
		VisualizationQuads();
		break;
	case VISUALIZATION_QUADSTRIP:
		this->setWindowTitle("Visualization QuadStrip");
		VisualizationQuadStrip();
		break;
	case VISUALIZATION_TEXTURE:
		this->setWindowTitle("Visualization Texture");
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
		visualization_state = static_cast<Visualization>((visualization_state + 1) % 3);
		
		if (visualization_state == VISUALIZATION_TEXTURE)
		{
			glEnable(GL_TEXTURE_2D);
			genTextureImage();
			Load2DTexture();
		}
		else
			glDisable(GL_TEXTURE_2D);
	}
	else if (_event->nativeVirtualKey() == Qt::Key_A)
	{
		visualization_state = static_cast<Visualization>((visualization_state + 2) % 3);

		if (visualization_state == VISUALIZATION_TEXTURE)
		{
			glEnable(GL_TEXTURE_2D);
			genTextureImage();
			Load2DTexture();
		}
		else
			glDisable(GL_TEXTURE_2D);
	}
	else if (_event->nativeVirtualKey() == Qt::Key_R)
	{
		axis = static_cast<Axis>((axis + 2) % 3);
		numberLayer = 0;

		switch (axis)
		{
		case Z:
			resize(Clamp(width, MIN_WIN_SIZE, MAX_WIN_SIZE),
				Clamp(height, MIN_WIN_SIZE, MAX_WIN_SIZE));
			break;
		case Y:
			resize(Clamp(width, MIN_WIN_SIZE, MAX_WIN_SIZE),
				Clamp(depth, MIN_WIN_SIZE, MAX_WIN_SIZE));
			break;
		case X:
			resize(Clamp(height, MIN_WIN_SIZE, MAX_WIN_SIZE),
				Clamp(depth, MIN_WIN_SIZE, MAX_WIN_SIZE));
			break;
		}

		if (visualization_state == VISUALIZATION_TEXTURE)
		{
			genTextureImage();
			Load2DTexture();
		}
	}
	else if (_event->nativeVirtualKey() == Qt::Key_F)
	{
		numberLayer = 0;
		ChangeLayer();
		QString path = DialogFile();
		LoadData(path);
	}
	else if(_event->nativeVirtualKey() == Qt::Key_T)
	{
		Dialog* dialog = new Dialog;
		dialog->exec();

		if (dialog->Max() > 0)
			max = dialog->Max();
		if (dialog->Min() > 0)
			min = dialog->Min();

		if (visualization_state == VISUALIZATION_TEXTURE)
		{
			genTextureImage();
			Load2DTexture();
		}

		delete dialog;
	}

	update();
};