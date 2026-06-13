#include "MyGLCanvas.h"

wxBEGIN_EVENT_TABLE(MyGLCanvas, wxGLCanvas)
EVT_PAINT(MyGLCanvas::OnPaint)
wxEND_EVENT_TABLE()

MyGLCanvas::MyGLCanvas(wxWindow* parent)
    : wxGLCanvas(parent, wxID_ANY), context(this) 
{
    Bind(wxEVT_LEFT_DOWN, &MyGLCanvas::OnMouseDown, this);
    Bind(wxEVT_LEFT_UP, &MyGLCanvas::OnMouseUp, this);

    Bind(wxEVT_RIGHT_DOWN, &MyGLCanvas::OnRightDown, this);
    Bind(wxEVT_RIGHT_UP, &MyGLCanvas::OnRightUp, this);

    Bind(wxEVT_MOTION, &MyGLCanvas::OnMouseMove, this);
    Bind(wxEVT_MOUSEWHEEL, &MyGLCanvas::OnMouseWheel, this);
}
void MyGLCanvas::AddPoint(float x, float y, float z) 
{
    points.push_back({ x, y, z });
    Refresh(); // trigger redraw
}
void MyGLCanvas::OnMouseDown(wxMouseEvent& event) 
{
    rotating = true;
    lastMousePos = event.GetPosition();
}
void MyGLCanvas::OnMouseUp(wxMouseEvent& event) 
{
    rotating = false;
}
void MyGLCanvas::OnRightDown(wxMouseEvent& event) 
{
    panning = true;
    lastMousePos = event.GetPosition();
}
void MyGLCanvas::OnRightUp(wxMouseEvent& event) 
{
    panning = false;
}
void MyGLCanvas::OnMouseMove(wxMouseEvent& event) 
{

    if (!event.Dragging())
        return;

    wxPoint pos = event.GetPosition();

    float dx = pos.x - lastMousePos.x;
    float dy = pos.y - lastMousePos.y;

    if (rotating) {
        angleY += dx * 0.5f;
        angleX += dy * 0.5f;
    }

    if (panning) {
        float panSpeed = 0.002f * zoom;
        panX += dx * panSpeed;
        panY -= dy * panSpeed;
    }

    lastMousePos = pos;
    Refresh();
}
void MyGLCanvas::OnMouseWheel(wxMouseEvent& event) 
{
    int rotation = event.GetWheelRotation();

    zoom -= rotation * 0.001f;

    if (zoom < 1.0f) zoom = 1.0f;
    if (zoom > 100.0f) zoom = 100.0f;

    Refresh();
}
void MyGLCanvas::OnPaint(wxPaintEvent&) 
{
    wxPaintDC dc(this);
    SetCurrent(context);

    int width = GetSize().x;
    int height = GetSize().y;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // =========================
    // 1. MAIN SCENE (FULL VIEW)
    // =========================
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float ratio = (float)width / height;
    glFrustum(-ratio, ratio, -1, 1, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Camera
    glTranslatef(0, 0, -zoom);
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    //glTranslatef(panX, panY, 0);
    float radY = angleY * 3.14159f / 180.0f;
    float radX = angleX * 3.14159f / 180.0f;

    // camera right vector
    float rightX = cos(radY);
    float rightZ = -sin(radY);

    // camera up vector
    float upX = sin(radX) * sin(radY);
    float upY = cos(radX);
    float upZ = sin(radX) * cos(radY);

    glTranslatef(
        panX * rightX + panY * upX,
        panY * upY,
        panX * rightZ + panY * upZ
    );

    // ---- DRAW POINTS ONLY ----
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    for (auto& p : points) {
        glColor3f(1, 1, 0);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    glDisable(GL_DEPTH_TEST);
    // ===================================
    // 2. SMALL AXIS VIEW (BOTTOM-LEFT)
    // ===================================

    int miniSize = 120; // size of axis widget

    glViewport(10, 10, miniSize, miniSize); // bottom-left corner

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Keep same rotation, NO pan, NO zoom
    glTranslatef(0, 0, -3);
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);

    // Disable depth interference from main scene
    glClear(GL_DEPTH_BUFFER_BIT);

    // Draw axes
    glBegin(GL_LINES);

    // X axis (red)
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    // Y axis (green)
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    // Z axis (blue)
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();

    glFlush();
    SwapBuffers();
}
