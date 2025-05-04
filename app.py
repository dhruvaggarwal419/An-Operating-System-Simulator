import streamlit as st
from process_scheduling_python import process_scheduling_app
from disk_scheduling_python import disk_scheduling_app
from memory_management_python import memory_management_app

st.sidebar.title("Navigation")
page = st.sidebar.radio("Go to", ["Process Scheduling", "Disk Scheduling", "Memory Management (Visualization - Contiguous)"])

if page == "Process Scheduling":
    process_scheduling_app()
elif page == "Disk Scheduling":
    disk_scheduling_app() 
elif page == "Memory Management (Visualization - Contiguous)":
    memory_management_app()