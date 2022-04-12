#pragma once
#include "wx/wx.h"

class Minesweeper : public wxFrame
{
public:
	Minesweeper();
	~Minesweeper();
	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

public:
	
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton **btn;
	int *Field = nullptr;
	bool firstClick = true;

	
};

