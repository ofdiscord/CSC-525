/*==================================================================================================
 PROGRAMMERS: Matthew Wilson and Garren Ijames
 COURSE: CSC 525/625
 MODIFIED BY: Matthew Wilson and Garren Ijames
 LAST MODIFIED DATE: 10/12/2016

 CONTRIBUTIONS:
		Matt - 50%
			Main Documentation
			Frame Buffer Output
			Circle Drawing
			Light Saber and Its Glow
			Bitmap Drawing

		Garren - 50%
			Base Image Creation
			Pixelmap Drawing
			Polygon w/ Stipple
			Text
			Lazers and Their Animations

 DESCRIPTION: Project 1 - Demonstrate Basic OpenGL Functionality
 NOTE: Light Sabre Deploy and Glow. Animated lazers.
 FILES: project1.cpp
 IDE/COMPILER: Visual Studio 2013
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on projProject.sln		to OPEN the project
	2.		Press Ctrl+F7						to COMPILE
	3.		Press Ctrl+Shift+B					to BUILD (COMPILE+LINK)
	4.		Press Ctrl+F5						to EXECUTE
==================================================================================================*/
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h> // include GLUT library
#include <fstream>
#include <cmath>
#include <string>

using std::ifstream;
using std::ofstream;
using std::floor;
using std::string;
using std::floor;
using std::cout;

// Global variables for pixel images
GLfloat pixelMap[512][512][3]; //holds pixel info for image to display
GLfloat pixelData[512 * 512 * 3]; //holds pixel info for image to output to text

// Global variable for polygon pattern
GLubyte polygonPattern[128] = {
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x01, 0xc0, 0x00,
		0x00, 0x1f, 0xfc, 0x00,
		0x00, 0x78, 0x8f, 0x00,
		0x00, 0xe3, 0xe3, 0x80,
		0x01, 0x83, 0xe0, 0xc0,
		0x03, 0xdf, 0xfd, 0xe0,
		0x06, 0xfe, 0x3f, 0xb0,
		0x06, 0x76, 0x37, 0x30,
		0x0c, 0xe7, 0x73, 0x98,
		0x0c, 0xc3, 0x61, 0x98,
		0x08, 0xf0, 0x07, 0x88,
		0x0b, 0xf8, 0x0f, 0xe8,
		0x1b, 0x98, 0x0c, 0xec,
		0x1f, 0x80, 0x00, 0xfc,
		0x1b, 0x98, 0x0c, 0xec,
		0x0b, 0xf8, 0x0f, 0xe8,
		0x08, 0xf0, 0x07, 0x88,
		0x0c, 0xc3, 0x61, 0x98,
		0x0c, 0xe7, 0x73, 0x98,
		0x06, 0x76, 0x37, 0x30,
		0x06, 0xfe, 0x3f, 0xb0,
		0x03, 0xdf, 0xfd, 0xe0,
		0x01, 0x83, 0xe0, 0xc0,
		0x00, 0xe3, 0xe3, 0x80,
		0x00, 0x78, 0x8f, 0x00,
		0x00, 0x1f, 0xfc, 0x00,
		0x00, 0x01, 0xc0, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
};

//!!!!!! Must replace with apropo bitmap. This just for testing !!!!!!
//bitmap image of man converted into hex
GLubyte rasters[260] = {
	0x01, 0x80, 0x00, 0x00,
	0x01, 0xE0, 0x00, 0x00,
	0x01, 0xff, 0xc0, 0x00,
	0x00, 0x0f, 0xc0, 0x00,

	0x07, 0x00, 0x80, 0x00,
	0xfc, 0x00, 0xc0, 0x00,
	0x3f, 0x00, 0xc0, 0x00,
	0x03, 0xc0, 0xc0, 0x00,

	0x00, 0xc0, 0x80, 0x00,
	0x00, 0xc1, 0xc0, 0x00,
	0x00, 0xc1, 0x80, 0x00,
	0x00, 0xc3, 0x00, 0x00,

	0x00, 0xc3, 0x00, 0x00,
	0x00, 0xc6, 0x00, 0x00,
	0x00, 0x86, 0x00, 0x00,
	0x00, 0x8e, 0x00, 0x00,

	0x00, 0x8c, 0x00, 0x00,
	0x01, 0x8c, 0x00, 0x00,
	0x01, 0x9c, 0x00, 0x00,
	0x01, 0x9c, 0x00, 0x00,

	0x01, 0x9c, 0x00, 0x00,
	0x01, 0xdc, 0x00, 0x00,
	0x01, 0xdc, 0x00, 0x00,
	0x01, 0xfc, 0x00, 0x00,

	0x01, 0xfc, 0x00, 0x00,
	0x01, 0xfe, 0x70, 0x00,
	0x01, 0xfe, 0xc0, 0x00,
	0x03, 0xff, 0x80, 0x00,

	0x03, 0xff, 0x00, 0x00,
	0x03, 0xff, 0x00, 0x00,
	0x03, 0xfd, 0xfc, 0x00,
	0x03, 0xf8, 0x03, 0x00,

	0x03, 0xf8, 0x03, 0x00,
	0x03, 0xf8, 0x06, 0x00,
	0x03, 0xf8, 0x0c, 0x00,
	0x03, 0xf8, 0x18, 0x00,

	0x03, 0xfc, 0x30, 0x00,
	0x01, 0xfc, 0x60, 0x00,
	0x01, 0xfe, 0xe0, 0x00,
	0x01, 0xff, 0xc0, 0x00,

	0x01, 0xff, 0x80, 0x00,
	0x03, 0xff, 0x80, 0x00,
	0x07, 0xff, 0x00, 0x00,
	0x0f, 0x80, 0x00, 0x00,

	0x0f, 0x01, 0x00, 0x00,
	0x1e, 0x3c, 0x00, 0x00,
	0x1c, 0x3f, 0x00, 0x00,
	0x38, 0x3f, 0x80, 0x00,

	0x70, 0x7f, 0xc0, 0x00,
	0x61, 0xff, 0xe0, 0x00,
	0x60, 0x3f, 0xf0, 0x00,
	0xe0, 0x3f, 0xf0, 0x00,

	0xe0, 0x1f, 0xf0, 0x00,
	0xe0, 0x1f, 0xf0, 0x00,
	0xf0, 0x0f, 0xf0, 0x00,
	0x3f, 0xf7, 0xf0, 0x00,

	0x01, 0xf3, 0xf0, 0x00,
	0x00, 0x11, 0xe0, 0x00,
	0x00, 0x18, 0x06, 0x00,
	0x00, 0x0f, 0x00, 0x00,

	0x00, 0x00, 0x01, 0x00,
	0x00, 0x00, 0x01, 0xe0,
	0x00, 0x00, 0x00, 0x20,
	0x00, 0x00, 0x00, 0x20,

	0x00, 0x00, 0x00, 0xe0

};

