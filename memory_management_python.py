import streamlit as st
import matplotlib.pyplot as plt

def visualize_memory_with_labels():
    with open("memory_management_storage_file.txt", "r") as ftr:
        memory = ftr.read()

    memory_blocks = []
    current_size = 0
    start_index = 0
    current_state = memory[0]

    # Group memory into continuous blocks
    for i in range(1, len(memory)):
        if memory[i] != current_state:
            memory_blocks.append((current_state, start_index, i - 1))
            start_index = i
            current_state = memory[i]
    memory_blocks.append((current_state, start_index, len(memory) - 1))  # Add last block

    # For visualization, compress total height to 1000 lines max
    max_lines = 1000
    step = max(1, len(memory) // max_lines)

    fig, ax = plt.subplots(figsize=(4, 12))  # Vertical orientation

    y_pos = 0
    for block in memory_blocks:
        state, start, end = block
        block_len = end - start + 1
        color = 'red' if state == '1' else 'green'
        height = block_len // step
        height = max(height, 1)  # Ensure visible

        ax.add_patch(plt.Rectangle((0, y_pos), 1, height, color=color))
        label = f"{block_len} {'allocated' if state == '1' else 'free'} from {start} to {end}"
        ax.text(1.05, y_pos + height / 2, label, fontsize=6, va='center')

        y_pos += height

    ax.set_xlim(0, 2)
    ax.set_ylim(0, y_pos)
    ax.axis('off')
    st.pyplot(fig)


def memory_management_app():
    def reset_memory():
        n = 10000000
        allocated_blocks = int(n * 0.1)
        with open("memory_management_storage_file.txt", "w") as ftr:
            for i in range(n):
                if 50050 <= i <= (50050 + allocated_blocks):
                    ftr.write('1')
                else:
                    ftr.write('0')
        with open("allocated_variable.txt", "w") as ftr1:
            ftr1.write('0')

        st.sidebar.text("Memory has been reset successfully!")

    def print_available_memory():
        with open("memory_management_storage_file.txt", "r") as ftr:
            memory = ftr.read()
        available_memory = []
        current_size = 0
        start_index = -1

        for i, ch in enumerate(memory):
            if ch == '0':
                if current_size == 0:
                    start_index = i
                current_size += 1
            else:
                if current_size > 0:
                    available_memory.append(f"{current_size} memory is available from {start_index} to {i-1}")
                    current_size = 0

        if current_size > 0:
            available_memory.append(f"{current_size} memory is available from {start_index} to {len(memory) - 1}")

        return available_memory

    def first_fit(size):
        with open("memory_management_storage_file.txt", "r+") as ftr:
            memory = ftr.read()
            index = memory.find('0' * size)
            if index != -1:
                memory = memory[:index] + '1' * size + memory[index + size:]
                ftr.seek(0)
                ftr.write(memory)
                return f"Memory Allocated using First Fit at index {index}"
            else:
                return "No space available for allocation in First Fit"

    def best_fit(size):
        with open("memory_management_storage_file.txt", "r+") as ftr:
            memory = ftr.read()
            min_block_size = float('inf')
            best_fit_index = -1
            current_size = 0
            start_index = 0
            for i in range(len(memory)):
                if memory[i] == '0':
                    if current_size == 0:
                        start_index = i
                    current_size += 1
                else:
                    if current_size >= size and current_size < min_block_size:
                        min_block_size = current_size
                        best_fit_index = start_index
                    current_size = 0
            if current_size >= size and current_size < min_block_size:
                min_block_size = current_size
                best_fit_index = start_index

            if best_fit_index != -1:
                memory = memory[:best_fit_index] + '1' * size + memory[best_fit_index + size:]
                ftr.seek(0)
                ftr.write(memory)
                return f"Memory Allocated using Best Fit at index {best_fit_index}"
            else:
                return "No space available for allocation in Best Fit"


    def worst_fit(size):
        with open("memory_management_storage_file.txt", "r+") as ftr:
            memory = ftr.read()
            max_block_size = 0
            worst_fit_index = -1
            current_size = 0
            start_index = 0

            for i in range(len(memory)):
                if memory[i] == '0':
                    if current_size == 0:
                        start_index = i
                    current_size += 1
                else:
                    if current_size >= size and current_size > max_block_size:
                        max_block_size = current_size
                        worst_fit_index = start_index
                    current_size = 0

            # Check the last block if memory ends in 0s
            if current_size >= size and current_size > max_block_size:
                max_block_size = current_size
                worst_fit_index = start_index

            if worst_fit_index != -1:
                memory = memory[:worst_fit_index] + '1' * size + memory[worst_fit_index + size:]
                ftr.seek(0)
                ftr.write(memory)
                return f"Memory Allocated using Worst Fit at index {worst_fit_index}"
            else:
                return "No space available for allocation in Worst Fit"


    def next_fit(size):
        with open("allocated_variable.txt", "r+") as ftr1:
            last_index = int(ftr1.read().strip())
        
        with open("memory_management_storage_file.txt", "r+") as ftr:
            memory = ftr.read()
            index = memory.find('0' * size, last_index)
            if index != -1:
                memory = memory[:index] + '1' * size + memory[index + size:]
                ftr.seek(0)
                ftr.write(memory)
                with open("allocated_variable.txt", "w") as ftr1:
                    ftr1.write(str(index + size))
                return f"Memory Allocated using Next Fit at index {index}"
            else:
                return "No space available for allocation in Next Fit"

    st.title('Memory Management System')
    st.header("Controls for Memory Management")
    reset_button = st.button('Reset Memory')
    if reset_button:
        reset_memory()

    show_memory_button = st.button('Show Available Memory')
    if show_memory_button:
        available_memory = print_available_memory()
        st.write("Available Memory:")
        for block in available_memory:
            st.write(block)

    size = st.number_input('Enter the size to allocate', min_value=1, max_value=1024 * 1024 * 1024, value=1024)
    unit = st.selectbox('Select size unit', ['KB', 'MB'])
    if unit == 'MB':
        size *= 1024 * 1024
    elif unit == 'GB':
        size *= 1024 * 1024 * 1024

    if st.button('First Fit Algorithm'):
        result = first_fit(size)
        st.write(result)

    if st.button('Best Fit Algorithm'):
        result = best_fit(size)
        st.write(result)

    if st.button('Worst Fit Algorithm'):
        result = worst_fit(size)
        st.write(result)

    if st.button('Next Fit Algorithm'):
        result = next_fit(size)
        st.write(result)

    if st.button('Visualize Memory'):
        visualize_memory_with_labels()
