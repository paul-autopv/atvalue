//
// Created by Paul.Nel on 22/02/2022.
//

#ifndef ATVALUE_OUTAGESCHEDULE_H
#define ATVALUE_OUTAGESCHEDULE_H

class OutageSchedule{
public:
    OutageSchedule() : OutageSchedule(0,0){};
    OutageSchedule(int start, int duration): start_day_ {start}, duration_ {duration < 0 ? 0 : duration}{}

    int start() const{ return start_day_; }
    int duration() const { return duration_; }
    int end() const{
        if (!duration_)
            return start();
        return start() + duration() - 1;
    }

private:
    int start_day_ {0};
    int duration_ {0};
};


#endif //ATVALUE_OUTAGESCHEDULE_H
