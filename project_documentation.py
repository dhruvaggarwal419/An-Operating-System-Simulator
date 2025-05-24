import streamlit as st


def project_documentation_app():

    st.title("Documentation")

    st.header("Process Scheduling")

    st.subheader("Definition")
    st.write("""
    Process Scheduling is the mechanism by which the operating system selects which process should execute next from the ready queue. It plays a critical role in multitasking, ensuring optimal CPU utilization and performance.
    """)

    st.subheader("Algorithms")

    st.markdown("**1. First-Come, First-Served (FCFS)**")
    st.write("Non-preemptive algorithm where the process that arrives first gets executed first.")

    st.markdown("**2. Shortest Job First (SJF)**")
    st.write("Non-preemptive algorithm where the process with the shortest burst time is selected next.")

    st.markdown("**3. Longest Job First (LJF)**")
    st.write("Non-preemptive algorithm that selects the process with the longest burst time.")

    st.markdown("**4. Round Robin (RR)**")
    st.write("Preemptive algorithm where each process is assigned a fixed time quantum in cyclic order.")

    st.markdown("**5. Shortest Remaining Time First (SRTF)**")
    st.write("Preemptive version of SJF; the process with the smallest remaining burst time is scheduled next.")

    st.markdown("**6. Longest Remaining Time First (LRTF)**")
    st.write("Preemptive algorithm where the process with the longest remaining burst time is executed next.")

    st.markdown("**7. Priority Scheduling (Non-Preemptive)**")
    st.write("The process with the highest priority is executed first without interruption.")

    st.markdown("**8. Priority Scheduling (Preemptive)**")
    st.write("If a new process with a higher priority arrives, it preempts the current process.")

    st.markdown("**9. Highest Response Ratio Next (HRRN)**")
    st.write("Non-preemptive algorithm that selects the process with the highest response ratio next.")

    st.header("Disk Scheduling")

    st.subheader("Definition")
    st.write("""
    Disk Scheduling algorithms determine the order in which disk I/O requests are processed to minimize seek time.
    """)

    st.subheader("Algorithms")

    st.markdown("**1. FCFS (First Come First Serve)**")
    st.write("Requests are addressed in the order they arrive.")

    st.markdown("**2. SSTF (Shortest Seek Time First)**")
    st.write("Chooses the request closest to the current head position.")

    st.markdown("**3. SCAN**")
    st.write("The disk arm moves in one direction and services requests in its path.")

    st.markdown("**4. CSCAN (Circular SCAN)**")
    st.write("Similar to SCAN but after reaching the end, it jumps to the beginning and continues.")

    st.markdown("**5. LOOK**")
    st.write("Similar to SCAN but the arm only goes as far as the last request in the current direction.")

    st.markdown("**6. CLOOK (Circular LOOK)**")
    st.write("Similar to CSCAN but doesn't go to the end if there are no requests.")

    st.header("Memory Management")

    st.subheader("Definition")
    st.write("""
    Memory Management in OS refers to the process of managing the system's primary memory, ensuring proper allocation and deallocation of memory blocks.
    """)

    st.subheader("Algorithms")

    st.markdown("**1. First Fit**")
    st.write("Allocates the first memory block that is large enough.")

    st.markdown("**2. Best Fit**")
    st.write("Allocates the smallest memory block that fits the request.")

    st.markdown("**3. Worst Fit**")
    st.write("Allocates the largest memory block available.")

    st.markdown("**4. Next Fit**")
    st.write("Works like First Fit but continues searching from the last allocated block.")

    st.header("Deadlock & Banker's Algorithm")

    st.subheader("Definition")
    st.write("""
    Deadlock is a situation in an OS where a set of processes are blocked because each process is holding a resource and waiting for another resource acquired by some other process.
    """)

    st.subheader("Banker's Algorithm (Deadlock Avoidance)")

    st.write("""
    The Banker's Algorithm is used to avoid deadlocks by simulating the allocation of resources and ensuring that the system remains in a safe state before actual allocation.
    """)

    st.header("Page Replacement Algorithms")

    st.subheader("Definition")
    st.write("""
    Page Replacement Algorithms are used in virtual memory systems to decide which memory pages to swap out when a new page needs to be loaded.
    """)

    st.subheader("Algorithms")

    st.markdown("**1. First-In-First-Out (FIFO)**")
    st.write("Replaces the oldest page in memory.")

    st.markdown("**2. Least Recently Used (LRU)**")
    st.write("Replaces the page that hasn’t been used for the longest period.")

    st.markdown("**3. Optimal (OPT)**")
    st.write("Replaces the page that will not be used for the longest time in the future.")

    st.header("AI OS Chatbot Assistant")

    st.subheader("Definition")
    st.write("""
    The AI OS Chatbot Assistant is an intelligent virtual assistant integrated into the OS simulator that provides real-time interaction, explanation, and help for users exploring operating system algorithms.
    """)

    st.subheader("Types of Features")

    st.markdown("**1. Natural Language Interface**")
    st.write("Users can interact with the chatbot using everyday English.")

    st.markdown("**2. OS Concept Explanations**")
    st.write("The bot explains technical OS topics like FCFS, LRU, etc.")

    st.markdown("**3. Algorithm Guidance**")
    st.write("Provides step-by-step guidance on how algorithms work.")

    st.markdown("**4. Query Response**")
    st.write("Answers questions like 'What is turnaround time in SJF?'")

    st.markdown("**5. Error Assistance**")
    st.write("Helps debug or explain simulator errors to the user.")

    st.markdown(
        "For the complete source code and implementation details, please visit the "
        "[GitHub Repository](https://github.com/dhruvaggarwal419/An-Operating-System-Simulator)."
    )