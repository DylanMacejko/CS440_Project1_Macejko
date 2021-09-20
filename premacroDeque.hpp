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
	if(it->location == &(it->back_arr[-1])){
		it->location = it->front_arr;
	}else{
		it->location = &(it->location[1]);
	}
}

void decrement(struct Deque_int_Iterator * it){
	//CHECK TO SEE HERE IF WE NEED TO CHECK FOR BEGINNING OF ITERATOR AS WELL
	if(it->location == it->front_arr){
		it->location = it->back_arr;
	}else{
		it->location = &(it->location[-1]);
	}
}

int dereference(struct Deque_int_Iterator * it){
	return *(it->location);
}

int Deque_int_Iterator_equal(struct Deque_int_Iterator it1, struct Deque_int_Iterator it2){
	return it1.location == it2.location;
}



void push_b(struct Deque_int * deque, int value);
void push_f(struct Deque_int * deque, int value);
size_t container_size(struct Deque_int * deque);
void pop_b(struct Deque_int * deque);
void pop_f(struct Deque_int * deque);
void clear_deq(struct Deque_int * deque);
void destructor(struct Deque_int * deque);
int empt(struct Deque_int * deque);
int elem_at(struct Deque_int * deque, size_t index);
int front_elem(struct Deque_int * deque);
int back_elem(struct Deque_int * deque);
struct Deque_int_Iterator beginning(struct Deque_int * deque);
struct Deque_int_Iterator ending(struct Deque_int * deque);
void Deque_int_ctor(struct Deque_int *, bool (* f)(const int, const int));
int dereference(struct Deque_int_Iterator * it);
void qsort(struct Deque_int * deque, struct Deque_int_Iterator it1, struct Deque_int_Iterator it2);


struct Deque_int{
	int* container;
	int capacity;
	int num_elements;
	int* front_indicator;
	int* back_indicator;
	int* front_array;
	int* back_array;
	void (*push_back)(struct Deque_int *, int);
	void (*push_front)(struct Deque_int *, int);
	size_t (*size)(struct Deque_int *);
	void (*pop_back)(struct Deque_int *);
	void (*pop_front)(struct Deque_int *);
	void (*clear)(struct Deque_int *);
	void (*dtor)(struct Deque_int *);
	int (*empty)(struct Deque_int *);
	int (*at)(struct Deque_int *, size_t);
	int (*front)(struct Deque_int *);
	int (*back)(struct Deque_int *);
	struct Deque_int_Iterator (*begin)(struct Deque_int *);
	struct Deque_int_Iterator (*end)(struct Deque_int *);
	bool (* compare)(const int&, const int&);
	void (* sort)(struct Deque_int *, struct Deque_int_Iterator, struct Deque_int_Iterator);
	char type_name[sizeof("Deque_int")] = "Deque_int";

};

void Deque_int_ctor(struct Deque_int * deque, bool (* comparator)(const int&, const int&)){

	deque->container = (int*) malloc(0);
	//deque->type_name = (char*) malloc(sizeof("Deque_int"));
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
	deque->compare = comparator;
  deque->sort = &qsort;
}

void push_f(struct Deque_int * deque, int value){
	if(deque->num_elements == 0){
		//printf("Starting from scratch \n");
		free(deque->container);
		deque->container = (int*) malloc((sizeof(int)) * 8);
		*(deque->container) = value;
		deque->num_elements = 1;
		deque->capacity = 8;
		deque->front_indicator = deque->container;
		deque->back_indicator = &((deque->front_indicator)[1]);
		deque->front_array = deque->container;
		deque->back_array = &(deque->container[8]);
	}else if(deque->num_elements > 0 && deque->num_elements == deque->capacity-1){
		//printf("resizing\n");
		//printf("Resizing array\n");
		int* temp = (int*) malloc((sizeof(int) * deque->capacity * 2));
		deque->capacity = 2 * deque->capacity;
		int start_index = 0;
		int* temp_front_indicator = &(temp[start_index]);
		for(Deque_int_Iterator it = deque->begin(deque); !Deque_int_Iterator_equal(it, deque->end(deque)); it.inc(&it)){
			temp[start_index+1] = it.deref(&it);
			start_index++;
		}
		int end_index = start_index;
		int* temp_back_indicator = &(temp[end_index]);
		free(deque->container);
		deque->container = temp;
		deque->front_indicator = temp_front_indicator;
		deque->back_indicator = &(temp_back_indicator[1]);
		deque->front_indicator = deque->front_indicator;
		*(deque->front_indicator) = value;
		deque->num_elements = deque->num_elements + 1;
		deque->front_array = deque->container;
		deque->back_array = &(deque->container[deque->capacity]);
	}else{
		//printf("In the else\n");
		if(deque->front_indicator == deque->front_array){
			//printf("The front indicator matches the front of the array. Looping back");
			deque->front_indicator = &(deque->back_array[-1]);
			*(deque->front_indicator) = value;
			deque->num_elements = deque->num_elements + 1;
		}else{
			//printf("The front indicator does not match the front of the array. Moving back");
			deque->front_indicator[-1] = value;
			deque->front_indicator = &(deque->front_indicator[-1]);
			deque->num_elements = deque->num_elements + 1;
		}
	}

}

