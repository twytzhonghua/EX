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
		--->driver:	1.6_async_notification:异步通知
		--->linux_app:
		--->script:
		
		
7.16--->
	Tuesday:
		--->java:├── 1_hello
				│   ├── hello.class
				│   └── hello.java
				├── 2_data_type //java中数据类型转换 整除 求余...
				│   ├── test.class
				│   └── test.java
				├── 3_lable	//标签  break continue
				│   ├── test.class
				│   └── test.java
				├── 4_array	//数组的声明方式和引用
				│   ├── test.class
				│   └── test.java
				└── 5_foreach//foreach来遍历数组
				    ├── test.class
					    └── test.java
				├── 6_Person//引用person类 构建person对象
				│   └── test.class
				├── 7_array_sort
				│   ├── array.class//利用java库和自己的算法排序
				│   └── array.java
				├── 8_changeable_fun//可变函数中参数类型不定的写法
				│   ├── array.class
				│   └── array.java
				└── 9_
				    ├── twod_array.class//二维虚拟数组的声明、初始化、引用
				    └── twod_array.java

		--->driver:7_irq
		--->hardware:桥式整流电路
	
7.17--->
	Wednesday:
		--->java:
			├── 10_chess_board //构建五子棋棋盘
			│   └── Gobang.java
			├── 11_this
			│   ├── retrunthis//this 指针的连续用法
			│   │   ├── Returnthis.class
			│   │   └── Returnthis.java
			│   └── this//this 指针的用法
			│       └── TestDog.java
			├── 12_overload//方法的重载
			│   └── Overload.java
			├── 13_package//java 中的打包， package myPackage.person   import myPackage.person  编译 javac -d . Person.java
			│   ├── myPackage
			│   │   └── Person.class
			│   ├── Person.java
			│   ├── test.java
			── 14_ConstructorOverload//构造函数 或方法的重载、参数个数不同 this
			│   ├── Apple.java
			/* public Apple(String name, String color, double weight){
			 ~                        | 15         this(name,color);
			 ~                        | 16         this.weight = weight;
			 ~                        | 17     }
			*/
			├── 15_extends//继承的写法
			│   ├── Apple.java
			│   └── Fruit.java
			├── 16_overwrite_fun //子类继承父类，改写父类中的方法
			│   ├── Bird.java
			│   └── Ostrich.java
			├── 17_super//super() 调用父类中的方法以实现自己的方法
			│   └── Sub.java/* public Sub(double size, String name, String color){
			~                        | 17         super(size,name);
			~                        | 18         this.color = color;
			~                        | 19     }   */
			├── 18_Polymorphism//子类向上转型，以父类编译，但是以子类方法执行
			│   └── SubClass.java// BaseClass ts = new SubClass();//以父类编译，以子类运行  

		--->driver:7_irq
		--->linux_app:
		--->script:
7.18--->
	Thursday:
		--->java:
		├── 19_instanceof // (a instanceof b) 判断a 是否 属于b类，转型的前提 
		│   ├── TestInstanceof.class
		│   └── TestInstanceof.java
		├── 20_reuse
									12 class Bird extends Animal{
		 ~                        | 13     private Animal a;//私有对象 复用父类的方法
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

		│   ├── Animal.class
		│   ├── Bird.class
		│   ├── TestInherit.class
		│   ├── TestInherit.java
		│   └── Wolf.class
		├── 21_data_conversion
						/*	String intstr = "123";
		                    |  5         int it = Integer.parseInt(intstr);
						*/
	    ├── Primitive2String.class
		│   └── Primitive2String.java
		├── 22_toString/*
		~                        | 15      *toString 是Object的一个方法，所有对象都是Object的子类，故拥有toString方法，
		~                        | 16      * 如果输出System.out.println(p) 即输出p.toString(),其实就是类的自我描述。
		~                        | 17      */

		│   ├── Apple.class
		│   ├── testToString.class
		│   └── testToString.java
		├── 23_inner_empty_obj2/*     public static void main(String args[]){
		~                        | 13         NullAccessStatic na = null;
		~                        | 14         na.test();
		~                        | 15         
		~                        | 16          // 空对象可以访问本类中的static成员或方法，不能访问其他的实例成员，否则会出现异常。
		~                        | 17         //下面的调用将会出现异常 
		~                        | 18         na.say(); 
								*/
		│   ├── NullAccessStatic.class
		│   └── NullAccessStatic.java
		├── 24_Singleton//单例类，类只能被创建一个对象
		│   ├── Singleton.class
		│   ├── TestSingletion.class
		│   └── TestSingletion.java
		├── 25_final////final修饰的成员变量只能在定义或初始化快中赋值，不能在普通方法中赋值，也不能重复赋值。
		│   ├── TestFinalLocalVariable.class
		│   └── TestFinalLocalVariable.java
		
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
	Monda:；
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
							
