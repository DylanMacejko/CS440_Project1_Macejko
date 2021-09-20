#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <cstdlib>
#include <cstdio>

#define Deque_DEFINE(t)																													\
	  struct Deque_##t##_Iterator{																									\
			t * location;																																\
			t * front_arr;																															\
			t * back_arr;																																\
			void (* inc)(struct Deque_##t##_Iterator *);																		\
			void (* dec)(struct Deque_##t##_Iterator *);																		\
			t & (* deref)(struct Deque_##t##_Iterator *);																		\
		};																																							\
																																										\
		void increment(struct Deque_##t##_Iterator * it){																	\
			if(it->location == &(it->back_arr[-1])){																			\
				it->location = it->front_arr;																								\
			}else{																																				\
				it->location = &(it->location[1]);																					\
			}																																							\
		}																																								\
																																										\
		void decrement(struct Deque_##t##_Iterator * it){																	\
			if(it->location == it->front_arr){																						\
				it->location = it->back_arr;																								\
			}else{																																				\
				it->location = &(it->location[-1]);																					\
			}																																							\
		}																																								\
																																										\
		t & dereference(struct Deque_##t##_Iterator * it){																\
			return *(it->location);																												\
		}																																								\
																																										\
		int Deque_##t##_Iterator_equal(struct Deque_##t##_Iterator it1, struct Deque_##t##_Iterator it2){				\
			return it1.location == it2.location;																					\
		}																																								\
		void push_b(struct Deque_##t * deque, t value);																\
		void push_f(struct Deque_##t * deque, t value);																\
		size_t container_size(struct Deque_##t * deque);																\
		void pop_b(struct Deque_##t * deque);																						\
		void pop_f(struct Deque_##t * deque);																						\
		void clear_deq(struct Deque_##t * deque);																				\
		void destructor(struct Deque_##t * deque);																			\
		int empt(struct Deque_##t * deque);																							\
		t & elem_at(struct Deque_##t * deque, size_t index);														\
		t & front_elem(struct Deque_##t * deque);																				\
		t & back_elem(struct Deque_##t * deque);																				\
		struct Deque_##t##_Iterator beginning(struct Deque_##t * deque);									\
		struct Deque_##t##_Iterator ending(struct Deque_##t * deque);											\
		void Deque_##t##_ctor(struct Deque_##t *, bool (* f)(const t & , const t & ));			\
		t & dereference(struct Deque_##t##_Iterator * it);																\
		void qsort(struct Deque_##t * deque, struct Deque_##t##_Iterator it1, struct Deque_##t##_Iterator it2);\
																																										\
		struct Deque_##t {																																\
			t * container;																																\
			int capacity;																																	\
			int num_elements;																															\
			t * front_indicator;																													\
			t * back_indicator;																													\
			t * front_array;																															\
			t * back_array;																															\
			void (*push_back)(struct Deque_##t *, t );																		\
			void (*push_front)(struct Deque_##t *, t );																	\
			size_t (*size)(struct Deque_##t *);																						\
			void (*pop_back)(struct Deque_##t *);																					\
			void (*pop_front)(struct Deque_##t *);																				\
			void (*clear)(struct Deque_##t *);																						\
			void (*dtor)(struct Deque_##t *);																							\
			int (*empty)(struct Deque_##t *);																							\
			t & (*at)(struct Deque_##t *, size_t);																				\
			t &  (*front)(struct Deque_##t *);																							\
			t &  (*back)(struct Deque_##t *);																							\
			struct Deque_##t##_Iterator (*begin)(struct Deque_##t *);												\
			struct Deque_##t##_Iterator (*end)(struct Deque_##t *);													\
			bool (* compare)(const t &, const t &);																			\
			void (* sort)(struct Deque_##t *, struct Deque_##t##_Iterator, struct Deque_##t##_Iterator);		\
			char type_name[sizeof("Deque_" #t )] = "Deque_" #t ;														\
		};																																							\
		void Deque_##t##_ctor(struct Deque_##t * deque, bool (* comparator)(const t & , const t & )){			\
			deque->container = ( t *) malloc(0);																					\
			deque->capacity = 0;																													\
			deque->num_elements  = 0;																											\
			deque->front_indicator = NULL;																								\
			deque->back_indicator = NULL;																									\
			deque->front_array = NULL;																										\
			deque->back_array = NULL;																											\
			deque->push_back = &push_b;																										\
			deque->push_front = &push_f;																									\
			deque->size = &container_size;																								\
			deque->pop_back = &pop_b;																											\
			deque->pop_front = &pop_f;																										\
			deque->clear = &clear_deq;																										\
			deque->dtor = &destructor;																										\
			deque->empty = &empt;																													\
			deque->at = &elem_at;																													\
			deque->front = &front_elem;																										\
			deque->back = &back_elem;																											\
			deque->begin = &beginning;																										\
			deque->end = &ending;																													\
			deque->compare = comparator;																									\
		  deque->sort = &qsort;																													\
		}																																								\
																																										\
		void push_f(struct Deque_##t * deque, t value){																\
			if(deque->num_elements == 0){																									\
				free(deque->container);																											\
				deque->container = ( t *) malloc(((int)sizeof( t )) * 8);										\
				*(deque->container) = value;																								\
				deque->num_elements = 1;																										\
				deque->capacity = 8;																												\
				deque->front_indicator = deque->container;																	\
				deque->back_indicator = &((deque->front_indicator)[1]);											\
				deque->front_array = deque->container;																			\
				deque->back_array = &(deque->container[8]);																	\
			}else if(deque->num_elements > 0 && deque->num_elements == deque->capacity-1){		\
				t * temp = ( t *) malloc((int)(sizeof( t ) * deque->capacity * 2));				\
				deque->capacity = 2 * deque->capacity;																			\
				int start_index = 0;																												\
				t * temp_front_indicator = &(temp[start_index]);														\
				for(Deque_##t##_Iterator it = deque->begin(deque); !Deque_##t##_Iterator_equal(it, deque->end(deque)); it.inc(&it)){		\
					temp[start_index+1] = it.deref(&it);																			\
					start_index++;																														\
				}																																						\
				int end_index = start_index;																								\
				t * temp_back_indicator = &(temp[end_index]);															\
				free(deque->container);																											\
				deque->container = temp;																										\
				deque->front_indicator = temp_front_indicator;															\
				deque->back_indicator = &(temp_back_indicator[1]);													\
				deque->front_indicator = deque->front_indicator;														\
				*(deque->front_indicator) = value;																					\
				deque->num_elements = deque->num_elements + 1;															\
				deque->front_array = deque->container;																			\
				deque->back_array = &(deque->container[deque->capacity]);										\
			}else{																																				\
				if(deque->front_indicator == deque->front_array){														\
					deque->front_indicator = &(deque->back_array[-1]);												\
					*(deque->front_indicator) = value;																				\
					deque->num_elements = deque->num_elements + 1;														\
				}else{																																			\
					deque->front_indicator[-1] = value;																				\
					deque->front_indicator = &(deque->front_indicator[-1]);										\
					deque->num_elements = deque->num_elements + 1;														\
				}																																						\
			}																																							\
		}																																								\
																																										\
		void push_b(struct Deque_##t * deque, t value){																\
			if(deque->num_elements == 0){																									\
				free(deque->container);																											\
				deque->container = ( t *) malloc(((int)sizeof( t )) * 8);										\
				*(deque->container) = value;																								\
				deque->num_elements = 1;																										\
				deque->capacity = 8;																												\
				deque->front_indicator = deque->container;																	\
				deque->back_indicator = &((deque->front_indicator)[1]);											\
				deque->front_array = deque->container;																			\
				deque->back_array = &(deque->container[8]);																	\
			}else if(deque->num_elements > 0 && deque->num_elements == deque->capacity-1){				\
				t * temp = ( t *) malloc((int)(sizeof( t ) * deque->capacity * 2));				\
				deque->capacity = 2 * deque->capacity;																			\
				int start_index = 0;																												\
				t * temp_front_indicator = &(temp[start_index]);														\
				for(Deque_##t##_Iterator it = deque->begin(deque); !Deque_##t##_Iterator_equal(it, deque->end(deque)); it.inc(&it)){		\
					temp[start_index] = it.deref(&it);																				\
					start_index++;																														\
				}																																						\
				int end_index = start_index;																								\
				t * temp_back_indicator = &(temp[end_index]);															\
				free(deque->container);																											\
				deque->container = temp;																										\
				deque->front_indicator = temp_front_indicator;															\
				deque->back_indicator = temp_back_indicator;																\
				deque->container[end_index] = value;																				\
				deque->back_indicator = &(deque->back_indicator[1]);												\
				deque->num_elements = deque->num_elements + 1;															\
				deque->front_array = deque->container;																			\
				deque->back_array = &(deque->container[deque->capacity]);										\
			}else{																																				\
				if(deque->back_indicator == &(deque->back_array[-1])){											\
					*(deque->back_indicator) = value;																					\
					deque->back_indicator = deque->front_array;																\
					deque->num_elements = deque->num_elements + 1;														\
				}else{																																			\
					*(deque->back_indicator) = value;																					\
					deque->back_indicator = &(deque->back_indicator[1]);											\
					deque->num_elements = deque->num_elements + 1;														\
				}																																						\
			}																																							\
		}																																								\
																																										\
		size_t container_size(struct Deque_##t * deque){																\
			return (size_t)deque->num_elements;																						\
		}																																								\
																																										\
		void pop_b(struct Deque_##t * deque){																						\
			if(deque->num_elements != 0){																									\
				if(deque->back_indicator == deque->front_array){														\
					deque->back_indicator = &(deque->back_array[-1]);													\
																																										\
				}else{																																			\
																																										\
					deque->back_indicator = &(deque->back_indicator[-1]);											\
				}																																						\
				deque->num_elements = deque->num_elements - 1;															\
			}																																							\
		}																																								\
																																										\
		void pop_f(struct Deque_##t * deque){																						\
			if(deque->num_elements != 0){																									\
																																										\
				if(deque->front_indicator == &(deque->back_array[-1])){											\
					deque->front_indicator = deque->front_array;															\
				}else{																																			\
					deque->front_indicator = &(deque->front_indicator[1]);										\
				}																																						\
				deque->num_elements = deque->num_elements - 1;															\
			}																																							\
		}																																								\
																																										\
		void clear_deq(struct Deque_##t * deque){																				\
			deque->num_elements = 0;																											\
			deque->front_indicator = NULL;																								\
			deque->back_indicator = NULL;																									\
			deque->front_array  = NULL;																										\
			deque->back_array = NULL;																											\
		}																																								\
																																										\
		void destructor(struct Deque_##t * deque){																			\
			free(deque->container);																												\
		}																																								\
																																										\
		int empt(struct Deque_##t * deque){																							\
			if(deque->num_elements == 0){																									\
				return 1;																																		\
			}																																							\
			return 0;																																			\
		}																																								\
																																										\
		t & elem_at(struct Deque_##t * deque, size_t index){														\
			if(&(deque->front_indicator[index]) > &(deque->back_array[-1])){							\
				long int offset = &(deque->front_indicator[index])-&(deque->back_array[-1])-1;		\
				return deque->front_array[offset];															\
			}																																							\
			return (deque->front_indicator[index]);																				\
		}																																								\
																																										\
		struct Deque_##t##_Iterator beginning(struct Deque_##t * deque){									\
			struct Deque_##t##_Iterator it;																									\
			it.location = deque->front_indicator;																					\
			it.front_arr = deque->front_array;																						\
			it.back_arr = deque->back_array;																							\
			it.inc = &increment;																													\
			it.dec = &decrement;																													\
			it.deref = &dereference;																											\
			return it;																																		\
		}																																								\
																																										\
		struct Deque_##t##_Iterator ending(struct Deque_##t * deque){											\
			struct Deque_##t##_Iterator it;																									\
			it.location = deque->back_indicator;																					\
			it.front_arr = deque->front_array;																						\
			it.back_arr = deque->back_array;																							\
			it.inc = &increment;																													\
			it.dec = &decrement;																													\
			it.deref = &dereference;																											\
			return it;																																		\
		}																																								\
																																										\
		t & front_elem(struct Deque_##t * deque){																				\
			return *(deque->front_indicator);																							\
		}																																								\
																																										\
		t & back_elem(struct Deque_##t * deque){																				\
		 return (deque->back_indicator[-1]);																						\
		}																																								\
																																										\
		void qsorthelper(struct Deque_##t * deque, int low, int high);									\
																																										\
		void qsort(struct Deque_##t * deque, struct Deque_##t##_Iterator it1, struct Deque_##t##_Iterator it2){	\
				Deque_##t##_Iterator infront;																									\
				Deque_##t##_Iterator behind;																									\
				infront.location = &(it1.location[1]);																			\
				infront.front_arr = it1.front_arr;																					\
				infront.back_arr = it1.back_arr;																						\
				infront.inc = it1.inc;																											\
				infront.dec = it1.dec;																											\
				infront.deref = it1.deref;																									\
				behind.location = it1.location;																							\
				behind.front_arr = it1.front_arr;																						\
				behind.back_arr = it1.back_arr;																							\
				behind.inc = it1.inc;																												\
				behind.dec = it1.dec;																												\
				behind.deref = it1.deref;																										\
				bool continue_sort = false;																									\
				for(; !Deque_##t##_Iterator_equal(infront, it2); infront.inc(&infront), behind.inc(&behind)){	\
						if(deque->compare(infront.deref(&infront), behind.deref(&behind))){			\
							continue_sort = true;																									\
							break;																																\
						}																																				\
				}																																						\
				if(continue_sort){																													\
					int first_iterator_index = -1;																						\
					int second_iterator_index = -1;																						\
					if(it2.location<=it1.location){																						\
						t * temp = ( t *) malloc((int)(sizeof( t ) * deque->capacity));				\
						int counter = 0;																												\
						for(Deque_##t##_Iterator it = deque->begin(deque); !Deque_##t##_Iterator_equal(it, deque->end(deque)); it.inc(&it)){	\
							temp[counter] = it.deref(&it);																				\
							if(Deque_##t##_Iterator_equal(it, it1)){																\
								first_iterator_index = counter;																			\
							}																																			\
							if(Deque_##t##_Iterator_equal(it, it2)){																\
								second_iterator_index = counter;																		\
							}																																			\
							counter++;																														\
						}																																				\
						free(deque->container);																									\
						deque->container = temp;																								\
						deque->front_indicator = deque->container;															\
						deque->back_indicator = &(deque->container[counter]);										\
						deque->front_array = deque->container;																	\
						deque->back_array = &(deque->container[deque->capacity]);								\
					}else{																																		\
						first_iterator_index = ((it1.location) - (deque->front_array));					\
						second_iterator_index = ((it2.location)-(deque->front_array));					\
					}																																					\
					qsorthelper(deque, first_iterator_index, second_iterator_index-1);				\
				}																																						\
		}																																								\
																																										\
		void qsorthelper(struct Deque_##t * deque, int low, int high){									\
			if(low<high){																																	\
				t pivot = deque->container[low];																					\
				int swap1 = low-1;																													\
				int swap2 = high+1;																													\
				int part = 0;																																\
				while(true){																																\
					do{																																				\
						swap1++;																																\
					}while(deque->compare(deque->container[swap1], pivot));										\
																																										\
					do{																																				\
						swap2--;																																\
					}while(deque->compare(pivot, deque->container[swap2]));										\
																																										\
					if(swap1>=swap2){																													\
						part = swap2;																														\
						break;																																	\
					}																																					\
					t temp2 = deque->container[swap1];																			\
					deque->container[swap1] = deque->container[swap2];												\
					deque->container[swap2] = temp2;																					\
				}																																						\
				qsorthelper(deque, low, part);																							\
				qsorthelper(deque, part+1, high);																						\
			}																																							\
		}																																								\
																																										\
		bool Deque_##t##_equal(struct Deque_##t deque1, struct Deque_##t deque2){					\
			if(deque1.num_elements != deque2.num_elements){																\
				return false;																																\
			}																																							\
			struct Deque_##t##_Iterator it1 = deque1.begin(&deque1);												\
			struct Deque_##t##_Iterator it2 = deque2.begin(&deque2);												\
																																										\
			while(!Deque_##t##_Iterator_equal(it1, deque1.end(&deque1)) && !Deque_##t##_Iterator_equal(it2, deque2.end(&deque2))){		\
				if(deque1.compare(it1.deref(&it1), it2.deref(&it2)) || deque1.compare(it2.deref(&it2), it1.deref(&it1))){						\
					return false;																															\
				}																																						\
				it1.inc(&it1);																															\
				it2.inc(&it2);																															\
			}																																							\
			return true;																																	\
		}																																								\

#endif
