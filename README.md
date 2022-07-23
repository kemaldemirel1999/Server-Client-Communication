
-----------------------------------------------------------
1-  server.c
server.c derlenmesi için:
gcc server.c -lpthread -o server.o
-----------------------------------------------------------
2-  client.c
client.c derlenmesi için:
gcc client.c -o client.o
-----------------------------------------------------------
3- Executable dosyaları oluşur ( client.o ve server.o )
client.o çalıştırmak için:
./client.o  

server.o çalıştırmak için:
./server.o 
-----------------------------------------------------------
PROGRAMIN AMACI:

server ve clientlar arasında iletişimin kurulduğu bir programdır. client her 10 saniyede bir 1000 elemanlı randomized bir array oluşturmaktadır ve server'a message passing 
yöntemi ile array'i ve process_id'yi göndermektedir.
Server'da main thread message passing yöntemi ile mesajı almaktadır ve array'in sortlanması için worker thread oluşturup bu görevi ona vermektedir ve 
worker thread sortlanmış array'i istemci process_id ile PID.txt olacak şekilde dosyaya yazmaktadır ve sonrasında istemciye sıralandı şeklinde sinyal göndermektedir.

Bu programda main_thread worker_thread'e görev vermektedir ve worker_thread'in görevinin bitmesini beklemektedir. 
Bu durum için pthread_join kullanılmıştır ve böylece main_thread bloklanmış olmaktadır.
