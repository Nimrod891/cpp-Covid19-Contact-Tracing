#include <iostream>
#include "../include/Session.h"
#include <fstream>


using namespace std;

int main(int argc, char** argv){
    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }

    std::string s = argv[1];
            //"../src/config4.json";
    //std::string s = "..\\src\\config1.json";
    Session sess(s);
    sess.simulate();
    sess.Output();

    return 0;
}


