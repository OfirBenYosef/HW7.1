#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grades.h"


typedef struct grades grades;
typedef struct student_data student_data;
typedef struct course_data;
//declartion
static int course_init(struct list *list, const char *name, int grade);
struct grades{
	struct list **students;
    //clone_func_t clone;//to do
	//destroy_func_t destroy;//to do

};
/*the node element*/
struct student_data {
	struct list **student_grades;
	int id;
	char *name;
	int avg;
	int num_of_course;
};

struct course_data {
	int grade;
	char *course_name;
};
/*
void* student_data_clone(void *elem , void **out){

	int new_id;
	char *new_name;
	strcpy(new_name,(char*)(*elem));
	int new_avg;
	int new_num_of_course;
	int space_need= (3*sizeof(int)+(strlen(new_name)+1)*sizeof(char*)+sizeof(int*));
	*out=(struct student_data)malloc(space_need);
    if (!out) {
        return NULL;
    }
    else{
    	out -> student_grades=course_data_clone(elem->student_grades);
	    out-> id =(int)(elem->id);
		strcpy((out ->name),(char*)(elem->name);
		out->avg=(int)(elem->avg);
		out->num_of_course=(int)(elem->num_of_course);
		int a =list_insert(list, new_node, new_student_data);
    }
    return out;
}

void* course_data_clone (void *elem, void **out){
	int new_grade;
	char *new_name;
	*out=(struct course_data)malloc(2*sizeof(int));
    if (!out) {
        return NULL;
    }
    else{
    	out->grade = (int)(elem->grade);
    	out->course_name = (char*)(elem->course_name);
    }
    return out;
}
void* student_data_destroy (void *elem){
	
	free((int)(elem->id));
	free((int)(elem->avg));
	free((int)(elem->num_of_course));

	free((str*)(elem->name));
	/*free course list*/
	/*list_destroy(elem->student_grades);
	free(elem);/
}
void* course_data_destroy (void *elem){
	free((int)(elem->grade));
	free((char*)(elem->course_name));
	free(elem);
}*/
/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
struct grades* grades_init(){
	struct grades *grades;
	struct list **studets_list;
	grades=(struct grades*)malloc(sizeof(*grades));
	studets_list=(struct list**)malloc(sizeof(struct list*));
	if (!grades || !studets_list) {
		/* Out of memory - must free what was allocated */
		free(grades);
		free(studets_list);
		return NULL;
	}
	studets_list=list_init(student_data_clone,student_data_destroy);//put
	grades-> students = studets_list;
	return grades;
}
   

/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades);

/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with 
 * the same "id" already exists in "grades"
 */
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
	
	return NULL;

}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade)
{
	if (!grades ||(grade <0)||(grade>100)|| !id){
			//print_no_can_do, do
		exit; //or return
		}

	else{
		struct student_data *curr_student_data;
		struct node *curr_node = find_in_grades(id,(grades->students));
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
				exit;
			}
		
		}
		else{
			exit;
		}
	}
}

/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "out" to NULL.
 */
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

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id){
	if (!grades || !id) {
		//print_no_can_do, do
		exit; //or return
	}
	else{
		struct student_data *curr_student_data;
		struct node *curr_node = find_in_grades(id,(grades->students));
		curr_student_data=list_get(curr_node);
		if(!curr_node){
			//no cant_do
			exit;

		}
		else{

			return print_grades((student_data->name),(curr_student_data->student_grades));
		}
	}
	return NULL;// ?

}

/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order 
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */

int grades_print_all(struct grades *grades);

static struct node *find_id(int id,struct list *list){

		struct node *curr_student= list_begin(list);
		while(curr_student){
			int curr_id=(int)(curr_student-> student_data-> id);
			if(curr_id == id){
				return curr_student;
			}
			else{
				curr_student=list_next(curr_student);
			}
		}
		return NULL;
}

static struct node *find_course(const char *name,struct list *list){ 

		struct node *curr_course = list_begin(list);
		while(curr_course){
			const char *curr_course=(const char*)(curr_course-> course_data->course_name);
			if(!strcmp(curr_course,name)){
				return curr_course;
			}
			else{
				curr_course=list_next(curr_course);
			}
		}
		return NULL;
}
static int student_init(struct list *list, const char *name, int id){

	struct student_data *new_student_data;
	struct node *new_node;
	int a;
	new_student_data=(struct student_data*)malloc(sizeof(struct student_data));
	new_node=(struct node*)malloc(sizeof(node));
	if (!new_student_data || !new_node) {
			free(new_student_data);
			free(new_node);
			exit;
	}
	else{
	new_student_data->student_grades=list_init(clone,destroy);//do funcs
	(new_student_data -> id)=id;
	strcpy((new_student_data->name),name);
	new_student_data->avg=0;
	new_student_data->num_of_course=0;
	a =list_insert(list, new_node, new_student_data);
	free(new_student_data);
	}
	return a;
}
static int course_init(struct list *list, const char *name, int grade){

	struct course_data *new_course_data;
	struct node *new_node;
	int a;
	new_course_data=(struct course_data*)malloc(sizeof(struct course_data));
	new_node=(struct node*)malloc(sizeof(struct node));
	if (!new_course_data|| !new_node) {
			free(new_course_data);
			free(new_node);
			exit;
	}
	else{
	
	(new_course_data -> grade) = grade;
	strcpy((new_course_data->course_name),name);

	 a = list_insert(list, new_node, new_course_data);
	free(new_course_data);
	}
	return a;
}


