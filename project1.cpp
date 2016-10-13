/*==================================================================================================
PROGRAMMERS: Matthew Wilson and Garren Ijames
COURSE: CSC 525/625
MODIFIED BY: Matthew Wilson and Garren Ijames
LAST MODIFIED DATE: 10/13/2016
CONTRIBUTIONS:
	Matt - 50%
		Main Documentation
		Frame Buffer Output
		Force Shield (Circle) and Glow
		Bitmap Img Creation and Drawing
		Intro Message
		Code Clean Up
		Fine Tuning Placements and Timings
	Garren - 50%
		Base Image Creation
		Pixelmap Drawing
		Polygon w/ Stipple
		Text
		Lazers and Their Animations
		Fine Tuning Placements and Timings

DESCRIPTION: Project 1 - Demonstrate Basic 2D OpenGL Functionality

NOTES: Image Parts:
	Lazers - drawn using lines with stipple
	Force Shield - drawn using line loop to approximate circle
	Imperial Logo - polygon with pattern
	Vader Quote - text using bitmap fonts
	Puple Man - bitmap image
	Background - pixelmap image

FILES: project1.cpp, data.txt (..\assets\data.txt)

IMAGE CITATION: Image composition made in GIMP using:
	"Darth Vader" - Retrieved from: http://digitalspyuk.cdnds.net/16/04/768x384/landscape-1453994837-movies-star-wars-darth-vader.jpg
	"Starbucks Cup" - Retrieved from: http://www.clipartkid.com/images/125/how-starbucks-could-save-your-life-carolyn-anderson-wellness-HaobaR-clipart.jpg
	
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
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::cos;
using std::sin;

// Global variable for pixel info
GLfloat pixelMap[512][512][3]; //for background display

GLfloat pixelData[512 * 512 * 3]; //for frame buffer output


///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// Large global variables for the polygon pattern and the bitMap pattern         //
// ----------------------------------------------------------------------------- //

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

//bitmap image of man converted into hex
GLubyte BitMan[260] = {
	0xe0, 0x00, 0x00, 0x00,
	0xf0, 0x00, 0x00, 0x1f,
	0x70, 0x00, 0x00, 0x1f,
	0x3c, 0x00, 0x00, 0x1c,
	0x1e, 0x00, 0x00, 0x1c,
	0x0f, 0x00, 0x00, 0x38,
	0x07, 0x80, 0x00, 0x38,
	0x03, 0xc0, 0x00, 0x78,
	0x01, 0xf0, 0x00, 0x78,
	0x00, 0xf8, 0x00, 0xf8,
	0x00, 0x7c, 0x01, 0xf0,
	0x00, 0x3e, 0x03, 0xe0,
	0x00, 0x1f, 0x0f, 0xe0,
	0x00, 0x1f, 0xbf, 0xc0,
	0x00, 0x0f, 0xff, 0xc0,
	0x00, 0x0f, 0xff, 0x80,
	0x00, 0x0f, 0xff, 0x00,
	0x00, 0x07, 0xfe, 0x00,
	0x03, 0x83, 0xfc, 0x00,
	0x03, 0x83, 0xf8, 0x00,
	0x03, 0x83, 0xf8, 0x00,
	0x01, 0x83, 0xf8, 0x00,
	0x01, 0xc3, 0xf8, 0x00,
	0x01, 0xc3, 0xfc, 0x00,
	0x00, 0xe3, 0xfc, 0x00,
	0x00, 0xf3, 0xfc, 0x00,
	0x00, 0xff, 0xfc, 0x00,
	0x00, 0x7f, 0xff, 0x80,
	0x00, 0x3f, 0xff, 0xc0,
	0x00, 0x0f, 0xff, 0xf0,
	0x00, 0x03, 0xfc, 0x78,
	0x00, 0x01, 0xf8, 0x38,
	0x00, 0x01, 0xf0, 0x1c,
	0x00, 0x00, 0xf8, 0x0e,
	0x00, 0x01, 0xf8, 0x0e,
	0x00, 0x01, 0xf8, 0x0e,
	0x00, 0x01, 0xf8, 0x00,
	0x00, 0x00, 0xf0, 0x00
};

//-- END: polygon and bitMap patterns --


///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// A few globals relating lazers, force shield and their animations drawing.     //
// ----------------------------------------------------------------------------- //

const int LAZER_NUMBER = 5; // number of lazers to display
const float LAZER_SPEED = 20; // scalar for how fast lazers move accross screen
float LAZER_COLOR[3] = {0, 1, 0}; // global color for lazers

struct Lazer {
	float xCoord;
	float yCoord;
	float size;
	float firingAngle;
};

Lazer lazers[LAZER_NUMBER];

short int FS_BGLOW = 0;

//-- END: Animation globals --


///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// This function captures the frame buffer and outputs pixel data to a text file //
// ----------------------------------------------------------------------------- //

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

//-- END: PixelDataOutput --


///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// This function manages updates to the lazer positions							 //
// ----------------------------------------------------------------------------- //

void lazersUpdate()
{
	for (int i = 0; i < LAZER_NUMBER; i++) //for each lazer
	{
		if (lazers[i].xCoord < -47)
		{
			lazers[i].firingAngle = (M_PI * -45.0) / 180.0;
		}
		if (lazers[i].xCoord < -150) //if the lazer is at the end of its run
		{
			lazers[i].xCoord = 150; //reset coords
			lazers[i].yCoord = 150;
			lazers[i].firingAngle = (M_PI * 45.0) / 180.0;
		}
		else //otherwise move lazers along path
		{
			lazers[i].xCoord -= LAZER_SPEED * cos(lazers[i].firingAngle);
			lazers[i].yCoord -= LAZER_SPEED * sin(lazers[i].firingAngle);
		}
	}
}

//-- END: lazersUpate --

///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// This function draws circles to form a force shield		                     //
// ----------------------------------------------------------------------------- //

void DrawFS()
{
	FS_BGLOW++; //increment FS color  state

	//set circle location and radius
	int x = -83, y = -80;
	int radius = 35;

	int lineAmount = 1000; //# of triangles used to draw circle

	glEnable(GL_LINE_SMOOTH); //enable smoothing to improve circles

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * M_PI;
	
	//set outer circle color and width
	switch (FS_BGLOW){
	case 0:
		glColor4f(0, .2, 1, .7);
		break;
	case 1:
		glColor4f(0, .425, 1, .7);
		break;
	case 2:
		glColor4f(0, .625, 1, .7);
		break;
	case 3:
		glColor4f(0, .775, 1, .7);
		break;
	case 4:
		glColor4f(0, .625, 1, .7);
		break;
	case 5:
		glColor4f(0, .425, 1, .7);
		FS_BGLOW = 0;
		break;
	default:
		break;
	}
	glLineWidth(5);

	glBegin(GL_LINE_LOOP); //generate line vertices to aproximate circle
	for (int i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radius * cos(i *  twicePi / lineAmount)),
			y + (radius* sin(i * twicePi / lineAmount))
			);
	}
	glEnd();

	//set inner circle color and width
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1);

	glBegin(GL_LINE_LOOP); //generate line vertices to aproximate circle
	for (int i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radius * cos(i *  twicePi / lineAmount)),
			y + (radius* sin(i * twicePi / lineAmount))
			);
	}
	glEnd();

	glDisable(GL_LINE_SMOOTH); //disable smoothing for other lines
}

//-- END: DrawForceShield


///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// This function manages line segment drawing for lazers                         //
// ----------------------------------------------------------------------------- //

void DrawLazers(){
	glLineWidth(6); //set line preferences

	//generate vertices and draw lines for lazers
	for (int i = 0; i < LAZER_NUMBER; i++)
	{
		Lazer lazer = lazers[i];
		float lazerDX = lazer.xCoord + lazer.size * cos(lazer.firingAngle);
		float lazerDY = lazer.yCoord + lazer.size * sin(lazer.firingAngle);

		glColor3fv(LAZER_COLOR);

		glBegin(GL_LINES);
			glVertex2f(lazer.xCoord, lazer.yCoord);
			glVertex2f(lazerDX, lazerDY);
		glEnd();
	}
}

// -- END: DrawLazers --


///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// This function manages Bitmap drawing                                          //
// ----------------------------------------------------------------------------- //

void DrawBitmap(){
	//set color
	glColor3f(.5, 0, .3);
	//draw bitmap image
	glRasterPos2i(-100, -100);
	glBitmap(32, 38, 0.0, 0.0, 32, 0, BitMan);
}

// -- END: DrawBitmap -- //

///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// Write some QoL intro text to frame buffer before loading main img             //
// ----------------------------------------------------------------------------- //

void DrawIntroText(){
	glColor3f(0, 0, 0);

	string firstStr = "Today, in a Galaxy very. . . here";
	string secondStr = "you waited patiently for our frame to be drawn";

	glRasterPos2i(-140, 100);

	for (int i = 0; i < firstStr.length(); i++){

		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, firstStr[i]);

	}

	glRasterPos2i(-185, 80);
	for (int i = 0; i < secondStr.length(); i++){

		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, secondStr[i]);

	}

	glFlush();
}

// -- END: DrawIntroText -- //


///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// Draw the Darth Vader background and polygon border                            //
// ----------------------------------------------------------------------------- //

void DrawBackground()
{
	// Enable polygon stipple for later use of pattern
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_STIPPLE);


	// Draw background image
	glRasterPos2i(-256, -256);
	glDrawPixels(512, 512, GL_RGB, GL_FLOAT, pixelMap);


	// Draw title text
	string titleText = "\"I said I wanted it black\""; //set text string
	int strWidth = 0;

	for (int i = 0; i < titleText.size(); i++) // acquire width
		strWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, titleText[i]);


	glColor3f(1, 1, 1);
	glRasterPos2i(-250, 230);

	for (int i = 0; i < titleText.size(); i++) // title text
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, titleText[i]);


	// Draw polygon pattern borders
	glColor3f(1, 0, 0);
	glPolygonStipple(polygonPattern);


	glBegin(GL_POLYGON);
		glVertex2i(160, 192);
		glVertex2i(192, 192);
		glVertex2i(192, 160);
		glVertex2i(160, 160);

	glEnd();
}

// -- END: DrawBackground --


///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// This function is the callback that will be passed to glutTimerFunc and        //
// subsequently make recursive calls by passing itself to a new instance of      //
// glutTimerFunc                                                                 //
// ----------------------------------------------------------------------------- //

void animateLazers(int value)
{
	DrawBackground();
	DrawBitmap();
	DrawFS();
	DrawLazers();
	lazersUpdate();
	glFlush();
	glutTimerFunc(1000, animateLazers, 0);
}

//-- END: animateLazers --


///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// This function executes all drawing functions and pixel data gathering in one  //
// location                                                                      //
// ----------------------------------------------------------------------------- //

void MasterDraw(){
	DrawIntroText();
	DrawBackground();
	DrawBitmap();
	DrawFS();
	DrawLazers();

	PixelDataOutput();
}

//-- END: MasterDraw --

///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// This initializer function sets the inital background color, viewing area      //
// dimensions and location, gathers pixel data for background and initializes    //
// list for lazer drawing.														 //
// ----------------------------------------------------------------------------- //

void myInit()
{
	glClearColor(1, 1, 1, 0); // specify a background clor: white
	gluOrtho2D(-256, 256, -256, 256); // specify a viewing area


	// Read content from text file for 512x512 image rgb values per pixel
	ifstream inputFile("..\\..\\Project1\\assets\\data.txt");
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


	// Initialize lazer list
	for (int i = 0; i < LAZER_NUMBER; i++)
	{
		Lazer lazer;
		lazer.size = 30;
		lazer.xCoord = i * lazer.size + lazer.size; // space the lazers out a bit
		lazer.yCoord = i * lazer.size + lazer.size;
		lazer.firingAngle = (M_PI * 45.0) / 180.0;
		lazers[i] = lazer;
	}
}

//-- END: myInit --

///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
// Main callback function. Creates blank background, initiates image drawing	 //
// and flushes the buffer to draw image to frame.								 //
// ----------------------------------------------------------------------------- //

void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT); // draw the background
	MasterDraw();
	glFlush(); // flush out the buffer contents
}

//-- END: myDisplayCallback --


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(512, 512); // specify a window size
	glutInitWindowPosition(100, 0); // specify a window position
	glutCreateWindow("Project 1"); // create a titled window

	cout << "Please wait patiently for pixel map information to be gathered.";

	myInit(); // setting up

	glutDisplayFunc(myDisplayCallback); // register a callback
	glutTimerFunc(1000, animateLazers, 1);
	
	glutMainLoop(); // get into an infinite loop

	return 0;
}
