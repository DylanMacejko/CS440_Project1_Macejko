#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <cstdlib>
#include <cstdio>

struct Deque_int_Iterator{
	int * location;
	int * front_arr;
	int * back_arr;
	void (* inc)(struct Deque_int_Iterator *);
	void (* dec)(struct Deque_int_Iterator *);
	int (* deref)(struct Deque_int_Iterator *);
};

void increment(struct Deque_int_Iterator * it){

}

void decrement(struct Deque_int_Iterator * it){

}

int dereference(struct Deque_int_Iterator * it){
	return *(it->location);
}

int Deque_int_Iterator_equal(struct Deque_int_Iterator it1, struct Deque_int_Iterator it2){
	return 1;
}


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
	int num_elements;
	int* front_indicator;
	int* back_indicator;
	int* front_array;
	int* back_array;
	Deque_int_Iterator it;
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
	deque->container = (int*) malloc(0);
	deque->type_name = (char*) "Deque_int";
	deque->capacity = 0;
	deque->num_elements  = 0;
	deque->front_indicator = NULL;
	deque->back_indicator = NULL;
	deque->front_array = NULL;
	deque->back_array = NULL;
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

void push_f(struct Deque_int * deque, int value){
	if(deque->num_elements == 0){
		deque->container = (int*) malloc(((int)sizeof(int)) * 4);
		(deque->container)[1] = value;
		deque->num_elements = 1;
		deque->capacity = 4;
		deque->front_indicator = &((deque->container)[1]);
		deque->back_indicator = &((deque->front_indicator)[1]);
		deque->front_array = deque->container;
		deque->back_array = &(deque->container[4]);
	}else if(deque->num_elements > 0 && deque->num_elements == deque->capacity){
		int* temp = (int*) malloc(deque->capacity * 2);
		deque->capacity = 2 * deque->capacity;
		int start_index = (deque->capacity)/4;
		int* temp_front_indicator = &(temp[start_index]);
		for(Deque_int_Iterator it = deque->begin(deque); !Deque_int_Iterator_equal(it, deque->end(deque)); it.inc(&it)){
			temp[start_index] = it.deref(&it);
			start_index++;
		}
		int end_index = start_index;
		int* temp_back_indicator = &(temp[end_index]);
		free(deque->container);
		deque->container = temp;
		deque->front_indicator = temp_front_indicator;
		deque->back_indicator = temp_back_indicator;
		deque->front_indicator = &(deque->front_indicator[-1]);
		*(deque->front_indicator) = value;
		deque->num_elements = deque->num_elements + 1;
		deque->front_array = deque->container;
		deque->back_array = &(deque->container[deque->capacity]);
	}else{
		if(deque->front_indicator == deque->front_array){
			deque->front_indicator = &(deque->back_array[-1]);
			*(deque->front_indicator) = value;
			deque->front_indicator = &(deque->front_indicator[-1]);
			deque->num_elements = deque->num_elements + 1;
		}else{
			deque->front_indicator[-1] = value;
			deque->front_indicator = &(deque->front_indicator[-1]);
			deque->num_elements = deque->num_elements + 1;
		}
	}

}

void push_b(struct Deque_int * deque, int value){
	if(deque->num_elements == 0){
		deque->container = (int*) malloc(((int)sizeof(int)) * 4);
		(deque->container)[1] = value;
		deque->num_elements = 1;
		deque->capacity = 4;
		deque->front_indicator = &((deque->container)[1]);
		deque->back_indicator = &((deque->front_indicator)[1]);
		deque->front_array = deque->container;
		deque->back_array = &(deque->container[4]);
	}else if(deque->num_elements > 0 && deque->num_elements == deque->capacity){
		int* temp = (int*) malloc(deque->capacity * 2);
		deque->capacity = 2 * deque->capacity;
		int start_index = (deque->capacity)/4;
		int* temp_front_indicator = &(temp[start_index]);
		for(Deque_int_Iterator it = deque->begin(deque); !Deque_int_Iterator_equal(it, deque->end(deque)); it.inc(&it)){
			temp[start_index] = it.deref(&it);
			start_index++;
		}
		int end_index = start_index;
		int* temp_back_indicator = &(temp[end_index]);
		free(deque->container);
		deque->container = temp;
		deque->front_indicator = temp_front_indicator;
		deque->back_indicator = temp_back_indicator;
		deque->container[end_index] = value;
		deque->back_indicator = &(deque->back_indicator[1]);
		deque->num_elements = deque->num_elements + 1;
		deque->front_array = deque->container;
		deque->back_array = &(deque->container[deque->capacity]);
	}else{
		if(deque->back_indicator == deque->back_array){
			deque->back_indicator = deque->front_array;
			*(deque->back_indicator) = value;
			deque->back_indicator = &(deque->back_indicator[1]);
			deque->num_elements = deque->num_elements + 1;
		}else{
			*(deque->back_indicator) = value;
			deque->back_indicator = &(deque->back_indicator[1]);
			deque->num_elements = deque->num_elements + 1;
		}
	}

}

int container_size(struct Deque_int * deque){
	return sizeof(deque->container);
}

void pop_b(struct Deque_int * deque){
	if(deque->num_elements == 0){
		printf("Cannot pop from a deque of no elements");
	}

	if(deque->back_indicator == deque->front_array){
		//FINISH POP
	}

}

void pop_f(struct Deque_int * deque){
	if(deque->num_elements == 0){
		printf("Cannot pop from a deque of no elements");
	}

}

void clear_deq(struct Deque_int * deque){
	free(deque->container);
	deque->capacity = 0;
	deque->num_elements = 0;
	deque->front_indicator = NULL;
	deque->back_indicator = NULL;
	deque->front_array  = NULL;
	deque->back_array = NULL;
}

void destructor(struct Deque_int * deque){
	free(deque->container);
}

int empt(struct Deque_int * deque){
	if(deque->num_elements == 0){
		return 1;
	}
	return 0;
}

int* elem_at(struct Deque_int * deque, int index){
	return &(deque->container)[index];
}


struct Deque_int_Iterator beginning(struct Deque_int * deque){
	struct Deque_int_Iterator it;
	it.location = deque->front_indicator;
	it.front_arr = deque->front_array;
	it.back_arr = deque->back_array;
	it.inc = &increment;
	it.dec = &decrement;
	it.deref = &dereference;
	return it;
}

struct Deque_int_Iterator ending(struct Deque_int * deque){
	struct Deque_int_Iterator it;
	it.location = deque->front_indicator;
	it.front_arr = deque->front_array;
	it.back_arr = deque->back_array;
	it.inc = &increment;
	it.dec = &decrement;
	it.deref = &dereference;
	return it;
}

int* front_elem(struct Deque_int * deque){
	return *(deque->front_indicator);
}

int* back_elem(struct Deque_int * deque){
 return *(deque->back_indicator[-1]);
}


#define Deque_DEFINE


#endif
