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
