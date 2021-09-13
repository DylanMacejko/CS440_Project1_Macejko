#ifndef DEQUE_HPP
#define DEQUE_HPP


void push_b(struct Deque_int * deque, int value){
	(*deque).container = realloc(container, sizeof(container) + sizeof(int));
	(*deque).container[capacity] = value;
	(*deque).capacity = (*deque).capacity + 1
}

void push_f(struct Deque_int * deque, int value){
	//include the reallocation of elements here, figure out circular dynamic array allocation
	(*deque).container[0] = value;
	(*deque).capacity = (*deque).capacity + 1;
}

int container_size(struct Deque * deque){
	return (*deque).capacity;
}

void pop_b(struct Deque * deque){

}

void pop_f(struct Deque * deque){

}

void clear_deq(struct Deque * deque){

}

void destructor(struct Deque * deque){

}


void Deque_int_ctor(struct Deque_int *, bool (* f)(const int, const int){
	container = malloc(sizeof(int));
	type_name = "int";
	capacity = 1;
	push_back = &push_b;
	push_front = &push_f;
	size = &container_size;
	pop_back = &pop_b;
	pop_front = &pop_f;
	clear = &clear_deq;
	dtor = &destructor;
}


struct Deque_int{	
	int* container;
	char * type_name;
	void (*push_back)(struct Deque_int *, int);
	void (*push_front)(struct Deque_int *, int);
	int (*size)(struct Deque_int *);
	void (*pop_back)(struct Deque_int *);
	void (*pop_front)(struct Deque_int *);
	void (*clear)(struct Deque_int *);
	void (*dtor)(struct Deque_int *);
}

struct Deque_int_Iterator{
	Deque_int_Iterator (* begin)(struct Deque_int *);
	Deque_int_Iterator (* end)(struct Deque_int *);
	void (* inc)(struct Deque_int_Iterator *);
	void (* dec)(struct Deque_int_Iterator *);
	void (* deref)(struct Deque_int_Iterator *);
}



#define Deque_DEFINE


#endif
