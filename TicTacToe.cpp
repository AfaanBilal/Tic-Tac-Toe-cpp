#include "TicTacToe.h"


TicTacToe::TicTacToe(const wxString& title)
       : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(580, 640))
{
  SetBackgroundColour(wxColour(240,240,240));
   
  menubar = new wxMenuBar;
  menuGame = new wxMenu;
  
  menuGame->Append(new wxMenuItem(menuGame, ID_MNG, wxT("&New Game"), wxT("")));
  menuGame->Append(new wxMenuItem(menuGame, ID_MAB, wxT("&About"), wxT("")));
  menuGame->AppendSeparator();
  menuGame->Append(new wxMenuItem(menuGame, ID_MEX, wxT("E&xit"), wxT("")));
  
  menubar->Append(menuGame, wxT("&Game"));
  
  SetMenuBar(menubar);
  
  who = 'X';
  moves = 0;
  ComputerOpponent = false;
  hasAnyWon = false;
  
  scoreX = scoreO = scoreTies = 0;

  sizer = new wxBoxSizer(wxVERTICAL);
  
  player = new wxTextCtrl(this, ID_TP, wxT(" Current: Player 1 (X) "), wxPoint(-1, -1), wxSize(-1, -1), wxTE_CENTER | wxTE_READONLY);
  score = new wxTextCtrl(this, ID_TS, wxT("Score: Player X = 0  ||  Player O = 0  ||  Ties = 0"), wxPoint(-1, -1), wxSize(-1, -1), wxTE_CENTER | wxTE_READONLY);
  cCo = new wxCheckBox(this, ID_CCO, wxT("Against the Computer?"), wxPoint(-1, -1));
  
  bNew = new wxButton(this, ID_BNG, wxT("New Game"));
  
  b00 = new wxButton(this, ID_B00, wxT(""));
  b01 = new wxButton(this, ID_B01, wxT(""));
  b02 = new wxButton(this, ID_B02, wxT(""));
  b10 = new wxButton(this, ID_B10, wxT(""));
  b11 = new wxButton(this, ID_B11, wxT(""));
  b12 = new wxButton(this, ID_B12, wxT(""));
  b20 = new wxButton(this, ID_B20, wxT(""));
  b21 = new wxButton(this, ID_B21, wxT(""));
  b22 = new wxButton(this, ID_B22, wxT(""));
  
  wxFont df = wxFont(40, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
  wxFont dbf = wxFont(13, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
  wxFont scoreFont = wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
  
  wxStaticText *titleTextPart1 = new  wxStaticText(this, -1, wxT("A Game of"));
  titleTextPart1->SetFont(wxFont(14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  titleTextPart1->SetForegroundColour(wxColour(13, 132, 123));
  
  wxStaticText *titleText = new  wxStaticText(this, -1, wxT("Tic Tac Toe"));
  titleText->SetFont(wxFont(30, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  titleText->SetForegroundColour(wxColour(13, 132, 200));
  
  wxStaticText *authorText = new  wxStaticText(this, -1, wxT("by Afaan Bilal"));
  authorText->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  authorText->SetForegroundColour(wxColour(13, 132, 123));
    
  score->SetFont(scoreFont);
  score->SetForegroundColour(wxColour(80,80,80));  
  player->SetForegroundColour(wxColour(80,180,100));
  player->SetFont(dbf);
  bNew->SetFont(dbf);
  cCo->SetFont(dbf);
  
  b00->SetFont(df);
  b01->SetFont(df);
  b02->SetFont(df);
  b10->SetFont(df);
  b11->SetFont(df);
  b12->SetFont(df);
  b20->SetFont(df);
  b21->SetFont(df);
  b22->SetFont(df);
  
  sizer->Add(titleTextPart1, 0, wxALIGN_LEFT | wxALL, 10);
  sizer->Add(titleText, 0, wxALIGN_CENTER | wxALL, 10);
  sizer->Add(authorText, 0, wxALIGN_RIGHT | wxALL, 10);
  sizer->Add(score, 0, wxEXPAND | wxALL, 10);
  sizer->Add(player, 0, wxEXPAND | wxALL, 10);
  sizer->Add(cCo, 0, wxALIGN_CENTER | wxALL, 10);
  
  gs = new wxGridSizer(4, 3, 3, 3);
    
  gs->Add(new wxStaticText(this, -1, wxT("")), 0, wxALIGN_CENTER, 0);
  gs->Add(bNew, 0, wxEXPAND);
  gs->Add(new wxStaticText(this, -1, wxT("")), 0, wxALIGN_CENTER, 0);
  
  gs->Add(b00, 0, wxEXPAND); 
  gs->Add(b01, 0, wxEXPAND);
  gs->Add(b02, 0, wxEXPAND);
  gs->Add(b10, 0, wxEXPAND);
  gs->Add(b11, 0, wxEXPAND);
  gs->Add(b12, 0, wxEXPAND);
  gs->Add(b20, 0, wxEXPAND);
  gs->Add(b21, 0, wxEXPAND);
  gs->Add(b22, 0, wxEXPAND);

  sizer->Add(gs, 1, wxEXPAND);
  SetSizer(sizer);
  SetMinSize(wxSize(580, 640));
  
  Connect(ID_BNG, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TicTacToe::OnNewGame));
  Connect(ID_MNG, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TicTacToe::OnNewGame));
  Connect(ID_MAB, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TicTacToe::OnAbout));
  Connect(ID_MEX, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TicTacToe::OnExit));
  Connect(ID_CCO, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(TicTacToe::OnCCO));
  
  Connect(ID_B00, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TicTacToe::OnClick));
  Connect(ID_B01, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TicTacToe::OnClick));
  Connect(ID_B02, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TicTacToe::OnClick));
  Connect(ID_B10, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TicTacToe::OnClick));
  Connect(ID_B11, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TicTacToe::OnClick));
  Connect(ID_B12, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TicTacToe::OnClick));
  Connect(ID_B20, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TicTacToe::OnClick));
  Connect(ID_B21, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TicTacToe::OnClick));
  Connect(ID_B22, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TicTacToe::OnClick));
  
  Centre();
  Reset();
  DarkenButtons(true);
  EnableButtons(false);
}