void push_b(struct Deque_int * deque, int value){
	if(deque->num_elements == 0){
		free(deque->container);
		deque->container = (int*) malloc(((int)sizeof(int)) * 8);
		*(deque->container) = value;
		deque->num_elements = 1;
		deque->capacity = 8;
		deque->front_indicator = deque->container;
		deque->back_indicator = &((deque->front_indicator)[1]);
		deque->front_array = deque->container;
		deque->back_array = &(deque->container[8]);
	}else if(deque->num_elements > 0 && deque->num_elements == deque->capacity-1){
		//printf("resizing\n");
		int* temp = (int*) malloc((int)(sizeof(int) * deque->capacity * 2));
		deque->capacity = 2 * deque->capacity;
		int start_index = 0;
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
		if(deque->back_indicator == &(deque->back_array[-1])){
		//	printf("looping to front in push");
			*(deque->back_indicator) = value;
			deque->back_indicator = deque->front_array;
			deque->num_elements = deque->num_elements + 1;
			//printf("finished loop appropriately");
		}else{
			*(deque->back_indicator) = value;
			deque->back_indicator = &(deque->back_indicator[1]);
			deque->num_elements = deque->num_elements + 1;
		}
	}

}

size_t container_size(struct Deque_int * deque){
	return (size_t)deque->num_elements;
}

void pop_b(struct Deque_int * deque){
	if(deque->num_elements != 0){
		if(deque->back_indicator == deque->front_array){
			deque->back_indicator = &(deque->back_array[-1]);
			*(deque->back_indicator) = 0;

		}else{
			deque->back_indicator[-1] = 0;
			deque->back_indicator = &(deque->back_indicator[-1]);
		}
		deque->num_elements = deque->num_elements - 1;
	}
}

void pop_f(struct Deque_int * deque){
	if(deque->num_elements != 0){
		*(deque->front_indicator) = 0;
		if(deque->front_indicator == &(deque->back_array[-1])){
			deque->front_indicator = deque->front_array;
		}else{
			deque->front_indicator = &(deque->front_indicator[1]);
		}
		deque->num_elements = deque->num_elements - 1;
	}

}

