//单例类，此类只能创建一个对象

class Singleton{

//static 记录已经产生的对象
	private static Singleton instance;
	
	private Singleton(){}
	
	public static Singleton getInstance(){
		if(instance == null){//如果没有参声对象，则产生新的对象
			instance = new Singleton();
		}
		return instance;//返回已经产生的对象
	
	}
	
}

public class TestSingletion{
	public static void main(String[] args){
		Singleton s1 = Singleton.getInstance();
		Singleton s2 = Singleton.getInstance();
		
		System.out.println( s1 == s2);//两次生成的对象为同一个对象。返回true
	} 
}
