public class test{
	public static void main(String args[]){
		int i = 0;
		int j = 0;

//		outer:
		for(i=0;i<5;i++)
			for(j=0;j<3;j++)
			{
				System.out.println("i=" + i + ",j=" + j);

				if(j==1)
//					break outer;
					break;// break inner for(j=....)
			}
	
	
	
		System.out.println("At last i=" + i + ",j=" + j);
	}
}
