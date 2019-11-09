
#ifndef EVO_ULTIMATUMAPP_H
#define EVO_ULTIMATUMAPP_H

#include <wx/app.h>
#include "evo_ultimatumMain.h"

class evo_ultimatumApp : public wxApp
{
    public:

        virtual bool OnInit();
        evo_ultimatumDialog *get_dialog();

    private:

        evo_ultimatumDialog *dlgexported;
};

#endif // EVO_ULTIMATUMAPP_H
