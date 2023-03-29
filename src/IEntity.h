#pragma once

#include "axis.h"

class IEntity{
    private:
        int appearance;
        Axis axisX;
        Axis axisY;
        double speed;
        double posX;
        double posY;
        short color;
        short background;
    
    public:
        virtual double getSpeed() = 0;
        virtual void setSpeed(double speed) = 0;
        virtual int getAppearance() = 0;
        virtual Axis getAxisX() = 0;
        virtual void setAxisX(Axis axisX) = 0;
        virtual Axis getAxisY() = 0;
        virtual void setAxisY(Axis axisY) = 0;
        virtual double getPosX() = 0;
        virtual double getPosY() = 0;
        virtual void setPosX(double posX) = 0;
        virtual void setPosY(double posY) = 0;
        virtual short getColor() = 0;
        virtual short getBackground() = 0;
        virtual void setColor(short color) = 0;
        virtual void setBackground(short background) = 0;

};