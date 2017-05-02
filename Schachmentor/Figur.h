#pragma once
class Figur
{
public:
	Figur();
	~Figur();
	void setTyp(char typ);
	void setPosx(int posx);
	void setPosy(int posy);
	char getTyp();
	int getPosx();
	int getPosy();
private:
	char typ;
	int posx;
	int posy;
};

