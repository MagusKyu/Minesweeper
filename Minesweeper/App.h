#pragma once
#include "wx/wx.h"
class Minesweeper;

class App: public wxApp
{
private:
	Minesweeper* minesweeper = nullptr;
public:
	App();
	~App();
	 bool OnInit();
};

