
public class Edge {
	
	private Node u,v;
	private String type;
	
	public Edge(Node u, Node v, String type){
		this.u = u;
		this.v = v;
		this.type = type;
	}
	
	public Node firstNode() {
		return this.u;
	}
	
	public Node secondNode() {
		return this.v;
	}
	
	public String getType() {
		return this.type;
	}
	
}
