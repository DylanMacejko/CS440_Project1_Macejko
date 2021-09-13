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
	return sizeof((*deque).container);
}

void pop_b(struct Deque * deque){

}

void pop_f(struct Deque * deque){

}

void clear_deq(struct Deque * deque){

}

void destructor(struct Deque * deque){

}

void empty(struct Deque * deque){
	if(capacity == 0){
		return 0;
	}else{
		return 1;
	}
}

int elem_at(struct Deque * deque, int index){
	return ((*deque).container)[index];
}


void Deque_int_ctor(struct Deque_int *, bool (* f)(const int, const int){
	container = malloc(0);
	type_name = "Deque_int";
	capacity = 1;
	push_back = &push_b;
	push_front = &push_f;
	size = &container_size;
	pop_back = &pop_b;
	pop_front = &pop_f;
	clear = &clear_deq;
	dtor = &destructor;
	empty = &empt;
	at = &elem_at;
	front = &front_elem;
	back = &back_elem;
	begin = &beginning;
	end = &ending;
}

Deque_int_iterator beginning(struct Deque_int * deque){
	return (*deque).container;
}

Deque_int_iterator ending(struct Deque_int * deque){
	return (*deque).container + (sizeof((*deque).container));
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
	void (*empty)(struct Deque_int *);
	int* (*at)(struct Deque_int *, int);
	int* (*front)(struct Deque_int *);
	int* (*back)(struct Deque_int *);
	Deque_int_Iterator (*begin)(struct Deque_int *);
	Deque_int_Iterator (*end)(struct Deque_int *);
}


struct Deque_int_Iterator{
	void (* inc)(struct Deque_int_Iterator *);
	void (* dec)(struct Deque_int_Iterator *);
	int (* deref)(struct Deque_int_Iterator *);
}



#define Deque_DEFINE


#endif