void clear_deq(struct Deque_int * deque){
	for(int i=0; i<deque->capacity; i++){
		deque->container[i] = 0;
	}
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

int elem_at(struct Deque_int * deque, size_t index){
	if(&(deque->front_indicator[index]) > &(deque->back_array[-1])){
		long int offset = &(deque->front_indicator[index])-&(deque->back_array[-1])-1;
		//printf("Front indicator after back array");
		//printf("This is the index produced by the offset: %ld", offset);
		return deque->front_array[offset];
	}
	//printf("Front indicator before back array");
	return (deque->front_indicator[index]);
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
	it.location = deque->back_indicator;
	it.front_arr = deque->front_array;
	it.back_arr = deque->back_array;
	it.inc = &increment;
	it.dec = &decrement;
	it.deref = &dereference;
	return it;
}

int front_elem(struct Deque_int * deque){
	return *(deque->front_indicator);
}

int back_elem(struct Deque_int * deque){
 return (deque->back_indicator[-1]);
}

void qsorthelper(struct Deque_int * deque, int low, int high);

void qsort(struct Deque_int * deque, struct Deque_int_Iterator it1, struct Deque_int_Iterator it2){
		Deque_int_Iterator infront;
		Deque_int_Iterator behind;
		infront.location = &(it1.location[1]);
		infront.front_arr = it1.front_arr;
		infront.back_arr = it1.back_arr;
		infront.inc = it1.inc;
		infront.dec = it1.dec;
		infront.deref = it1.deref;
		behind.location = it1.location;
		behind.front_arr = it1.front_arr;
		behind.back_arr = it1.back_arr;
		behind.inc = it1.inc;
		behind.dec = it1.dec;
		behind.deref = it1.deref;
		bool continue_sort = false;
		for(; !Deque_int_Iterator_equal(infront, it2); infront.inc(&infront), behind.inc(&behind)){
				if(deque->compare(infront.deref(&infront), behind.deref(&behind))){
					continue_sort = true;
					break;
				}
		}
		if(continue_sort){
			int first_iterator_index = -1;
			int second_iterator_index = -1;
			if(it2.location<=it1.location){
				int* temp = (int*) malloc((int)(sizeof(int) * deque->capacity));
				int counter = 0;
				for(Deque_int_Iterator it = deque->begin(deque); !Deque_int_Iterator_equal(it, deque->end(deque)); it.inc(&it)){
					temp[counter] = it.deref(&it);
					if(Deque_int_Iterator_equal(it, it1)){
						first_iterator_index = counter;
					}
					if(Deque_int_Iterator_equal(it, it2)){
						second_iterator_index = counter;
					}
					counter++;
				}
				free(deque->container);
				deque->container = temp;
				deque->front_indicator = deque->container;
				deque->back_indicator = &(deque->container[counter]);
				deque->front_array = deque->container;
				deque->back_array = &(deque->container[deque->capacity]);
			}else{
				first_iterator_index = ((it1.location) - (deque->front_array));
				//printf("First: %d \n", first_iterator_index);
				second_iterator_index = ((it2.location)-(deque->front_array));
				//printf("Second: %d \n", second_iterator_index);
			}
			qsorthelper(deque, first_iterator_index, second_iterator_index-1);
		}
}

void qsorthelper(struct Deque_int * deque, int low, int high){
	//printf("making call to helper");
	if(low<high){
		/*
		int pivot = deque->container[high];
		int swapping = low - 1;
		int part;
		for (int iterat = low; iterat<high; iterat++){
			if(deque->compare(deque->container[iterat], pivot)){
				swapping++;
				int temp1 = deque->container[swapping];
				deque->container[swapping] = deque->container[iterat];
				deque->container[iterat] = temp1;
			}
		}
		int temp2 = deque->container[swapping+1];
		deque->container[swapping+1] = deque->container[high];
		deque->container[high] = temp2;
		part = swapping+1;
		*/
		int pivot = deque->container[low];
		int swap1 = low-1;
		int swap2 = high+1;
		int part = 0;
		while(true){
			do{
				swap1++;
			}while(deque->compare(deque->container[swap1], pivot));

			do{
				swap2--;
			}while(deque->compare(pivot, deque->container[swap2]));

			if(swap1>=swap2){
				part = swap2;
				break;
			}
			int temp2 = deque->container[swap1];
			deque->container[swap1] = deque->container[swap2];
			deque->container[swap2] = temp2;

		}
		qsorthelper(deque, low, part);
		qsorthelper(deque, part+1, high);
	}

}

bool Deque_int_equal(struct Deque_int deque1, struct Deque_int deque2){
	if(deque1.num_elements != deque2.num_elements){
		return false;
	}
	struct Deque_int_Iterator it1 = deque1.begin(&deque1);
	struct Deque_int_Iterator it2 = deque2.begin(&deque2);

	while(!Deque_int_Iterator_equal(it1, deque1.end(&deque1)) && !Deque_int_Iterator_equal(it2, deque2.end(&deque2))){
		if(deque1.compare(it1.deref(&it1), it2.deref(&it2)) || deque1.compare(it2.deref(&it2), it1.deref(&it1))){
			return false;
		}
		it1.inc(&it1);
		it2.inc(&it2);
	}
	return true;
}

void printdeq(struct Deque_int deque){
	for(int i = 0; i<deque.capacity; i++){
		printf("%i ", deque.container[i]);
	}

	printf("\n\n\n");

}


#endif