//This function captures the frame buffer and outputs pixel data to a text file
void PixelDataOutput(){
	//gather frame buffer pixel data
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, 512, 512, GL_RGB, GL_FLOAT, pixelData);

	//open stream to text file for output
	ofstream pixOutStream;
	pixOutStream.open("C:\\Temp\\savedImg.txt");

	//write formatted data to text file
	for (int i = 0; i < (512 * 512 * 3); i++){
		pixOutStream << pixelData[i];
		pixOutStream << " ";
	}
}

//This function manages line segment drawing for lazers 
void DrawLazers(){
	//set line preferences
	glColor3f(1, 0, 0);
	glLineWidth(3);

	//draw lines
	glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(10, 10);
		glVertex2f(50, 50);
		glVertex2f(45, 45);
	glEnd();
}

//This function manages Bitmap drawing
void DrawBitman(){
	//set color
	glColor3f(.5, 0, .3);
	//draw bitmap image
	glRasterPos2i(-100, -100);
	glBitmap(27, 65, 0.0, 0.0, 32, 0, rasters);
}

void DrawBackground()
{
	// Enable polygon stipple for later use of pattern
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_STIPPLE);

	// Draw background image
	glRasterPos2i(-256, -256);
	glDrawPixels(512, 512, GL_RGB, GL_FLOAT, pixelMap);

	// Draw title text
	string titleText = "\"I said I wanted it black\"";
	int strWidth = 0;

	for (int i = 0; i < titleText.size(); i++) // acquire width
		strWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, titleText[i]);

	int offset = floor(strWidth / 2);

	glColor3f(1, 1, 1);
	glRasterPos2i(-offset, 30);

	for (int i = 0; i < titleText.size(); i++) // title text
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, titleText[i]);

	// Draw polygon pattern borders
	glColor3f(1, 0, 0);
	glPolygonStipple(polygonPattern);

	glBegin(GL_POLYGON);
		glVertex2i(-256, -256);
		glVertex2i(-256, -160);
		glVertex2i(256, -160);
		glVertex2i(256, -256);
	glEnd();


	// Draw lines
}


//This function executes all drawing functions and pixel data gathering in one location
void MasterDraw(){
	DrawBackground();
	DrawBitman();
	DrawLazers();

	PixelDataOutput();
}
//***********************************************************************************
void myInit()
{
	glClearColor(1, 1, 1, 0); // specify a background clor: white
	gluOrtho2D(-256, 256, -256, 256); // specify a viewing area

	//// Read content from text file for 512x512 image rgb values per pixel
	ifstream inputFile(".//assets//data.txt");
	int counter = 0;
	int currentRow = 0;
	int currentCol = 0;
	float fVal;

	if (inputFile)
	{
		while (inputFile >> fVal)
		{
			currentCol = counter % 512;
			currentRow = floor(counter / 512);

			float fValRed = fVal;
			float fValGreen;
			float fValBlue;

			inputFile >> fValGreen;
			inputFile >> fValBlue;

			pixelMap[currentRow][currentCol][0] = fValRed;
			pixelMap[currentRow][currentCol][1] = fValGreen;
			pixelMap[currentRow][currentCol][2] = fValBlue;

			counter += 1;
		}
	}
}


//***********************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT); // draw the background
	MasterDraw(); //draw all image components
	glFlush(); // flush out the buffer contents
}

//***********************************************************************************
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(512, 512); // specify a window size
	glutInitWindowPosition(100, 0); // specify a window position
	glutCreateWindow("Project 1 - OpenGL Awakens"); // create a titled window

	myInit(); // setting up

	glutDisplayFunc(myDisplayCallback); // register a callback
	
	glutMainLoop(); // get into an infinite loop

	return 0;
}