void TicTacToe::OnCCO(wxCommandEvent& event)
{
    ComputerOpponent = cCo->GetValue();
    scoreX = scoreO = scoreTies = 0;
    UpdateScore();
    Reset();
}

void TicTacToe::DarkenButtons(bool e = true)
{
    wxColour clr = (e) ? wxColour(150,150,150) : wxColour(230, 230, 230) ;
    b00->SetBackgroundColour(clr);
    b01->SetBackgroundColour(clr);
    b02->SetBackgroundColour(clr);
    b10->SetBackgroundColour(clr);
    b11->SetBackgroundColour(clr);
    b12->SetBackgroundColour(clr);
    b20->SetBackgroundColour(clr);
    b21->SetBackgroundColour(clr);
    b22->SetBackgroundColour(clr);
}

void TicTacToe::EnableButtons(bool e = true)
{    
    b00->Enable(e);
    b01->Enable(e);
    b02->Enable(e);
    b10->Enable(e);
    b11->Enable(e);
    b12->Enable(e);
    b20->Enable(e);
    b21->Enable(e);
    b22->Enable(e);
}

void TicTacToe::Reset()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            v[i][j] = ' ';
    
    for (int i = 0; i < 9; i++)
        board[i] = '0';
        
    
    b00->SetLabel(wxT(""));
    b01->SetLabel(wxT(""));
    b02->SetLabel(wxT(""));
    b10->SetLabel(wxT(""));
    b11->SetLabel(wxT(""));
    b12->SetLabel(wxT(""));
    b20->SetLabel(wxT(""));
    b21->SetLabel(wxT(""));
    b22->SetLabel(wxT(""));
    
    DarkenButtons(false);    
    EnableButtons();
    
    who = 'X';
    moves = 0;
    hasAnyWon = false;
    
    player->Clear();
    player->WriteText(wxT(" Current: Player 1 (X) "));
}

bool TicTacToe::CheckIfDraw()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (v[i][j] == ' ')
               return false;

    return true;
}

bool TicTacToe::CheckIfWon()
{
    if (v[0][0] == who && v[0][1] == who && v[0][2] == who) { wl = H_1; return true; }
    if (v[1][0] == who && v[1][1] == who && v[1][2] == who) { wl = H_2; return true; }
    if (v[2][0] == who && v[2][1] == who && v[2][2] == who) { wl = H_3; return true; }
    if (v[0][0] == who && v[1][0] == who && v[2][0] == who) { wl = V_1; return true; }
    if (v[0][1] == who && v[1][1] == who && v[2][1] == who) { wl = V_2; return true; }
    if (v[0][2] == who && v[1][2] == who && v[2][2] == who) { wl = V_3; return true; }
    if (v[0][0] == who && v[1][1] == who && v[2][2] == who) { wl = D_1; return true; }
    if (v[0][2] == who && v[1][1] == who && v[2][0] == who) { wl = D_2; return true; }

    return false;
}

void TicTacToe::OnNewGame(wxCommandEvent& event)
{
    Reset();
} 

