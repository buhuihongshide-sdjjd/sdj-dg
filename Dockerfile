FROM ubuntu:22.04
WORKDIR /app
COPY generate.cpp .
COPY answer.cpp .
RUN apt-get update && apt-get install g++ python3 zip -y
RUN g++ -o generate generate.cpp
RUN g++ -o answer answer.cpp
CMD ["sh", "-c", "./generate && ./answer && zip ./data.zip ./*.in ./*.ans && python3 -m http.server 80"]
