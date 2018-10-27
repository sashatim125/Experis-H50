#include <stdio.h>
#include <stdlib.h>
/*
struct Color {
	enum ColorEnum { RED, GREEN, DEFAULT };
	static void setColor(ColorEnum color){		
		static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
		std::puts(pallete[color]);
	}
};
*/

typedef enum __Color_ColorEnum { __Color_RED, __Color_GREEN, __Color_DEFAULT } __Color_ColorEnum;

void __Color_setColor___Color_ColorEnum(__Color_ColorEnum color)
{		
	static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
	fputs(pallete[color], stdout);
}

/*
class Scaleable {
public:
	virtual ~Scaleable() { }	
	virtual void scale(double) = 0;
};
*/

typedef struct __Scaleable __Scaleable;


void __Scaleable_DTOR (__Scaleable* const _this)
{}

void __PureVirtualCall()
{
	fprintf(stderr,"CALL TO PURE VIRTUAL FUNCTION! \n");
	abort();
}


typedef
struct __Scaleable_VT_t
{
	void(*m_DTOR)(__Scaleable * const);
	void(*m_scale_double)(__Scaleable * const, double);
	
} __Scaleable_VT_t;

static __Scaleable_VT_t const __Scaleable_VT= {__Scaleable_DTOR, (void(*)(__Scaleable*, double))__PureVirtualCall};


struct __Scaleable
{
	const void* m_vptr;
	
};

void __Scaleable_CTOR(__Scaleable* const _this)
{
	_this->m_vptr = &__Scaleable_VT;
}

typedef struct __Shape __Shape;

typedef
struct __Shape_VT_t
{
/*base*/
	void(*m_DTOR)(__Scaleable * const);
	
	void(*m_scale_double)(__Scaleable * const, double);
/*der*/
	void (*m_draw_const)(const __Shape * const);
	
	void (*m_draw_const___Color_ColorEnum)(const __Shape * const, __Color_ColorEnum);
	
	double (*m_area_const)(const __Shape * const);
	
} __Shape_VT_t;

static int __Shape_NumOfShapes = 0;

struct __Shape
{
	__Scaleable m_base;
	
	int m_id;
};




void __Shape_draw_const(const __Shape * const _this)
{
	printf("Shape::draw() - %d\n", _this->m_id);
}

void __Shape_draw_const___Color_ColorEnum(const __Shape * const _this, __Color_ColorEnum _c)
{
	printf("Shape::draw(c) - %d\n",_this-> m_id);
	__Color_setColor___Color_ColorEnum(_c);
	((__Shape_VT_t*)_this)->m_draw_const(_this);
	__Color_setColor___Color_ColorEnum(__Color_DEFAULT);
}

void __Shape_scale_double(__Shape * const _this, double f)
{ 
	printf("Shape::scale(%f)\n", f);
}

double __Shape_area_const(const __Shape * const _this)
{
	return -1;
}

void __Shape_printInventory()
{
	printf("Shape::printInventory - %d\n", __Shape_NumOfShapes);
}

void __Shape_DTOR(__Shape * const _this)
{
/*body*/
	__Shape_draw_const(_this);
	
	--__Shape_NumOfShapes; 
	
	printf("Shape::~Shape - %d\n", _this->m_id);
/*base*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Scaleable_VT;
	__Scaleable_DTOR((__Scaleable*)_this);
}

static __Shape_VT_t const __Shape_VT=
{
	(void(*)(__Scaleable * const))__Shape_DTOR,
	(void(*)(__Scaleable * const, double))__Shape_scale_double,	
	__Shape_draw_const,
	__Shape_draw_const___Color_ColorEnum,
	__Shape_area_const
};


void __Shape_CTOR(__Shape * const _this)
{
/*base*/
	__Scaleable_CTOR((__Scaleable * const)_this);
/*mil*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Shape_VT;
	_this->m_id = ++__Shape_NumOfShapes;
/*body*/	
	printf("Shape::Shape() - %d\n", _this->m_id); 
}