void TicTacToe::OnAbout(wxCommandEvent& event)
{
    AboutDialog *abt = new AboutDialog(wxT("About Tic Tac Toe"));
    abt->Show(true);
}

void TicTacToe::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void TicTacToe::OnClick(wxCommandEvent& event) 
{
  //b01->SetLabel(((wxButton*)event.GetEventObject())->GetLabel());
  wxButton *b = (wxButton*)event.GetEventObject();
  
  if (b->GetLabel() != wxT(""))
        return;
        
  wxString w = wxString::Format(wxT("%c"), who);
  b->SetLabel(w);
  
  
  if (ComputerOpponent && who == 'X') moves++;


  switch(event.GetId())
  {
        case ID_B00:
            board[0] = v[0][0] = who;
            if (ComputerOpponent) MakeMove(moves, new wxPoint(0, 0));
            break;
            
        case ID_B01:
            board[1] = v[0][1] = who;
            if (ComputerOpponent) MakeMove(moves, new wxPoint(0, 1));
            break;

        case ID_B02:
            board[2] = v[0][2] = who;
            if (ComputerOpponent) MakeMove(moves, new wxPoint(0, 2));
            break;

        case ID_B10:
            board[3] = v[1][0] = who;
            if (ComputerOpponent) MakeMove(moves, new wxPoint(1, 0));
            break;

        case ID_B11:
            board[4] = v[1][1] = who;
            if (ComputerOpponent) MakeMove(moves, new wxPoint(1, 1));
            break;

        case ID_B12:
            board[5] = v[1][2] = who;
            if (ComputerOpponent) MakeMove(moves, new wxPoint(1, 2));
            break;

        case ID_B20:
            board[6] = v[2][0] = who;
            if (ComputerOpponent) MakeMove(moves, new wxPoint(2, 0));
            break;

        case ID_B21:
            board[7] = v[2][1] = who;
            if (ComputerOpponent) MakeMove(moves, new wxPoint(2, 1));
            break;

        case ID_B22:
            board[8] = v[2][2] = who;
            if (ComputerOpponent) MakeMove(moves, new wxPoint(2, 2));
            break;
  }

  if (hasAnyWon) return;
  
  if (IsWinOrDraw()) return;
  
  if (!ComputerOpponent) UpdatePlayerInfo();  
  //event.Skip();
}

void TicTacToe::FillTheFirstBlank(wxString w)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == '0')
        {
            board[i] = who;
            switch (i)
            {
                case 0:
                    b00->SetLabel(w);
                    v[0][0] = who;
                    break;
                case 1:
                    b01->SetLabel(w);
                    v[0][1] = who;
                    break;
                case 2:
                    b02->SetLabel(w);
                    v[0][2] = who;
                    break;
                case 3:
                    b10->SetLabel(w);
                    v[1][0] = who;
                    break;
                case 4:
                    b11->SetLabel(w);
                    v[1][1] = who;
                    break;
                case 5:
                    b12->SetLabel(w);
                    v[1][2] = who;
                    break;
                case 6:
                    b20->SetLabel(w);
                    v[2][0] = who;
                    break;
                case 7:
                    b21->SetLabel(w);
                    v[2][1] = who;
                    break;
                case 8:
                    b22->SetLabel(w);
                    v[2][2] = who;
                    break;
            }
            
            break; 
        }
    }
}

void TicTacToe::UpdatePlayerInfo()
{
  who = (who == 'X') ? 'O' : 'X';
  int pl = (who == 'X') ? 1 : 2;
  wxString computerPlayer = (ComputerOpponent && pl == 2) ? wxT("(Computer)") : wxT("");
  wxString plinfo = wxString::Format(wxT(" Current: Player %i (%c) %s "), pl, who, computerPlayer.c_str());
  player->Clear();
  player->WriteText(plinfo);
}


