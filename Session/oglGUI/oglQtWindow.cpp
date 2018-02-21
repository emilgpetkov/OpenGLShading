#include "oglQtWindow.h"

#include <math.h>

OglShadingWindow::OglShadingWindow(QWindow *parent) :
	QWindow(parent),
	m_bAnimating(false),
	m_bRotateView(false),
	m_bPanView(false),
	m_bGeometryChanged(false),
	m_ptInitial(QPoint(0, 0)),
	m_pGLContext(nullptr),
	m_pDevice(nullptr),
	m_pRenderer(nullptr),
	m_pSphere(nullptr),
	m_dZoomFactor(0.1), // The view vector is going to move in its direction by that factor * its lenght
	m_dCameraMoveSensitivity(5.0),
	m_dPitch(0.0),
	m_dYaw(0.0)
{
	this->setSurfaceType(QWindow::OpenGLSurface);
}

OglShadingWindow::~OglShadingWindow()
{
	// Free the previously allocated memory if any and reset the corresponding pointers
	if (m_pDevice != nullptr)
	{
		delete m_pDevice;
		m_pDevice = nullptr;
	}

	if (m_pGLContext != nullptr)
	{
		delete m_pGLContext;
		m_pGLContext = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pSphere != nullptr)
	{
		delete m_pSphere;
		m_pSphere = nullptr;
	}
}

void OglShadingWindow::render(QPainter *pPainter)
{
	Q_UNUSED(pPainter);
}

void OglShadingWindow::render()
{
	// Create the device if it is not available
	if (m_pDevice == nullptr)
	{
		m_pDevice = new QOpenGLPaintDevice;
	}

	// Resize the device to the actual window size
	m_pDevice->setSize(this->size());

	if (m_pRenderer != nullptr)
	{
		// If the renderer is available...
		// Set the viewport
		double dRatio = devicePixelRatio();
		m_pRenderer->setViewport(0, 0, size().width() * dRatio, size().height() * dRatio);

		if (m_bGeometryChanged)
		{
			// If we need to regenerate the geometrical data
			float *m_pGeomData;
			unsigned int m_unGeomVertCount;
			unsigned int m_unComponentsPerVertex;
			int m_nVertexParams;
			unsigned int *m_pElements;
			unsigned int m_unElmsCount;

			// Regenerate the data
			m_pSphere->generateVertexData(m_pGeomData, m_unGeomVertCount, m_unComponentsPerVertex, m_nVertexParams);
			m_pSphere->generateElements(m_pElements, m_unElmsCount);

			if (m_pGeomData != nullptr && m_nVertexParams != OglSpheref::vpNone)
			{
				// Set the data to the renderer
				m_pRenderer->setGeometry(m_pGeomData, m_unGeomVertCount, m_unComponentsPerVertex, m_nVertexParams);
				m_pRenderer->setElements(m_pElements, m_unElmsCount);
			}

			// We have regenerated the data, so unset the flag
			m_bGeometryChanged = false;
		}

		// Do render
		m_pRenderer->doRender();
	}

	QPainter pPainter(m_pDevice);
	render(&pPainter);
}

void OglShadingWindow::initialize()
{
	// Usually used cursor shape
	setCursor(Qt::CursorShape(kCurUsual));

	if (m_pRenderer == nullptr)
	{
		// Create the renderer and the sphere
		m_pRenderer = new OglRenderer;

		if (m_pSphere != nullptr)
		{
			// First free the allocated memory, if any
			delete m_pSphere;
			m_pSphere = nullptr;
		}

		m_pSphere = new OglSpheref;

		float *m_pGeomData;
		unsigned int m_unGeomVertCount;
		unsigned int m_unComponentsPerVertex;
		int m_nVertexParams;
		unsigned int *m_pElements;
		unsigned int m_unElmsCount;

		// Generate the data
		m_pSphere->generateVertexData(m_pGeomData, m_unGeomVertCount, m_unComponentsPerVertex, m_nVertexParams);
		m_pSphere->generateElements(m_pElements, m_unElmsCount);

		if (m_pGeomData != nullptr && m_nVertexParams != OglSpheref::vpNone)
		{
			// Set the data to the renderer. Needed before the initialization of the renderer
			m_pRenderer->setGeometry(m_pGeomData, m_unGeomVertCount, m_unComponentsPerVertex, m_nVertexParams);
			m_pRenderer->setElements(m_pElements, m_unElmsCount);

			// Initialize the renderer
			m_pRenderer->initialize();

			// Set camera/view parameters
			vec3d pos = m_pSphere->getCenter() + vec3d(1.0, 0.0, 0.0) * (3.0 * m_pSphere->getRadius());
			vec3d target = vec3d(0.0, 0.0, 0.0);
			m_pRenderer->setView(pos, target, vec3d(0.0, 0.0, -1.0));

			// Set projections' data needed to generate the projection matrices
			double dAspect = static_cast<double>(size().width()) / static_cast<double>(size().height());
			m_pRenderer->setPerspective(50.0, dAspect, 0.1, 1000.0);
			m_pRenderer->setOrtho(-dAspect, dAspect, 1.0, -1.0, -100.0, 100.0);

			// Set ortho, i.e. turn perspective OFF
			m_pRenderer->setIsPerspective(false);
		}
	}
}

