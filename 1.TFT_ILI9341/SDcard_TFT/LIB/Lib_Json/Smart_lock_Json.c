#include "Smart_lock_Json.h"


json_t *root;
char* str_Res;
int Flag_Json_To_TFT = 0;				// Co bao da co du lieu hien thi len LCD

char *Id			=""	;
char *name		=""	;
char *gender  = "";
char *birth  	= "";
char *_class 	= "";
char *msv			=""	;
char *school	=""	;

char new_ID[20];
char new_name[20];
char new_gender[20];
char new_birth[20];
char new_class[20];
char new_msv[20];
char new_school[20];


char old_ID[20] ;
char old_name[20] ;
char old_gender[20];
char old_birth[20];
char old_class[20];
char old_msv[20] ;
char old_school[20] ;



void Get_Info_Json(char *Res){

//	int j;
	json_t *DATA;
	json_error_t error;

//	UART_PutStr(USART1,Res); 

	DATA = json_loads((const char*)Res, 0 , &error);

	if(json_is_object(DATA)){
		Id 			= (char *)json_string_value(json_object_get(DATA , "card"		));		
		name 		= (char *)json_string_value(json_object_get(DATA , "name"		));
		gender 	= (char *)json_string_value(json_object_get(DATA , "gender"		));		
		birth 	= (char *)json_string_value(json_object_get(DATA , "birth"		));		
		_class  = (char *)json_string_value(json_object_get(DATA , "_class"		));
		msv 		= (char *)json_string_value(json_object_get(DATA , "msv"		));
		school 	= (char *)json_string_value(json_object_get(DATA , "school"	));											

//		printf("1-%s\n",name);
//		printf("1-%s\n",Id);
//		printf("1-%s\n",school);
//		printf("1-%s\n",msv);
		
		
		memcpy(new_ID	 	 ,Id		 ,strlen(Id)+1);
		memcpy(new_name	 ,name	 ,strlen(name)+1);
		memcpy(new_gender,gender ,strlen(gender)+1);
		memcpy(new_birth ,birth	 ,strlen(birth)+1);
		memcpy(new_class ,_class ,strlen(_class)+1);
		memcpy(new_msv	 ,msv		 ,strlen(msv)+1);
		memcpy(new_school,school ,strlen(school)+1);
//		printf("0-%s\n",new_name);
//		printf("0-%s\n",new_ID);
//		printf("0-%s\n",new_school);
//		printf("0-%s\n",new_msv);
		
		Flag_Json_To_TFT = 1;
		
	}	
	json_decref(DATA);		

}		

void json_packing(char *Buffer){
	int  j;
	root = json_object();
	json_object_set_new(root, "ID", json_string(Buffer));
	str_Res = json_dumps(root, JSON_PRESERVE_ORDER);
	printf("%s\n", str_Res);
	json_decref(root);		
	json_delete(root);	
	Flag_RFID_To_Json = 0;
	for(j=0;j<strlen(str_Res);j++){str_Res[j]=0;}
}

void Json_Copy_Info(char* TEN){
	int k;

//	printf("2-%s\n",new_name);
//	printf("2-%s\n",new_ID);
//	printf("2-%s\n",new_school);
//	printf("2-%s\n",new_msv);
	
	memcpy(old_ID	 	 ,new_ID		 ,strlen(new_ID)+1);
	memcpy(old_name	 ,new_name	 ,strlen(new_name)+1);
	memcpy(old_gender	 ,new_gender	 ,strlen(new_gender)+1);
	memcpy(old_birth ,new_birth	 ,strlen(new_birth)+1);
	memcpy(old_class	 ,new_class	 ,strlen(new_class)+1);
	memcpy(old_msv	 ,new_msv	 	 ,strlen(new_msv)+1);
	memcpy(old_school,new_school ,strlen(new_school)+1);
//	printf("2*-%s\n",old_name);
//	printf("2*-%s\n",old_ID);
//	printf("2*-%s\n",old_school);
//	printf("2*-%s\n",old_msv);

	for(k=0;k<20;k++){
		new_ID[k]			=0;
		new_name[k]		=0;
		new_gender[k] =0;
		new_birth[k]  =0;
		new_class[k]  =0;
		new_school[k]	=0;
		new_msv[k]		=0;
	}	
}

void Delay_Ms(unsigned int time){
	unsigned int i, j ;
	for( i=0; i<time; i++){
		for(j=0; j<0x2AFF; j++){}
	}
}