bool TicTacToe::IsWinOrDraw()
{
  bool isWoD = false;
  
  if (CheckIfWon())
  { 
     isWoD = true;   
     int Player = (who == 'X') ? 1 : 2;
     switch (wl)
     {
        case H_1:
            b00->SetBackgroundColour(wxColour(*wxGREEN));
            b01->SetBackgroundColour(wxColour(*wxGREEN));
            b02->SetBackgroundColour(wxColour(*wxGREEN));
            break;
        case H_2:
            b10->SetBackgroundColour(wxColour(*wxGREEN));
            b11->SetBackgroundColour(wxColour(*wxGREEN));
            b12->SetBackgroundColour(wxColour(*wxGREEN));
            break;
        case H_3:
            b20->SetBackgroundColour(wxColour(*wxGREEN));
            b21->SetBackgroundColour(wxColour(*wxGREEN));
            b22->SetBackgroundColour(wxColour(*wxGREEN));
            break;
        case V_1:
            b00->SetBackgroundColour(wxColour(*wxGREEN));
            b10->SetBackgroundColour(wxColour(*wxGREEN));
            b20->SetBackgroundColour(wxColour(*wxGREEN));
            break;
        case V_2:
            b01->SetBackgroundColour(wxColour(*wxGREEN));
            b11->SetBackgroundColour(wxColour(*wxGREEN));
            b21->SetBackgroundColour(wxColour(*wxGREEN));
            break;
        case V_3:
            b02->SetBackgroundColour(wxColour(*wxGREEN));
            b12->SetBackgroundColour(wxColour(*wxGREEN));
            b22->SetBackgroundColour(wxColour(*wxGREEN));
            break;
        case D_1:
            b00->SetBackgroundColour(wxColour(*wxGREEN));
            b11->SetBackgroundColour(wxColour(*wxGREEN));
            b22->SetBackgroundColour(wxColour(*wxGREEN));
            break;
        case D_2:
            b02->SetBackgroundColour(wxColour(*wxGREEN));
            b11->SetBackgroundColour(wxColour(*wxGREEN));
            b20->SetBackgroundColour(wxColour(*wxGREEN));
            break;
     }
     who == 'X' ? scoreX++ : scoreO++;
     wxString msg = (ComputerOpponent && who == 'O') ? wxT("Oh no! The Computer (O) has won!") : wxString::Format(wxT("Congratulations, Player %i (%c) has won!"), Player, who);
     wxMessageDialog *dial = new wxMessageDialog(NULL, msg, wxT("TicTacToe"), wxOK);
     dial->ShowModal();
  } 
  else if (CheckIfDraw())
  {
      scoreTies++;
      isWoD = true;
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Sorry, the game is over as a draw!"), wxT("TicTacToe"), wxOK);
      dial->ShowModal();
  }
  
  if (isWoD) { UpdateScore(); EnableButtons(false); return true; }
  else { return false; }
}

void TicTacToe::UpdateScore()
{
    score->SetValue(wxString::Format("Score: Player X = %i  ||  Player O %s = %i  ||  Ties = %i", scoreX, ComputerOpponent ? wxT("(Computer)") : wxT(""), scoreO, scoreTies));
}

