#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;
class ctgs{
    public:
    ctgs(){
        srand(time(0));
        for(int i=0;i<24;i++){
            str_[i] = str[i];
        }
    }
    string get_rand(){
        int temp = rand() % 24;
        if(str[temp] == "none"){
            return get_rand();
        }
        string temp2 = str[temp];
        str[temp] = "none";
        return temp2;
    }
    int get_index(string inp){
        for(int i =0;i<24;i++){
            if(str_[i] == inp){
                return i;
            }
        }
    }
    private:
    string str_[24];
    string str[24] = {
        "General Knowledge",
        "Entertainment: Books",
        "Entertainment: Books",
        "Entertainment: Music",
        "Entertainment: Musicals & Theatres",
        "Entertainment: Television",
        "Entertainment: Video Games",
        "Entertainment: Board Games",
        "Science & Nature",
        "Science: Computers",
        "Science: Mathematics",
        "Mythology",
        "Sports",
        "Geography",
        "History",
        "Politics",
        "Art",
        "Celebrities",
        "Animals",
        "Vehicles",
        "Entertainment: Comics",
        "Science: Gadgets",
        "Entertainment: Japanese Anime & Manga",
        "Entertainment: Cartoon & Animations"
    };
};