void __Shape_CTOR___Shape_const_ptr(__Shape * const _this, const __Shape * const _other)
{
/*base*/
	__Scaleable_CTOR((__Scaleable * const)_this);
/*mil*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Shape_VT;
	_this->m_id = ++__Shape_NumOfShapes;
/*body*/
	printf("Shape::Shape(Shape&) - %d from - %d\n", _this->m_id, _other->m_id);
}






/*
class Shape : public Scaleable {
public:
	Shape() : m_id(++NumOfShapes) {
		std::printf("Shape::Shape() - %d\n", m_id); 
	}
	
	virtual
	~Shape() {
		draw();
		--NumOfShapes; 
		std::printf("Shape::~Shape - %d\n", m_id);
	}

	Shape(const Shape& other) : m_id(++NumOfShapes) {
		std::printf("Shape::Shape(Shape&) - %d from - %d\n", m_id, other.m_id);
	}

	virtual void draw() const {
		std::printf("Shape::draw() - %d\n", m_id);		
	}
	
	virtual void draw(Color::ColorEnum c) const {
		std::printf("Shape::draw(c) - %d\n", m_id);
		Color::setColor(c);
		draw();
		Color::setColor(Color::DEFAULT);
	}
	
	virtual void scale(double f = 1) { 
		std::printf("Shape::scale(%f)\n", f);
	}
	virtual double area() const { return -1; }
	
	static void printInventory() {
		std::printf("Shape::printInventory - %d\n", NumOfShapes);
	}

private:
	static int NumOfShapes;
	Shape& operator=(const Shape &); // disabled, no implementation provided

protected:
	 int m_id;
};

int Shape::NumOfShapes = 0;
*/

typedef struct __Circle __Circle;

typedef
struct __Circle_VT_t
{
/*base*/
	void(*m_DTOR)(__Scaleable * const);
	
	void(*m_scale_double)(__Scaleable * const, double);

	void (*m_draw_const)(const __Shape * const);
	
	void (*m_draw_const___Color_ColorEnum)(const __Shape * const, __Color_ColorEnum);
	
	double (*m_area_const)(const __Shape * const);
	
} __Circle_VT_t;


struct __Circle
{
	__Shape m_base;
	
	double m_radius;
};

void __Circle_draw_const(const __Circle * const _this)
{
	printf("Circle::draw()  - %d, r:%f\n", ((__Shape*)_this)->m_id, _this->m_radius);
}

void __Circle_scale_double(__Circle * const _this, double f)
{ 
	printf("Circle::scale(%f)\n", f);
	_this->m_radius *= f;
}

double __Circle_area_const(const __Circle * const _this)
{
	return _this->m_radius * _this->m_radius * 3.1415;
}

double __Circle_radius_const(const __Circle * const _this)
{ 
	printf("Circle::draw()  - %d, r:%f\n", ((__Shape*)_this)->m_id, _this->m_radius);
	return _this->m_radius;
}

void __Circle_DTOR(__Circle * const _this)
{
/*body*/
	printf("Circle::~Circle() - %d, r:%f\n", ((__Shape*)_this)->m_id, _this->m_radius);
/*base*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Shape_VT;
	__Shape_DTOR((__Shape * const)_this);
}

static __Circle_VT_t const __Circle_VT=
{
	(void(*)(__Scaleable * const))__Circle_DTOR,
	(void(*)(__Scaleable * const, double))__Circle_scale_double,	
	(void (*)(const __Shape * const))__Circle_draw_const,
	__Shape_draw_const___Color_ColorEnum,
	(double (*)(const __Shape * const))__Circle_area_const
};


void __Circle_CTOR(__Circle * const _this)
{
/*base*/
	__Shape_CTOR((__Shape * const)_this);
/*mil*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Circle_VT;
	_this->m_radius = 1;
/*body*/
	printf("Circle::Circle() - %d, r:%f\n", ((__Shape*)_this)->m_id, _this->m_radius);
}

