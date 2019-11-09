
#include <AP_HAL/AP_HAL.h>

#include "ur_system.h"

#include <errno.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>

extern const AP_HAL::HAL& hal;
extern UR_System ur_system;

evo_ultimatumApp app;

#define SCHED_TASK(func, _interval_ticks, _max_time_micros) SCHED_TASK_CLASS(UR_System, &ur_system, func, _interval_ticks, _max_time_micros)

/*
  scheduler table - all regular tasks are listed here, along with how
  often they should be called (in 20ms units) and the maximum time
  they are expected to take (in microseconds)
 */

const AP_Scheduler::Task UR_System::_scheduler_tasks[] = {
    SCHED_TASK(_update,      50,     9000),
};

UR_System::UR_System()
{
}

void UR_System::setup(void)
{
    dlg = app.get_dialog();

    hal.scheduler->delay(100);

    _scheduler.init(&_scheduler_tasks[0], ARRAY_SIZE(_scheduler_tasks));

    _nowmicros = AP_HAL::micros();

    hal.console->printf("System init!\n");
}

void UR_System::loop(void)
{
    if ((AP_HAL::micros() - _nowmicros) > 19900) {
        _nowmicros = AP_HAL::micros();
        _scheduler.tick();
        _scheduler.run(20000);
    }
}

void UR_System::_update(void)
{
    uint32_t seconds;

    seconds = ur_system.get_time_left(TIME_TARGET_BASE);
    dlg->update_lcd_val(seconds);
}

uint32_t UR_System::get_time_left(uint32_t time_left)
{
    time_t time_now;
    uint32_t seconds;

    time(&time_now);

#if TIMER_MODE == TM_RELATIVE
    seconds = abs(difftime(time_now, mktime(&_time_begin)));
#endif // ENABLE_TIME_TARGET

#if TIMER_MODE == TM_ABSOLUTE
    seconds = hour_to_sec(time_left) - abs(time_now - mktime(&_time_begin));
#endif // ENABLE_TIME_TARGET

#if TIMER_MODE == TM_NOW
    seconds = difftime(time_now, mktime(&_time_begin));
#endif // ENABLE_TIME_TARGET

    return seconds;
}

void UR_System::_timer_trigger()
{
}

uint32_t UR_System::get_time_millis()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    uint32_t time_millis = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // convert tv_sec & tv_usec to millisecond
    return time_millis;
}

void UR_System::set_time_begin(struct tm time_begin)
{
    _time_begin = time_begin;
}
