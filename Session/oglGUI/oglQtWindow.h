#ifndef OPENGLSHADINGWINDOW_H
#define OPENGLSHADINGWINDOW_H

#include "oglGUI_Global.h"

#include <QWidget>
#include <QWindow>
#include <QOpenGLFunctions>
#include <QPainter>
#include <QExposeEvent>
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>

#include "oglrenderer.h"
#include "oglSphere.h"

// OpenGL Surface window-class
class OPENGLSHADINGWINDOWSHARED_EXPORT OglShadingWindow : public QWindow, protected QOpenGLFunctions
{
	Q_OBJECT // Need to "work" as a QObject

public:
	// Public methods
	explicit OglShadingWindow(QWindow *parent); // C-tor
	virtual ~OglShadingWindow(); // Virtual d-tor, we would need to free the allocated memory in this child-class

	// Reimplemented public virtual methods
	virtual void render(QPainter *pPainter); // Rendering method
	virtual void render(); // Rendering method
	virtual void initialize(); // Need to initialize the object of this type

	void setAnimation(bool bAnimating);

	// Set the data used for the current rendered geometry
	void setRenderData(const vec3d &ptSphereCenter, const double &dSphereRadius,
					   const unsigned int &unSmoothU, const unsigned int &unSmoothV, const unsigned int &unLOD);

public slots:
	// Slots
	void renderLater();
	void renderNow();

signals:
	// Need to handle the key event
	void signalKeyPressed(QKeyEvent *pEvent);

protected:
	// Reimplemented protected virtual methods. Their functionality is self-explaining
	virtual bool event(QEvent *pEvent);
	virtual void exposeEvent(QExposeEvent *pEvent);

	virtual void wheelEvent(QWheelEvent *pEvent);
	virtual void keyPressEvent(QKeyEvent *pEvent);

	virtual void mousePressEvent(QMouseEvent *pEvent);
	virtual void mouseReleaseEvent(QMouseEvent *pEvent);
	virtual void mouseMoveEvent(QMouseEvent *pEvent);

private:
	// Private data
	bool m_bAnimating;
	bool m_bRotateView; // Need to know if the view is being rotated
	bool m_bPanView; // Need to know if the view is being panned
	bool m_bGeometryChanged; // Need to know if we need to regenerate the geometry
	QPoint m_ptInitial; // Previously picked point on screen, used when rotating/panning the view
	QOpenGLContext *m_pGLContext; // OpenGL-context where to draw
	QOpenGLPaintDevice *m_pDevice; // OpenGL-paint device where to draw
	OglRenderer *m_pRenderer; // OpenGL Renderer which is going to do the render concerning functionality

	double m_dZoomFactor; // Needed to know the zoom magnitude
	double m_dCameraMoveSensitivity; // A sort of empirical unit deg/linear units
	double m_dPitch; // View rotation about the view's horizontal axis. A sort of empirical unit deg/linear units
	double m_dYaw; // View rotation bout the view's up-vector. A sort of empirical unit deg/linear units

	OglSpheref *m_pSphere; // The sphere to be rendered

	// Need to predefine a few cursor styles provided by Qt
	enum
	{
		kCurUsual = Qt::CrossCursor,
		kCurPan = Qt::ClosedHandCursor
	};
};

#endif // OPENGLSHADINGWINDOW_H
