package myPackage; //javac -d . Person.java

public class Person{
    private String name;
    private int age;

    public void setName(String name){
    
        if(name.length()>6 || name.length() < 2){ 
            System.out.println("name length error");
            return;
        }   
        else{
            this.name = name;
        }   
    
    }   

    public String getName(){
        return this.name;
    }   

    public void setAge(int age){
    
        if(age<0 || age>150){
            System.out.println("input age error");
            return;
        }   
        else{
            this.age = age;
        }   
    
    }   

    
    
    public int getAge(){
        return this.age;
    }  
    
}
