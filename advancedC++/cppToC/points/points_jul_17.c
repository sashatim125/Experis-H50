#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PHASE (2)

/***** Phase 1 *****{{ */
#if PHASE >= 1
/*
class Point2D
{
public:
	Point2D();
	Point2D(double _x, double _y);

	double GetX() const;
	double GetY() const;
	double Distance(const Point2D& _other) const;

	Point2D &operator+=(const Point2D& _other);
	Point2D &operator*=(double _factor);

private:
	double m_x;
	double m_y;		
};
*/

typedef struct Point2D
{
	double m_x;
	double m_y;
} Point2D;


/*
Point2D::Point2D()
: m_x(0), m_y(0)
{
}
*/

void __Point2D_CTOR(Point2D* const _this)
{
/*Base*/

/*MIL*/
	_this->m_x = _this->m_y = 0;

/*Body*/
}

/*
Point2D::Point2D(double _x, double _y)
: m_x(_x), m_y(_y)
{
}
*/

void __Point2D_CTOR_double_double(Point2D* const _this, double _x, double _y)
{
/*Base*/

/*MIL*/
	_this->m_x = _x;
	_this->m_y = _y;
/*Body*/
}

/*copy contructor*/
void __Point2D_CTOR_const_Point2D_ptr(Point2D* const _this, const Point2D* const _other)
{
/*Base*/

/*MIL*/
	(_this->m_x) = (_other->m_x);
	
	(_this->m_y) = (_other->m_y);
/*Body*/
}

void __Point2D_DTOR(Point2D* const _this)
{}

/*
inline double Point2D::GetX() const
{
	return m_x;
}
*/

double __Point2D_const_GetX(const Point2D* const _this)
{
	return _this->m_x;
}

/*
inline double Point2D::GetY() const
{
	return m_y;
}
*/


double __Point2D_const_GetY(const Point2D* const _this)
{
	return _this->m_y;
}


/*
double Point2D::Distance(const Point2D& _other) const
{
	double dx = m_x - _other.m_x;
	double dy = m_y - _other.m_y;
	return sqrt(dx * dx + dy * dy);
}
*/

double __Point2D_const_Distance_const_Point2D_ptr(const Point2D* const _this, const Point2D* const _other)
{
	double dx;
	double dy;
	
	dx = _this->m_x - _other->m_x;
	dy = _this->m_y - _other->m_y;
		
	return sqrt(dx * dx + dy * dy);
}




/*
Point2D& Point2D::operator+=(const Point2D& _other)
{
	m_x += _other.m_x;
	m_y += _other.m_y;
	
	return *this;
}
*/

Point2D* __Point2D_operatorplusequal_const_Point2D_ptr(Point2D* const _this, const Point2D* const _other)
{
	(_this->m_x) += (_other->m_x);
	
	(_this->m_y) += (_other->m_y);

	return _this;
}

/*
Point2D& Point2D::operator*=(double _factor)
{
	m_x *= _factor;
	m_y *= _factor;
	
	return *this;
}
*/

Point2D* __Point2D_operatormultiplyequal_double(Point2D* const _this, double _factor)
{
	(_this->m_x) *= _factor;
	
	(_this->m_y) *= _factor;

	return _this;
}

/*
Point2D* Point2D_operatorequal_const_Point2D_ptr(Point2D* const _this, const Point2D* const _other)
{
	(_this->m_x) = (_other->m_x);
	
	(_this->m_y) = (_other->m_y);

	return _this;
}
*/

/*
void pointless()
{
	Point2D p0;
	Point2D p1(0,10);
	printf("distance p0 --> p1 == %f\n", p0.Distance(p1));

	Point2D dxy(+4, -7);
	p1 += dxy;
	printf("%f, %f\n", p1.GetX(), p1.GetY());
	printf("now distance p0 --> p1 == %f\n", p0.Distance(p1));
}
*/

