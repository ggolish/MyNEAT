from . import neat_backend
import networkx as nx
import matplotlib.pyplot as plt

def display_genome(g):
    nodes = []
    labels = {}
    for n in [g.get_node(i) for i in range(len(g.nodes))]:
        nodes.append(n.innovation_number)
        labels[n.innovation_number] = n.get_type()[0]
    connections = []
    for c in [g.get_connection(i) for i in range(len(g.connections))]:
        if c.disabled == False:
            connections.append((c.from_node.innovation_number, c.to_node.innovation_number))
    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(connections)
    nx.draw(G, with_labels=True, labels=labels)
    plt.show()

