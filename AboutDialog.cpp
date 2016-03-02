#include "AboutDialog.h"

AboutDialog::AboutDialog(const wxString & title)
       : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(260, 260))
{
  sizer = new wxBoxSizer(wxVERTICAL);
  
  wxStaticText *titleText = new  wxStaticText(this, -1, wxT("Tic Tac Toe"));
  titleText->SetFont(wxFont(30, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  titleText->SetForegroundColour(wxColour(13, 132, 200));
  
  wxStaticText *authorText = new  wxStaticText(this, -1, wxT("(c) 2014 Afaan Bilal"));
  authorText->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  authorText->SetForegroundColour(wxColour(13, 132, 123));
  
  wxStaticText *descText = new  wxStaticText(this, -1, wxT("This is a small game built in C++ primarily to help me learn wxWidgets."), wxDefaultPosition, wxSize(-1, 40));
  descText->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  descText->SetForegroundColour(wxColour(60, 60, 60));
  
  wxStaticText *linkText = new  wxStaticText(this, -1, wxT("www.coderevolution.tk\ngoogle.com/+AfaanBilal"), wxDefaultPosition, wxSize(-1, 40));
  linkText->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  linkText->SetForegroundColour(wxColour(13, 132, 143));
      
  sizer->Add(titleText, 0, wxALIGN_CENTER | wxALL, 10);
  sizer->Add(authorText, 0, wxALIGN_CENTER | wxALL, 10);
  sizer->Add(descText, 0, wxALIGN_LEFT | wxALL, 10);
  sizer->Add(linkText, 0, wxALIGN_LEFT | wxALL, 10);
 
  SetSizer(sizer);
    
  Centre();
  ShowModal();
  Destroy(); 
}

