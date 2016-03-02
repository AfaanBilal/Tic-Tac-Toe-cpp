#include "main.h"
#include "TicTacToe.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

    TicTacToe *ttt = new TicTacToe(wxT("Tic Tac Toe"));
    ttt->Show(true);

    return true;
}
