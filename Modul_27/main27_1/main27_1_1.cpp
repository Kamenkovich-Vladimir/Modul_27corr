#include <iostream>
#include <cmath>
#include <cassert>
enum colors {
	green, red, blue, none
};
class Shape
{
public:
	Shape(double x, double y, int color) {
		this->x = x;
		this->y = y;
		this->color = color;
	}
	std::string getColor_inString() {	//Если надо получить цвет фигуры в строке
		switch (color)
		{
		case 0:
			return "green";
			break;
		case 1:
			return "red";
			break;
		case 2:
			return "blue";
			break;
		case 3:
			return "none";
			break;
		default:
			break;
		}
	}
	//гетеры координат центра фигуры
	double getX() const {
		return x;
	}
	double getY() const {
		return y;
	}
private:	
	//координаты центра фигуры
	double x = 0;
	double y = 0;
	//цвет фигуры
	int color = 3;
};

class Square : public Shape
{
public:
	Square(double x, double y, int color, double edge): Shape(x, y ,color)	{
		assert(edge >= 0);
		this->edge = edge;
	}
	double shapeSquare() const {	//Площадь квадрата и описывающего его квадрата
		return pow(edge, 2);
	}
private:
	double edge = 0;
};
class Circle : public Shape
{
public:
	
	Circle(double x, double y, int color, double radius): Shape(x, y ,color) {
		assert(radius >= 0);
		this->radius = radius;
	};
	double shapeArea() const {
		return atan(1) * 4 * pow(radius,2); //Площадь круга
	}
	double describingArea() const {		//Площадь описывающего его квадрата
		return pow(2 * radius, 2);
	}
private:
	double radius = 0;
};
class Triangle : public Shape
{
public:	
	Triangle(double x, double y, int color, double edge) : Shape(x, y, color) {
		assert(edge >= 0);
		this->edge = edge;
	};
	double shapeArea() const {
		return edge * edge * std::sqrt(3) / 4; //Площадь треугольника
	}
	double describingArea() const {		//Площадь описывающего его квадрата
		return pow(edge, 2);
	}
private:
	double edge = 0;
};
class Rectangle : public Shape
{
public:
	
	Rectangle(double x, double y, int color, double width, double height): Shape(x, y, color) {
		assert(width >= 0 && height >= 0);
		this->width = width;
		this->height = height;
	};
	double max() const{				//Найдем максимальную сторону прямоугольника
		if (width < height)
			return height;
		else
			return width;
	}
	double shapeArea() const{		//Площадь прямоугольника
		return width * height;
	}
	double describingArea() const{
		return pow(max(), 2);		////Площадь описывающего его квадрата
	}
private:
	double width;
	double height;
};
static bool checkColor(int intColor) {
	if (intColor < 0 || intColor > 3) {
		std::cout << "Invalid color of the shape! Try again!\n\n";
		return false;
	}
	else
		return true;
}

int main()
{
	std::cout << "***************** The hierarchy of geometric shapes *****************\n\n";

	std::string command = "";


	while (true) {
		std::cout << "Enter the command (circle, square, triangle, rectangle) or 'exit' to exit the program: ";
		std::cin >> command;

		if (command == "circle") {
			double radius;
			double x, y;
			int intColor;
			Circle* circle = nullptr;
			std::cout << "Enter coordinates of circle's center (x y): ";
			std::cin >> x >> y;
			std::cout << "Enter color of circle (0 - green, 1 - red, 2 - blue, 3 - none): ";
			std::cin >> intColor;
			if (!checkColor(intColor)) continue;
			std::cout << "Enter radius of circle: ";
			std::cin >> radius;
			if (radius < 0) {
				std::cout << "Invalid radius! Try again!\n\n";
				continue;
			}
			circle = new Circle(x, y, intColor, radius);
			std::cout << "The area of the circle - " << circle->shapeArea() << std::endl;
			std::cout << "the area of the square describing the figure - " <<circle->describingArea() << std::endl << std::endl;
			delete circle;
		}
		else if (command == "square") {
			double edge;
			double x, y;
			int intColor;
			Square* square = nullptr;
			std::cout << "Enter coordinates of square's center (x y): ";
			std::cin >> x >> y;
			std::cout << "Enter color of square (0 - green, 1 - red, 2 - blue, 3 - none): ";
			std::cin >> intColor;
			if (!checkColor(intColor)) continue;
			std::cout << "Enter edge of square: ";
			std::cin >> edge;
			if (edge < 0) {
				std::cout << "Invalid edge! Try again!\n\n";
				continue;
			}
			square = new Square(x, y, intColor, edge);
			std::cout << "The area of the square - " << square->shapeSquare() << std::endl;
			std::cout << "the area of the square describing the figure - " << square->shapeSquare() << std::endl << std::endl;
			delete square;
		}
		else if (command == "triangle") {
			double edge;
			double x, y;
			int intColor;
			Triangle* triangle = nullptr;
			std::cout << "Enter coordinates of triangle's center (x y): ";
			std::cin >> x >> y;
			std::cout << "Enter color of triangle (0 - green, 1 - red, 2 - blue, 3 - none): ";
			std::cin >> intColor;
			if (!checkColor(intColor)) continue;
			std::cout << "Enter edge of triangle: ";
			std::cin >> edge;
			if (edge < 0) {
				std::cout << "Invalid edge! Try again!\n\n";
				continue;
			}
			triangle = new Triangle(x, y, intColor, edge);
			std::cout << "The area of the triangle - " << triangle->shapeArea() << std::endl;
			std::cout << "the area of the square describing the figure - " << triangle->describingArea() << std::endl << std::endl;
			delete triangle;
		}
		else if (command == "rectangle") {
			double width, height;
			double x, y;
			int intColor;
			Rectangle* rectangle = nullptr;
			std::cout << "Enter coordinates of rectangle's center (x y): ";
			std::cin >> x >> y;
			std::cout << "Enter color of rectangle (0 - green, 1 - red, 2 - blue, 3 - none): ";
			std::cin >> intColor;
			if (!checkColor(intColor)) continue;
			std::cout << "Enter width and height of rectangle: ";
			std::cin >> width >> height;
			if (width < 0 || height < 0) {
				std::cout << "Invalid data! Try again!\n\n";
				continue;
			}
			rectangle = new Rectangle(x, y, intColor, width, height);
			
			std::cout << "The area of the square - " << rectangle->shapeArea() << std::endl;
			std::cout << "the area of the square describing the figure - " << rectangle->describingArea() <<
				std::endl << std::endl;
			delete rectangle;
		}
		else if (command == "exit") {
			return 0;
		}
		else {
			std::cerr << "Invalid command!\n\n";
		}
	}
}