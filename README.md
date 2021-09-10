# Large Scale, High Thoughput System
Timer Lawn: Unbound Low Latency Timer Data Structure for Large Scale, High Thoughput System에 나온 구현을 해본다  
https://arxiv.org/abs/1906.10860  


# 목표
1. C++을 사용해서 구현  
2. multi thread를 활용
2. 최대한 합리적으로 만든다


# 만드는 이유
c++로 리얼 시세 서버를 만드는데 20분 지연을 지원해야했다.  
delay를 지원하는 Redis module에서 딜레이 구현에 사용된 논문을 발견는데, 슈더코드가 재미있어 보여서 만들었다.  


# How to build
```
$ make
$ ./out
```

# Reference
https://github.com/TamarLabs/ReDe  
