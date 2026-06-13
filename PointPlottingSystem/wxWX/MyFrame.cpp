#include "MyFrame.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "3D Plotter", wxDefaultPosition,wxSize(800, 600)) {

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Left panel (controls)
	wxPanel* panel = new wxPanel(this,wxID_ANY, wxDefaultPosition, wxSize(100, 100));
	wxBoxSizer* panelsizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vbox = new wxBoxSizer(wxHORIZONTAL);

	xInput = new wxTextCtrl(panel, wxID_ANY);
	yInput = new wxTextCtrl(panel, wxID_ANY);
	zInput = new wxTextCtrl(panel, wxID_ANY);

	wxButton* plotbtn = new wxButton(panel, wxID_ANY, "Plot Point");

	vbox->Add(new wxStaticText(panel, wxID_ANY, "X:"), 0);
	vbox->Add(xInput, 0);
	vbox->Add(new wxStaticText(panel, wxID_ANY, "Y:"), 0);
	vbox->Add(yInput, 0);
	vbox->Add(new wxStaticText(panel, wxID_ANY, "Z:"), 0);
	vbox->Add(zInput, 0);
	vbox->Add(plotbtn, 0, wxLEFT, 10);

	wxBoxSizer* csv = new wxBoxSizer(wxHORIZONTAL);

	csvinput = new wxTextCtrl(panel, wxID_ANY);

	wxButton* readbtn = new wxButton(panel, wxID_ANY, "Read Points");

	csv->Add(new wxStaticText(panel, wxID_ANY, "CSV:"), 0);
	csv->Add(csvinput, 0, wxEXPAND);
	csv->Add(readbtn, 0, wxLEFT, 10);

	panelsizer->Add(vbox, 0, wxTOP, 5);
	panelsizer->Add(csv, 0, wxTOP, 5);

	panel->SetSizer(panelsizer);

	// OpenGL canvas
	canvas = new MyGLCanvas(this);

	mainSizer->Add(canvas, 1, wxEXPAND);
	mainSizer->Add(panel, 0, wxEXPAND | wxALL, 10);

	SetSizer(mainSizer);

	// Button event
	plotbtn->Bind(wxEVT_BUTTON, &MyFrame::OnAddPoint, this);
	readbtn->Bind(wxEVT_BUTTON, &MyFrame::OnReadCSVAndAddPoints, this);
}

void MyFrame::OnAddPoint(wxCommandEvent&) {
	if (xInput->IsEmpty() || yInput->IsEmpty() || zInput->IsEmpty())
		return;
	float x = std::stof(xInput->GetValue().ToStdString());
	float y = std::stof(yInput->GetValue().ToStdString());
	float z = std::stof(zInput->GetValue().ToStdString());

	canvas->AddPoint(x, y, z);
}
void MyFrame::OnReadCSVAndAddPoints(wxCommandEvent&)
{
	if (csvinput->IsEmpty())
		return;
	std::string strCSV = csvinput->GetValue().ToStdString();

	if (strCSV.empty())
		return;

	std::ifstream file("points.csv");

	std::string line;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		float x, y, z;
		char comma;

		ss >> x >> comma
			>> y >> comma
			>> z;

		canvas->AddPoint(x, y, z);
	}

}