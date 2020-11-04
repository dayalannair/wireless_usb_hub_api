cmake_minimum_required(VERSION 3.10)

project(proof_of_concept)

add_executable(poc 
RaspberryPi_CC2500_config.c 
RaspberryPi_CC2500_interface.c
)

target_link_libraries(poc wiringPi)