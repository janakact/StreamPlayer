#include <string>
#include <conio.h>


using namespace std; 


char getcolor(int color)
{
	char col;
	if( color < 10)
		col=color+'0';
	else
		col=color+55;
	return col;
}

int setColor(int bcolor,int fcolor)
{
	char buff[256];
	char bc[2];
	char fc[2];
	bc[0]=getcolor(bcolor);
	fc[0]=getcolor(fcolor);
	bc[1]='\0';
	fc[1]='\0';

	sprintf( buff,"color %s%s",bc,fc );
	system(buff);
	return 0;
}
