docker build -t gen .
docker run -p 4444:80 -d gen
wget 127.0.0.1:4444/data.zip
docker stop $(docker ps -aq)
docker rmi gen:latest -f