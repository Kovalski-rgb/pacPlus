#include "axis.h"
#include "IEntity.h"

class Pacman : public IEntity{
    private:
        int appearance;
        Axis axisX;
        Axis axisY;
        double speed;
        int lifes;
        double posX;
        double posY;
        double initPosY;
        double initPosX;

        short color;
        short background;

    public:
        Pacman(){
            speed = 0.1;
            lifes = 3;
            axisY = neutral;
            axisX = down;
            appearance = 35;
            posX = 0;
            posY = 0;

            initPosY = posY;
            initPosX = posX;

            color = 0;
            background = 3;
        }

        Pacman(double posY, double posX){
            speed = 0.1;
            lifes = 3;
            axisY = neutral;
            axisX = down;
            appearance = 35;
            this->posX = posX;
            this->posY = posY;

            initPosY = posY;
            initPosX = posX;

            color = 0;
            background = 3;
        }

        int getLifes(){
            return lifes;
        }
        void setLifes(int lifes){
            this->lifes = lifes;
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

        double getInitPosX(){
            return initPosX;
        }

        double getInitPosY(){
            return initPosY;
        }

};