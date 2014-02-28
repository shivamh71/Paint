// Include Files
// ----------------------------------------------------------------- //

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glut.h>
#include <list>
#include "canvas_t.h"
#include "drawing_t.h"
#include "line_t.h"
#include "fill_t.h"
#include "polygon_t.h"
#include "point_t.h"
#include "color_t.h"
#include "pen_t.h"
#include "pixel_t.h"
using namespace std;

// ----------------------------------------------------------------- //


// draw mode enumeration
enum draw_mode {LINE,POLYGON,POINT};


// public variables
// ----------------------------------------------------------------- //

vector<vector<pixel_t> > raster;
vector<string> steps;
vector<fill_t> fills;
canvas_t* canvas;
drawing_t* drawing = NULL;
pen_t* pen;
color_t* drawColor;
color_t* backgroundColor;
color_t* fillColor;
point_t* startPoint;
point_t* endPoint;
point_t* polygonPoint;
polygon_t* polygon;
bool canvasDisplay = false;
bool draw = false;
bool drawPolygon = false;
bool fillState = false;
bool erase = false;
int lineCount = 0;
draw_mode mode = POINT;
int red, green, blue, size;
int fillType; // fill type [checkerboard or solid]
string name; 
ofstream fout;
ifstream fin;
string label;
int width, height, r, g, b, s, x, y, n; // variables used for loading image
point_t *p, *q;
line_t *l;
polygon_t *pol;
color_t *c;
fill_t *f;

// ----------------------------------------------------------------- //

// display function
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	if (canvasDisplay) {
		glPointSize(1.0);
		if (draw) drawing->draw(raster);
		glBegin(GL_POINTS);
		for (int i=0;i<raster.size();i++) { // draw 2D array of pixels
			for (int j=0;j<raster[i].size();j++) {		
				glColor3f((float)(raster[i][j].r/255),(float)(raster[i][j].g/255),(float)(raster[i][j].b/255));
				glVertex2f(i,j);
			}
		}
		glEnd();
	}
	glutSwapBuffers();
}

// ----------------------------------------------------------------- //

// reshape function
void reshape( int w, int h ) { 
	if (h==0) 
		h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,(GLdouble)w,0.0,(GLdouble)h,-1.,1.);
	glViewport(0,0,w,h);
	canvas->setWinWidth(w);
	canvas->setWinHeight(h);
	glutPostRedisplay();
}

// ----------------------------------------------------------------- //

