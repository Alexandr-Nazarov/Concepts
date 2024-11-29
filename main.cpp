#include <iostream>
#include <string>


class A {
	int m_a;
public:
	A(int a) :m_a(a) {}
	friend std::ostream& operator<<(std::ostream&, const A&);
};

std::ostream& operator<<(std::ostream& out, const A& ref) {
	out << ref.m_a << '\n';
	return out;
}

class Point {
	int m_x, m_y;
public:
	Point(int x = 0, int y = 0) :m_x(x), m_y(y) {}

	friend std::ostream& operator<<(std::ostream&, const Point&);

	std::string to_string()const {

		return "Point: x=" + std::to_string(m_x) + " y=" + std::to_string(m_y);
	}

};

std::ostream& operator<<(std::ostream& out, const Point& ref) {
	out << ref.to_string() << '\n';
	return out;
}


template<typename T>
concept String_std = requires(T t) { std::to_string(t); };

template<typename T>
concept String_metod = requires(T t) { t.to_string(); };

template<typename T>
concept Ostream = requires(std::ostream & out, T t) { out << t; };

template<typename T>
	requires (String_std<T> || String_metod<T> || Ostream<T>)
void print_any_how(T val) {

	std::cout << val;
}

int main(){

print_any_how(2.2);
std::cout << std::endl;

print_any_how(Point(1, 2));
std::cout << std::endl;

print_any_how(A(1));
std::cout << std::endl;
}