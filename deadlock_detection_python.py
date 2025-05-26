import streamlit as st
import numpy as np
import deadlock_python  # type: ignore
import networkx as nx
import matplotlib.pyplot as plt

def deadlock_detection_app():
    def draw_allocation_graph(n, m, allocation, max_matrix, available):
        G = nx.DiGraph()
        for j in range(m):
            G.add_node(f"R{j}", color='skyblue')
        for i in range(n):
            G.add_node(f"P{i}", color='lightgreen')
        for i in range(n):
            for j in range(m):
                if allocation[i][j] > 0:
                    G.add_edge(f"R{j}", f"P{i}", label=f"A:{allocation[i][j]}")
        for i in range(n):
            for j in range(m):
                need = max_matrix[i][j] - allocation[i][j]
                if need > 0:
                    G.add_edge(f"P{i}", f"R{j}", label=f"N:{need}")
        pos = nx.spring_layout(G, seed=42)
        edge_labels = nx.get_edge_attributes(G, 'label')
        node_colors = [G.nodes[node]['color'] for node in G.nodes]

        fig, ax = plt.subplots()
        nx.draw(G, pos, with_labels=True, node_color=node_colors, node_size=1500, arrows=True, ax=ax)
        nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, ax=ax)

        st.pyplot(fig)


    st.title("Banker's Algorithm")

    n = st.number_input("Number of Processes (n)", min_value=1, step=1)
    m = st.number_input("Number of Resource Types (m)", min_value=1, step=1)

    allocation = []
    max_matrix = []
    available = []

    if n > 0 and m > 0:
        st.write("### Allocation Matrix (Current allocation)")
        for i in range(int(n)):
            row = st.text_input(
                f"Enter resources allocated to Process P{i} (connected to R0 to R{int(m)-1})",
key=f"alloc_row_{i}")
            if row:
                allocation.append(list(map(int, row.strip().split())))
            else:
                allocation.append([0] * int(m))

        st.write("### Max Matrix (Maximum demand)")
        for i in range(int(n)):
            row = st.text_input(
                f"Enter maximum demand for Process P{i} (connected to R0 to R{int(m)-1})",
key=f"max_row_{i}")
            if row:
                max_matrix.append(list(map(int, row.strip().split())))
            else:
                max_matrix.append([0] * int(m))

        st.write("### Available Vector (Resources available)")
        available_str = st.text_input(
            f"Available resources (space separated {int(m)} numbers)",
            key="available_vector"
        )
        if available_str:
            available = list(map(int, available_str.strip().split()))
        else:
            available = [0] * int(m)

        if st.button("Show Entered Data"):
            st.write("Allocation Matrix:")
            st.write(np.array(allocation))
            st.write("Max Matrix:")
            st.write(np.array(max_matrix))
            st.write("Available Vector:")
            st.write(np.array(available))
            need = np.array(max_matrix) - np.array(allocation)
            st.write("Need Matrix (Max - Allocation):")
            st.write(need)

    if st.button("Check System Safety"):
        if allocation is None:
            st.error(f"Allocation matrix input should have exactly {n} rows and {m} columns per row.")
        elif max_matrix is None:
            st.error(f"Max matrix input should have exactly {n} rows and {m} columns per row.")
        elif available is None:
            st.error(f"Available vector input should have exactly {m} numbers.")
        else:
            safe, safe_sequence = deadlock_python.check_safety(n, m, allocation, max_matrix, available)
            if safe:
                st.success("The system is in a SAFE state. No deadlock will occur.")
                st.write("### Safe Sequence:")
                st.code(" → ".join(f"P{pid}" for pid in safe_sequence), language="text")
            else:
                st.error("The system is in an UNSAFE state. Deadlock may occur!")
        st.write('### Diagram')
        draw_allocation_graph(int(n), int(m), allocation, max_matrix, available)
