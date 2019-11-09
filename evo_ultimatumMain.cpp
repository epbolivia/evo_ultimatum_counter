
#include "evo_ultimatumMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(evo_ultimatumDialog)
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

#include <errno.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>

#include "ur_system.h"

const AP_HAL::HAL& hal = AP_HAL::get_HAL();

UR_System ur_system;
volatile bool evo_ultimatumDialog::_start_urus_running = false;

//(*IdInit(evo_ultimatumDialog)
const long evo_ultimatumDialog::ID_STATICBITMAP1 = wxNewId();
const long evo_ultimatumDialog::ID_BUTTON1 = wxNewId();
const long evo_ultimatumDialog::ID_BUTTON2 = wxNewId();
const long evo_ultimatumDialog::ID_PANEL1 = wxNewId();
const long evo_ultimatumDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(evo_ultimatumDialog, wxDialog)
    //(*EventTable(evo_ultimatumDialog)
    //*)
END_EVENT_TABLE()

evo_ultimatumDialog::evo_ultimatumDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(evo_ultimatumDialog)
    Create(parent, id, _("Urus GUI app"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(720,480));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(0,0), wxSize(720,480), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetBackgroundColour(wxColour(0,0,0));
    static_bg_bitmap = new wxStaticBitmap(Panel1, ID_STATICBITMAP1, wxNullBitmap, wxPoint(0,0), wxSize(720,408), wxSIMPLE_BORDER, _T("ID_STATICBITMAP1"));
    start = new wxButton(Panel1, ID_BUTTON1, _("Start"), wxPoint(0,464), wxSize(16,16), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    start->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUTEXT));
    close = new wxButton(Panel1, ID_BUTTON2, wxEmptyString, wxPoint(704,464), wxSize(16,16), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    close->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUTEXT));
    LcdTimeCounter = new wxLCDWindow(Panel1,wxPoint(96,376),wxSize(536,104));
    LcdTimeCounter->SetNumberDigits( 11);
    LcdTimeCounter->SetLightColour( wxColour(255,0,6));
    LcdTimeCounter->SetGrayColour( wxColour(53,0,2));
    LcdTimeCounter->SetValue( _T("00:00:00:00"));
    TimerLooper.SetOwner(this, ID_TIMER1);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&evo_ultimatumDialog::OnstartClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&evo_ultimatumDialog::OnQuit);
    Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&evo_ultimatumDialog::OnPanel1Paint,0,this);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&evo_ultimatumDialog::OnTimer1Trigger);
    //*)

    wxImage image = wxImage(_T("resources/"IMAGE_FILE_NAME), wxBITMAP_TYPE_PNG).Rescale(Panel1->GetSize().GetWidth(), Panel1->GetSize().GetHeight() - 80);
    static_bg_bitmap->SetBitmap(image);
    TimerLooper.Stop();
}

evo_ultimatumDialog::~evo_ultimatumDialog()
{
    //(*Destroy(evo_ultimatumDialog)
    //*)
}

void evo_ultimatumDialog::OnQuit(wxCommandEvent& event)
{
    _start_urus_running = false;
    sleep(1);
    hal.scheduler->stop_clock(0);
    sleep(1);
    Close();
}

void evo_ultimatumDialog::OnstartClick(wxCommandEvent& event)
{
    uint32_t seconds;
    static bool in_proc = false;

    if (in_proc) {
        printf("Allready started!\n");
        return;
    }

    in_proc = true;

    time(&_time_now);

    _time_begin = *localtime(&_time_now);

#if TIMER_MODE == TM_RELATIVE
    _time_begin.tm_hour = TM_REL_HOUR;
    _time_begin.tm_min = TM_REL_MIN;
    _time_begin.tm_sec = TM_REL_SEC;

    _time_begin.tm_year = get_year(TM_REL_YEAR);
    _time_begin.tm_mon = get_month(TM_REL_MONTH);
    _time_begin.tm_mday = TM_REL_MDAY;
#endif // ENABLE_TIME_TARGET

    mktime(&_time_begin);

    ur_system.set_time_begin(_time_begin);

    seconds = ur_system.get_time_left(TIME_TARGET_BASE);
    update_lcd_val(seconds);

    printf("Hour: %02u Min: %02u Sec: %02u \n", (seconds / 3600), ((seconds / 60) % 60), (seconds % 60));
    printf("The current seconds timezone %u \n", _time_now);
    printf("Current local time and date: %s \n", asctime(&_time_begin));

    int argc = 0;
    char* const argv[] = {""};
    hal.run(argc, argv);

    ur_system.setup();
    TimerLooper.Start(5);
}

void *evo_ultimatumDialog::_start_urus(void *arg)
{
    if (_start_urus_running) {
        return NULL;
    }

    _start_urus_running = true;

    ur_system.setup();

    while (_start_urus_running) {
            ur_system.loop();
            usleep(10000);
    }

    _start_urus_running = false;
    hal.console->printf("Stoped thread!\n");
    sleep(1);

    return NULL;
}

wxLCDWindow* evo_ultimatumDialog::get_lcd()
{
    return LcdTimeCounter;
}

void evo_ultimatumDialog::update_lcd_val(uint32_t seconds)
{
    uint32_t time_in_mill;
    time_in_mill = ur_system.get_time_millis();

    wxSprintf(_timestring, _("%02u:%02u:%02u:%02u"), (seconds / 3600) % 99, ((seconds / 60) % 60), (seconds % 60), (time_in_mill / 10) % 100);
    get_lcd()->SetValue(_timestring);
}

void evo_ultimatumDialog::OnPanel1Paint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
}

void evo_ultimatumDialog::OnTimer1Trigger(wxTimerEvent& event)
{
    ur_system.loop();
}
