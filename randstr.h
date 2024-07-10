#include <vector>
#include <string>
#include <time.h>
#include <cstdlib>
using namespace std;
class randstr{
    public:
    randstr(){
        vec.push_back(vec1);
        vec.push_back(vec2);
        vec.push_back(vec3);
    }
    string getstr(int index){
        srand(time(0));
        int temp = rand() % vec[index].size();
        return vec[index][temp];
        // return to_string(time(0));
    }
    private:
    vector<vector<string>> vec;
    vector<string> vec1 = {
        "Seyed wants to ask you some questions, are you ready?",
        "Don\'t be afraid of Seyed, he\'s kind!",
        "Show everyone who you are!"
    };
    vector<string> vec2 = {
        "Awesome",
        "Exelent",
        "Perfect",
        "You did a greate job!"
    };
    vector<string> vec3 = {
        "Be careful!",
        "Don\'t lose your hope",
        "Don\'t worry you can do that"
    };
};