void TicTacToe::MakeMove(int move, wxPoint* p)
{
    bool madeMove = false;
    
    UpdatePlayerInfo();
    
    wxMilliSleep(300);
    
    if (CanWin() != -1) {
        WinIfCan();
        madeMove = true;
    } else if (HasToBlock() != -1) {
        BlockOpponent();
        madeMove = true;
    }
    
    if (madeMove) {
      if (IsWinOrDraw()) { hasAnyWon = true; return; }
      UpdatePlayerInfo();
      return;
    }
    
    wxString w = wxString::Format(wxT("%c"), who);
    
    switch (move)
    {
        case 1: // first move
            switch(p->x)
            {
                case 0:
                case 2:
                    b11->SetLabel(w);
                    board[4] = v[1][1] = who;
                    break;
                
                case 1:
                    if (p->y == 1) {
                        b00->SetLabel(w);
                        board[0] = v[0][0] = who;                    
                    } else {
                        b11->SetLabel(w);
                        board[4] = v[1][1] = who;                        
                    }
                    break;
            }             
            break;
        case 2: // second move
            switch (p->x)
            {
                case 0:
                    switch (p->y)
                    {
                        case 0:
                            if (board[8] == 'X' && board[4] == 'O') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            } else if (board[1] == 'X' && board[2] == '0') {
                                b02->SetLabel(w);
                                board[2] = v[0][2] = who;
                            } else if (board[2] == 'X' && board[1] == '0') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            } else if (board[4] == 'O' && board[6] == '0') {
                                b20->SetLabel(w);
                                board[6] = v[2][0] = who;
                            } else if (board[3] == '0') {
                                b10->SetLabel(w);
                                board[3] = v[1][0] = who;
                            }
                            break;
                        
                        case 1:
                            if (board[4] == 'O') {
                                if (board[0] == 'X' && board[2] == '0') {
                                    b02->SetLabel(w);
                                    board[2] = v[0][2] = who;
                                } else if (board[2] == 'X' && board[0] == '0') {
                                    b00->SetLabel(w);
                                    board[0] = v[0][0] = who;
                                } else {
                                    if (board[6] == '0') {
                                        b20->SetLabel(w);
                                        board[6] = v[2][0] = who;
                                    } else if (board[0] == '0') {
                                        b00->SetLabel(w);
                                        board[0] = v[0][0] = who;
                                    } else if (board[8] == '0') {
                                        b22->SetLabel(w);
                                        board[8] = v[2][2] = who;
                                    }
                                }
                            } else if (board[4] == 'X' && board[7] == '0') {
                                b21->SetLabel(w);
                                board[7] = v[2][1] = who;
                            } else if (board[4] == '0' && board[8] == '0' && board[0] == '0') {
                                b00->SetLabel(w);
                                board[0] = v[0][0] = who;
                            }
                            break;
                        
                        case 2:
                            if (board[6] == 'X' && board[4] == 'O') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            } else if (board[4] == 'O' && board[0] == 'X' && board[1] == '0') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            } else if (board[4] == 'X') {
                                b20->SetLabel(w);
                                board[6] = v[2][0] = who;
                            } else if (board[8] == 'X' && board[5] == '0') {
                                b12->SetLabel(w);
                                board[5] = v[1][2] = who;
                            } else if (board[5] == 'X' && board[8] == '0') {
                                b22->SetLabel(w);
                                board[8] = v[2][2] = who;
                            } else if (board[0] == '0') {
                                b00->SetLabel(w);
                                board[0] = v[0][0] = who;
                            } else if (board[3] == '0') {
                                b10->SetLabel(w);
                                board[3] = v[1][0] = who;
                            }
                    }
                    break;
                
                case 1:
                    switch (p->y)
                    {
                        case 0:
                            if (board[8] == 'X' && board[4] == 'O' && board[1] == '0') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            } else if (board[0] == 'X' && board[6] == '0') {
                                b20->SetLabel(w);
                                board[6] = v[2][0] = who;
                            } else if (board[4] == 'O' && board[3] != 'X' && board[5] == '0') {
                                b12->SetLabel(w);
                                board[5] = v[1][2] = who;
                            } else {
                                b02->SetLabel(w);
                                board[2] = v[0][2] = who;
                            }
                            break;
                        
                        // case 1: not needed
                        case 2:
                            if (board[4] == 'X' && board[3] == '0') {
                                b10->SetLabel(w);
                                board[3] = v[1][0] = who;
                            } else if (board[2] == '0') {
                                b02->SetLabel(w);
                                board[2] = v[0][2] = who;
                            } else {
                                b22->SetLabel(w);
                                board[8] = v[2][2] = who;
                            }
                            break;
                    }
                    break;
                
                case 2:
                    switch (p->y)
                    {
                        case 0:
                            if (board[1] == 'X' && board[4] == 'O' && board[5] == '0') {
                                b12->SetLabel(w);
                                board[5] = v[1][2] = who;
                            } else if (board[4] == 'X' && board[2] == '0') {
                                b02->SetLabel(w);
                                board[2] = v[0][2] = who;
                            } else if (board[0] == 'X' && board[3] == '0') {
                                b10->SetLabel(w);
                                board[3] = v[1][0] = who;
                            } else if (board[7] == 'X' || board[8] == 'X') {
                                if (board[8] == '0') {
                                    b22->SetLabel(w);
                                    board[8] = v[2][2] = who;
                                } else if (board[7] == '0') {
                                    b21->SetLabel(w);
                                    board[7] = v[2][1] = who;
                                } 
                            } else if (board[1] == '0') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            }   
                            break;
                        
                        case 1:
                            if (board[4] == 'X' && board[1] == '0') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            } else if (board[6] == 'X' || board[8] == 'X') {
                                if (board[8] == '0') {
                                    b22->SetLabel(w);
                                    board[8] = v[2][2] = who;
                                } else if (board[6] == '0') {
                                    b20->SetLabel(w);
                                    board[6] = v[2][0] = who;
                                }
                            } else {
                                b02->SetLabel(w);
                                board[2] = v[0][2] = who;
                            }
                            break;
                        
                        case 2:
                            if (board[1] == 'X' && board[4] == 'O') {
                                b10->SetLabel(w);
                                board[3] = v[1][0] = who;
                            } else if (board[2] == 'X' || board[5] == 'X') {
                                if (board[2] == '0') {
                                    b02->SetLabel(w);
                                    board[2] = v[0][2] = who;
                                } else if (board[5] == '0') {
                                    b12->SetLabel(w);
                                    board[5] = v[1][2] = who;
                                }
                            } else if (board[6] == 'X' || board[7] == 'X') {
                                if (board[6] == '0') {
                                    b20->SetLabel(w);
                                    board[6] = v[2][0] = who;
                                } else if (board[7] == '0') {
                                    b21->SetLabel(w);
                                    board[7] = v[2][1] = who;
                                }
                            } else if (board[7] == '0' && board[1] == '0'){
                                b21->SetLabel(w);
                                board[7] = v[2][1] = who;
                            } else {
                                b20->SetLabel(w);
                                board[6] = v[2][0] = who;
                            }
                            break;
                    }
                    break;
                                
            }                                
            break;
            
        case 3: // third move;
            switch(p->x)
            {
                case 0:
                    switch(p->y)
                    {
                        case 0: 
                            if (CanWin() != -1) {
                                WinIfCan();
                            } else if (board[4] == 'O') {
                                if (board[3] == 'X' && board[6] == '0') {
                                    b20->SetLabel(w);
                                    board[6] = v[2][0] = who;
                                } else if (board[6] == 'X' && board[3] == '0') {
                                    b10->SetLabel(w);
                                    board[3] = v[1][0] = who;
                                } else if (board[1] == 'X' && board[2] == '0') {
                                    b02->SetLabel(w);
                                    board[2] = v[0][2] = who;
                                } else if (board[2] == 'X' && board[1] == '0') {
                                    b01->SetLabel(w);
                                    board[1] = v[0][1] = who;
                                } else if (board[8] == 'X' && (board[2] == '0' || board[6] == '0')) { // fork protection
                                    if (board[1] == '0' && board[7] == '0') {
                                        b01->SetLabel(w);
                                        board[1] = v[0][1] = who;
                                    } else if (board[3] == '0' && board[5] == '0') {
                                        b10->SetLabel(w);
                                        board[3] = v[1][0] = who;
                                    }
                                } else if(board[6] == '0') {
                                    b20->SetLabel(w);
                                    board[6] = v[2][0] = who;
                                }
                                    
                            }
                            break;
                        
                        case 1:
                            if (board[4] == 'O' && board[0] == 'X' && board[2] == '0') {
                                b02->SetLabel(w);
                                board[2] = v[0][2] = who;
                            } else if (board[7] == '0') {
                                b21->SetLabel(w);
                                board[7] = v[2][1] = who;
                            }
                            break; 
                           
                        case 2:
                            if (board[4] == 'O') {
                                if (board[0] == 'X' && board[1] == '0') {
                                    b01->SetLabel(w);
                                    board[1] = v[0][1] = who;
                                } else if (board[1] == 'X' && board[0] == '0') {
                                    b00->SetLabel(w);
                                    board[0] = v[0][0] = who;
                                } else if (board[5] == 'X' && board[8] == '0') {
                                    b22->SetLabel(w);
                                    board[8] = v[2][2] = who;
                                } else if (board[8] == 'X' && board[5] == '0') {
                                    b12->SetLabel(w);
                                    board[5] = v[1][2] = who;
                                } else if (board[7] == '0') {
                                    b21->SetLabel(w);
                                    board[7] = v[2][1] = who;
                                } else if (board[0] == '0') {
                                    b00->SetLabel(w);
                                    board[0] = v[0][0] = who;
                                }                                    
                            } else if (board[6] == '0') {
                                b20->SetLabel(w);
                                board[6] = v[2][0] = who;
                            }
                            break;
                    }
                    break;
                
                case 1:
                    switch (p->y)
                    {
                        case 0:
                            if (CanWin() != -1) {
                                WinIfCan();
                            } else if (board[0] == 'X' && board[6] == '0') {
                                b20->SetLabel(w);
                                board[6] = v[2][0] = who;
                            } else if (board[6] == 'X' && board[0] == '0') {
                                b00->SetLabel(w);
                                board[0] = v[0][0] = who;
                            } else if (board[4] == 'X' && board[5] == '0') {
                                b12->SetLabel(w);
                                board[5] = v[1][2] = who;
                            } else if (board[8] == '0') {
                                b22->SetLabel(w);
                                board[8] = v[2][2] = who;
                            } else if (board[7] == '0') {
                                b21->SetLabel(w);
                                board[7] = v[2][1] = who;
                            } 
                            break;
                        
                        //case 1: not needed
                        
                        case 2:
                            if (CanWin() != -1) {
                                WinIfCan();
                            } else if (board[4] == 'X' && board[3] == '0') {
                                b10->SetLabel(w);
                                board[3] = v[1][0] = who;
                            } else if (board[2] == 'X' && board[8] == '0') {
                                b22->SetLabel(w);
                                board[8] = v[2][2] = who;
                            } else if (board[8] == 'X' && board[2] == '0') {
                                b02->SetLabel(w);
                                board[8] = v[0][2] = who;
                            } else if (board[6] == '0') {
                                b20->SetLabel(w);
                                board[6] = v[2][0] = who;
                            } else if (board[1] == '0') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            }
                            break;
                    }
                    break;
                    
                case 2:
                    switch (p->y)
                    {
                        case 0:
                            if (CanWin() != -1) {
                                WinIfCan();
                            } else if (board[4] == 'X' && board[2] == '0') {
                                b02->SetLabel(w);
                                board[2] = v[0][2] = who;
                            } else if (board[3] == 'X' && board[0] == '0') {
                                b00->SetLabel(w);
                                board[0] = v[0][0] = who;
                            } else if (board[0] == 'X' && board[3] == '0') {
                                b10->SetLabel(w);
                                board[3] = v[1][0] = who;
                            } else if (board[7] == 'X' && board[8] == '0') {
                                b22->SetLabel(w);
                                board[8] = v[2][2] = who;
                            } else if (board[8] == 'X' && board[7] == '0') {
                                b21->SetLabel(w);
                                board[7] = v[2][1] = who;
                            } else if (board[0] == '0') {
                                b00->SetLabel(w);
                                board[0] = v[0][0] = who;
                            } else if (board[7] == '0') {
                                b21->SetLabel(w);
                                board[7] = v[2][1] = who;
                            } else if (board[1] == '0') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            }                                
                            break;
                            
                        case 1:
                            if (CanWin() != -1) {
                                WinIfCan();
                            } else if (board[4] == 'X' && board[1] == '0') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            } else if (board[6] == 'X' && board[8] == '0') {
                                b22->SetLabel(w);
                                board[8] = v[2][2] = who;
                            } else if (board[8] == 'X' && board[6] == '0') {
                                b20->SetLabel(w);
                                board[6] = v[2][0] = who;
                            } else if (board[2] == '0') {
                                b02->SetLabel(w);
                                board[2] = v[0][2] = who;
                            } else if (board[0] == '0') {
                                b00->SetLabel(w);
                                board[0] = v[0][0] = who;
                            } else if (board[1] == '0') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            }
                            break;
                            
                        case 2:
                            if (CanWin() != -1) {
                                WinIfCan();
                            } else if (board[4] == 'X' && board[0] == '0') {
                                b00->SetLabel(w);
                                board[0] = v[0][0] = who;
                            } else if (board[7] == 'X' && board[6] == '0') {
                                b20->SetLabel(w);
                                board[6] = v[2][0] = who;
                            } else if (board[6] == 'X' && board[7] == '0') {
                                b21->SetLabel(w);
                                board[7] = v[2][1] = who;
                            } else if (board[5] == 'X' && board[2] == '0') {
                                b02->SetLabel(w);
                                board[2] = v[0][2] = who;
                            } else if (board[2] == 'X' && board[5] == '0') {
                                b12->SetLabel(w);
                                board[5] = v[1][2] = who;
                            } else if (board[0] == '0') {
                                b00->SetLabel(w);
                                board[0] = v[0][0] = who;
                            } else if (board[7] == '0') {
                                b21->SetLabel(w);
                                board[7] = v[2][1] = who;
                            } else if (board[1] == '0') {
                                b01->SetLabel(w);
                                board[1] = v[0][1] = who;
                            } else if (board[6] == '0') {
                                b20->SetLabel(w);
                                board[6] = v[2][0] = who;
                            }
                            break;                        
                    }                    
                    break;
            }
            break;
        
        // fourth move
        case 4:
            FillTheFirstBlank(w);
            break;
                
    }
        
    
    if (IsWinOrDraw()) { hasAnyWon = true; return; }
    UpdatePlayerInfo();
}

