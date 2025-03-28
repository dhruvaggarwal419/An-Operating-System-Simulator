import matplotlib.pyplot as plt
import streamlit as st

def disk_scheduling_app():
    def calculateMovements(positions):
        movements = 0
        for i in range(1, len(positions)):
            movements = movements + abs(positions[i] - positions[i-1])
        return movements
    
    def plot_fig(x, y, algo, movements):
        fig = plt.figure(figsize=(10, 5))
        plt.plot(x, y, marker='o', linestyle='-', color='green', markersize=8, markerfacecolor='lightgreen')
        for i, txt in enumerate(x):
            plt.annotate(txt, (x[i], y[i]), textcoords="offset points", xytext=(0,10), ha='center')
        plt.xticks(sorted(set(x))) 
        plt.yticks(y)
        plt.xlabel("Track Number")
        plt.ylabel("Order of execution")
        plt.title(algo)
        plt.grid(True, linestyle='--', alpha=0.7)
        plt.show()
        st.pyplot(fig)
        st.markdown(f"The Total Movements are **{movements}**")

    def FCFS_Algorithm(requests, head):
        movements = 0
        positions = []
        positions.append(head)
        for i in requests:
            positions.append(i)
            movements = movements + abs(i - head)
            head = i
        x = positions 
        y = range(len(positions)) 
        plot_fig(x, y, "FCFS Disk Scheduling Visualization", movements)

    def SSTS_Algorithm(requests, head):
        movements = 0
        positions = []
        positions.append(head)
        minDiff = float('inf')
        minIndex = -1
        for _ in range(len(requests)):
            minDiff = float('inf')
            for j in range(0, len(requests)):
                if (requests[j] != float('inf') and minDiff > (abs(requests[j]-head))):
                    minDiff = abs(requests[j] - head)
                    minIndex = j
            if minIndex != -1:
                movements = movements + abs(requests[minIndex] - head)
                head = requests[minIndex]
                positions.append(requests[minIndex])
                requests[minIndex] = float('inf')
        x = positions
        y = range(len(positions))
        plot_fig(x, y, "SSTS Disk Scheduling Visualization", movements)

    def SCAN_Algorithm(requests, head, option_chosen):
        movements = 0
        positions = []
        positions.append(head)
        if option_chosen == "Low":
            sorted_requests = sorted(requests)
            approxValue = 0
            for i in range(0, len(sorted_requests)):
                if (sorted_requests[i] <= head):
                    approxValue = i
                else:
                    break
            for i in range(approxValue, -1, -1):
                positions.append(sorted_requests[i])
            if positions[-1] != 0:
                positions.append(0)
            for i in range(approxValue+1, len(sorted_requests)):
                positions.append(sorted_requests[i]) 
        else:
            sorted_requests = sorted(requests)
            approxValue = 0
            for i in range(0, len(sorted_requests)):
                if sorted_requests[i] >= head:
                    approxValue = i
                    break
            for i in range(approxValue, len(sorted_requests)):
                positions.append(sorted_requests[i]) 
            positions.append(max(sorted_requests)+1)
            for i in range(approxValue-1, -1, -1):
                positions.append(sorted_requests[i])
        x = positions
        y = range(len(positions))
        movements = calculateMovements(positions)
        plot_fig(x, y, "Scan (Elevator) Disk Scheduling Visualization", movements)

    def C_SCAN_Algorithm(requests, head, option_chosen):
        movements = 0
        positions = []
        positions.append(head)
        if option_chosen == "Low":
            sorted_requests = sorted(requests)
            approxValue = 0
            for i in range(0, len(sorted_requests)):
                if (sorted_requests[i] <= head):
                    approxValue = i
                else:
                    break
            for i in range(approxValue, -1, -1):
                positions.append(sorted_requests[i])
            if positions[-1] != 0:
                positions.append(0)
            positions.append(max(requests)+1)
            for i in range(len(sorted_requests)-1, approxValue, -1):
                positions.append(sorted_requests[i]) 
        else:
            sorted_requests = sorted(requests)
            approxValue = 0
            for i in range(0, len(sorted_requests)):
                if sorted_requests[i] >= head:
                    approxValue = i
                    break
            for i in range(approxValue, len(sorted_requests)):
                positions.append(sorted_requests[i]) 
            positions.append(max(sorted_requests)+1)
            positions.append(0)
            for i in range(0, approxValue):
                positions.append(sorted_requests[i])

        x = positions
        y = range(len(positions))
        movements = calculateMovements(positions)
        plot_fig(x, y, "C-Scan (Elevator) Disk Scheduling Visualization", movements)

    def LOOK_Algorithm(requests, head, option_chosen):
        movements = 0
        positions = []
        positions.append(head)
        approxValue = 0
        if option_chosen == "Low":
            sorted_requests = sorted(requests)
            for i in range(0, len(sorted_requests)):
                if sorted_requests[i] <= head:
                    approxValue = i
                else:
                    break
            for j in range(approxValue, -1, -1):
                positions.append(sorted_requests[j])
            for j in range(approxValue+1, len(sorted_requests)):
                positions.append(sorted_requests[j])
        else:
            sorted_requests = sorted(requests)
            for i in range(0, len(sorted_requests)):
                if sorted_requests[i] >= head:
                    approxValue = i
                    break
            for j in range(approxValue, len(sorted_requests)):
                positions.append(sorted_requests[j])
            for j in range(approxValue-1, -1, -1):
                positions.append(sorted_requests[j])
        x = positions
        y = range(len(positions))
        movements = calculateMovements(positions)
        plot_fig(x, y, "Look Disk Scheduling Visualization", movements)

    def C_LOOK_Algorithm(requests, head, option_chosen):
        movements = 0
        positions = []
        positions.append(head)
        approxValue = 0
        if option_chosen == "Low":
            sorted_requests = sorted(requests)
            for i in range(0, len(sorted_requests)):
                if sorted_requests[i] <= head:
                    approxValue = i
                else:
                    break
            for j in range(approxValue, -1, -1):
                positions.append(sorted_requests[j])
            for j in range(len(sorted_requests)-1, approxValue+1, -1):
                positions.append(sorted_requests[j])
        else:
            sorted_requests = sorted(requests)
            for i in range(0, len(sorted_requests)):
                if sorted_requests[i] <= head:
                    approxValue = i
                else:
                    break
            for j in range(approxValue+1, len(sorted_requests)):
                positions.append(sorted_requests[j])
            for j in range(0, approxValue+1):
                positions.append(sorted_requests[j])
        x = positions
        movements = calculateMovements(positions)
        y = range(len(positions))
        plot_fig(x, y, "C-Look Disk Scheduling Visualization", movements)

    st.title("Disk Scheduling\n")
    num_processes = st.number_input("Enter the number of Requests: ", min_value = 1, step = 1)
    try:
        num_processes = int(num_processes)
    except ValueError:
        print("Invalid Error!")
        st.stop()
    option = st.selectbox(
        "Select the Disk Scheduling Algorithm : ",
        ["FCFS", "SSTS", "SCAN", "C-SCAN", "LOOK", "C-LOOK"]
    )
    st.header(f"Enter the {num_processes} Requests\n")
    requests = []
    for i in range(num_processes):
        request = st.number_input(f"Enter the {i+1} Request : ", min_value = 0, step = 1)
        requests.append(request)
    head = st.number_input(f"Enter the head : ", min_value = 0, step = 1)
    if option == "SCAN" or option == "C-SCAN" or option == "LOOK" or option == "C-LOOK":
        option1 = st.selectbox(
            "Moving Towards which cylinder : ",
            ["High", "Low"]
        )
    if st.button("Process"):
        if option == "FCFS":
            FCFS_Algorithm(requests, head)
        elif option == "SSTS":
            SSTS_Algorithm(requests, head)
        elif option == "SCAN":
            SCAN_Algorithm(requests, head, option1)
        elif option == "C-SCAN":
            C_SCAN_Algorithm(requests, head, option1)
        elif option == "LOOK":
            LOOK_Algorithm(requests, head, option1)
        else:
            C_LOOK_Algorithm(requests, head, option1)