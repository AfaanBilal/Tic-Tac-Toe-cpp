#include <wx/wx.h>
#include "AboutDialog.h"

enum WinLine
{
    H_1,
    H_2,
    H_3,
    V_1,
    V_2,
    V_3,
    D_1,
    D_2
};

class TicTacToe : public wxFrame
{
public:
  TicTacToe(const wxString& title);
  void OnClick(wxCommandEvent& event);
  void OnNewGame(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnCCO(wxCommandEvent& event);
  void EnableButtons(bool e);
  void DarkenButtons(bool e);
  void Reset();
  bool IsWinOrDraw();
  void UpdatePlayerInfo();
  void MakeMove(int move, wxPoint* p);
  void WinIfCan();
  void FillTheFirstBlank(wxString w);
  int HasToBlock();
  void BlockOpponent();
  int CanWin();
  bool CheckIfWon();
  bool CheckIfDraw();
  void UpdateScore();

  wxMenuBar *menubar;
  wxMenu *menuGame;

  wxBoxSizer *sizer;
  wxGridSizer *gs;
  wxTextCtrl *player;
  wxTextCtrl *score;
  int scoreX, scoreO, scoreTies;
  wxCheckBox *cCo;
  wxButton *bNew;
  wxButton *b00, *b01, *b02, *b10, *b11, *b12, *b20, *b21, *b22;
  char who;
  char v[3][3];
  int moves;
  char board[9];
  bool ComputerOpponent, hasAnyWon;
  WinLine wl;
};

const int ID_TP = 100;
const int ID_TS = 101;
const int ID_BNG = 102;
const int ID_MNG = 103;
const int ID_MAB = 104;
const int ID_MEX = 105;
const int ID_CCO = 106;

const int ID_B00 = 200;
const int ID_B01 = 201;
const int ID_B02 = 202;
const int ID_B10 = 210;
const int ID_B11 = 211;
const int ID_B12 = 212;
const int ID_B20 = 220;
const int ID_B21 = 221;
const int ID_B22 = 222;
