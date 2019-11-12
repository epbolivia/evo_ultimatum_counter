/*
   Dynamic multiplatform time left counter.
   Copyright (c) 2019 Hiroshi Takey F. <htakey@gmail.com>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
