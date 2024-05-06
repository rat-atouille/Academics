
/**
 * @author Hailey Pong
 * This class represents the location (x,y) of pel
 *
 */
public class Location {
	
	private int x, y;
	
	// constructor sets x and y 
	public Location (int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	// return x
	public int getx() {
		return this.x;
	}
	
	// return y
	public int gety() {
		return this.y;
	}
	
	// compares x and y
	public int compareTo(Location p) {
		//smaller
		//System.out.println("**compare**");
		if (this.gety() > p.gety() || (this.gety() == p.gety() && this.getx() >
		p.getx())) {
			//System.out.println("smaller");
			return 1;
		}
		//same
		else if (this.getx() == p.getx() && this.gety() == p.gety()) {
			//System.out.println("same");
			return 0;
		}
		//larger
		else if (this.gety() < p.gety() || (this.gety() == p.gety() && this.getx() <
		p.getx())) {
			//System.out.println("larger");
			return -1;
		}
		else {
			//System.out.println("NA");
			return -10;
		}
	}
	
	
}
