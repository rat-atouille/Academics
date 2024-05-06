/**
 * This class represents the records that will be stored in the hash table, implemented in Dictionary.java
 * @author Hailey Pong
 *
 */

public class Record {

	//instance variables
	private String key;
	private int score, level;
	

	/*
	 * Constructor
	 * @param String key, int score, int level
	 */	
	public Record(String key, int score, int level) {
		this.key = key;
		this.score = score;
		this.level = level;
	}

	/*
	 * @return string stored in this Record object
	 */
	public String getKey() {
		return key;
	}
	
	/*
	 * @return first int stored in this Record object
	 */
	 public int getScore() {
		 return score;
	 }


	/*
	 * @return second int stored in this Record object
	 */
	 public int getLevel() {
		 return level;
	 }
	 
	
}
