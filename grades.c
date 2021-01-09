#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grades.h"
#include "linked-list.h"

typedef struct grades grades;
typedef struct student_data student_data;
typedef struct course_data course_data;
typedef struct node node;
typedef struct list list;
//declartion
#define EXIT 100
#define SUCCESS 0
struct grades{
	list **students;
};
/*the node element*/
struct student_data {
	list **student_grades;
	int id;
	char *name;
	int avg;
	int num_of_course;
};

struct course_data {
	int grade;
	char *course_name;
};
void course_data_destroy (void *elem);
void student_data_destroy (void *elem);
int course_data_clone(void *elem, void **out);
int student_data_clone(void *elem , void **out);
static int print_grades(struct student_data *student_data, list **student_grades);


static node *find_id(int id,list **list){
	    node *curr_student = list_begin(*list);
		while(curr_student){
			student_data *new_student=list_get(curr_student);
			int curr_id=(int)(new_student->id);
			if(curr_id == id){
				return curr_student;
			}
			else{
				curr_student=list_next(curr_student);
			}
		}
		return NULL;
}
static int course_init(list *list, const char *name, int grade){

	course_data *new_course_data;
	int new_course;
	new_course_data=(course_data*)malloc(sizeof(course_data));
	if (!new_course_data) {
			free(new_course_data);
			return 0;
	}
	else{
	
	
	(new_course_data -> grade) = grade;
	strcpy((new_course_data->course_name),name);
	new_course=list_push_back(list,new_course_data);
	free(new_course_data);
	}
	return new_course;
}
static int student_init(list *list, const char *name, int id){

	student_data *new_student_data;
	int new;
	new_student_data=(student_data*)malloc(sizeof(student_data));
	if (!new_student_data ) {
			free(new_student_data);
			return 0;
	}
	else{
	//new_student_data->student_grades=list_init(clone,destroy);//do funcs
	(new_student_data -> id)=id;
	strcpy((new_student_data->name),name);
	new_student_data->avg=0;
	new_student_data->num_of_course=0;
	new =list_push_back(list,new_student_data);
	free(new_student_data);
	}
	return new;
}
static node *find_course(const char *name,list **list){ 
		node *curr_course = list_begin(*list);
		while(curr_course){
			course_data *curr_course_data=list_get(curr_course);
			const char *curr_course_name=(curr_course_data->course_name);
			if(!strcmp(curr_course_name,name)){
				return curr_course;
			}
			else{
				curr_course=list_next(curr_course);
			}
		}
		return NULL;
}
float grades_calc_avg(struct grades *grades, int id, char **out){
	if (!grades ||!out|| !id) {
			//print_no_can_do, do
		return -1;
	}
	else{
		struct student_data *curr_student_data;
		struct node *curr_node = find_id(id,(grades->students));
		if(!curr_node){
			//no cant_do
			return -1;

		}
		else{
			curr_student_data=list_get(curr_node);
			*out=curr_student_data->name;
			return (curr_student_data->avg);
		}
	}
	return -1;	
}
int grades_add_grade(struct grades *grades,const char *name,int id,int grade){

	if(!grades ||(grade <0)||(grade>100)|| !id){
		return EXIT; 
		}

	else{
		student_data *curr_student_data;
		node *curr_node = find_id(id,(grades->students));
		if(curr_node){
			curr_student_data=list_get(curr_node);
			if(!find_course(name,(curr_student_data->student_grades))){
				/* clc the new avg*/
				int temp_avg=curr_student_data->avg;
				int temp_num=curr_student_data->num_of_course;
				curr_student_data->avg=(temp_avg+grade/(temp_num+1));
				curr_student_data->num_of_course=temp_num+1;
				if(!course_init(*(curr_student_data->student_grades) ,name,grade)){
					return EXIT;
				}
				else{
					return SUCCESS;
				}
			}
			else{
				return EXIT;
			}
		}
	}
	return SUCCESS; //? not EXIT?
}

int grades_add_student(struct grades *grades, const char *name, int id){
	if (!grades || !name || !id) {
		return EXIT; 
	}
	else{
		struct node *curr_node =find_id(id,(grades->students));
		if(!curr_node){
			return student_init(*(grades->students),name,id);
		}

	}
	
	return EXIT;
}

