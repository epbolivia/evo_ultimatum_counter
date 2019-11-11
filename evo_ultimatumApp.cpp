
#include "evo_ultimatumApp.h"

//(*AppHeaders
#include "evo_ultimatumMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(evo_ultimatumApp);

bool evo_ultimatumApp::OnInit()
{
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	evo_ultimatumDialog Dlg(0);
    	dlgexported = &Dlg;
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }

    return wxsOK;

}

evo_ultimatumDialog *evo_ultimatumApp::get_dialog()
{
    return dlgexported;
}
