#include <stdio.h>
#include <string.h>
#include "linked-linked.h"
#include <stdlib.h>
#include "grades.h"

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

/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
struct grades* grades_init();{
	struct grades *grades;
	struct list **studets_list;
	grades=(struct grades*)malloc(sizeof(*grades));
	studets_list=(struct list**)malloc(sizeof(struct list*));
	if (!grades || !studets) {
		/* Out of memory - must free what was allocated */
		free(grades);
		free(studets_list);
		return NULL;
	}
	students_list=list_init(clone,destroy);//put
	grades-> students = students_list;
	return grades;
};
   

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
		exit; //or return
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

};


/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
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
				
				//...avg
				return course_init((curr_student->student_grades) ,name,grade);
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
};

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
		if(!curr_node){
			//no cant_do
			exit;

		}
		else{

			return print_grades((student_data->name),(curr_student_data->student_grades));
		}
	}
	return NULL;// ?

};

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

static struct *node find_id(int id,struct list *list){

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
};

static struct *node find_course(const char *name,struct list *list){

		struct node *curr_course= list_begin(list);
		while(curr_course){
			const char *curr_course=(const char*)(curr_course-> course_data->course_name);
			if(!strcmp(curr_course,name){
				return curr_course;
			}
			else{
				curr_course=list_next(curr_course);
			}
		}
		return NULL;
};
static int student_init(struct list *list, const char *name, int id){

	struct student_data *new_student_data;
	struct node *new_node;
	new_student_data=(struct student_data*)malloc(sizeof(*student_data));
	new_node=(struct node*)malloc(sizeof(*node));
	if (!new_student_data || !new_node) {
			free(new_student_data);
			free(new_node);
			exit;
	}
	else{
	new_student_data->student_grades=list_init(clone,destroy);//do funcs
	(new_student_data -> id)=id;
	strcpy((new_student->name),name);
	new_student->avg=0;
	new_student->num_of_course=0;
	int a =list_insert(list, new_node, new_student_data);
	free(new_student_data);
	}
	return a;
}
static int course_init(struct list *list, const char *name, int grade){

	struct course_data *new_course_data;
	struct node *new_node;
	new_student_data=(struct course_data*)malloc(sizeof(*course_data));
	new_node=(struct node*)malloc(sizeof(*node));
	if (!new_curse_data || !new_node) {
			free(new_curse_data);
			free(new_node);
			exit;
	}
	else{
	
	(new_course_data -> grade) = grade;
	strcpy((new_student->name),name);
	int a =list_insert(list, new_node, new_course_data);
	free(new_course_data);
	}
	return a;
}
void* student_data_clone(void *elem){

	int new_id;
	char *new_name;
	int new_avg;
	int new_num_of_course;
	struct student_data *new_data=(struct student_data)malloc(sizeof(struct student_data));
    if (!new_data) {
        return NULL;
    }
    else{
    	new_data -> student_grades=course_data_clone(elem->student_grades);
	    new_data -> id =(int)(elem->id);
		strcpy((new_data ->name),(str*)(elem->name);
		new_data->avg=(int)(elem->avg);
		new_data->num_of_course=(int)(elem->num_of_course);
		int a =list_insert(list, new_node, new_student_data);
    }
    return new_data;
}

void* course_data_clone (*void elem){
	int new_grade;
	char *new_name;
	struct course_data *new_data=(struct course_data)malloc(sizeof(struct course_data));
    if (!new_data) {
        return NULL;
    }
    else{
    	new_data->grade = (int)(elem->grade);
    	new_data->course_name = (char*)(elem->course_name);
    }
    return new_data;
};
void* student_data_destroy (void *elem){
	/*free ints*/
	free((int)(elem->id));
	free((int)(elem->avg));
	free((int)(elem->num_of_course));
	/* free str*/
	free((str*)(elem->name));
	/*free course list*/
	list_destroy(elem->student_grades);
	free(elem);
};
void* course_data_destroy (void *elem){
	free((int)(elem->grade));
	free((char*)(elem->course_name));
	free(elem);
};
