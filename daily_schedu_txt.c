/*********schedu:*************************/
/**************************************************************************************
*	Monday:		linux_app() 	script 				1.java  2.driver
*	Tuesday:		hardware                      	1.java  2.driver
*	Wednesday:	linux_app()   script          		1.java  2.driver								
*	Thurday:		hardware                      	1.java  2.driver								
*	Firday:		OS(a chapter) script            	1.java  2.driver								
*	Saturday:                                 		1.java  2.driver								
*	Sunday:		system_transplant()                   	1.java  2.driver								
*****************************************************************************************/




7.13--->
	Saturday:
		--->driver:	1.atomic(2_atomic_drv)
					2.spin_lock(3_spin_lock)
					3.block_noblock(4_block_noblock)
					4.poll(5_poll)
								
						

7.14--->
	Sunday:
		--->driver:
		--->java:
			
			
			
7.15--->
	Monday:
		--->java:
		--->driver:	1.6_async_notification:�첽֪ͨ
		--->linux_app:
		--->script:
		
		
7.16--->
	Tuesday:
		--->java:������ 1_hello
				���0�2�0�2 ������ hello.class
				���0�2�0�2 ������ hello.java
				������ 2_data_type //java����������ת�� ���� ����...
				���0�2�0�2 ������ test.class
				���0�2�0�2 ������ test.java
				������ 3_lable	//��ǩ  break continue
				���0�2�0�2 ������ test.class
				���0�2�0�2 ������ test.java
				������ 4_array	//�����������ʽ������
				���0�2�0�2 ������ test.class
				���0�2�0�2 ������ test.java
				������ 5_foreach//foreach����������
				    ������ test.class
					    ������ test.java
				������ 6_Person//����person�� ����person����
				���0�2�0�2 ������ test.class
				������ 7_array_sort
				���0�2�0�2 ������ array.class//����java����Լ����㷨����
				���0�2�0�2 ������ array.java
				������ 8_changeable_fun//�ɱ亯���в������Ͳ�����д��
				���0�2�0�2 ������ array.class
				���0�2�0�2 ������ array.java
				������ 9_
				    ������ twod_array.class//��ά�����������������ʼ��������
				    ������ twod_array.java

		--->driver:7_irq
		--->hardware:��ʽ������·
	
7.17--->
	Wednesday:
		--->java:
			������ 10_chess_board //��������������
			���0�2�0�2 ������ Gobang.java
			������ 11_this
			���0�2�0�2 ������ retrunthis//this ָ��������÷�
			���0�2�0�2 ���0�2�0�2 ������ Returnthis.class
			���0�2�0�2 ���0�2�0�2 ������ Returnthis.java
			���0�2�0�2 ������ this//this ָ����÷�
			���0�2�0�2     ������ TestDog.java
			������ 12_overload//����������
			���0�2�0�2 ������ Overload.java
			������ 13_package//java �еĴ���� package myPackage.person   import myPackage.person  ���� javac -d . Person.java
			���0�2�0�2 ������ myPackage
			���0�2�0�2 ���0�2�0�2 ������ Person.class
			���0�2�0�2 ������ Person.java
			���0�2�0�2 ������ test.java
			���� 14_ConstructorOverload//���캯�� �򷽷������ء�����������ͬ this
			���0�2�0�2 ������ Apple.java
			/* public Apple(String name, String color, double weight){
			 ~                        | 15         this(name,color);
			 ~                        | 16         this.weight = weight;
			 ~                        | 17     }
			*/
			������ 15_extends//�̳е�д��
			���0�2�0�2 ������ Apple.java
			���0�2�0�2 ������ Fruit.java
			������ 16_overwrite_fun //����̳и��࣬��д�����еķ���
			���0�2�0�2 ������ Bird.java
			���0�2�0�2 ������ Ostrich.java
			������ 17_super//super() ���ø����еķ�����ʵ���Լ��ķ���
			���0�2�0�2 ������ Sub.java/* public Sub(double size, String name, String color){
			~                        | 17         super(size,name);
			~                        | 18         this.color = color;
			~                        | 19     }   */
			������ 18_Polymorphism//��������ת�ͣ��Ը�����룬���������෽��ִ��
			���0�2�0�2 ������ SubClass.java// BaseClass ts = new SubClass();//�Ը�����룬����������  

		--->driver:7_irq
		--->linux_app:
		--->script:
