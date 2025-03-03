g++ -o generate generate.cpp
g++ -o answer answer.cpp
./generate && ./answer
zip ./data.zip ./*.in ./*.ans
rm ./*.in ./*.ans
rm generate answer