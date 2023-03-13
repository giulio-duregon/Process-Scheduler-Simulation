#include <iostream>
#include <exception>
#include "process.hpp"

#ifndef SCHEDULER_H
#define SCHEDULER_H

// For state transitions
bool v;
enum SCHEDULER_TYPE
{
    FCFS,
    LCFS,
    SRTF,
    RR,
    PRIO,
    PREPRIO
};

char *GET_ENUM_NAME(int enum_code)

{
    static char *enum_name[] = {
        (char *)"FCFS",
        (char *)"LCFS",
        (char *)"SRTF",
        (char *)"RR",
        (char *)"PRIO",
        (char *)"PREPRIO"};
    return enum_name[enum_code];
}

class Scheduler
{
public:
    virtual void add_process(Process *process_to_add){};
    virtual Process *get_next_process() { return nullptr; };
    Scheduler(){};

    bool does_preemt()
    {
        if (_scheduler_type == PREPRIO)
        {
            return true;
        }
        return false;
    }
    SCHEDULER_TYPE parse_type(const char *char_str)
    {
        switch (*char_str)
        {
        case 'F':
            return FCFS;
        case 'L':
            return LCFS;
        case 'S':
            return SRTF;
        case 'R':
            return RR;
        case 'P':
            return PRIO;
        case 'E':
            return PREPRIO;
        default:
            throw "Type of scheduler must be F, L, S, R, P or E";
        }
    }

    void set_scheduler_type(const char *s)
    {
        // Get / Set type of scheduler based on first character
        SCHEDULER_TYPE type = parse_type(s);
        _scheduler_type = type;

        // Increment pointer (get away from the character string)
        s++;

        // Fish out arguments
        scan_optional(s);
    }
    SCHEDULER_TYPE get_type()
    {
        return _scheduler_type;
    }
    int quantum = 0;
    int maxprio = 0;

private:
    SCHEDULER_TYPE _scheduler_type;
    void scan_optional(const char *s)
    {
        sscanf(s, "%d:%d", &quantum, &maxprio);
        if (maxprio == 0)
        {
            maxprio = 4;
        }
        printf("quantum: %d, maxprio: %d\n", quantum, maxprio);
    }
};

class FIFO_Scheduler : Scheduler
{
public:
    void add_process(Process *to_add)
    {
        set_process_dynamic_prio(to_add);

        std::deque<Process *>::iterator it;
        for (it = RUN_QUEUE.begin(); it != RUN_QUEUE.end(); ++it)
        {
            Process *temp = *it;
            if (to_add->get_dynamic_prio() < temp->get_dynamic_prio())
            {
                RUN_QUEUE.insert(it, to_add);
                return;
            }
        }
        RUN_QUEUE.push_back(to_add);
        return;
    };

    void set_process_dynamic_prio(Process *process)
    {
        if (process->get_dynamic_prio() <= -1)
        {
            process->set_dynamic_prio(process->get_static_prio() - 1);
        }
    }

    Process *get_next_process()
    {
        if (RUN_QUEUE.size() >= 1)
        {
            Process *next_process = RUN_QUEUE.front();
            RUN_QUEUE.pop_front();
            return next_process;
        }
        else
        {
            return nullptr;
        }
    };
    std::deque<Process *> RUN_QUEUE;

private:
    int quantum = 10000;
};

Scheduler *build_scheduler(SCHEDULER_TYPE type)
{
    switch (type)
    {
    case FCFS:
        return (Scheduler *)new FIFO_Scheduler;
    };
};
#endif