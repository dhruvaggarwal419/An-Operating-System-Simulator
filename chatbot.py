import streamlit as st
import requests
import json

GEMINI_API_KEY = "AIzaSyBUOsiraKCtjS-EQ6bo0ajkTns9GaOe89w"
GEMINI_API_URL = f"https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key={GEMINI_API_KEY}"


def chatbot_integration_app():
    def call_gemini_api(user_message):
        try:
            payload = {
                "contents": [
                    {
                        "parts": [
                            {
                                "text": user_message
                            }
                        ]
                    }
                ],
                "generationConfig": {
                    "temperature": 0.7,
                    "topP": 0.8,
                    "topK": 40,
                    "maxOutputTokens": 1024
                }
            }
            
            headers = {
                "Content-Type": "application/json"
            }
            
            response = requests.post(
                GEMINI_API_URL,
                headers=headers,
                json=payload,
                timeout=30
            )
            
            if response.status_code == 200:
                response_data = response.json()
                
                if "candidates" in response_data and len(response_data["candidates"]) > 0:
                    ai_response = response_data["candidates"][0]["content"]["parts"][0]["text"]
                    return ai_response
                else:
                    return "I couldn't generate a response. Please try again."
            else:
                return f"API Error: {response.status_code}. Please try again."
                
        except requests.exceptions.Timeout:
            return "Request timed out. Please try again."
        except requests.exceptions.ConnectionError:
            return "Connection error. Please check your internet connection."
        except Exception as e:
            return f"An error occurred: {str(e)}"

    def main():
        st.title("🤖 Simple AI Chatbot")
        
        if "messages" not in st.session_state:
            st.session_state.messages = []
        
        with st.sidebar:
            st.header("Chat Controls")
            if st.button("🗑️ Clear Chat", use_container_width=True):
                st.session_state.messages = []
                st.rerun()
        
        for message in st.session_state.messages:
            with st.chat_message(message["role"]):
                st.markdown(message["content"])
        
        if user_input := st.chat_input("Type your message here..."):
            
            st.session_state.messages.append({
                "role": "user",
                "content": user_input
            })
            
            with st.chat_message("user"):
                st.markdown(user_input)
            
            with st.chat_message("assistant"):
                with st.spinner("Thinking..."):
                    ai_response = call_gemini_api(user_input)
                
                st.markdown(ai_response)
            
            st.session_state.messages.append({
                "role": "assistant",
                "content": ai_response
            })

    main()

chatbot_integration_app()