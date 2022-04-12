#include "Minesweeper.h"
wxBEGIN_EVENT_TABLE(Minesweeper, wxFrame)
EVT_BUTTON(10000, OnButtonClicked)
wxEND_EVENT_TABLE()

Minesweeper::Minesweeper() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(200, 200), wxSize(600, 400))
{
	btn = new wxButton * [nFieldWidth * nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	Field = new int[nFieldWidth * nFieldHeight];
	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
		{
			btn[y * nFieldHeight + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Minesweeper::OnButtonClicked, this);
			Field[y * nFieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();

}


Minesweeper:: ~Minesweeper()
{
	delete[] btn;
}

void Minesweeper::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;
	if (firstClick)
	{
		int mines = 30;

		while (mines)
		{
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			if (Field[ry * nFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				Field[ry * nFieldWidth + rx] = -1;
				mines--;
			}
		}
		firstClick = false;
	}
	btn[y * nFieldWidth + x]->Enable(false);

	if (Field[y * nFieldWidth + x] == -1)
	{
		wxMessageBox("KABOOM BRO!! - Nice try, Game over.");

		firstClick = true;
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y < nFieldHeight; y++)
			{
				Field[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
			}
		}
	}
	else 
	{
		int mine_count = 0;
		for(int i = -1; i<2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (x + 1 >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
					if (Field[(y + j) * nFieldHeight + (x + i)] == -1)
						mine_count++;

			}

		if (mine_count > 0)
		{
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
	}
	evt.Skip();
}