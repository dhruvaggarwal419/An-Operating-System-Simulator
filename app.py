import streamlit as st
from process_scheduling_python import process_scheduling_app
from disk_scheduling_python import disk_scheduling_app
st.sidebar.title("Navigation")
page = st.sidebar.radio("Go to", ["Process Scheduling", "Disk Scheduling"])
if page == "Process Scheduling":
    process_scheduling_app()
elif page == "Disk Scheduling":
    disk_scheduling_app()