7.18--->
	Thursday:
		--->java:
		������ 19_instanceof // (a instanceof b) �ж�a �Ƿ� ����b�࣬ת�͵�ǰ�� 
		���0�2�0�2 ������ TestInstanceof.class
		���0�2�0�2 ������ TestInstanceof.java
		������ 20_reuse
									12 class Bird extends Animal{
		 ~                        | 13     private Animal a;//˽�ж��� ���ø���ķ���
		 ~                        | 14 
		 ~                        | 15     public Bird(Animal a){
		 ~                        | 16         this.a = a;
		 ~                        | 17     }
		 ~                        | 18 
		 ~                        | 19     public void breath(){
		 ~                        | 20         a.breath();
		 ~                        | 21     }
		 ~                        | 22  
		 ~                        | 23     public void fly(){
		 ~                        | 24         System.out.println("I can fly in the blue sky");
		 ~                        | 25     
		 ~                        | 26     }
		 ~                        | 27     
		 ~                        | 28 }

		���0�2�0�2 ������ Animal.class
		���0�2�0�2 ������ Bird.class
		���0�2�0�2 ������ TestInherit.class
		���0�2�0�2 ������ TestInherit.java
		���0�2�0�2 ������ Wolf.class
		������ 21_data_conversion
						/*	String intstr = "123";
		                    |  5         int it = Integer.parseInt(intstr);
						*/
	 �0�2�0�2 ������ Primitive2String.class
		���0�2�0�2 ������ Primitive2String.java
		������ 22_toString/*
		~                        | 15      *toString ��Object��һ�����������ж�����Object�����࣬��ӵ��toString������
		~                        | 16      * ������System.out.println(p) �����p.toString(),��ʵ�����������������
		~                        | 17      */

		���0�2�0�2 ������ Apple.class
		���0�2�0�2 ������ testToString.class
		���0�2�0�2 ������ testToString.java
		������ 23_inner_empty_obj2/*     public static void main(String args[]){
		~                        | 13         NullAccessStatic na = null;
		~                        | 14         na.test();
		~                        | 15         
		~                        | 16          // �ն�����Է��ʱ����е�static��Ա�򷽷������ܷ���������ʵ����Ա�����������쳣��
		~                        | 17         //����ĵ��ý�������쳣 
		~                        | 18         na.say(); 
								*/
		���0�2�0�2 ������ NullAccessStatic.class
		���0�2�0�2 ������ NullAccessStatic.java
		������ 24_Singleton//�����࣬��ֻ�ܱ�����һ������
		���0�2�0�2 ������ Singleton.class
		���0�2�0�2 ������ TestSingletion.class
		���0�2�0�2 ������ TestSingletion.java
		������ 25_final////final���εĳ�Ա����ֻ���ڶ�����ʼ�����и�ֵ����������ͨ�����и�ֵ��Ҳ�����ظ���ֵ��
		���0�2�0�2 ������ TestFinalLocalVariable.class
		���0�2�0�2 ������ TestFinalLocalVariable.java
		
		--->driver:
		--->hardware:

7.19--->
	Friday:
		--->java:
		--->driver:
		--->linux_app:
		--->script:
		
7.20--->
	Saturday:
		--->java:
		--->driver:
		--->system_transplant:	
								
						

7.21--->
	Sunday:
		--->java:
		--->driver:
		--->system_transplant:	
			
7.22--->
	Monda:��
		--->java:
		--->driver:
		--->linux_app:
		--->script:
		
		
7.23--->
	Tuesday:
		--->java:
		--->driver:
		--->hardware:
	
7.24--->
	Wednesday:
		--->java:
		--->driver:
		--->linux_app:
		--->script:
		
7.25--->
	Thursday:
		--->java:
		--->driver:
		--->hardware:

7.26--->
	Friday:
		--->java:
		--->driver:
		--->linux_app:
		--->script:
		
7.27--->
	Saturday:
		--->java:
		--->driver:
		--->system_transplant:	
								
						

7.28--->
	Sunday:
		--->java:
		--->driver:
		--->system_transplant:	
							
