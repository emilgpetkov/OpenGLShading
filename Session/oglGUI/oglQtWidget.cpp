#include "oglQtWidget.h"

OglMainWidget::OglMainWidget(QWidget *pParent, Qt::WindowFlags flags) :
	QWidget(pParent, flags),
	m_pChildGLWindow(nullptr),
	m_pWindowContainer(nullptr),
	m_pPropertiesDlg(nullptr)
{
	// Create the OpenGL child-window and the properties' dialog
	m_pChildGLWindow = new OglShadingWindow(nullptr);
	m_pPropertiesDlg = new OglPropertiesDlg(this);

	// Container for the OpenGL child-window. It is meant to control the OpenGL window
	m_pWindowContainer = this->createWindowContainer(m_pChildGLWindow, this, flags);
	m_pWindowContainer->setParent(this);
	m_pWindowContainer->resize(size());
	m_pWindowContainer->setFocusPolicy(Qt::WheelFocus);

	m_pPropertiesDlg->show();
	m_pPropertiesDlg->resize(100, 100);

	m_pWindowContainer->setFocus();
	m_pPropertiesDlg->clearFocus();

	// Connect the signals from the OpenGL window and the properties' dialog to the corresponding slots in the current object
	connect(m_pChildGLWindow, SIGNAL(signalKeyPressed(QKeyEvent*)), this, SLOT(handleKeyPressed(QKeyEvent*)));
	connect(m_pPropertiesDlg, SIGNAL(sigRenderGL()), this, SLOT(renderGL()));

	// Set window to maximized
	setWindowState(Qt::WindowMaximized);
}

OglMainWidget::~OglMainWidget()
{
	// Free the previously allocated memory, if any
	if (m_pChildGLWindow != nullptr)
	{
		delete m_pChildGLWindow;
		m_pChildGLWindow = nullptr;
	}

	if (m_pWindowContainer != nullptr)
	{
		delete m_pWindowContainer;
		m_pWindowContainer = nullptr;
	}

	if (m_pPropertiesDlg != nullptr)
	{
		delete m_pPropertiesDlg;
	}
}

void OglMainWidget::handleKeyPressed(QKeyEvent *pEvent)
{
	int nKey = pEvent->key();

	if (nKey == Qt::Key_1 && pEvent->modifiers() == Qt::ControlModifier)
	{
		// Show the properties' dialog
		if (m_pPropertiesDlg != nullptr && ! m_pPropertiesDlg->isVisible())
		{
			m_pPropertiesDlg->show();
		}
	}
}

void OglMainWidget::renderGL()
{
	vec3d ptCen;
	double dRadius = 0.0;
	unsigned int unSmoothU = 0u, unSmoothV = 0u, unLOD = 0u;

	// Get the render data from the properties and set it to the OpenGL-window
	m_pPropertiesDlg->getRenderData(ptCen, dRadius, unSmoothU, unSmoothV, unLOD);
	m_pChildGLWindow->setRenderData(ptCen, dRadius, unSmoothU, unSmoothV, unLOD);
	m_pChildGLWindow->renderNow();
}

void OglMainWidget::showEvent(QShowEvent *pEvent)
{
	if (m_pWindowContainer != nullptr)
	{
		m_pWindowContainer->show();
		m_pWindowContainer->setFocus();
	}

	if (m_pPropertiesDlg != nullptr)
	{
		m_pPropertiesDlg->show();
	}

	pEvent->setAccepted(false);
}

void OglMainWidget::resizeEvent(QResizeEvent *pEvent)
{
	if (m_pWindowContainer != nullptr)
	{
		m_pWindowContainer->resize(size());
		m_pWindowContainer->setFocus();
	}

	pEvent->setAccepted(true);
}
