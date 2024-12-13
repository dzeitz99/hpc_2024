FROM ubuntu:trusty

WORKDIR /home/dzeitz/Desktop/hpc_2024/exercise_session_12/exercise_session_12/poisson_solver_serial

COPY /home/dzeitz/Desktop/hpc_2024/exercise_session_12/exercise_session_12/poisson_solver_serial/main.cpp .

RUN sudo apt-get update && apt-get install -y -q g++
RUN sudo pwd
RUN sudo g++ -o main main.cpp

CMD ./main
