class Base{
	public double size;
	public String name;
	
	public Base(Double size, String name){
		this.size = size;
		this.name = name;
	}
}


public class Sub extends Base{
	
	public String color;

	public Sub(double size, String name, String color){
		super(size,name);//父类的构造函数
		this.color = color;
	}
		
	public static void main(String args[]){
		Sub s =  new Sub(5.6, "test object" ,"red");
		
		System.out.println(s.size + "," + s.name +"," + s.color);
	}
}
