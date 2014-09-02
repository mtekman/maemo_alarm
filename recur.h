#include <alarmd/libalarm.h>
#include <map>


//Recur-Args
#define weekday_arg "--weekday="
#define monthday_arg "--monthday="
#define hour_arg "--hour="
#define min_arg "--min="

using namespace std;


class Recur{

public:
	const char *weekday;
	int monthday, hour, minute;

	alarm_recur_t art; // To be setup from other args
	map <const char *, int > arg_map;

	Recur(){
		arg_map["sun"]=0; arg_map["mon"]=1;arg_map["tue"]=2;
		arg_map["wed"]=3;arg_map["thu"]=4; arg_map["fri"]=5;
		arg_map["sat"]=6;

		// defaults
		monthday = hour = minute = -1;
		weekday = ""; 
	}

	void setupRecurMask(){
/* uint64_t mask_min;    // 0 .. 59
   uint32_t mask_hour;   // 0 .. 23
   uint32_t mask_mday;   // 1 .. 31   1=first
   uint32_t mask_wday;   // 0 .. 6    0=sunday
   uint32_t mask_mon;    // 0 .. 11   0=january */
		if (monthday!=-1) art.mask_mday = monthday;
		if (hour!=-1) art.mask_hour = hour;
		if (minute!=-1) art.mask_min = minute;
		if (weekday!="") art.mask_wday = arg_map[weekday];
		// month not implemented
	}

};

