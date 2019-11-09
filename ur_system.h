
#pragma once

#include <AP_HAL/AP_HAL.h>
#include <AP_Scheduler/AP_Scheduler.h>

#include "evo_ultimatumApp.h"
#include "evo_ultimatumMain.h"

#define hour_to_sec(time) time * 3600
#define get_year(year) year - 1900
#define get_month(month) month - 1

#define TIME_TARGET_BASE 48 //set the time left in hour, by default 48 hrs.

#define TM_REL_HOUR        9
#define TM_REL_MIN        30
#define TM_REL_SEC         0
#define TM_REL_YEAR     2019
#define TM_REL_MONTH      11
#define TM_REL_MDAY        6

#define TM_NOW      0   //display timer counter from zero
#define TM_RELATIVE 1   //display timer counter from TM_REL_X defines
#define TM_ABSOLUTE 2   //display timer counter from TIME_TARGET_BASE

#define TIMER_MODE TM_RELATIVE //change to set timer mode

#define IMAGE_FILE_NAME "urus_logo_v2.png"

class UR_System {
public:

    UR_System();

    void setup(void);
    void loop(void);

    uint32_t get_time_left(uint32_t time_left);
    uint32_t get_time_millis();
    void set_time_begin(struct tm time_begin);

private:

    AP_Scheduler _scheduler;
    static const AP_Scheduler::Task _scheduler_tasks[] PROGMEM;

    void _update(void);
    void _timer_trigger();

    uint32_t _nowmicros;
    struct tm _time_begin;
    evo_ultimatumDialog *dlg;
};
