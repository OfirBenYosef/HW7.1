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
struct grades{
	list **students;
    //clone_func_t clone;//to do
	//destroy_func_t destroy;//to do

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
 void* student_data_clone(void *elem , void **out){
 	student_data *to_be_clone=(student_data*)elem;
	int *new_id=(int*)(malloc(sizeof(int)));
	char *temp;
	strcpy(temp,(char*)(to_be_clone->name));
	char *new_name=(char*)(malloc(sizeof(char*)*(strlen(temp)+1)));
	int *new_avg=(int*)(malloc(sizeof(int)));
	int *new_num_of_course=(int*)(malloc(sizeof(int)));
	list *new_list=(list*)(malloc(sizeof(list*))) ;
	*out=(student_data*)malloc(sizeof(student_data));
    if (!out ||!new_num_of_course ||!new_avg ||!new_name ||!new_id ||!new_list) {
        return NULL;
        free(new_id);
        free(new_name);
        free(new_avg);
        free(new_num_of_course);
        free(out);
        free(new_list);
    }

    else{
    	to_be_clone->id=*new_id;
    	to_be_clone->num_of_course=*new_num_of_course;
    	to_be_clone->avg=*new_avg;
		strcpy(to_be_clone->name,new_name);
		to_be_clone->student_grades=list_init(course_data_clone,course_data_destroy);
		out=&to_be_clone;
		
    }
    return out;
} 
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
static node *find_course(const char *name,list *list){ 
		node *curr_course = list_begin(list);
		while(curr_course){
			course_data *curr_course_data=list_get(curr_course);
			const char *curr_course_name=(char*)(*curr_course_data->course_name);
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
		struct node *curr_node = find_in_grades(id,(grades->students));
		if(!curr_node){
			//no cant_do
			return -1;

		}
		else{
			curr_student_data=list_get(curr_node);
			return (curr_student_data->avg);
		}
	}
	return -1;	
}
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){

	if(!grades ||(grade <0)||(grade>100)|| !id){
			//print_no_can_do, do
		return 0; //or return
		}

	else{
		student_data *curr_student_data;
		node *curr_node = find_in_grades(id,(grades->students));
		if(curr_node){
			curr_student_data=list_get(curr_node);
			if(!find_course(name,(curr_student_data->student_grades))){
				/* clc the new avg*/
				int temp_avg=curr_student_data->avg;
				int temp_num=curr_student_data->num_of_course;
				curr_student_data->avg=(temp_avg+grade/(temp_num+1));
				curr_student_data->num_of_course=temp_num+1;
				return course_init((curr_student_data->student_grades) ,name,grade);
			}
			else{
				//print_no_cant_do,do
				return NULL;
			}
		}
	}
}

int grades_add_student(struct grades *grades, const char *name, int id){
	if (!grades || !name || !id) {
			//print_no_can_do, do
		return NULL; //or return
	}
	else{
		struct node *curr_node =find_in_grades(id,(grades->students));
		if(!curr_node){
			return student_init((grades->students),name,id);
		}
		else{
			//print no_can_do
		}
	}
	
	return -1;
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
	studets_list=list_init(student_data_clone,student_data_destroy);//put
	grades_new-> students = studets_list;
	return grades_new;
}

