
#ifndef EVO_ULTIMATUMMAIN_H
#define EVO_ULTIMATUMMAIN_H

//(*Headers(evo_ultimatumDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/lcdwindow.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
#include <wx/timer.h>
//*)

class evo_ultimatumDialog: public wxDialog
{
    public:

        evo_ultimatumDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~evo_ultimatumDialog();

        wxLCDWindow* get_lcd();
        void update_lcd_val(uint32_t seconds);

    private:

        wxChar _timestring[12];

        static void *_start_urus(void *arg);
        static volatile bool _start_urus_running;
        static volatile bool _timer_running;

        time_t _time_now;
        struct tm _time_begin;

        //uint32_t _get_time_left(uint32_t time_left, struct tm time_begin);

        //(*Handlers(evo_ultimatumDialog)
        void OnQuit(wxCommandEvent& event);
        void OnstartClick(wxCommandEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        //*)

        //(*Identifiers(evo_ultimatumDialog)
        static const long ID_STATICBITMAP1;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_PANEL1;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(evo_ultimatumDialog)
        wxButton* close;
        wxButton* start;
        wxLCDWindow* LcdTimeCounter;
        wxPanel* Panel1;
        wxStaticBitmap* static_bg_bitmap;
        wxTimer TimerLooper;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // EVO_ULTIMATUMMAIN_H
