#include "App.h"
#include "Minesweeper.h"

wxIMPLEMENT_APP(App);

App::App()
{

}

App::~App() {

}

bool App::OnInit()
{
	minesweeper = new Minesweeper();
	minesweeper->Show();
	return true;
}