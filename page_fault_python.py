import streamlit as st

def simulate_fcfs(pages, frames):
    memory = []
    faults = 0
    visualization = []

    for page in pages:
        if page not in memory:
            faults += 1
            if len(memory) < frames:
                memory.append(page)
            else:
                memory.pop(0)
                memory.append(page)
        visualization.append(list(memory))

    return faults, visualization


def simulate_lru(pages, frames):
    memory = []
    recently_used = []
    faults = 0
    visualization = []

    for page in pages:
        if page not in memory:
            faults += 1
            if len(memory) < frames:
                memory.append(page)
            else:
                lru_page = recently_used.pop(0)
                memory.remove(lru_page)
                memory.append(page)
        else:
            recently_used.remove(page)

        recently_used.append(page)
        visualization.append(list(memory))

    return faults, visualization


def simulate_optimal(pages, frames):
    memory = []
    faults = 0
    visualization = []

    for i in range(len(pages)):
        page = pages[i]
        if page not in memory:
            faults += 1
            if len(memory) < frames:
                memory.append(page)
            else:
                future = pages[i+1:]
                indices = [future.index(p) if p in future else float('inf') for p in memory]
                idx_to_replace = indices.index(max(indices))
                memory[idx_to_replace] = page
        visualization.append(list(memory))

    return faults, visualization


def page_replacement_app():
    st.title("Page Replacement Algorithms Simulator")

    reference_string = st.text_input("Enter the reference string (space separated):", "7 0 1 2 0 3 0 4 2 3 0 3 2")
    frames = st.number_input("Number of Frames", min_value=1, max_value=10, value=3)

    if st.button("Simulate"):
        try:
            pages = list(map(int, reference_string.strip().split()))
        except ValueError:
            st.error("Invalid input! Please enter only integers.")
            return

        fcfs_faults, fcfs_vis = simulate_fcfs(pages, frames)
        lru_faults, lru_vis = simulate_lru(pages, frames)
        opt_faults, opt_vis = simulate_optimal(pages, frames)

        # Output comparison
        st.subheader("Page Faults Comparison:")
        st.write(f"FCFS: {fcfs_faults} faults")
        st.write(f"LRU: {lru_faults} faults")
        st.write(f"Optimal: {opt_faults} faults")

        best = min(fcfs_faults, lru_faults, opt_faults)
        if best == fcfs_faults:
            st.success("FCFS performed best for this reference string.")
        elif best == lru_faults:
            st.success("LRU performed best for this reference string.")
        else:
            st.success("Optimal algorithm performed best for this reference string.")

        st.subheader("🔍 Step-by-Step Visualization")

        def show_steps(visualization, name):
            st.markdown(f"**{name}**")
            for i, mem in enumerate(visualization):
                st.write(f"Step {i+1}: Page → {pages[i]}, Frame → {mem}")

        show_steps(fcfs_vis, "FCFS")
        show_steps(lru_vis, "LRU")
        show_steps(opt_vis, "Optimal")

page_replacement_app()
