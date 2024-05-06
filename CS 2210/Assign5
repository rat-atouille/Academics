import java.util.Iterator;
import java.util.Stack;

public class Graph implements GraphADT{
	
	private int n;
	private Edge edge[][]; 		// store Edges object in the matrix
	private Node node[];		// store nodes
	
	// constructor
	public Graph(int n) {
		this.n = n;
		edge = new Edge[n][n];
		node = new Node[n];
		// create an array storing n nodes
		for (int i = 0; i < n; i++) {
			node[i] = new Node(i);
		}		
	}
	
	
	// return node with specified int
	// throw exception if it doesnt exist
	public Node getNode(int id) throws GraphException{
		
		// check if id is valid Node id
		Boolean valid = (id >=0 && id < n );
		
		// id is invalid or the node with given id does not exist
		if (!valid || node[id].getId() != id) {
			throw new GraphException("does not exist");
		}
		else {
			return (node[id]);
		}
	}
	
	// add edge to Node u and v 
	// throws exception if either node doesn't exist or if edge already exists
	public void addEdge (Node u, Node v, String edgeType) throws GraphException{
	
		// check if Node u and v are valid nodes
		Boolean valid = (u.getId()>=0 && u.getId() < n && v.getId() >= 0 && v.getId() < n);
		
		// either node does not exist or edge already exists so throw exception
		if (!valid ||
				node[u.getId()].getId() != u.getId() 
				|| node[v.getId()].getId() != v.getId() 
				||  edge[u.getId()][v.getId()] != null) {
			throw new GraphException("either node does not exist or edge already exists");
		}

		// add edge
		else {			
			edge[u.getId()][v.getId()] = new Edge(u,v,edgeType);
			edge[v.getId()][u.getId()] = new Edge(v,u,edgeType);
		}

	}
	
	// return iterator storing all edges
	// return null if u does not have any edges
	public Iterator<Edge> incidentEdges(Node u) throws GraphException{
		
		// check if Node u is a valid node
		Boolean valid = (u.getId()>=0 && u.getId()<n);
		
		// invalid node throw exception
		if (valid == false) {
			throw new GraphException("invalid node");
		}
		
		// node exists
		if (valid == true) {
			//System.out.println("**");
			
			// store incident edges
			Stack <Edge> incidents = new Stack<Edge>();

			for (int i =0; i < n; i++) {
				if (edge[u.getId()][i] != null) {
					incidents.push(edge[u.getId()][i]);
				}
			}
			
			// no incident edges
			if (incidents.isEmpty()) {
				return null;
			}
			
			//return incident edges
			else {
				return incidents.iterator();
			}
		}
		
		// node doesn't exist
		else {
			return null;
	}
}
	
	// return edge connecting u and v
	// throws exception if there is no edge
	public Edge getEdge(Node u, Node v) throws GraphException {
		
		// check if Node u and v are valid nodes
		Boolean valid = (u.getId()>=0 && u.getId() < n && v.getId() >= 0 && v.getId() < n);
		
		if (valid == false ||
				node[u.getId()].getId() != u.getId() 
				|| node[v.getId()].getId() != v.getId() 
				|| edge[u.getId()][v.getId()] == null) {
			throw new GraphException("does not exist");
		}

		// return edge
		else {
			return (edge[u.getId()][v.getId()]);
		}		
	}
	
	
	// return true if node u and v are adjacent
	// false otherwise
	public boolean areAdjacent(Node u, Node v) throws GraphException {
		
		// check if Node u and v are valid nodes
		Boolean valid = (u.getId()>=0 && u.getId() < n && v.getId() >= 0 && v.getId() < n);
		
		// are adjacent
		if (valid == true) {
			return (edge[u.getId()][v.getId()] != null);
		}
		
		// invalid nodes throw exception
		else {
			throw new GraphException("invalid node");
		}
	}
	

}
