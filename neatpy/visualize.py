from . import neat_backend
import networkx as nx
from networkx.drawing.nx_agraph import to_agraph

def genome_to_png(g, name, caption=None):
    if caption == None:
        caption = name
    nodes = []
    labels = []
    for n in [g.get_node(i) for i in range(len(g.nodes))]:
        nodes.append(n.innovation_number)
        labels.append(n.get_type()[0])

    connections = []
    for c in [g.get_connection(i) for i in range(len(g.connections))]:
        if c.disabled == False:
            connections.append((c.from_node.innovation_number, c.to_node.innovation_number, 
                {"weight": "{:.02f}".format(c.weight)}))

    G = nx.MultiDiGraph()
    G.add_nodes_from(nodes)
    G.add_edges_from(connections)

    A = to_agraph(G)
    A.graph_attr["label"] = caption
    A.node_attr["shape"] = "circle"
    for i in range(len(nodes)):
        A.get_node(nodes[i]).attr["label"] = labels[i]
    for x, y, d in connections:
        A.get_edge(x, y).attr["label"] = d["weight"]
    A.layout("dot")
    A.draw("{}.png".format(name))
