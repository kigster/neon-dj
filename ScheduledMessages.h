
#ifndef ScheduleMessage_H
#define ScheduleMessage_H

#include <SmartMatrix3.h>
#include <stdio.h>

/*
Friday - Poolside
 3:00 - 4:30pm	Simon Mark
 4:30 - 5:45pm	Architecture

Friday - Night
 9:00 - 10:15pm	Exoendo
10:15 - 11:30pm	Betty Ray
11:30 - 12:45am	LeftCtrl
12:45 -  2:00am	aacdebo
 2:00 -  3:15am	Micron

Saturday - Poolside
11:30 - 12:45pm	bassben
12:45 - 2:00pm	rrrus
2:00 - 3:15pm	Ghost Squadron
3:15 - 4:30pm	kev/null
4:30 - 6:00pm	Daniel V

Saturday - Night

 9:30 - 10:45pm	Chloramor
10:45 - 11:00pm Ceremony
11:00 - 12:15am	davesimon
12:15 - 1:30am	Kem
 1:30 - 2:45am	Dulce Vita
 2:45 - 4:00am	Dan Suda
 4:00 - 5:30am	Stickybeats
 5:30 - 6:45am	Mo Corleone

Sunday Morning - Poolside


10:30 - 12:00pm Erik Karki
*/

 typedef char ItemType[];

class ScheduledMessages {
public:

  const char * array[] = {
      "First entry",
      "Second entry",
      "Third entry",
  };

#define n_array (sizeof (array) / sizeof (const char *))


  uint day;
  int month;
  int year;
  int hour;
  int minute;
  int durationMinutes;

  uint32_t epochStart, epochEnd;

  bool operator<(ScheduledMessage other) const {
    return epochStart < other.epochStart;
  }

};

#endif
