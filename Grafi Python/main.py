import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

def plot_frame(G,colormap,ax):
    ax.clear()
    pos_layout = nx.spring_layout(G,seed=1)
    colors = [colormap[v] for v in G]
    nx.draw_networkx(G, with_labels=True, pos=pos_layout, node_color=colors)
    plt.pause(1)
    #plt.show()

def visit(G, vs, animation, draw_graph_and_tree, alfa):
    if animation:
        plt.figure()
        ax = plt.axes()
        colormap = {v:'blue' for v in G}
        plot_frame(G,colormap,ax)

    Q = []
    T = nx.Graph()
    Q.append(vs)
    G.nodes[vs]['found'] = True
    T.add_node(vs)
    while Q:
        vgreen = Q.pop(alfa)
        if animation:
            colormap[vgreen] = 'green'
        for v in G[vgreen]:
            if animation and colormap[v] == 'blue':
                colormap[v] = 'yellow'
            if 'found' not in G.nodes[v]:
                Q.append(v)
                G.nodes[v]['found'] = True
                T.add_node(v)
                T.add_edge(vgreen,v)
        if animation:
            if Q: colormap[Q[alfa]] = 'orange'
            plot_frame(G,colormap,ax)
            colormap[vgreen] = 'red'
    
    if animation:
        plot_frame(G,colormap,ax)
        plt.close()
    
    if draw_graph_and_tree:
        pos_layoutG = nx.spring_layout(G,seed=1)
        pos_layoutT = nx.spring_layout(T,seed=1)
        plt.figure()
        nx.draw_networkx(G,with_labels=True,pos=pos_layoutG)
        plt.figure()
        nx.draw_networkx(T,with_labels=True,pos=pos_layoutT)
        plt.show()

    for v in G:
        del G.nodes[v]['found']
        
    return T

def breadth_first_search(G, vs, animation = False, draw_graph_and_tree = False):
    visit(G,vs, animation, draw_graph_and_tree, 0)

def depth_first_search(G, vs, animation = False, draw_graph_and_tree = False):
    visit(G,vs, animation, draw_graph_and_tree, -1)

G = nx.cycle_graph(10)
G.add_nodes_from([10,11])
G.add_edges_from([(10,0),(10,4),(10,11)])
G.add_edges_from([(11,5),(11,7)])
G.add_edges_from([(1,9),(2,4),(6,8)])

breadth_first_search(G,0, animation = True, draw_graph_and_tree=True)
depth_first_search(G,0, animation = True, draw_graph_and_tree=True)