int TicTacToe::CanWin()
{
    if (board[0] == 'O' && board[1] == 'O' && board[2] == '0') return 2;
    if (board[0] == 'O' && board[2] == 'O' && board[1] == '0') return 1;
    if (board[0] == 'O' && board[4] == 'O' && board[8] == '0') return 8;
    if (board[0] == 'O' && board[3] == 'O' && board[6] == '0') return 6;
    if (board[0] == 'O' && board[6] == 'O' && board[3] == '0') return 3;
    if (board[1] == 'O' && board[2] == 'O' && board[0] == '0') return 0;
    if (board[1] == 'O' && board[4] == 'O' && board[7] == '0') return 7;
    if (board[2] == 'O' && board[5] == 'O' && board[8] == '0') return 8;
    if (board[2] == 'O' && board[4] == 'O' && board[6] == '0') return 6;
    if (board[3] == 'O' && board[6] == 'O' && board[0] == '0') return 0;
    if (board[3] == 'O' && board[4] == 'O' && board[5] == '0') return 5;
    if (board[5] == 'O' && board[8] == 'O' && board[2] == '0') return 2;
    if (board[5] == 'O' && board[4] == 'O' && board[3] == '0') return 3;
    if (board[6] == 'O' && board[3] == 'O' && board[0] == '0') return 0;
    if (board[6] == 'O' && board[4] == 'O' && board[2] == '0') return 2;
    if (board[6] == 'O' && board[7] == 'O' && board[8] == '0') return 8;
    if (board[6] == 'O' && board[8] == 'O' && board[7] == '0') return 7;
    if (board[7] == 'O' && board[8] == 'O' && board[6] == '0') return 6;
    if (board[7] == 'O' && board[4] == 'O' && board[1] == '0') return 1;
    if (board[8] == 'O' && board[6] == 'O' && board[7] == '0') return 7;
    if (board[8] == 'O' && board[4] == 'O' && board[0] == '0') return 0;
    if (board[8] == 'O' && board[2] == 'O' && board[5] == '0') return 5;
    
    return -1;        
}

