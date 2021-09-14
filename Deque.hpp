#ifndef DEQUE_HPP
#define DEQUE_HPP

void push_b(struct Deque_int * deque, int value);
void push_f(struct Deque_int * deque, int value);
int container_size(struct Deque_int * deque);
void pop_b(struct Deque_int * deque);
void pop_f(struct Deque_int * deque);
void clear_deq(struct Deque_int * deque);
void destructor(struct Deque_int * deque);
int empt(struct Deque_int * deque);
int* elem_at(struct Deque_int * deque, int index);
int* front_elem(struct Deque_int * deque);
int* back_elem(struct Deque_int * deque);
struct Deque_int_Iterator beginning(struct Deque_int * deque);
struct Deque_int_Iterator ending(struct Deque_int * deque);
void Deque_int_ctor(struct Deque_int *, bool (* f)(const int, const int));
int dereference(struct Deque_int_Iterator * it);


struct Deque_int{
	int* container;
	char * type_name;
	int capacity;
	void (*push_back)(struct Deque_int *, int);
	void (*push_front)(struct Deque_int *, int);
	int (*size)(struct Deque_int *);
	void (*pop_back)(struct Deque_int *);
	void (*pop_front)(struct Deque_int *);
	void (*clear)(struct Deque_int *);
	void (*dtor)(struct Deque_int *);
	int (*empty)(struct Deque_int *);
	int* (*at)(struct Deque_int *, int);
	int* (*front)(struct Deque_int *);
	int* (*back)(struct Deque_int *);
	struct Deque_int_Iterator (*begin)(struct Deque_int *);
	struct Deque_int_Iterator (*end)(struct Deque_int *);
};

void Deque_int_ctor(struct Deque_int * deque, bool (* f)(const int, const int)){
	deque->container = malloc(0);
	deque->type_name = "Deque_int";
	deque->capacity = 0;
	deque->push_back = &push_b;
	deque->push_front = &push_f;
	deque->size = &container_size;
	deque->pop_back = &pop_b;
	deque->pop_front = &pop_f;
	deque->clear = &clear_deq;
	deque->dtor = &destructor;
	deque->empty = &empt;
	deque->at = &elem_at;
	deque->front = &front_elem;
	deque->back = &back_elem;
	deque->begin = &beginning;
	deque->end = &ending;
}

void push_b(struct Deque_int * deque, int value){
	deque->container = realloc(deque->container, sizeof(deque->container) + sizeof(int));
	(deque->container)[deque->capacity] = value;
	deque->capacity = deque->capacity + 1;
}

void push_f(struct Deque_int * deque, int value){
	int* temp = malloc(sizeof(deque->container) + sizeof(int));
	temp[0] = value;
	deque->capacity = deque->capacity + 1;
	for(int i=0; i<deque->capacity; i++){
		temp[i+1] = (deque->container)[i];
	}
	deque->container = temp;
	free(deque->container);
	deque->container = temp;
}

int container_size(struct Deque_int * deque){
	return sizeof(deque->container);
}

void pop_b(struct Deque_int * deque){
	deque->container = realloc(deque->container, sizeof(deque->container) - sizeof(int));
	deque->capacity = deque->capacity - 1;
}

void pop_f(struct Deque_int * deque){
	int* temp = malloc(sizeof(deque->container) - sizeof(int));
	for(int i=1; i<deque->capacity; i++){
		temp[i-1] = (deque->container)[i];
	}
	deque->capacity = deque->capacity - 1;
}

void clear_deq(struct Deque_int * deque){
	free(deque->container);
	(deque->capacity) = 0;
}

void destructor(struct Deque_int * deque){

}

int empt(struct Deque_int * deque){
	if((deque->capacity) == 0){
		return 0;
	}
	return 1;
}

int elem_at(struct Deque_int * deque, int index){
	return (deque->container)[index];
}


struct Deque_int_Iterator beginning(struct Deque_int * deque){
	return deque->container;
}

struct Deque_int_Iterator ending(struct Deque_int * deque){
	return deque->container + (sizeof(deque->container));
}

int* front_elem(struct Deque_int * deque){
	return 0;
}

int* back_elem(struct Deque_int * deque){
 return 0;
}

int dereference(struct Deque_int_Iterator * it){
	return *(*it).location;
}


struct Deque_int_Iterator{
	int * location;
	void (* inc)(struct Deque_int_Iterator *);
	void (* dec)(struct Deque_int_Iterator *);
	int (* deref)(struct Deque_int_Iterator *);
}



#define Deque_DEFINE


#endif
