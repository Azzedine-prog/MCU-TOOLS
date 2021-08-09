 /* filename : parser-project
 author : azzedine
 date of creation : 2021/8/4
 */
/**************************************************************
*	this is a test file for this library where you will know 
*	it will work , and you can read the readme also 
*	this library is just made by me (amateur) not that professional 
*	feel free to contribute or suggest or help when you find any 
*	fix or upgrade for this modest project .
*	
*	author : AZZEDINE LAKHDAR
*	 EMBEDDED SYSTEMS student 
*		8/7/2021
*						thanks for using this .    .
											   .  .
											    ..
*****************************************************************/
#include<stdio.h>
#include "parser.h"
#include <stdlib.h>
#include<time.h>
//static int *pipe,*freq;
int abs(int number){
	if(number>0)
		return number;
	else 
		return (-1*number);
}
void freq_fun(int number){
	//printf("that number is : %d \n",number);
	// pipe = (int*) malloc(sizeof(int));
	// *pipe = number;
}
void pipe_fun(int number){
	//printf("char string : %s\n",mychar);
	//freq = (int*) malloc(sizeof(int));
	//*freq = number;
}
void version(void){
	printf("this is version 15.0.2 \n open source library \n \t made by : A Z Z E D I N E  L A K H D A R \n");
}
void unit(char* string){
	// code here
}
void output(int number){
	//code here
}
void precision(int number){
	//code here
}
int out_freq(int m,int n,int p,int frequency){
	int tmp = (frequency*n)/(p*m);
	return tmp;
}
/*double secondes_taken(clock_t *t,clock_t base){
	*t = clock()-base;
	double time_taken = ((double)(*t))/CLOCKS_PER_SEC;
	return time_taken;
}*/
int main(int argc,char**argv){ 
	//printf("bdina1");
	linked_list_string* my_arguments = argument_init();
	add_argument_with_help_and_action("freq","f",0,INT,"specifying frequence (default 8)",&freq_fun,NULL,NULL,my_arguments);
	add_argument_with_help_and_action("pipe","p",0,INT,"specifying pipeline architecture (default 4)",&pipe_fun,NULL,NULL,my_arguments);
	add_argument_with_help_and_action("version","v",0,BOOL,"for app version ",NULL,NULL,&version,my_arguments);
	add_argument_with_help_and_action("unit","u",0,CHAR,"specifying unit s: seconds or m for milliseconds(default s)",NULL,&unit,NULL,my_arguments);
	add_argument_with_help_and_action("output","o",0,INT,"specifying output frqeuncy wanted ",&output,NULL,NULL,my_arguments);
	add_argument_with_help_and_action("precision","j",0,INT,"specifying precision of output frequency (default 10)",&precision,NULL,NULL,my_arguments);
	add_argument_with_help_and_action("mcu","m",0,INT,"specifying microcontroller used (default stm32f4)",&precision,NULL,NULL,my_arguments);
	//printf("bdina1");
	if(manage_arguments(argc,argv,my_arguments) != 0){
		//printf("error");
		return 1;
	}
	node_string* freq_node = get_node_by_self("freq",my_arguments);
	if(get_node_by_self("version",my_arguments)->status == True){
		return 0;
	}
	node_string* unit_node = get_node_by_self("u",my_arguments);
	node_string* pipe_node = get_node_by_self("p",my_arguments);
	node_string* output_node = get_node_by_self("o",my_arguments);
	node_string* precision_node = get_node_by_self("j",my_arguments);
	int freq=8,pipe = 4,unit = 1000,delay=0,precision = 10;
	char* unit_char;
	if(freq_node->status == True){
		//printf("true1\n");
		freq = freq_node->int_value;
	}
	if(precision_node->status == True){
		//printf("true1\n");
		precision = precision_node->int_value;
		if(precision>84){
			printf("precision can't surpass 84\n");
			return 1;
		}
	}
	if(pipe_node->status == True){
		//printf("true2\n");
		pipe = pipe_node->int_value;
	}
	if(unit_node->status == True){
		//printf("true3\n");
		if(str_cmp(unit_node->string,"m") == 1){
			unit = 1;
		}
	}
	if(output_node->status == True){
		//clock_t t,base;
		//base = clock();
		int out = output_node->int_value;
		srand(time(0));
		int p_pos = (rand())%4,n=(rand())%433,m=(rand())%64,tmp=0;
		unsigned long long counter = 0,counter_tmp=0,advancement=1;
		int p_array[] = {2,4,6,8};
		printf("input frequency : %d Mhz,output wanted : %dMhz,precision : %d\n",freq,out,precision);
		//printf("for output frequency %d Mhz , n = %d,m = %d,p = %d\n",out,n,m,p_array[p_pos]);
		while(((out-tmp)>precision) || ((out-tmp)<0)){
			//t = clock();
			if(counter == 10000000000){
				printf("we didn't find a combination for your number \n try again");
				return 1;
			}
			if((counter-counter_tmp)>100000){
			counter_tmp = counter;
			fflush(stdout);
			printf("(%llu) --> outfreq = %dMhz,n = %d,m = %d,p = %d\r",counter,tmp,n,m,p_array[p_pos]);
			}
			counter = counter + 1;
			srand(time(0));
			p_pos = (rand())%4;
			//srand(time(0));
			n=(rand())%433;
			//srand(time(0));
			m=(rand())%64;
			if((m != 0))
				tmp = out_freq(m,n,p_array[p_pos],freq);
		}
		fflush(stdout);
		printf("<--[for output frequency %d Mhz , n = %d,m = %d,p = %d]-->\n",tmp,n,m,p_array[p_pos]);
		return 0;
	}
	printf("frequency : %d Mhz , pipeline : %d, unit : %d ms\n",freq,pipe,unit);
	delay = 1000*pipe/freq;
	if(unit==1)
	printf("delay for 1 millisecond will be : %d\n",delay);
	else if(unit == 1000)
	printf("delay for 1 second will be : %d\n",1000*delay);
	return 0;
}