void TicTacToe::WinIfCan()
{
    wxString w = wxString::Format(wxT("%c"), who);
    switch (CanWin())
    {
        case 0:
            b00->SetLabel(w);
            board[0] = v[0][0] = who;
            break;
        case 1:
            b01->SetLabel(w);
            board[1] = v[0][1] = who;
            break;
        case 2:
            b02->SetLabel(w);
            board[2] = v[0][2] = who;
            break;
        case 3:
            b10->SetLabel(w);
            board[3] = v[1][0] = who;
            break;
        case 5:
            b12->SetLabel(w);
            board[5] = v[1][2] = who;
            break;
        case 6:
            b20->SetLabel(w);
            board[6] = v[2][0] = who;
            break;
        case 7:
            b21->SetLabel(w);
            board[7] = v[2][1] = who;
            break;
        case 8:
            b22->SetLabel(w);
            board[8] = v[2][2] = who;
            break;
    }
}

int TicTacToe::HasToBlock()
{
    if (board[0] == 'X' && board[1] == 'X' && board[2] == '0') return 2;
    if (board[0] == 'X' && board[2] == 'X' && board[1] == '0') return 1;
    if (board[0] == 'X' && board[4] == 'X' && board[8] == '0') return 8;
    if (board[0] == 'X' && board[3] == 'X' && board[6] == '0') return 6;
    if (board[0] == 'X' && board[6] == 'X' && board[3] == '0') return 3;
    if (board[1] == 'X' && board[2] == 'X' && board[0] == '0') return 0;
    if (board[1] == 'X' && board[4] == 'X' && board[7] == '0') return 7;
    if (board[2] == 'X' && board[5] == 'X' && board[8] == '0') return 8;
    if (board[2] == 'X' && board[4] == 'X' && board[6] == '0') return 6;
    if (board[3] == 'X' && board[6] == 'X' && board[0] == '0') return 0;
    if (board[3] == 'X' && board[4] == 'X' && board[5] == '0') return 5;
    if (board[5] == 'X' && board[8] == 'X' && board[2] == '0') return 2;
    if (board[5] == 'X' && board[4] == 'X' && board[3] == '0') return 3;
    if (board[6] == 'X' && board[3] == 'X' && board[0] == '0') return 0;
    if (board[6] == 'X' && board[4] == 'X' && board[2] == '0') return 2;
    if (board[6] == 'X' && board[7] == 'X' && board[8] == '0') return 8;
    if (board[6] == 'X' && board[8] == 'X' && board[7] == '0') return 7;
    if (board[7] == 'X' && board[8] == 'X' && board[6] == '0') return 6;
    if (board[7] == 'X' && board[4] == 'X' && board[1] == '0') return 1;
    if (board[8] == 'X' && board[6] == 'X' && board[7] == '0') return 7;
    if (board[8] == 'X' && board[4] == 'X' && board[0] == '0') return 0;
    if (board[8] == 'X' && board[2] == 'X' && board[5] == '0') return 5;
    
    return -1;        
}

void TicTacToe::BlockOpponent()
{
    wxString w = wxString::Format(wxT("%c"), who);
    switch (HasToBlock())
    {
        case 0:
            b00->SetLabel(w);
            board[0] = v[0][0] = who;
            break;
        case 1:
            b01->SetLabel(w);
            board[1] = v[0][1] = who;
            break;
        case 2:
            b02->SetLabel(w);
            board[2] = v[0][2] = who;
            break;
        case 3:
            b10->SetLabel(w);
            board[3] = v[1][0] = who;
            break;
        case 5:
            b12->SetLabel(w);
            board[5] = v[1][2] = who;
            break;
        case 6:
            b20->SetLabel(w);
            board[6] = v[2][0] = who;
            break;
        case 7:
            b21->SetLabel(w);
            board[7] = v[2][1] = who;
            break;
        case 8:
            b22->SetLabel(w);
            board[8] = v[2][2] = who;
            break;
    }
}





