#include "oglpropertiesdlg.h"

OglPropertiesDlg::OglPropertiesDlg(QWidget *pParent, Qt::WindowFlags flags) :
	QDialog(pParent, flags),
	m_pLBSphereCenter(nullptr),
	m_pLBSphereRadius(nullptr),
	m_pLBSphereSmoothU(nullptr),
	m_pLBSphereSmoothV(nullptr),
	m_pEDSphereCenterX(nullptr),
	m_pEDSphereCenterY(nullptr),
	m_pEDSphereCenterZ(nullptr),
	m_pEDSphereRadius(nullptr),
	m_pEDSphereSmoothU(nullptr),
	m_pEDSphereSmoothV(nullptr),
	m_pLBLOD(nullptr),
	m_pEDLOD(nullptr),
	m_pPBRender(nullptr),
	m_pMainLayout(nullptr)
{
	// Create the labels and line-edits
	m_pLBSphereCenter = new QLabel(this);
	m_pLBSphereRadius = new QLabel(this);
	m_pLBSphereSmoothU = new QLabel(this);
	m_pLBSphereSmoothV = new QLabel(this);
	m_pEDSphereCenterX = new QLineEdit(this);
	m_pEDSphereCenterY = new QLineEdit(this);
	m_pEDSphereCenterZ = new QLineEdit(this);
	m_pEDSphereRadius = new QLineEdit(this);
	m_pEDSphereSmoothU = new QLineEdit(this);
	m_pEDSphereSmoothV = new QLineEdit(this);

	m_pLBLOD = new QLabel(this);
	m_pEDLOD = new QLineEdit(this);

	m_pPBRender = new QPushButton(this);
	m_pMainLayout = new QGridLayout(this);

	setWindowTitle(tr("Fractal Properties..."));

	if (hasFocus())
	{
		setWindowOpacity(1.0);
	}
	else
	{
		setWindowOpacity(m_cdWindowOpacity);
	}

	// Set text to lables
	m_pLBSphereCenter->setText(tr("Sphere Center: "));
	m_pLBSphereRadius->setText(tr("Sphere Radius: "));
	m_pLBSphereSmoothU->setText(tr("Number of segments in U: "));
	m_pLBSphereSmoothV->setText(tr("Number of segments in V: "));
	m_pLBLOD->setText(tr("Level of Details: "));
	m_pPBRender->setText(tr("Render"));

	// Set default values into line-edits
	m_pEDSphereCenterX->setText("0.0");
	m_pEDSphereCenterY->setText("0.0");
	m_pEDSphereCenterZ->setText("0.0");
	m_pEDSphereRadius->setText("1.0");
	m_pEDSphereSmoothU->setText("24");
	m_pEDSphereSmoothV->setText("24");
	m_pEDLOD->setText("0");

	// Add the widgets to the grid layout
	m_pMainLayout->addWidget(m_pLBSphereCenter, 0, 0);
	m_pMainLayout->addWidget(m_pEDSphereCenterX, 0, 1);
	m_pMainLayout->addWidget(m_pEDSphereCenterY, 0, 2);
	m_pMainLayout->addWidget(m_pEDSphereCenterZ, 0, 3);
	m_pMainLayout->addWidget(m_pLBSphereRadius, 1, 0);
	m_pMainLayout->addWidget(m_pEDSphereRadius, 1, 1);
	m_pMainLayout->addWidget(m_pLBSphereSmoothU, 2, 0);
	m_pMainLayout->addWidget(m_pEDSphereSmoothU, 2, 1);
	m_pMainLayout->addWidget(m_pLBSphereSmoothV, 3, 0);
	m_pMainLayout->addWidget(m_pEDSphereSmoothV, 3, 1);
	m_pMainLayout->addWidget(m_pLBLOD, 4, 0);
	m_pMainLayout->addWidget(m_pEDLOD, 4, 1);
	m_pMainLayout->addWidget(m_pPBRender, 5, 1);

	// Set the grid layout to the current dialog
	setLayout(m_pMainLayout);

	// Connect the clicked-signal of the render button to the renderGL-slot of the current dialog
	connect(m_pPBRender, SIGNAL(clicked(bool)), this, SLOT(renderGL()));

	// The current dialog to be Non-Modal
	setWindowModality(Qt::NonModal);
	setFocusPolicy(Qt::WheelFocus);
}

OglPropertiesDlg::~OglPropertiesDlg()
{
	// Free the previously allocated memory
	if (m_pLBSphereCenter != nullptr)
	{
		delete m_pLBSphereCenter;
	}

	if (m_pLBSphereRadius != nullptr)
	{
		delete m_pLBSphereRadius;
	}

	if (m_pLBSphereSmoothU != nullptr)
	{
		delete m_pLBSphereSmoothU;
	}

	if (m_pLBSphereSmoothV != nullptr)
	{
		delete m_pLBSphereSmoothV;
	}

	if (m_pEDSphereCenterX != nullptr)
	{
		delete m_pEDSphereCenterX;
	}

	if (m_pEDSphereCenterY != nullptr)
	{
		delete m_pEDSphereCenterY;
	}

	if (m_pEDSphereCenterZ != nullptr)
	{
		delete m_pEDSphereCenterZ;
	}

	if (m_pEDSphereRadius != nullptr)
	{
		delete m_pEDSphereRadius;
	}

	if (m_pEDSphereSmoothU != nullptr)
	{
		delete m_pEDSphereSmoothU;
	}

	if (m_pEDSphereSmoothV != nullptr)
	{
		delete m_pEDSphereSmoothV;
	}

	if (m_pLBLOD != nullptr)
	{
		delete m_pLBLOD;
	}

	if (m_pEDLOD != nullptr)
	{
		delete m_pEDLOD;
	}

	if (m_pPBRender != nullptr)
	{
		delete m_pPBRender;
	}

	if (m_pMainLayout != nullptr)
	{
		delete m_pMainLayout;
	}
}

void OglPropertiesDlg::getRenderData(vec3d &ptSphereCenter, double &dSphereRadius,
									 unsigned int &unSmoothU, unsigned int &unSmoothV, unsigned int &unLOD)
{
	// Output the render area from the current dialog
	ptSphereCenter = vec3d(m_pEDSphereCenterX->text().toDouble(),
						   m_pEDSphereCenterY->text().toDouble(),
						   m_pEDSphereCenterZ->text().toDouble());

	dSphereRadius = m_pEDSphereRadius->text().toDouble();
	unSmoothU = m_pEDSphereSmoothU->text().toUInt();
	unSmoothV = m_pEDSphereSmoothV->text().toUInt();
	unLOD = m_pEDLOD->text().toUInt();
}

void OglPropertiesDlg::renderGL()
{
	emit sigRenderGL(); // Emit the signal to render the OpenGL-window
}

void OglPropertiesDlg::focusInEvent(QFocusEvent *pEvent)
{
	Q_UNUSED(pEvent);
	setWindowOpacity(1.0);
}

void OglPropertiesDlg::focusOutEvent(QFocusEvent *pEvent)
{
	Q_UNUSED(pEvent);
	setWindowOpacity(m_cdWindowOpacity);
}

void OglPropertiesDlg::enterEvent(QEvent *pEvent)
{
	Q_UNUSED(pEvent);
	setWindowOpacity(1.0);
}

void OglPropertiesDlg::leaveEvent(QEvent *pEvent)
{
	Q_UNUSED(pEvent);
	setWindowOpacity(m_cdWindowOpacity);
}