void __Circle_CTOR_double(__Circle * const _this, double _r)
{
/*base*/
	__Shape_CTOR((__Shape * const)_this);
/*mil*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Circle_VT;
	_this->m_radius = _r;
/*body*/
	printf("Circle::Circle(double) - %d, r:%f\n", ((__Shape*)_this)->m_id, _this->m_radius); 
}

void __Circle_CTOR___Circle_const_ptr(__Circle * const _this, const __Circle * const _other)
{
/*base*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Circle_VT;
	__Shape_CTOR___Shape_const_ptr((__Shape * const)_this,(__Shape * const)_other);
/*mil*/
	_this->m_radius =_other->m_radius;
	printf("Circle::Circle(Circle&) - %d, r:%f\n", ((__Shape*)_this)->m_id, _this->m_radius);
}


/*
class Circle : public Shape {	
public:
	Circle() : m_radius(1) { 
		std::printf("Circle::Circle() - %d, r:%f\n", m_id, m_radius); 
	}

	Circle(double r) : m_radius(r) { 
		std::printf("Circle::Circle(double) - %d, r:%f\n", m_id, m_radius); 
	}

	Circle(const Circle& other)
	: Shape(other), m_radius(other.m_radius) { 
		std::printf("Circle::Circle(Circle&) - %d, r:%f\n", m_id, m_radius);
	}

	~Circle() { 
		std::printf("Circle::~Circle() - %d, r:%f\n", m_id, m_radius); 
	}

	void draw() const { 
		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
	}

	void scale(double f = 2) {
		std::printf("Circle::scale(%f)\n", f);
		m_radius *= f;
	}
    
	double area() const {
		return m_radius * m_radius * 3.1415;	
	}

	double radius() const { 
		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
		return m_radius;
	}

private:
	double m_radius;
};
*/

typedef struct __Rectangle __Rectangle;

typedef
struct __Rectangle_VT_t
{
/*base*/
	void(*m_DTOR)(__Scaleable * const);
	
	void(*m_scale_double)(__Scaleable * const, double);

	void (*m_draw_const)(const __Shape * const);
	
	void (*m_draw_const___Color_ColorEnum)(const __Shape * const, __Color_ColorEnum);
	
	double (*m_area_const)(const __Shape * const);
	
} __Rectangle_VT_t;


struct __Rectangle
{
	__Shape m_base;
	
	int m_a;
	int m_b;
};

