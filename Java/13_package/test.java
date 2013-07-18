import myPackage.Person;
public class test{
	
	public static void main(String args[]){
	
		Person p = new Person();

		p.setName("Albert");
		p.setAge(24);

		
		System.out.println("name=" + p.getName());
		System.out.println("Age=" + p.getAge());
	}
	
}