void OglShadingWindow::setAnimation(bool bAnimating)
{
	m_bAnimating = bAnimating;

	if (m_bAnimating)
	{
		renderLater();
	}
}

void OglShadingWindow::setRenderData(const vec3d &ptSphereCenter, const double &dSphereRadius,
									 const unsigned int &unSmoothU, const unsigned int &unSmoothV, const unsigned int &unLOD)
{
	// Needed render data
	if (m_pSphere == nullptr || m_pRenderer == nullptr)
	{
		return;
	}

	m_pSphere->setCenter(ptSphereCenter);
	m_pSphere->setRadius(dSphereRadius);
	m_pSphere->setSmoothU(unSmoothU);
	m_pSphere->setSmoothV(unSmoothV);
	m_pRenderer->setLOD(unLOD);

	m_bGeometryChanged = true;
}

void OglShadingWindow::renderLater()
{
	requestUpdate();
}

void OglShadingWindow::renderNow()
{
	// Is the window exposed?
	if (! isExposed())
	{
		return;
	}

	bool bNeedsInitialize = false;

	// Create the GL-context if needed
	if (m_pGLContext == nullptr)
	{
		m_pGLContext = new QOpenGLContext(this);
		m_pGLContext->setFormat(this->requestedFormat());
		m_pGLContext->create();
		bNeedsInitialize = true;
	}

	m_pGLContext->makeCurrent(this);

	// Initialization...
	if (bNeedsInitialize)
	{
		initializeOpenGLFunctions();
		initialize();
	}

	// Render
	render();
	m_pGLContext->swapBuffers(this);

	if (m_bAnimating)
	{
		renderLater();
	}
}

bool OglShadingWindow::event(QEvent *pEvent)
{
	switch (pEvent->type())
	{
	case QEvent::UpdateRequest:
		renderNow();
		return true;
	default:
		return QWindow::event(pEvent);
	}
}

void OglShadingWindow::exposeEvent(QExposeEvent *pEvent)
{
	Q_UNUSED(pEvent);

	if (isExposed())
	{
		// Render if the window is exposed
		renderNow();
	}
}

void OglShadingWindow::wheelEvent(QWheelEvent *pEvent)
{
	if (m_pRenderer == nullptr)
	{
		return;
	}

	// Zoom In/Out
	int nDelta = pEvent->delta();
	double dZoomFactor = 0.0, dSizeZoomFactor = 1.0;

	if (nDelta > 0)
	{
		dSizeZoomFactor = dZoomFactor = -m_dZoomFactor;
	}
	else if (nDelta < 0)
	{
		dZoomFactor = m_dZoomFactor;
		dSizeZoomFactor = OglZero(m_dZoomFactor) ? m_dZoomFactor : 1.0 / m_dZoomFactor;
	}

	if (m_pRenderer->getIsPerspective())
	{
		// If perspective is ON, move the camera and it's target towards latter
		vec3d ptPos, ptTarget, vUp;
		vec3d vDir, vTransl;

		// Get the view parameters
		m_pRenderer->getView(ptPos, ptTarget, vUp);
		vDir = (ptTarget - ptPos);

		dZoomFactor *= 0.50;

		// Move the camera's position and target
		vTransl = -vDir * dZoomFactor;
		ptPos = ptPos + vTransl;

		// Set the view's parameters to the renderer
		m_pRenderer->setView(ptPos, ptTarget, vUp);
	}
	else
	{
		// If ortho...
		double dLeft = 0.0, dRight = 0.0, dTop = 0.0, dBottom = 0.0;
		double dNear = 0.0, dFar = 0.0;

		// Get the projection's parameters
		m_pRenderer->getOrtho(dLeft, dRight, dTop, dBottom, dNear, dFar);

		// Resize the viewport's dimesions
		if (nDelta < 0)
		{
			dLeft *= fabs(nDelta) / 100.0;
			dTop *= fabs(nDelta) / 100.0;
		}
		else if (nDelta > 0)
		{
			dLeft /= fabs(nDelta) / 100.0;
			dTop /= fabs(nDelta) / 100.0;
		}

		dRight = -dLeft;
		dBottom = -dTop;

		// Set the ortho parameters
		m_pRenderer->setOrtho(dLeft, dRight, dTop, dBottom, dNear, dFar);
	}

	// Render
	renderNow();
}

