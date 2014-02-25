import java.util.Comparator;
import java.util.ArrayList;
import java.util.PriorityQueue;

class Vertex {

	public final int num;
	public final ArrayList<Edge> adj;

	public Vertex(final int __num, final ArrayList<Edge> __adj) {
		num = __num;
		adj = __adj;
	}

}

class Edge {
	public final Vertex dest;
	public final int weight;

	public Edge(final Vertex __dest, final int __weight) {
		dest = __dest;
		weight = __weight; 
	}

}

class Node {
	
	public boolean visited;	
	public int dist;
	public final Vertex V;

	public Node(final boolean __visited, final int __dist, final Vertex __V) {
		visited = __visited;
		dist = __dist;
		V = __V;
	}

}

class NodeComparator implements Comparator<Node> {

	public int compare(final Node n1, final Node n2) {
		return n1.dist < n2.dist ? -1 : 1;
	}

}

public class DijkstraSSSP {

	private final int src, dest;
	private int spLength = Integer.MAX_VALUE;
	private final PriorityQueue<Node> Q;

	public DijkstraSSSP(final int __src, final int __dest, final ArrayList<Vertex> graph) {
		Node[] nodes = new Node[graph.size()]; 
		src = __src;
		dest = __dest;
		Q = new PriorityQueue<Node>(graph.size(), new NodeComparator());
		for (Vertex v : graph) {
			Q.add(nodes[v.num] = new Node(false, v.num == src ? 0 : Integer.MAX_VALUE, v));
		}
		while (!Q.isEmpty()) {
			Node n = Q.poll();
			n.visited = true;
			if (n.V.num == dest) {
				spLength = n.dist;
				break;
			}
			for (Edge e : n.V.adj) {
				Node dest = nodes[e.dest.num];
				if (!dest.visited) {
					int d = n.dist + e.weight;
					if (d < dest.dist) {
						dest.dist = d;
						Q.remove(dest);
						Q.add(dest);
					}
				}
			}
		}
	}

	public int getSPLength() {
		return spLength;
	}
	
	public static void main(String[] args) {
		ArrayList<Vertex> graph = new ArrayList<Vertex>(6);	
		ArrayList<Edge>[] adj = new ArrayList<>[6];
		DijkstraSSSP test;
		for (int i = 0; i < 6; ++i) {
			adj[i] = new ArrayList<Edge>();
			graph.add(new Vertex(i, adj[i]));
		}
		adj[0].add(new Edge(graph.get(1), 7));
		adj[0].add(new Edge(graph.get(2), 9));
		adj[0].add(new Edge(graph.get(5), 14));
		adj[1].add(new Edge(graph.get(2), 10));
		adj[1].add(new Edge(graph.get(3), 15));
		adj[2].add(new Edge(graph.get(3), 11));
		adj[2].add(new Edge(graph.get(5), 2));
		adj[3].add(new Edge(graph.get(4), 6));
		adj[5].add(new Edge(graph.get(4), 9));
		test = new DijkstraSSSP(0, 4, graph);
		System.out.println(test.getSPLength());
	}

}