void pointless()
{
	Point2D p0;
	Point2D p1;
	Point2D dxy;
	
	__Point2D_CTOR(&p0);
	__Point2D_CTOR_double_double(&p1,0,10);
	
	printf("distance p0 --> p1 == %f\n", __Point2D_const_Distance_const_Point2D_ptr(&p0,&p1));
	
	__Point2D_CTOR_double_double(&dxy,+4,-7);

	__Point2D_operatorplusequal_const_Point2D_ptr(&p1,&dxy);
	
	printf("%f, %f\n", __Point2D_const_GetX(&p1), __Point2D_const_GetY(&p1));
	printf("now distance p0 --> p1 == %f\n", __Point2D_const_Distance_const_Point2D_ptr(&p0,&p1));
	
	__Point2D_DTOR(&dxy);
	__Point2D_DTOR(&p1);
	__Point2D_DTOR(&p0);	
}


#endif

/* }} ***** Phase 1 *****/


/*----------------------------------------------------------------*/
/***** Phase 2 *****{{ */
#if PHASE >= 2
/*
class NamedPoint2D : public Point2D
{
public:
	NamedPoint2D(const char *_name = "origin");
	NamedPoint2D(double _x, double _y, const char *_name = "anonymous Point");
	NamedPoint2D(const Point2D& point, const char *_name = "anonymous Point");
	const char *GetName() const;

private:
	const char *m_name;	
};
*/


typedef struct NamedPoint2D
{
	Point2D m_base;
	const char *m_name;	
	
} NamedPoint2D;


/*
NamedPoint2D::NamedPoint2D(const char *_name)
: m_name(_name)
{
}
*/

void __NamedPoint2D_CTOR_const_char_ptr(NamedPoint2D* const _this, const char *_name)
{
/*base*/		
	__Point2D_CTOR((Point2D*)_this);
/*MIL*/
	_this->m_name = _name;
/*body*/
}


/*
NamedPoint2D::NamedPoint2D(double _x, double _y, const char *_name)
: m_name(_name), Point2D(_x, _y)
{
}
*/


void __NamedPoint2D_CTOR_double_double_const_char_ptr(NamedPoint2D* const _this, double _x, double _y, const char *_name)
{
	/*Base*/
	__Point2D_CTOR_double_double((Point2D*)_this,_x,_y);
	
	/*MIL*/
	_this->m_name = _name;
	
	/*BODY*/
}




/*
NamedPoint2D::NamedPoint2D(const Point2D& _point, const char *_name)
: m_name(_name), Point2D(_point)
{
}
*/


void __NamedPoint2D_CTOR_const_Point2D_ptr_const_char_ptr
	(NamedPoint2D* const _this, const Point2D* const _point, const char *_name)
{
/*base*/
	__Point2D_CTOR_const_Point2D_ptr((Point2D*)_this, _point);
/*MIL*/
	_this->m_name = _name;
/*body*/
}


void __NamedPoint2D_DTOR(NamedPoint2D* const _this)
{
/*body*/

/*base*/		
	__Point2D_DTOR((Point2D*)_this);
}

/*
const char *NamedPoint2D::GetName() const
{
	return m_name;
}
*/

const char* __NamedPoint2D_const_GetName(const NamedPoint2D* const _this)
{
	return _this->m_name;
}



/*----------------------------------------------------------------*/
/*
class Rectangle
{
public:
	Rectangle(const Point2D& _a, const Point2D& _b, const char *_name = "anonymous Rectangle");

	const char *GetName() const;
	double CalcArea() const;

private:
	NamedPoint2D m_a;
	Point2D m_b;
	static const int s_curvature = 1;	
};
*/

#define __RECTANGLE_S_CURVATURE 1	

typedef struct Rectangle
{
	NamedPoint2D m_a;
	Point2D m_b;
	
} Rectangle;

/*
Rectangle::Rectangle(const Point2D& _a, const Point2D& _b, const char *_name)
: m_a(_a, _name), m_b(_b)
{
}
*/



void __Rectangle_CTOR_const_Point2D_ptr_const_Point2D_ptr_const_char_ptr
	(Rectangle * const _this, const Point2D* const _a, const Point2D* const _b, const char *_name)
{
/*base*/

/*MIL*/
	__NamedPoint2D_CTOR_const_Point2D_ptr_const_char_ptr(&(_this->m_a),_a,_name);
	
	__Point2D_CTOR_const_Point2D_ptr(&(_this->m_b),_b);

/*body*/
}



