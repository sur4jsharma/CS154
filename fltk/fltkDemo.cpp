#include<FL/Fl.H>
#include<FL/Fl_Double_Window.H>
#include<FL/fl_draw.H>
#include<string>
#include<bits/stdc++.h>

using namespace std;

class Shape
{
	public:
		int line_width;
		int line_color;
		int body_color;
		vector<pair<int,int>> points;
		Shape(int l_width,int l_color,int b_color)
		{
			cout<<"Shape constructor\n";
			line_width = l_width;
			line_color = l_color;
			body_color = b_color;
		}
		void add_point(pair<int,int> p)
		{
			points.push_back(p);
		}
		virtual void draw() {}
};

class Line:public Shape
{
	public:
		Line(pair<int,int> point1,pair<int,int> point2,int l_width,int l_color):Shape(l_width,l_color,0)
		{
			cout<<"Line constructor\n";
			add_point(point1);
			add_point(point2);
		}
		void draw()
		{
			cout<<"Draw in Line\n";
			fl_line_style(FL_SOLID,line_width);
			fl_color(line_color);
			fl_line(points[0].first,points[0].second,points[1].first,points[1].second);
		}
};

class Circle:public Shape
{
	int radius;
	public:
		Circle(pair<int,int> center,int r,int l_width,int l_color,int b_color):radius(r),Shape(l_width,l_color,b_color)
		{
			add_point(center);
		}
		void draw()
		{
			fl_line_style(FL_SOLID,line_width);
			fl_color(line_color);
			fl_circle(points[0].first,points[0].second,radius);
		}
};


class Windows:Fl_Double_Window
{
	vector<Shape*> shapes;
	public:
		Windows(int x,int y,int w,int h,const char* title):Fl_Double_Window(x,y,w,h,title)
		{
			cout<<"Window consructor\n";
			color(FL_BLACK);
			show();
		}
		void attach_shape_to_window(Shape *s)
		{
			cout<<"Attach to window\n";
			shapes.push_back(s);
		}
		void draw()
		{
			cout<<"draw in Window\n";
			//Fl_Double_Window::draw();
			cout<<"total number of shapes:"<<shapes.size()<<endl;
			for(int i=0;i<shapes.size();i++)
				shapes[i]->draw();// Run time polymorphism
		}
};

int main()
{
	int w{Fl::w()/2};
	int h{Fl::h()};
	Windows window(w,0,w,h,"Shape Drawing");

	// X,y axis drawn
	int orgin_x = w/4;
	int orgin_y = h/2;
	pair<int,int> p1(w/10,orgin_y);
	pair<int,int> p2(9*w/10,orgin_y);
	Line line1(p1,p2,3,FL_BLUE);
	pair<int,int> p3(orgin_x,h/10);
	pair<int,int> p4(orgin_x,9*h/10);
	Line line2(p3,p4,3,FL_BLUE);

	//draw y=2*x + 2
	double x = 50;
	double y = (2*x + 20);
	p3 = make_pair(orgin_x+x,orgin_y-y);
	x = -50;
	y = 2*x + 20;
	p2 = make_pair(orgin_x+x,orgin_y-y);
	Line res(p3,p2,3,FL_RED);
	window.attach_shape_to_window(&line1);
	window.attach_shape_to_window(&line2);
	window.attach_shape_to_window(&res);

	int center_x = orgin_x;
	int center_y = orgin_y - 20;
	pair<int,int> center(center_x,center_y);
	Circle c0(center,5,3,FL_WHITE,FL_GREEN);
	window.attach_shape_to_window(&c0);
	//window.draw();
	return Fl::run();
}