void __Rectangle_draw_const(const __Rectangle * const _this)
{
	printf("Rectangle::draw()  - %d, [%d, %d]\n", ((__Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

void __Rectangle_draw_const___Color_ColorEnum(const __Rectangle * const _this, __Color_ColorEnum c)
{
	printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c, ((__Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

void __Rectangle_scale_double(__Rectangle * const _this, double f)
{ 
	printf("Rectangle::scale(%f)\n", f);
	_this->m_a *= f;
	_this->m_b *= f;
}

double __Rectangle_area_const(const __Rectangle * const _this)
{
	return _this->m_a * _this->m_b;
}


void __Rectangle_DTOR(__Rectangle * const _this)
{
/*body*/
	printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", ((__Shape*)_this)->m_id, _this->m_a, _this->m_b);
/*base*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Shape_VT;
	__Shape_DTOR((__Shape*)_this);
}

static __Rectangle_VT_t const __Rectangle_VT =
{
	(void(*)(__Scaleable * const))__Rectangle_DTOR,
	(void(*)(__Scaleable * const, double))__Rectangle_scale_double,	
	(void (*)(const __Shape * const))__Rectangle_draw_const,
	(void (*)(const __Shape * const, __Color_ColorEnum))__Rectangle_draw_const___Color_ColorEnum,
	(double (*)(const __Shape * const))__Rectangle_area_const
};


void __Rectangle_CTOR(__Rectangle * const _this)
{
/*base*/
	__Shape_CTOR((__Shape * const)_this);
/*mil*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Rectangle_VT;
	_this->m_a = 1;
	_this->m_b = 1;
/*body*/
	printf("Rectangle::Rectangle() - %d, [%d, %d]\n", ((__Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

void __Rectangle_CTOR_int(__Rectangle * const _this,int a)
{
/*base*/
	__Shape_CTOR((__Shape * const)_this);
/*mil*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Rectangle_VT;
	_this->m_a = a;
	_this->m_b = a;
/*body*/
	printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", ((__Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

void __Rectangle_CTOR_int_int(__Rectangle * const _this,int a, int b)
{
/*base*/
	__Shape_CTOR((__Shape * const)_this);
/*mil*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Rectangle_VT;
	_this->m_a = a;
	_this->m_b = b;
/*body*/
	printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", ((__Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

void __Rectangle_CTOR___Rectangle_const_ptr(__Rectangle * const _this, const __Rectangle * const _other)
{
/*base*/
	__Shape_CTOR___Shape_const_ptr((__Shape * const)_this,(__Shape * const)_other);
/*mil*/
	*(__Scaleable_VT_t**)_this = (__Scaleable_VT_t*)&__Rectangle_VT;
	_this->m_a = _other->m_a;
	_this->m_b = _other->m_b;
/*body*/
	printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", ((__Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

/*
class Rectangle: public Shape {
public:
	Rectangle() : m_a(1), m_b(1) { 
		std::printf("Rectangle::Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
	}

	Rectangle(int a) : m_a(a), m_b(a) { 
		std::printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", m_id, m_a, m_b);
	}

	Rectangle(int a, int b) : m_a(a), m_b(b) { 
		std::printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", m_id, m_a, m_b);
	}
	
	Rectangle(const Rectangle &other ) 
	: m_a(other.m_a), m_b(other.m_b), Shape(other) { 
		std::printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", m_id, m_a, m_b);
	}
	
	~Rectangle() { 
		std::printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
	}

	void draw() const { 
		std::printf("Rectangle::draw()  - %d, [%d, %d]\n", m_id, m_a, m_b);
	}

    void draw(Color::ColorEnum c) const {
		std::printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c, m_id, m_a, m_b);
	}

	void scale(double f = 4){
		std::printf("Rectangle::scale(%f)\n", f);
		m_a *= f;
		m_b *= f;
	}

	double area() const {
		return m_a * m_b;
	}

private:
	int m_a, m_b;
};

*/

void __report___Shape_const_ptr(const __Shape * const s)
{
	puts("-----report-----");
	
	(*(__Shape_VT_t**)s)->m_draw_const(s);

	__Shape_printInventory();
	
	puts("-----report-----");
}


/*
void report(const Shape& s) {
	std::puts("-----report-----");
	s.draw(); 
	Shape::printInventory();
	std::puts("-----report-----");
}
*/

/* C code !!!!
inline void draw(Shape& obj)

	puts("-----draw(Shape&)-----");
	((__Shape_VT_t*)s)->m_scale_double(obj);
	((__Shape_VT_t*)s)->m_draw_const(obj);
	puts("-----draw(Shape&)-----");
*/


/*
inline void draw(Shape& obj) { 
	std::puts("-----draw(Shape&)-----");
	obj.scale();
	obj.draw();	
	std::puts("-----draw(Shape&)-----");
}
*/

__Circle unit;
int is_unit_init = 0;


void __draw___Circle_val(const __Circle * const c)
{
	__Circle l_c;
	__Circle_CTOR___Circle_const_ptr(&l_c,c);
	
	puts("-----draw(Circle)-----");

	if(!is_unit_init)
	{
		__Circle_CTOR_double(&unit,1);
		++is_unit_init;
	}
	
	__Circle_draw_const(&unit);

	__Circle_scale_double(&unit,3);

	__Circle_draw_const(&l_c);
	
	puts("-----draw(Circle)-----");
	
	__Circle_DTOR(&l_c);
}

/*
void draw(Circle c) { 
	std::puts("-----draw(Circle)-----");

	static Circle unit(1);
	
	unit.draw();
	unit.scale(3);
	c.draw(); 
	std::puts("-----draw(Circle)-----");
}
*/

void doObjArray()
{
	__Shape objects[3];
	union
	{
		__Circle c;
		__Rectangle r;
		int i;	
	}temp;
	
	__Circle_CTOR(&(temp.c));
	__Shape_CTOR___Shape_const_ptr(&objects[0],(__Shape*)&(temp.c));
	__Circle_DTOR(&(temp.c));
	
	__Rectangle_CTOR_int(&(temp.r),4);
	__Shape_CTOR___Shape_const_ptr(&objects[1],(__Shape*)&(temp.r));
	__Rectangle_DTOR(&(temp.r));
		
	__Circle_CTOR_double(&(temp.c),9);
	__Shape_CTOR___Shape_const_ptr(&objects[2],(__Shape*)&(temp.c));
	__Circle_DTOR(&(temp.c));

    for(temp.i = 0; temp.i < 3; ++temp.i) 
		__Shape_draw_const(&objects[temp.i]);
		
	for(temp.i = 2; temp.i >= 0; --temp.i) 
		__Shape_DTOR(&objects[temp.i]);
}

/*
void doObjArray(){
	Shape objects[] = {
	    Circle(),
	    Rectangle(4),
	    Circle(9)
	};

    for(int i = 0; i < 3; ++i) 
		objects[i].draw();
}
*/


void disappear()
{
	puts("-----disappear-----");

	__Circle defaultCircle();

	puts("-----disappear-----");
}


/*
void disappear() {
	std::puts("-----disappear-----");

	Circle defaultCircle();

	std::puts("-----disappear-----");
}
*/

/*
template <class T>
double diffWhenDoubled(T& shape){
	double a0 = shape.area();
	shape.scale(2);
	double a1 = shape.area();
	return a1 - a0;
}
*/


void doPointerArray()
{
	puts("-----doPointerArray-----");
	
	__Shape *array[3];
	int i;
	array[0] = malloc(sizeof(__Circle));
	array[1] = malloc(sizeof(__Rectangle));
	array[2] = malloc(sizeof(__Circle));
	
	__Circle_CTOR((__Circle*)array[0]);
	__Rectangle_CTOR_int((__Rectangle*)array[1],3);
	__Circle_CTOR_double((__Circle*)array[2], 4);
	
    for(i = 0; i < 3; ++i)
    { 
    	(*(__Shape_VT_t**)array[i])->m_scale_double((__Scaleable*)array[i],1);
    	(*(__Shape_VT_t**)array[i])->m_draw_const((__Shape*)array[i]);
	}
	
	double diffWhenDoubled___Shape_ptr(__Shape * const shape)
	{
		double a0 = (*(__Shape_VT_t**)shape)->m_area_const((__Shape*)shape);
		
		(*(__Shape_VT_t**)shape)->m_scale_double((__Scaleable*)shape,2);
		
		double a1 = (*(__Shape_VT_t**)shape)->m_area_const((__Shape*)shape);
		
		return a1 - a0;
	}

	printf("area: %f\n", diffWhenDoubled___Shape_ptr(array[2]));

    for(i= 0; i < 3; ++i)
    {
    	(*(__Shape_VT_t**)array[i])->m_DTOR((__Scaleable*)array[i]);
    	free(array[i]); 
		array[i] = 0; 
	}

	puts("-----doPointerArray-----");
}

/*
void doPointerArray(){
	std::puts("-----doPointerArray-----");
	Shape *array[] =  {
	    new Circle(),
	    new Rectangle(3),
	    new Circle(4)
	};

    for(int i = 0; i < 3; ++i){ 
		array[i]->scale();
		array[i]->draw();
	}

	std::printf("area: %f\n", diffWhenDoubled(*array[2]));

    for(int i = 0; i < 3; ++i) { 
		delete array[i]; 
		array[i] = 0; 
	}

	std::puts("-----doPointerArray-----");
}
*/

void dispose__Rectangle_ptr(__Rectangle* p)
{
	size_t *start , num, i;
	
	start = ((size_t*)p)-1;
	
	num = *start;
	
	for(i = num-1; i >= 0 && i != -1; --i)
	{
		__Rectangle_DTOR(p+i);
	}
	
	free(start);
}

/*
void dispose(Rectangle* p){
  delete[] p;
}
*/

typedef
struct __Empty
{
	char m_min_size;
} __Empty;

void __Empty_CTOR(__Empty * const _this, int id)
{
	printf("Empty::Empty(%d)\n", id);
}

void __Empty_DTOR(__Empty * const _this)
{
	puts("Empty::~Empty()");
}

/*
class Empty {
public:
    Empty(int id = 0) { std::printf("Empty::Empty(%d)\n", id); }
   ~Empty() { std::puts("Empty::~Empty()");}	
};
*/

typedef
struct __EmptyEmpty
{
	int m_i;
	
} __EmptyEmpty;

void __EmptyEmpty_CTOR(__EmptyEmpty * const _this, int id)
{
/*base*/
	__Empty_CTOR((__Empty * const) _this,0);
/*mil*/
	_this->m_i = id;
/*body*/
	printf("EmptyEmpty::EmptyEmpty(%d)\n", _this->m_i); 
}

void __EmptyEmpty_DTOR(__EmptyEmpty * const _this)
{
/*base*/
	__Empty_DTOR((__Empty * const) _this);
}


/*
class EmptyEmpty  : public Empty{
	int m_i;
public:
	EmptyEmpty(int id) : m_i(id){
		 std::printf("EmptyEmpty::EmptyEmpty(%d)\n", m_i); 
	}
};
*/

typedef
struct __EmptyBag
{
	__EmptyEmpty ee;
	
} __EmptyBag;


void __EmptyBag_CTOR(__EmptyBag * const _this)
{
/*mil*/
	__Empty_CTOR((__Empty * const) _this,1);
	__Empty_CTOR((__Empty * const) _this,2);
	__EmptyEmpty_CTOR(&(_this->ee),2);
	
/*body*/
	puts("EmptyBag::EmptyBag()");
}

void __EmptyBag_DTOR(__EmptyBag * const _this)
{
/*body*/
	puts("EmptyBag::~EmptyBag");
/*base*/
	__EmptyEmpty_DTOR(&(_this->ee));
	__Empty_DTOR((__Empty * const) _this);
	__Empty_DTOR((__Empty * const) _this);
}


/*
class EmptyBag {
	Empty e1;
	Empty e2;
	EmptyEmpty ee;
public: 
	EmptyBag() : e2(2), e1(1), ee(2) {
		std::puts("EmptyBag::EmptyBag()");
	}
	~EmptyBag(){
		std::puts("EmptyBag::~EmptyBag");
	}	
};
*/

int main(int argc, char **argv, char **envp)
{
    __Circle c;
	__Rectangle s;
    __Circle c2;
    
	printf("---------------Start----------------\n");
	
	__Circle_CTOR(&c);
	__Rectangle_CTOR_int(&s,4);

	printf("0.-------------------------------\n");
	__draw___Circle_val(&c);


	printf("+..............\n");
	__draw___Circle_val(&c);

	printf("+..............\n");
			
	puts("-----draw(Shape&)-----");
	(*(__Shape_VT_t**)&s)->m_scale_double((__Scaleable*)&s,1);
	(*(__Shape_VT_t**)&s)->m_draw_const((__Shape*)&s);
	puts("-----draw(Shape&)-----");

	printf("+..............\n");
		
	__report___Shape_const_ptr((__Shape*)&c);
	
	printf("1.-------------------------------\n");	

	doPointerArray();

	printf("2.-------------------------------\n");

    doObjArray();

	printf("3.-------------------------------\n");

    __Shape_printInventory();
    __Circle_CTOR___Circle_const_ptr(&c2,&c);
   __Shape_printInventory();

	printf("4.-------------------------------\n");

    __Circle olympics[5];
    
    int i;
    for(i=0; i<5; ++i)
    {
    	__Circle_CTOR(&olympics[i]);
    }
    
	double diffWhenDoubled___Circle_ptr(__Circle * const shape)
	{
		double a0 = (*(__Circle_VT_t**)shape)->m_area_const((__Shape*)shape);
		
		(*(__Circle_VT_t**)shape)->m_scale_double((__Scaleable*)shape,2);
		
		double a1 = (*(__Circle_VT_t**)shape)->m_area_const((__Shape*)shape);
		
		return a1 - a0;
	}
    
	printf("olympic diff %f\n", diffWhenDoubled___Circle_ptr(&olympics[1]));

	printf("5.-------------------------------\n");
	
	
	size_t *start = malloc(sizeof(__Rectangle)*4 + sizeof(size_t));
	
	__Rectangle* fourRectangles;
	/*
	if(!start)
	{
		return NULL;
	}
	*/
	
	*start = 4;
	
	fourRectangles = (__Rectangle*)(start+1);
	
	for(i=0; i<4; ++i)
	{
		__Rectangle_CTOR(fourRectangles+i);
	}
		
    dispose__Rectangle_ptr(fourRectangles);

	printf("6.-------------------------------\n");

	__EmptyBag eb;
	__EmptyBag_CTOR(&eb);
	
	printf("Empty things are: %zu %zu %zu", sizeof(__Empty), sizeof(__EmptyEmpty), sizeof(__EmptyBag) );
	
	printf("7.-------------------------------\n");
		
	disappear();	

	printf("---------------END----------------\n");
	
	
	__EmptyBag_DTOR(&eb);
	
	for(i=4; i>=0; --i)
    {
    	__Circle_DTOR(&olympics[i]);
    }
		
	__Circle_DTOR(&c2);
	__Rectangle_DTOR(&s);
	__Circle_DTOR(&c);
	if(is_unit_init)
	{
		__Circle_DTOR(&unit);
	}

}


/*int main(int argc, char **argv, char **envp)
{	
	std::printf("---------------Start----------------\n");
    Circle c;
	Rectangle s(4);

	std::printf("0.-------------------------------\n");		
	draw(c);

	std::printf("+..............\n");		
	draw(c);

	std::printf("+..............\n");		
    draw(s);

	std::printf("+..............\n");		
	report(c);

	std::printf("1.-------------------------------\n");	
	
    doPointerArray();

	std::printf("2.-------------------------------\n");

    doObjArray();

	std::printf("3.-------------------------------\n");

    Shape::printInventory();
    Circle c2 = c;
    c2.printInventory();

	std::printf("4.-------------------------------\n");
   
    Circle olympics[5];
	std::printf("olympic diff %f\n", diffWhenDoubled(olympics[1]));

	std::printf("5.-------------------------------\n");

    Rectangle *fourRectangles = new Rectangle[4];
    dispose(fourRectangles);

	std::printf("6.-------------------------------\n");
	EmptyBag eb;
	std::printf("Empty things are: %zu %zu %zu", sizeof(Empty), sizeof(EmptyEmpty), sizeof(EmptyBag) );
	
	std::printf("7.-------------------------------\n");
	disappear();	

	std::printf("---------------END----------------\n");

    return 0;
}
*/
