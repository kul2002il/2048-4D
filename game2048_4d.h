#ifndef GAME2048_4D_H
#define GAME2048_4D_H

#include <QWidget>
#include <QLabel>
#include <QFormLayout>
#include <QFrame>
#include <QKeyEvent>
#include <QVector>
#include <QMessageBox>
#include "boxnan.cpp"
//#include <QDebug>

class game2048_4D : public QWidget
{
	Q_OBJECT
public:
	explicit game2048_4D(QWidget *parent = nullptr);

	int counter = 0;
	QLabel *counterOut;

	int game[3][3][3][3];
	boxNan *Op[3][3][3][3];

	void keyPressEvent(QKeyEvent* pe);
	void update(bool add = 0);
	int compose(int &A0, int &A1, int &A2);
	void clear();

signals:

public slots:
};

#endif // GAME2048_4D_H
