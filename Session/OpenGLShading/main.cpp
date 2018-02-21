#include "OpenGLShading.h"

#include "oglQtWidget.h"

#include <QApplication>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	OglMainWidget wd;
	wd.resize(640, 480);
	wd.show();

	return app.exec();
}

