public class Apple{

	public String name;
	public String color;
	public double weight;
	public	Apple(){
	}
	
	public Apple(String name, String color){
		this.name = name;
		this.color = color;
	}
	
	public Apple(String name, String color, double weight){
		this(name,color);
		this.weight = weight;
	}
	
	public static void main(String args[]){
		Apple app1 = new Apple("boo", "green");
		Apple app2 = new Apple("hh","red",1.56);
		
		System.out.println("app1.name=" + app1.name + ", app1.color=" + app1.color + ", app1.weight" + app1.weight);
		System.out.println("app2.name=" + app2.name + ", app2.color=" + app2.color + ", app2.weight" + app2.weight);
	}
}
