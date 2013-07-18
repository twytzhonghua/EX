class Person{
	public String name;
	public int age;

	public void say(String content){
		System.out.println(content);
	}

	
}

public class test{
	
	public static void main(String args[]){
	
		Person p = new Person();

		p.name = "Albert";
		p.age = 24;

		p.say("Java 很简单");

		System.out.println("name=" + p.name);
		System.out.println("Age=" + p.age);
	}
	
}
