#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int main(int argc, char** argv){

    //Quick change
    string command = "gsettings set org.gnome.settings-daemon.plugins.color night-light-temperature";
    if(argc > 1){
        system((command + " " + string(argv[1])).c_str());
        return 0;
    }
    
    /*Glib::RefPtr<Gio::Settings> colorSetting = 
                  Gio::Settings::create("org.gnome.settings-daemon.plugins.color");
    Glib::ustring tempKey = "night-light-temperature";*/

    string newTemp;
    cout<<"New temperature value (default: 4000): ";
    cin>>newTemp;
    //tempSetting.set_int(tempKey, k);

    command = command + " " + newTemp;
    if(system(command.c_str())){
        cout<<"There has been an error changing color temperature!"<<endl;
    }
    return 0;
}