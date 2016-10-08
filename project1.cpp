/*==================================================================================================
 PROGRAMMER: Garren Ijames
 COURSE: CSC 525/625
 MODIFIED BY:	Garren Ijames
 LAST MODIFIED DATE: 9/30/2016
 DESCRIPTION: Read in pixel data from 'autumn.txt' and render the picture they create to the
 graphics window.
 NOTE: N/A
 FILES: lab7.cpp
 IDE/COMPILER: Visual Studio 2013
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on labProject.sln	to OPEN the project
	2.		Press Ctrl+F7					to COMPILE
	3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
	4.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h> // include GLUT library
#include <fstream>
#include <cmath>

using std::ifstream;
using std::floor;

GLfloat pixelMap[512][512][3];

void drawPoints()
{
	//draw pixels
	glRasterPos2i(-256, -256);
	glDrawPixels(512, 512, GL_RGB, GL_FLOAT, pixelMap);
}

//***********************************************************************************
void myInit()
{
	glClearColor(1, 1, 1, 0); // specify a background clor: white
	gluOrtho2D(-256, 256, -256, 256); // specify a viewing area
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 8);

	//read in the pixel data from file
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
	drawPoints();
	glFlush(); // flush out the buffer contents
}

//***********************************************************************************
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(512, 512); // specify a window size
	glutInitWindowPosition(100, 0); // specify a window position
	glutCreateWindow("Project 1"); // create a titled window

	myInit(); // setting up

	glutDisplayFunc(myDisplayCallback); // register a callback

	glutMainLoop(); // get into an infinite loop

	return 0;
}
