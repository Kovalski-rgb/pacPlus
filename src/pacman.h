#include "axis.h"

class Pacman{
    private:
        int appearance;
        Axis axisX;
        Axis axisY;
        double speed;
        int lifes;
        double posX;
        double posY;

    public:
        Pacman(){
            speed = 0.1;
            lifes = 3;
            axisY = neutral;
            axisX = down;
            appearance = 35;
            posX = 0;
            posY = 0;
        }

        Pacman(double posY, double posX){
            speed = 0.1;
            lifes = 3;
            axisY = neutral;
            axisX = down;
            appearance = 35;
            this->posX = posX;
            this->posY = posY;
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
};