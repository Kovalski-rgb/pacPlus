#include <stdlib.h>
#include "IpathFinder.h"

using namespace std;

class RandomPath: public IPathFinder{
    public:
    
    RandomPath(){

    }

    vector<Axis> turnDirection(){
        int order = rand() % 2;
        Axis yAxis;
        Axis xAxis;
        if(order = 1){
            yAxis = static_cast<Axis>(rand() % 3 - 1);
            if(yAxis != 0){
                xAxis = neutral;
            }else{
                xAxis = static_cast<Axis>(rand() % 2);
                if(xAxis == 0){
                    xAxis = down;
                }
            }
        }else{
            xAxis = static_cast<Axis>(rand() % 3 - 1);
            if(xAxis != 0){
                yAxis = neutral;
            }else{
                yAxis = static_cast<Axis>(rand() % 2);
                if(yAxis == 0){
                    yAxis = down;
                }
            }
        }
        vector<Axis> direction 
        {
            yAxis, xAxis
        };
        return direction;
    }

};
