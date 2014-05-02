#include <iostream>
#include <string>
#include <map>

#include "timeops.h"
#include "alarmcookie.h"
#include "arghandler.h"

#define APPID "getup"


using namespace std;


int main (int argc, char ** argv) {

    ArgHandler *ah = new ArgHandler(argc, argv);

    if (ah->list){
        listActiveAlarms();
        exit(0);
    }

    if (ah->deleting){
        deleteCookie((cookie_t) ah->delete_cookie);
        exit(0);
    }

    //Adding
	time_t now = time(0);
    time_t then = makeArmTime(ah->time);

	cout << "now:\t" << ctime(&now) << flush;
    cout << "then:\t" << ctime(&then) << flush;

    int seconds_till = difftime(then, now);
    cout << "\nseconds: " << seconds_till << endl;

    addAlarmdJob(seconds_till, ah->message, ah->sound, ah->command, ah->silent);
    listActiveAlarms();
}
