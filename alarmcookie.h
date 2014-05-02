#include <alarmd/libalarm.h>
#include <iostream>

#define APPID "getup"

using namespace std;

int listActiveAlarms(){
    cookie_t *list = 0;
    cookie_t cookie = 0;
    alarm_event_t *eve = 0;

    if( (list = alarmd_event_query(0,0, 0,0, APPID)) == 0 )
    {
        cout << "Could not fetch" << endl;
	free(list);
	alarm_event_delete(eve);
        return -1;
    }

    
    for(int i=0; (cookie = list[i]) != 0; ++i )
    {
        alarm_event_delete(eve); 			//clear current details
        if( (eve = alarmd_event_get(cookie)) == 0 ) {
            cout << "Details for cookie " << (long)cookie << " could not be acessed" << endl;
            continue;
        }
        cout << "cookie#: " << (long)(cookie) << ',' << ctime(&eve->trigger) << endl;
    }
    return 0;
}



bool deleteCookie(cookie_t cookie){ 
	return alarmd_event_del(cookie) != -1;
}


cookie_t addAlarmdJob(int secs_from_now, char * message, char * sound, char * command, bool silent)
{
	int32_t flag = ALARM_EVENT_SHOW_ICON | ALARM_EVENT_BOOT;

	alarm_action_t *act = 0;
	alarm_event_t *eve = 0;

	eve = new alarm_event_t();
	eve->alarm_appid = APPID;
	eve->alarm_time = time(0) + secs_from_now;
	eve->flags = flag;
	eve->sound = sound; //DOESN'T WORK -- known BUG: http://talk.maemo.org/showthread.php?p=1062958
	eve->message = message;


	// Each act is a pointer to a new action relating to eve

	if (!silent) {
		act = alarm_event_add_actions(eve,1);
		alarm_action_set_label(act, "If you can read this, you are awake\nPress to stop.");
		act->flags |= ALARM_ACTION_WHEN_RESPONDED;
		act->flags |= ALARM_ACTION_TYPE_NOP;
	}


    if (string(command)!=""){
        //Add the command, a shell must be specified in the preamble
        act = alarm_event_add_actions(eve, 1);
        alarm_action_set_exec_command(act, command);
        act->flags |= ALARM_ACTION_WHEN_TRIGGERED;
        act->flags |= ALARM_ACTION_TYPE_EXEC;
    }

	return alarmd_event_add(eve);	
}
