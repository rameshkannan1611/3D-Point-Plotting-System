
#ifndef __MYGLCANVAS__
#define __MYGLCANVAS__

#include <wx/wx.h>
#include <wx/glcanvas.h>

struct Point 
{
    float x, y, z;
};


class MyGLCanvas : public wxGLCanvas {
public:
    MyGLCanvas(wxWindow* parent);

    void AddPoint(float x, float y, float z);
    void OnMouseDown(wxMouseEvent& event);
    void OnMouseUp(wxMouseEvent& event);

    void OnRightDown(wxMouseEvent& event);

    void OnRightUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseWheel(wxMouseEvent& event);
private:
    wxGLContext context;
    std::vector<Point> points;

    void OnPaint(wxPaintEvent&);

    float angleX = 20.0f;
    float angleY = 30.0f;
    float zoom = 10.0f;

    float panX = 0.0f;
    float panY = 0.0f;

    bool rotating = false;
    bool panning = false;

    wxPoint lastMousePos;
    wxDECLARE_EVENT_TABLE();
};

#endif