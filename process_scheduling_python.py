import streamlit as st  #type: ignore
import process_scheduling
import process_scheduling_chart
import plotly.express as px #type: ignore
import pandas as pd #type: ignore
import matplotlib.pyplot as plt #type: ignore

def process_scheduling_app():
    priority = []

    def display_Gantt_Chart(gantt_data):
        fig, ax = plt.subplots(figsize=(10, 2))

        y_position = 0
        
        for entry in gantt_data:
            process_number, start_time, end_time = entry
            print(process_number)
            label = f"P{process_number}" if process_number != 0 else "Idle"
            if (process_number == 0):
                st.write(f"Idle Time! No Process is running!")
            else:
                st.write(f"P{process_number} is running from {start_time} to {end_time}\n")
            bar_width = end_time - start_time
            ax.barh(y_position, width=bar_width, left=start_time, height=0.4, align='center', color='skyblue', edgecolor='black')
            ax.text(start_time + bar_width / 2, y_position, label, ha='center', va='center', fontsize=10, fontweight='bold', color='black')

        ax.set_xlabel("Time")
        ax.set_yticks([])
        ax.set_title("Gantt Chart for Process Scheduling")
        ax.set_xlim(0, max(entry[2] for entry in gantt_data))
        ax.grid(True, linestyle="--", alpha=0.5)
        st.pyplot(fig)

    def findMean(df):
        return (df['Response Time'].mean() + df['Turnaround Time'].mean() + df['Waiting Time'].mean())/3.0

    def findBestAlgo(processes, num_processes, time_quantum = 2, time_quantum2 = 4):
        priority_list = list(range(1, num_processes + 1))
        algorithms = {
            "FCFS": process_scheduling.FCFS_scheduling,
            "Preemptive SJFS": process_scheduling.SJFS_Premption_scheduling,
            "Non-Preemptive SJFS": process_scheduling.SJFS_No_Premption_scheduling,
            "Preemptive LJFS": process_scheduling.LJFS_Premption_scheduling,
            "Non-Preemptive LJFS": process_scheduling.LJFS_No_Premption_scheduling,
            "Round Robin": lambda p, n: process_scheduling.Round_Robin_scheduling(p, n, time_quantum),
            "HRRN": process_scheduling.HRRN_scheduling,
            "Priority Non-Preemptive": lambda p, n: process_scheduling.Priority_No_Premption_scheduling(p, priority_list, n),
            "Priority Preemptive": lambda p, n: process_scheduling.Priority_Premption_scheduling(p, priority_list, n)
        }
        
        mean_values = {}
        
        for algo_name, algo_function in algorithms.items():
            output = algo_function(processes, num_processes)
            
            if "Priority" in algo_name:
                df = pd.DataFrame(output, columns=["Process ID", "Arrival Time", "Burst Time", 
                                                "Response Time", "Turnaround Time", "Waiting Time", "Priority"])
            else:
                df = pd.DataFrame(output, columns=["Process ID", "Arrival Time", "Burst Time", 
                                                "Response Time", "Turnaround Time", "Waiting Time"])
            
            mean_values[algo_name] = findMean(df)

        best_algorithm = min(mean_values, key=mean_values.get)
        return best_algorithm


    st.title("Process Scheduling")

    num_processes = st.number_input("Enter the number of processes: ", min_value = 1, step = 1)
    try:
        num_processes = int(num_processes)
    except ValueError:
        print("Invalid Error!")
        st.stop()
    option = st.selectbox(
        "Select the Process Scheduling Algorithm : ",
        ["FCFS", "Preemptive SJFS", "Non-Preemptive SJFS", "Preemptive LJFS", "Non-Preemptive LJFS", "Round Robin", "HRRN", "Priority Non-Preemptive", "Priority Preemptive"]
    )
    st.header(f"Enter the Arrival Time and Burst Time of {num_processes} Processes\n")
    processes = []
    for i in range(num_processes):
        col1, col2, col3 = st.columns(3)
        with col1:
            arrival_time = st.number_input(f"Enter the arrival time of {i+1} Process : ", min_value = 1, step = 1)
        with col2:
            burst_time = st.number_input(f"Enter the burst time of {i+1} Process : ", min_value = 1, step = 1)
        if option == "Priority Preemptive" or option == "Priority Non-Preemptive":
            with col3:
                priority_val = st.number_input(f"Enter the priority of {i+1} Process : ", min_value = 1, step = 1)
                priority.append(priority_val)
        processes.append([arrival_time, burst_time])

    t1 = None 
    t2 = None

    if option == "Round Robin":
        t1 = st.number_input(f"Enter the time quanta : ", min_value = 1, step = 1)
    if st.button("Process"):
        if (option == "FCFS"):
            output = process_scheduling.FCFS_scheduling(processes, num_processes)
            output1 = process_scheduling_chart.FCFS_scheduling(processes, num_processes)
        elif (option == "Preemptive SJFS"):
            output = process_scheduling.SJFS_Premption_scheduling(processes, num_processes)
            output1 = process_scheduling_chart.SJFS_Premption_scheduling(processes, num_processes)
        elif (option == "Non-Preemptive SJFS"):
            output = process_scheduling.SJFS_No_Premption_scheduling(processes, num_processes)
            output1 = process_scheduling_chart.SJFS_No_Premption_scheduling(processes, num_processes)
        elif (option == "Preemptive LJFS"):
            output = process_scheduling.LJFS_Premption_scheduling(processes, num_processes)
            output1 = process_scheduling_chart.LJFS_Premption_scheduling(processes, num_processes)
        elif (option == "Non-Preemptive LJFS"):
            output = process_scheduling.LJFS_No_Premption_scheduling(processes, num_processes)
            output1 = process_scheduling_chart.LJFS_No_Premption_scheduling(processes, num_processes)
        elif (option == "Round Robin"):
            output = process_scheduling.Round_Robin_scheduling(processes, num_processes, t1)
            output1 = process_scheduling_chart.Round_Robin_scheduling(processes, num_processes, t1)
        elif (option == "HRRN"):
            output = process_scheduling.HRRN_scheduling(processes, num_processes)
            output1 = process_scheduling_chart.HRRN_scheduling(processes, num_processes)
        elif (option == "Priority Non-Preemptive"):
            output = process_scheduling.Priority_No_Premption_scheduling(processes, priority, num_processes)
            output1 = process_scheduling_chart.Priority_No_Premption_scheduling(processes, priority, num_processes)
        elif (option == "Priority Preemptive"):
            output = process_scheduling.Priority_Premption_scheduling(processes, priority, num_processes)
            output1 = process_scheduling_chart.Priority_Premption_scheduling(processes, priority, num_processes)
        if option == "Priority Preemptive" or option == "Priority Non-Preemptive":
            df = pd.DataFrame(output, columns=["Process ID", "Arrival Time", "Burst Time", "Response Time", "Turnaround Time", "Waiting Time", "Priority"])
        else:
            df = pd.DataFrame(output, columns=["Process ID", "Arrival Time", "Burst Time", "Response Time", "Turnaround Time", "Waiting Time"])
        st.header("Gantt's Chart\n")
        display_Gantt_Chart(output1)
        st.header("Scheduling Results\n")
        st.table(df)
        st.subheader(f"Average Response Time : {df['Response Time'].mean()}")
        st.subheader(f"Average Turnaround Time : {df['Turnaround Time'].mean()}")
        st.subheader(f"Average Waiting Time : {df['Waiting Time'].mean()}")
        best_algo_val = findBestAlgo(processes, num_processes)
        st.markdown(f"Out of all the scheduling algorithms **{best_algo_val}** is giving the best results!")