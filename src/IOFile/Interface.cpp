#include "stdafx.h"
#include <Kapsul3D.h>
#include "IOFile.h"

class CPluginApp : public CWinApp
{
public:
	CPluginApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKoreApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CKoreApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CPluginApp, CWinApp)
	//{{AFX_MSG_MAP(CPluginApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKoreApp construction

CPluginApp theApp;

CPluginApp::CPluginApp()
{
}

BOOL CPluginApp::InitInstance() 
{
	return CWinApp::InitInstance();
}

// -- Interface ---------------------------------------------------------------

CKIoFile* CreateFileInterface()
{
	return new CKIoFile();
}

void DeleteFileInterface(CKIoFile* Interface)
{
	delete Interface;
}
