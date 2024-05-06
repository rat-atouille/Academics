
/**
 * This class represents the data items to be sotred in the nodes of the binary search tree
 *
 */
public class Pel {
	
	private int color;
	private Location Location;
	
	public Pel (Location p, int color) {
		this.Location = p;
		this.color = color;
	}
	
	/*
	 * @return location of this Pel object
	 */
	public Location getLocus() {
		return this.Location;
	}
	
	/*
	 * @return color of this Pel object
	 */
	public int getColor() {
		return this.color;
	}

}
