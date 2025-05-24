import streamlit as st
from process_scheduling_python import process_scheduling_app
from disk_scheduling_python import disk_scheduling_app
from memory_management_python import memory_management_app
from deadlock_detection_python import deadlock_detection_app
from page_fault_python import page_replacement_app
from project_documentation import project_documentation_app

st.sidebar.title("Navigation")
page = st.sidebar.radio("Go to", ["Process Scheduling", "Disk Scheduling", "Memory Management (Visualization - Contiguous)", "Deadlock Detection", "Page Replacement Algorithms Simulator", "Documentation"])
if page == "Process Scheduling":
    process_scheduling_app()
elif page == "Disk Scheduling":
    disk_scheduling_app() 
elif page == "Memory Management (Visualization - Contiguous)":
    memory_management_app()
elif page == "Deadlock Detection":
    deadlock_detection_app()
elif page == "Page Replacement Algorithms Simulator":
    page_replacement_app()
elif page == "Documentation":
    project_documentation_app()