
import streamlit as st
import pandas as pd
import joblib

# Load data and model
df = pd.read_csv("cleaned_dataset.csv")
model = joblib.load("tardis_model.pkl")

st.title("TARDIS Train Delay Prediction Dashboard")
st.markdown("Analyze train delay trends and predict future delays based on operational factors.")

# Sidebar inputs
st.sidebar.header("Prediction Input")
input_data = {}

features = [
    "Average journey time",
    "Number of scheduled trains",
    "Number of cancelled trains",
    "Number of trains delayed at departure",
    "Average delay of late trains at departure",
    "Number of trains delayed > 15min",
    "Number of trains delayed > 30min",
    "Number of trains delayed > 60min",
    "Pct delay due to external causes",
    "Pct delay due to infrastructure",
    "Pct delay due to traffic management",
    "Pct delay due to rolling stock",
    "Pct delay due to station management and equipment reuse",
    "Pct delay due to passenger handling (crowding, disabled persons, connections)",
    "Month"
]

for feat in features:
    val = st.sidebar.number_input(feat, value=float(df[feat].mean()))
    input_data[feat] = val

input_df = pd.DataFrame([input_data])

if st.sidebar.button("Predict Delay"):
    prediction = model.predict(input_df)[0]
    st.subheader(f"Predicted Average Arrival Delay: {prediction:.2f} minutes")

st.header("Exploratory Analysis")
st.image("arrival_delay_distribution.png", caption="Arrival Delay Distribution")
st.image("departure_delay_by_station.png", caption="Departure Delay by Station")
st.image("correlation_heatmap.png", caption="Correlation Heatmap")

st.header("Station Summary")
st.dataframe(df.groupby("Departure station")["Average delay of all trains at departure"].mean().sort_values(ascending=False).head(10))
