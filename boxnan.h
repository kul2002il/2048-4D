#ifndef BOXNAN_H
#define BOXNAN_H

#include <QLabel>

class boxNan : public QLabel
{
public:
	inline explicit boxNan(int inNan = 0);	//Почему-то без inline не работает.
	inline void setNan(int inNan);	//Также.
};

#endif // BOXNAN_H
