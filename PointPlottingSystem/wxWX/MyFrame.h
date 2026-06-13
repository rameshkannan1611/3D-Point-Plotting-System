
#ifndef __MYFR6AME__
#define __MYFRAME__

#include <wx/wx.h>
#include <MyGLCanvas.h>

class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    wxTextCtrl* xInput;
    wxTextCtrl* yInput;
    wxTextCtrl* zInput;
    wxTextCtrl* csvinput;
    MyGLCanvas* canvas;

    void OnAddPoint(wxCommandEvent&);
    void OnReadCSVAndAddPoints(wxCommandEvent&);
};

#endif