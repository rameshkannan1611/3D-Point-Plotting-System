//////////////////////////////////////////////////////////////
// Author Name              : Ramesh S
// Creation Date            : 30-March-2026
// Last Updated Date        : 03-June-2026
// Last Updated Time        : 23:20 IST
// Project                  : 3D Coordinate System
// Description              : A light application for plotting xyz points
//                            in 3D space
// Status                   : Under-Developing
//////////////////////////////////////////////////////////////



#ifndef __POINTPLOTTINGSYSTEM__
#define __POINTPLOTTINGSYSTEM__
#include "MyFrame.h"
#include <vector>

class MyApp : public wxApp {
public:
    bool OnInit() {
        MyFrame* frame = new MyFrame();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
#endif
