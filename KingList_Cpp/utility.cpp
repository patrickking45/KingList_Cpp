#include <QColor>


using namespace std;

inline vector<string> split(string str, string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    vector<string> arr;
    current=strtok(cstr,sep.c_str());
    while(current != NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

inline QColor getQColorFromString(string rgbString){

    if(rgbString == ""){
        rgbString = "255,255,255";
    }

    vector<string> rgb = split(rgbString, ",");
    return QColor(stoi(rgb[0]),stoi(rgb[1]),stoi(rgb[2]),255);
}

inline string getRGBStringFromQColor(QColor color){
    return ( to_string(color.red()) + ", " + to_string(color.green()) + ", " + to_string(color.blue()) );
}


