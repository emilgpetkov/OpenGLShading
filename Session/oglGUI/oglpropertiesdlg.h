#ifndef OGLPROPERTIESDLG_H
#define OGLPROPERTIESDLG_H

#include "oglGUI_Global.h"

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

#include "oglvector.h"

using namespace OglGeomUtils;

// Properties dialog
class OPENGLSHADINGWINDOWSHARED_EXPORT OglPropertiesDlg : public QDialog
{
	Q_OBJECT // Need to "work" as a QObject

public:
	explicit OglPropertiesDlg(QWidget *pParent, Qt::WindowFlags flags = Qt::WindowFlags()); // C-tor
	virtual ~OglPropertiesDlg();  // Virtual d-tor, we would need to free the allocated memory in this child-class

	// Get the Render Data from the current dialog
	void getRenderData(vec3d &ptSphereCenter, double &dSphereRadius,
					   unsigned int &unSmoothU, unsigned int &unSmoothV, unsigned int &unLOD);

signals:
	void sigRenderGL(); // Emit the signal when need to render

public slots:
	void renderGL(); // Handle the click-event from the Render-Button

protected:
	// Reimplemented protected virtual methods. Their functionality is self-explaining
	virtual void focusInEvent(QFocusEvent *pEvent);
	virtual void focusOutEvent(QFocusEvent *pEvent);
	virtual void enterEvent(QEvent *pEvent);
	virtual void leaveEvent(QEvent *pEvent);

private:
	// Labels and LineEdits
	QLabel *m_pLBSphereCenter;
	QLabel *m_pLBSphereRadius;
	QLabel *m_pLBSphereSmoothU;
	QLabel *m_pLBSphereSmoothV;

	QLineEdit *m_pEDSphereCenterX;
	QLineEdit *m_pEDSphereCenterY;
	QLineEdit *m_pEDSphereCenterZ;
	QLineEdit *m_pEDSphereRadius;
	QLineEdit *m_pEDSphereSmoothU;
	QLineEdit *m_pEDSphereSmoothV;

	QLabel *m_pLBLOD;
	QLineEdit *m_pEDLOD;

	QPushButton *m_pPBRender; // Render Button
	QGridLayout *m_pMainLayout; // Grid layout where to arrange the labels and line-edits

	const double m_cdWindowOpacity = 0.5; // Opacity when the dialog is out of focus

};

#endif // OGLPROPERTIESDLG_H
