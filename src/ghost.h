#include "axis.h"
#include "IEntity.h"
#include "IpathFinder.h"
#include "randomPath.h"

class Ghost : public IEntity{
    private:
        int appearance;
        Axis axisX;
        Axis axisY;
        double speed;
        double posX;
        double posY;
        short color;
        short background;

        double initPosY;
        double initPosX;

        IPathFinder* AI;

    public:
        Ghost(){
            speed = 0.1;
            axisY = neutral;
            axisX = neutral;
            this->appearance = 63;
            this->posX = 0;
            this->posY = 0;
            initPosY = posY;
            initPosX = posX;
            this->color = 0;
            this->background = 7;
            AI = new RandomPath();
        }

        Ghost(double posY, double posX, int appearance, short color, short background){
            speed = 0.1;
            axisY = neutral;
            axisX = neutral;
            this->appearance = appearance;
            this->posX = posX;
            this->posY = posY;
            initPosY = posY;
            initPosX = posX;
            this->color = color;
            this->background = background;
            AI = new RandomPath();
        }

        Ghost(double posY, double posX, int appearance, short color, short background, IPathFinder* AI){
            speed = 0.1;
            axisY = neutral;
            axisX = neutral;
            this->appearance = appearance;
            this->posX = posX;
            this->posY = posY;
            initPosY = posY;
            initPosX = posX;
            this->color = color;
            this->background = background;
            this->AI = AI;
        }

        double getSpeed(){
            return speed;
        }
        void setSpeed(double speed){
            this->speed = speed;
        }

        int getAppearance(){
            return appearance;
        }

        Axis getAxisX(){
            return axisX;
        }
        void setAxisX(Axis axisX){
            this->axisX = axisX;
        }

        Axis getAxisY(){
            return axisY;
        }
        void setAxisY(Axis axisY){
            this->axisY = axisY;
        }

        double getPosX(){
            return posX;
        }
        double getPosY(){
            return posY;
        }

        void setPosX(double posX){
            this->posX = posX;
        }
        void setPosY(double posY){
            this->posY = posY;
        }
        short getColor(){
            return this->color;
        }
        short getBackground(){
            return this->background;
        }
        void setColor(short color){
            this->color = color;
        }
        void setBackground(short background){
            this->background = background;
        }

        std::vector<Axis> nextPath(){
            return AI->turnDirection();
        }

        double getInitPosX(){
            return initPosX;
        }

        double getInitPosY(){
            return initPosY;
        }
};