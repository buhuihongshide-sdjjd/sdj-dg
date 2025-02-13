docker build -t generator .
docker run -p 4444:80 -d generator
