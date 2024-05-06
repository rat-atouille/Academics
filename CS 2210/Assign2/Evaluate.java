
/**
 * @author Hailey Pong
 * This class implements all the auxiliary methods needed by the algorithm that plays the game
 */

public class Evaluate {

	private char[][] gameBoard; 		//2D array
	private int gameSize, winSize;
	
	
	/*
	 * constructor
	 * initializes the array gameBoard
	 * @param int size of the array
	 * @param int tilesToWin number of adjacent tiles needed to win
	 * @param int maxLevels playing quality
	 */
	public Evaluate (int size, int tilesToWin, int maxLevels) {
		gameBoard = new char[size][size];
		gameSize = size;
		winSize = tilesToWin;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				gameBoard[i][j] = 'e';}
		}
	}
	
	/*
	 * @return empty Dictionary
	 */
	public Dictionary createDictionary() {
		Dictionary dictionary = new Dictionary(10037);
		return (dictionary);
	}
	
	/*
	 * 
	 */
	public Record repeatedState(Dictionary dict) {
		String s = "";	//string representation of the game
		for (int row = 0; row < gameSize; row++) {
			for (int col  = 0; col < gameSize; col++) {
				s += (gameBoard[row][col]); 
			}
		}
		if (dict.get(s) != null) return dict.get(s);
		else return null;
	}
	
	/*
	 * insert record in dictionary if there are no dupilicate keys
	 */
	public void insertState(Dictionary dict, int score, int level) {
		String s = "";	//string representation of the game
		for (int row = 0; row < gameSize; row++) {
			for (int col  = 0; col < gameSize; col++) {
				s += (gameBoard[row][col]); 
				} 
			}
		Record rec = new Record(s,score,level);
		if (dict.get(rec.getKey()) == null) {
			dict.put(rec);
		}
	}
	
	
	/*
	 * stores symbol in designated array
	 */
	public void storePlay(int row, int col, char symbol) {
		gameBoard[row][col] = symbol;
	}
	
	
	/*
	 * @return true if designated array stores 'e' else return false
	 */
	public boolean squareIsEmpty (int row, int col) {
		if (gameBoard[row][col] == 'e') {
			return true;
		}
		else return false;
	}
	
	/*
	 * @return true if designated array stores 'c' else return false
	 */
	public boolean tileOfComputer (int row, int col) {
		if (gameBoard[row][col] == 'c') {
			return true;
		}
		else return false;
	}
	
	
	/*
	 * @return true if designated array stores 'h' else return false
	 */
	public boolean tileOfHuman (int row, int col) {
		if (gameBoard[row][col] == 'h') {
			return true;
		}
		else return false;
	}
	
	
	/*
	 * return true if required adjacent char is in the array
	 * else return false
	 */
	public boolean wins(char symbol) {
		
		for (int i = 0; i < gameSize; i++) {
			for (int j = 0; j < gameSize; j++) {
				if (diagonalL(i,j,symbol)) {
					return true;}
				else if (diagonalR(i,j,symbol)) {
					return true;}
				else if (vertical(i,j,symbol)) {
					return true;}
				else if (horizontal(i,j,symbol)) {
					return true;}
			}
		}
		return (false);
	}
	
	
	/*
	 * @return true if there are no empty positions left
	 * @return false otherwise
	 */
	public boolean isDraw() {
		for (int row = 0; row < gameSize; row++) {
			for (int col = 0; col < gameSize; col++) {
				if (gameBoard[row][col] == 'e') {
				return (false);}
			}
		}
		return true;
	}
	
	
	public int evalBoard() {
		
		if (wins('h') == true) {
			return (0);
		}
		else if (wins('c') == true) {
			return (3);
		}
		else if ((wins('c') == false) && (wins('h') == false) && (isDraw() == true)) {
			return (2);
		}
		else {
			return (1);
		}
	}
	
	
	private boolean diagonalL(int row, int col, char symbol) {
		int count = 0;
		
		for (int i = 0; row-i >=0 && col +i < gameSize; i++) {
			if (gameBoard[row-i][col+i] != symbol && count < winSize) {
				return false;
			}
			count++;
		}
		if (count >= winSize) {
			return true;}
	
		return (false);
	}
	
	/*
	 * read diagonally from right downwards
	 */
	private boolean diagonalR(int row, int col, char symbol) {
		int count = 0;
		int pos = 0;
		
		if (row>col) {
			pos = row;}
		else {
			pos = col;}
		
		for (int i = 0; pos+i < gameSize ; i++) {
			if (gameBoard[row+i][col+i] != symbol && count < winSize) {
				return false;
			}
			count++;
		}
		if (count >= winSize) return true;
		return (false);
	}
	
	
	/*
	 * iterate through the loop horizontally
	 */
	private boolean horizontal(int row, int col, char symbol) {
		int count = 0;		
		char curr;

			
		for (int c = col; c < gameSize; c++) {
			
			curr = gameBoard[row][c];

			//element at the beginning of the array
			 if ((c==0 && c+1 <gameSize) && (curr == symbol && gameBoard[row][c+1] == symbol)){
				count++;
			}
			//element that is not the end of the list
			else if ((c-1 >= 0 && c+1 <gameSize) && (curr == symbol && gameBoard[row][c-1] == symbol)){
				count++;}
			
			//element at the end of matrix
			else if ((c == gameSize-1) && (curr == symbol && gameBoard[row][c-1] == symbol)) {
				count++;}	
		}
		
		if (count >= winSize) return (true);
		else return (false);
		
	}
	
	/*
	 * iterate through the loop vertically
	 */
	private boolean vertical(int row, int col, char symbol) {
		int count = 0;	
		char curr;
		for (int r=row; r < gameSize; r++) {
			curr = gameBoard[r][col];
			
			if ((r == 0 && r+1 <gameSize) && (curr == symbol && gameBoard[r+1][col] == symbol)){
				count++;}
			
			else if ((r-1 >= 0 && r+1 <gameSize) && (curr == symbol && gameBoard[r-1][col] == symbol)){
				count++;}
			
			//element at the end of matrix
			else if ((r == gameSize-1) && (curr == symbol && gameBoard[r-1][col] == symbol)) {
				count++;}	}
			
		if (count >= winSize) return true;
		else return false;
	}
}
