#include <iostream>
#include <time.h>

using namespace std;


time_t makeArmTime(const char * alarm_string) {
    int yyyy=-1, mm=-1, dd=-1, HH=-1, MM=-1, SS=0;

	sscanf( alarm_string,
            "%04d/%02d/%02d-%02d:%02d",
            &yyyy, &mm ,&dd , &HH, &MM);
	
	int date = yyyy | mm | dd;
	if (date == -1 ) {
		cerr << "No date given, assuming today." << endl; 
        sscanf( alarm_string, "%02d:%02d:%02d", &HH, &MM, &SS);

		int times = HH | MM;
		if (times == -1 ) {
			cerr << "No time given either, doing squat." << endl; 
			exit(-1);
		}
	}
	
	time_t now = time(0);
	
	tm *time_then = localtime(&now);
	
	// Must have minute, hour by this stage
    time_then->tm_sec = SS;
	time_then->tm_min = MM;
	time_then->tm_hour = HH;

	if (date != - 1){
		time_then->tm_mday = dd;
		time_then->tm_mon = mm-1;
		time_then->tm_year = yyyy - 1900;
	}
	
	return mktime(time_then);
}
