#ifndef ARG_HANDLER
#define ARG_HANDLER

#include <string.h>
#include <iostream>
#include <stdio.h>

//Main-Args
#define silent_arg "--silent"
#define sound_arg "--sound="
#define command_arg "--command="
#define message_arg "--message="
#define icon_arg "--icon="


//Recur-Args
#define weekday_arg "--weekday="
#define monthday_arg "--monthday="
#define hour_arg "--hour="
#define min_arg "--min="

#define target " alarum"

using namespace std;


class Recur{
public:
    //Arg map
    /*
    map <char *, int > arg_map = {
     {"sun",0},{"mon",1},{"tue",2},
     {"wed",3},{"thu",4},{"fri",5},{"sat",6}
    };
    */
    Recur (){}; // to implement
};

class ArgHandler{
public:
    bool silent, list, deleting;
    int delete_cookie;
    char * sound, *command, *message, *icon, *time;
    Recur *recr;

    ArgHandler(int argc, char ** argv){
        //Copy
        this->argc = argc;
        this->argv = argv;

        //Defaults
        deleting = list = silent = false;
        delete_cookie = -1;
        sound = command = "";
        message = "Wakey wakey!";
        icon = "/usr/share/icons/default/cursors/trek";
        recr = 0;

        parseArgs();
//        printMainOpts();
    }

private:
    int argc; char ** argv;

    void printMainOpts(){
        cerr << "silent:" << silent << endl;
        cerr << "sound:" << sound << endl;
        cerr << "command:" << command << endl;
        cerr << "message:" << message << endl;
        cerr << "icon:" << icon << endl;
    }


    int parseArgs()
    {
        if (argc < 2) usage();

        string first = argv[1];

        if (first=="list"){
            list=  true;
            return 0;
        }
        if (first=="delete"){
            if (argc<3) usage();
            deleting = true;
            sscanf( argv[2], "%d", &delete_cookie);
            return 0;
        }

        //Not list or delete? Move on to time functions
        if (first!="set") usage();
        if (argc<3) usage();

        time = argv[2];

        //Opts
        if (argc >= 3){
            for (int i =3; i< argc; i++){
                string arg = argv[i];

                //std::string.c_str() returns a const char *, which cannot be modified.
                //Need to fully copy the string into a new char * array.
                string temp = arg.substr(arg.find('=')+1,string::npos).c_str();
                char *past_equals = new char[temp.length()+1];
                strcpy(past_equals, temp.c_str());

                if (arg.find(silent_arg)!=-1) silent = true;
                else if (arg.find(sound_arg)!=-1) sound = past_equals;
                else if (arg.find(command_arg)!=-1) command = past_equals;
                else if (arg.find(message_arg)!=-1) message = past_equals;
                else if (arg.find(icon_arg)!=-1) icon = past_equals;
                else {
                    cerr << "Uh.. could not parse: " << argv[i] << endl;
                    exit(-1);
                }
            }
        }
        return 0;
    }


    void usage(){
        cerr << "usage:" << endl;
        cerr <<  target  << " set <TIME> [OPTS] [RECUR]" << endl;
        cerr << "    or " << " list" << endl;
        cerr << "    or " << " delete <cookie_id>" << endl;
        cerr << endl;
        cerr << "where TIME:" << endl;
        cerr << "   yyyy/mm/dd-HH:MM\tstart on date" << endl;
        cerr << "   HH:MM[:SS]      \tstart today [with secs]" << endl;
        cerr << endl;
        cerr << "where OPTS:" << endl;
        cerr << silent_arg << "\tstealth mode, no buttons" << endl;
        cerr << sound_arg << "\"Q\"\tset sound to Q" << endl;
        cerr << command_arg << "\"R\"\trun command R" << endl;
        cerr << message_arg << "\"S\"\tset message to S" << endl;
        cerr << icon_arg << "\"T\"\tset icon to T" << endl;
        cerr << endl;
        cerr << "where RECUR:" << endl;
        cerr << weekday_arg << "sun,mon,.." << endl;
        cerr << monthday_arg << "0,..,31" << endl;
        cerr << hour_arg << "0,..,23" << endl;
        cerr << min_arg << "0,..,59" << endl;
        exit(-1);
    }
};


#endif