void keyboard(unsigned char key, int x, int y) { // keyboard callback
	switch (key) {

		// exit paint
		case 27:
			exit(0);
			break;

		// initialize new canvas	
		case 'n':
		case 'N':
			if (drawing!=NULL) {
				canvasDisplay = false;
				drawing->flushDrawing();
				steps.clear(); // clear current step data
				canvas->deinitializeCanvas(raster); // clear canvas
				canvas->initializeCanvas(raster,*backgroundColor); // color new canvas
				canvasDisplay = true;
				draw = false;
				mode = POINT;
			}
			else {
				backgroundColor = new color_t();
				canvas->initializeCanvas(raster,*backgroundColor);
				canvasDisplay = true;
			}
			break;

		// initialize new drawing
		case 'd':
		case 'D':
			if (drawing!=NULL) {
				canvasDisplay = false;
				drawing->flushDrawing();
				steps.clear();
				canvas->deinitializeCanvas(raster);
				canvas->initializeCanvas(raster,*backgroundColor);
				canvasDisplay = true;
				mode = POINT;
			}
			drawing = new drawing_t();
			pen = new pen_t();
			startPoint = new point_t();
			endPoint = new point_t();
			polygon = new polygon_t();
			cout<<"enter pen size : ";
			cin>>size;
			cout<<"enter pen color (rgb values space separated) : ";
			cin>>red>>green>>blue;
			drawColor = new color_t(red,green,blue);
			pen->setPenSize(size);
			pen->setPenColor(*drawColor);
			draw = true;
			break;

		// line drawing mode
		case '1':
			if (mode==POINT) mode = LINE;
			else mode = POINT;
			break;

		// polygon drawing mode
		case '2':
			if (mode==POINT || mode==LINE) {
				mode = POLYGON;
			}
			else {
				mode = POINT;
				color_t temp = pen->getPenColor();
				line_t* l = new line_t(*endPoint,*polygonPoint,temp);
				polygon->addToLineList(l);
				drawing->addLine(l);
				steps.push_back("LINE");
				drawing->addPolygon(polygon);
				steps.push_back("POLYGON");
				drawPolygon = false;
				lineCount = 0;
			}
			break;

		// change pen characterstics
		case 'c':
		case 'C':
			cout<<"enter pen size : ";
			cin>>size;
			cout<<"enter pen color (rgb values space separated) : ";
			cin>>red>>green>>blue;
			drawColor = new color_t(red,green,blue);
			pen->setPenSize(size);
			pen->setPenColor(*drawColor);
			break;

		// saving all class information in text file
		case 's':
		case 'S':
			cout<<"Save As : ";
			cin>>name;
			fout.open(name.c_str(),ios::out);
			if (canvas==NULL) {
				cout<<"No drawing to save\n";
			}
			else if (drawing==NULL) {
				fout<<"canvas  ";
				fout<<canvas->canvasWidth;
				fout<<"  ";
				fout<<canvas->canvasHeight;
				fout<<"  ";
				fout<<canvas->backgroundRed;
				fout<<"  ";
				fout<<canvas->backgroundGreen;
				fout<<"  ";
				fout<<canvas->backgroundBlue;
				fout<<"\n";
				fout<<"END";
			}
			else {
				fout<<"canvas  ";
				fout<<canvas->canvasWidth;
				fout<<"  ";
				fout<<canvas->canvasHeight;
				fout<<"  ";
				fout<<canvas->backgroundRed;
				fout<<"  ";
				fout<<canvas->backgroundGreen;
				fout<<"  ";
				fout<<canvas->backgroundBlue;
				fout<<"\n";
				fout<<"pen "<<pen->getPenSize()<<" "<<pen->getPenColor().getRedValue()<<" ";
				fout<<pen->getPenColor().getGreenValue()<<" "<<pen->getPenColor().getBlueValue()<<"\n";
				fout<<"drawcolor "<<drawColor->getRedValue()<<" "<<drawColor->getGreenValue()<<" "<<drawColor->getBlueValue()<<"\n";
				fout<<"backcolor "<<backgroundColor->getRedValue()<<" "<<backgroundColor->getGreenValue()<<" "<<backgroundColor->getBlueValue()<<"\n";
				list<point_t*>::iterator pit = drawing->pointList.begin();
				list<line_t*>::iterator lit = drawing->lineList.begin();
				list<polygon_t*>::iterator polit = drawing->polygonList.begin();
				vector<fill_t>::iterator fit = fills.begin();
				for (int i=0;i<steps.size();i++) {
					if (steps[i]=="POINT") {
						point_t p = *(*pit);
						pit++;
						fout<<"point "<<p.getX()<<" "<<p.getY()<<" "<<p.getPointSize()<<" "<<p.getPointColor().getRedValue();
						fout<<" "<<p.getPointColor().getGreenValue()<<" "<<p.getPointColor().getBlueValue()<<"\n";
					}
					else if (steps[i]=="LINE") {
						line_t l = *(*lit);
						lit++;
						color_t c = l.getLineColor();
						fout<<"line "<<c.getRedValue()<<" "<<c.getGreenValue()<<" "<<c.getBlueValue()<<" ";
						point_t p;
						p = l.getLineStartPoint();
						fout<<p.getX()<<" "<<p.getY()<<" "<<p.getPointSize()<<" "<<p.getPointColor().getRedValue();
						fout<<" "<<p.getPointColor().getGreenValue()<<" "<<p.getPointColor().getBlueValue()<<" ";
						p = l.getLineEndPoint();
						fout<<p.getX()<<" "<<p.getY()<<" "<<p.getPointSize()<<" "<<p.getPointColor().getRedValue();
						fout<<" "<<p.getPointColor().getGreenValue()<<" "<<p.getPointColor().getBlueValue()<<"\n";
					}
					else if (steps[i]=="POLYGON") {
						polygon_t p = *(*polit);
						polit++;
						list<point_t> l =p.getPointList();
						fout<<"polygon "<<l.size();
						list<point_t>::iterator pi;
						for (pi=l.begin();pi!=l.end();pi++) {
							point_t p = *pi;
							fout<<" "<<p.getX()<<" "<<p.getY()<<" "<<p.getPointSize()<<" "<<p.getPointColor().getRedValue();
							fout<<" "<<p.getPointColor().getGreenValue()<<" "<<p.getPointColor().getBlueValue();
						}
						fout<<"\n";
					}
					else if (steps[i]=="FLOODFILL") {
						fill_t f = *fit;
						fit++;
						fout<<"FLOODFILL ";
						point_t p = f.fillPoint;
						fout<<p.getX()<<" "<<p.getY()<<" "<<p.getPointSize()<<" "<<p.getPointColor().getRedValue();
						fout<<" "<<p.getPointColor().getGreenValue()<<" "<<p.getPointColor().getBlueValue()<<" ";
						color_t c = f.firstColor;
						fout<<c.getRedValue()<<" "<<c.getGreenValue()<<" "<<c.getBlueValue()<<"\n";
					}
					else if (steps[i]=="CHECKERFILL") {
						fill_t f = *fit;
						fit++;
						fout<<"CHECKERFILL ";
						point_t p = f.fillPoint;
						fout<<p.getX()<<" "<<p.getY()<<" "<<p.getPointSize()<<" "<<p.getPointColor().getRedValue();
						fout<<" "<<p.getPointColor().getGreenValue()<<" "<<p.getPointColor().getBlueValue()<<" ";
						color_t c = f.firstColor;
						fout<<c.getRedValue()<<" "<<c.getGreenValue()<<" "<<c.getBlueValue()<<" ";
						c = f.secondColor;
						fout<<c.getRedValue()<<" "<<c.getGreenValue()<<" "<<c.getBlueValue()<<" "<<f.checkSize<<"\n";
					}
				}
				fout<<"END";
			}
			
			fout.close();
			break;

		// load image from text file
		case 'l':
		case 'L':
			cout<<"Load file : ";
			cin>>name;
			fin.open(name.c_str());
			if (!fin) {
				cout<<"file does not exist\n";
				break;
			}
			mode = POINT;
			draw = true;
			fillState = false;
			canvasDisplay = true;
			steps.clear();
			fills.clear();
			canvas = new canvas_t(700,700);
			drawing = new drawing_t();
			polygon = new polygon_t();
			startPoint = new point_t();
			endPoint = new point_t();
			pen = new pen_t();
			while(!fin.eof()) {
				fin>>label;
				if (label=="END")
					break;
				if (label=="canvas") {
					fin>>width;
					fin>>height;
					fin>>r>>g>>b;
					canvas->displayCanvas(raster,width,height,r,g,b);
				}
				else if (label=="pen") {
					fin>>s>>r>>g>>b;
					pen->setPenSize(s);
					c = new color_t(r,g,b);
					pen->setPenColor(*c);
				}
				else if (label=="drawcolor") {
					fin>>r>>g>>b;
					drawColor = new color_t(r,g,b);
				}
				else if (label=="backcolor") {
					fin>>r>>g>>b;
					backgroundColor = new color_t(r,g,b);
				}
				else if (label=="point") {
					fin>>x>>y>>s>>r>>g>>b;
					p = new point_t(x,y);
					c = new color_t(r,g,b);
					p->setPointColor(*c);
					p->setPointSize(s);
					steps.push_back("POINT");
					drawing->addPoint(p);
					drawing->draw(raster);
				}
				else if (label=="line") {
					l = new line_t();
					fin>>r>>g>>b;
					c = new color_t(r,g,b);
					l->setLineColor(*c);
					fin>>x>>y>>s>>r>>g>>b;
					p = new point_t(x,y);
					c = new color_t(r,g,b);
					p->setPointColor(*c);
					p->setPointSize(s);
					l->setLineStartPoint(*p);
					fin>>x>>y>>s>>r>>g>>b;
					p = new point_t(x,y);
					c = new color_t(r,g,b);
					p->setPointColor(*c);
					p->setPointSize(s);
					l->setLineEndPoint(*p);
					drawing->addLine(l);
					steps.push_back("LINE");
					drawing->draw(raster);
				}
				else if (label=="polygon") {
					fin>>n;
					pol = new polygon_t();
					fin>>x>>y>>s>>r>>g>>b;
					p = new point_t(x,y);
					c = new color_t(r,g,b);
					p->setPointColor(*c);
					p->setPointSize(s);
					startPoint = p;
					for (int i=0;i<n-1;i++) {
						fin>>x>>y>>s>>r>>g>>b;
						q = new point_t(x,y);
						c = new color_t(r,g,b);
						q->setPointColor(*c);
						q->setPointSize(s);
						l = new line_t();
						l->setLineColor(*c);
						l->setLineStartPoint(*p);
						l->setLineEndPoint(*q);
						pol->addToLineList(l);
						p = q;
					}
					l = new line_t();
					l->setLineColor(*c);
					l->setLineStartPoint(*p);
					l->setLineEndPoint(*startPoint);
					pol->addToLineList(l);
					drawing->addPolygon(pol);
					steps.push_back("POLYGON");
					drawing->draw(raster);
				}
				else if (label=="FLOODFILL") {
					fin>>x>>y>>s>>r>>g>>b;
					p = new point_t(x,y);
					c = new color_t(r,g,b);
					p->setPointColor(*c);
					p->setPointSize(s);
					f = new fill_t("floodfill",*p);
					fin>>r>>g>>b;
					c = new color_t(r,g,b);
					f->firstColor = *c;
					fills.push_back(*f);
					steps.push_back("FLOODFILL");
					f->floodFill(raster,canvas->canvasWidth,canvas->canvasHeight);
				}
				else if (label=="CHECKERFILL") {
					fin>>x>>y>>s>>r>>g>>b;
					p = new point_t(x,y);
					c = new color_t(r,g,b);
					p->setPointColor(*c);
					p->setPointSize(s);
					f = new fill_t("floodfill",*p);
					fin>>r>>g>>b;
					c = new color_t(r,g,b);
					f->firstColor = *c;
					fin>>r>>g>>b>>s;
					c = new color_t(r,g,b);
					f->secondColor = *c;
					f->checkSize = s;
					fills.push_back(*f);
					steps.push_back("CHECKERFILL");
					f->checkerFill(raster,canvas->canvasWidth,canvas->canvasHeight);
				}
			}
			fin.close();
			break;

		// get fill type and color
		case 'f':
		case 'F':
			if (!fillState) {
				cout<<"Enter fill type [3 for checkerboard 4 for floodfill] : ";
				cin>>fillType;
				fillState = true;
			}
			else {
				fillState = false;
			}
			break;

		// case for entering and leaving the erase mode	
		case 'e':
		case 'E':
			if (!erase) {
				pen->setPenColor(*backgroundColor);
				erase = true;
			}
			else {
				erase = false;
				pen->setPenColor(*drawColor);
			}
			break;

		// default case	
		default:
			break;
	}
	glutPostRedisplay();
}

