#ifndef BOXNAN_CPP
#define BOXNAN_CPP

#include "boxnan.h"
#include <cmath>

boxNan::boxNan(int inNan)
{
    setNan(inNan);
    this->setAlignment(Qt::AlignCenter);
}

void boxNan::setNan(int inNan)
{
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);

    if(inNan == 0)
    {
        palette.setColor(QPalette::Background, Qt::gray);
        this->setAutoFillBackground(true); //  !!!
        this->setPalette(palette);
        this->setText("  ");
    }
    else
    {
        QColor fon;
        fon.setHsv((inNan*17+60)%256, 150, 255);

        palette.setColor(QPalette::Background, fon);

        this->setAutoFillBackground(true); //  !!!
        this->setPalette(palette);
        this->setNum(pow(2,inNan));
    }
}

#endif // BOXNAN_CPP
