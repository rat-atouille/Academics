
public class Node {

	private int id;
	private boolean mark;
	
	public Node(int id) {
		this.id = id;
	}
	
	public void markNode(boolean mark){
		this.mark = mark;
	}
	
	public boolean getMark() {
		return this.mark;
	}
	
	public int getId() {
		return this.id;
	}
	
}