void OglShadingWindow::keyPressEvent(QKeyEvent *pEvent)
{
	// Handle the key-pressed
	int nKey = pEvent->key();

	if (nKey >= Qt::Key_Left && nKey <= Qt::Key_Down)
	{
		// Rotate the view using the arrow-keys
		// Left/right - yaw, i.e. rotate about view's up vector;
		// Rotate the camera's position about camera's target and
		// set the view horizontal (vViewX) vector
		// as a cross product of the Up-vector x target-to-position-vector.
		// ---------
		// Up/Down - pitch, i.e. rotate about view's horizontal vector;
		// Rotate the camera's position about camera's target and
		// set the view's Up-Vector as a cross product of the
		// target-to-position-vector (vView) x view horizontal (vViewX) vector.

		vec3d ptPos, ptTarget, vUp;
		vec3d vDir, vView;
		m_pRenderer->getView(ptPos, ptTarget, vUp);
		vView = ptPos - ptTarget;
		vDir = vView.normal();

		if (nKey == Qt::Key_Left)
		{
			double dAng = -m_dCameraMoveSensitivity;
			mat4d mRot;
			vec3d vViewX = vUp.crossProduct(vDir).normal();
			mRot.setToRotation(OglRadians(dAng), ptTarget, vUp);
			ptPos = mRot * ptPos;
			vViewX = vUp.crossProduct((ptPos - ptTarget).normal()).normal();
			m_pRenderer->setView(ptPos, ptTarget, vUp);
		}
		else if (nKey == Qt::Key_Right)
		{
			double dAng = m_dCameraMoveSensitivity;
			mat4d mRot;
			vec3d vViewX = vUp.crossProduct(vDir).normal();
			mRot.setToRotation(OglRadians(dAng), ptTarget, vUp);
			ptPos = mRot * ptPos;
			vViewX = vUp.crossProduct((ptPos - ptTarget).normal()).normal();
			m_pRenderer->setView(ptPos, ptTarget, vUp);
		}
		else if (nKey == Qt::Key_Up)
		{
			double dAng = m_dCameraMoveSensitivity;

			mat4d mRot;
			const vec3d vViewX = vUp.crossProduct(vDir).normal();
			mRot.setToRotation(OglRadians(dAng), ptTarget, vViewX);
			ptPos = mRot * ptPos;
			vView = (ptPos - ptTarget);
			vUp = vView.normal().crossProduct(vViewX.normal()).normal();

			m_pRenderer->setView(ptPos, ptTarget, vUp);
		}
		else if (nKey == Qt::Key_Down)
		{
			double dAng = -m_dCameraMoveSensitivity;

			mat4d mRot;
			const vec3d vViewX = vUp.crossProduct(vDir).normal();
			mRot.setToRotation(OglRadians(dAng), ptTarget, vViewX);
			ptPos = mRot * ptPos;
			vUp = vView.normal().crossProduct(vViewX.normal()).normal();

			m_pRenderer->setView(ptPos, ptTarget, vUp);
		}

		//Render
		renderNow();
	}
	else if (nKey == Qt::Key_P)
	{
		// Turn perspective On/Off
		m_pRenderer->setIsPerspective(! m_pRenderer->getIsPerspective());
		renderNow(); // Render
	}
	else
	{
		// Emit a signal that might be caught by the parent-widget
		emit signalKeyPressed(pEvent);
	}

	pEvent->setAccepted(true); // Accept the event
}