void __Rectangle_DTOR(Rectangle * const _this)
{
/*body*/

/*base*/
	__Point2D_DTOR(&(_this->m_b));
	
	__NamedPoint2D_DTOR(&(_this->m_a));
}

/*
const char *Rectangle::GetName() const
{
	return m_a.GetName();
}
*/

const char* __Rectangle_const_GetName(const Rectangle * const _this)
{
	return __NamedPoint2D_const_GetName(&(_this->m_a));
}


/*
double Rectangle::CalcArea() const
{
	Point2D p1(m_a.GetX(), m_b.GetY());
	double sideA = m_a.Distance(p1);
	double sideB = m_a.Distance(Point2D(m_b.GetX(), m_a.GetY()));
	return sideA * sideB * s_curvature;
}
*/

double __Rectangle_const_CalcArea(const Rectangle * const _this)
{
	Point2D p1;
	double sideA;
	double sideB;
	
	Point2D temp_Point2D;
	
	__Point2D_CTOR_double_double(&p1,
		__Point2D_const_GetX((Point2D*)(&(_this->m_a))), 
		__Point2D_const_GetY(&(_this->m_b)));
	
	
	sideA = __Point2D_const_Distance_const_Point2D_ptr((Point2D*)(&(_this->m_a)), &p1);
	
	__Point2D_CTOR_double_double(&temp_Point2D, 
		__Point2D_const_GetX(&(_this->m_b)),
		__Point2D_const_GetY((Point2D*)(&(_this->m_a))));
		
	sideB = __Point2D_const_Distance_const_Point2D_ptr((Point2D*)(&(_this->m_a)), &temp_Point2D);
	
	__Point2D_DTOR(&temp_Point2D);
	__Point2D_DTOR(&p1);
	
	return sideA * sideB * __RECTANGLE_S_CURVATURE;
}




/*----------------------------------------------------------------*/
/*
void dog()
{
	NamedPoint2D home(5,7, "home");
	Point2D point(home);
	NamedPoint2D dog(point);

	dog *= 2;
	printf("Distance from %s to %s is %f\n", home.GetName(), dog.GetName(), home.Distance(dog));
}
*/


void dog()
{
	NamedPoint2D home;
	Point2D point;
	NamedPoint2D dog;
	
	
	__NamedPoint2D_CTOR_double_double_const_char_ptr(&home, 5, 7, "home");
	__Point2D_CTOR_const_Point2D_ptr(&point, (const Point2D*)&home);
	__NamedPoint2D_CTOR_const_Point2D_ptr_const_char_ptr(&dog, &point, "anonymous Point");

	__Point2D_operatormultiplyequal_double((Point2D*)&dog, 2);

	printf("Distance from %s to %s is %f\n", 
		__NamedPoint2D_const_GetName(&home),
		__NamedPoint2D_const_GetName(&dog),
		__Point2D_const_Distance_const_Point2D_ptr((Point2D*)&home, (Point2D*)&dog));
	
	__NamedPoint2D_DTOR(&dog);
	__Point2D_DTOR(&point);
	__NamedPoint2D_DTOR(&home);

}

/*
void area()
{
	Point2D p0;
	Point2D p1(12,12);
	Rectangle r(p0, p1);
	
	printf("The area of %s is %f\n", r.GetName(), r.CalcArea());
	printf("rectangle size %zu", sizeof(r));
}
*/

void area()
{
	Point2D p0;
	Point2D p1;
	Rectangle r;
	
	__Point2D_CTOR(&p0);
	__Point2D_CTOR_double_double(&p1,12,12);
	__Rectangle_CTOR_const_Point2D_ptr_const_Point2D_ptr_const_char_ptr(
		&r, &p0, &p1, "anonymous Rectangle");

	printf("The area of %s is %f\n", 
		__Rectangle_const_GetName(&r),
		__Rectangle_const_CalcArea(&r));

	printf("rectangle size %lu", sizeof(r));
	
	__Rectangle_DTOR(&r);
	__Point2D_DTOR(&p1);
	__Point2D_DTOR(&p0);
}





#endif
/* }} ***** Phase 2 *****/

/*----------------------------------------------------------------*/

int main()
{
#if PHASE >= 1
	pointless();
#endif

#if PHASE >= 2
	dog();
	area();
#endif

	return 0;
}

