#include "game2048_4d.h"

game2048_4D::game2048_4D(QWidget *parent) : QWidget(parent)
{
    QGridLayout *MainGrid = new QGridLayout;
    //*
    QLabel *name = new QLabel("2048");
    QFont FontNameGamePortal2D = name->font();
    FontNameGamePortal2D.setPixelSize(80);
    name->setFont(FontNameGamePortal2D);
    MainGrid->addWidget(name,0,0);

    QLabel *name2 = new QLabel("4D");
    name2->setFont(FontNameGamePortal2D);
    MainGrid->addWidget(name2,1,0);

    QFrame *counterFrame = new QFrame;
    QGridLayout *counterGrid = new QGridLayout;
    QLabel *counterLable = new QLabel("Счёт");
    QFont counterFont = name->font();
    counterFont.setPixelSize(40);
    counterLable->setFont(counterFont);
    counterGrid->addWidget(counterLable,0,0);
    counterOut = new QLabel();
    counterOut->setFont(counterFont);
    counterGrid->addWidget(counterOut,1,0);
    counterFrame->setLayout(counterGrid);
    MainGrid->addWidget(counterFrame,2,0);

    //*/
    for(uint8_t i0 = 0; i0<3;i0++)
    {
        for(uint8_t i1 = 0; i1<3;i1++)
        {
            QFrame *frame = new QFrame;
            QGridLayout *frameGrid = new QGridLayout;
            for(uint8_t i2 = 0; i2<3;i2++)
            {
                for(uint8_t i3 = 0; i3<3;i3++)
                {
                    Op[i0][i1][i2][i3] = new boxNan();
                    frameGrid->addWidget(Op[i0][i1][i2][i3], i2, i3);
                }
            }
            frame->setLayout(frameGrid);
            MainGrid->addWidget(frame,i0,i1+1);
        }
    }

    this->setLayout(MainGrid);
    clear();
}

void game2048_4D::clear()
{
    for(uint8_t i0 = 0; i0<3;i0++)
        for(uint8_t i1 = 0; i1<3;i1++)
            for(uint8_t i2 = 0; i2<3;i2++)
                for(uint8_t i3 = 0; i3<3;i3++)
                    game[i0][i1][i2][i3] = 0;
    update(1);
}

void game2048_4D::update(bool add)
{
    struct pos
    {
        int c[4];
    };

    QVector<pos> clean;
    for(uint8_t i0 = 0; i0<3;i0++)
        for(uint8_t i1 = 0; i1<3;i1++)
            for(uint8_t i2 = 0; i2<3;i2++)
                for(uint8_t i3 = 0; i3<3;i3++)
                {
                    Op[i0][i1][i2][i3]->setNan(game[i0][i1][i2][i3]);
                    if(game[i0][i1][i2][i3] == 0)
                        clean.append({i0, i1, i2, i3});
                }
    if(clean.size() == 0) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            QString::fromUtf8("Игра окончена"),
            QString::fromUtf8("Начать заново?"),
            QMessageBox::Yes | QMessageBox::No
        );

        if (reply == QMessageBox::Yes) {
            clear();
        }
        else if (reply == QMessageBox::No) {
            this->close();
        }

        return;
    }
    if(add)
    {
        int setArrPos = rand() % clean.size();
        game[clean[setArrPos].c[0]]
            [clean[setArrPos].c[1]]
            [clean[setArrPos].c[2]]
            [clean[setArrPos].c[3]] = rand()%100 > 75 ? 1 : 2;
        update(0);
    }
}

int game2048_4D::compose(int &A0, int &A1, int &A2)
{
    if(!(A0 == 0 && A1 == 0 && A2 == 0))
    {
        if(A0 == 0)
        {
            A0 = A1;
            A1 = A2;
            A2 = 0;
            return compose(A0, A1, A2) + 1;
        }
        else if (A0 == A1)
        {
            A0++;
            A1 = A2;
            A2 = 0;
            return A0;
        }
        else if (A0 == A2 && A1 == 0)
        {
            A0++;
            A2 = 0;
            return A0;
        }
        else if (A1 == A2 && A1 != 0)
        {
            A1++;
            A2 = 0;
            return A1;
        }
        else if (A1 == 0)
        {
            A1 = A2;
            A2 = 0;
            return 1;
        }
    }
    return 0;
}

void game2048_4D::keyPressEvent(QKeyEvent* pe)
{
    int step = 0;
    switch (pe->key())
    {
    case Qt::Key_W:
        for(uint8_t i0 = 0; i0<3;i0++)
            for(uint8_t i1 = 0; i1<3;i1++)
                for(uint8_t i2 = 0; i2<3;i2++)
                    step += compose(game[0][i0][i1][i2],
                            game[1][i0][i1][i2],
                            game[2][i0][i1][i2]);
        break;
    case Qt::Key_S:
        for(uint8_t i0 = 0; i0<3;i0++)
            for(uint8_t i1 = 0; i1<3;i1++)
                for(uint8_t i2 = 0; i2<3;i2++)
                    step += compose(game[2][i0][i1][i2],
                            game[1][i0][i1][i2],
                            game[0][i0][i1][i2]);
        break;

    case Qt::Key_A:
        for(uint8_t i0 = 0; i0<3;i0++)
            for(uint8_t i1 = 0; i1<3;i1++)
                for(uint8_t i2 = 0; i2<3;i2++)
                    step += compose(game[i0][0][i1][i2],
                            game[i0][1][i1][i2],
                            game[i0][2][i1][i2]);
        break;
    case Qt::Key_D:
        for(uint8_t i0 = 0; i0<3;i0++)
            for(uint8_t i1 = 0; i1<3;i1++)
                for(uint8_t i2 = 0; i2<3;i2++)
                    step += compose(game[i0][2][i1][i2],
                            game[i0][1][i1][i2],
                            game[i0][0][i1][i2]);
        break;
    case Qt::Key_I:
        for(uint8_t i0 = 0; i0<3;i0++)
            for(uint8_t i1 = 0; i1<3;i1++)
                for(uint8_t i2 = 0; i2<3;i2++)
                    step += compose(game[i0][i1][0][i2],
                            game[i0][i1][1][i2],
                            game[i0][i1][2][i2]);
        break;
    case Qt::Key_K:
        for(uint8_t i0 = 0; i0<3;i0++)
            for(uint8_t i1 = 0; i1<3;i1++)
                for(uint8_t i2 = 0; i2<3;i2++)
                    step += compose(game[i0][i1][2][i2],
                            game[i0][i1][1][i2],
                            game[i0][i1][0][i2]);
        break;

    case Qt::Key_J:
        for(uint8_t i0 = 0; i0<3;i0++)
            for(uint8_t i1 = 0; i1<3;i1++)
                for(uint8_t i2 = 0; i2<3;i2++)
                    step += compose(game[i0][i1][i2][0],
                            game[i0][i1][i2][1],
                            game[i0][i1][i2][2]);
        break;
    case Qt::Key_L:
        for(uint8_t i0 = 0; i0<3;i0++)
            for(uint8_t i1 = 0; i1<3;i1++)
                for(uint8_t i2 = 0; i2<3;i2++)
                    step += compose(game[i0][i1][i2][2],
                            game[i0][i1][i2][1],
                            game[i0][i1][i2][0]);
        break;

    case Qt::Key_R:
        clear();
        break;
    }
    update(step > 0);
    counter += step;
    counterOut->setNum(counter);
}
