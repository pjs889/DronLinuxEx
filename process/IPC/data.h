#define MAXX_TEXT 512
#define MAX_PERSON 5
   
 struct Person
     {
              // long으로 선언된 msg_type은 반드시 구조체에 포함.
               long int my_msg_type;
                // 사용자가 정의하는 데이터 타입
                 char name[10];
	          int age;
	           int id;
	    };

