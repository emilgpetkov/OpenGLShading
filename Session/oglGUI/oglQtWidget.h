#ifndef OGLMAINWIDGET_H
#define OGLMAINWIDGET_H

#include "oglGUI_Global.h"

#include <QWidget>

#include "oglQtWindow.h"
#include "oglpropertiesdlg.h"

// Used as a Main Widget
class OPENGLSHADINGWINDOWSHARED_EXPORT OglMainWidget : public QWidget
{
	Q_OBJECT // Need to "work" as a QObject

public:
	// Public method
	explicit OglMainWidget(QWidget *pParent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags()); // C-tor
	virtual ~OglMainWidget(); // Virtual d-tor, we would need to free the allocated memory in this child-class

public slots:
	// Slots
	void handleKeyPressed(QKeyEvent *pEvent); // Handler for the key-event from the OpenGL-window
	void renderGL(); // Render the OpenGL-window's content

protected:
	// Reimplemented protected virtual methods. Their functionality is self-explaining
	virtual void showEvent(QShowEvent *pEvent);
	virtual void resizeEvent(QResizeEvent *pEvent);

private:
	// Private data
	QWidget *m_pWindowContainer; // Container for the OpenGL child-window
	OglShadingWindow *m_pChildGLWindow; // OpenGL child-window
	OglPropertiesDlg *m_pPropertiesDlg; // Properties' Dialog for user-interaction
};

#endif // OGLMAINWIDGET_H
