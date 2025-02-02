
#include "framework.h"
#include "okg_lab2.h"

extern int ak;
extern HDC hdc;

VOID DRAW_Waves_and_Ship1(HDC hdc, int ak, int xend, int yend)
{

// ak – помощен брояч
// xend, yend – размер на растера

  Graphics graphics(hdc);  // инициализация на графичен режим
	
int dx=xend/9;			       // определяне на стъпка по х	
int dy=yend/2;			       // определяне на стъпка по y
Point p[] = {			// вълни при положение 1
	   Point(0, dy+5),   // стартова точка на първия сплайн
	   Point(dx, dy+30),    // първа управляваща точка на първия сплайн
	   Point(2*dx, dy-30),    // втора управляваща точка на първия сплайн
	   Point(3*dx, dy+5),  // крайна точка на първия сплайн и 
						 // стартова точка на втория сплайн
	   Point(4*dx, dy+30),   // първа управляваща точка на втория сплайн
	   Point(5*dx, dy-30),  // втора управляваща точка на втория сплайн
	   Point(6*dx, dy+5),  // крайна точка на втория сплайн и 
						 // стартова точка на третия сплайн
	   Point(7*dx, dy+30),  // първа управляваща точка на третия сплайн
	   Point(8*dx, dy-30),  // втора управляваща точка на третия сплайн
	   Point(xend,dy+5)   // крайна точка на третия сплайн
		};
Point p1[] = {		// вълни при положение 2
	   Point(0, dy+10),   
	   Point(dx, dy+20),    
	   Point(2*dx, dy-20),   
	   Point(3*dx, dy+10),  
	   Point(4*dx, dy+20),   
	   Point(5*dx, dy-20),  
	   Point(6*dx, dy+10),
	   Point(7*dx, dy+20),
	   Point(8*dx, dy-20),
	   Point(xend, dy+10)
		};
Point p2[] = {		// вълни при положение 3
	   Point(0, dy+5),   
	   Point(dx, dy+10),    
	   Point(2*dx, dy-10),    
	   Point(3*dx, dy+5),  
	   Point(4*dx, dy+10),   
	   Point(5*dx, dy-10), 
	   Point(6*dx, dy+5),
	   Point(7*dx, dy+10),
	   Point(8*dx, dy-10),
	   Point(xend, dy+5)
		};
Point p3[] = {		// вълни при положение 4
	   Point(0, dy),  
	   Point(dx, dy-30),    
	   Point(2*dx, dy+30),    
	   Point(3*dx, dy),  
 	   Point(4*dx, dy-30),   
	   Point(5*dx, dy+30),  
	   Point(6*dx, dy),
	   Point(7*dx, dy-30),
	   Point(8*dx, dy+30),
	   Point(xend, dy)
	};

	Pen Neavypen(Color(63,0,168,196)); //цветове на вълните - молив
	SolidBrush Neavybr(Color(63,0,168,196)); //цветове на вълните - четка
	GraphicsPath myPath, myPath1;

myPath.StartFigure();
	switch (ak)
	{
	case 0:
		{
		myPath.AddLine(0,yend,0,dy+5);
		myPath.AddBeziers(p2,10);
		myPath.AddLine(xend,dy+5,xend,yend);
		}
		break;
	case 1:
		{
		myPath.AddLine(0,yend,0,dy+10);
		myPath.AddBeziers(p1,10);
		myPath.AddLine(xend,dy+10,xend,yend);
		}
		break;
	case 2:
		{
		myPath.AddLine(0,yend,0,dy+5);
		myPath.AddBeziers(p2,10);
		myPath.AddLine(xend,dy+5,xend,yend);
		}
		break;
	case 3:
		{
		myPath.AddLine(0,yend,0,dy);
		myPath.AddBeziers(p3,10);  
		myPath.AddLine(xend,dy,xend,yend);
		}
		break;
	case 4:
		{
		myPath.AddLine(0,yend,0,dy+10);
		myPath.AddBeziers(p,10);
		myPath.AddLine(xend,dy+10,xend,yend);
		}
		break;
	}

myPath.CloseFigure();

myPath1.StartFigure(); // съставна фигура - кораб

myPath1.AddLine(xend/4, yend/2-30,xend/4+xend/5,yend/2-30);
myPath1.AddBezier(xend/4, yend/2-30,xend/4+xend/12,yend/2+60,xend/4+xend/6,yend/2+60,xend/4+xend/5,yend/2-30);
myPath1.AddLine(xend/4+xend/10,yend/2-30,xend/4+xend/10,yend/2-80);
myPath1.AddLine(xend/4+xend/10-1,yend/2-80,xend/4+xend/10-1,yend/2-30);
myPath1.CloseFigure();
SolidBrush Shipbr(Color(164,0,168,16)); //оцветяване на кораба


Matrix myMatrix; //иницииране на матрица за трансформации

if ((ak==1)||(ak==3))
{
//задаване на отместване до началото на координатната система
myMatrix.Translate(-float(xend/4+xend/10),-float(yend/4));
myMatrix.Rotate(-8.0f);  //задаване на ротация
myPath1.Transform(&myMatrix); 
float sx=float(1)+float(ak)/10;
myMatrix.Scale(sx,sx); //задаване на мащабиране
myMatrix.Translate(+float(1.8*(xend/4+xend/10)),+float(3*(yend/5)), MatrixOrderAppend);//задаване на транслация
myPath1.Transform(&myMatrix); // придвижване на кораба
}
if (ak==2)
{

myMatrix.Scale(1.125f,1.125f);
myMatrix.Translate(-20.0f,-10.0f, MatrixOrderAppend);
myPath1.Transform(&myMatrix); // придвижване на кораба 
}

if (ak==4)
{
myMatrix.Translate(-float(xend/4+xend/10),-float(yend/4));
myMatrix.Rotate(+5.0f); 
myPath1.Transform(&myMatrix); 
myMatrix.Scale(1.3f,1.3f);
myMatrix.Translate(+float(2.2*(xend/4+xend/10)),+float(1.8*(yend/4)), MatrixOrderAppend);
myPath1.Transform(&myMatrix);
}

graphics.FillPath(&Shipbr, &myPath1);

graphics.FillPath(&Neavybr, &myPath);

}
