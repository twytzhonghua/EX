import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.*;

public class Gobang
{
	private String[][] board;
	private static int BOARD_SIZE = 15;


	public void initBoard()
	{
		board = new String[BOARD_SIZE][BOARD_SIZE];
	
		for(int i=0;i<BOARD_SIZE;i++)
		{
			for(int j=0;j<BOARD_SIZE;j++)
				board[i][j] = "+";
		}
	}
	
	
	public void printBoard()
	{
		for(int i=0;i<BOARD_SIZE;i++)
		{
			for(int j=0;j<BOARD_SIZE;j++)
				System.out.print(board[i][j]);
			
			System.out.print("\n");
		}


	}

	public static void main(String args[]) throws Exception
	{
		Gobang gd = new Gobang();

		gd.initBoard();
		gd.printBoard();
		
		System.out.println("请输入你下棋的坐标，以x,y格式");
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	
		String inputStr = null;

		while((inputStr = br.readLine()) != null)
		{
			String[] posStrarr = inputStr.split(",");

			int xPos = Integer.parseInt(posStrarr[0]);
			int yPos = Integer.parseInt(posStrarr[1]);
			

			gd.board[xPos - 1][yPos - 1] = "*";

			gd.printBoard();
			System.out.println("请输入你下棋的坐标，以x,y格式");

		}
	}


}