// ----------------------------------------------------------------- //

void mouse(int button, int state, int x, int y) { // mouse call back
	if (draw) {
		if (fillState) { // in case of fill mode click is used to get fill location
			if (state==GLUT_DOWN) {
				if (button==GLUT_LEFT_BUTTON) {
					point_t *p = new point_t(x,canvas->getWinHeight()-y);
		   			p->setPointColor(*backgroundColor);
		   			p->setPointSize(pen->getPenSize());
					if (fillType == 4) {
						fill_t f("SOLID",*p);
						cout<<"enter fill color (rgb values space separated) : ";
						cin>>red>>green>>blue;
						color_t * first = new color_t(red,green,blue);
						f.firstColor = *first;
						f.floodFill(raster,canvas->canvasWidth,canvas->canvasHeight);
						steps.push_back("FLOODFILL");
						fills.push_back(f);
					}
					else {
						fill_t f("CHECKERBOARD",*p);
						cout<<"enter first fill color (rgb values space separated) : ";
						cin>>red>>green>>blue;
						color_t * first = new color_t(red,green,blue);
						f.firstColor = *first;
						cout<<"enter second fill color (rgb values space separated) : ";
						cin>>red>>green>>blue;
						cout<<"Enter checkerboard pixel size : ";
						cin>>f.checkSize;
						color_t * second = new color_t(red,green,blue);
						f.secondColor = *second;
						f.checkerFill(raster,canvas->canvasWidth,canvas->canvasHeight);
						steps.push_back("CHECKERFILL");
						fills.push_back(f);
					}
				}
			}
		}
		else { // in case of not fill i.e. draw mode point is used to draw line or polygon
			if (mode==POINT) { // point drawing mode
				if (state==GLUT_DOWN) {
		       		if (button==GLUT_LEFT_BUTTON) {
		       			point_t *p = new point_t(x,canvas->getWinHeight()-y);
		       			color_t temp = pen->getPenColor();
		       			p->setPointColor(temp);
		       			p->setPointSize(pen->getPenSize());
		       			drawing->addPoint(p);
		       			steps.push_back("POINT");
		       		} 
		       	}
			}
			else if (mode==LINE) { // line drawing mode
				if (state==GLUT_DOWN) {
		       		if (button==GLUT_LEFT_BUTTON) {
		       			point_t *p = new point_t(x,canvas->getWinHeight()-y);
		       			color_t temp = pen->getPenColor();
		       			p->setPointColor(temp);
		       			p->setPointSize(pen->getPenSize());
		       			if (lineCount==1) {
		       				lineCount = 0;
		       				endPoint = p;
		       				line_t* l = new line_t(*startPoint,*endPoint,temp);
		       				drawing->addLine(l);
		       				steps.push_back("LINE");
		       			}
		       			else {
		       				drawing->addPoint(p);
		       				steps.push_back("POINT");
		       				startPoint = p;
		       				lineCount++;
		       			}
		       		} 
		       	}
			}
			else if (mode==POLYGON) { // polygon drawing mode
				if (state==GLUT_DOWN) {
		       		if (button==GLUT_LEFT_BUTTON) {
		       			drawPolygon = true;
		       			point_t *p = new point_t(x,canvas->getWinHeight()-y);
		       			color_t temp = pen->getPenColor();
		       			p->setPointColor(temp);
		       			p->setPointSize(pen->getPenSize());
		       			if (lineCount==1) {
		       				endPoint = p;
		       				line_t* l = new line_t(*startPoint,*endPoint,temp);
		       				polygon->addToLineList(l);
		       				drawing->addLine(l);
		       				steps.push_back("LINE");
		       				startPoint = endPoint;
		       			}
		       			else {
		       				drawing->addPoint(p);
		       				steps.push_back("POINT");
		       				startPoint = p;
		       				polygonPoint = p;
		       				polygon = new polygon_t();
		       				lineCount++;
		       			}
		       		} 
		       	}
			}
		}
	}
	glutPostRedisplay();
}

// ----------------------------------------------------------------- //

int main(int argc, char *argv[]) {

	// initialize glut
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );

	// creating new window
	canvas = new canvas_t(700,700);
	glutInitWindowSize(canvas->getWinWidth(),canvas->getWinHeight());
	glutCreateWindow("PAINT");

	// glut callback and loop functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
}

// ----------------------------------------------------------------- //