int grades_print_student(struct grades *grades, int id){
	if (!grades || !id) {
		
		return EXIT; 
	}
	else{
		struct student_data *curr_student_data;

		curr_student_data = (student_data*)find_id(id,(grades->students));
		
		if(!curr_student_data){
			return EXIT;

		}
		else{

			/*if(print_grades(curr_student_data,(curr_student_data->student_grades))){
				return EXIT;
			}
			else{
				return SUCCESS;
			}*/
			return print_grades(curr_student_data,(curr_student_data->student_grades));
			
		}
	}
	return EXIT;

}

int grades_print_all(struct grades *grades){

	if (!grades) {
		
		return EXIT; 
	}
	struct node *student_temp=list_begin(*(grades->students));

	while(student_temp){
		student_data *student_d =list_get(student_temp);
		int temp_id=(int)(student_d->id);
		if(!grades_print_student(grades,temp_id)){
			student_temp=list_next(student_temp);
			//temp_id=(int)(student_d->id);
		}
		else {
			return EXIT;
		}

		return SUCCESS;
	}
	return SUCCESS;
}

static int print_grades(struct student_data *student_data, list **student_grades){ //static?
	if (!student_data || !student_grades) {
		
		return EXIT; 
	}
	int id=student_data-> id;
	char *name=(char*)(student_data-> name);
	printf("%d %s:", id, name);
	struct node *curr_student_course=list_begin(*student_grades);
	
	if(!curr_student_course){
		return EXIT;
	}
	while(curr_student_course){
		course_data *curr_course_data=list_get(curr_student_course);
		if(!curr_course_data){
		return EXIT;
		}

		const char *curr_course_name=(curr_course_data->course_name);

		//char course=(char)(curr_student_course->course_data->list_get(course_data));
		int grade=(curr_course_data->grade);
		
		printf("%s %d,", curr_course_name, grade);
		curr_student_course=list_next(curr_student_course);
	}
		//char course=(char)(curr_course->course_data->course_name);
		course_data *curr_course_data=list_get(curr_student_course);
		if(!curr_course_data){
		return EXIT;
		}
		const char *curr_course_name=(curr_course_data->course_name);
		int grade=(curr_course_data->grade);
		
		printf("%s %d\n", curr_course_name, grade);

		return SUCCESS;

	}

grades* grades_init(){ 
    grades *grades_new;
    list **studets_list;
	grades_new=(grades*)(malloc(sizeof(grades)));
	studets_list=(list**)(malloc(sizeof(list*)));
	if (!grades_new || !studets_list) {
		/* Out of memory - must free what was allocated */
		free(grades_new);
		free(studets_list);
		return NULL;
	}
	*studets_list=list_init(student_data_clone,student_data_destroy);
	grades_new-> students = studets_list;
	return grades_new;
}
void  course_data_destroy (void *elem){
	course_data *to_be_destroy=(course_data*)elem;
	free((to_be_destroy->course_name));
	free(elem);
	
}
void student_data_destroy (void *elem){
	student_data *to_be_destroy=(student_data*)elem;
	free((to_be_destroy->name));
	/*free the course list*/
	list_destroy(*(to_be_destroy->student_grades));
	free(elem);
	
}
int student_data_clone(void *elem, void **out){
	char *temp=NULL;
	course_data *to_be_clone = (course_data*)elem;
	strcpy(temp,(to_be_clone->course_name));
	//char *new_name= (char*)malloc(sizeof(char*)*(strlen(temp)+1));
	*out=(course_data*)malloc(sizeof(course_data));
    if (!out) {
    	//free(new_name);
    	free(out);
        return EXIT;
    }
    else{
    *out=to_be_clone;
    //strcpy((out->course_name),(to_be_clone->course_name));
    }
    return 0;
}

int course_data_clone (void *elem, void **out){
	char *temp=NULL;
	course_data *to_be_clone =(course_data*)elem;
	strcpy(temp,(to_be_clone->course_name));
	//char *new_name= (char*)malloc(sizeof(char*)*(strlen(temp)+1));
	*out=(course_data*)malloc(sizeof(course_data));
    if (!out) {
    	//free(new_name);
    	free(out);
        return EXIT;
    }
    else{
    *out=to_be_clone;
    }
    return 0;
}
void grades_destroy(struct grades *grades){
	list_destroy(*(grades->students));
	free(grades);
}