void OglShadingWindow::mousePressEvent(QMouseEvent *pEvent)
{
	// Initialize mouse dragging in the form of view rotate/pan
	m_ptInitial = pEvent->pos();

	Qt::MouseButtons mouseButtons = pEvent->buttons();

	if (mouseButtons & Qt::LeftButton)
	{
		m_bRotateView = true;
	}
	else if (mouseButtons & Qt::MidButton)
	{
		m_bPanView = true;
	}
}

void OglShadingWindow::mouseMoveEvent(QMouseEvent *pEvent)
{
	// Current mous position
	QPoint ptScreenPoint = pEvent->pos();

	if (m_bRotateView)
	{
		// If we are rotating the view, the calculations are similar to the arrow keys
		// x-Offset -> yaw -> rotate camera position about target and Up-vector
		// y-Offset -> pitch ->  rotate camera position about target and horizontal vViewX-vector
		// Combine both rotations
		double dOffsetX = static_cast<double>(ptScreenPoint.x() - m_ptInitial.x());
		double dOffsetY = static_cast<double>(ptScreenPoint.y() - m_ptInitial.y());

		vec3d ptPos, ptTarget, vUp;
		vec3d vDir, vView;
		m_pRenderer->getView(ptPos, ptTarget, vUp);
		vView = ptPos - ptTarget;
		vDir = vView.normal();

		const vec3d &vViewX = vUp.normal().crossProduct(vDir).normal();

		dOffsetX *= m_dCameraMoveSensitivity / 100.0;
		dOffsetY *= m_dCameraMoveSensitivity / 100.0;

		m_dYaw = (dOffsetX);
		m_dPitch = (dOffsetY);

		mat4d mRotYaw, mRotPitch, mRotTot;
		mRotYaw.setToRotation(OglRadians(m_dYaw), ptTarget, vUp.normal()); // Set yaw-rotation
		mRotPitch.setToRotation(OglRadians(-m_dPitch), ptTarget, vViewX.normal()); // Set pitch-rotation
		mRotTot = mRotPitch * mRotYaw; // Get total rotation: first yaw, then pitch
		ptPos = mRotTot * ptPos; // Transform the camera position
		vView = ptPos - ptTarget; // target-to-position-vector
		vUp = vView.normal().crossProduct(vViewX.normal()).normal(); // Recalculate the Up-Vector
		m_pRenderer->setView(ptPos, ptTarget, vUp); // Set the view parameters

		// Render
		renderNow();
	}
	else if (m_bPanView)
	{
		// Pan -> move the camera position and target in the direction of the mouse move
		setCursor(Qt::CursorShape(kCurPan));

		double dOffsetX = static_cast<double>(ptScreenPoint.x() - m_ptInitial.x());
		double dOffsetY = static_cast<double>(m_ptInitial.y() - ptScreenPoint.y());

		dOffsetX *= m_dCameraMoveSensitivity / 1000.0;
		dOffsetY *= m_dCameraMoveSensitivity / 1000.0;

		vec3d ptPos, ptTarget, vUp;
		vec3d vDir, vView;
		m_pRenderer->getView(ptPos, ptTarget, vUp);
		vView = ptTarget - ptPos;
		vDir = vView.normal();

		const vec3d &vViewX = vUp.normal().crossProduct(vDir).normal();

		// Set translation using the mouse move offset as distance and Up- and vViewX-vectors as directions
		// in vertical and horizontal directions
		mat4d mTransl;
		mTransl.setToTranslation((vViewX * dOffsetX + vUp * dOffsetY));
		ptPos = mTransl * ptPos; // Transform the camera position
		ptTarget = mTransl * ptTarget; // Transform the camera target

		vUp = vView.normal().crossProduct(vViewX.normal()).normal(); // Recalculate the Up-Vector
		m_pRenderer->setView(ptPos, ptTarget, vUp); // Set the view parameters

		renderNow(); // Render
	}

	m_ptInitial = ptScreenPoint; // Save the mouse position as an intialn one
}

void OglShadingWindow::mouseReleaseEvent(QMouseEvent *pEvent)
{
	Q_UNUSED(pEvent);

	// Unset the rotate/pan view flags
	m_bRotateView = false;
	m_bPanView = false;
	setCursor(Qt::CursorShape(kCurUsual));
}
