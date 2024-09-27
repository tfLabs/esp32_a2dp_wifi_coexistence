
idf_component_register(SRCS "app_main.c" "main.cpp" "Application.cpp" "audio_input/I2SSampler.cpp" "config.cpp" "transports/TCPSocketTransport.cpp" "audio_input/ADCSampler.cpp"
                       INCLUDE_DIRS "." "audio_input" "transports")
